#include "DetectedRing.h"

#include "../../DB/EvadeSpellData.h"

bool DetectedRing::update_polygon()
{
    if (!cached_start_pos.is_valid())
        cached_start_pos = get_start_pos();

    const auto height = local_player->get_position().y;

    if (spell_data->is_start_pos_from_unit || spell_data->is_start_pos_updated_on_flash)
    {
        const auto start_pos = get_start_pos().to_3d(height);
        cached_start_pos = start_pos.to_2d();
    }

    const auto end_pos = get_end_pos();

    if (cached_end_pos.distance(end_pos) < 1.f)
        return false;

    cached_end_pos = end_pos;
    cached_radius = get_radius();
    polygon = Geometry::Ring(cached_end_pos.to_3d(height), cached_radius, spell_data->ring_radius).to_polygon();
    return true;
}
