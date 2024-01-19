#include "AutoSmite.h"
#include "Activator.h"

namespace Activator
{
	void AutoSmite::initialize(SpellSlot* smite_slot)
	{
		smite_spell = sdk->register_spell(smite_slot->get_slot_id(), local_player->get_bounding_radius() + 500.f);

		Menu::auto_smite = Menu::main_menu->add_menu("auto_smite", "Auto smite", ICON_FA_BOLT);
		enable = Menu::auto_smite->add_keybind("enable", "Enable", false, 'H', true, ICON_FA_CHECK);
		Menu::auto_smite->set_enabled(enable);

		monster_settings = Menu::auto_smite->add_menu("monster_settings", "Monsters");
		enable_buffs = monster_settings->add_checkbox("enable_buffs", "Red/Blue buff", true);
		enable_baron = monster_settings->add_checkbox("enable_baron", "Baron nashor", true);
		enable_herald = monster_settings->add_checkbox("enable_herald", "Rift herald", true);
		enable_drake = monster_settings->add_checkbox("enable_drake", "Dragon", true);
		enable_crab = monster_settings->add_checkbox("enable_crab", "Crab", true);
		enable_big_monster_camps = monster_settings->add_checkbox("enable_big_monsters", "Camps big monster", true);

		callbacks<EventType::OnTick>::add_callback(on_update, "AutoSmite");
	}

	void AutoSmite::on_unload()
	{
		sdk->remove_spell(smite_spell);
	}

	void AutoSmite::on_update()
	{
		if (!get().enable->get_bool() || !get().smite_spell->is_ready())
			return;

		for (const auto& minion : entities->get_minions())
		{
			if (!minion->is_jungle_minion())
				continue;
			
			const auto hash = minion->get_character_hash();

			if (hash == CharacterHash::Sru_Crab && !get().enable_crab->get_bool())
				continue;

			if ((hash == CharacterHash::SRU_Blue || hash == CharacterHash::SRU_Red)
				&& !get().enable_buffs->get_bool())
				continue;

			if (minion->is_baron() && !get().enable_baron->get_bool())
				continue;

			if (minion->is_herald() && !get().enable_herald->get_bool())
				continue;

			if (minion->is_dragon() && !get().enable_drake->get_bool())
				continue;

			if ((hash == CharacterHash::SRU_Krug || hash == CharacterHash::SRU_Gromp || hash == CharacterHash::SRU_Murkwolf || hash == CharacterHash::SRU_Razorbeak)
				&& !get().enable_big_monster_camps->get_bool())
				continue;

			if (get().smite_spell->handle()->get_damage() >= minion->get_health() && minion->is_valid_target(get().smite_spell->range()))
				get().smite_spell->cast(minion);
		}
	}

	void AutoSmite::on_draw()
	{
		
	}
}