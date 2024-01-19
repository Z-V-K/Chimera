#include "PermashowDebug.h"

#pragma region pathcontroller
std::string pathIsGhosting = "False";
std::string pathIsMoving = "False";
std::string pathSegments = "0";
std::string pathCurrentSegment = "0";
std::string pathLength = "0";
std::string pathServerPos = "0 | 0 | 0";
std::string pathNavStart = "0 | 0 | 0";
std::string pathNavEnd = "0 | 0 | 0";
#pragma endregion 

#pragma region lists
std::unordered_map<std::string, std::string> buff_list;
std::unordered_map<std::string, std::string> item_list;
std::unordered_map<std::string, std::pair<float, std::string>> particle_list;
#pragma endregion

#pragma region gameinfo
std::string playerPos;
std::string gameCursorPos;
std::string cursorPos;
std::string hoveredObject;
std::string gameTime;
std::string ping;
#pragma endregion

#pragma region process_spell
std::string spellName = "None";
std::string spellSlot = "None";
std::string spellIsAuto = "false";
std::string spellIsSpell = "false";
std::string spellGetStartPos = "0 | 0 | 0";
std::string spellGetEndPos = "0 | 0 | 0";
std::string spellGetTarget = "None";
std::string spellGetMissileSpeed = "0";
std::string spellHash = "None";
std::string spellTags = "None";
std::string baseDamage = "None";
std::string cooldownTime = "None";
std::string delayCastOffsetPct = "None";
std::string delayTotalTimePct = "None";
std::string turnSpeedScalar = "None";
std::string castRange = "None";
std::string castRangeDisplayOverride = "None";
std::string castRadius = "None";
std::string castConeDistance = "None";
std::string missileSpecMissileWidth = "None";
std::string castType = "None";
std::string castFrame = "None";
std::string mLineWidth = "None";

std::map<SlotId, std::string> spellSlotToString =
{
	{ SlotId::Q, "Q"},
	{ SlotId::E, "E"},
	{ SlotId::W, "W"},
	{ SlotId::R, "R"},
	{ SlotId::Auto1, "Auto1"},
	{ SlotId::Auto2, "Auto2"},
	{ SlotId::Item1, "Item1"},
	{ SlotId::Item2, "Item2"},
	{ SlotId::Item3, "Item3"},
	{ SlotId::Item4, "Item4"},
	{ SlotId::Item5, "Item5"},
	{ SlotId::Item6, "Item6"},
	{ SlotId::Item_Trinket, "Item_Trinket"},
	{ SlotId::Recall, "Recall"},
	{ SlotId::SpecialAttack, "SpecialAttack"},
	{ SlotId::Summoner1, "Summoner1"},
	{ SlotId::Summoner2, "Summoner2"},
	{ SlotId::Unknown, "Unknown"},
};
#pragma endregion

#pragma region localplayer_stats
std::string mana = "0";
std::string bonus_mana = "0";
std::string max_mana = "0";
std::string mana_regen = "0";
std::string hp = "";
std::string bonus_hp = "0";
std::string max_hp = "";
std::string health_regen = "0";
std::string ability_haste = "0";
std::string base_ad = "0";
std::string bonus_ad = "0";
std::string total_ap = "0";
std::string bonus_ap_mul = "0";
std::string shield = "";
std::string physical_shield = "0";
std::string magical_shield = "0";
std::string magic_pen_flat = "0";
std::string magic_pen_percentage = "0";
std::string lethality = "0";
std::string armor_pen_percentage = "0";
std::string atk_range = "0";
std::string atk_speed_mul = "0";
std::string attack_delay = "0";
std::string attack_cast_delay = "0";
std::string crit_dmg_mul = "0";
std::string crit_chance = "0";
std::string armor = "0";
std::string bonus_armor = "0";
std::string magic_resistance = "0";
std::string bonus_magic_resistance = "0";
std::string movement_speed = "0";
std::string current_gold = "0";
std::string level = "0";
std::string accumulated_xp = "0";
#pragma endregion

#pragma region localplayer_info
std::string index = "0x0";
std::string network_id = "0";
std::string team = "0";
std::string name = "";
std::string model_name = "0";
std::string visibility = "";
std::string is_invulnerable = "";
std::string is_targetable = "";
std::string recall_state = "";
std::string direction = "0";
std::string is_lane_minion = "0";
std::string is_pet = "0";
std::string is_ward = "0";
std::string effect_emitter = "0";
#pragma endregion

#pragma region missileclient
std::string missile_spell_data = "";
std::string missile_start_pos = "";
std::string missile_end_pos = "";
std::string missile_cast_pos = "";
std::string missile_slot_id = "";
std::string missile_index = "";
std::string missile_source = "";
std::string missile_target = "";
#pragma endregion

void PermashowDebug::init_permashows()
{
#pragma region permashow_setup
	ps_process_spell		= permashow_manager->add_permashow(Menu::process_spell, { 250, 100 });
	ps_game_info			= permashow_manager->add_permashow(Menu::game_info, { 500, 100 });
	ps_buff_manager			= permashow_manager->add_permashow(Menu::buff_manager, { 800, 100 });
	ps_path_controller		= permashow_manager->add_permashow(Menu::path_controller, { 1300, 100 });
	ps_local_player_stats	= permashow_manager->add_permashow(Menu::local_player_stats, { 1000, 100 });
	ps_local_player_info	= permashow_manager->add_permashow(Menu::local_player_info, { 1300, 100 });
	ps_item_list			= permashow_manager->add_permashow(Menu::item_list, { 1500, 100 });
	ps_particle_list		= permashow_manager->add_permashow(Menu::particle_list, { 500, 500 });
	ps_missile_client		= permashow_manager->add_permashow(Menu::missile_client, { 1200, 100 });
#pragma endregion

#pragma region ps_process_spell
	ps_process_spell->add_element("SpellName", &spellName);
	ps_process_spell->add_element("SpellSlot", &spellSlot);
	ps_process_spell->add_element("IsAuto", &spellIsAuto);
	ps_process_spell->add_element("IsSpell", &spellIsSpell);
	ps_process_spell->add_element("StartPos", &spellGetStartPos);
	ps_process_spell->add_element("EndPos", &spellGetEndPos);
	ps_process_spell->add_element("Target", &spellGetTarget);
	ps_process_spell->add_element("MissileSpeed", &spellGetMissileSpeed);
	ps_process_spell->add_element("spellHash", &spellHash);
	ps_process_spell->add_element("spellTags", &spellTags);
	ps_process_spell->add_element("baseDamage", &baseDamage);
	ps_process_spell->add_element("cooldownTime", &cooldownTime);
	ps_process_spell->add_element("delayCastOffsetPct", &delayCastOffsetPct);
	ps_process_spell->add_element("delayTotalTimePct", &delayTotalTimePct);
	ps_process_spell->add_element("turnSpeedScalar", &turnSpeedScalar);
	ps_process_spell->add_element("castRange", &castRange);
	ps_process_spell->add_element("castRangeDisplayOverride", &castRangeDisplayOverride);
	ps_process_spell->add_element("castRadius", &castRadius);
	ps_process_spell->add_element("castConeDistance", &castConeDistance);
	ps_process_spell->add_element("missileSpecMissileWidth", &missileSpecMissileWidth);
	ps_process_spell->add_element("castType", &castType);
	ps_process_spell->add_element("castFrame", &castFrame);
	ps_process_spell->add_element("mLineWidth", &mLineWidth);
#pragma endregion

#pragma region ps_game_info
	ps_game_info->add_element("Player pos", &playerPos);
	ps_game_info->add_element("Cursor pos", &cursorPos);
	ps_game_info->add_element("Game cursor pos", &gameCursorPos);
	ps_game_info->add_element("Hovered Object", &hoveredObject);
	ps_game_info->add_element("GameTime", &gameTime);
	ps_game_info->add_element("Ping", &ping);
#pragma endregion

#pragma region ps_path_controller
	ps_path_controller->add_element("IsGhosting", &pathIsGhosting);
	ps_path_controller->add_element("IsMoving", &pathIsMoving);
	ps_path_controller->add_element("Segments", &pathSegments);
	ps_path_controller->add_element("CurrentSegment", &pathCurrentSegment);
	ps_path_controller->add_element("Length", &pathLength);
	ps_path_controller->add_element("Server Pos", &pathServerPos);
	ps_path_controller->add_element("NavStart", &pathNavStart);
	ps_path_controller->add_element("NavEnd", &pathNavEnd);
#pragma endregion

#pragma region ps_localplayer_stats
	ps_local_player_stats->add_element("Mana", &mana);
	ps_local_player_stats->add_element("Bonus Mana", &bonus_mana);
	ps_local_player_stats->add_element("Max Mana", &max_mana);
	ps_local_player_stats->add_element("Mana Regen", &mana_regen);
	ps_local_player_stats->add_element("Health", &hp);
	ps_local_player_stats->add_element("Bonus Health", &bonus_hp);
	ps_local_player_stats->add_element("Max Health", &max_hp);
	ps_local_player_stats->add_element("Health Regen", &health_regen);
	ps_local_player_stats->add_element("Ability Haste", &ability_haste);
	ps_local_player_stats->add_element("Base AD", &base_ad);
	ps_local_player_stats->add_element("Bonus AD", &bonus_ad);
	ps_local_player_stats->add_element("Total AP", &total_ap);
	ps_local_player_stats->add_element("Bonus AP Mul", &bonus_ap_mul);
	ps_local_player_stats->add_element("Shield", &shield);
	ps_local_player_stats->add_element("Physical Shield", &physical_shield);
	ps_local_player_stats->add_element("Magical Shield", &magical_shield);
	ps_local_player_stats->add_element("Magic Pen Flat", &magic_pen_flat);
	ps_local_player_stats->add_element("Magic Pen %", &magic_pen_percentage);
	ps_local_player_stats->add_element("Lethality", &lethality);
	ps_local_player_stats->add_element("Armor Pen %", &armor_pen_percentage);
	ps_local_player_stats->add_element("Attack Range", &atk_range);
	ps_local_player_stats->add_element("Attack Speed Mul", &atk_speed_mul);
	ps_local_player_stats->add_element("Attack Delay", &attack_delay);
	ps_local_player_stats->add_element("Attack Cast Delay", &attack_cast_delay);
	ps_local_player_stats->add_element("Crit Damage Mul", &crit_dmg_mul);
	ps_local_player_stats->add_element("Crit Chance", &crit_chance);
	ps_local_player_stats->add_element("Armor", &armor);
	ps_local_player_stats->add_element("Bonus Armor", &bonus_armor);
	ps_local_player_stats->add_element("Magic Resistance", &magic_resistance);
	ps_local_player_stats->add_element("Bonus Magic Resistance", &bonus_magic_resistance);
	ps_local_player_stats->add_element("Movement Speed", &movement_speed);
	ps_local_player_stats->add_element("Current Gold", &current_gold);
	ps_local_player_stats->add_element("Level", &level);
	ps_local_player_stats->add_element("XP", &accumulated_xp);
#pragma endregion

#pragma region ps_localplayer_info
	ps_local_player_info->add_element("Index", &index);
	ps_local_player_info->add_element("Network ID", &network_id);
	ps_local_player_info->add_element("Team", &team);
	ps_local_player_info->add_element("Name", &name);
	ps_local_player_info->add_element("Model Name", &model_name);
	ps_local_player_info->add_element("Visibility", &visibility);
	ps_local_player_info->add_element("Invulnerable", &is_invulnerable);
	ps_local_player_info->add_element("Targetable", &is_targetable);
	ps_local_player_info->add_element("Recall State", &recall_state);
	ps_local_player_info->add_element("Direction", &direction);
	ps_local_player_info->add_element("Is Lane Minion", &is_lane_minion);
	ps_local_player_info->add_element("Is Pet", &is_pet);
	ps_local_player_info->add_element("Is Ward", &is_pet);
	ps_local_player_info->add_element("Is Effect Emitter", &effect_emitter);
#pragma endregion

#pragma region missile_client
	ps_missile_client->add_element("spell_data", &missile_spell_data);
	ps_missile_client->add_element("start_pos", &missile_start_pos);
	ps_missile_client->add_element("end_pos", &missile_end_pos);
	ps_missile_client->add_element("cast_pos", &missile_cast_pos);
	ps_missile_client->add_element("slot_id", &missile_slot_id);
	ps_missile_client->add_element("index", &missile_index);
	ps_missile_client->add_element("source", &missile_source);
	ps_missile_client->add_element("target", &missile_target);
#pragma endregion

#pragma region permashow_set
	ps_buff_manager->set_draw(Menu::buff_manager_enable);
	ps_process_spell->set_draw(Menu::process_spell_enable);
	ps_game_info->set_draw(Menu::game_info_enable);
	ps_path_controller->set_draw(Menu::path_controller_enable);
	ps_local_player_stats->set_draw(Menu::local_player_stats_enable);
	ps_local_player_info->set_draw(Menu::local_player_info_enable);
	ps_item_list->set_draw(Menu::item_list_enable);
	ps_particle_list->set_draw(Menu::particle_list_enable);
	ps_missile_client->set_draw(Menu::missile_client_enable);
#pragma endregion
}

void PermashowDebug::init_menu()
{
	Menu::main_menu = menu_manager->create_menu("Permashow", "Permashow", ICON_FA_DEBUG);

	Menu::process_spell = Menu::main_menu->add_menu("processspell", "Processed Spell");
	Menu::process_spell_enable = Menu::process_spell->add_checkbox("processSpellGroupBox", "ProcessSpell", false);
	Menu::process_spell->set_enabled(Menu::process_spell_enable);

	Menu::game_info = Menu::main_menu->add_menu("gameinfo", "Game Info");
	Menu::game_info_enable = Menu::game_info->add_checkbox("gameInfoGroupBox", "GameInfo", false);
	Menu::game_info->set_enabled(Menu::game_info_enable);

	Menu::path_controller = Menu::main_menu->add_menu("path_controller", "Path Controller");
	Menu::path_controller_enable = Menu::path_controller->add_checkbox("pathControllerGroupBox", "PathController", false);
	Menu::path_controller->set_enabled(Menu::path_controller_enable);

	Menu::buff_manager = Menu::main_menu->add_menu("buff_manager", "Buff Manager");
	Menu::buff_manager_enable = Menu::buff_manager->add_checkbox("buffManagerGroupBox", "BuffManager", false);
	Menu::buff_manager->set_enabled(Menu::buff_manager_enable);

	Menu::item_list = Menu::main_menu->add_menu("item_list", "Item List");
	Menu::item_list_enable = Menu::item_list->add_checkbox("item_list_enable", "ItemList", false);
	Menu::item_list->set_enabled(Menu::item_list_enable);

	Menu::local_player_stats = Menu::main_menu->add_menu("local_player_stats", "Local Player Stats");
	Menu::local_player_stats_enable = Menu::local_player_stats->add_checkbox("local_player_stats", "LocalPlayerStats", false);
	Menu::local_player_stats->set_enabled(Menu::local_player_stats_enable);

	Menu::local_player_info = Menu::main_menu->add_menu("local_player_info", "Local Player Info");
	Menu::local_player_info_enable = Menu::local_player_info->add_checkbox("local_player_info", "LocalPlayerInfo", false);
	Menu::local_player_info->set_enabled(Menu::local_player_info_enable);

	Menu::particle_list = Menu::main_menu->add_menu("paricle_list", "Particle List");
	Menu::particle_list_enable = Menu::particle_list->add_checkbox("particle_list_enable", "Particle List", false);
	Menu::particle_list->set_enabled(Menu::particle_list_enable);
	
	Menu::missile_client = Menu::main_menu->add_menu("missile_client", "Missile Client");
	Menu::missile_client_enable = Menu::missile_client->add_checkbox("missile_client", "MissileClient", false);
	Menu::missile_client->set_enabled(Menu::missile_client_enable);
}

void PermashowDebug::initialize()
{
	callbacks<EventType::OnProcessSpellCast>::add_callback(on_process_spell, "PermashowDebug");
	callbacks<EventType::OnTick>::add_callback(on_game_tick, "PermashowDebug");
	callbacks<EventType::OnCreateObject>::add_callback(on_create_object, "PermashowDebug");
	callbacks<EventType::OnDeleteObject>::add_callback(on_delete_object, "PermashowDebug");

	init_menu();
	init_permashows();
}

void PermashowDebug::on_process_spell(SpellCastInfo* spell)
{
	if (!Menu::process_spell_enable->get_bool() || !spell || !spell->get_source()->is_me())
		return;

	const auto sp = spell->get_start_pos();
	const auto ep = spell->get_end_pos();
	const auto st = spell->get_target();
	const auto sd = spell->get_spell_data();
	spellName = sd->get_spell_name();
	spellIsAuto = btos(spell->is_auto());
	spellIsSpell = btos(spell->is_spell());
	spellGetStartPos = precision_to_string(sp.x) + " | " + precision_to_string(sp.y) + " | " + precision_to_string(sp.z);
	spellGetEndPos = precision_to_string(ep.x) + " | " + precision_to_string(ep.y) + " | " + precision_to_string(ep.z);
	spellGetTarget = "None";
	if (st != nullptr) { spellGetTarget = st->get_name(); }
	spellGetMissileSpeed = std::to_string(sd->missileSpeed());
	spellSlot = std::to_string((int)spell->get_slot()) + " | " + spellSlotToString[spell->get_slot()];
	spellHash = std::format("{:#X}", sd->get_hash());
	spellTags = "";
	for (const auto& tag : sd->mSpellTags())
	{
		spellTags += tag + " | ";
	}
	baseDamage = "";
	for (const auto& dmg : sd->mDataValues_BaseDamage())
	{
		baseDamage += precision_to_string(dmg) + " | ";
	}
	cooldownTime = "";
	for (const auto& cd : sd->cooldown_time())
	{
		cooldownTime += precision_to_string(cd) + " | ";
	}
	delayCastOffsetPct = precision_to_string(sd->delayCastOffsetPercent());
	delayTotalTimePct = precision_to_string(sd->delayTotalTimePercent());
	turnSpeedScalar = precision_to_string(sd->mTurnSpeedScalar());
	castRange = "";
	for (const auto& range : sd->castRange())
	{
		castRange += precision_to_string(range) + " | ";
	}
	castRangeDisplayOverride = "";
	for (const auto& range : sd->castRangeDisplayOverride())
	{
		castRangeDisplayOverride += precision_to_string(range) + " | ";
	}
	castRadius = "";
	for (const auto& radius : sd->castRadius())
	{
		castRadius += precision_to_string(radius) + " | ";
	}
	castConeDistance = precision_to_string(sd->castConeDistance());
	missileSpecMissileWidth = precision_to_string(sd->mMissileSpec_mMissileWidth());
	castType = std::to_string(sd->castType());
	castFrame = precision_to_string(sd->castFrame());
	mLineWidth = precision_to_string(sd->mLineWidth());
}

void PermashowDebug::on_game_tick()
{
	if (Menu::buff_manager_enable->get_bool())
	{
		buff_list.clear();
		const auto& lp_buff_list = local_player->get_buffs();

		if (!lp_buff_list.empty())
		{
			for (const auto& buff : lp_buff_list)
			{
				buff_list.insert({
					buff->get_name(),
					std::string(std::format("TYPE: {} | STACKS: {} | {:#x}", (int)buff->get_type(), buff->get_count(), (uintptr_t)buff) + " | " + precision_to_string(buff->get_remaining_time())) + " | " + std::format("{:#x}", buff->get_hash())
					});
			}
		}

		ps_buff_manager->clear_elements();
		for (auto& item : buff_list)
		{
			ps_buff_manager->add_element(item.first, &item.second);
		}
	}

	if (Menu::particle_list_enable->get_bool())
	{
		for (const auto& particle : particle_list)
		{
			if (particle.second.first - game_time->get_time() < 0.0f)
				particle_list.erase(particle.first);
		}

		ps_particle_list->clear_elements();
		for (auto& particle : particle_list)
		{
			ps_particle_list->add_element(particle.first, &particle.second.second);
		}
	}

	if (Menu::path_controller_enable->get_bool())
	{
		const auto pc = local_player->get_path_controller_common();
		const auto sp = pc->get_server_pos();
		const auto ns = pc->get_nav_start();
		const auto ne = pc->get_nav_end();

		pathIsGhosting = btos(pc->is_dashing());
		pathIsMoving = btos(pc->is_moving());
		pathSegments = std::to_string(pc->get_nb_waypoints());
		pathCurrentSegment = std::to_string(pc->get_curr_segment());
		pathLength = precision_to_string(pc->get_path_length());
		pathServerPos = precision_to_string(sp.x) + " | " + precision_to_string(sp.y) + " | " + precision_to_string(sp.z);
		pathNavStart = precision_to_string(ns.x) + " | " + precision_to_string(ns.y) + " | " + precision_to_string(ns.z);
		pathNavEnd = precision_to_string(ne.x) + " | " + precision_to_string(ne.y) + " | " + precision_to_string(ne.z);
	}

	if (Menu::local_player_stats_enable->get_bool())
	{
		mana = std::to_string(static_cast<int>(local_player->get_mana()));
		bonus_mana = std::to_string(static_cast<int>(local_player->get_bonus_mana()));
		max_mana = std::to_string(static_cast<int>(local_player->get_max_mana()));
		mana_regen = precision_to_string(local_player->get_mana_regen());
		hp = std::to_string(static_cast<int>(local_player->get_health()));
		bonus_hp = std::to_string(static_cast<int>(local_player->get_bonus_health()));
		max_hp = std::to_string(static_cast<int>(local_player->get_max_health()));
		health_regen = precision_to_string(local_player->get_health_regen());
		ability_haste = std::to_string(static_cast<int>(local_player->get_ability_haste()));
		base_ad = std::to_string(static_cast<int>(local_player->get_base_ad()));
		bonus_ad = std::to_string(static_cast<int>(local_player->get_bonus_ad()));
		total_ap = std::to_string(static_cast<int>(local_player->get_ap()));
		bonus_ap_mul = precision_to_string(local_player->get_bonus_ap_multiplier());
		shield = std::to_string(static_cast<int>(local_player->get_shield()));
		physical_shield = std::to_string(static_cast<int>(local_player->get_shield())); //!
		magical_shield = std::to_string(static_cast<int>(local_player->get_magic_shield()));
		magic_pen_flat = std::to_string(static_cast<int>(local_player->get_magic_pen_flat()));
		magic_pen_percentage = precision_to_string(local_player->get_magic_pen_multiplier());
		lethality = std::to_string(static_cast<int>(local_player->get_lethality()));
		armor_pen_percentage = precision_to_string(local_player->get_armor_pen_multiplier());
		atk_range = std::to_string(static_cast<int>(local_player->get_attack_range()));
		atk_speed_mul = precision_to_string(local_player->get_attack_speed_multiplier());
		attack_delay = precision_to_string(local_player->get_attack_delay()) + " | " + std::to_string(local_player->get_attack_delay() * 1000);
		attack_cast_delay = precision_to_string(local_player->get_attack_cast_delay()) + " | " + std::to_string(local_player->get_attack_cast_delay() * 1000);
		crit_dmg_mul = precision_to_string(local_player->get_crit_damage_multiplier());
		crit_chance = precision_to_string(local_player->get_crit());
		armor = std::to_string(static_cast<int>(local_player->get_armor()));
		bonus_armor = std::to_string(static_cast<int>(local_player->get_bonus_armor()));
		magic_resistance = std::to_string(static_cast<int>(local_player->get_spell_block()));
		bonus_magic_resistance = std::to_string(static_cast<int>(local_player->get_bonus_spell_block()));
		movement_speed = std::to_string(static_cast<int>(local_player->get_movement_speed()));
		current_gold = std::to_string(static_cast<int>(local_player->get_current_gold()));
		level = std::to_string(local_player->get_level());
		accumulated_xp = std::to_string(static_cast<int>(local_player->get_accumulated_experience()));
	}

	if (Menu::local_player_info_enable->get_bool())
	{
		index				= std::format("0x{:X}", local_player->get_index());
		network_id			= std::format("0x{:X}", local_player->get_network_id());
		team				= std::to_string(static_cast<int>(local_player->get_team()));
		name				= local_player->get_name();
		model_name			= local_player->get_model_name();
		visibility			= btos(local_player->is_visible());
		is_invulnerable		= btos(local_player->is_invulnerable());
		is_targetable		= btos(local_player->is_targetable());
		recall_state		= btos(local_player->is_recalling());
		char buff[64];
		sprintf(buff, "%.2f | %.2f", local_player->get_direction().x, local_player->get_direction().z);
		direction			= buff;
		is_lane_minion		= btos(local_player->is_lane_minion());
		is_pet				= btos(local_player->is_pet());
		is_ward				= btos(local_player->is_ward());
		effect_emitter		= btos(local_player->is_effect_emitter());
	}

	if (Menu::game_info_enable->get_bool())
	{
		const auto& pp = local_player->get_position();
		const auto& cs = cursor->get_world_position();
		const auto& cs2 = input->get_cursor_screen_position();

		playerPos = precision_to_string(pp.x) + " | " + precision_to_string(pp.y) + " | " + precision_to_string(pp.z);
		cursorPos = precision_to_string(cs2.x) + " | " + precision_to_string(cs2.y);
		gameCursorPos = precision_to_string(cs.x) + " | " + precision_to_string(cs.y) + " | " + precision_to_string(cs.z);
		gameTime = precision_to_string(game_time->get_time());
		ping = precision_to_string(net_client->get_ping());

		hoveredObject = "None";
		if (cursor->get_hovered_unit() != nullptr)
		{
			hoveredObject = cursor->get_hovered_unit()->get_name();
		}
	}

	if (Menu::item_list_enable->get_bool())
	{
		item_list.clear();
		const auto& lp_item_list = local_player->get_items();

		for (int i = 0; i < lp_item_list.size(); ++i)
		{
			if (!lp_item_list[i]) continue;

			item_list.insert({
				std::to_string(i),
				std::to_string(static_cast<int>(lp_item_list[i]->get_item_id()))
				});
		}

		ps_item_list->clear_elements();
		for (auto& item : item_list)
		{
			ps_item_list->add_element(item.first, &item.second);
		}
	}
}

void PermashowDebug::on_create_object(GameObject* obj)
{
	if (obj->is_missile())
	{
		const auto missile_client = obj->get_missile_client();

		if (!missile_client)
			return;

		missile_spell_data = std::format("{:#X}", (uintptr_t)missile_client->get_spell_data());
		missile_start_pos = std::format("{} {} {}", precision_to_string(missile_client->get_start_position().x), precision_to_string(missile_client->get_start_position().y), precision_to_string(missile_client->get_start_position().z));
		missile_end_pos = std::format("{} {} {}", precision_to_string(missile_client->get_end_position().x), precision_to_string(missile_client->get_end_position().y), precision_to_string(missile_client->get_end_position().z));
		missile_cast_pos = std::format("{} {} {}", precision_to_string(missile_client->get_cast_position().x), precision_to_string(missile_client->get_cast_position().y), precision_to_string(missile_client->get_cast_position().z));
		missile_index = std::format("{:#X}", missile_client->get_missile_index());
		missile_slot_id = std::to_string((int)missile_client->get_slot()) + " | " + spellSlotToString[missile_client->get_slot()];

		const auto source = missile_client->get_source();
		const auto target = missile_client->get_target();
		missile_source = source ? source->get_name().c_str() : "None";
		missile_target = target ? target->get_name().c_str() : "None";
	}

	if (obj->is_effect_emitter())
	{
		if (particle_list.find(obj->get_name()) == particle_list.end())
		{
			const auto attachment = obj->get_attachment();
			const auto target_attachment = obj->get_target_attachment();
			const auto emitter = obj->get_emitter();
			const auto hash = obj->get_effect_hash();

			std::string obj_name = obj->get_name();
			std::string attachment_name = attachment ? attachment->get_name() : "None";
			std::string target_name = target_attachment ? target_attachment->get_name() : "None";
			std::string emitter_name = emitter ? emitter->get_name() : "None";

			particle_list.insert({
				obj->get_name(),
				{
					(game_time->get_time() + 10.0f),
					std::string(std::format("PARTICLE: {} | EMITTER: {} | ATTACHMENT: {} | TARGET ATTACHMENT: {} | EFFECTHASH: {:#x}",
					obj_name.c_str(),
					emitter_name.c_str(),
					attachment_name.c_str(),
					target_name.c_str(),
					hash))
				}
				});
		}
	}
}

void PermashowDebug::on_delete_object(GameObject* obj)
{

}

std::string PermashowDebug::btos(bool x)
{
	if (x) return "True";
	return "False";
}

std::string PermashowDebug::precision_to_string(float pVal) {
	char buff[125];
	sprintf(buff, "%.2f", pVal);
	return buff;
}