#pragma once

#include "../Impl/Common/Common.h"
#include "../Framework/GameObjects/GameObject/GameObject.h"
#include "../Framework/Containers/ManagerTemplate.h"
#include "../Impl/Singleton/Singleton.h"

class ManagerList : public singleton<ManagerList>
{
private:
	ManagerTemplate<GameObject>* get_m_hero_list();
	ManagerTemplate<GameObject>* get_m_minion_list();
	ManagerTemplate<GameObject>* get_m_turret_list();
	ManagerTemplate<GameObject>* get_m_missile_list();
	ManagerTemplate<GameObject>* get_m_inhibitor_list();
	ManagerTemplate<GameObject>* get_m_attackable_unit_list();
public:
	std::vector<GameObject*> get_champion_list();
	std::vector<GameObject*> get_minion_list();
	std::vector<GameObject*> get_turret_list();
	std::vector<GameObject*> get_missile_list();
	std::vector<GameObject*> get_inhibitor_list();
	std::vector<GameObject*> get_attackable_unit_list();
};
