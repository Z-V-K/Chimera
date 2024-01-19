#include "DetectedMissileLine.h"

#include "../../DB/EvadeSpellData.h"

bool DetectedMissileLine::update_polygon()
{
	if (!cached_start_pos.is_valid())
		cached_start_pos = get_start_pos();

	const auto height = local_player->get_position().y;

	const auto start_pos = get_start_pos().to_3d(height);
	const auto end_pos = get_end_pos().to_3d(height);

	cached_start_pos = start_pos.to_2d();

	if (original_start_pos.distance(start_pos.to_2d()) >= original_start_pos.distance(end_pos.to_2d()))
		return false;

	cached_end_pos = end_pos.to_2d();
	cached_radius = get_radius();

	polygon = Geometry::Rectangle(start_pos, end_pos, cached_radius).to_polygon();
	return true;
}
