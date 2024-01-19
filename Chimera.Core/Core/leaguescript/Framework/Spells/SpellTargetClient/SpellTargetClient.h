#pragma once

#include "../Impl/Common/Common.h"
#include "../Impl/Vector/Vector.h"

class SpellTargetClient final
{
public:
	uintptr_t get_cast_spell_argument();
	int get_caster_game_object_index();
	int get_target_game_object_index();
	const Vec3& get_spell_start_position();
	const Vec3& get_target_position();
	const Vec3& get_target_position2();
	const Vec3& get_target_position3();

	void set_caster_index(uint32_t index);
	void set_target_index(uint32_t index);
	void set_start_position(const Vec3& pos);
	void set_target_position(const Vec3& pos);
	void set_target_position2(const Vec3& pos);
	void set_target_position3(const Vec3& pos);
};