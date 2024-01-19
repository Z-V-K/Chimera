#pragma once

class DamageSpell
{
public:
	DamageSpell(GameObject* source, SlotId spell_slot) : slot(spell_slot)
	{
		const std::vector<float> base_dmg_vector = source->get_spell(slot)->get_spell_data()->mDataValues_BaseDamage();

		// start at 1 because mDataValues_BaseDamage contains 7 values and we want to ignore the 1st one (spell lvl 0).
		for (size_t i = 1; i < base_dmg_vector.size(); i++)
		{
			base_damage[i - 1] = base_dmg_vector[i];
		}
	}

	SlotId slot;

	double base_damage[6] = { 0, 0, 0, 0, 0, 0 };

	bool has_stages = false;
	int stages = 0;

	bool has_stacks = false;
	int stacks = 0;

	bool has_on_hit = false;
	float on_hit_ratio = 1.f;

	std::function<void()> on_update = nullptr;
};