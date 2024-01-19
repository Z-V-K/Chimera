#include "../pch.h"
#include "SpellBook.h"

#include "../Framework/Spells/SpellTargetClient/SpellTargetClient.h"
#include "../Framework/GameObjects/GameObject/GameObject.h"
#include "../Framework/GameEngine/ObjectManager/ObjectManager.h"
#include "../Framework/Spells/SpellCastInfo/SpellCastInfo.h"
#include "../Framework/Enums/EventType.h"
#include "../Impl/Hooks/Hook.h"
#include "../Impl/Managers/EventManager/EventManager.h"
#include "../Impl/Bypass/Bypass.h"

#include "../Impl/Hooks/retspoof/x64RetSpoof.h"

Hook< convention_type::fastcall_t, void, Spellbook*, SpellSlot*, int, void*, uint32_t, bool > HookOnCastspell;
Hook< convention_type::fastcall_t, char, SpellCastInfo*, bool, bool*, bool, uint32_t, int > HookOnStopCast;
Hook< convention_type::fastcall_t, bool, Spellbook*, SpellCastInfo* > HookOnCastComplete;
Hook< convention_type::fastcall_t, void, SpellCastInfo*, Vec3* > HookOnSpellImpact;

class Wrapper
{
public:
	static void __fastcall OnCastspellCallee(Spellbook* thisPtr, SpellSlot* spellSlot, int slotId, void* castSpellArgument, uint32_t networkId, bool unk)
	{
		bool process = true;

		Vec3 startPos = spellSlot->get_target_client()->get_spell_start_position();
		Vec3 endPos = spellSlot->get_target_client()->get_target_position();
		GameObject* target = ObjectManager::find_object(spellSlot->get_target_client()->get_target_game_object_index());

		g_event_manager->trigger(Enums::EventType::OnCastSpell, slotId, startPos, endPos, target, &process);
		g_event_manager->trigger_lua_bool(Enums::EventType::OnCastSpell, &process, slotId, startPos, endPos, target);
		
		if (process)
		{
			x64RetSpoof::spoof_call(HookOnCastspell.m_original, thisPtr, spellSlot, slotId, castSpellArgument, networkId, unk);
		}
	}

	static char __fastcall OnStopCastCallee(SpellCastInfo* thisPtr, bool animationCancelled, bool* executeCastFrame, bool forceStop, uint32_t destroyMissile, int missileNetworkId)
	{
		const auto ret = x64RetSpoof::spoof_call(HookOnStopCast.m_original, thisPtr, animationCancelled, executeCastFrame, forceStop, destroyMissile, missileNetworkId);

		g_event_manager->trigger(Enums::EventType::OnStopCast, (SpellCastInfo*)((uintptr_t) thisPtr + 0x8), destroyMissile, animationCancelled);
		g_event_manager->trigger_lua(Enums::EventType::OnStopCast, (SpellCastInfo*)((uintptr_t) thisPtr + 0x8), destroyMissile, animationCancelled);
			
		return ret;
	}

	static bool __fastcall OnCastCompleteCallee(Spellbook* thisPtr, SpellCastInfo* spell)
	{
		g_event_manager->trigger(Enums::EventType::OnCastComplete, spell);
		g_event_manager->trigger_lua(Enums::EventType::OnCastComplete, spell);

		return x64RetSpoof::spoof_call(HookOnCastComplete.m_original, thisPtr, spell);
	}

	static void __fastcall OnSpellImpactCallee(SpellCastInfo* spell, Vec3* positionHit)
	{
		x64RetSpoof::spoof_call(HookOnSpellImpact.m_original, spell, positionHit);

		g_event_manager->trigger(Enums::EventType::OnSpellImpact, spell);
		g_event_manager->trigger_lua(Enums::EventType::OnSpellImpact, spell);
	}
};

void Spellbook::send_spellcast_packet(Enums::SpellSlot slot_id, const Vec3& startPos, const Vec3& end_pos, GameObject* target)
{
	SpellSlot* spellslot = GameObject::get_local_player()->get_spell_slot_by_id(slot_id);

	if(!spellslot)
	{
		g_ctx->mConsole->log_warning(skCrypt("Cannot cast spell with slot %i!"), (int)slot_id);
		return;
	}

	uint32_t targetNetworkId = 0;
	uint32_t targetIndex	 = 0;
	if (target)
	{
		targetNetworkId = target->get_network_id();
		targetIndex		= target->get_index();
	}

	spellslot->get_target_client()->set_caster_index(GameObject::get_local_player()->get_index());
	spellslot->get_target_client()->set_target_index(targetIndex);
	spellslot->get_target_client()->set_start_position(startPos);
	spellslot->get_target_client()->set_target_position(end_pos);
	spellslot->get_target_client()->set_target_position2(end_pos);
	spellslot->get_target_client()->set_target_position3(end_pos);

	send_spellcast_packet(spellslot, slot_id, spellslot->get_target_client()->get_cast_spell_argument(), targetNetworkId);
}

void Spellbook::send_spellcast_packet(SpellSlot* spell_slot, Enums::SpellSlot slot_id, uintptr_t cast_spell_argument, unsigned network_id)
{
	Bypass::castspell_flag();
	Bypass::mainloop_check();

	typedef void(__fastcall* fnCastSpell)(Spellbook*, SpellSlot*, int, uintptr_t, unsigned);
	static fnCastSpell fn = (fnCastSpell)MAKE_RVA(Addresses::Spellbook::SendSpellcastPacket);

	x64RetSpoof::spoof_call(fn, GameObject::get_local_player()->get_spell_book_ref(), spell_slot, (int) slot_id, cast_spell_argument, network_id);
}

void Spellbook::update_charged_spell(SpellSlot* spell_slot, Enums::SpellSlot slot_id, Vec3* position, bool release_cast)
{
	Bypass::mainloop_check();

	typedef void(__fastcall* fnUpdateChargedSpell)(Spellbook*, SpellSlot*, int, Vec3*, bool);
	static fnUpdateChargedSpell fn = (fnUpdateChargedSpell)MAKE_RVA(Addresses::Spellbook::UpdateChargedSpell);

	x64RetSpoof::spoof_call(fn, GameObject::get_local_player()->get_spell_book_ref(), spell_slot, (int) slot_id, position, release_cast);
}

Enums::SpellState Spellbook::get_spell_state(Enums::SpellSlot slot)
{
	bool can_use{ };

	typedef Enums::SpellState(__fastcall* fnGetSpellState)(uintptr_t, int, bool*);
	static fnGetSpellState fn = (fnGetSpellState)MAKE_RVA(Addresses::Spellbook::GetSpellState);

	return x64RetSpoof::spoof_call(fn, (uintptr_t)this, (int)slot, &can_use);
}

bool Spellbook::can_use_spell(Enums::SpellSlot slot)
{
	bool ret{ };

	typedef Enums::SpellState(__fastcall* fnGetSpellState)(uintptr_t, int, bool*);
	static fnGetSpellState fn = (fnGetSpellState)MAKE_RVA(Addresses::Spellbook::GetSpellState);

	x64RetSpoof::spoof_call(fn, (uintptr_t)this, (int)slot, &ret);

	return ret;
}

bool Spellbook::apply_hooks()
{
	HookOnCastspell.apply_jmp(MAKE_RVA(Addresses::Spellbook::SendSpellcastPacket), (uintptr_t)Wrapper::OnCastspellCallee, 15);
	HookOnStopCast.apply_jmp(MAKE_RVA(Addresses::GameObjectAddresses::OnStopCast), (uintptr_t)Wrapper::OnStopCastCallee, 14);
	HookOnCastComplete.apply_jmp(MAKE_RVA(Addresses::GameObjectAddresses::OnCastComplete), (uintptr_t)Wrapper::OnCastCompleteCallee, 16);
	HookOnSpellImpact.apply_jmp(MAKE_RVA(Addresses::Spellbook::OnSpellImpact), (uintptr_t)Wrapper::OnSpellImpactCallee, 15);

	return HookOnCastspell.is_applied();
}