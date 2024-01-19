#include "TurretMissileManager.h"

GameObject* closest_attack = nullptr;
GameObject* attack_target = nullptr;
GameObject* attack_closest_turret = nullptr;
int start_time = 0;
double damage = 0.0;

void TurretMissileManager::initialize()
{
	callbacks<EventType::OnCreateObject>::add_callback(on_create, "TurretMissileManager");
	callbacks<EventType::OnDeleteObject>::add_callback(on_delete, "TurretMissileManager");
	callbacks<EventType::OnProcessSpellCast>::add_callback(on_process_spell, "TurretMissileManager");
}

void TurretMissileManager::on_unload()
{
}

void TurretMissileManager::on_create(GameObject* obj)
{
    if (!obj || !obj->is_missile())
        return;

    const auto missile = obj->get_missile_client();
    if (!missile)
        return;

    const auto source = missile->get_source();
    const auto target = missile->get_target();

    if (!source || !target || !source->is_turret() || source != attack_closest_turret)
        return;

    closest_attack = obj;
    attack_target = target;

    start_time = game_time->get_tick_count();
    damage = dmg_lib->get_auto_attack_damage(source, target);
}

void TurretMissileManager::on_delete(GameObject* obj)
{
    if (obj == closest_attack)
        closest_attack = nullptr;
}

void TurretMissileManager::on_process_spell(SpellCastInfo* spell)
{
	if (!spell)
		return;

	const auto source = spell->get_source();

	if (!source || !source->is_turret() || source->get_distance(local_player) > 2500)
		return;

    float closest = FLT_MAX;
    GameObject* closest_turret = nullptr;
    for (const auto& t : entities->get_turrets())
    {
        if (!t || !t->is_alive()) 
            continue;

        const auto distance = t->get_distance(local_player);

        if (distance > 2500)
            continue;

        if (distance < closest)
        {
            closest = distance;
            closest_turret = t;
        }
    }

    attack_closest_turret = closest_turret;
}

GameObject* TurretMissileManager::get_target()
{
    return attack_target;
}

bool TurretMissileManager::is_attack_valid()
{
    return attack_closest_turret != nullptr && closest_attack != nullptr && attack_target != nullptr;
}

double TurretMissileManager::get_damage()
{
    return damage;
}

int TurretMissileManager::get_predicted_land_time()
{
    if (!closest_attack || !attack_closest_turret || !attack_target)
        return 0;

    return start_time +
        (int) (attack_closest_turret->get_attack_cast_delay() * 1000.f +
        attack_closest_turret->get_distance(attack_target) / closest_attack->get_missile_client()->get_spell_data()->missileSpeed() * 1000.f) +
        net_client->get_ping();
}

GameObject* TurretMissileManager::get_closest_turret()
{
    return attack_closest_turret;
}