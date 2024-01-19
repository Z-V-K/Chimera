#include "Plugin.h"

#include "../Plugins/Activator/Activator.h"
#include "../Plugins/TargetSelector/TargetSelector.h"
#include "../Plugins/Orbwalker/Orbwalker.h"
#include "../Plugins/Awareness/RangeIndicator/RangeIndicator.h"
#include "../Plugins/Permashow/PermashowDebug.h"
#include "../Plugins/Prediction/Prediction.h"
#include "../Plugins/Awareness/Awareness.h"
#include "../Plugins/Awareness/SpellTracker/SpellTracker.h"
#include "../Plugins/Awareness/Waypoints/Waypoints.h"
#include "../Plugins/Awareness/WardTracker/WardTracker.h"
#include "../Plugins/Awareness/JungleTracker/JungleTracker.h"
#include "../Plugins/DamageLib/DamageLib.h"
#include "../Plugins/Awareness/ChampionTracker/ChampionTracker.h"
#include "../Plugins/HealthPred/HealthPrediction.h"
#include "../Plugins/Awareness/Hud/Hud.h"
#include "../Plugins/Awareness/StasisTracker/StasisTracker.h"
#include "../Plugins/Awareness/ItemTracker/ItemTracker.h"
#include "../Plugins/Awareness/NotificationSystem/NotificationSystem.h"
#include "AntiGapcloser/AntiGapcloser.h"
#include "Debug/Debug.h"
#include "Evade/Evade.h"
#include "Utils/Collisions.h"

namespace Plugin
{
	void on_load()
	{
		PermashowDebug::initialize();
		DamageLib::initialize();
		HealthPrediction::initialize();
		TargetSelector::initialize();
		Orbwalker::initialize();
		Debug::initialize();
		Collisions::initialize();
		Prediction::initialize();
		Awareness::initialize();
		Awareness::ChampionTracker::initialize();
		Awareness::WardTracker::initialize();
		Awareness::RangeIndicator::initialize();
		Awareness::Waypoints::initialize();
		Awareness::SpellTracker::initialize();
		Awareness::JungleTracker::initialize();
		Awareness::Hud::initialize();
		Awareness::StasisTracker::initialize();
		Awareness::ItemTracker::initialize();
		Awareness::NotificationSystem::initialize();
		AntiGapcloser::initialize();
		Activator::initialize();
		//Evade::initialize();
	}

	void on_unload()
	{
		Orbwalker::on_unload();
		Debug::on_unload();
		DamageLib::on_unload();
		//Evade::on_unload();
	}
}
