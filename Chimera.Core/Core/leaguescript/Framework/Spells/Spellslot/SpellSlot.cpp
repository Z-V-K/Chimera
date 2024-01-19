#include "../pch.h"
#include "SpellSlot.h"

#include "../../../Impl/Hooks/retspoof/x64RetSpoof.h"
#include "../Framework/GameEngine/GameTime/GameTime.h"
#include "../Framework/Rendering/r3dTexture/r3dTexture.h"

float SpellSlot::get_cooldown() const
{
	const auto gameTime = GameClock::get_time();
	
	if (get_ammo() > 0)
	{
		return get_ready_at() > gameTime ? get_ready_at() - gameTime : 0.f;
	}

	if (get_ammo_ready_at() > 0)
	{
		return get_ammo_ready_at() > gameTime ? get_ammo_ready_at() - gameTime : 0.f;
	}

	return get_ready_at() > gameTime ? get_ready_at() - gameTime : 0.f;
}

SpellTargetClient* SpellSlot::get_target_client() const
{
	return RVA_CAST_THIS(SpellTargetClient*, Structures::SpellSlot::TargetClient);
}

SpellData* SpellSlot::get_spell_data() const
{
	return RVA_CAST_THIS(SpellData*, Structures::SpellSlot::SpellData);
}

Enums::SpellSlot SpellSlot::get_slot_id() const
{
	return RVA_CAST_THIS(Enums::SpellSlot, Structures::SpellSlot::SlotId);
}

int SpellSlot::get_ammo() const
{
	return RVA_CAST_THIS(int, Structures::SpellSlot::Ammo);
}

int SpellSlot::get_level() const
{
	return RVA_CAST_THIS(int, Structures::SpellSlot::Level);
}

float SpellSlot::get_max_cooldown() const
{
	return RVA_CAST_THIS(float, Structures::SpellSlot::MaxCD);
}

float SpellSlot::get_ready_at() const
{
	return RVA_CAST_THIS(float, Structures::SpellSlot::ReadyAt);
}

float SpellSlot::get_damage() const
{
	return RVA_CAST_THIS(float, Structures::SpellSlot::Damage);
}

float SpellSlot::get_ammo_ready_at() const
{
	return RVA_CAST_THIS(float, Structures::SpellSlot::AmmoReadyAt);
}

float SpellSlot::get_ammo_cooldown() const
{
	return RVA_CAST_THIS(float, Structures::SpellSlot::AmmoCooldown);
}

PVOID SpellSlot::get_icon() const
{
	typedef r3dTexture* (__fastcall* fnGetIconTexture)(const SpellSlot*, bool);
	fnGetIconTexture fn = (fnGetIconTexture)(MAKE_RVA(Addresses::SpellDataInst::GetIconTexture));

	r3dTexture* texture = *reinterpret_cast<r3dTexture**>(x64RetSpoof::spoof_call(fn, this, false));

	if (!texture)
		return nullptr;

	return texture->get_dx_texture();
}

LuaTexture SpellSlot::get_icon_lua() const
{
	return LuaTexture(get_icon());
}
