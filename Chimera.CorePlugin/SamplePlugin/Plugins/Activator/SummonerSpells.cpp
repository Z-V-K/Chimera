#include "SummonerSpells.h"
#include "Activator.h"

namespace Activator
{
	struct SummonerSpell
	{
		Spell* spell = nullptr;

		bool is_heal = false;
		bool is_barrier = false;
		bool is_exhaust = false;
		bool is_cleanse = false;
		bool is_ignite = false;
	};

	SummonerSpell summoner_1{ };
	SummonerSpell summoner_2{ };

	SummonerSpell* get_heal() { return summoner_1.is_heal ? &summoner_1 : summoner_2.is_heal ? &summoner_2 : nullptr; }
	SummonerSpell* get_barrier() { return summoner_1.is_barrier ? &summoner_1 : summoner_2.is_barrier ? &summoner_2 : nullptr; }
	SummonerSpell* get_exhaust() { return summoner_1.is_exhaust ? &summoner_1 : summoner_2.is_exhaust ? &summoner_2 : nullptr; }
	SummonerSpell* get_cleanse() { return summoner_1.is_cleanse ? &summoner_1 : summoner_2.is_cleanse ? &summoner_2 : nullptr; }
	SummonerSpell* get_ignite() { return summoner_1.is_ignite ? &summoner_1 : summoner_2.is_ignite ? &summoner_2 : nullptr; }
	
	void init_summoner(const uint32_t hash, SummonerSpell& summoner_spell, SlotId slot_id)
	{
		switch (hash)
		{
		case spell_hash("summonerboost"):
			summoner_spell.spell = sdk->register_spell(slot_id, 0.f);
			summoner_spell.is_cleanse = true;
			return;
		case spell_hash("summonerexhaust"):
			summoner_spell.spell = sdk->register_spell(slot_id, 650.f);
			summoner_spell.is_exhaust = true;
			return;
		case spell_hash("summonerheal"):
			summoner_spell.spell = sdk->register_spell(slot_id, 0.f);
			summoner_spell.is_heal = true;
			return;
		case spell_hash("summonerdot"):
			summoner_spell.spell = sdk->register_spell(slot_id, 600.f);
			summoner_spell.is_ignite = true;
			return;
		case spell_hash("summonerbarrier"):
			summoner_spell.spell = sdk->register_spell(slot_id, 0.f);
			summoner_spell.is_barrier = true;
			return;
		default:
			return;
		}
	}

	void SummonerSpells::initialize()
	{
		Menu::summoner_spells = Menu::main_menu->add_menu("summoner_spells", "Summoner spells", ICON_FA_WAND_MAGIC);
		enable = Menu::summoner_spells->add_checkbox("enable", "Enable", true);
		Menu::summoner_spells->set_enabled(enable);

		const auto summ1_hash = local_player->get_spell(SlotId::Summoner1)->get_spell_data()->get_hash();
		const auto summ2_hash = local_player->get_spell(SlotId::Summoner2)->get_spell_data()->get_hash();

		init_summoner(summ1_hash, summoner_1, SlotId::Summoner1);
		init_summoner(summ2_hash, summoner_2, SlotId::Summoner2);

		if (summoner_1.is_cleanse || summoner_2.is_cleanse)
		{
			cleanse_tab = Menu::summoner_spells->add_menu("summ_cleanse", "Cleanse");
			cleanse_tab->set_texture(summoner_1.is_cleanse ? summoner_1.spell->texture() : summoner_2.spell->texture());
			cleanse_enable = cleanse_tab->add_checkbox("enable", "Enable", true);
			cleanse_tab->set_enabled(cleanse_enable);

			cleanse_stun = cleanse_tab->add_checkbox("cleanse_stun", "Stun", true);
			cleanse_taunt = cleanse_tab->add_checkbox("cleanse_taunt", "Taunt", true);
			cleanse_berserk = cleanse_tab->add_checkbox("cleanse_berserk", "Berserk", true);
			cleanse_polymorph = cleanse_tab->add_checkbox("cleanse_polymorph", "Polymorph", true);
			cleanse_snare = cleanse_tab->add_checkbox("cleanse_snare", "Snare", true);
			cleanse_fear = cleanse_tab->add_checkbox("cleanse_fear", "Fear", true);
			cleanse_charm = cleanse_tab->add_checkbox("cleanse_charm", "Charm", true);
			cleanse_blind = cleanse_tab->add_checkbox("cleanse_blind", "Blind", true);
			cleanse_asleep = cleanse_tab->add_checkbox("cleanse_asleep", "Asleep", true);
			cleanse_ignite = cleanse_tab->add_checkbox("cleanse_ignite", "Ignite if will kill", true);
			cleanse_exhaust = cleanse_tab->add_checkbox("cleanse_exhaust", "Exhaust", true);
			cleanse_delay = cleanse_tab->add_slider("cleanse_delay", "Delay", 200, 0, 2000);
			cleanse_enemies = cleanse_tab->add_slider("cleanse_enemies", "Min. enemies in range", 1, 0, 5);
			cleanse_enemies_range = cleanse_tab->add_slider("cleanse_enemies_range", "^- Range", local_player->get_attack_range() + 200, 0, 2500);
		}

		if (summoner_1.is_heal || summoner_2.is_heal)
		{
			heal_tab = Menu::summoner_spells->add_menu("summ_heal", "Heal");
			heal_tab->set_texture(summoner_1.is_heal ? summoner_1.spell->texture() : summoner_2.spell->texture());
			heal_enable = heal_tab->add_checkbox("enable", "Enable", true);
			heal_tab->set_enabled(heal_enable);

			heal_hp = heal_tab->add_slider("heal_hp", "If HP <= %X", 20, 1, 50);
			heal_incoming_dmg = heal_tab->add_slider("heal_incoming_dmg", "If incoming damage >= %X HP", 10, 1, 100);
			heal_not_level1 = heal_tab->add_checkbox("heal_not_level1", "Dont use level 1", true);
			heal_enemies = heal_tab->add_slider("heal_enemies", "Min. enemies in range", 1, 0, 5);
			heal_enemies_range = heal_tab->add_slider("heal_enemies_range", "^- Range", local_player->get_attack_range() + 200, 0, 2500);
		}

		if (summoner_1.is_barrier || summoner_2.is_barrier)
		{
			barrier_tab = Menu::summoner_spells->add_menu("summ_barrier", "Barrier");
			barrier_tab->set_texture(summoner_1.is_barrier ? summoner_1.spell->texture() : summoner_2.spell->texture());
			barrier_enable = barrier_tab->add_checkbox("enable", "Enable", true);
			barrier_tab->set_enabled(barrier_enable);
			
			barrier_hp = barrier_tab->add_slider("barrier_hp", "If HP <= %X", 10, 1, 50);
			barrier_incoming_dmg = barrier_tab->add_slider("barrier_incoming_dmg", "If incoming damage >= %X HP", 10, 1, 100);
			barrier_not_level1 = barrier_tab->add_checkbox("barrier_not_level1", "Dont use level 1", true);
			barrier_enemies = barrier_tab->add_slider("barrier_enemies", "Min. enemies in range", 1, 0, 5);
			barrier_enemies_range = barrier_tab->add_slider("barrier_enemies_range", "^- Range", local_player->get_attack_range() + 200, 0, 2500);
		}

		if (summoner_1.is_ignite || summoner_2.is_ignite)
		{
			ignite_tab = Menu::summoner_spells->add_menu("summ_ignite", "Ignite");
			ignite_tab->set_texture(summoner_1.is_ignite ? summoner_1.spell->texture() : summoner_2.spell->texture());
			ignite_enable = ignite_tab->add_checkbox("enable", "Enable", true);
			ignite_tab->set_enabled(ignite_enable);

			ignite_combo_only = ignite_tab->add_checkbox("ignite_combo_only", "Only in combo mode", true);
			ignite_ignore_if_killable = ignite_tab->add_checkbox("ignite_ignore_if_killable", "Ignore if killable with 2 autos", true);
		}

		callbacks<EventType::OnTick>::add_callback(on_update, "SummsActivator");
		callbacks<EventType::OnDraw>::add_callback(on_draw, "SummsActivator");
		callbacks<EventType::OnBuffGainLose>::add_callback(on_buff_gainlose, "SummsActivator");
	}

	void SummonerSpells::on_unload()
	{
		sdk->remove_spell(summoner_1.spell);
		sdk->remove_spell(summoner_2.spell);

		callbacks<EventType::OnTick>::remove_callback(on_update);
		callbacks<EventType::OnDraw>::remove_callback(on_draw);
	}
	
	bool SummonerSpells::should_cleanse(Buff* buff)
	{
		if (buff->get_hash() == buff_hash("SummonerExhaust"))
			return get().cleanse_exhaust->get_bool();
		
		switch(buff->get_type())
		{
		case BuffType::Stun:
			return get().cleanse_stun->get_bool();
		case BuffType::Taunt:
			return get().cleanse_taunt->get_bool();
		case BuffType::Berserk:
            return get().cleanse_berserk->get_bool();
        case BuffType::Polymorph:
            return get().cleanse_polymorph->get_bool();
		case BuffType::Snare:
			return get().cleanse_snare->get_bool();
		case BuffType::Fear:
			return get().cleanse_fear->get_bool();
		case BuffType::Charm:
			return get().cleanse_charm->get_bool();
		case BuffType::Blind:
			return get().cleanse_blind->get_bool();
		case BuffType::Asleep:
			return get().cleanse_asleep->get_bool();
		default:
			return false;
		}
	}

	GameObject* get_ignite_target(Spell* ignite, bool ignore_if_killable)
	{
		std::vector<GameObject*> potential_targets{ };
		
		for (const auto& hero : entities->get_heroes())
		{
			if (!hero->is_enemy() || hero->get_distance(local_player) >= ignite->range())
				continue;

			if (hero->get_health() <= 50 + (20 * local_player->get_level())
				&& (!ignore_if_killable || hero->get_health() > dmg_lib->get_auto_attack_damage(local_player, hero) * 2))
				potential_targets.push_back(hero);
		}

		return target_selector->get_target(potential_targets, DamageType::Raw);
	}

	void SummonerSpells::on_update()
	{
		if (!local_player->is_alive())
			return;
		
		if (const auto ignite = get_ignite(); ignite != nullptr && ignite->spell->is_ready())
		{
			if (!get().ignite_combo_only->get_bool() || orbwalker->get_mode() == OrbwalkerMode::Combo)
			{
				if (const auto target = get_ignite_target(ignite->spell, get().ignite_ignore_if_killable->get_bool()))
					ignite->spell->cast(target);
			}
		}

		if (const auto cleanse = get_cleanse(); cleanse != nullptr && cleanse->spell->is_ready())
		{
			if (get().cleanse_ignite->get_bool())
			{
				if (const auto ignite = local_player->get_buff(buff_hash("SummonerDot"));
					ignite != nullptr && local_player->get_health() < 10 + 4 * (ignite->get_caster()->get_level()))
				{
					cleanse->spell->cast();
				}
			}
		}
		
		if (const auto barrier = get_barrier();
			barrier != nullptr
			&& barrier->spell->is_ready()
			&& (!get().barrier_not_level1->get_bool() || local_player->get_level() > 1))
		{
			const auto incoming_damage = health_pred->get_incoming_damage(local_player, 250);
			if ((local_player->get_health() - incoming_damage) * 100 / local_player->get_max_health() <= get().barrier_hp->get_int()
				&& incoming_damage >= get().barrier_incoming_dmg->get_int()
				&& local_player->count_enemies_in_range(get().barrier_enemies_range->get_int()) >= get().barrier_enemies->get_int())
			{
				barrier->spell->cast();
				return; // return because we dont want to use both barrier + heal if we have both summs.
			}
		}
		
		if (const auto heal = get_heal();
			heal != nullptr
			&& heal->spell->is_ready()
			&& (!get().heal_not_level1->get_bool() || local_player->get_level() > 1))
		{
			const auto incoming_damage = health_pred->get_incoming_damage(local_player, 250);
			if ((local_player->get_health() - incoming_damage) * 100 / local_player->get_max_health() <= get().heal_hp->get_int()
				&& incoming_damage >= get().heal_incoming_dmg->get_int()
				&& local_player->count_enemies_in_range(get().heal_enemies_range->get_int()) >= get().heal_enemies->get_int())
			{
				heal->spell->cast();
			}
		}
	}

	void SummonerSpells::on_draw()
	{
		
	}

	void SummonerSpells::on_buff_gainlose(Buff* buff, bool gain)
	{
		if (!gain || !local_player->is_alive() || buff->get_owner() != local_player)
			return;
		
		if (const auto cleanse = get_cleanse();
			cleanse != nullptr
			&& cleanse->spell->is_ready()
			&& get().cleanse_enable->get_bool()
			&& local_player->count_enemies_in_range(get().cleanse_enemies_range->get_int()) >= get().cleanse_enemies->get_int())
		{
			if (get().should_cleanse(buff))
			{
				scheduler->delay_action(get().cleanse_delay->get_int(), [cleanse]()
				{
					if (cleanse->spell->is_ready())
						cleanse->spell->cast();
				});
			}
		}
	}
}
