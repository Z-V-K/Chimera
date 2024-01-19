#include "AoePrediction.h"

#include "Prediction.h"
#include "../../SDK/Geometry.h"

PredictionOutput get_line_prediction(PredictionInput* input);
PredictionOutput get_circle_prediction(PredictionInput* input);
PredictionOutput get_cone_prediction(PredictionInput* input);

PredictionOutput AoePrediction::predict(PredictionInput* input)
{
    switch (input->type)
    {
    case SkillshotType::Line:
        return get_line_prediction(input);
    case SkillshotType::Circle:
        return get_circle_prediction(input);
    case SkillshotType::Cone:
        return get_cone_prediction(input);
    default:
        return { };
    }
}

std::vector<PossibleTarget> get_possible_targets(PredictionInput* input)
{
    std::vector<PossibleTarget> possible_targets { };
    const auto original_unit = input->unit;
    for(const auto& hero : entities->get_heroes())
    {
        if (!hero->is_enemy() 
            || hero == original_unit
            || !hero->is_valid_target(input->range + 200.f + input->real_radius(), input->range_check_from()))
            continue;

        input->unit = hero;
        PredictionOutput prediction = Prediction::get_prediction_internal(input, false, false);
        if (prediction.hit_chance >= HitChance::Medium)
            possible_targets.push_back({ prediction.unit_position().to_2d(), hero });
    }
    return possible_targets;
}

std::vector<Vec2> get_line_candidates(const Vec2& from, const Vec2& to, float range, const Vec2& end_position)
{
    Vec2 segment_end = from.extend(end_position, range);
    ProjectionInfo projection_info = to.project_on(from, segment_end);
    if (!projection_info.is_on_segment)
        return { };

    return { projection_info.segment_point };
}

std::pair<int, std::vector<PossibleTarget>> get_line_hits(const Vec2& start, Vec2& end, double radius, const std::vector<PossibleTarget>& targets)
{
    int num = 0;
    std::vector<PossibleTarget> possible_targets_list { };
    for (const auto& target : targets)
    {
	    if (target.position.distance_squared(start, end, true) < pow(radius, 2.0))
	    {
            ++num;
            possible_targets_list.push_back(target);
	    }
    }

    return { num, possible_targets_list };
}

std::pair<int, std::vector<GameObject*>> get_cone_hits(const Vec2& end, double range, float angle, const std::vector<PossibleTarget>& targets)
{
    int num = 0;

    std::vector<GameObject*> ai_hero_client_list{ };

    for (const auto& target : targets)
    {
        Vec2 vector2 = end.rotated((float)(-(double)angle / 2.0));
        Vec2 other = vector2.rotated(angle);

        if (target.position.distance_squared(Vec2()) < pow(range, 2.0) && vector2.cross_product(target.position) > 0.0 && target.position.cross_product(other) > 0.0)
        {
            ++num;
            ai_hero_client_list.push_back(target.unit);
        }
    }

    return { num, ai_hero_client_list };
}

PredictionOutput get_line_prediction(PredictionInput* input)
{
    const auto unit = input->unit;

    if (!unit || !unit->is_hero())
        return { };

    PredictionOutput prediction = Prediction::get_prediction_internal(input, false, true);
    std::vector<PossibleTarget> possible_targets{ { prediction.unit_position().to_2d(), unit } };
    if (prediction.hit_chance >= HitChance::Medium)
    {
        const auto tmp_targets = get_possible_targets(input);
        possible_targets.insert(possible_targets.end(), tmp_targets.begin(), tmp_targets.end());
    }
    if (possible_targets.size() > 1)
    {
        std::vector<Vec2> vec2_list{ };

        for (const auto& possible_target : possible_targets)
        {
            const auto line_candidates = get_line_candidates(input->from().to_2d(), possible_target.position, input->range, possible_targets[0].position);
            vec2_list.insert(vec2_list.end(), line_candidates.begin(), line_candidates.end());
        }

        int num1 = -1;
        Vec2 vec2_1 { };
        std::vector<PossibleTarget> source{ };
        for (auto& vec2_2 : vec2_list)
        {
	        if (possible_targets[0].position.distance_squared(input->from().to_2d(), vec2_2, true) <= pow(input->real_radius(), 2.0))
	        {
                const auto line_hits = get_line_hits(input->from().to_2d(), vec2_2, input->real_radius(), possible_targets);

                if (line_hits.first >= num1)
                {
                    num1 = line_hits.first;
                    vec2_1 = vec2_2;
                    source = line_hits.second;
                }
	        }
        }

        if (num1 > 1)
        {
            float num2 = -1.f;
            Vec2 vec2_3{ };
            Vec2 vec2_4{ };
            std::vector<Vec2> list{ };
            list.reserve(possible_targets.size());
            for (const auto& t : possible_targets)
                list.push_back(t.position);

            for (int index1 = 0; index1 < source.size(); ++index1)
            {
                for (int index2 = 0; index2 < source.size(); ++index2)
                {
                    Vec2 vector2_5 = input->from().to_2d();
                    Vec2 segment_end = vec2_1;
                    ProjectionInfo projection_info1 = list[index1].project_on(vector2_5, segment_end);
                    ProjectionInfo projection_info2 = list[index2].project_on(vector2_5, segment_end);
                    float num3 = source[index1].position.distance_squared(projection_info1.line_point) + source[index2].position.distance_squared(projection_info2.line_point);
                    if ((double)num3 >= (double)num2 && (double)(projection_info1.line_point - list[index1]).angle_between(projection_info2.line_point - list[index2]) > 90.0)
                    {
                        num2 = num3;
                        vec2_3 = list[index1];
                        vec2_4 = list[index2];
                    }
                }
            }

            PredictionOutput ret;

            ret.input = input;
            ret._cast_position = ((vec2_3 + vec2_4) * .5f).to_3d();
            ret.hit_chance = prediction.hit_chance;
            ret._unit_position = prediction.unit_position();

            for (const auto& t : possible_targets)
                ret.aoe_targets_hit.push_back(t.unit);

            return ret;
        }
    }
	
    return prediction;
}

PredictionOutput get_circle_prediction(PredictionInput* input)
{
    const auto unit = input->unit;

    if (unit == nullptr || !unit->is_hero())
        return { };

    PredictionOutput prediction = Prediction::get_prediction_internal(input, false, true);
    std::vector<PossibleTarget> source = { { prediction.unit_position().to_2d(), unit } };

    if (prediction.hit_chance >= HitChance::Medium)
    {
        const auto tmp_targets = get_possible_targets(input);
        source.insert(source.end(), tmp_targets.begin(), tmp_targets.end());
    }

    std::vector<Vec2> source_pos{ };
    source_pos.reserve(source.size());
    for (const auto& elt : source)
        source_pos.push_back(elt.position);

    while (source.size() > 1)
    {
        const auto mec = Geometry::Mec::get_mec(source_pos);

        if (mec.radius <= input->real_radius() - 10.0 && mec.center.distance_squared(input->range_check_from().to_2d()) < pow(input->range, 2.0))
        {
            PredictionOutput ret{ };
            ret.input = input;
            ret._cast_position = mec.center.to_3d();
            ret._unit_position = prediction.unit_position();
            ret.hit_chance = prediction.hit_chance;
            for (const auto& t : source)
                ret.aoe_targets_hit.push_back(t.unit);

            return ret;
        }

        float num1 = 1.f;
        int index1 = 1;

        for (int index2 = 1; index2 < source.size(); ++index2)
        {
            float num2 = source[index2].position.distance_squared(source[0].position);
            if (num2 > num1 || Math::NearEqual(num1, -1.f))
            {
                index1 = index2;
                num1 = num2;
            }
        }

        source.erase(source.begin() + index1);
    }

    return prediction;
}

PredictionOutput get_cone_prediction(PredictionInput* input)
{
    const auto unit = input->unit;

    if (!unit || !unit->is_hero())
        return { };

    PredictionOutput prediction = Prediction::get_prediction_internal(input, false, true);

    std::vector<PossibleTarget> targets{ { prediction.unit_position().to_2d(), unit } };
    if (prediction.hit_chance >= HitChance::Medium)
    {
        const auto tmp_targets = get_possible_targets(input);
        targets.insert(targets.end(), tmp_targets.begin(), tmp_targets.end());
    }

    if (targets.size() > 1)
    {
        std::vector<Vec2> vec2_list { };
        for (auto& t : targets)
            t.position -= input->from().to_2d();

        for (int index1 = 0; index1 < targets.size(); ++index1)
        {
            for (int index2 = 0; index2 < targets.size(); ++index2)
            {
                if (index1 != index2)
                {
                    Vec2 vector2 = (targets[index1].position + targets[index2].position) * 0.5f;
                    if (std::find(vec2_list.begin(), vec2_list.end(), vector2) == vec2_list.end())
                        vec2_list.push_back(vector2);
                }
            }
        }
        int num = -1;
        std::vector<GameObject*> ai_hero_client_list{ };
        Vec2 vec2_1 { };

        for (const auto& end : vec2_list)
        {
            const auto cone_hits = get_cone_hits(end, input->range, input->real_radius(), targets);
            if (cone_hits.first > num)
            {
                vec2_1 = end;
                ai_hero_client_list = cone_hits.second;
                num = cone_hits.first;
            }
        }
        
        Vec2 vec2_2 = vec2_1 + input->from().to_2d();
        if (num > 1 && (double)input->from().to_2d().distance_squared(vec2_2) > pow(50.0, 2.0))
        {
            PredictionOutput ret{ };
            ret.hit_chance = prediction.hit_chance;
            ret.aoe_targets_hit = ai_hero_client_list;
            ret._unit_position = prediction.unit_position();
            ret._cast_position = vec2_2.to_3d();
            ret.input = input;

            return ret;
        }
    }

    return prediction;
}