#pragma once

#include "../../Impl/Managers/AntiGapcloserManager/AntiGapcloserManager.h"
#include "../Framework/GameObjects/MissileClient/MissileClient.h"
#include "../Framework/GameObjects/GameObject/GameObject.h"
#include "../Framework/Buffs/BuffEntry/BuffEntry.h"
#include "../Framework/Navigation/PathControllerCommon/PathControllerCommon.h"
#include "../Framework/Navigation/NavMesh/NavMesh.h"
#include "../Framework/Spells/SpellData/SpellData.h"
#include "../Framework/Spells/SpellCastInfo/SpellCastInfo.h"
#include "../Framework/Spells/Spellslot/SpellSlot.h"
#include "../Framework/Items/ItemSlot/ItemSlot.h"
#include "../Framework/GameEngine/GameTime/GameTime.h"
#include "../Framework/GameEngine/NetClient/NetClient.h"
#include "../Framework/Hud/Hud/Hud.h"
#include "../Framework/Hud/Cursor/Cursor.h"
#include "../Framework/Hud/Chat/Chat.h"
#include "../Framework/Hud/Minimap/Minimap.h"
#include "../Framework/Rendering/r3dRenderer/r3dRenderer.h"
#include "../Framework/GameEngine/ObjectManager/ObjectManager.h"
#include "../Impl/EntityList/EntityList.h"
#include "../Impl/Managers/EventManager/EventManager.h"
#include "../Impl/Managers/DrawManager/DrawManager.h"
#include "../Impl/Managers/DmgLibManager/DamageLibManager.h"
#include "../Impl/Managers/EvadeManager/EvadeManager.h"
#include "../Impl/Managers/OrbwalkerManager/OrbwalkerManager.h"
#include "../Impl/Managers/TargetSelectorManager/TargetSelectorManager.h"
#include "../Impl/Managers/MenuManager/MenuManager.h"
#include "../Impl/Managers/GlowManager/GlowManager.h"
#include "../Impl/Managers/HealthPredManager/HealthPredictionManager.h"
#include "../Impl/Managers/PermashowManager/PermashowManager.h"
#include "../Impl/Managers/PredictionManager/PredictionManager.h"
#include "../Impl/Input/Input.h"
#include "../Impl/Scheduler/Scheduler.h"
namespace SDK
{
#define GET_EXPORTED_CLASS(NAME) virtual NAME * get_exported##NAME ();
#define DEFINE_EXPORTED_CLASS(CLASS) static inline CLASS * exported##CLASS { new CLASS () };

	class PluginSDK final
	{
	public:
		~PluginSDK();

		GET_EXPORTED_CLASS(MissileClient);
		GET_EXPORTED_CLASS(GameObject);
		GET_EXPORTED_CLASS(BuffEntry);
		GET_EXPORTED_CLASS(PathControllerCommon);
		GET_EXPORTED_CLASS(SpellCastInfo);
		GET_EXPORTED_CLASS(ItemSlot);
		GET_EXPORTED_CLASS(SpellSlot);
		GET_EXPORTED_CLASS(SpellData);
		GET_EXPORTED_CLASS(Hud);
		GET_EXPORTED_CLASS(Cursor);
		GET_EXPORTED_CLASS(NetClient);
		GET_EXPORTED_CLASS(NavMesh);
		GET_EXPORTED_CLASS(ObjectManager);
		virtual GameObject* get_local_player();
		virtual Console* get_console();
		virtual EventManager* get_cb_manager();
		virtual DrawManager* get_draw_manager();
		virtual GameClock* get_game_clock();
		virtual NetClient* get_net_client();
		virtual Hud* get_hud();
		virtual Minimap* get_minimap();
		virtual Cursor* get_cursor();
		virtual Input* get_input();
		virtual r3dRenderer* get_renderer();
		virtual ExportedMenuManager* get_menu_manager();
		virtual Chat* get_chat();
		virtual EntityList* get_entity_list();
		virtual NavMesh* get_nav_mesh();
		virtual ObjectManager* get_object_manager();
		virtual DamageLibManager* get_damage_lib_manager();
		virtual OrbwalkerManager* get_orbwalker_manager();
		virtual EvadeManager* get_evade_manager();
		virtual TargetSelectorManager* get_target_selector_manager();
		virtual HealthPredictionManager* get_health_prediction_manager();
		virtual PredictionManager* get_prediction_manager();
		virtual AntiGapcloserManager* get_anti_gapcloser_manager();
		virtual Scheduler* get_scheduler();
		virtual GlowManager* get_glow_manager();
		virtual PermashowManager* get_permashow_manager();
	};
 
	static inline PluginSDK* exported_plugin_sdk = { new PluginSDK() };
	DEFINE_EXPORTED_CLASS(MissileClient);
	DEFINE_EXPORTED_CLASS(GameObject);
	DEFINE_EXPORTED_CLASS(BuffEntry);
	DEFINE_EXPORTED_CLASS(PathControllerCommon);
	DEFINE_EXPORTED_CLASS(SpellDataResource);
	DEFINE_EXPORTED_CLASS(SpellCastInfo);
	DEFINE_EXPORTED_CLASS(ItemSlot);
	DEFINE_EXPORTED_CLASS(SpellSlot);
	DEFINE_EXPORTED_CLASS(SpellData);
	DEFINE_EXPORTED_CLASS(Hud);
	DEFINE_EXPORTED_CLASS(Cursor);
	DEFINE_EXPORTED_CLASS(NetClient);
	DEFINE_EXPORTED_CLASS(NavMesh);
	DEFINE_EXPORTED_CLASS(ObjectManager);
}
