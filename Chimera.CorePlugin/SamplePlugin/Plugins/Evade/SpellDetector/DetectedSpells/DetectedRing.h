#pragma once
#include "DetectedSpell.h"

struct DetectedRing : public DetectedSpell
{
	DetectedRing(EvadeSpellData* spell_data, const Vec2& end_pos) :
		DetectedSpell(spell_data, { }, end_pos) { }

	bool update_polygon() override;
};
