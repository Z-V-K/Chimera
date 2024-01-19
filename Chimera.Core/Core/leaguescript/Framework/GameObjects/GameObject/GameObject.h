#pragma once

#include "CharacterData.h"
#include "../../../SDK/LUA/LuaTexture.h"
#include "../EffectEmitter/EffectEmitter.h"

#include "../Impl/Common/Common.h"
#include "../Impl/Vector/Vector.h"
#include "../Framework/Enums/GameObjectEnums.h"
#include "../Framework/Enums/SpellEnums.h"
#include "../Framework/Items/ItemSlot/ItemSlot.h"
#include "../Framework/Spells/Spellbook/SpellBook.h"
#include "../Framework/GameObjects/MissileClient/MissileClient.h"
#include "../Framework/Buffs/BuffManager/BuffManager.h"
#include "../Framework/Spells/SpellCastInfo/SpellCastInfo.h"
#include "../Framework/CharacterInfo/CharacterState.h"
#include "../Framework/Navigation/PathControllerCommon/PathControllerCommon.h"

#ifndef EXPORT_FUNC
#define EXPORT_FUNC(RET, NAME, ARGS_IN, ARGS_OUT ) \
virtual RET __EXPORT##NAME ARGS_IN { return obj->NAME ARGS_OUT; };
#endif

class SpellCastInfo;

class GameObject final
{
private:
	uintptr_t* VTable();
public:
	
	void issue_order(Enums::IssueOrderType order, Vec3* position, GameObject* target, bool is_attack_move, bool is_minion, bool unk) const;
	void user_issue_order(Enums::IssueOrderType order, Vec3 position, GameObject* target) const;

	void cast_spell(Enums::SpellSlot slot_id, const Vec3& start_pos, const Vec3& end_pos, GameObject* target) const;

	void update_charged_spell(Enums::SpellSlot slot_id, Vec3& position, bool release) const;

	MissileClient* get_missile_client() const;
	EffectEmitter* get_effect_emitter() const;
	BuffManager* get_buff_manager() const;
	Spellbook* get_spell_book() const;
	Spellbook* get_spell_book_ref() const;
	PathControllerCommon* get_path_controller_common() const;
	SpellData* get_basic_attack() const;
	ItemSlot* get_item(Enums::ItemId item) const;
	SpellSlot* get_item_spell_slot(Enums::ItemId item) const;
	SpellSlot* get_spell_slot_by_id(Enums::SpellSlot id) const;
	SpellCastInfo* get_active_spell() const;
	BuffEntry* get_buff(const std::string& buff_name) const;
	BuffEntry* get_buff_by_hash(const uint32_t buff_name) const;
	CharacterState* get_character_state() const;
	GameObject* get_owner_player() const;

	uint32_t get_effect_hash() const;
	GameObject* get_emitter() const;
	GameObject* get_attachment() const;
	GameObject* get_target_attachment() const;
	
	std::vector<BuffEntry*> get_buffs() const;
	std::vector<BuffEntry*> get_buffs(Enums::BuffType buffs_type) const;
	std::vector<ItemSlot*> get_items() const;

	std::string get_name() const;
	std::string get_model_name() const;
	uint32_t get_character_hash() const;
	CharacterData* get_character_data() const;

	const Vec3& get_position() const;
	const Vec3& get_direction() const;
	Vec2 get_health_bar_screen_position() const;

	Enums::GameObjectTeam get_team() const;
	Enums::CombatType get_combat_type() const;
	Enums::RecallState get_recall_state() const;

	int get_buff_count(const std::string& buff_name) const;
	int get_buff_count(uint32_t buff_hash) const;

	unsigned get_index() const;
	unsigned get_network_id() const;
	float get_current_gold() const;
	unsigned get_visibility() const;
	unsigned get_level_up_points() const;
	unsigned get_level() const;

	float get_bounding_radius() const;
	float get_health() const;
	float get_max_health() const;
	float get_bonus_health() const;
	float get_bonus_mana() const;
	float get_shield() const;
	float get_magic_shield() const;
	float get_physical_shield() const;
	float get_mana() const;
	float get_max_mana() const;
	float get_ability_haste() const;
	float get_lethality() const;
	float get_armor() const;
	float get_bonus_armor() const;
	float get_magic_res() const;
	float get_bonus_magic_res() const;
	float get_base_ad() const;
	float get_bonus_ad() const;
	float get_movement_speed() const;
	float get_crit_damage_multiplier() const;
	float get_crit() const;
	float get_ap() const;
	float get_bonus_ap_multiplier() const;
	float get_attack_speed_multiplier() const;
	float get_attack_range() const;
	bool is_targetable() const;
	float get_accumulated_experience() const;
	float get_magic_pen_flat() const;
	float get_armor_pen_multiplier() const;
	float get_magic_pen_multiplier() const;
	float get_mana_regen() const;
	float get_health_regen() const;
	float get_attack_delay() const;
	float get_attack_cast_delay() const;

	Enums::SpellState get_spell_state(Enums::SpellSlot spell_slot) const;
	bool can_use_spell(Enums::SpellSlot spell_slot) const;

	bool is_cast_object_winding_up() const;

	bool is_invulnerable() const;
	bool is_visible_on_screen(int tolerance = 0) const; 
	bool is_melee() const;
	bool is_ranged() const;
	bool is_ally() const;
	bool is_ally(const GameObject* other) const;
	bool is_enemy() const;
	bool is_enemy(const GameObject* other) const;
	bool is_neutral() const;
	bool is_visible() const;
	bool is_zombie() const;
	bool is_recalling() const;
	bool is_teleporting() const;
	bool compare_object_type_flag(Enums::TypeFlag flag) const;
	bool has_buff(const std::string& buff_name) const;
	bool has_buff(const uint32_t buff_hash) const;
	bool has_buff_type(Enums::BuffType buff_type) const;
	bool has_item(Enums::ItemId item_id) const;
	bool can_use_item(Enums::ItemId item_id) const;
	bool is_me() const;
	Enums::GameObjectType get_type() const;
	uintptr_t get_unit_info_component() const;
	bool is_minion() const;
	bool is_lane_minion() const;
	bool is_inhibitor() const;
	bool is_nexus() const;
	bool is_champion() const;
	bool is_turret() const;
	bool is_missile() const;
	bool is_effect_emitter() const;
	bool is_ward() const;
	bool is_baron() const;
	bool is_herald() const;
	bool is_dragon() const;
	bool is_alive() const;
	bool is_plant() const;
	bool is_pet() const;
	bool is_practice_tool_dummy() const;
	bool is_clone() const;
	bool is_neutral_camp() const;
	bool is_facing(const Vec3& position) const;
	bool is_facing_obj(const GameObject* game_object) const;
	bool is_in_range_obj(const GameObject* game_object, float range) const;
	bool is_in_range(const Vec3& position, float range) const;
	bool is_in_auto_attack_range(const GameObject* to, float extra_range = 0) const;
	bool is_valid_target(float range, const Vec3& from = Vec3(), bool ignore_invulnerability = false) const;

	Enums::TurretType get_turret_type() const;

	float get_base_health_for_level() const;
	PVOID get_circle_icon() const;
	PVOID get_square_icon() const;

	LuaTexture get_circle_icon_lua() const;
	LuaTexture get_square_icon_lua() const;

	bool operator==(const GameObject* other) const;
	bool operator!=(const GameObject* other) const;

	float get_total_respawn_time() const;
	float get_remaining_respawn_time() const;
	float get_gold_given_on_death() const;

	float get_timer_expiry() const;

	static bool apply_hooks();

	static GameObject* get_local_player();

#pragma region EXPORTS
	EXPORT_FUNC(void, user_issue_order, (GameObject* obj, Enums::IssueOrderType order, Vec3& position, GameObject* target), (order, position, target))
	EXPORT_FUNC(void, cast_spell, (GameObject* obj, Enums::SpellSlot slotId, const Vec3& startPos, const Vec3& endPos, GameObject* target), (slotId, startPos, endPos, target))
	EXPORT_FUNC(void, update_charged_spell, (GameObject* obj, Enums::SpellSlot slotId, Vec3& position, bool release), (slotId, position, release))
	EXPORT_FUNC(Enums::GameObjectType, get_type, (GameObject* obj), ())
	EXPORT_FUNC(MissileClient*, get_missile_client, (GameObject* obj), ());
	EXPORT_FUNC(PathControllerCommon*, get_path_controller_common, (GameObject* obj), ());
	EXPORT_FUNC(SpellData*, get_basic_attack, (GameObject* obj), ());
	EXPORT_FUNC(bool, has_item, (GameObject* obj, Enums::ItemId item), (item));
	EXPORT_FUNC(bool, can_use_item, (GameObject* obj, Enums::ItemId item), (item));
	EXPORT_FUNC(ItemSlot*, get_item, (GameObject* obj, Enums::ItemId item), (item));
	EXPORT_FUNC(SpellSlot*, get_item_spell_slot, (GameObject* obj, Enums::ItemId item), (item));

	EXPORT_FUNC(bool, is_effect_emitter, (GameObject* obj), ());
	EXPORT_FUNC(uint32_t, get_effect_hash, (GameObject* obj), ());
	EXPORT_FUNC(GameObject*, get_emitter, (GameObject* obj), ());
	EXPORT_FUNC(GameObject*, get_attachment, (GameObject* obj), ());
	EXPORT_FUNC(GameObject*, get_target_attachment, (GameObject* obj), ());

	EXPORT_FUNC(SpellSlot*, get_spell_slot_by_id, (GameObject* obj, Enums::SpellSlot id), (id));
	EXPORT_FUNC(SpellCastInfo*, get_active_spell, (GameObject* obj), ());
	EXPORT_FUNC(Enums::SpellState, get_spell_state, (GameObject* obj, Enums::SpellSlot id), (id));
	EXPORT_FUNC(bool, can_use_spell, (GameObject* obj, Enums::SpellSlot id), (id));
	EXPORT_FUNC(BuffEntry*, get_buff_by_hash, (GameObject* obj, const uint32_t buffHash), (buffHash));

	EXPORT_FUNC(bool, is_cast_object_winding_up, (GameObject* obj), ());

	EXPORT_FUNC(std::vector<BuffEntry*>, get_buffs, (GameObject* obj), ());
	EXPORT_FUNC(std::vector<BuffEntry*>, get_buffs, (GameObject* obj, Enums::BuffType buffsType), (buffsType));
	EXPORT_FUNC(std::vector<ItemSlot*>, get_items, (GameObject* obj), ());

	EXPORT_FUNC(std::string, get_name, (GameObject* obj), ());
	EXPORT_FUNC(std::string, get_model_name, (GameObject* obj), ());
	EXPORT_FUNC(uint32_t, get_character_hash, (GameObject* obj), ());
	EXPORT_FUNC(PVOID, get_circle_icon, (GameObject* obj), ());
	EXPORT_FUNC(PVOID, get_square_icon, (GameObject* obj), ());

	EXPORT_FUNC(const Vec3&, get_position, (GameObject* obj), ());
	EXPORT_FUNC(const Vec3&, get_direction, (GameObject* obj), ());
	EXPORT_FUNC(Vec2, get_health_bar_screen_position, (GameObject* obj), ());
	EXPORT_FUNC(GameObject*, get_owner_player, (GameObject* obj), ());

	EXPORT_FUNC(Enums::GameObjectTeam, get_team, (GameObject* obj), ());

	EXPORT_FUNC(int, get_buff_count, (GameObject* obj, uint32_t buffHash), (buffHash));

	EXPORT_FUNC(unsigned, get_index, (GameObject* obj), ());
	EXPORT_FUNC(unsigned, get_network_id, (GameObject* obj), ());
	EXPORT_FUNC(float, get_current_gold, (GameObject* obj), ());
	EXPORT_FUNC(unsigned, get_visibility, (GameObject* obj), ());
	EXPORT_FUNC(unsigned, get_level_up_points, (GameObject* obj), ());
	EXPORT_FUNC(unsigned, get_level, (GameObject* obj), ());

	EXPORT_FUNC(float, get_bounding_radius, (GameObject* obj), ());
	EXPORT_FUNC(float, get_health, (GameObject* obj), ());
	EXPORT_FUNC(float, get_max_health, (GameObject* obj), ());
	EXPORT_FUNC(float, get_bonus_health, (GameObject* obj), ());
	EXPORT_FUNC(float, get_bonus_mana, (GameObject* obj), ());
	EXPORT_FUNC(float, get_shield, (GameObject* obj), ());
	EXPORT_FUNC(float, get_physical_shield, (GameObject* obj), ());
	EXPORT_FUNC(float, get_magic_shield, (GameObject* obj), ());
	EXPORT_FUNC(float, get_mana, (GameObject* obj), ());
	EXPORT_FUNC(float, get_max_mana, (GameObject* obj), ());
	EXPORT_FUNC(float, get_ability_haste, (GameObject* obj), ());
	EXPORT_FUNC(float, get_lethality, (GameObject* obj), ());
	EXPORT_FUNC(float, get_armor, (GameObject* obj), ());
	EXPORT_FUNC(float, get_bonus_armor, (GameObject* obj), ());
	EXPORT_FUNC(float, get_magic_res, (GameObject* obj), ());
	EXPORT_FUNC(float, get_bonus_magic_res, (GameObject* obj), ());
	EXPORT_FUNC(float, get_base_ad, (GameObject* obj), ());
	EXPORT_FUNC(float, get_bonus_ad, (GameObject* obj), ());
	EXPORT_FUNC(float, get_movement_speed, (GameObject* obj), ());
	EXPORT_FUNC(float, get_crit_damage_multiplier, (GameObject* obj), ());
	EXPORT_FUNC(float, get_crit, (GameObject* obj), ());
	EXPORT_FUNC(float, get_ap, (GameObject* obj), ());
	EXPORT_FUNC(float, get_bonus_ap_multiplier, (GameObject* obj), ());
	EXPORT_FUNC(float, get_attack_speed_multiplier, (GameObject* obj), ());
	EXPORT_FUNC(float, get_attack_range, (GameObject* obj), ());
	EXPORT_FUNC(float, is_targetable, (GameObject* obj), ());
	EXPORT_FUNC(float, get_accumulated_experience, (GameObject* obj), ());
	EXPORT_FUNC(float, get_magic_pen_flat, (GameObject* obj), ());
	EXPORT_FUNC(float, get_armor_pen_multiplier, (GameObject* obj), ());
	EXPORT_FUNC(float, get_magic_pen_multiplier, (GameObject* obj), ());
	EXPORT_FUNC(float, get_mana_regen, (GameObject* obj), ());
	EXPORT_FUNC(float, get_health_regen, (GameObject* obj), ());
	EXPORT_FUNC(float, get_attack_delay, (GameObject* obj), ());
	EXPORT_FUNC(float, get_attack_cast_delay, (GameObject* obj), ());

	EXPORT_FUNC(bool, is_invulnerable, (GameObject* obj), ());
	EXPORT_FUNC(bool, is_visible_on_screen, (GameObject* obj, int tolerance = 0), (tolerance));
	EXPORT_FUNC(bool, is_melee, (GameObject* obj), ());
	EXPORT_FUNC(bool, is_ranged, (GameObject* obj), ());
	EXPORT_FUNC(bool, is_ally, (GameObject* obj), ());
	EXPORT_FUNC(bool, is_ally, (GameObject* obj, GameObject* other), (other));
	EXPORT_FUNC(bool, is_enemy, (GameObject* obj), ());
	EXPORT_FUNC(bool, is_enemy, (GameObject* obj, GameObject* other), (other));
	EXPORT_FUNC(bool, is_neutral, (GameObject* obj), ());
	EXPORT_FUNC(bool, is_visible, (GameObject* obj), ());
	EXPORT_FUNC(bool, is_zombie, (GameObject* obj), ());
	EXPORT_FUNC(bool, is_recalling, (GameObject* obj), ());
	EXPORT_FUNC(bool, is_teleporting, (GameObject* obj), ());
	EXPORT_FUNC(bool, compare_object_type_flag, (GameObject* obj, Enums::TypeFlag flag), (flag));
	EXPORT_FUNC(bool, has_buff, (GameObject* obj, const uint32_t buffHash), (buffHash));
	EXPORT_FUNC(bool, has_buff_type, (GameObject* obj, Enums::BuffType buffType), (buffType));
	EXPORT_FUNC(bool, is_me, (GameObject* obj), ());
	EXPORT_FUNC(bool, is_minion, (GameObject* obj), ());
	EXPORT_FUNC(bool, is_lane_minion, (GameObject* obj), ());
	EXPORT_FUNC(bool, is_inhibitor, (GameObject* obj), ());
	EXPORT_FUNC(bool, is_nexus, (GameObject* obj), ());
	EXPORT_FUNC(bool, is_champion, (GameObject* obj), ());
	EXPORT_FUNC(bool, is_turret, (GameObject* obj), ());
	EXPORT_FUNC(bool, is_missile, (GameObject* obj), ());
	EXPORT_FUNC(bool, is_neutral_camp, (GameObject* obj), ());
	EXPORT_FUNC(bool, is_ward, (GameObject* obj), ());
	EXPORT_FUNC(bool, is_baron, (GameObject* obj), ());
	EXPORT_FUNC(bool, is_herald, (GameObject* obj), ());
	EXPORT_FUNC(bool, is_dragon, (GameObject* obj), ());
	EXPORT_FUNC(bool, is_alive, (GameObject* obj), ());
	EXPORT_FUNC(bool, is_plant, (GameObject* obj), ());
	EXPORT_FUNC(bool, is_pet, (GameObject* obj), ());
	EXPORT_FUNC(bool, is_practice_tool_dummy, (GameObject* obj), ());
	EXPORT_FUNC(bool, is_clone, (GameObject* obj), ());
	EXPORT_FUNC(bool, is_facing, (GameObject* obj, const Vec3& position), (position));
	EXPORT_FUNC(bool, is_facing_obj, (GameObject* obj, GameObject* gameObject), (gameObject));
	EXPORT_FUNC(bool, is_in_range_obj, (GameObject* obj, GameObject* gameObject, float range), (gameObject, range));
	EXPORT_FUNC(bool, is_in_range, (GameObject* obj, const Vec3& position, float range), (position, range));
	EXPORT_FUNC(bool, is_in_auto_attack_range, (GameObject* obj, GameObject* to, float extraRange = 0), (to, extraRange));
	EXPORT_FUNC(bool, is_valid_target, (GameObject* obj, float range, const Vec3& from = Vec3(), bool bIgnoreInvulnerability = false), (range, from, bIgnoreInvulnerability));

	EXPORT_FUNC(Enums::TurretType, get_turret_type, (GameObject* obj), ());

	EXPORT_FUNC(float, get_total_respawn_time, (GameObject* obj), ());
	EXPORT_FUNC(float, get_remaining_respawn_time, (GameObject* obj), ());
	EXPORT_FUNC(float, get_gold_given_on_death, (GameObject* obj), ());
	EXPORT_FUNC(float, get_timer_expiry, (GameObject* obj), ());
#pragma endregion
};
#ifdef EXPORT_FUNC
#undef EXPORT_FUNC
#endif