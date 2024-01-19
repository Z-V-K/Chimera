#include "../pch.h"
#include "PluginSDK.h"

namespace SDK {

	PluginSDK::~PluginSDK()
	{
		delete g_event_manager;
		delete g_draw_manager;
		delete g_game_clock;
		delete g_input;
		delete g_renderer;
		delete g_exported_menu_manager;
		delete g_entityList;
		delete g_scheduler;
		delete g_glow_manager;
		delete g_permashow_manager;
	}

#define IMPL_EXPORTED_CLASS(CLASS) CLASS * PluginSDK::get_exported##CLASS () { return exported##CLASS; };

	IMPL_EXPORTED_CLASS(MissileClient);
	IMPL_EXPORTED_CLASS(GameObject);
	IMPL_EXPORTED_CLASS(BuffEntry);
	IMPL_EXPORTED_CLASS(PathControllerCommon);
	IMPL_EXPORTED_CLASS(SpellCastInfo);
	IMPL_EXPORTED_CLASS(ItemSlot);
	IMPL_EXPORTED_CLASS(SpellSlot);
	IMPL_EXPORTED_CLASS(SpellData);
	IMPL_EXPORTED_CLASS(Hud);
	IMPL_EXPORTED_CLASS(Cursor);
	IMPL_EXPORTED_CLASS(NetClient);
	IMPL_EXPORTED_CLASS(NavMesh);
	IMPL_EXPORTED_CLASS(ObjectManager);

	GameObject* PluginSDK::get_local_player()
	{
		return GameObject::get_local_player();
	}

	Console* PluginSDK::get_console()
	{
		return g_ctx->mConsole.get();
	}

	EventManager* PluginSDK::get_cb_manager()
	{
		return g_event_manager;
	}

	DrawManager* PluginSDK::get_draw_manager()
	{
		return g_draw_manager;
	}

	GameClock* PluginSDK::get_game_clock()
	{
		return g_game_clock;
	}

	NetClient* PluginSDK::get_net_client()
	{
		return NetClient::get_instance();
	}

	Hud* PluginSDK::get_hud()
	{
		return Hud::get_instance();
	}

	Minimap* PluginSDK::get_minimap()
	{
		return g_minimap;
	}

	Cursor* PluginSDK::get_cursor()
	{
		return get_hud()->get_cursor();
	}

	Input* PluginSDK::get_input()
	{
		return g_input;
	}

	r3dRenderer* PluginSDK::get_renderer()
	{
		return g_renderer;
	}

	ExportedMenuManager* PluginSDK::get_menu_manager()
	{
		return g_exported_menu_manager;
	}

	Chat* PluginSDK::get_chat()
	{
		return Chat::instance();
	}

	EntityList* PluginSDK::get_entity_list()
	{
		return g_entityList;
	}

	NavMesh* PluginSDK::get_nav_mesh()
	{
		return NavMesh::instance();
	}

	ObjectManager* PluginSDK::get_object_manager()
	{
		return ObjectManager::get_instance();
	}

	DamageLibManager* PluginSDK::get_damage_lib_manager()
	{
		return g_damage_lib;
	}

	OrbwalkerManager* PluginSDK::get_orbwalker_manager()
	{
		return g_orbwalker_manager;
	}

	EvadeManager* PluginSDK::get_evade_manager()
	{
		return g_evade_manager;
	}

	TargetSelectorManager* PluginSDK::get_target_selector_manager()
	{
		return g_target_selector_manager;
	}

	HealthPredictionManager* PluginSDK::get_health_prediction_manager()
	{
		return g_health_pred_manager;
	}

	PredictionManager* PluginSDK::get_prediction_manager()
	{
		return g_prediction_manager;
	}

	AntiGapcloserManager* PluginSDK::get_anti_gapcloser_manager()
	{
		return g_anti_gapcloser;
	}

	Scheduler* PluginSDK::get_scheduler()
	{
		return g_scheduler;
	}

	GlowManager* PluginSDK::get_glow_manager()
	{
		return g_glow_manager;
	}

	PermashowManager* PluginSDK::get_permashow_manager()
	{
		return g_permashow_manager;
	}
}
