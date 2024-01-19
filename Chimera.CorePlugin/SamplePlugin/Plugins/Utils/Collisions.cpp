#include "Collisions.h"

#include "../Prediction/Prediction.h"

void Collisions::initialize()
{
	for (const auto& hero : entities->get_heroes())
	{
		// we even check for allies since there can be viego in enemy team
		if (hero->get_character_hash() == CharacterHash::Yasuo)
			yasuo_in_game = true;
		if (hero->get_character_hash() == CharacterHash::Samira)
			samira_in_game = true;
	}

	callbacks<EventType::OnCreateObject>::add_callback(on_create, "Collisions");
	callbacks<EventType::OnDeleteObject>::add_callback(on_delete, "Collisions");
	callbacks<EventType::OnProcessSpellCast>::add_callback(on_process_spell_cast, "Collisions");
}

void Collisions::on_create(GameObject* obj)
{
	if (!yasuo_in_game || !obj || !obj->is_missile())
		return;

	if (const auto src = obj->get_missile_client()->get_source())
	{
		if (obj->is_enemy() && obj->get_name().find("WChildMis") != std::string::npos)
		{
			if (!windwalls.contains(src->get_network_id()))
			{
				windwalls.insert({ src->get_network_id(), { src, obj, nullptr } });
			}
			else if(windwalls.count(src->get_network_id()) == 1 && windwalls[src->get_network_id()].p2 == nullptr)
			{
				windwalls[src->get_network_id()].p2 = obj;
			}
		}
	}
}

void Collisions::on_delete(GameObject* obj)
{
	if (!yasuo_in_game || !obj || !obj->is_missile())
		return;

	if (obj->get_name() == "YasuoW_VisualMis")
	{
		if (const auto src = obj->get_missile_client()->get_source())
		{
			windwalls.erase(src->get_network_id());
		}
	}
}

void Collisions::on_process_spell_cast(SpellCastInfo* spell)
{
	if (!spell || !spell->is_spell())
		return;

	const auto source = spell->get_source();
	if (!source || !source->is_enemy() || source->get_character_hash() != CharacterHash::Yasuo || spell->get_slot() != SlotId::W)
		return;

	wall_cast_t = game_time->get_tick_count();
}

std::vector<GameObject*> Collisions::get_collision(const std::vector<Vec3>& positions, PredictionInput* input)
{
    std::unordered_set<GameObject*> source{ };

    for (const auto& position : positions)
    {
        if (!position.is_valid())
            continue;

        Vec2 position_2d = position.to_2d();

        if (vector_contains(input->collision_objects, CollisionObject::Heroes))
        {
	        for (const auto& hero : entities->get_heroes())
	        {
                if ((hero->is_ally() && !vector_contains(input->collision_objects, CollisionObject::Allies))
                    || hero == input->unit 
                    || !hero->is_valid_target(std::min((float)((double)input->range + (double)input->radius + 100.0), 2000.f), input->range_check_from()))
                    continue;

                input->unit = hero;
                Vec2 vector2 = Prediction::get_prediction_internal(input, false, false).unit_position().to_2d();

                float num = (float)((double)input->real_radius());
                ProjectionInfo projection_info = vector2.project_on(input->from().to_2d(), position_2d);

                if (projection_info.is_on_segment && ((double)projection_info.segment_point.distance(vector2) <= (double)num || (double)projection_info.line_point.distance(vector2) <= (double)num))
                {
                    source.insert(hero);
                }
	        }
        }

        if (vector_contains(input->collision_objects, CollisionObject::Minions))
        {
	        for (const auto& minion : entities->get_minions())
	        {
                if (!minion
                    || minion->is_ally()
                    || minion == input->unit
                    || !minion->is_valid_target(std::min((float)((double)input->range + (double)input->radius + 100.0), 2000.f), input->range_check_from()))
                    continue;

                float distance = minion->get_server_position().distance(input->from());
                float num1 = minion->get_bounding_radius() + input->unit->get_bounding_radius();
                if (!will_die(input, minion, distance))
                {
                    if ((double)distance < (double)num1 || (double)minion->get_server_position().distance(position) < (double)num1 || (double)minion->get_server_position().distance(input->unit->get_server_position()) < (double)num1)
                    {
                        source.insert(minion);
                    }
                    else
                    {
                        Vec3 vector3 = minion->get_server_position();
                        int num2 = minion->is_jungle_minion() ? 20 : 15;
                        if (minion->get_path_controller_common()->is_moving())
                        {
                            PredictionInput new_input{ };
                            new_input.collision = false;
                            new_input.speed = input->speed;
                            new_input.delay = input->delay;
                            new_input.range = input->range;
                            new_input._from = input->from();
                            new_input.radius = input->radius;
                            new_input.unit = minion;
                            new_input.type = input->type;
                            vector3 = Prediction::get_prediction(&new_input).cast_position();
                            num2 = 50 + (int)input->radius;
                        }

                        Vec2 pos_2d = position.to_2d();
                        if ((double)vector3.to_2d().distance_squared(input->from().to_2d(), pos_2d, true) <= pow((double)input->radius + (double)num2 + (double)minion->get_bounding_radius(), 2.0))
                            source.insert(minion);
                    }
                }
	        }
        }

        if (vector_contains(input->collision_objects, CollisionObject::GameWall))
        {
            float num = position.distance(input->from()) / 10.f;
            for (int index = 0; index < 9; ++index)
            {
                Vec2 vector2 = input->from().to_2d().extend(position.to_2d(), num * (float)index);
                if ((nav_mesh->get_pos_flags(vector2.to_3d()) & CellFlags::Wall) == CellFlags::Wall)
                    source.insert(local_player);
            }
        }

        if (vector_contains(input->collision_objects, CollisionObject::YasuoWall) && game_time->get_tick_count() - wall_cast_t <= 4000)
        {
            if (yasuo_in_game)
            {
                for (const auto& wall : std::views::values(windwalls))
                {
                    if (!wall.p1 || !wall.p2)
                        continue;

                    Vec2 p1 = wall.p1->get_server_position().to_2d();
                    Vec2 p2 = wall.p2->get_server_position().to_2d();
                    Vec2 pos_2d = position.to_2d();
                    Vec2 from_2d = input->from().to_2d();

                    if (p1.intersection(p2, pos_2d, from_2d).intersects)
                        source.insert(local_player);
                }
            }

            if (samira_in_game)
            {
	            for (const auto& hero : entities->get_heroes())
	            {
                    if (hero->is_ally() || !hero->is_alive() || !hero->has_buff(buff_hash("SamiraW")))
                        continue;

                    float num = 325.f + input->radius;
                    if ((double)hero->get_server_position().distance(input->from()) <= (double)num)
                        source.insert(local_player);
                    else if ((double)position.distance(hero->get_server_position()) <= (double)num)
                    {
                        source.insert(local_player);
                    }
                    else
                    {
                        Vec2 pos_2d = hero->get_server_position().to_2d();
                        ProjectionInfo projection_info = pos_2d.project_on(input->from().to_2d(), position_2d);
                        if (projection_info.is_on_segment
                            && ((double)projection_info.segment_point.distance(position.to_2d()) <= (double)num
                                || (double)projection_info.line_point.distance(position.to_2d()) <= (double)num))
                            source.insert(local_player);
                    }
	            }
            }
        }
    }

    return std::vector(source.begin(), source.end());
}

bool Collisions::is_collision(const std::vector<Vec3>& positions, PredictionInput* input)
{
	return !get_collision(positions, input).empty();
}

bool Collisions::has_yasuo_windwall_collision(const Vec3& start, const Vec3& end)
{
	return has_yasuo_windwall_collision(start, end, 50.f);
}

bool Collisions::has_yasuo_windwall_collision(const Vec3& start, const Vec3& end, float extra_radius)
{
	if (samira_in_game)
	{
		for (const auto& target : entities->get_heroes())
		{
			if (!target->is_hero() || target->get_character_hash() != CharacterHash::Samira || !target->is_alive())
				continue;

			if (target->has_buff(buff_hash("SamiraW")))
			{
				float num = 325.f + extra_radius;
				if (target->get_server_position().distance(start) <= num || end.distance(target->get_server_position()) <= num)
					return true;

				Vec2 end_proj = target->get_server_position().to_2d();
				ProjectionInfo projection_info = end.to_2d().project_on(start.to_2d(), end_proj);
				if (projection_info.is_on_segment && (projection_info.segment_point.distance(end.to_2d()) <= num || projection_info.line_point.distance(end.to_2d()) <= num))
					return true;
			}
		}
	}

	return false;
}

bool Collisions::will_die(PredictionInput* input, GameObject* minion, float distance)
{
	if (!minion || !minion->is_minion())
		return false;

	float num = distance / input->speed + input->delay;
	if (input->speed == FLT_MAX)
		num = input->delay;
	int time = (int)((double)num * 1000.0) - net_client->get_ping();
	return (double)health_pred->get_health_prediction(minion, time, 0) <= 0.0;
}
