#pragma once
#include "DetectedSpells/DetectedSpell.h"

namespace Evade
{
	class SpellDetector
	{
	public:
		inline static std::vector<DetectedSpell*> detected_spells{ };

		static void initialize();
		static void on_unload();

		static void on_process_spell(SpellCastInfo* spell);
		static void on_create_object(GameObject* obj);
		static void on_delete_object(GameObject* obj);
		static void on_tick();
		static void on_draw();

		static void on_create_missile(GameObject* obj);
	};
}
