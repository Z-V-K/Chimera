#include "../pch.h"
#include "EntityList.h"

#include "../Common/Utils.h"
#include "../Framework/GameEngine/ObjectManager/ObjectManager.h"
#include "../Impl/Managers/EventManager/EventManager.h"


class Utils;
EntityList* g_entityList = new EntityList();

void EntityList::initialize()
{
	ObjectManager* objManager{ ObjectManager::get_instance() };
	GameObject* gameObject{ objManager->get_first_object() };

	while (gameObject) {
		add_to_vectors(gameObject);

		gameObject = objManager->get_next_object(gameObject);
	}

	add_callbacks();
}

void EntityList::add_callbacks()
{
	g_event_manager->add_event(Enums::OnCreateObject, on_create_object, "EntityList");
	g_event_manager->add_event(Enums::OnDeleteObject, on_delete_object, "EntityList");
}

void EntityList::remove_callbacks()
{
	g_event_manager->remove_event(Enums::OnCreateObject, on_create_object);
	g_event_manager->remove_event(Enums::OnDeleteObject, on_delete_object);
}

void EntityList::add_to_vectors(GameObject* obj)
{
	if (!obj)
		return;

	objects.push_back(obj);

	if (obj->get_name().find(skCrypt("monsterCamp_")) != std::string::npos)
	{
		neutral_camps.push_back(obj);

		return;
	}

	if (obj->is_missile())
	{
		missiles.push_back(obj);

		if (obj->is_ally())
			ally_missiles.push_back(obj);
		else if (obj->is_enemy())
			enemy_missiles.push_back(obj);

		return;
	}

	//if (obj->is_champion() || obj->is_practice_tool_dummy())
	//{
	//	heroes.push_back(obj);

	//	if (obj->is_ally())
	//		ally_heroes.push_back(obj);
	//	else if (obj->is_enemy())
	//		enemy_heroes.push_back(obj);
	//}

	if (obj->is_turret())
	{
		turrets.push_back(obj);

		if (obj->is_ally())
			ally_turrets.push_back(obj);
		else if (obj->is_enemy())
			enemy_turrets.push_back(obj);
	}

	if (obj->is_minion())
	{
		if (obj->is_clone())
		{
			clones.push_back(obj);

			if (obj->is_ally())
				ally_clones.push_back(obj);
			else if (obj->is_enemy())
				enemy_clones.push_back(obj);

			return;
		}

		//minions.push_back(obj);

		//if (obj->is_ally())
		//	ally_minions.push_back(obj);
		//else if (obj->is_enemy())
		//	enemy_minions.push_back(obj);
		//else if (obj->is_neutral())
		//	neutral_minions.push_back(obj);
	}

	if (obj->is_inhibitor())
	{
		inhibitors.push_back(obj);

		if (obj->is_ally())
			ally_inhibitors.push_back(obj);
		else if (obj->is_enemy())
			enemy_inhibitors.push_back(obj);
	}

	if (obj->is_nexus())
	{
		nexus.push_back(obj);

		if (obj->is_ally())
			ally_nexus = obj;
		else if (obj->is_enemy())
			enemy_nexus = obj;
	}
}

void EntityList::remove_from_vectors(GameObject* obj)
{
	if (!obj)
		return;

	std::erase(objects, obj);

	if (obj->is_neutral_camp())
	{
		std::erase(neutral_camps, obj);

		return;
	}

	if (obj->is_missile())
	{
		std::erase(missiles, obj);

		if (obj->is_ally())
			std::erase(missiles, obj);
		else if (obj->is_enemy())
			std::erase(missiles, obj);

		return;
	}

	if (obj->is_turret())
	{
		std::erase(turrets, obj);

		if (obj->is_ally())
			std::erase(ally_turrets, obj);
		else if (obj->is_enemy())
			std::erase(enemy_turrets, obj);
	}

	if (obj->is_minion())
	{
		if (obj->is_clone())
		{
			std::erase(clones, obj);

			if (obj->is_ally())
				std::erase(ally_clones, obj);
			else if (obj->is_enemy())
				std::erase(enemy_clones, obj);

			return;
		}

	/*	std::erase(minions, obj);

		if (obj->is_ally())
			std::erase(ally_minions, obj);
		else if (obj->is_enemy())
			std::erase(enemy_minions, obj);
		else if (obj->is_neutral())
			std::erase(neutral_minions, obj);*/
	}

	if (obj->is_inhibitor())
	{
		std::erase(inhibitors, obj);

		if (obj->is_ally())
			std::erase(ally_inhibitors, obj);
		else if (obj->is_enemy())
			std::erase(enemy_inhibitors, obj);
	}

	if (obj->is_nexus())
	{
		std::erase(nexus, obj);

		if (obj->is_ally())
			ally_nexus = nullptr;
		else if (obj->is_enemy())
			enemy_nexus = nullptr;
	}
}

void EntityList::on_create_object(GameObject* obj)
{
	g_entityList->add_to_vectors(obj);
}

void EntityList::on_delete_object(GameObject* obj)
{
	g_entityList->remove_from_vectors(obj);
}