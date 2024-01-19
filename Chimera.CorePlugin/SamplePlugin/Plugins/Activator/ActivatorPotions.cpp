#include "ActivatorPotions.h"
#include "Activator.h"

namespace Activator
{
	bool lock_item = false;

	void Potions::initialize()
	{
		Menu::potions = Menu::main_menu->add_menu("potions", "Potions", ICON_FA_FLASK_POTION);
		enable = Menu::potions->add_checkbox("enable", "Enable", true);
		Menu::potions->set_enabled(enable);

		potion_health = Menu::potions->add_slider("potion_health", "Potion: min health %", 50, 0, 99);

		cookie_health = Menu::potions->add_slider("cookie_health", "Cookies: min health %", 50, 0, 99);
		cookie_mana = Menu::potions->add_slider("cookie_mana", "Cookies: min mana %", 30, 0, 99);

		corrupting_pot_health = Menu::potions->add_slider("corrupting_pot_health", "Corrupting pot: min health %", 50, 0, 99);
		corrupting_pot_mana = Menu::potions->add_slider("corrupting_pot_mana", "Corrupting pot: min mana %", 30, 0, 99);

		callbacks<EventType::OnSlowTick>::add_callback(on_tick, "ActivatorPotions");
	}

	void Potions::on_tick()
	{
		const int health_pct = (local_player->get_health() / local_player->get_max_health()) * 100;
		const int mana_pct = local_player->get_max_mana() > 0 ? (local_player->get_health() / local_player->get_max_health()) * 100 : 0;

		const bool should_use_pot = health_pct < get().potion_health->get_int();
		const bool should_use_cookie = health_pct < get().cookie_health->get_int() || mana_pct < get().cookie_mana->get_int();
		const bool should_use_corrupt = health_pct < get().corrupting_pot_health->get_int() || mana_pct < get().corrupting_pot_mana->get_int();

		if (!should_use_pot && should_use_cookie && !should_use_corrupt)
			return;

		if (local_player->has_buff(buff_hash("item2010")) || local_player->has_buff(buff_hash("itemdarkcrystalflask")))
			return;

		auto cookie_slot = local_player->get_item_spell_slot(ItemId::Total_Biscuit_of_Everlasting_Will);

		if (cookie_slot && should_use_cookie)
		{
			local_player->cast_spell(cookie_slot->get_slot_id());
			return;
		}

		auto corrupting_slot = local_player->get_item_spell_slot(ItemId::Corrupting_Potion);
		if (corrupting_slot && should_use_corrupt)
		{
			local_player->cast_spell(corrupting_slot->get_slot_id());
			return;
		}

		if (local_player->has_buff(buff_hash("item2003")) || local_player->has_buff(buff_hash("itemcrystalflask")))
			return;

		auto potion_slot = local_player->get_item_spell_slot(ItemId::Health_Potion);

		if (!potion_slot)
			potion_slot = local_player->get_item_spell_slot(ItemId::Refillable_Potion);
		
		if (potion_slot && should_use_pot)
		{
			local_player->cast_spell(potion_slot->get_slot_id());
		}
	}

	void Potions::on_unload()
	{
		
	}

}