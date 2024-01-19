#pragma once

#include "../Framework/GameEngine/ManagerList/ManagerList.h"

class GameObject;
class MissileClient;

class EntityList
{
public:
	std::vector<GameObject*> heroes { };
	std::vector<GameObject*> ally_heroes { };
	std::vector<GameObject*> enemy_heroes { };

	std::vector<GameObject*> minions { };
	std::vector<GameObject*> ally_minions { };
	std::vector<GameObject*> enemy_minions { };
	std::vector<GameObject*> neutral_minions { };

	std::vector<GameObject*> turrets { };
	std::vector<GameObject*> ally_turrets { };
	std::vector<GameObject*> enemy_turrets { };

	std::vector<GameObject*> inhibitors { };
	std::vector<GameObject*> ally_inhibitors { };
	std::vector<GameObject*> enemy_inhibitors { };

	std::vector<GameObject*> nexus { };
	GameObject* ally_nexus { };
	GameObject* enemy_nexus { };

	std::vector<GameObject*> missiles { };
	std::vector<GameObject*> ally_missiles { };
	std::vector<GameObject*> enemy_missiles { };

	std::vector<GameObject*> clones { };
	std::vector<GameObject*> ally_clones { };
	std::vector<GameObject*> enemy_clones { };

	std::vector<GameObject*> neutral_camps { };

	std::vector<GameObject*> objects { };

	void initialize();
	void add_callbacks();
	void remove_callbacks();
	void add_to_vectors(GameObject* obj);
	void remove_from_vectors(GameObject* obj);
	static void on_create_object(GameObject* obj);
	static void on_delete_object(GameObject* obj);

	// ========== EXPORTED ==========
	virtual std::vector<GameObject*> get_heroes() { return ManagerList::get().get_champion_list(); }
	virtual std::vector<GameObject*> get_minions() { return ManagerList::get().get_minion_list(); }

	virtual std::vector<GameObject*> get_turrets() { return turrets; }
	virtual std::vector<GameObject*> get_ally_turrets() { return ally_turrets; }
	virtual std::vector<GameObject*> get_enemy_turrets() { return enemy_turrets; }

	virtual std::vector<GameObject*> get_inhibitors() { return inhibitors; }
	virtual std::vector<GameObject*> get_ally_inhibitors() { return ally_inhibitors; }
	virtual std::vector<GameObject*> get_enemy_inhibitors() { return enemy_inhibitors; }

	virtual std::vector<GameObject*> get_nexus() { return nexus; }
	virtual GameObject* get_ally_nexus() { return ally_nexus; }
	virtual GameObject* get_enemy_nexus() { return enemy_nexus; }

	virtual std::vector<GameObject*> get_missiles() { return missiles; }
	virtual std::vector<GameObject*> get_ally_missiles() { return ally_missiles; }
	virtual std::vector<GameObject*> get_enemy_missiles() { return enemy_missiles; }

	virtual std::vector<GameObject*> get_clones() { return clones; }
	virtual std::vector<GameObject*> get_ally_clones() { return ally_clones; }
	virtual std::vector<GameObject*> get_enemy_clones() { return enemy_clones; }

	virtual std::vector<GameObject*> get_neutral_camps() { return neutral_camps; }

	virtual std::vector<GameObject*> get_all_objects() { return objects; }
};

extern EntityList* g_entityList;