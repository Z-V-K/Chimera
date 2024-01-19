#include "../pch.h"
#include "EventManager.h"

EventManager* g_event_manager = new EventManager();

void EventManager::add_event(Enums::EventType cbType, void* fct, const char* name)
{
	m_Callbacks[cbType].push_back({ fct, name });
}

void EventManager::add_event(Enums::EventType cbType, luabridge::LuaRef fct)
{
	m_CallbacksLua[cbType].push_back(fct);	
}

bool EventManager::remove_event(Enums::EventType cbType, void* fct)
{
	auto f = &m_Callbacks[cbType];

	std::erase_if(*f, [fct](const callback& cb) { return cb.func == fct; });
	return false;
}

bool EventManager::remove_event(Enums::EventType cbType, luabridge::LuaRef fct)
{
	auto f = &m_CallbacksLua[cbType];

	const auto it = std::find(f->begin(), f->end(), fct);

	if(it != f->end())
	{
		f->erase(it);
		return true;
	}

	return false;
}

void EventManager::exported_add_event(Enums::EventType cbType, void* fct, const char* name)
{
	add_event(cbType, fct, name);
}

bool EventManager::exported_remove_event(Enums::EventType cbType, void* fct)
{
	return remove_event(cbType, fct);
}

bool EventManager::fire_on_before_attack(GameObject* target)
{
	bool process = true;

	trigger(Enums::OnBeforeAttackOrbwalker, target, &process);

	return process;
}

void EventManager::fire_on_after_attack(GameObject* target)
{
	trigger(Enums::OnAfterAttackOrbwalker, target);
}

bool EventManager::fire_on_before_move(Vec3* pos)
{
	bool process = true;

	trigger(Enums::OnBeforeAttackOrbwalker, &pos, &process);

	return process;
}

void EventManager::fire_on_after_move(const Vec3& pos)
{
	trigger(Enums::OnAfterMoveOrbwalker, pos);
}

void EventManager::clear_events()
{
	for (int i = 0; i < Enums::EventType::size; i++)
	{
		m_Callbacks[i].clear();
		m_CallbacksLua[i].clear();
	}
}
