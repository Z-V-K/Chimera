#include "DetectedLine.h"

#include "../../DB/EvadeSpellData.h"

bool DetectedLine::update_polygon()
{
	if (!cached_start_pos.is_valid())
		cached_start_pos = get_start_pos();

	const auto height = local_player->get_position().y;

	if (spell_data->is_start_pos_from_unit || spell_data->is_start_pos_updated_on_flash)
	{
		const auto start_pos = get_start_pos().to_3d(height);
		cached_start_pos = start_pos.to_2d();
	}

	const auto start_pos = cached_start_pos.to_3d(height);
	const auto end_pos = get_end_pos().to_3d(height);

	if (end_pos.to_2d().distance(cached_end_pos) < 1.f)
		return false;

	cached_end_pos = end_pos.to_2d();
	cached_radius = get_radius();

	polygon = Geometry::Rectangle(start_pos, end_pos, cached_radius).to_polygon();
	return true;
}
