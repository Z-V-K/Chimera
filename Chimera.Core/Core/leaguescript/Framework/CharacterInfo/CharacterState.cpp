#include "../pch.h"
#include "CharacterState.h"

#include "../Impl/Common/Common.h"
#include "../Enums/GameObjectEnums.h"

bool CharacterState::can_attack()
{
    return this->get_flags() & (DWORD)Enums::GameObjectActionState::CanAttack;
}

bool CharacterState::can_cast()
{
    return this->get_flags() & (DWORD)Enums::GameObjectActionState::CanCast;
}

bool CharacterState::is_immovable()
{
    return this->get_flags() & (DWORD)Enums::GameObjectActionState::Immovable;
}

bool CharacterState::is_slowed()
{
    return this->get_flags() & (DWORD)Enums::GameObjectActionState::Slowed;
}

bool CharacterState::is_stealthed()
{
    return this->get_flags() & (DWORD)Enums::GameObjectActionState::Stealthed;
}

bool CharacterState::is_taunted()
{
    return this->get_flags() & (DWORD)Enums::GameObjectActionState::Taunted;
}

bool CharacterState::is_feared()
{
    return this->get_flags() & (DWORD)Enums::GameObjectActionState::Feared;
}

bool CharacterState::is_fleeing()
{
    return this->get_flags() & (DWORD)Enums::GameObjectActionState::Fleeing;
}

bool CharacterState::is_suppressed()
{
    return this->get_flags() & (DWORD)Enums::GameObjectActionState::Supressed;
}

bool CharacterState::is_asleep()
{
    return this->get_flags() & (DWORD)Enums::GameObjectActionState::Sleep;
}

bool CharacterState::is_charmed()
{
    return this->get_flags() & (DWORD)Enums::GameObjectActionState::Charmed;
}

DWORD& CharacterState::get_flags()
{
    return RVA_CAST_THIS(DWORD, Structures::CharacterState::Flags);
}