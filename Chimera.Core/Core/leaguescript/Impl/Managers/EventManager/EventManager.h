#pragma once
#include "../Framework/Enums/EventType.h"
#include "../Impl/Common/Common.h"
#include "../Impl/Singleton/Singleton.h"
#include "../Impl/DirectX/DirectX.h"
#include "../Framework/GameObjects/GameObject/GameObject.h"
#include "../Impl/Vector/Vector.h"
#include "../SDK/LUA/LuaIncludes.h"
#include "../Impl/Logger/Logger.h"

struct callback
{
	void* func;
	const char* name;
};

class EventManager
{
public:
    std::vector<callback> m_Callbacks[(unsigned int)Enums::EventType::size];
    std::vector<luabridge::LuaRef> m_CallbacksLua[(unsigned int)Enums::EventType::size];

	void add_event(Enums::EventType cbType, void* fct, const char* name);
	void add_event(Enums::EventType cbType, luabridge::LuaRef fct);
	bool remove_event(Enums::EventType cbType, void* fct);
	bool remove_event(Enums::EventType cbType, luabridge::LuaRef fct);
	void clear_events();

	virtual void exported_add_event(Enums::EventType cbType, void* fct, const char* name);
	virtual bool exported_remove_event(Enums::EventType cbType, void* fct);

	virtual bool fire_on_before_attack(GameObject* target);
	virtual void fire_on_after_attack(GameObject* target);

	virtual bool fire_on_before_move(Vec3* pos);
	virtual void fire_on_after_move(const Vec3& pos);

	DWORD generate_exception(Enums::EventType type, const char* name, bool lua, uint32_t code, LPEXCEPTION_POINTERS ex)
	{
		char buff[256];
		sprintf(buff,
			"%s: Exception triggered.\nAddr: 0x%llx\nCode: 0x%llX\nRIP: 0x%llX\nRAX: 0x%llX\nRBX: 0x%llX\nRCX: 0x%llX\nRDX: 0x%llX",
			(std::string(lua ? "[LUA] [" : "[DLL] [") + name + "::" + Enums::event_type_str[(int)type] + "]").c_str(),
			(uintptr_t) ex->ExceptionRecord->ExceptionAddress,
			(uintptr_t) code,
			(uintptr_t) ex->ContextRecord->Rip,
			(uintptr_t) ex->ContextRecord->Rax,
			(uintptr_t) ex->ContextRecord->Rbx,
			(uintptr_t) ex->ContextRecord->Rcx,
			(uintptr_t) ex->ContextRecord->Rdx
		);

		Log::error(buff);

		return EXCEPTION_EXECUTE_HANDLER;
	}

	void trigger_seh(Enums::EventType type, bool lua, const std::function<void()>& fn, const char* name)
	{
		__try
		{
			fn();
		}
		__except (generate_exception(type, name, lua, GetExceptionCode(), GetExceptionInformation())) { }
	}

	template <typename... Args>
	void trigger(Enums::EventType cbType, Args... args)
	{
		for (const auto& cb : m_Callbacks[(unsigned)cbType])
		{
			trigger_seh(cbType, false, [cb, args...]()
			{
				static_cast<void(*)(Args...)>(cb.func)(args...);
			}, cb.name);
		}
	}

	template <typename... Args>
	void trigger_lua(Enums::EventType cbType, Args... args)
	{
		for (const auto& cb : m_CallbacksLua[(unsigned)cbType])
		{
			trigger_seh(cbType, true, [cb, args...]()
			{
				cb(args...);
			}, "");
		}
	}

	template <typename... Args>
	void trigger_lua_bool(Enums::EventType cbType, bool* process, Args... args)
	{
		for (const auto& cb : m_CallbacksLua[(unsigned)cbType])
		{
			trigger_seh(cbType, true, [cb, process, args...]()
			{
				const luabridge::LuaResult ret = cb(args...);
				if (ret.size() > 0)
					*process = (bool)ret[0];
			}, "");
		}
	}
};

extern EventManager* g_event_manager;
