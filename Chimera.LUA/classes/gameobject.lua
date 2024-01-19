---@class gameobject
---@field public type integer
---@field public missile_client missileclient
---@field public pcc pcc
---@field public basic_attack spelldata
---@field public effect_hash number
---@field public emitter gameobject
---@field public attachment gameobject
---@field public target_attachment gameobject
---@field public buffs buff[]
---@field public items item[]
---@field public name string
---@field public model_name string
---@field public character_hash number
---@field public circle_icon texture
---@field public square_icon texture
---@field public position vec3
---@field public direction vec3
---@field public hp_bar_pos vec2
---@field public owner_player gameobject
---@field public team integer
---@field public index integer
---@field public netid integer
---@field public golds number
---@field public visibility number
---@field public levelup_points number
---@field public level number
---@field public bounding number
---@field public health number
---@field public max_health number
---@field public bonus_health number
---@field public bonus_mana number
---@field public shield number
---@field public magic_shield number
---@field public mana number
---@field public max_mana number
---@field public ability_haste number
---@field public lethality number
---@field public armor number
---@field public bonus_armor number
---@field public magic_res number
---@field public bonus_magic_res number
---@field public base_ad number
---@field public movement_speed number
---@field public crit_damage_multiplier number
---@field public crit number
---@field public ap number
---@field public bonus_ap_multiplier number
---@field public attack_speed_multiplier number
---@field public attack_range number
---@field public is_targetable boolean
---@field public accumulated_experience number
---@field public magic_pen_flat number
---@field public armor_pen_multiplier number
---@field public magic_pen_multiplier number
---@field public mana_regen number
---@field public health_regen number
---@field public attack_delay number
---@field public attack_cast_delay number
---@field public is_invulnerable boolean
---@field public is_melee boolean
---@field public is_ranged boolean
---@field public is_ally boolean
---@field public is_enemy boolean
---@field public is_neutral boolean
---@field public is_visible boolean
---@field public is_zombie boolean
---@field public is_recalling boolean
---@field public is_teleporting boolean
---@field public is_me boolean
---@field public is_minion boolean
---@field public is_lane_minion boolean
---@field public is_inhibitor boolean
---@field public is_nexus boolean
---@field public is_champion boolean
---@field public is_turret boolean
---@field public is_missile boolean
---@field public is_neutral_camp boolean
---@field public is_ward boolean
---@field public is_baron boolean
---@field public is_herald boolean
---@field public is_dragon boolean
---@field public is_alive boolean
---@field public is_plant boolean
---@field public is_pet boolean
---@field public is_practice_tool_dummy boolean
---@field public is_clone boolean
---@field public turret_type number
---@field public total_respawn_time number
---@field public remaining_respawn_time number
---@field public gold_on_death number
---@field public timer_expiry number
local gameobject = { }

---@param order number
---@param position vec3
---@param target gameobject
---@return nil
function gameobject:issue_order(order, position, target) end

---@param slot number
---@param start_pos vec3
---@param end_pos vec3
---@param target gameobject
---@return nil
function gameobject:cast_spell(slot, start_pos, end_pos, target) end

---@param slot number
---@param pos vec3
---@param release boolean
---@return nil
function gameobject:update_charged_spell(slot, pos, release) end

---@param item_id number
---@return boolean
function gameobject:has_item(item_id) end

---@param item_id number
---@return boolean
function gameobject:can_use_item(item_id) end

---@param item_id item
---@return boolean
function gameobject:get_item(item_id) end

---@param item_id number
---@return spellslot
function gameobject:get_item_slot(item_id) end

---@param slot number
---@return spellslot
function gameobject:get_spell_slot_by_id(slot) end

---@param slot number
---@return number
function gameobject:get_spell_state(slot) end

---@param slot number
---@return boolean
function gameobject:can_use_spell(slot) end

---@param hash number
---@return buff
function gameobject:get_buff(hash) end

---@param type number
---@return buff
function gameobject:get_buffs_by_type(type) end

---@param hash number
---@return number
function gameobject:get_buff_count(hash) end

---@param tolerance number
---@return boolean
function gameobject:is_visible_on_screen(tolerance) end

---@param hash number
---@return boolean
function gameobject:has_buff(hash) end

---@param type number
---@return boolean
function gameobject:has_buff_type(type) end

---@param pos vec3
---@return boolean
function gameobject:is_facing(pos) end

---@param obj gameobject
---@return boolean
function gameobject:is_facing_obj(obj) end

---@param pos vec3
---@return boolean
function gameobject:is_in_range(pos) end

---@param obj gameobject
---@return boolean
function gameobject:is_in_range_obj(obj) end

---@param obj gameobject
---@param extra_range number
---@return boolean
function gameobject:is_in_auto_attack_range(obj, extra_range) end

---@param range number
---@param from vec3
---@param ignore_invulnerability boolean
---@return boolean
function gameobject:is_valid_target(range, from, ignore_invulnerability) end

---@param slot number
---@return nil
function gameobject:cast_spell_self(slot) end

---@param slot number
---@param target gameobject
---@return nil
function gameobject:cast_spell_target(slot, target) end

---@param slot number
---@param start_pos vec3
---@param end_pos vec3
---@return nil
function gameobject:cast_spell_pos(slot, start_pos, end_pos) end

---@param start vec3
---@param dest vec3
---@param smooth boolean
---@return vec3[]
function gameobject:build_path(start, dest, smooth) end

---@type gameobject
_G.player = {}