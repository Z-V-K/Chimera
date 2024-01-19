#include "../pch.h"
#include "../Framework/GameObjects/GameObject/GameObject.h"

#include "../../Navigation/SetPathDashData/SetPathDashData.h"
#include "../EffectEmitter/EffectCreateDataClient.h"
#include "../EffectEmitter/EffectEmitterAttachment.h"
#include "../Impl/Base/base.h"
#include "../Impl/Hooks/Hook.h"
#include "../Impl/Common/Utils.h"
#include "../Impl/Managers/EventManager/EventManager.h"
#include "../Impl/Hooks/retspoof/x64RetSpoof.h"
#include "../Impl/Encryption/Encryption.h"
#include "../Framework/Rendering/r3dTexture/r3dTexture.h"
#include "../Framework/GameEngine/GameTime/GameTime.h"
#include "../Impl/Logger/Logger.h"
#include "../Framework/Containers/RiotVector.h"
#include "../Impl/Bypass/Bypass.h"


Hook< convention_type::fastcall_t, int64_t, GameObject*, int > HookOnCreateObject;
Hook< convention_type::fastcall_t, int64_t, void*, GameObject* > HookOnDeleteObject;
Hook< convention_type::fastcall_t, int64_t, Spellbook*, SpellCastInfo* > HookOnProcessSpell;
Hook< convention_type::fastcall_t, int64_t, GameObject*, uint8_t, Vec3*, GameObject*, bool, bool, bool > HookOnIssueOrder;
Hook< convention_type::fastcall_t, int64_t, GameObject*, int64_t, const char*, int, char, float, char > HookOnPlayAnimation;
Hook< convention_type::fastcall_t, int8_t, BuffManager*, uint8_t, uint32_t, float > HookOnBuffRemove;
Hook< convention_type::fastcall_t, void, uintptr_t, BuffEntry**, uint32_t, uint32_t, uint16_t, float, int8_t, uint32_t, int8_t > HookOnBuffAdd;
Hook< convention_type::fastcall_t, int64_t, GameObject*, RiotVector<Vec3>, int, uintptr_t, int, char*, char, int, int, int > HookOnSetPath;
Hook< convention_type::fastcall_t, bool, GameObject*, SpellData**, uintptr_t, float, uintptr_t > HookOnProcessAutoAttack;
Hook< convention_type::fastcall_t, int64_t, uintptr_t, EffectCreateDataClient* > HookOnCreateClientEffect;

Hook< convention_type::fastcall_t, uintptr_t, uintptr_t, uintptr_t, uint32_t* > HookOnGetHealthBarScreenPosDetection;
Hook< convention_type::fastcall_t, int64_t, int64_t, int > HookOnDebug2;

struct EffectEmitterInfo
{
	GameObject* emitter;
	uint32_t effect_hash;
};

std::unordered_map<const GameObject*, EffectEmitterInfo> effect_emitter_owners { };

class Wrapper
{
public:
	static int64_t __fastcall OnCreateObjectCallee(GameObject* thisPtr, int networkId)
	{
		auto res = x64RetSpoof::spoof_call(HookOnCreateObject.m_original, thisPtr, networkId);

		g_event_manager->trigger(Enums::OnCreateObject, thisPtr);
		g_event_manager->trigger_lua(Enums::OnCreateObject, thisPtr);

		return res;
	}

	static int64_t __fastcall OnDeleteObjectCallee(void* thisPtr, GameObject* sender)
	{
		g_event_manager->trigger(Enums::OnDeleteObject, sender);
		g_event_manager->trigger_lua(Enums::OnDeleteObject, sender);

		if (sender->is_effect_emitter() && effect_emitter_owners.contains(sender))
			effect_emitter_owners.erase(sender);

		return x64RetSpoof::spoof_call(HookOnDeleteObject.m_original, thisPtr, sender);
	}

	static int64_t __fastcall OnProcessSpellCallee(Spellbook* thisPtr, SpellCastInfo* castInfo)
	{			
		g_event_manager->trigger(Enums::OnProcessSpell, castInfo);
		g_event_manager->trigger_lua(Enums::OnProcessSpell, castInfo);

		return x64RetSpoof::spoof_call(HookOnProcessSpell.m_original, thisPtr, castInfo);
	}

	static int64_t __fastcall OnIssueOrderCallee(GameObject* thisPtr, uint8_t order, Vec3* position, GameObject* target, bool isAttackMove, bool isMinion, bool unk)
	{
		bool process = true;
		int64_t ret = 0;

		g_event_manager->trigger(Enums::OnIssueOrder, order, position, target, &process);
		g_event_manager->trigger_lua_bool(Enums::OnIssueOrder, &process, order, position, target);

		if(process)
			ret = x64RetSpoof::spoof_call(HookOnIssueOrder.m_original, thisPtr, order, position, target, isAttackMove, isMinion, unk);

		return ret;
	}

	static int64_t __fastcall OnPlayAnimationCallee(GameObject* thisPtr, int64_t riotHashFunction, const char* animationName, int a4, char a5, float a6, char a7)
	{
		bool process = true;

		uint32_t animationHash = FNV1A32Lower(animationName);

		g_event_manager->trigger(Enums::OnPlayAnimation, thisPtr, animationName, animationHash, &process);
		g_event_manager->trigger_lua_bool(Enums::OnPlayAnimation, &process, thisPtr, animationName, animationHash);

		if (process)
			return x64RetSpoof::spoof_call(HookOnPlayAnimation.m_original,  thisPtr, riotHashFunction, animationName, a4, a5, a6, a7);

		return 0;
	}

	static void OnBuffAddCallee(uintptr_t a1, BuffEntry** a2, uint32_t a3, uint32_t a4, uint16_t a5, float a6, int8_t a7, uint32_t a8, int8_t a9)
	{
		x64RetSpoof::spoof_call(HookOnBuffAdd.m_original, a1, a2, a3, a4, a5, a6, a7, a8, a9);

		if (a2 && *a2 && (*a2)->is_valid())
		{
			g_event_manager->trigger(Enums::OnBuffGainLose, *a2, true);
			g_event_manager->trigger_lua(Enums::OnBuffGainLose, *a2, true);
		}
	}

	static int8_t OnBuffRemoveCallee(BuffManager* a1, uint8_t a2, uint32_t a3, float a4)
	{
		const uintptr_t buff_array_start = a1->get_buff_entries_array();
		const uintptr_t buff_array_end = a1->get_buff_entries_array_end();
		
		if (!buff_array_start || !buff_array_end)
			return x64RetSpoof::spoof_call(HookOnBuffRemove.m_original, a1, a2, a3, a4);
		
		if (!((buff_array_end - buff_array_start) >> 4))
			return x64RetSpoof::spoof_call(HookOnBuffRemove.m_original, a1, a2, a3, a4);
		
		BuffEntry* buff = *reinterpret_cast<BuffEntry**>(buff_array_start + 0x10 * a2);
		
		if (buff->is_valid())
		{
			g_event_manager->trigger(Enums::OnBuffGainLose, buff, false);
			g_event_manager->trigger_lua(Enums::OnBuffGainLose, buff, false);
		}

		return x64RetSpoof::spoof_call(HookOnBuffRemove.m_original, a1, a2, a3, a4);
	}

	static int64_t __fastcall OnSetPathCallee(GameObject* obj, RiotVector<Vec3> pWaypoints, int nb_waypoints, SetPathDashData* dash_data, int is_not_dash, char* a6, char a7, int a8, int a9, int a10)
	{
		std::vector<Vec3> waypoints{ };
		for (int i = 0; i < pWaypoints.size; i++)
			waypoints.push_back(pWaypoints.elements[i]);
		
		g_event_manager->trigger(Enums::OnSetPath, obj, waypoints, !is_not_dash, dash_data->dash_speed);
		g_event_manager->trigger_lua(Enums::OnSetPath, obj, waypoints, !is_not_dash, dash_data->dash_speed);

		return x64RetSpoof::spoof_call(HookOnSetPath.m_original, obj, pWaypoints, nb_waypoints, (uintptr_t) dash_data, is_not_dash, a6, a7, a8, a9, a10);
	}

	static bool __fastcall OnProcessAutoAttackCallee(GameObject* obj, SpellData** auto_attack, uintptr_t a3, float a4, uintptr_t a5)
	{
		g_event_manager->trigger(Enums::OnProcessAutoAttack, obj, *auto_attack);
		g_event_manager->trigger_lua(Enums::OnProcessAutoAttack, obj, *auto_attack);
		return x64RetSpoof::spoof_call(HookOnProcessAutoAttack.m_original, obj, auto_attack, a3, a4, a5);
	}

	static int64_t __fastcall OnCreateClientEffectCallee(uintptr_t a1, EffectCreateDataClient* client_data)
	{
		int64_t ret = x64RetSpoof::spoof_call(HookOnCreateClientEffect.m_original, a1, client_data);
		
		GameObject*** pEffect_emitter = (GameObject***) a1;

		if (!pEffect_emitter || !(*pEffect_emitter))
			return ret;

		GameObject* src = client_data->get_effect_emitter();
		uint32_t effect_hash = client_data->get_effect_hash();

		if ((**pEffect_emitter) != nullptr && src != nullptr)
			effect_emitter_owners.insert({ **pEffect_emitter, { src, effect_hash } });

		return ret;
	}

	static uintptr_t __fastcall OnGetHealthBarScreenPosDetectionCallee(uintptr_t a1, uintptr_t a2, uint32_t* a3) 
	{
		if (*a3 != 0xC && *a3 != 0xA)
		{
			return a2;
		}

		return x64RetSpoof::spoof_call(HookOnGetHealthBarScreenPosDetection.m_original, a1, a2, a3);
	}

	static int64_t __fastcall Debug2(int64_t a1, int a2)
	{
		g_ctx->mConsole->log(skCrypt("Assigned audio id: 0x%X to %s"), a2, ((GameObject*)a1)->get_name().c_str());
		return HookOnDebug2.call_original(a1, a2);
	}
};

bool GameObject::operator==(const GameObject* other) const
{
	return this->get_network_id() == other->get_network_id();
}

bool GameObject::operator!=(const GameObject* other) const
{
	return this != other;
}

float GameObject::get_base_health_for_level() const
{
	typedef float (__fastcall* fnGetBaseHealthForLevel)(const GameObject*, unsigned int);
	fnGetBaseHealthForLevel fn = (fnGetBaseHealthForLevel)MAKE_RVA(Addresses::GameObjectAddresses::GetBaseHealthForLevel);

	return fn(this, get_level());
}

PVOID GameObject::get_square_icon() const
{
	typedef r3dTexture* (__fastcall* fnGetSquareIconPortrait)(const GameObject*);
	fnGetSquareIconPortrait fn = (fnGetSquareIconPortrait) MAKE_RVA(Addresses::GameObjectAddresses::GetSquareIconPortrait);

	r3dTexture* ptr = *reinterpret_cast<r3dTexture**>(x64RetSpoof::spoof_call(fn, this));

	if (!ptr)
		return nullptr;

	return ptr->get_dx_texture();
}

PVOID GameObject::get_circle_icon() const
{
	typedef r3dTexture* (__fastcall* fnGetCircleIconPortrait)(const GameObject*);
	fnGetCircleIconPortrait fn = (fnGetCircleIconPortrait)MAKE_RVA(Addresses::GameObjectAddresses::GetCircleIconPortrait);

	r3dTexture* ptr = *reinterpret_cast<r3dTexture**>(x64RetSpoof::spoof_call(fn, this));

	if (!ptr)
		return nullptr;

	return ptr->get_dx_texture();
}

LuaTexture GameObject::get_circle_icon_lua() const
{
	return LuaTexture(get_circle_icon());
}

LuaTexture GameObject::get_square_icon_lua() const
{
	return LuaTexture(get_square_icon());
}

uintptr_t* GameObject::VTable()
{
	return *reinterpret_cast<uintptr_t**>(this);
}

unsigned GameObject::get_index() const
{
	return RVA_CAST_THIS(unsigned, Structures::GameObject::Index);
}

unsigned GameObject::get_network_id() const
{
	return RVA_CAST_THIS(unsigned, Structures::GameObject::NetworkId);
}

float GameObject::get_current_gold() const
{
	return RVA_CAST_THIS(float, Structures::GameObject::CurrentGold);
}

unsigned GameObject::get_visibility() const
{
	return RVA_CAST_THIS(unsigned, Structures::GameObject::Visibility);
}

unsigned GameObject::get_level_up_points() const
{
	return RVA_CAST_THIS(unsigned, Structures::GameObject::LevelUpPoints);
}

unsigned GameObject::get_level() const
{
	return RVA_CAST_THIS(unsigned, Structures::GameObject::Level);
}

std::string GameObject::get_name() const
{
	return RVA_CAST_THIS(std::string, Structures::GameObject::Name);
}

std::string GameObject::get_model_name() const
{
	return RVA_CAST_THIS(std::string, Structures::GameObject::ModelName);
}

CharacterData* GameObject::get_character_data() const
{
	return RVA_CAST_THIS(CharacterData*, Structures::GameObject::CharacterData);
}

uint32_t GameObject::get_character_hash() const
{
	const CharacterData* charData = get_character_data();

	return charData ? charData->get_character_hash() : 0;
}

const Vec3& GameObject::get_position() const
{
	return RVA_CAST_THIS(Vec3, Structures::GameObject::Position);
}

const Vec3& GameObject::get_direction() const
{
	return RVA_CAST_THIS(Vec3, Structures::GameObject::Direction);
}

MissileClient* GameObject::get_missile_client() const
{
	return RVA_CAST_THIS_REF(MissileClient*, Structures::GameObject::MissileClient);
}

EffectEmitter* GameObject::get_effect_emitter() const
{
	return RVA_CAST_THIS_REF(EffectEmitter*, Structures::GameObject::EffectEmitter);	
}

BuffManager* GameObject::get_buff_manager() const
{
	return RVA_CAST_THIS_REF(BuffManager*, Structures::GameObject::BuffManager);
}

Spellbook* GameObject::get_spell_book() const
{
	return RVA_CAST_THIS(Spellbook*, Structures::GameObject::SpellBook);
}

Spellbook* GameObject::get_spell_book_ref() const
{
	return RVA_CAST_THIS_REF(Spellbook*, Structures::GameObject::SpellBook);
}

std::vector<ItemSlot*> GameObject::get_items() const
{
	std::vector<ItemSlot*> ret{ };

	if (!is_champion())
		return ret;

	for (int i = 0; i < 7; i++)
	{
		ItemSlot* itemSlot = *reinterpret_cast<ItemSlot**>(reinterpret_cast<uintptr_t>(this) + static_cast<unsigned int>(Structures::GameObject::ItemList) + 0x8 * i);

		if (!itemSlot)
			continue;

		ret.push_back(itemSlot);
	}

	return ret;
}

Enums::GameObjectTeam GameObject::get_team() const
{
	return RVA_CAST_THIS(Enums::GameObjectTeam, Structures::GameObject::Team);
}

Enums::CombatType GameObject::get_combat_type() const
{
	return RVA_CAST_THIS(Enums::CombatType, Structures::GameObject::CombatType);
}

Enums::RecallState GameObject::get_recall_state() const
{
	return RVA_CAST_THIS(Enums::RecallState, Structures::GameObject::RecallState);
}

float GameObject::get_health() const
{
	return RVA_CAST_THIS(float, Structures::GameObject::Health);
}

float GameObject::get_max_health() const
{
	return RVA_CAST_THIS(float, Structures::GameObject::MaxHealth);
}

float GameObject::get_bonus_health() const
{
	return get_max_health() - get_base_health_for_level();
}

float GameObject::get_bonus_mana() const
{
	const CharacterData* charData = get_character_data();

	if (!charData)
		return 0.f;

	const BaseCharacterData* baseCharData = charData->get_base_character_data();

	return baseCharData ? get_max_mana() - baseCharData->get_base_mana() : 0.f;
}

float GameObject::get_shield() const
{
	return RVA_CAST_THIS(float, Structures::GameObject::Shield);
}

float GameObject::get_magic_shield() const
{
	return RVA_CAST_THIS(float, Structures::GameObject::MagicShield);
}

float GameObject::get_physical_shield() const
{
	return RVA_CAST_THIS(float, Structures::GameObject::PhysicalShield);
}

float GameObject::get_mana() const
{
	return RVA_CAST_THIS(float, Structures::GameObject::Mana);
}

float GameObject::get_max_mana() const
{
	return RVA_CAST_THIS(float, Structures::GameObject::MaxMana);
}

float GameObject::get_ability_haste() const
{
	return RVA_CAST_THIS(float, Structures::GameObject::AbilityHaste);
}

float GameObject::get_lethality() const
{
	return RVA_CAST_THIS(float, Structures::GameObject::Lethality);
}

float GameObject::get_armor() const
{
	return RVA_CAST_THIS(float, Structures::GameObject::Armor);
}

float GameObject::get_bonus_armor() const
{
	return RVA_CAST_THIS(float, Structures::GameObject::BonusArmor);
}

float GameObject::get_magic_res() const
{
	return RVA_CAST_THIS(float, Structures::GameObject::MagicRes);
}

float GameObject::get_bonus_magic_res() const
{
	return RVA_CAST_THIS(float, Structures::GameObject::BonusMagicRes);
}

float GameObject::get_base_ad() const
{
	return RVA_CAST_THIS(float, Structures::GameObject::BaseAD);
}

float GameObject::get_bonus_ad() const
{
	return RVA_CAST_THIS(float, Structures::GameObject::BonusAD);
}

float GameObject::get_movement_speed() const
{
	return RVA_CAST_THIS(float, Structures::GameObject::MovementSpeed);
}

float GameObject::get_crit_damage_multiplier() const
{
	return RVA_CAST_THIS(float, Structures::GameObject::CritDamageMultiplier);
}

float GameObject::get_crit() const
{
	return RVA_CAST_THIS(float, Structures::GameObject::Crit);
}

float GameObject::get_ap() const
{
	return RVA_CAST_THIS(float, Structures::GameObject::TotalAP);
}

float GameObject::get_bonus_ap_multiplier() const
{
	return RVA_CAST_THIS(float, Structures::GameObject::BonusAPMultiplier);
}

float GameObject::get_attack_speed_multiplier() const
{
	return RVA_CAST_THIS(float, Structures::GameObject::AttackSpeedMultiplier);
}

float GameObject::get_attack_range() const
{
	return RVA_CAST_THIS(float, Structures::GameObject::AttackRange);
}

bool GameObject::is_targetable() const
{
	return RVA_CAST_THIS(bool, Structures::GameObject::IsTargetable);
}

float GameObject::get_accumulated_experience() const
{
	return RVA_CAST_THIS(float, Structures::GameObject::AccumulatedExperience);
}

float GameObject::get_magic_pen_flat() const
{
	return RVA_CAST_THIS(float, Structures::GameObject::MagicPenFlat);
}

float GameObject::get_armor_pen_multiplier() const
{
	return RVA_CAST_THIS(float, Structures::GameObject::ArmorPenMultiplier);
}

float GameObject::get_magic_pen_multiplier() const
{
	return RVA_CAST_THIS(float, Structures::GameObject::MagicPenMultiplier);
}

float GameObject::get_mana_regen() const
{
	return RVA_CAST_THIS(float, Structures::GameObject::ManaRegen);
}

float GameObject::get_health_regen() const
{
	return RVA_CAST_THIS(float, Structures::GameObject::HealthRegen);
}

bool GameObject::is_in_range_obj(const GameObject* to, float range) const
{
	return this->is_in_range(to->get_position(), range);
}

bool GameObject::is_in_range(const Vec3& position, float range) const
{
	return this->get_position().to_2d().distance(position.to_2d()) <= range;
}

bool GameObject::is_in_auto_attack_range(const GameObject* to, float extra_range) const
{
	float range{ this->get_attack_range() + to->get_bounding_radius() + extra_range};

	return this->is_in_range_obj(to, range);
}

bool GameObject::is_valid_target(float range, const Vec3& from, bool ignore_invulnerability) const
{
	if (get_max_health() <= 0 || get_health() <= 0)
		return false;

	if (!ignore_invulnerability && this->is_invulnerable() && !this->is_targetable())
		return false;

	if (!from.is_valid())
		return GameObject::get_local_player()->is_in_range_obj(this, range) && this->is_visible();
	
	return this->is_in_range(from, range) && this->is_visible() && this->is_alive();
}

std::list<std::string> turret_t1 =
{
	xorstr_("SRUAP_Turret_Order1"),
	xorstr_("SRUAP_Turret_Chaos1"),
	xorstr_("TT_OrderTurret5"),
	xorstr_("TT_ChaosTurret5"),
	xorstr_("HA_AP_OrderTurret"),
	xorstr_("HA_AP_ChaosTurret")
};

std::list<std::string> turret_t2 =
{
	xorstr_("SRUAP_Turret_Order2"),
	xorstr_("SRUAP_Turret_Chaos2"),
	xorstr_("TT_OrderTurret2"),
	xorstr_("TT_ChaosTurret2"),
	xorstr_("HA_AP_OrderTurret2"),
	xorstr_("HA_AP_ChaosTurret2")
};

std::list<std::string> turret_t3 =
{
	xorstr_("SRUAP_Turret_Order3"),
	xorstr_("SRUAP_Turret_Chaos3"),
	xorstr_("TT_OrderTurret1"),
	xorstr_("TT_ChaosTurret1"),
	xorstr_("HA_AP_OrderTurret3"),
	xorstr_("HA_AP_ChaosTurret3")
};

std::list<std::string> turret_t4 =
{
	xorstr_("SRUAP_Turret_Order4"),
	xorstr_("SRUAP_Turret_Chaos4"),
	xorstr_("TT_OrderTurret3"),
	xorstr_("TT_ChaosTurret3")
};

Enums::TurretType GameObject::get_turret_type() const
{
	if (!is_turret())
		return Enums::TurretType::Unknown;

	static bool is_t1 = std::ranges::find(turret_t1, get_name()) != turret_t1.end();
	static bool is_t2 = std::ranges::find(turret_t2, get_name()) != turret_t2.end();
	static bool is_t3 = std::ranges::find(turret_t3, get_name()) != turret_t3.end();
	static bool is_t4 = std::ranges::find(turret_t4, get_name()) != turret_t4.end();

	if (is_t1)
		return Enums::TurretType::TierOne;
	if (is_t2)
		return Enums::TurretType::TierTwo;
	if (is_t3)
		return Enums::TurretType::TierThree;
	if (is_t4)
		return Enums::TurretType::TierFour;

	return Enums::TurretType::Unknown;
}

float GameObject::get_bounding_radius() const
{
	typedef float(__thiscall* vtableFunc)(const GameObject*);
	return base::call_virtual<vtableFunc>((PVOID) this, static_cast<uintptr_t>(Structures::GameObjectVTable::GetBoundingRadius))(this);
}

int GameObject::get_buff_count(const std::string& buff_name) const
{
	BuffEntry* buffEntry{ get_buff_manager()->get_buff(buff_name) };

	if (!buffEntry)
		return 0;

	return buffEntry->get_count();
}

int GameObject::get_buff_count(uint32_t buffHash) const
{
	BuffEntry* buffEntry{ get_buff_manager()->get_buff_by_hash(buffHash) };

	if (!buffEntry)
		return 0;

	return buffEntry->get_count();
}

bool GameObject::is_visible() const
{
	typedef bool(__thiscall* vtableFunc)(const GameObject*);
	return base::call_virtual<vtableFunc>((PVOID) this, static_cast<uintptr_t>(Structures::GameObjectVTable::IsVisible))(this);
}

bool GameObject::is_zombie() const
{
	typedef bool(__thiscall* vtableFunc)(const GameObject*);
	return base::call_virtual<vtableFunc>((PVOID) this, static_cast<uintptr_t>(Structures::GameObjectVTable::IsZombie))(this);
}

PathControllerCommon* GameObject::get_path_controller_common() const
{
	typedef PathControllerCommon* (__thiscall* vtableFunc)(const GameObject*);
	return base::call_virtual<vtableFunc>((PVOID) this, static_cast<uintptr_t>(Structures::GameObjectVTable::GetPathControllerCommon))(this);
}

float GameObject::get_total_respawn_time() const
{
	if (!is_champion())
		return 0.f;

	typedef float(__fastcall* fnGetTotalRespawnTime)(const GameObject*);
	static fnGetTotalRespawnTime fn = (fnGetTotalRespawnTime)MAKE_RVA(Addresses::GameObjectAddresses::GetTotalRespawnTime);

	return x64RetSpoof::spoof_call(fn, this);
}

float GameObject::get_remaining_respawn_time() const
{
	if (!is_champion())
		return 0.f;

	typedef float(__fastcall* fnGetRespawnTimeRemaining)(const GameObject*);
	static fnGetRespawnTimeRemaining fn = (fnGetRespawnTimeRemaining) MAKE_RVA(Addresses::GameObjectAddresses::GetRespawnTimeRemaining);

	return x64RetSpoof::spoof_call(fn, this);
}

float GameObject::get_gold_given_on_death() const
{
	if (!is_champion())
		return 0.f;

	typedef float(__fastcall* fnGetGoldGivenOnDeath)(const GameObject*);
	static fnGetGoldGivenOnDeath fn = (fnGetGoldGivenOnDeath)MAKE_RVA(Addresses::GameObjectAddresses::GetGoldGivenOnDeath);

	return x64RetSpoof::spoof_call(fn, this);
}

/*
 *		GAME FUNCTIONS
 */

float GameObject::get_timer_expiry() const
{
	if (!is_neutral_camp())
		return 0.f;

	// bypass detection | 13.21 OK
	*(DWORD*)(this + 0xCC) |= 0x8;
	typedef float(__fastcall* fnGetTimerExpiry)(const GameObject*);
	static fnGetTimerExpiry fn = (fnGetTimerExpiry)MAKE_RVA(Addresses::GameObjectAddresses::GetTimerExpiry);

	float value = x64RetSpoof::spoof_call(fn, this) - GameClock::get_time();

	return value > 0 ? value : 0;
}

bool GameObject::compare_object_type_flag(Enums::TypeFlag flag) const
{
	typedef bool(__fastcall* fnCompObjFlag)(uintptr_t, DWORD);
	static fnCompObjFlag fn = (fnCompObjFlag)MAKE_RVA(Addresses::GameObjectAddresses::CompareTypeFlags);

	return x64RetSpoof::spoof_call(fn, (uintptr_t) this, (DWORD) flag);
}

float GameObject::get_attack_delay() const
{
	typedef float(__fastcall* fnAtkDelay)(uintptr_t, uint32_t);
	static fnAtkDelay fn = (fnAtkDelay)MAKE_RVA(Addresses::GameObjectAddresses::GetAttackDelay);

	return x64RetSpoof::spoof_call(fn, (uintptr_t)this, (uint32_t) 0);
}

float GameObject::get_attack_cast_delay() const
{
	typedef float(__fastcall* fnAtkCastDelay)(uintptr_t);
	static fnAtkCastDelay fn = (fnAtkCastDelay)MAKE_RVA(Addresses::GameObjectAddresses::GetAttackCastDelay);

	return x64RetSpoof::spoof_call(fn, (uintptr_t)this);
}

bool GameObject::is_invulnerable() const
{
	return RVA_CAST_THIS(bool, Structures::GameObject::IsInvulnerable) == 1;
}

SpellData* GameObject::get_basic_attack() const
{
	typedef SpellData**(__fastcall* fnGetBasicAtk)(uintptr_t);
	static fnGetBasicAtk fn = (fnGetBasicAtk)MAKE_RVA(Addresses::GameObjectAddresses::GetBasicAttack);

	return *x64RetSpoof::spoof_call(fn, (uintptr_t)this);
}

Vec2 GameObject::get_health_bar_screen_position() const
{
	const auto uic = get_unit_info_component();
	Vec2 ret{ };

	typedef int64_t(__fastcall* fnHpBarPos)(uintptr_t, Vec2*, uintptr_t);
	static fnHpBarPos fn = (fnHpBarPos)MAKE_RVA(Addresses::GameObjectAddresses::GetHealthBarScreenPosition);

	x64RetSpoof::spoof_call(fn, uic, &ret, *(uintptr_t*)(MAKE_RVA(Addresses::r3dRenderer::screenInstance))+ (uintptr_t) Addresses::r3dRenderer::screenInstance_W2S);

	return ret;
}

bool GameObject::is_alive() const
{
	typedef bool(__fastcall* fnIsDead)(const GameObject*);
	static fnIsDead fn = (fnIsDead)MAKE_RVA(Addresses::GameObjectAddresses::IsDead);

	return !x64RetSpoof::spoof_call(fn, this) && get_health() > 0;
}

/*
 *		CUSTOM IMPLEMENTATION FUNCTIONS
 */

bool GameObject::is_ally() const
{
	return get_team() == get_local_player()->get_team();
}

bool GameObject::is_ally(const GameObject* other) const
{
	return get_team() == other->get_team();
}

bool GameObject::is_enemy() const
{
	return !is_ally();
}

bool GameObject::is_enemy(const GameObject* other) const
{
	return !is_ally(other);
}

bool GameObject::is_neutral() const
{
	return get_team() == Enums::GameObjectTeam::Neutral;
}

Enums::SpellState GameObject::get_spell_state(Enums::SpellSlot spell_slot) const
{
	return get_spell_book_ref()->get_spell_state(spell_slot);
}

bool GameObject::can_use_spell(Enums::SpellSlot spell_slot) const
{
	return get_spell_book_ref()->can_use_spell(spell_slot);
}

bool GameObject::is_cast_object_winding_up() const
{
	if (!is_champion() && !is_minion())
		return false;

	typedef bool(__thiscall* vtableFunc)(const GameObject*);
	return base::call_virtual<vtableFunc>((PVOID)this, (uintptr_t) Structures::GameObjectVTable::IsCastObjectWindingUp)(this);
}

Enums::GameObjectType GameObject::get_type() const
{
	typedef uintptr_t(__thiscall* vtableFunc)(const GameObject*);
	uintptr_t addr = base::call_virtual<vtableFunc>((PVOID) this, 1)(this);

	if (addr)
		return static_cast<Enums::GameObjectType>(*reinterpret_cast<uintptr_t*>(addr + 0x8));

	return Enums::GameObjectType::Unknown;
}

uintptr_t GameObject::get_unit_info_component() const
{
	const EncryptedBuffer<uint64_t>* uic
		= reinterpret_cast<EncryptedBuffer<uint64_t>*>((uintptr_t)this + (uintptr_t)Structures::GameObject::UnitInfoComponent);
	return uic->Decrypt();
}

bool GameObject::is_me() const
{
	return this->get_network_id() == get_local_player()->get_network_id();
}

bool GameObject::is_minion() const
{
	return compare_object_type_flag(Enums::TypeFlag::Minion);
}

bool GameObject::is_lane_minion() const
{
	if (!is_minion())
		return false;
	
	const EncryptedBuffer<bool>* is_lane_minion
		= reinterpret_cast<EncryptedBuffer<bool>*>((uintptr_t)this + (uintptr_t)Structures::GameObject::EncryptedIsLaneMinion);
	return is_lane_minion->Decrypt();
}

bool GameObject::is_inhibitor() const
{
	return compare_object_type_flag(Enums::TypeFlag::Building) && get_type() == Enums::GameObjectType::BarracksDampener;
}

bool GameObject::is_nexus() const
{
	return compare_object_type_flag(Enums::TypeFlag::Building) && get_type() == Enums::GameObjectType::HQ;
}

bool GameObject::is_champion() const
{
	return compare_object_type_flag(Enums::TypeFlag::Hero);
}

bool GameObject::is_turret() const
{
	return compare_object_type_flag(Enums::TypeFlag::Turret);
}

bool GameObject::is_missile() const
{
	return compare_object_type_flag(Enums::TypeFlag::Missile);
}

bool GameObject::is_effect_emitter() const
{
	return get_type() == Enums::GameObjectType::obj_GeneralParticleEmitter;	
}

bool GameObject::is_ward() const
{
	if (!is_minion() || is_plant()) 
		return false;

	const auto char_hash = get_character_hash();

	return char_hash == 0x8223B6BA
	|| char_hash == 0x7C1BCAD9
	|| char_hash == 0x97648C10
	|| char_hash == 0x55814507
	|| char_hash == 0x5783643F
	|| char_hash == 0x40D7e043
	|| char_hash == 0xE20532FD;
}

bool GameObject::is_baron() const
{
	return is_minion() && get_character_hash() == 0x68AC12C9;
}

bool GameObject::is_herald() const
{
	return is_minion() && get_character_hash() == 0xddaf53d2;
}

bool GameObject::is_dragon() const
{
	if (!is_minion())
		return false;

	const uint32_t hash = get_character_hash();

	return hash == 0x11d34e07
		|| hash == 0x606dcd87
		|| hash == 0x99a947d9
		|| hash == 0x27f996f4
		|| hash == 0xa076eece
		|| hash == 0x5944e907
		|| hash == 0xf956a026;
}

bool GameObject::has_buff(const std::string& buff_name) const
{
	return get_buff_manager()->get_buff(buff_name);
}

bool GameObject::has_buff(const uint32_t buff_hash) const
{
	return get_buff_manager()->get_buff_by_hash(buff_hash);
}

bool GameObject::has_buff_type(Enums::BuffType buff_type) const
{
	return get_buff_manager()->has_buff_type(buff_type);
}

bool GameObject::has_item(Enums::ItemId item_id) const
{
	return get_item(item_id) != nullptr;
}

bool GameObject::can_use_item(Enums::ItemId item_id) const
{
	const auto slot = get_item_spell_slot(item_id);

	return can_use_spell(slot->get_slot_id()) && slot->get_ammo() > 0;
}

bool GameObject::is_plant() const
{
	return is_minion() && get_name().find(skCrypt("Plant")) != std::string::npos;
}

bool GameObject::is_pet() const
{
	if (!is_minion())
		return false;

	const EncryptedBuffer<bool>* uic
		= reinterpret_cast<EncryptedBuffer<bool>*>((uintptr_t)this + (uintptr_t)Structures::GameObject::EncryptedIsPet);
	return uic->Decrypt();
}

bool GameObject::is_clone() const
{
	if (!is_minion())
		return false;

	typedef bool(__fastcall* fnIsClone)(const GameObject*);
	static fnIsClone fn = (fnIsClone)MAKE_RVA(Addresses::GameObjectAddresses::IsClone);

	return x64RetSpoof::spoof_call(fn, this);
}

bool GameObject::is_neutral_camp() const
{
	return get_type() == Enums::GameObjectType::NeutralMinionCamp;
}

bool GameObject::is_facing(const Vec3& position) const
{
	return this->get_position().to_2d().angle_between(position.to_2d()) < 90.0f;
}

bool GameObject::is_facing_obj(const GameObject* target) const
{
	return this->is_facing(target->get_position());
}

bool GameObject::is_practice_tool_dummy() const
{
	if (!is_champion())
		return false;

	return get_character_hash() == 0x6a9da18b;
}

bool GameObject::is_visible_on_screen(int tolerance) const
{
	return this->get_position().is_on_screen(tolerance);
}

bool GameObject::is_melee() const
{
	return get_combat_type() == Enums::CombatType::Melee;
}

bool GameObject::is_ranged() const
{
	return !is_melee();
}

bool GameObject::is_recalling() const
{
	return get_recall_state() == Enums::RecallState::Recall || get_recall_state() == Enums::RecallState::EmpoweredRecall;
}

bool GameObject::is_teleporting() const
{
	return get_recall_state() == Enums::RecallState::Teleport;
}

ItemSlot* GameObject::get_item(Enums::ItemId item) const
{
	if (!is_champion())
		return nullptr;

	for(int i = 0; i < 7; i++)
	{
		ItemSlot* itemSlot = *reinterpret_cast<ItemSlot**>(reinterpret_cast<uintptr_t>(this) + static_cast<unsigned int>(Structures::GameObject::ItemList) + 0x8 * i);

		if (!itemSlot)
			continue;

		if(itemSlot->get_item_id() == item)
		{
			return itemSlot;
		}
	}

	return nullptr;
}

SpellSlot* GameObject::get_item_spell_slot(Enums::ItemId item) const
{
	if (!is_champion())
		return nullptr;

	for (int i = 0; i < 7; i++)
	{
		ItemSlot* itemSlot = *reinterpret_cast<ItemSlot**>(reinterpret_cast<uintptr_t>(this) + static_cast<unsigned int>(Structures::GameObject::ItemList) + sizeof(uintptr_t) * i);

		if (!itemSlot)
			continue;

		if (itemSlot->get_item_id() == item)
		{
			return get_spell_slot_by_id((Enums::SpellSlot) ((int) Enums::SpellSlot::Item1 + i));
		}
	}

	return nullptr;
}

SpellSlot* GameObject::get_spell_slot_by_id(Enums::SpellSlot id) const
{
	return *reinterpret_cast<SpellSlot**>(reinterpret_cast<uintptr_t>(this) + static_cast<unsigned int>(Structures::GameObject::SpellBook) + static_cast<unsigned int>(Structures::SpellBook::FirstSlot) + 0x8 * static_cast<int>(id));
}

SpellCastInfo* GameObject::get_active_spell() const
{
	uintptr_t ptr = RVA_CAST_THIS(uintptr_t, (uint32_t) Structures::GameObject::SpellBook + (uint32_t) Structures::SpellBook::ActiveSpell);

	if (!ptr)
		return nullptr;

	return (SpellCastInfo*)(ptr + 0x8);
}

BuffEntry* GameObject::get_buff(const std::string& buff_name) const
{
	return this->get_buff_manager()->get_buff(buff_name);
}

BuffEntry* GameObject::get_buff_by_hash(const uint32_t buffHash) const
{
	return this->get_buff_manager()->get_buff_by_hash(buffHash);
}

CharacterState* GameObject::get_character_state() const
{
	return RVA_CAST_THIS_REF(CharacterState*, Structures::GameObject::CharacterState);
}

GameObject* GameObject::get_owner_player() const
{
	if (!compare_object_type_flag(Enums::TypeFlag::AttackableUnit))
		return nullptr;

	typedef GameObject*(__fastcall* fnGetOwnerPlayer)(const GameObject*);
	static fnGetOwnerPlayer fn = (fnGetOwnerPlayer)MAKE_RVA(Addresses::GameObjectAddresses::GetOwnerPlayer);

	return fn(this);
}

uint32_t GameObject::get_effect_hash() const
{
	if (!is_effect_emitter())
		return 0;

	if (!effect_emitter_owners.contains(this))
		return 0;

	return effect_emitter_owners[this].effect_hash;
}

GameObject* GameObject::get_emitter() const
{
	if (!is_effect_emitter())
		return 0;

	if (!effect_emitter_owners.contains(this))
		return 0;

	return effect_emitter_owners[this].emitter;
}

GameObject* GameObject::get_attachment() const
{
	if (!is_effect_emitter())
		return nullptr;
	
	if (const auto emitter = get_effect_emitter())
	{
		if (const auto attachment = emitter->get_attachment())
			return attachment->get_object();
	}

	return nullptr;
}

GameObject* GameObject::get_target_attachment() const
{
	if (!is_effect_emitter())
		return nullptr;
	
	if (const auto emitter = get_effect_emitter())
	{
		if (const auto attachment = emitter->get_target_attachment())
			return attachment->get_object();
	}

	return nullptr;
}

std::vector<BuffEntry*> GameObject::get_buffs() const
{
	return this->get_buff_manager()->get_buffs();
}

std::vector<BuffEntry*> GameObject::get_buffs(Enums::BuffType buffs_type) const
{
	return this->get_buff_manager()->get_buffs(buffs_type);
}

void GameObject::issue_order(Enums::IssueOrderType order, Vec3* position, GameObject* target, bool is_attack_move, bool is_minion, bool unk) const
{
	Bypass::issueorder_flag(order);
	Bypass::mainloop_check();

	typedef char(__fastcall* fnIssueOrder)(uintptr_t, uint8_t, Vec3*, GameObject*, bool, bool, bool);
	static fnIssueOrder fn = (fnIssueOrder)MAKE_RVA(Addresses::LocalPlayer::IssueOrder);

	x64RetSpoof::spoof_call(fn, (uintptr_t) get_local_player(), (uint8_t) order, position, target, is_attack_move, is_minion, unk);

	Bypass::issueorder_flag(order);
	Bypass::mainloop_check();
}

void GameObject::user_issue_order(Enums::IssueOrderType order, Vec3 position, GameObject* target) const
{
	issue_order(order, &position, target, false, false, false);
}

void GameObject::cast_spell(Enums::SpellSlot slotId, const Vec3& start_pos, const Vec3& end_pos, GameObject* target) const
{
	if (get_spell_state(slotId) == Enums::SpellState::Ready)
		get_spell_book()->send_spellcast_packet(slotId, start_pos, end_pos, target);
}

void GameObject::update_charged_spell(Enums::SpellSlot slot_id, Vec3& position, bool release) const
{
	get_spell_book()->update_charged_spell(get_spell_slot_by_id(slot_id), slot_id, &position, release);
}

GameObject* GameObject::get_local_player() {
	return RVA_CAST(GameObject*, Addresses::LocalPlayer::LocalPlayerInstance);
}

bool GameObject::apply_hooks()
{
	HookOnProcessSpell.apply_jmp(MAKE_RVA(Addresses::GameObjectAddresses::OnProcessSpell), (uintptr_t) Wrapper::OnProcessSpellCallee, 19);
	HookOnProcessAutoAttack.apply_jmp(MAKE_RVA(Addresses::GameObjectAddresses::ProcessAutoAttack), (uintptr_t) Wrapper::OnProcessAutoAttackCallee, 18);
	HookOnCreateObject.apply_jmp(MAKE_RVA(Addresses::GameObjectAddresses::OnCreateObject), (uintptr_t) Wrapper::OnCreateObjectCallee, 16);
	HookOnDeleteObject.apply_jmp(MAKE_RVA(Addresses::GameObjectAddresses::OnDeleteObject), (uintptr_t) Wrapper::OnDeleteObjectCallee, 16);
	HookOnIssueOrder.apply_jmp(MAKE_RVA(Addresses::LocalPlayer::IssueOrder), (uintptr_t) Wrapper::OnIssueOrderCallee, 15);
	HookOnPlayAnimation.apply_jmp(MAKE_RVA(Addresses::GameObjectAddresses::PlayAnimation), (uintptr_t) Wrapper::OnPlayAnimationCallee, 15);
	HookOnBuffAdd.apply_jmp(MAKE_RVA(Addresses::GameObjectAddresses::OnBuffAdd), (uintptr_t)Wrapper::OnBuffAddCallee, 14);
	HookOnBuffRemove.apply_jmp(MAKE_RVA(Addresses::GameObjectAddresses::OnBuffRemove), (uintptr_t)Wrapper::OnBuffRemoveCallee, 16);
	HookOnSetPath.apply_jmp(MAKE_RVA(Addresses::GameObjectAddresses::SetPath), (uintptr_t)Wrapper::OnSetPathCallee, 17);
	HookOnCreateClientEffect.apply_jmp(MAKE_RVA(Addresses::GameObjectAddresses::CreateClientEffect), (uintptr_t) Wrapper::OnCreateClientEffectCallee, 16);
	HookOnGetHealthBarScreenPosDetection.apply_jmp(MAKE_RVA(Addresses::Bypass::GetHealthBarScreenPositionDetection), (uintptr_t) Wrapper::OnGetHealthBarScreenPosDetectionCallee, (size_t) 15);
	//HookOnDebug2.apply_jmp(MAKE_RVA(0x36fd10), (uintptr_t)Wrapper::Debug2, (size_t) 16);

	return true;
}
