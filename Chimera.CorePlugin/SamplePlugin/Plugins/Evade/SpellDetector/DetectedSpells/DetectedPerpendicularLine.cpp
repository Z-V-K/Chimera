#include "DetectedPerpendicularLine.h"

#include "../../DB/EvadeSpellData.h"

bool DetectedPerpendicularLine::update_polygon()
{
	if (!cached_start_pos.is_valid())
		cached_start_pos = get_start_pos();

	const auto og_end_pos = get_end_pos();

	if (cached_end_pos.distance(og_end_pos) > 1.f)
		cached_end_pos = get_end_pos();
	else
		return false;

	const auto height = local_player->get_position().y;

	const Vec2 perpendicular_dir = direction.perpendicular();
	const Vec2 start_pos = cached_end_pos - perpendicular_dir * spell_data->perpendicular_length;
	const Vec2 end_pos = cached_end_pos + perpendicular_dir * spell_data->perpendicular_length;

	cached_radius = get_radius();

	polygon = Geometry::Rectangle(start_pos.to_3d(height), end_pos.to_3d(height), cached_radius).to_polygon();
	return true;
}
