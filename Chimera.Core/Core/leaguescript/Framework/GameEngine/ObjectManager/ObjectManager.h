#pragma once

#include "../Impl/Common/Common.h"

#include "../Framework/GameObjects/GameObject/GameObject.h"

#ifndef EXPORT_FUNC
#define EXPORT_FUNC(RET, NAME, ARGS_IN, ARGS_OUT ) \
virtual RET __EXPORT##NAME ARGS_IN { return obj->NAME ARGS_OUT; };
#endif

class ObjectManager final
{
private:
public:
	static ObjectManager* get_instance();
	static GameObject* get_object_by_network_id(unsigned network_id);
	static GameObject* find_object(unsigned id);

	GameObject* get_first_object();
	GameObject* get_next_object(GameObject* object);

	EXPORT_FUNC(GameObject*, get_object_by_network_id, (ObjectManager* obj, unsigned network_id), (network_id));
	EXPORT_FUNC(GameObject*, find_object, (ObjectManager* obj, unsigned id), (id));
};

#undef EXPORT_FUNC