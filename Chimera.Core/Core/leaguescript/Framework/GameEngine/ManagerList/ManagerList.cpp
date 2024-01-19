#include "../pch.h"
#include "ManagerList.h"

ManagerTemplate<GameObject>* ManagerList::get_m_hero_list()
{
	return RVA_CAST(ManagerTemplate<GameObject>*, Addresses::ManagerList::M_HeroList);
}

ManagerTemplate<GameObject>* ManagerList::get_m_minion_list()
{
	return RVA_CAST(ManagerTemplate<GameObject>*, Addresses::ManagerList::M_MinionList);
}

ManagerTemplate<GameObject>* ManagerList::get_m_turret_list()
{
	return RVA_CAST(ManagerTemplate<GameObject>*, Addresses::ManagerList::M_TurretList);
}

ManagerTemplate<GameObject>* ManagerList::get_m_missile_list()
{
	return RVA_CAST(ManagerTemplate<GameObject>*, Addresses::ManagerList::M_MissileList);
}

ManagerTemplate<GameObject>* ManagerList::get_m_inhibitor_list()
{
	return RVA_CAST(ManagerTemplate<GameObject>*, Addresses::ManagerList::M_InhibitorList);
}

ManagerTemplate<GameObject>* ManagerList::get_m_attackable_unit_list()
{
	return RVA_CAST(ManagerTemplate<GameObject>*, Addresses::ManagerList::M_AttackableUnitList);
}

std::vector<GameObject*> ManagerList::get_champion_list()
{
	const auto& game_list = get_m_hero_list();
	return { game_list->entities, game_list->entities + game_list->size };
}

std::vector<GameObject*> ManagerList::get_turret_list()
{
	const auto& game_list = get_m_turret_list();
	return { game_list->entities, game_list->entities + game_list->size };
}

std::vector<GameObject*> ManagerList::get_minion_list()
{
	const auto& game_list = get_m_minion_list();

	std::vector<GameObject*> ret = { game_list->entities, game_list->entities + game_list->size };

	return ret;
}

std::vector<GameObject*> ManagerList::get_missile_list()
{
	const auto& game_list = get_m_missile_list();
	return { game_list->entities, game_list->entities + game_list->size };
}

std::vector<GameObject*> ManagerList::get_inhibitor_list()
{
	const auto& game_list = get_m_inhibitor_list();
	return { game_list->entities, game_list->entities + game_list->size };
}

std::vector<GameObject*> ManagerList::get_attackable_unit_list()
{
	const auto& game_list = get_m_attackable_unit_list();
	return { game_list->entities, game_list->entities + game_list->size };
}
