#pragma once

struct DamagePassive
{
	virtual ~DamagePassive() = default;

	CharacterHash champion = CharacterHash::Unknown;
	std::function<bool(GameObject* obj)> overwrite_attack_damage = [](GameObject* obj){ return false; };

	DamagePassive(CharacterHash champion) : champion(champion) { }
	virtual DamageOutput get_damage(GameObject* source, GameObject* target) = 0;
	virtual bool is_active(GameObject* source, GameObject* target) = 0;
};