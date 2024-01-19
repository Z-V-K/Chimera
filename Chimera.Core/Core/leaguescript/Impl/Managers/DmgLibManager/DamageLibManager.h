#pragma once
#include "../Framework/GameObjects/GameObject/GameObject.h"
#include "../Framework/Enums/SpellEnums.h"

enum class DamageType
{
	Raw,
	Physical,
	Magical,
	Hybrid
};

struct DamageOutput
{
	double magical;
	double physical;
	double raw;

	DamageOutput(double magical, double physical, double raw) : magical(magical), physical(physical), raw(raw) { }
	DamageOutput() : magical(0.0), physical(0.0), raw(0.0) { }

	operator double() const { return magical + physical + raw; }

	DamageType get_damage_type() const
	{
		if (magical > 0.0 && physical > 0.0)
			return DamageType::Hybrid;

		if (magical > 0.0)
			return DamageType::Magical;

		if (physical > 0.0)
			return DamageType::Physical;

		if (raw > 0.0)
			return DamageType::Raw;

		return DamageType::Physical;
	}

	DamageOutput& operator +=(DamageOutput other)
	{
		magical += other.magical;
		physical += other.physical;
		raw += other.raw;

		return *this;
	}

	DamageOutput& operator -=(DamageOutput other)
	{
		magical -= other.magical;
		physical -= other.physical;
		raw -= other.raw;

		return *this;
	}
};

class DamageLibManager
{
private:
	typedef DamageOutput(*fn_get_spell_damage)(GameObject*, GameObject*, Enums::SpellSlot, int stage, int stacks);
	typedef double(*fn_calculate_damage)(GameObject*, GameObject*, DamageType, double);
	typedef DamageOutput(*fn_get_auto_attack_damage)(GameObject*, GameObject*, bool, bool);

	fn_get_spell_damage _get_spell_damage = nullptr;
	fn_calculate_damage _calculate_damage = nullptr;
	fn_get_auto_attack_damage _get_auto_attack_damage = nullptr;
public:

	virtual void setCallbacks(
		fn_get_spell_damage get_spell_damage,
		fn_calculate_damage calculate_damage,
		fn_get_auto_attack_damage get_auto_attack_damage
	);

	virtual DamageOutput get_damage(GameObject* source, GameObject* target, Enums::SpellSlot spell_slot, int stage = 1, int stacks = 1);
	virtual double calculate_damage(GameObject* source, GameObject* target, DamageType damage_type, double base_damage);
	virtual DamageOutput get_auto_attack_damage(GameObject* source, GameObject* target, bool include_passive = true, bool include_items = true);

	void remove_callbacks();
};

extern DamageLibManager* g_damage_lib;