#pragma once
#include "DetectedSpell.h"

struct DetectedPerpendicularLine : public DetectedSpell
{
	DetectedPerpendicularLine(EvadeSpellData* spell_data, const Vec2& start_pos, const Vec2& end_pos) :
		DetectedSpell(spell_data, start_pos, end_pos) { }

	bool update_polygon() override;
};