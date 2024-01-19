#include "Prediction.h"

#include "AoePrediction.h"
#include "PathsCache.h"
#include "../../SDK/Geometry.h"
#include "../Utils/Collisions.h"


void draw_path(const std::vector<Vec2>& path)
{
	for (int i = 1; i < path.size(); i++)
	{
        const auto p = path[i].to_3d();
        const auto p2 = path[i - 1].to_3d();
        draw_manager->circle(p, 20.f, Color(255, 255, 0, 100), 1, true);
        draw_manager->line(p2, p, Color(255, 0, 0, 100), 2.f);
	}
}

void Prediction::initialize()
{
    PathsCache::get().initialize();

    prediction->set_callbacks(
        &get_prediction
    );
}

GameObject* get_yuumi_attachment(GameObject* yuumi)
{
    for (const auto& hero : entities->get_heroes())
    {
        if (!hero
            || hero->get_team() != yuumi->get_team()
            || !hero->is_valid_target(FLT_MAX)
            || !hero->has_buff(buff_hash("YuumiWAlly"))
            || hero->get_distance(yuumi) > 50.0)
                continue;

        return hero;
    }

    return nullptr;
}

PredictionOutput Prediction::get_prediction(PredictionInput* input)
{
    return get_prediction_internal(input, true, true);
}

PredictionOutput Prediction::get_prediction_internal(PredictionInput* input, bool aoe, bool check_collision)
{
    if (!input)
        return { };

    PredictionOutput prediction { input };
    bool found_prediction = false;

    const auto unit = input->unit;

    if (unit == nullptr || !unit->is_valid_target(FLT_MAX))
      return prediction;

    if (unit->get_character_hash() == CharacterHash::Yuumi)
    {
        if (get_yuumi_attachment(unit) != nullptr)
            return prediction;
    }

    if (aoe)
    {
        input->delay += net_client->get_ping() / 2000.0 + 0.059999998658895493;
        if (input->aoe)
            return AoePrediction::predict(input);
    }

    if (input->range != FLT_MAX && unit->get_position().distance_squared(input->range_check_from()) > pow(input->range * 1.5, 2.0))
        return prediction;

    if (unit->is_hero())
    {
        if (unit->get_path_controller_common()->is_dashing())
        {
            found_prediction = get_dashing_prediction(input, &prediction);
        }
        else
        {
            const auto remaining_time_immobile = unit_immobile_until(unit);
            if (remaining_time_immobile >= 0.0)
            {
                found_prediction = get_immobile_prediction(input, &prediction, remaining_time_immobile);
            }
        }
    }

    if (!found_prediction)
    {
        const auto path = unit->get_path_controller_common()->get_path_2d();
        get_position_on_path(input, &prediction, path, Vec2::path_length(path), unit->get_movement_speed(), true);
    }

    if (input->range != FLT_MAX)
    {
        if (prediction.hit_chance >= HitChance::High
            && input->range_check_from().distance_squared(unit->get_server_position())
                > pow(input->range + input->real_radius() * 3.0 / 4.0, 2.0))
            prediction.hit_chance = HitChance::Medium;

        if (input->range_check_from().distance_squared(prediction.unit_position()) > pow(input->range + (input->type == SkillshotType::Circle ? input->real_radius() : 0.0), 2.0))
            prediction.hit_chance = HitChance::OutOfRange;
    }

    if (check_collision && input->collision && prediction.hit_chance > HitChance::Impossible)
    {
        prediction.collision_objects = Collisions::get_collision({ prediction.cast_position() }, input);

        if (!prediction.collision_objects.empty())
        {
            prediction.hit_chance = HitChance::Collision;
        }
    }

    return prediction;
}

bool Prediction::get_dashing_prediction(PredictionInput* input, PredictionOutput* output)
{
    GapCloserInformation gapcloser_info = anti_gapcloser->get_gapcloser_information(input->unit, true);

    PredictionOutput dash_prediction { input };

    if (gapcloser_info.sender == nullptr && gapcloser_info.target == nullptr)
        return false;

    console->log("Getting dash prediction from: %s", gapcloser_info.sender->get_name().c_str());

    Vec2 vector2 = gapcloser_info.end_position.to_2d();
    PredictionInput input1 = *input;

	std::vector<Vec2> path { };
    path.push_back(input->unit->get_server_position().to_2d());
    path.push_back(vector2);

    double speed = (double)gapcloser_info.speed;

    PredictionOutput position_on_path;
	get_position_on_path(&input1, &position_on_path, path, Vec2::path_length(path), speed);
    if (position_on_path.hit_chance >= HitChance::High && (double)position_on_path.unit_position().to_2d().distance(input->unit->get_server_position().to_2d(), vector2, true) < 200.0)
    {
        position_on_path._cast_position = position_on_path._unit_position;
        position_on_path.hit_chance = HitChance::Dashing;

        *output = position_on_path;
        return true;
    }
    if ((double)gapcloser_info.start_position.distance(gapcloser_info.end_position) > 200.0 
        && (double)input->delay / 2.0 + (double)input->from().to_2d().distance(vector2) / (double)input->speed - 0.25 
			<= (double)input->unit->get_distance(vector2.to_3d()) / (double)gapcloser_info.speed + (double)input->real_radius() / (double)input->unit->get_movement_speed())
    {
        PredictionOutput pred;
        pred._cast_position = vector2.to_3d();
        pred._unit_position = vector2.to_3d();
        pred.hit_chance = HitChance::Dashing;

        *output = pred;
        return true;
    }
    dash_prediction._cast_position = gapcloser_info.end_position;
    dash_prediction._unit_position = gapcloser_info.end_position;

    *output = dash_prediction;
    return true;
}

bool Prediction::get_immobile_prediction(PredictionInput* input, PredictionOutput* output, double remaining_immobile_time)
{
    const auto unit = input->unit;
    const auto server_position = unit->get_server_position();
    const float num = input->delay + unit->get_distance(input->from()) / input->speed;
    if ((double) num <= remaining_immobile_time + (double) input->real_radius() / (double) unit->get_movement_speed())
    {
        output->_cast_position = server_position;
        output->_unit_position = server_position;
        output->hit_chance = HitChance::Immobile;
    }
    if ((double) num - 0.20000000298023224 <= remaining_immobile_time + (double) input->real_radius() / (double) unit->get_movement_speed())
    {
        output->_cast_position = server_position;
        output->_unit_position = server_position;
        output->hit_chance = HitChance::VeryHigh;
    }

    output->_cast_position = server_position;
    output->_unit_position = server_position;
    output->hit_chance = HitChance::Medium;
    return true;
}

bool is_immobilizing_buff(Buff* buff)
{
    return buff->get_type() == BuffType::Charm
        || buff->get_type() == BuffType::Knockup
        || buff->get_type() == BuffType::Stun 
        || buff->get_type() == BuffType::Suppression 
        || buff->get_type() == BuffType::Snare 
        || buff->get_type() == BuffType::Fear 
        || buff->get_type() == BuffType::Taunt 
        || buff->get_type() == BuffType::Knockback 
        || buff->get_type() == BuffType::Asleep;
}

double Prediction::unit_immobile_until(GameObject* unit)
{
    double ret = 0.0;
    
    for (const auto& buff : unit->get_buffs())
    {
        if (!buff || !buff->is_active() || game_time->get_time() > buff->get_end_time() || !is_immobilizing_buff(buff))
            continue;
    
        ret = std::max((float) ret, buff->get_end_time());
    }

    return ret - game_time->get_time();
}

std::vector<Vec2> cut_path(std::vector<Vec2>& path, float distance)
{
    std::vector<Vec2> vector2List{ };
    float num1 = distance;
    if ((double) distance < 0.0)
    {
        path[0] += (path[1] - path[0]).normalized() * distance;
        return path;
    }
    for (int index1 = 0; index1 < path.size() - 1; ++index1)
    {
        float num2 = path[index1].distance(path[index1 + 1]);
        if ((double) num2 > (double) num1)
        {
            vector2List.push_back(path[index1] + (path[index1 + 1] - path[index1]).normalized() * num1);
            for (int index2 = index1 + 1; index2 < path.size(); ++index2)
                vector2List.push_back(path[index2]);
            break;
        }
        num1 -= num2;
    }
    if (!vector2List.empty())
        return vector2List;

    return { path.back() };
}

bool Prediction::get_position_on_path(PredictionInput* input, PredictionOutput* output, std::vector<Vec2> path, const float path_length, float speed, bool fix_speed)
{
    const auto unit = input->unit;
    if (fix_speed && unit->get_position().distance_squared(input->from()) < pow(250, 2.0))
        speed *= 1.5f;

    speed = speed == -1.f ? unit->get_movement_speed() : speed;
    Vec3 server_position = unit->get_server_position();

    if (path.size() <= 1 || (unit->is_winding_up() && !unit->get_path_controller_common()->is_dashing()))
    {
        output->_unit_position = server_position;
        output->_cast_position = server_position;
        output->hit_chance = HitChance::VeryHigh;

        return true;
    }

    if (path.size() == 2 && path_length < 5.0 && (unit->is_practice_tool_dummy() || unit->is_minion() || unit->is_jungle_minion()))
    {
        output->_unit_position = server_position;
        output->_cast_position = server_position;
        output->hit_chance = HitChance::VeryHigh;

        return true;
    }

    if (input->speed == FLT_MAX && path_length >= input->delay * speed - input->real_radius())
    {
        float num = input->delay * speed;

        for (size_t i = 0; i < path.size() - 1; ++i)
        {
            Vec2 vec2_1 = path[i];
            Vec2 to_vec2 = path[i + 1];

            const float distance = vec2_1.distance(to_vec2);

            if (distance >= num)
            {
                Vec2 vec2_2 = (to_vec2 - vec2_1).normalized();
                Vec2 vec2_3 = vec2_1 + vec2_2 * num;
                Vec2 vec2_4 = vec2_1 + vec2_2 * (i == path.size() - 2 ? std::min(num + input->real_radius(), distance) : num + input->real_radius());

                output->_cast_position = vec2_3.to_3d();
                output->_unit_position = vec2_4.to_3d();
                output->hit_chance = get_hitchance(unit);

                return true;
            }

            num -= distance;
        }
    }

    if (input->speed != FLT_MAX && path_length >= input->delay * speed - input->real_radius())
    {
        float distance = input->delay * speed;

        if ((input->type == SkillshotType::Line || input->type == SkillshotType::Cone) && input->from().distance_squared(server_position) < pow(200.0, 2.0))
            distance = input->delay * speed;

        path = cut_path(path, distance);
        float delay = 0.f;

        for (int index = 0; index < path.size() - 1; ++index)
        {
            Vec2 vec2_5 = path[index];
            Vec2 vec2_6 = path[index + 1];

            float num = vec2_5.distance(vec2_6) / speed;        // time to reach 2_6 from 2_5. t = d/v
            Vec2 vec2_7 = (vec2_6 - vec2_5).normalized();       // direction from 2_5 to 2_6

            const auto movement_collision = Vec2::vec2_movement_collision((vec2_5 - vec2_7 * speed * delay), vec2_6, speed, input->from().to_2d(), input->speed, delay);
            float collision_time = movement_collision.t;
            Vec2 collision_pos = movement_collision.pos;

            if (collision_pos.is_valid() && collision_time >= delay && collision_time <= delay + num)
            {
	            if (collision_pos.distance_squared(vec2_6) >= 20.0)
	            {
                    Vec2 vec2_8 = collision_pos - vec2_7 * input->real_radius();
                    output->_cast_position = collision_pos.to_3d();
                    output->_unit_position = vec2_8.to_3d();
                    output->hit_chance = get_hitchance(unit);


                    return true;
	            }
                break;
            }

            delay += num;
        }
    }

    Vec2 vec2 = path.back();
    output->_cast_position = vec2.to_3d();
    output->_unit_position = vec2.to_3d();
    output->hit_chance = HitChance::Medium;
    return true;
}

HitChance Prediction::get_hitchance(GameObject* unit)
{
    return unit->is_hero() && PathsCache::get().get_current_path(unit).time() >= .1 ? HitChance::High : HitChance::VeryHigh;
}