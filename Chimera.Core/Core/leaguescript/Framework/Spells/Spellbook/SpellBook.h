#pragma once

#include "../Framework/Spells/Spellslot/SpellSlot.h"
#include "../Framework/Enums/SpellEnums.h"
#include "../Impl/Common/Common.h"
#include "../SpellCastInfo/SpellCastInfo.h"

class Spellbook final
{
public:
	Enums::SpellState get_spell_state(Enums::SpellSlot slot);
	bool can_use_spell(Enums::SpellSlot slot);

	void send_spellcast_packet(SpellSlot* spell_slot, Enums::SpellSlot slot_id, uintptr_t cast_spell_argument, unsigned network_id);
	void update_charged_spell(SpellSlot* spell_slot, Enums::SpellSlot slot_id, Vec3* position, bool release_cast);

	static bool apply_hooks();

	void send_spellcast_packet(Enums::SpellSlot slot_id, const Vec3& start_pos, const Vec3& end_pos, GameObject* target);
};
