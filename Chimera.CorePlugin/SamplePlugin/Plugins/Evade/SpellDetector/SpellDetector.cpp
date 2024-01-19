#include "SpellDetector.h"

#include "../Evade.h"
#include "../DB/EvadeDB.h"
#include "DetectedSpells/DetectedCircle.h"
#include "DetectedSpells/DetectedCone.h"
#include "DetectedSpells/DetectedCustomShape.h"
#include "DetectedSpells/DetectedLine.h"
#include "DetectedSpells/DetectedMissileLine.h"
#include "DetectedSpells/DetectedPerpendicularLine.h"
#include "DetectedSpells/DetectedRing.h"

void Evade::SpellDetector::initialize()
{
	callbacks<EventType::OnProcessSpellCast>::add_callback(on_process_spell, "SpellDetector");
	callbacks<EventType::OnCreateObject>::add_callback(on_create_object, "SpellDetector");
	callbacks<EventType::OnDeleteObject>::add_callback(on_delete_object, "SpellDetector");
	callbacks<EventType::OnTick>::add_callback(on_tick, "SpellDetector");
	callbacks<EventType::OnDraw>::add_callback(on_draw, "SpellDetector");
}

void Evade::SpellDetector::on_unload()
{
	
}

DetectedSpell* create_detected_spell_on_cast(EvadeSpellData* spell_data, SpellCastInfo* spell, GameObject* source, const Vec2& direction)
{
	DetectedSpell* detected_spell = nullptr;

	switch (spell_data->type)
	{
	case EvadeSpellType::Line:
		if (spell_data->is_perpendicular)
			detected_spell = new DetectedPerpendicularLine(spell_data, spell->get_start_pos().to_2d(), spell->get_end_pos().to_2d());
		else
			detected_spell = new DetectedLine(spell_data, spell->get_start_pos().to_2d(), spell->get_end_pos().to_2d());
		break;
	case EvadeSpellType::MissileLine:
		detected_spell = new DetectedMissileLine(spell_data, spell->get_start_pos().to_2d(), spell->get_end_pos().to_2d());
		break;
	case EvadeSpellType::Circle:
		detected_spell = new DetectedCircle(spell_data, spell->get_start_pos().to_2d(), spell->get_end_pos().to_2d());
		break;
	case EvadeSpellType::Cone:
		detected_spell = new DetectedCone(spell_data, spell->get_start_pos().to_2d(), spell->get_end_pos().to_2d());
		break;
	case EvadeSpellType::Ring:
		detected_spell = new DetectedRing(spell_data, spell->get_end_pos().to_2d());
		break;
	case EvadeSpellType::CustomPolygon:
		detected_spell = new DetectedCustomShape(spell_data, spell->get_start_pos().to_2d(), spell->get_end_pos().to_2d());
		break;
	}

	if (!detected_spell)
		return nullptr;

	detected_spell->source = source;
	detected_spell->target = spell->get_target();
	detected_spell->cast_time = game_time->get_time();
	if (spell_data->object_names.empty())
		detected_spell->end_time = game_time->get_time() + spell_data->delay(detected_spell) + spell_data->duration(detected_spell);

	detected_spell->direction = direction;

	return detected_spell;
}

void add_end_explosion_to_spell(DetectedSpell* spell)
{
	if (!spell->spell_data->end_explosion)
		return;

	auto end_explosion_polygon = spell->spell_data->end_explosion(spell);

	std::vector<Geometry::Polygon> polygons{ spell->polygon, end_explosion_polygon };

	auto clipped_polygons = Geometry::to_polygons(Geometry::clip_polygons(polygons));

	if (clipped_polygons.size() == 1)
		spell->polygon = clipped_polygons[0];
}

Vec3 p1{ };
Vec3 p2{ };

void Evade::SpellDetector::on_process_spell(SpellCastInfo* spell)
{
	if (!spell || spell->is_auto())
		return;

	console->log("[OnProcessSpell] Spell casted: Name: %s Hash: 0x%X",
		spell->get_spell_data()->get_spell_name().c_str(),
		spell->get_spell_data()->get_hash());

	const auto source = spell->get_source();
	if (!source /* || source->is_ally()*/)
		return;

	const auto spell_data = EvadeDB::get_data(spell->get_spell_data()->get_hash());

	if (!spell_data)
		return;

	spell_data->on_process_spell(spell);

	const auto initial_direction = (spell->get_end_pos().to_2d() - spell->get_start_pos().to_2d()).normalized();
	const auto multiple_number = spell_data->multiple_number(source, spell);
	if (multiple_number > 1)
	{
		const auto multiple_angle = spell_data->multiple_angle(source, spell);
		for (int i = -(multiple_number - 1) / 2; i <= (multiple_number - 1) / 2; i++)
		{
			DetectedSpell* detected_spell = create_detected_spell_on_cast(spell_data, spell, source, initial_direction.rotated(multiple_angle * i));
			if (!detected_spell)
				return;

			detected_spells.push_back(detected_spell);
		}

		return;
	}

	p1 = spell->get_start_pos();

	DetectedSpell* detected_spell = create_detected_spell_on_cast(spell_data, spell, source, initial_direction);
	if (!detected_spell)
		return;
	detected_spells.push_back(detected_spell);
	console->info("[OnProcessSpell] Added %s", spell->get_spell_data()->get_spell_name().c_str());
}

void Evade::SpellDetector::on_create_object(GameObject* obj)
{
	if (obj->is_missile())
	{
		console->info("[OnCreateObject] Created missile: %s", obj->get_name().c_str());
		on_create_missile(obj);
	}
}

bool vector_contains_missile_name(const std::vector<std::string>& vector, const std::string& missile_name)
{
	for (const auto& name : vector)
	{
		if (name.find(missile_name) != std::string::npos)
			return true;
	}

	return false;
}

void Evade::SpellDetector::on_create_missile(GameObject* obj)
{
	const auto missile = obj->get_missile_client();
	const auto source = missile->get_source();

	if (!source /*|| !source->is_enemy()*/)
		return;

	const auto start_pos = missile->get_start_position().to_2d();
	const auto end_pos = missile->get_end_position().to_2d();

	for (const auto& spell : detected_spells)
	{
		if (spell->missile != nullptr || spell->spell_data->object_names.empty() || missile->get_source() != spell->source)
			continue;

		const float distance = spell->original_start_pos.distance(start_pos);
		const float angle = spell->direction.distance((end_pos - start_pos).normalized());

		console->log("[OnCreateMissile] Trying to assign missile %s to spell %s. Distance: %.2f Angle: %.2f", 
			obj->get_name().c_str(), 
			spell->spell_data->menu_name, 
			distance, 
			angle);

		if (vector_contains_missile_name(spell->spell_data->object_names, obj->get_name()) 
			&& (spell->spell_data->skip_distance_check || distance < 10.f)
			&& (spell->spell_data->skip_angle_check || angle < .10f))
		{
			console->warn("[OnCreateMissile] **Success**", obj->get_name().c_str());
			spell->missile = obj;
			return;
		}
	}

	const auto spell_data = EvadeDB::get_data(obj->get_name());
	if (!spell_data)
		return;

	DetectedSpell* detected_spell = nullptr;

	switch (spell_data->type)
	{
	case EvadeSpellType::Line:
		detected_spell = new DetectedLine(spell_data, start_pos, end_pos);
		break;
	case EvadeSpellType::MissileLine:
		detected_spell = new DetectedMissileLine(spell_data, start_pos, end_pos);
		break;
	case EvadeSpellType::Circle:
		detected_spell = new DetectedCircle(spell_data, start_pos, end_pos);
		break;
	case EvadeSpellType::Cone:
		detected_spell = new DetectedCone(spell_data, start_pos, end_pos);
		break;
	case EvadeSpellType::Ring:
		detected_spell = new DetectedRing(spell_data, end_pos);
		break;
	case EvadeSpellType::CustomPolygon:
		detected_spell = new DetectedCustomShape(spell_data, start_pos, end_pos);
		break;
	}

	if (!detected_spell)
		return;

	detected_spell->source = source;
	detected_spell->missile = obj;
	detected_spell->direction = (end_pos - start_pos).normalized();

	detected_spells.push_back(detected_spell);
	console->log("[OnCreateMissile] Created new DetectedSpell: %s", detected_spell->spell_data->menu_name);
}

void Evade::SpellDetector::on_delete_object(GameObject* obj)
{
	if (obj->is_missile())
	{
		const auto it = std::remove_if(detected_spells.begin(), detected_spells.end(), [obj](DetectedSpell* spell)
		{
			return spell->missile == obj;
		});

		detected_spells.erase(it, detected_spells.end());
	}
}

void Evade::SpellDetector::on_tick()
{
	if (input->is_key_pressed('M'))
	{
		EvadeSpellData* data = new EvadeSpellData(CharacterHash::Unknown, "Debug");
		data->set_duration(60.f)
			->set_radius(100.f)
			->set_range(1000.f)
			->set_is_range_fixed(true);

		DetectedSpell* spell = new DetectedLine(data, cursor->get_world_position().to_2d(), local_player->get_position().to_2d());
		detected_spells.push_back(spell);
	}

	auto i = detected_spells.begin();
	while (i != detected_spells.end())
	{
		const auto spell = *i;
		if (!spell 
			|| (spell->spell_data->object_names.empty() 
				&& spell->end_time != 0.f 
				&& game_time->get_time() > spell->end_time)
			|| (!spell->spell_data->object_names.empty()
				&& spell->missile == nullptr
				&& game_time->get_time() > spell->cast_time + 1.5f))
		{
			console->log("[OnTick] Erased DetectedSpell: %s", spell->spell_data->menu_name);
			i = detected_spells.erase(i);
			delete spell;
			continue;
		}

		const bool updated = spell->update_polygon();
		if (updated && spell->spell_data->has_end_explosion)
			add_end_explosion_to_spell(spell);

		++i;
	}
}

void Evade::SpellDetector::on_draw()
{
	draw_manager->circle(p1, 20.f, Color(255, 0, 0));
	draw_manager->circle(p2, 20.f, Color(0, 255, 0));

	const auto height = local_player->get_position().y;
	for (const auto& spell : detected_spells)
	{
		bool dangerous = spell->is_path_dangerous(local_player->get_server_position(), cursor->get_world_position(), local_player->get_movement_speed(), .03 + net_client->get_ping() / 2000);

		switch(spell->spell_data->type)
		{
		//case EvadeSpellType::Line:
		//case EvadeSpellType::MissileLine:
		//	if (spell->polygon.points.size() != 4)
		//		break;
		//	//draw_manager->circle(spell->polygon.points[0], 20.f, Color(255, 0, 0));
		//	//draw_manager->circle(spell->polygon.points[2], 20.f, Color(255, 0, 0));
		//	//draw_manager->rectangle_2points(spell->polygon.points[0], spell->polygon.points[2], Color(255, 255, 255, 20), 6.f, 1, true);
		//	break;
		case EvadeSpellType::Circle:
			draw_manager->circle(spell->cached_end_pos.to_3d(height), spell->cached_radius, Color(32, 164, 243, 20), 1, true);
			break;
		default:
			spell->polygon.draw(dangerous ? Color(255, 0, 0, 190) : Color(255, 255, 255, 190), 1.f, false);
		}
	}
}