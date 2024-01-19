#include "../pch.h"
#include "../Framework/GameEngine/ObjectManager/ObjectManager.h"

#include "../Impl/Hooks/retspoof/x64RetSpoof.h"
#include "../Impl/Bypass/Bypass.h"

ObjectManager* ObjectManager::get_instance()
{
	return RVA_CAST(ObjectManager*, Addresses::ObjectManager::ObjectManagerInstance);
}

GameObject* ObjectManager::get_first_object()
{
	Bypass::mainloop_check();

	typedef GameObject* (__fastcall* fnGetFirst)(ObjectManager*);
	static fnGetFirst fn = (fnGetFirst)MAKE_RVA(Addresses::ObjectManager::GetFirstObject);

	GameObject* ret = x64RetSpoof::spoof_call(fn, this);

	return ret;
}

GameObject*  ObjectManager::get_next_object(GameObject* object)
{
	typedef GameObject*(__fastcall* fnGetNext)(ObjectManager*, GameObject*);
	static fnGetNext fn = (fnGetNext)MAKE_RVA(Addresses::ObjectManager::GetNextObject);

	return x64RetSpoof::spoof_call(fn, this, object);
}

GameObject* ObjectManager::find_object(unsigned id)
{
	typedef GameObject* (__fastcall* fnFindObject)(ObjectManager*, int);
	static fnFindObject fn = (fnFindObject)MAKE_RVA(Addresses::ObjectManager::FindObject);
	
	return x64RetSpoof::spoof_call(fn, get_instance(), (int) id);
}

GameObject* ObjectManager::get_object_by_network_id(unsigned network_id)
{
	typedef GameObject* (__fastcall* fnGetNetworkObject)(ObjectManager*, unsigned int);
	static fnGetNetworkObject fn = (fnGetNetworkObject)MAKE_RVA(Addresses::ObjectManager::GetNetworkObject);

	return x64RetSpoof::spoof_call(fn, get_instance(), network_id);
}