#include "AntiGapcloser.h"

#ifndef ADD_DASH_DATA_VAR
#define ADD_DASH_DATA_VAR(TYPE, NAME) TYPE NAME = {}; TrackedDashData& set_##NAME( const TYPE& NAME ) { this->NAME = NAME; return *this; }
#endif

struct TrackedDashData
{
	ADD_DASH_DATA_VAR(std::string, name)
	ADD_DASH_DATA_VAR(std::string, spell_name)

	ADD_DASH_DATA_VAR(std::uint32_t, required_buffhash)
	ADD_DASH_DATA_VAR(std::uint32_t, spell_name_hash)

	ADD_DASH_DATA_VAR(bool, wait_for_new_path)
	ADD_DASH_DATA_VAR(bool, is_dangerous)
	ADD_DASH_DATA_VAR(bool, is_fixed_range)
	ADD_DASH_DATA_VAR(bool, is_targeted)
	ADD_DASH_DATA_VAR(bool, is_inverted)
	ADD_DASH_DATA_VAR(bool, find_target_by_buffhash)
	ADD_DASH_DATA_VAR(bool, wait_for_targetable)
	ADD_DASH_DATA_VAR(bool, is_cc)
	ADD_DASH_DATA_VAR(bool, is_unstoppable)

	ADD_DASH_DATA_VAR(float, delay)
	ADD_DASH_DATA_VAR(float, speed)
	ADD_DASH_DATA_VAR(float, range)
	ADD_DASH_DATA_VAR(float, min_range)
	ADD_DASH_DATA_VAR(float, extra_range)
	ADD_DASH_DATA_VAR(float, add_ms_ratio)
	ADD_DASH_DATA_VAR(float, always_fixed_delay)

	TrackedDashData()
	{
		this->speed = FLT_MAX;
		this->spell_name_hash = hash_fnv1a(spell_name.c_str());
	}
};

#undef ADD_DASH_DATA_VAR

struct TrackedDash
{
	GameObject* sender = nullptr;
	GameObject* target = nullptr;

	TrackedDashData* dash_data = nullptr;

	float start_time = 0.f;
	float end_time = 0.f;
	float speed = 0.f;

	Vec3 start_position { };
	Vec3 end_position{ };

	bool is_finished_detecting = false;
};

std::vector<TrackedDash> detected_dashes;
std::vector<TrackedDashData> dashes_data;

std::vector<gapcloser_event> p_handlers;

TrackedDashData& add_dash(const std::string& spell_name, float range, float speed)
{
	TrackedDashData data;
	data.spell_name = spell_name;
	data.range = range;
	data.speed = speed;

	dashes_data.push_back(data);

	return dashes_data[dashes_data.size() - 1];
}

void AntiGapcloser::initialize()
{
	anti_gapcloser->set_callbacks(
		&get_gapcloser_information,
		&add_callback
	);

	callbacks<EventType::OnTick>::add_callback(on_update, "AntiGapcloser");
	callbacks<EventType::OnSetPath>::add_callback(on_new_path, "AntiGapcloser");
	callbacks<EventType::OnProcessSpellCast>::add_callback(on_process_spell, "AntiGapcloser");

	add_dash("3152Active", 300.f, 1150.f).set_name("Hextech Rocketbelt").set_is_fixed_range(true);
	add_dash("6671Cast", 425.f, 1350.f).set_name("Prowler's Claw").set_min_range(200.f);
	add_dash("6693Active", 500.f, 2000.f).set_name("Galeforce").set_is_targeted(true).set_delay(0.2f);

	for (auto& hero : entities->get_heroes())
	{
		if (hero->is_ally())
			continue;

		switch (hero->get_character_hash())
		{
		case CharacterHash::Aatrox:
			add_dash("AatroxE", 300.f, 800.f).set_wait_for_new_path(true);
			break;
		case CharacterHash::Ahri:
			add_dash("AhriTumble", 500.f, 1200.f).set_is_fixed_range(true).set_add_ms_ratio(1.f);
			break;
		case CharacterHash::Akali:
			add_dash("AkaliE", 350.f, 1400.f).set_is_fixed_range(true).set_is_inverted(true).set_delay(0.2f);
			add_dash("AkaliEb", FLT_MAX, 1700.f).set_is_targeted(true).set_required_buffhash(buff_hash("AkaliEMis")).set_find_target_by_buffhash(true);
			add_dash("AkaliR", 750.f, 1500.f).set_is_fixed_range(true);
			add_dash("AkaliRb", 800.f, 3000.f).set_is_fixed_range(true);
			break;
		case CharacterHash::Alistar:
			add_dash("Headbutt", 650.f, 1500.f).set_is_targeted(true).set_is_cc(true);
			break;
		case CharacterHash::Caitlyn:
			add_dash("CaitlynE", 390.f, 1000.f).set_is_fixed_range(true).set_is_inverted(true).set_delay(0.15f);
			break;
		case CharacterHash::Camille:
			add_dash("CamilleEDash2", 800.f, 1050.f).set_is_cc(true).set_add_ms_ratio(1.f);
			break;
		case CharacterHash::Corki:
			add_dash("CarpetBomb", 600.f, 650.f).set_min_range(300.f).set_add_ms_ratio(1.f);
			break;
		case CharacterHash::Diana:
			add_dash("DianaTeleport", 825.f, 2500.f).set_is_targeted(true);
			break;
		case CharacterHash::Ekko:
			add_dash("EkkoEAttack", 600.f, 2000.f).set_is_targeted(true).set_delay(0.1f);
			break;
		case CharacterHash::Elise:
			add_dash("EliseSpiderQCast", 475.f, 1200.f).set_is_targeted(true);
			add_dash("EliseSpiderE", 700.f, 1000.f).set_is_targeted(true).set_wait_for_targetable(true).set_always_fixed_delay(0.5f);
			break;
		case CharacterHash::Evelynn:
			add_dash("EvelynnE2", 400.f, 1900.f).set_is_targeted(true);
			break;
		case CharacterHash::Fiora:
			add_dash("FioraQ", 450.f, 500.f).set_add_ms_ratio(2.f);
			break;
		case CharacterHash::Fizz:
			add_dash("FizzQ", 550.f, 1400.f).set_is_fixed_range(true).set_is_targeted(true);
			break;
		case CharacterHash::Galio:
			add_dash("GalioE", 650.f, 2300.f).set_is_cc(true).set_delay(0.4f);
			break;
		case CharacterHash::Gnar:
			add_dash("GnarE", 475.f, 900.f);
			add_dash("GnarBigE", 675.f, 1165.f);
			break;
		case CharacterHash::Gragas:
			add_dash("GragasE", 600.f, 900.f).set_is_cc(true).set_is_fixed_range(true);
			break;
		case CharacterHash::Graves:
			add_dash("GravesMove", 375.f, 1150.f).set_wait_for_new_path(true);
			break;
		case CharacterHash::Gwen:
			add_dash("GwenE", 350.f, 1050.f).set_add_ms_ratio(1.f);
			break;
		case CharacterHash::Hecarim:
			add_dash("HecarimRampAttack", 900.f, 1200.f).set_is_cc(true).set_is_targeted(true);
			add_dash("HecarimUlt", 1000.f, 1100.f).set_is_cc(true).set_is_unstoppable(true).set_min_range(300.f);
			break;
		case CharacterHash::Illaoi:
			add_dash("IllaoiWAttack", 300.f, 800.f).set_is_targeted(true);
			break;
		case CharacterHash::Irelia:
			add_dash("IreliaQ", 600.f, 1400.f).set_is_targeted(true).set_add_ms_ratio(1.f);
			break;
		case CharacterHash::JarvanIV:
			add_dash("JarvanIVDragonStrike", 850.f, 2000.f).set_is_cc(true).set_wait_for_new_path(true).set_delay(0.4f);
			break;
		case CharacterHash::Jax:
			add_dash("JaxLeapStrike", 700.f, 1600.f).set_is_targeted(true);
			break;
		case CharacterHash::Jayce:
			add_dash("JayceToTheSkies", 600.f, 1000.f).set_is_targeted(true);
			break;
		case CharacterHash::Kaisa:
			add_dash("KaisaR", 3000.f, 3700.f);
			break;
		case CharacterHash::Kayn:
			add_dash("KaynQ", 350.f, 1150.f);
			add_dash("KaynRJumpOut", 500.f, 1200.f).set_wait_for_new_path(true).set_delay(3.f);
			break;
		case CharacterHash::Khazix:
			add_dash("KhazixE", 700.f, 1250.f);
			add_dash("KhazixELong", 850.f, 1250.f);
			break;
		case CharacterHash::Kindred:
			add_dash("KindredQ", 300.f, 500.f).set_add_ms_ratio(1.f);
			break;
		case CharacterHash::Kled:
			add_dash("KledRiderQ", 300.f, 1000.f).set_is_inverted(true).set_delay(0.25f);
			add_dash("KledEDash", 700.f, 600.f).set_add_ms_ratio(1.f);
			break;
		case CharacterHash::Leblanc:
			add_dash("LeblancW", 600.f, 1450.f);
			add_dash("LeblancRW", 600.f, 1450.f);
			break;
		case CharacterHash::LeeSin:
			add_dash("BlindMonkQTwo", 2000.f, 2000.f).set_is_targeted(true).set_required_buffhash(buff_hash("BlindMonkQOne")).set_find_target_by_buffhash(true);
			add_dash("BlindMonkWOne", 700.f, 1350.f).set_is_targeted(true).set_add_ms_ratio(1.f);
			break;
		case CharacterHash::Leona:
			add_dash("LeonaZenithBlade", 900.f, 1300.f).set_is_cc(true).set_always_fixed_delay(0.75f);
			break;
		case CharacterHash::Lillia:
			add_dash("LilliaW", 500.f, 1000.f).set_always_fixed_delay(0.8f);
			break;
		case CharacterHash::Lucian:
			add_dash("LucianE", 475.f, 1350.f).set_wait_for_new_path(true);
			break;
		case CharacterHash::Malphite:
			add_dash("UFSlash", 1000.f, 1500.f).set_is_cc(true).set_is_unstoppable(true).set_add_ms_ratio(1.f);
			break;
		case CharacterHash::Maokai:
			add_dash("MaokaiW", 525.f, 1300.f).set_is_cc(true).set_is_unstoppable(true).set_is_targeted(true);
			break;
		case CharacterHash::MonkeyKing:
			add_dash("MonkeyKingNimbus", 625.f, 1050.f).set_is_targeted(true).set_add_ms_ratio(1.f);
			break;
		case CharacterHash::Nidalee:
			add_dash("Pounce", 750.f, 950.f).set_wait_for_new_path(true).set_min_range(350.f);
			break;
		case CharacterHash::Ornn:
			add_dash("OrnnE", 650.f, 1600.f).set_is_cc(true).set_is_fixed_range(true).set_delay(0.35f);
			break;
		case CharacterHash::Pantheon:
			add_dash("PantheonW", 600.f, 1100.f).set_is_cc(true).set_is_targeted(true);
			break;
		case CharacterHash::Poppy:
			add_dash("PoppyE", 475.f, 1800.f).set_is_cc(true).set_is_targeted(true);
			break;
		case CharacterHash::Pyke:
			add_dash("PykeE", 550.f, 2000.f).set_is_cc(true).set_is_fixed_range(true);
			break;
		case CharacterHash::Qiyana:
			add_dash("QiyanaE", 550.f, 1100.f).set_is_fixed_range(true).set_is_targeted(true).set_add_ms_ratio(1.f);
			break;
		case CharacterHash::Rakan:
			add_dash("RakanW", 650.f, 1700.f).set_is_cc(true).set_always_fixed_delay(0.85f);
			break;
		case CharacterHash::Rammus:
			add_dash("Tremors2", 1500.f, 1000.f).set_is_unstoppable(true).set_always_fixed_delay(0.85f);
			break;
		case CharacterHash::RekSai:
			add_dash("RekSaiEBurrowed", 800.f, 800.f).set_is_fixed_range(true);
			break;
		case CharacterHash::Rell:
			add_dash("RellW_Dismount", 500.f, 1000.f).set_is_cc(true).set_always_fixed_delay(0.85f);
			break;
		case CharacterHash::Renekton:
			add_dash("RenektonDice", 450.f, 760.f).set_is_fixed_range(true).set_add_ms_ratio(1.f);
			add_dash("RenektonSliceAndDice", 450.f, 760.f).set_is_fixed_range(true).set_add_ms_ratio(1.f);
			break;
		case CharacterHash::Riven:
			add_dash("RivenFeint", 250.f, 1200.f).set_is_fixed_range(true);
			break;
		case CharacterHash::Samira:
			add_dash("SamiraE", 650.f, 1600.f).set_is_fixed_range(true).set_is_targeted(true);
			break;
		case CharacterHash::Sejuani:
			add_dash("SejuaniQ", 650.f, 1000.f).set_is_cc(true);
			break;
		case CharacterHash::Shen:
			add_dash("ShenE", 600.f, 800.f).set_is_cc(true).set_min_range(300.f).set_add_ms_ratio(1.f);
			break;
		case CharacterHash::Shyvana:
			add_dash("ShyvanaTransformLeap", 950.f, 1100.f).set_is_unstoppable(true);
			break;
		case CharacterHash::Sylas:
			add_dash("SylasW", 400.f, 1450.f).set_is_targeted(true);
			add_dash("SylasE2", 800.f, 1950.f).set_is_cc(true);
			add_dash("SylasE", 400.f, 1450.f);
			break;
		case CharacterHash::Talon:
			add_dash("TalonQ", 575.f, 1600.f).set_is_targeted(true);
			break;
		case CharacterHash::Tristana:
			add_dash("TristanaW", 900.f, 1100.f).set_delay(0.25f);
			break;
		case CharacterHash::Tryndamere:
			add_dash("TryndamereE", 660.f, 900.f);
			break;
		case CharacterHash::Urgot:
			add_dash("UrgotE", 450.f, 1200.f).set_is_cc(true).set_is_fixed_range(true).set_delay(0.45f).set_add_ms_ratio(1.f);
			break;
		case CharacterHash::Vayne:
			add_dash("VayneTumble", 300.f, 500.f).set_is_fixed_range(true).set_add_ms_ratio(1.f);
			break;
		case CharacterHash::Vi:
			add_dash("ViQ", 725.f, 1400.f).set_is_cc(true).set_wait_for_new_path(true);
			break;
		case CharacterHash::Viego:
			add_dash("ViegoR", 500.f, 1000.f).set_is_unstoppable(true).set_always_fixed_delay(0.6f);
			add_dash("ViegoW", 300.f, 1000.f).set_is_cc(true).set_is_fixed_range(true);
			break;
		case CharacterHash::Volibear:
			add_dash("VolibearR", 700.f, 1000.f).set_is_unstoppable(true).set_always_fixed_delay(1.f);
			break;
		case CharacterHash::XinZhao:
			add_dash("XinZhaoEDash", 1100.f, 2500.f).set_is_targeted(true);
			break;
		case CharacterHash::Yasuo:
			add_dash("YasuoEDash", 475.f, 750.f).set_is_fixed_range(true).set_is_targeted(true).set_add_ms_ratio(0.875f);
			break;
		case CharacterHash::Yone:
			add_dash("YoneE", 300.f, 1200.f).set_is_fixed_range(true);
			break;
		case CharacterHash::Zac:
			add_dash("ZacE", 1800.f, 1000.f).set_wait_for_new_path(true);
			break;
		case CharacterHash::Zed:
			add_dash("ZedR", 625.f, 1000.f).set_is_targeted(true).set_always_fixed_delay(1.6f);
			break;
		case CharacterHash::Zeri:
			add_dash("ZeriE", 2000.f, 600.f).set_wait_for_new_path(true).set_add_ms_ratio(1.f);
			break;
		case CharacterHash::Belveth:
			add_dash("BelvethQ", 400.f, 800.f + hero->get_movement_speed()).set_wait_for_new_path(true);
			break;
		case CharacterHash::Nilah:
			add_dash("NilahE", 450.f, 2200.f).set_is_targeted(true);
			break;
		}
	}
}

GapCloserInformation AntiGapcloser::get_gapcloser_information(GameObject* obj, bool all_dash)
{
	for (const TrackedDash& dash : detected_dashes)
	{
		if (dash.sender != obj || !dash.is_finished_detecting)
			continue;

		if (!all_dash && ((dash.target == nullptr || !dash.target->is_me()) && dash.sender->get_distance(local_player) > 500)) 
			continue;

		GapCloserInformation args;
		args.type = GapCloserType::Skillshot;
		args.sender = dash.sender;
		args.target = dash.target;
		args.start_time = dash.start_time;
		args.end_time = dash.end_time;
		args.speed = dash.speed;
		args.start_position = dash.start_position;
		args.end_position = dash.end_position;
		args.is_unstoppable = dash.dash_data->is_unstoppable;
		args.is_cc = dash.dash_data->is_cc;

		if (!dash.dash_data->name.empty())
			args.type = GapCloserType::Item;

		if (dash.target != nullptr && dash.target->is_me())
			args.type = GapCloserType::Targeted;

		return args;
	}

	return { };
}

bool AntiGapcloser::add_callback(gapcloser_event callback)
{
	if (!callback)
		return false;

	p_handlers.push_back(callback);
	return true;
}

void AntiGapcloser::on_update()
{
	detected_dashes.erase(std::remove_if(detected_dashes.begin(), detected_dashes.end(), [](const TrackedDash& dash)
		{
			return game_time->get_time() >= dash.end_time;
		}), detected_dashes.end());

	for (TrackedDash& dash : detected_dashes)
	{
		if (dash.is_finished_detecting || !dash.dash_data->wait_for_targetable) 
			continue;

		if (game_time->get_time() - dash.start_time < 0.15f) 
			continue;

		if (dash.sender->is_targetable())
		{
			if (dash.sender->get_distance(local_player) > 150)
			{
				dash.end_time = game_time->get_time() - 0.1f; //delete Elise E dash, it was not casted on me
				continue;
			}

			dash.end_position = dash.sender->get_position();

			if (dash.dash_data->always_fixed_delay > 0)
				dash.speed = dash.start_position.distance(dash.end_position) / dash.dash_data->always_fixed_delay;

			dash.start_time = game_time->get_time();
			dash.end_time = dash.start_time + dash.dash_data->always_fixed_delay;
			dash.is_finished_detecting = true;
		}
	}

	for (const TrackedDash& dash : detected_dashes)
	{
		if (!dash.is_finished_detecting || !dash.sender->is_valid_target()) 
			continue;

		if ((dash.target == nullptr || !dash.target->is_me()) && dash.sender->get_distance(local_player) > 500) 
			continue;

		GapCloserInformation args;
		args.type = GapCloserType::Skillshot;
		args.sender = dash.sender;
		args.target = dash.target;
		args.start_time = dash.start_time;
		args.end_time = dash.end_time;
		args.speed = dash.speed;
		args.start_position = dash.start_position;
		args.end_position = dash.end_position;
		args.is_unstoppable = dash.dash_data->is_unstoppable;
		args.is_cc = dash.dash_data->is_cc;

		if (!dash.dash_data->name.empty())
			args.type = GapCloserType::Item;

		if (dash.target != nullptr && dash.target->is_me())
			args.type = GapCloserType::Targeted;

		for (auto const& callback : p_handlers)
		{
			if (callback != nullptr)
			{
				reinterpret_cast<gapcloser_event>(callback)(&args);
			}
		}
	}
}

void AntiGapcloser::on_new_path(GameObject* sender, const std::vector<Vec3>& path, bool is_dash, float dash_speed)
{
	if (is_dash)
	{
		float length = path.size() > 1 ?  Vec3::path_length(path) : 0;

		for (TrackedDash& dash : detected_dashes)
		{
			if (dash.is_finished_detecting || !dash.dash_data->wait_for_new_path || sender != dash.sender) continue;

			dash.start_time = game_time->get_time() - dash.dash_data->delay;
			dash.end_time = game_time->get_time() + length / dash_speed;
			dash.start_position = path.front();
			dash.end_position = path.back();
			dash.speed = dash_speed;
			dash.is_finished_detecting = true;
		}
	}
}

void AntiGapcloser::on_process_spell(SpellCastInfo* spell)
{
	const auto sender = spell->get_source();

	if (!sender || !sender->is_enemy())
		return;

	auto name = spell->get_spell_data()->get_spell_name();
	auto it = std::find_if(dashes_data.begin(), dashes_data.end(), [&name](const TrackedDashData& x) { return x.spell_name == name; });

	if (it != dashes_data.end())
	{
		GameObject* target = spell->get_target();

		if (it->find_target_by_buffhash)
		{
			for (auto&& t : entities->get_heroes())
			{
				if (sender->is_ally() && !t->is_enemy())
					continue;

				if (sender->is_enemy() && !t->is_ally())
					continue;

				if (t->is_valid_target() && t->has_buff(it->required_buffhash))
				{
					target = t;
					break;
				}
			}
		}

		if (it->is_targeted && target == nullptr)
		{
			return;
		}

		if (target && it->required_buffhash && !target->has_buff(it->required_buffhash))
		{
			return;
		}

		auto start = spell->get_start_pos();
		auto end = spell->get_end_pos();

		if (it->min_range > 0 && start.distance_squared(end) < std::powf(it->min_range, 2))
		{
			end = start.extend(end, it->min_range);
		}

		if (it->is_fixed_range || start.distance_squared(end) > std::powf(it->range, 2))
		{
			end = start.extend(end, it->range);
		}

		if (it->is_inverted)
		{
			end = start - (end - start);
		}

		if (target && !it->is_fixed_range)
		{
			end = target->get_position();
		}

		if (it->extra_range > 0)
		{
			end = end.extend(start, -it->extra_range);
		}

		TrackedDash new_dash;
		new_dash.sender = sender;
		new_dash.target = target;
		new_dash.dash_data = &(*it);
		new_dash.start_position = start;
		new_dash.end_position = end;
		new_dash.speed = it->speed + sender->get_movement_speed() * it->add_ms_ratio;

		if (sender->get_character_hash() == CharacterHash::Belveth)
		{
			auto belveth_speed = 750 + 50 * sender->get_spell(SlotId::Q)->get_level() + sender->get_movement_speed();

			if (sender->has_buff(buff_hash("BelvethRSteroid")))
				belveth_speed += belveth_speed / 10.f;

			new_dash.speed = belveth_speed;
		}

		if (it->always_fixed_delay > 0)
			new_dash.speed = new_dash.start_position.distance(new_dash.end_position) / it->always_fixed_delay;

		new_dash.start_time = game_time->get_time();
		new_dash.end_time = new_dash.start_time + it->delay + start.distance(end) / new_dash.speed;

		if (it->wait_for_targetable)
			new_dash.end_time = new_dash.start_time + 2.5f;

		new_dash.is_finished_detecting = !it->wait_for_new_path && !it->wait_for_targetable;

		detected_dashes.push_back(new_dash);
	}
}