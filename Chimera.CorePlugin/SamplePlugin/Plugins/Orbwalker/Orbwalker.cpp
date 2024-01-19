#include "Orbwalker.h"

#include "TurretMissileManager.h"

float lastMoveAntiAFK = 0.f;

OrbwalkerMode active_mode = OrbwalkerMode::None;

int lastLocalAttackTick;
int lastServerAttackTick;
int autoAttackCounter;
int attackPauseTick;
int movePauseTick;
int allPauseTick;
int lastFakeClickTick;
int lastAutoAttackTick;
int lastMovementTick;

GameObject* force_target;
GameObject* waiting_for_target;

bool isAphelios = false;
bool isGraves = false;
bool isJhin = false;
bool isKalista = false;
bool isRengar = false;
bool isSett = false;

bool missileLaunched = false;
bool nextAttackIsPassive = false;
bool jaxInGame = false;
bool gangplankInGame = false;
bool tahmKenchInGame = false;
bool calcItemDamage = false;

bool reset_auto = false;

std::vector<CharacterHash> champions_blocked_by_windwall {
	CharacterHash::Annie,
	CharacterHash::TwistedFate,
	CharacterHash::Leblanc,
	CharacterHash::Urgot,
	CharacterHash::Vladimir,
	CharacterHash::Fiddlesticks,
	CharacterHash::Ryze,
	CharacterHash::Sivir,
	CharacterHash::Soraka,
	CharacterHash::Teemo,
	CharacterHash::Tristana,
	CharacterHash::MissFortune,
	CharacterHash::Ashe,
	CharacterHash::Morgana,
	CharacterHash::Zilean,
	CharacterHash::Twitch,
	CharacterHash::Karthus,
	CharacterHash::Anivia,
	CharacterHash::Sona,
	CharacterHash::Janna,
	CharacterHash::Corki,
	CharacterHash::Karma,
	CharacterHash::Veigar,
	CharacterHash::Swain,
	CharacterHash::Caitlyn,
	CharacterHash::Orianna,
	CharacterHash::Brand,
	CharacterHash::Vayne,
	CharacterHash::Cassiopeia,
	CharacterHash::Heimerdinger,
	CharacterHash::Ezreal,
	CharacterHash::Kennen,
	CharacterHash::KogMaw,
	CharacterHash::Lux,
	CharacterHash::Xerath,
	CharacterHash::Ahri,
	CharacterHash::Graves,
	CharacterHash::Varus,
	CharacterHash::Viktor,
	CharacterHash::Lulu,
	CharacterHash::Ziggs,
	CharacterHash::Draven,
	CharacterHash::Quinn,
	CharacterHash::Syndra,
	CharacterHash::AurelionSol,
	CharacterHash::Zoe,
	CharacterHash::Zyra,
	CharacterHash::Kaisa,
	CharacterHash::Taliyah,
	CharacterHash::Jhin,
	CharacterHash::Kindred,
	CharacterHash::Jinx,
	CharacterHash::Lucian,
	CharacterHash::Yuumi,
	CharacterHash::Thresh,
	CharacterHash::Kalista,
	CharacterHash::Xayah,
	CharacterHash::Aphelios,
	CharacterHash::Bard,
	CharacterHash::Ivern,
	CharacterHash::Nami,
	CharacterHash::Velkoz,
	CharacterHash::Lissandra,
	CharacterHash::Malzahar
};

bool Orbwalker::combo_mode()
{
	return active_mode == OrbwalkerMode::Combo;
}

bool Orbwalker::last_hit_mode()
{
	return active_mode == OrbwalkerMode::LastHit;
}

bool Orbwalker::lane_clear_mode()
{
	return active_mode == OrbwalkerMode::LaneClear;
}

bool Orbwalker::harass_mode()
{
	return active_mode == OrbwalkerMode::Harass;
}

bool Orbwalker::flee_mode()
{
	return active_mode == OrbwalkerMode::Flee;
}

OrbwalkerMode Orbwalker::orbwalker_mode()
{
	return active_mode;
}

void Orbwalker::on_process_spell(SpellCastInfo* processed_spell)
{
	const auto source = processed_spell->get_source();
	if (!source || !source->is_me())
		return;

	if (!processed_spell->is_auto())
		return;

	const auto target = processed_spell->get_target();

	if (!target)
		return;

	lastAutoAttackTick = game_time->get_tick_count() - net_client->get_ping() / 2;
	lastServerAttackTick = game_time->get_tick_count() - net_client->get_ping() / 2.f;
	missileLaunched = false;
	lastMovementTick = 0;
	++autoAttackCounter;
}

void Orbwalker::on_cast_complete(SpellCastInfo* processed_spell)
{
	if (processed_spell->get_source() != local_player)
		return;

	if (isSett && processed_spell->get_slot() == SlotId::Q)
		nextAttackIsPassive = false;

	on_cast_complete_delayed(processed_spell);
}

void Orbwalker::on_stop_cast(SpellCastInfo* spell, bool destroy_missile, bool animation_cancelled)
{
	if (spell->get_source() != local_player || !destroy_missile || !animation_cancelled)
		return;

	if (Menu::debug->get_bool())
		console->log("stop cast");

	reset_auto_attack_timer();
}

void Orbwalker::on_issue_order(IssueOrderType order, Vec3* position, GameObject* target, bool* process)
{
	lastMoveAntiAFK = game_time->get_time();
}

void Orbwalker::on_draw()
{
	if (!Menu::debug->get_bool())
		return;

	char buff[64];
	sprintf(buff, "can_attack: %i", can_attack());

	const Vec2 pos = local_player->get_position().to_screen();
	draw_manager->screen_text(pos, buff, can_attack() ? Color(255, 255, 255) : Color(220, 0, 0), 16);

	sprintf(buff, "can_move: %i", can_move());
	draw_manager->screen_text(pos + Vec2(0, 20), buff, can_move() ? Color(255, 255, 255) : Color(220, 0, 0), 16);
	sprintf(buff, Menu::hotkey_fast_lane_clear->get_bool() ? "FAST" : "LH");
	draw_manager->screen_text(pos + Vec2(0, 35), buff, last_hit_mode() ? Color(0, 255, 0) : Color(255, 0, 0), 16);

	if (const auto target = target_selector->get_target(local_player->get_attack_range(), DamageType::Physical))
		draw_manager->circle(target->get_position(), target->get_bounding_radius(), Color{ 255, 0, 0, 150 }, 2);

	for (const auto& c : entities->get_heroes())
	{
		Vec2 pos = renderer->world_to_screen(c->get_position());
		char buff[64];
		sprintf(buff, "0x%llX | 0x%X | 0x%X", c, c->get_index(), c->get_network_id());
		draw_manager->screen_text(pos + Vec2(0, 50), buff, Color{255, 255, 255}, 16);
	}

	for (const auto& minion : entities->get_minions())
	{
		if (!minion)
			continue;
		//if (!minion->is_alive() || minion->get_health() <= 0 || !minion->is_valid_target(FLT_MAX))
		//	continue;

		//if (!minion->is_lane_minion() || (minion->is_jungle_minion() && !Menu::lasthit_jungle->get_bool()))
		//	continue;
		char buff[64];

		Vec2 pos = renderer->world_to_screen(minion->get_position()) - Vec2{ 0, 30.f };
		
		//sprintf(buff, "0x%llX 0x%X ward: %i pet: %i H: 0x%X", minion, minion->get_index(), minion->is_ward(), minion->is_pet(), minion->get_character_hash());
		sprintf(buff, "%s 0x%llX 0x%X", minion->get_name().c_str(), minion, minion->get_index());
		draw_manager->screen_text(pos - Vec2(0, 30.f), buff, Color{255, 255, 255}, 14);

		/*sprintf(buff, "Alive: %i", minion->is_alive());
		draw_manager->screen_text(pos, buff, Color{ 255, 255, 255 }, 13);
		pos.y += 15.f;


		sprintf(buff, "health >= 0: %i", minion->get_health() >= 0.f);
		draw_manager->screen_text(pos, buff, Color{ 255, 255, 255 }, 13);
		pos.y += 15.f;*/

		bool can_lh = can_last_hit(minion, time_for_auto_to_reach_target(local_player, minion));

		sprintf(buff, "lasthit: %i | %.2f %.2f", can_lh, minion->get_health(), minion->get_mana());
		draw_manager->screen_text(pos, buff, can_lh ? Color{ 0, 220, 0 } : Color{ 255, 255, 255 }, 13);
		pos.y += 14.f;

		const auto predicted_hp = health_pred->get_health_prediction(minion, time_for_auto_to_reach_target(local_player, minion));
		const auto dmg = (double) dmg_lib->get_auto_attack_damage(local_player, minion);

		sprintf(buff, "HP: %.2f\np:%.2f\nd:%.2f", minion->get_health(), predicted_hp, dmg);
		draw_manager->screen_text(pos, buff, Color{ 255, 255, 255 }, 13);
		pos.y += 45.f;
	}

	const auto under_mouse = cursor->get_hovered_unit();

	if (under_mouse)
	{
		const auto dmg = dmg_lib->get_auto_attack_damage(local_player, under_mouse);
		const auto predicted_hp = health_pred->get_health_prediction(under_mouse, time_for_auto_to_reach_target(local_player, under_mouse));
		char buff[64];
		sprintf(buff, "%.2f | %.2f", predicted_hp, (double) dmg);
		draw_manager->text(under_mouse->get_position() + Vec3(100, 50, 0), buff, Color{ 255, 0, 255 }, 16);
	}
}

void Orbwalker::on_cast_complete_delayed(SpellCastInfo* processed_spell)
{
	if (processed_spell->get_spell_data() && processed_spell->get_spell_data()->is_auto_reset())
	{
		reset_auto_attack_timer();
	}

	if (!processed_spell->is_auto())
		return;

	cb_manager->fire_on_after_attack(processed_spell->get_target());
	missileLaunched = true;
}

bool is_casting()
{
	const auto spell = local_player->get_active_spell();
	return (spell && spell->is_spell()) || local_player->is_winding_up();
}

void anti_afk()
{
	local_player->move_to(local_player->get_position());
}

void Orbwalker::on_game_update()
{
	if (Menu::glow_player->get_bool() && !glow->is_glowing(local_player))
		make_player_glow();

	//if (game_time->get_time() - lastMoveAntiAFK > 15)
	//	anti_afk();

	active_mode = get_mode();

	if (!local_player->is_alive() || active_mode == OrbwalkerMode::None)
		return;

	orbwalk(get_target(), cursor->get_world_position());
}

void Orbwalker::orbwalk(GameObject* target, const Vec3& pos)
{
	if (can_attack() && attack(target))
		return;

	const bool _can_move = can_move((float)Menu::windup_delay->get_int());

	if (!_can_move)
		return;

	if (Menu::combo_without_move->get_bool())
		return;

	if (Menu::limit_attack->get_bool()
		&& (double)local_player->get_attack_delay() < 0.38461539149284363
		&& autoAttackCounter % 3 != 0
		&& !can_move(500.f))
		return;

	move(pos.is_valid() ? pos : cursor->get_world_position());
}

bool Orbwalker::can_move()
{
	return can_move(0.f);
}

bool Orbwalker::can_move(float extra_windup)
{
	if (is_casting() 
		|| (tahmKenchInGame && local_player->has_buff(0x07507a1e)))
		return false;

	if (isKalista)
		return true;

	int num = 0;
	if (isRengar && (local_player->has_buff(0x4e2e6243) || local_player->has_buff(0x162c88e7)))
		num = 200;

	if (lastLocalAttackTick > lastServerAttackTick)
	{
		return game_time->get_tick_count() >= lastLocalAttackTick + local_player->get_attack_cast_delay() * 1000.f + 1.f / 30.f * 1000.f + num;
	}

	return game_time->get_tick_count() + net_client->get_ping() / 2.f + 1000.f / 30000.f >= lastServerAttackTick + local_player->get_attack_cast_delay() * 1000.f + extra_windup + num;
}

bool Orbwalker::can_attack()
{
	return can_attack(0.f);
}

bool Orbwalker::can_attack(float extra_windup)
{
	if (is_casting() 
		|| (tahmKenchInGame && local_player->has_buff(0x07507a1e)) // tahmkenchwhasdevouredtarget
		|| local_player->has_buff_type(BuffType::Fear) 
		|| local_player->has_buff_type(BuffType::Polymorph) 
		|| local_player->has_buff(0xdf1e9ff3) // polymorph
		|| (!isKalista && local_player->has_buff_type(BuffType::Blind)))
		return false;

	if (isRengar && (local_player->has_buff(0x4e2e6243) || local_player->has_buff(0x162c88e7))) // rengarq / rengarqemp
		return true;

	if ((isAphelios && local_player->has_buff(0xdf4239bf)) || (isJhin && local_player->has_buff(0x78a61078))) // apheliospreload / jhinpassivereload
		return false;

	if (reset_auto && !local_player->get_path_controller_common()->is_dashing())
	{
		reset_auto = false;
		return true;
	}

	int num = (int) (local_player->get_attack_delay() * 1000);
	if (isGraves)
	{
		if (!local_player->has_buff(0xc929c428)) // gravesbasicattackammo1
			return false;
		num = (int)((double)local_player->get_attack_delay() * 1000.0 * 1.0740296840667725 - 716.23809814453125);
	}
	else if (isSett && nextAttackIsPassive)
		num = (int)((double)local_player->get_attack_delay() * 1000.0 / 8.0);


	if (lastLocalAttackTick > lastServerAttackTick)
	{
		return game_time->get_tick_count() >= lastLocalAttackTick + 25 + num;
	}

	return game_time->get_tick_count() + net_client->get_ping() / 2 + 25 >= lastServerAttackTick + num;
}

bool Orbwalker::can_attack_with_windwall(GameObject* target)
{
	if (!target)
		return false;

	if (jaxInGame)
	{
		if (target->is_alive() && target->get_character_hash() == CharacterHash::Jax && target->has_buff(0x4f95e352))
			return false;
	}

	/*
	if (!Menu::yasuo_wall_check->get_bool())
		return true;

	if (((IEnumerable<string>) this.WindWallBrokenChampions).Any<string>((Func<string, bool>) (x = > string.Equals(GameObjects.Player.CharacterName, x, StringComparison.CurrentCultureIgnoreCase))) && Collisions.HasYasuoWindWallCollision(GameObjects.Player.ServerPosition, target.Position))
		return false;
	if (((IEnumerable<string>) this.SpecialWindWallChampions).Any<string>((Func<string, bool>) (x = > string.Equals(GameObjects.Player.CharacterName, x, StringComparison.CurrentCultureIgnoreCase))))
	{
		if (GameObjects.Player.CharacterName == "Elise")
		{
			if (string.Equals(GameObjects.Player.Spellbook.GetSpell(SpellSlot.R).Name, "eliser", StringComparison.CurrentCultureIgnoreCase) && Collisions.HasYasuoWindWallCollision(GameObjects.Player.ServerPosition, target.Position))
				return false;
		}
		else if (GameObjects.Player.CharacterName == "Nidalee")
		{
			if (string.Equals(GameObjects.Player.Spellbook.GetSpell(SpellSlot.Q).Name, "javelintoss", StringComparison.CurrentCultureIgnoreCase) && Collisions.HasYasuoWindWallCollision(GameObjects.Player.ServerPosition, target.Position))
				return false;
		}
		else if (GameObjects.Player.CharacterName == "Jayce")
		{
			if (string.Equals(GameObjects.Player.Spellbook.GetSpell(SpellSlot.Q).Name, "jayceshockblast", StringComparison.CurrentCultureIgnoreCase) && Collisions.HasYasuoWindWallCollision(GameObjects.Player.ServerPosition, target.Position))
				return false;
		}
		else if (GameObjects.Player.CharacterName == "Gnar")
		{
			if (string.Equals(GameObjects.Player.Spellbook.GetSpell(SpellSlot.Q).Name, "gnarq", StringComparison.CurrentCultureIgnoreCase) && Collisions.HasYasuoWindWallCollision(GameObjects.Player.ServerPosition, target.Position))
				return false;
		}
		else if (GameObjects.Player.CharacterName == "Azir" && GameObjects.AzirSoldiers.All<EffectEmitter>((Func<EffectEmitter, bool>) (x = > (GameObject)x != (GameObject)null && x.IsValid && (double)x.Distance(target.Position) > 350.0)))
		{
			if (Collisions.HasYasuoWindWallCollision(GameObjects.Player.ServerPosition, target.Position))
				return false;
		}
		else if (GameObjects.Player.CharacterName == "Neeko" && Collisions.HasYasuoWindWallCollision(GameObjects.Player.ServerPosition, target.Position))
			return false;
	}*/
	return true;
}

float Orbwalker::get_attack_cast_delay()
{
	return isSett && nextAttackIsPassive ? local_player->get_attack_delay() - local_player->get_attack_cast_delay() / 8.f : local_player->get_attack_cast_delay();
}

bool Orbwalker::attack(GameObject* target)
{
	if (!target)
		return false;

	if (Menu::debug->get_bool())
		console->log("trying to attack: %s %i %i %i %i", target->get_name().c_str(), target != nullptr, is_casting(), local_player->is_in_auto_attack_range(target), can_attack_with_windwall(target));

	if (!target
		|| is_casting()
		|| !local_player->is_in_auto_attack_range(target)
		|| !can_attack_with_windwall(target) 
		|| !cb_manager->fire_on_before_attack(target)
		)
		return false;

	if (isKalista)
		missileLaunched = false;

	if (Menu::debug->get_bool())
		console->dbg("atk %s", target->get_name().c_str());

	local_player->attack(target);
	lastLocalAttackTick = game_time->get_tick_count();
	return true;
}

void Orbwalker::move(const Vec3& pos)
{
	Vec3 vector3 = pos;
	if (!vector3.is_valid())
		return;
	const float x = std::max(30.f, (float) Menu::hold_radius->get_int());
	if (vector3.distance_squared(local_player->get_position()) < std::pow((float) x, 2.f))
	{
		if (local_player->get_path_controller_common()->get_path_length() == 0.f)
			return;

		lastMovementTick = game_time->get_tick_count() - 70;
	}
	else
	{
		float num1 = 0.0f;
		const auto waypoints = local_player->get_path_controller_common()->get_path();
		if (waypoints.size() > 1 && local_player->get_path_controller_common()->get_path_length() > 100.f)
		{
			const auto path = local_player->build_navigation_path(local_player->get_position(), pos);
			if (path.size() > 1)
			{
				num1 = (waypoints[1] - waypoints[0]).angle_between(path[1] - path[0]);
				float num2 = path.back().distance_squared(waypoints.back());
				if (((double)num1 < 10.0 && (double)num2 < std::pow(500.0, 2.0)) || (double)num2 < std::pow(50.0, 2.0))
					return;
			}
		}
		if ((game_time->get_tick_count() - lastMovementTick < 70 + std::min(60, net_client->get_ping()) && (double)num1 < 60.0)
		|| ((double)num1 >= 60.0 && game_time->get_tick_count() - lastMovementTick < 60))
			return;

		if (!cb_manager->fire_on_before_move(&vector3))
			return;

		local_player->move_to(vector3);

		lastMovementTick = game_time->get_tick_count();
	}
}

bool Orbwalker::can_last_hit(GameObject* minion, int delay)
{
	const auto predicted_hp = health_pred->get_health_prediction(minion, delay);
	const auto dmg = dmg_lib->get_auto_attack_damage(local_player, minion);

	return predicted_hp > 0 && (predicted_hp <= dmg || minion->get_health() <= dmg);
}

bool Orbwalker::should_prepare_for_turret(GameObject* minion)
{
	if (!minion->is_under_ally_turret())
		return false;

	const auto dmg = dmg_lib->get_auto_attack_damage(local_player, minion);

	if (TurretMissileManager::is_attack_valid() && TurretMissileManager::get_target() == minion)
	{
		if (health_pred->has_minion_aggro(minion))
		{
			const auto health_when_missile_hits = 
				health_pred->get_health_prediction(minion, TurretMissileManager::get_predicted_land_time() - game_time->get_tick_count());

			if (dmg + TurretMissileManager::get_damage() < health_when_missile_hits
				&& dmg * 2 + TurretMissileManager::get_damage() > health_when_missile_hits)
			{
				return true;
			}
		}
		else
		{
			console->log("%.2f", TurretMissileManager::get_damage());

			if (dmg + TurretMissileManager::get_damage() < minion->get_health()
				&& dmg * 2 + TurretMissileManager::get_damage() > minion->get_health())
			{
				return true;
			}
		}
	}
	else
	{
		bool better_option = false;
		for (const auto& m : entities->get_minions()) {
			if (!m || !m->is_enemy() || !m->is_valid_target(FLT_MAX))
				continue;

			if (m->is_ranged() && m->get_max_health() < minion->get_max_health())
			{
				better_option = true;
				break;
			}
		}

		if (!health_pred->has_minion_aggro(minion) && (minion->is_melee() || better_option))
		{
			const auto turret_dmg = dmg_lib->get_auto_attack_damage(TurretMissileManager::get_closest_turret(), minion);
			if (dmg + turret_dmg < minion->get_health()
				&& dmg * 2 + turret_dmg > minion->get_health())
			{
				return true;
			}
		}
	}

	return false;
}

int Orbwalker::time_for_auto_to_reach_target(GameObject* source, GameObject* target)
{
	if (!target)
		return 0;

	if (!source)
		source = local_player;

	const int animation_time = (int) (source->get_attack_cast_delay() * 1000) + net_client->get_ping();

	if (source->is_melee()) 
		return animation_time;

	const float dist = source->get_distance(target) - target->get_bounding_radius() / 2;
	const float missile_speed = source->get_basic_attack()->missileSpeed();

	const auto travel_time = 1000.f * (dist / missile_speed);

	return animation_time + (int) travel_time;
}

void Orbwalker::reset_auto_attack_timer(int delay)
{
	allPauseTick = 0;
	attackPauseTick = 0;
	lastAutoAttackTick = 0;
	movePauseTick = 0;

	reset_auto = true;
}

bool Orbwalker::is_priority_minion(GameObject* minion)
{
	if (!minion)
		return false;

	return minion->is_siege_minion() || minion->is_super_minion();
}

GameObject* Orbwalker::should_wait_laneclear(const std::vector<GameObject*>& minions)
{
	for (const auto& minion : minions)
	{
		if (!minion || !minion->is_enemy() || !minion->is_alive() || !minion->is_valid_target(local_player->get_attack_range()))
			continue;

		if (health_pred->has_minion_aggro(minion) && (can_last_hit(minion, time_for_auto_to_reach_target(local_player, minion) * 2)
			|| (!Menu::hotkey_fast_lane_clear->get_bool() && minion->get_health() < dmg_lib->get_auto_attack_damage(local_player, minion) * 3.f)))
			return minion;
	}

	return nullptr;
}

GameObject* Orbwalker::should_wait_lasthit(const std::vector<GameObject*>& minions)
{
	for (const auto& minion : minions)
	{
		if (!minion || !minion->is_alive() || !minion->is_valid_target(local_player->get_attack_range()) || !is_priority_minion(minion))
			continue;

		if (health_pred->has_minion_aggro(minion) && can_last_hit(minion, time_for_auto_to_reach_target(local_player, minion) * 2))
			return minion;
	}

	return nullptr;
}

OrbwalkerMode Orbwalker::get_mode()
{
	if (Menu::hotkey_combo->get_bool())
		return OrbwalkerMode::Combo;
	if (Menu::hotkey_harass->get_bool())
		return OrbwalkerMode::Harass;
	if (Menu::hotkey_lane_clear->get_bool())
		return OrbwalkerMode::LaneClear;
	if (Menu::hotkey_last_hit->get_bool())
		return OrbwalkerMode::LastHit;
	if (Menu::hotkey_flee->get_bool())
		return OrbwalkerMode::Flee;

	return OrbwalkerMode::None;
}

GameObject* Orbwalker::get_target()
{
	switch (active_mode)
	{
	case OrbwalkerMode::Combo:
		return get_target_combo();
	case OrbwalkerMode::Harass:
		return get_target_harass();
	case OrbwalkerMode::LaneClear:
		return get_target_laneclear();
	case OrbwalkerMode::LastHit:
		return get_target_lasthit();
	default:
		return nullptr;
	}
}

GameObject* Orbwalker::get_target_combo()
{
	return target_selector->get_target(local_player->get_attack_range(), DamageType::Mixed);
}

GameObject* Orbwalker::get_target_harass()
{
	if (Menu::harass_focus_mode->get_int() == 1)
	{
		if (GameObject* ret = get_target_lasthit())
			return ret;
	}

	if (local_player->is_under_enemy_turret() && !Menu::harass_under_turret->get_bool())
		return nullptr;

	if (GameObject* target = target_selector->get_target(local_player->get_attack_range(), DamageType::Mixed))
		return target;

	if (Menu::harass_focus_mode->get_int() == 0)
	{
		if (GameObject* ret = get_target_lasthit())
			return ret;
	}

	return nullptr;
}

GameObject* Orbwalker::get_target_laneclear()
{
	if (waiting_for_target && waiting_for_target->is_valid_target(local_player->get_attack_range()) && health_pred->has_minion_aggro(waiting_for_target))
	{
		if (can_last_hit(waiting_for_target, time_for_auto_to_reach_target(local_player, waiting_for_target)))
		{
			waiting_for_target = nullptr;
			return waiting_for_target;
		}

		return nullptr;
	}

	if (const auto target = get_target_lasthit())
		return target;

	auto turret_targets = entities->get_enemy_turrets();
	auto jungle_targets = entities->get_minions();
	auto minion_targets = entities->get_minions();

	std::erase_if(turret_targets, [](GameObject* a) { return !a || a->is_ally() || !a->is_valid_target(local_player->get_attack_range()); });
	std::erase_if(jungle_targets, [](GameObject* a) { return !a || a->is_ally() || a->is_plant() || !a->is_valid_target(local_player->get_attack_range()); });
	std::erase_if(minion_targets, [](GameObject* a) { return !a || a->is_ally() || a->is_plant() || !a->is_valid_target(local_player->get_attack_range()); });
	std::sort(turret_targets.begin(), turret_targets.end(), [](GameObject* a, GameObject* b) { return a->get_distance(local_player) < b->get_distance(local_player); });
	std::sort(jungle_targets.begin(), jungle_targets.end(), [](GameObject* a, GameObject* b) { return a->get_max_health() > b->get_max_health(); });
	std::sort(minion_targets.begin(), minion_targets.end(), [](GameObject* a, GameObject* b) { return a->get_max_health() > b->get_max_health(); });

	if (!turret_targets.empty())
		return turret_targets.front();

	if (!jungle_targets.empty())
		return jungle_targets.front();

	if (const auto target = should_wait_laneclear(minion_targets))
	{
		waiting_for_target = target;
		return nullptr;
	}

	if (!minion_targets.empty())
		return minion_targets.front();

	return nullptr;
}

GameObject* Orbwalker::get_target_lasthit()
{
	auto minions = entities->get_minions();
	std::sort(minions.begin(), minions.end(), [](GameObject* a, GameObject* b) { return a->get_max_health() > b->get_max_health(); });

	bool has_priority_minion = false;
	GameObject* ret = nullptr;

	for (const auto& minion : minions)
	{
		if (!minion || !minion->is_enemy() || !minion->is_valid_target(local_player->get_attack_range()) || minion->is_plant())
			continue;

		if ((gangplankInGame && (minion->get_character_hash() == CharacterHash::Barrel && !Menu::lasthit_barrels->get_bool()))
			|| (minion->is_neutral() && !Menu::lasthit_jungle))
			continue;

		if (is_priority_minion(minion))
			has_priority_minion = true;

		if (can_last_hit(minion, time_for_auto_to_reach_target(local_player, minion)) || should_prepare_for_turret(minion))
		{
			//if (Menu::debug->get_bool())
			//	console->log("CAN LAST HIT!");

			ret = minion;
		}
	}

	if (has_priority_minion && !is_priority_minion(ret) && should_wait_lasthit(minions))
		return nullptr;

	return ret;
}

int t = 0;
void on_createobj(GameObject* obj)
{
	//if (obj->is_missile() && obj->get_missile_client()->get_source() == local_player)
	//	MessageBoxA(nullptr, std::format("{:#x}", (uintptr_t) obj->get_missile_client()).c_str(), "", MB_OK);
	//if (obj->is_missile() && obj->get_missile_client()->get_source() == local_player)
	//	t = game_time->get_tick_count() - local_player->get_attack_cast_delay() * 1000;
}

void on_delete(GameObject* obj)
{
	//if (obj->is_missile() && obj->get_missile_client()->get_source() == local_player)
	//{
	//	console->log("%i", game_time->get_tick_count() - t);
	//	t = 0;
	//}
}

void Orbwalker::initialize()
{
	Menu::main_menu = menu_manager->create_menu("menuOrbwalker", "Orbwalker", ICON_FA_BOW_ARROW);

	Menu::debug = Menu::main_menu->add_checkbox("debug", "Debug", false);

	Menu::hotkeys = Menu::main_menu->add_menu("groupOrbHotkeys", "Hotkeys", ICON_FA_KEYBOARD);
	Menu::visuals = Menu::main_menu->add_menu("groupOrbVisuals", "Visuals", ICON_FA_EYE);
	Menu::settings = Menu::main_menu->add_menu("groupOrbSettings", "Settings", ICON_FA_COGS);
	
	Menu::hotkey_combo = Menu::hotkeys->add_keybind("entryHotkeysCombo", "Combo Mode", true, VK_SPACE, false);
	Menu::combo_without_move = Menu::hotkeys->add_keybind("combo_without_move", "Combo without moving", true, 'N', false);
	Menu::hotkey_flee = Menu::hotkeys->add_keybind("entryHotkeysFlee", "Flee Mode", true, 'Z', false);
	Menu::hotkey_lane_clear = Menu::hotkeys->add_keybind("entryHotkeysLaneClear", "Lane Clear Mode", true, 'V', false);
	Menu::hotkey_fast_lane_clear = Menu::hotkeys->add_keybind("entryHotkeysFastLaneClear", "Fast lane clear", true, VK_LBUTTON, false);
	Menu::hotkey_last_hit = Menu::hotkeys->add_keybind("entryHotkeysLastHit", "Last Hit Mode", true, 'X', false);
	Menu::hotkey_harass = Menu::hotkeys->add_keybind("entryHotkeysMixed", "Harass Mode", true, 'C', false);

	Menu::glow_player = Menu::visuals->add_checkbox("glow_player", "Glow player", true);
	Menu::glow_player_color = Menu::visuals->add_colorpick("glow_player_color", "^- Color", Color(255, 255, 255));

	Menu::glow_player->set_on_value_change([](MenuItem* cb)
	{
		if (cb->get_bool() && !glow->is_glowing(local_player))
		{
			make_player_glow();
		}
		else if (!cb->get_bool() && glow->is_glowing(local_player))
		{
			glow->remove_object(local_player);
		}
	});

	Menu::glow_player_color->set_on_value_change([](MenuItem* cp)
	{
		if (Menu::glow_player->get_bool())
		{
			glow->remove_object(local_player);
			make_player_glow();
		}
	});
	
	Menu::limit_attack = Menu::settings->add_checkbox("limit_attack", "Limit if attack speed > 2.5", false);
	Menu::hold_radius = Menu::settings->add_slider("hold_radius", "Hold radius", 50, 0, 250);
	Menu::lasthit_barrels = Menu::settings->add_checkbox("lasthit_barrels", "Last hit barrels", true);
	Menu::lasthit_jungle = Menu::settings->add_checkbox("lasthit_jungle", "Last hit jungle", true);
	Menu::harass_under_turret = Menu::settings->add_checkbox("harass_under_turret", "Harass under turret", true);
	Menu::harass_focus_mode = Menu::settings->add_combo("harass_focus_mode", "Harass mode", 0, { "Focus farm", "Focus heroes" });

	Menu::delays = Menu::settings->add_menu("delays", "Delays", ICON_FA_CLOCK);
	Menu::windup_delay = Menu::delays->add_slider("windup_delay", "Windup delay", 60, 0, 250);

	Menu::advanced = Menu::settings->add_menu("advanced", "Advanced");
	Menu::missile_check = Menu::advanced->add_checkbox("missile_check", "Missile check", true);	
	//Menu::yasuo_wall_check = Menu::advanced->add_checkbox("yasuowall_check", "Yasuo wall check", true);	

	callbacks<EventType::OnTick>::add_callback(on_game_update, "Orbwalker");
	callbacks<EventType::OnDraw>::add_callback(on_draw, "Orbwalker");
	callbacks<EventType::OnProcessSpellCast>::add_callback(on_process_spell, "Orbwalker");
	callbacks<EventType::OnCastComplete>::add_callback(on_cast_complete, "Orbwalker");
	callbacks<EventType::OnIssueOrder>::add_callback(on_issue_order, "Orbwalker");
	callbacks<EventType::OnStopCast>::add_callback(on_stop_cast, "Orbwalker");

	callbacks<EventType::OnCreateObject>::add_callback(on_createobj, "Orbwalker");
	callbacks<EventType::OnDeleteObject>::add_callback(on_delete, "Orbwalker");

	orbwalker->set_callbacks(
		&get_mode
	);

	TurretMissileManager::initialize();

	const auto character_hash = local_player->get_character_hash();
	if (character_hash == CharacterHash::Aphelios)
		isAphelios = true;
	if (character_hash == CharacterHash::Graves)
		isGraves = true;
	if (character_hash == CharacterHash::Jhin)
		isJhin = true;
	if (character_hash == CharacterHash::Kalista)
		isKalista = true;
	if (character_hash == CharacterHash::Rengar)
		isRengar = true;
	if (character_hash == CharacterHash::Sett)
		isSett = true;

	for (const auto& enemy : entities->get_heroes())
	{
		if (!enemy || !enemy->is_enemy())
			continue; 

		const auto char_hash = enemy->get_character_hash();

		if (char_hash == CharacterHash::Jax)
			jaxInGame = true;

		if (char_hash == CharacterHash::Gangplank)
			gangplankInGame = true;

		if (char_hash == CharacterHash::TahmKench)
			tahmKenchInGame = true;
	}
}

void Orbwalker::make_player_glow()
{
	glow->register_object(local_player, Color(0, 0, 0), 5, 5);
	glow->register_object(local_player, Menu::glow_player_color->get_color(), 2, 1);
}

void Orbwalker::on_unload()
{
	glow->remove_object(local_player);
}