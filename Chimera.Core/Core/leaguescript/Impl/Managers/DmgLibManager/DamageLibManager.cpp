#include "../pch.h"
#include "DamageLibManager.h"

DamageLibManager* g_damage_lib = new DamageLibManager();

void DamageLibManager::setCallbacks(
	fn_get_spell_damage get_spell_damage,
	fn_calculate_damage calculate_damage,
	fn_get_auto_attack_damage get_auto_attack_damage)
{
	this->_get_spell_damage = get_spell_damage;
	this->_calculate_damage = calculate_damage;
	this->_get_auto_attack_damage = get_auto_attack_damage;
}

DamageOutput DamageLibManager::get_damage(GameObject* source, GameObject* target, Enums::SpellSlot spell_slot, int stage, int stacks)
{
	if (!_get_spell_damage)
		return { };

	return _get_spell_damage(source, target, spell_slot, stage, stacks);
}

double DamageLibManager::calculate_damage(GameObject* source, GameObject* target, DamageType damage_type, double base_damage)
{
	if (!_calculate_damage)
		return 0.f;

	return _calculate_damage(source, target, damage_type, base_damage);
}

DamageOutput DamageLibManager::get_auto_attack_damage(GameObject* source, GameObject* target, bool include_passive, bool include_items)
{
	if (!_get_auto_attack_damage)
		return { };

	return _get_auto_attack_damage(source, target, include_passive, include_items);
}

void DamageLibManager::remove_callbacks()
{
	_get_spell_damage = nullptr;
	_calculate_damage = nullptr;
	_get_auto_attack_damage = nullptr;
}
