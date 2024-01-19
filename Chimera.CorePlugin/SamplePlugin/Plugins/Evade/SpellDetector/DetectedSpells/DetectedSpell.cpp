#include "DetectedSpell.h"

#include "../../DB/EvadeSpellData.h"

Vec2 DetectedSpell::get_start_pos()
{
	const auto start_pos = spell_data->start_position(this);

	if (start_pos.is_valid())
		return start_pos;

	if (spell_data->is_start_pos_from_unit && source != nullptr)
	{
		original_start_pos = source->get_position().to_2d();
	}

	if (spell_data->offset_start != 0.f && missile == nullptr)
		return original_start_pos.extend(original_end_pos, spell_data->offset_start);

	if (spell_data->type == EvadeSpellType::MissileLine && missile != nullptr)
		return missile->get_position().to_2d().extend(original_start_pos, spell_data->radius(this) * 2);

	return original_start_pos;
}

Vec2 DetectedSpell::get_end_pos()
{
	auto end_pos = spell_data->end_position(this);

	if (end_pos.is_valid())
		return end_pos;

	if (spell_data->is_end_pos_to_unit && source != nullptr)
		return source->get_position().to_2d();

	const auto range = get_range();
	const auto start_pos = spell_data->is_start_pos_from_unit ? cached_start_pos : original_start_pos;

	if (spell_data->is_range_fixed)
		return start_pos.extend(original_end_pos, range);

	if (spell_data->is_range_limited && start_pos.distance(original_end_pos) > range)
		return start_pos.extend(original_end_pos, range + spell_data->extra_range);

	if (spell_data->is_range_min && start_pos.distance(original_end_pos) < spell_data->min_range)
		return start_pos.extend(original_end_pos, spell_data->min_range + spell_data->extra_range);

	return original_end_pos + direction * spell_data->extra_range;
}

float DetectedSpell::get_range()
{
	const float range = spell_data->range(this);
	const float missile_speed = spell_data->missile_speed(this);

	const float calculated_range = original_start_pos.distance(original_end_pos);

	if (spell_data->is_range_min && calculated_range < spell_data->min_range)
		return spell_data->min_range;

	if (spell_data->is_range_limited)
		return std::min(calculated_range, range);

	if (spell_data->type != EvadeSpellType::Circle || range == FLT_MAX || missile_speed == FLT_MAX)
		return range;

	return std::min(calculated_range, range);
}

float DetectedSpell::get_radius()
{	
	return spell_data->radius(this) + 5.f + (spell_data->add_bounding ? local_player->get_bounding_radius() : 0.f);
}

bool DetectedSpell::is_colliding(const Vec2& pos, float delay)
{
	if (spell_data->missile_speed(this) == FLT_MAX)
		return polygon.is_inside(pos.to_3d());


}

float DetectedSpell::displacement_after_time(float delay)
{

}

Vec2 DetectedSpell::pos_after_time(float delay)
{
	return cached_start_pos.extend(cached_end_pos + direction, displacement_after_time(delay));
}

bool DetectedSpell::is_path_dangerous(const Vec3& start, const Vec3& end, float movement_speed, float time)
{
	const Vec2 p1 = start.to_2d();
	const Vec2 p2 = end.to_2d();

	if (spell_data->missile_speed(this) == FLT_MAX || missile == nullptr)
		return polygon.is_inside(start) || polygon.is_inside(end);

	for (size_t i = 0; i < polygon.points.size(); i++)
	{
		Vec2 edge_p1 = polygon.points[i].to_2d();
		Vec2 edge_p2 = polygon.points[i == 0 ? polygon.points.size() - 1 : i - 1].to_2d();

		IntersectionResultVec2 intersection = p1.intersection(p2, edge_p1, edge_p2);

		if (intersection.intersects)
			return true;
	}

	return false;
}