#pragma once

#include "DamageSpell.h"

class DamageChamp
{
public:

	DamageChamp(GameObject* src) : src(src)
	{
		Q = new DamageSpell(src, SlotId::Q);
		W = new DamageSpell(src, SlotId::W);
		E = new DamageSpell(src, SlotId::E);
		R = new DamageSpell(src, SlotId::R);
	}

	virtual ~DamageChamp() = default;

	GameObject* src;

	DamageSpell* Q;
	DamageSpell* W;
	DamageSpell* E;
	DamageSpell* R;

	virtual DamageOutput get_damage(GameObject* target, SlotId spell_slot, int level, int stage = 1, int stacks = 1) = 0;

	DamageSpell* get_spell(SlotId slot_id) const
	{
		if (slot_id == SlotId::Q)
			return Q;
		if (slot_id == SlotId::W)
			return W;
		if (slot_id == SlotId::E)
			return E;
		if (slot_id == SlotId::R)
			return R;

		return nullptr;
	}
};