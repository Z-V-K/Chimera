#include "EventSystem.h"

#include "../Impl/Common/Common.h"
#include "../Impl/Managers/EventManager/EventManager.h"
#include "../Impl/Hooks/Hook.h"
#include "../Impl/Hooks/retspoof/x64RetSpoof.h"
#include "../Framework/GameObjects/GameObject/GameObject.h"
#include "../Framework/GameEngine/ObjectManager/ObjectManager.h"
#include "../Framework/Enums/EventType.h"

Hook< convention_type::fastcall_t, int64_t, uintptr_t*, int, int* > HookOnNotify;

namespace Wrapper {
	int64_t OnNotify(uintptr_t* a1, int event_id, int* p_network_id) {
		GameObject* obj = ObjectManager::get_object_by_network_id(*p_network_id);

		g_event_manager->trigger(Enums::OnNotifyEvent, obj, EventSystem::convert_event_to_name(event_id), event_id);

		return x64RetSpoof::spoof_call(HookOnNotify.m_original, a1, event_id, p_network_id);
	}
}

char* EventSystem::convert_event_to_name(int event_id)
{
	typedef char* (__fastcall* fnConvertEventToName)(int);
	fnConvertEventToName fn = (fnConvertEventToName) MAKE_RVA(Addresses::EventSystem::ConvertEventToName);

	return x64RetSpoof::spoof_call(fn, event_id);
}

bool EventSystem::apply_hooks() {
	HookOnNotify.apply_jmp(MAKE_RVA(Addresses::EventSystem::Notify), (uintptr_t)Wrapper::OnNotify, 14);

	return true;
}