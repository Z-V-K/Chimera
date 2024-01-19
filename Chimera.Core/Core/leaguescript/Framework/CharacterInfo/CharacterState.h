#pragma once


class CharacterState final
{
    bool can_attack();
    bool can_cast();
    bool is_immovable();
    bool is_slowed();
    bool is_stealthed();
    bool is_taunted();
    bool is_feared();
    bool is_fleeing();
    bool is_suppressed();
    bool is_asleep();
    bool is_charmed();
    DWORD& get_flags();
};
