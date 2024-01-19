#include "HealthPrediction.h"

std::unordered_map<GameObject*, std::shared_ptr<PredictedDamage>> active_attacks{ };

void HealthPrediction::initialize()
{
	health_pred->set_callbacks(
		&get_health_prediction,
		&get_incoming_damage,
		&has_turret_aggro,
		&has_minion_aggro,
		&turret_aggro_start_time,
		&get_aggro_turret
	);

	callbacks<EventType::OnTick>::add_callback(on_game_update, "HealthPred");
	callbacks<EventType::OnProcessSpellCast>::add_callback(on_process_spell, "HealthPred");
	callbacks<EventType::OnCastComplete>::add_callback(on_cast_complete, "HealthPred");
	callbacks<EventType::OnStopCast>::add_callback(on_stop_cast, "HealthPred");
	callbacks<EventType::OnDeleteObject>::add_callback(on_delete_object, "HealthPred");
}

float HealthPrediction::get_health_prediction(GameObject* obj, int time, int delay)
{
	if (!obj)
		return 0.f;
	
	return obj->get_health() - get_incoming_damage(obj, time, delay);
}

float HealthPrediction::get_incoming_damage(GameObject* obj, int time, int delay)
{
	if (!obj)
		return 0.f;
	
	float calculated_dmg = 0.0f;

	for (const auto& attack : std::views::values(active_attacks))
	{
		if (attack->target != obj || attack->processed || attack->source == nullptr)
			continue;

		if ((float) attack->start_tick 
				+ attack->delay 
				+ 1000.f * 
					(attack->source->is_melee() ? 0.f : std::max(0.f, obj->get_distance(attack->source) - attack->target_bounding_radius) / attack->projectile_speed) 
				+ (float) delay 
			< (float) (game_time->get_tick_count() + time))
		{
			calculated_dmg += attack->damage;
		}
	}

	return calculated_dmg;
}

bool HealthPrediction::has_minion_aggro(GameObject* minion)
{
	if (!minion || !minion->is_minion())
		return false;

	if (!minion || !minion->is_minion())
		return false;

	for (const auto& attack : std::views::values(active_attacks))
	{
		if (!attack->source->is_minion() || attack->target != minion)
			continue;

		return true;
	}

	return false;
}

bool HealthPrediction::has_turret_aggro(GameObject* minion)
{
	if (!minion || !minion->is_minion())
		return false;

	for (const auto& attack : std::views::values(active_attacks))
	{
		if (!attack->source->is_turret() || attack->target != minion)
			continue;

		return true;
	}

	return false;
}

int HealthPrediction::turret_aggro_start_time(GameObject* minion)
{
	if (!minion || !minion->is_minion())
		return 0;

	for (const auto& attack : std::views::values(active_attacks))
	{
		if (!attack->source->is_turret() || attack->target != minion)
			continue;

		return attack->start_tick;
	}

	return 0;
}

GameObject* HealthPrediction::get_aggro_turret(GameObject* minion)
{
	if (!minion || !minion->is_minion())
		return nullptr;

	for (const auto& attack : std::views::values(active_attacks))
	{
		if (!attack->source->is_turret() || attack->target != minion)
			continue;

		return attack->source;
	}

	return nullptr;
}

void HealthPrediction::on_process_spell(SpellCastInfo* processed_spell)
{
	const auto sender = processed_spell->get_source();
	const auto target = processed_spell->get_target();

	if (!sender || !target || !target->is_alive() || !processed_spell->is_auto())
		return;

	PredictedDamage dmg {
		game_time->get_tick_count() - net_client->get_ping() / 2,
		sender->is_melee() ? FLT_MAX : (sender->is_turret() ? 1200.f : processed_spell->get_spell_data()->missileSpeed()),
		sender->get_attack_delay() * 1000.f - (sender->is_turret() ? 70.f : 0.f),
		sender->get_bounding_radius(),
		 dmg_lib->get_auto_attack_damage(sender, target),
		sender->get_attack_cast_delay() * 1000.f,
		sender,
		target,
		false,
		false
	};

	if (!active_attacks.contains(sender))
		active_attacks.insert({ sender, nullptr });
	
	active_attacks.at(sender) = std::make_shared<PredictedDamage>(dmg);
}

void HealthPrediction::on_cast_complete(SpellCastInfo* processed_spell)
{
	const auto sender = processed_spell->get_source();
	const auto target = processed_spell->get_target();

	if (!sender || !target || !target->is_alive() || !processed_spell->is_auto() || sender->is_ranged() || !active_attacks.contains(sender))
		return;

	active_attacks.at(sender)->processed = true;
}

void HealthPrediction::on_stop_cast(SpellCastInfo* spell, bool destroy_missile, bool animation_cancelled)
{
	const auto sender = spell->get_source();
	const auto target = spell->get_target();

	if (!sender || !target || !target->is_alive() || !spell->is_auto() || !animation_cancelled || !destroy_missile)
		return;

	if (!active_attacks.contains(sender))
		return;

	active_attacks.erase(sender);
}

void HealthPrediction::on_delete_object(GameObject* obj)
{
	if (!obj || !obj->is_missile())
		return;

	const auto missile = obj->get_missile_client();

	if (!missile)
		return;

	const auto sender = missile->get_source();

	if (!sender || !active_attacks.contains(sender))
		return;

	active_attacks.at(sender)->processed = true;
}

void HealthPrediction::on_game_update()
{
	for (auto it = active_attacks.begin(); it != active_attacks.end();) {
		if (it->second->start_tick < game_time->get_tick_count() - 3000 || it->second->processed) {
			it = active_attacks.erase(it);
		}
		else
			++it;
	}
}