#pragma once

namespace Enums
{
	enum class SpellState : int {
		Unknown = -1,
		Ready = 0,
		NotAvailable = 4,
		Supressed = 8,
		NotLearned = 12,
		Channeling = 24,
		Cooldown = 32,
		NoMana = 64,
	};

	enum class SpellSlot : int {
		Unknown = -1,
		Q = 0,
		W = 1,
		E = 2,
		R = 3,
		Summoner1,
		Summoner2,
		Item1,
		Item2,
		Item3,
		Item4,
		Item5,
		Item6,
		Item_Trinket,
		Recall,
		SpecialAttack = 45,
		SpecialSpell1 = 48,
		Auto1 = 64,
		Auto2 = 65,
		Auto3 = 66,
	};
}