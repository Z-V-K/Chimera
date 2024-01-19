#pragma once

namespace Enums {
	enum EventType : int {
		OnWndProc = 1,
		OnGameTick,
		OnSlowTick,
		OnDraw,
		OnCreateObject,
		OnDeleteObject,
		OnProcessSpell,
		OnIssueOrder,
		OnCastSpell,
		OnStopCast,
		OnCastComplete,
		OnDrawEnvironment,
		OnSpellImpact,
		OnPlayAnimation,
		OnBuffGainLose,
		OnSetPath,
		OnProcessAutoAttack,
		OnNotifyEvent,
		OnBeforeAttackOrbwalker,
		OnAfterAttackOrbwalker,
		OnBeforeMoveOrbwalker,
		OnAfterMoveOrbwalker,

		size
	};

	static inline const char* event_type_str[]{
		"Unknown",
		"OnWndProc",
		"OnGameTick",
		"OnSlowTick",
		"OnDraw",
		"OnCreateObject",
		"OnDeleteObject",
		"OnProcessSpell",
		"OnIssueOrder",
		"OnCastSpell",
		"OnStopCast",
		"OnCastComplete",
		"OnDrawEnvironment",
		"OnSpellImpact",
		"OnPlayAnimation",
		"OnBuffGainLose",
		"OnSetPath",
		"OnProcessAutoAttack",
		"OnNotifyEvent",
		"OnBeforeAttackOrbwalker",
		"OnAfterAttackOrbwalker",
		"OnBeforeMoveOrbwalker",
		"OnAfterMoveOrbwalker",
	};
}