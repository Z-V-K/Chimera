#include "../pch.h"

#ifndef _ARRAYSIZE
#define _ARRAYSIZE(_ARR) ((int)(sizeof(_ARR) / sizeof(*(_ARR))))
#endif

void Console::log(const char* text, ...)
{
	char buf[1024];
	va_list args;
	va_start(args, text);
	vsnprintf(buf, _ARRAYSIZE(buf), text, args);
	buf[_ARRAYSIZE(buf) - 1] = 0;
	va_end(args);

	__log(buf);
}

void Console::warn(const char* text, ...) {
	char buf[1024];
	va_list args;
	va_start(args, text);
	vsnprintf(buf, _ARRAYSIZE(buf), text, args);
	buf[_ARRAYSIZE(buf) - 1] = 0;
	va_end(args);

	__warn(buf);
}

void Console::err(const char* text, ...) {
	char buf[1024];
	va_list args;
	va_start(args, text);
	vsnprintf(buf, _ARRAYSIZE(buf), text, args);
	buf[_ARRAYSIZE(buf) - 1] = 0;
	va_end(args);

	__err(buf);
}

void Console::dbg(const char* text, ...) {
	char buf[1024];
	va_list args;
	va_start(args, text);
	vsnprintf(buf, _ARRAYSIZE(buf), text, args);
	buf[_ARRAYSIZE(buf) - 1] = 0;
	va_end(args);

	__dbg(buf);
}

void Console::info(const char* text, ...) {
	char buf[1024];
	va_list args;
	va_start(args, text);
	vsnprintf(buf, _ARRAYSIZE(buf), text, args);
	buf[_ARRAYSIZE(buf) - 1] = 0;
	va_end(args);

	__info(buf);
}

bool GameObject::is_super_minion()
{
	if (!is_minion())
		return false;

	const auto hash = get_character_hash();

	return hash == CharacterHash::SRU_ChaosMinionSuper
		|| hash == CharacterHash::SRU_OrderMinionSuper
		|| hash == CharacterHash::HA_ChaosMinionSuper
		|| hash == CharacterHash::HA_OrderMinionSuper;
}

bool GameObject::is_siege_minion()
{
	if (!is_minion())
		return false;

	const auto hash = get_character_hash();

	return hash == CharacterHash::SRU_ChaosMinionSiege
		|| hash == CharacterHash::SRU_OrderMinionSiege
		|| hash == CharacterHash::HA_ChaosMinionSiege
		|| hash == CharacterHash::HA_OrderMinionSiege;
}

int GameObject::count_allies_in_range(float range)
{
	auto count = 0;

	for (const auto hero : entities->get_heroes())
	{
		if (is_ally() && !hero->is_ally())
			continue;

		if (is_enemy() && !hero->is_enemy())
			continue;

		if (hero != this && hero->is_alive() && hero->is_visible() && get_distance(hero) <= range)
			count++;
	}

	return count;
}

int GameObject::count_enemies_in_range(float range)
{
	auto count = 0;

	for (const auto hero : entities->get_heroes())
	{
		if (is_ally() && !hero->is_enemy())
			continue;

		if (is_enemy() && !hero->is_ally())
			continue;

		if (hero != this && hero->is_alive() && hero->is_visible() && get_distance(hero) <= range)
			count++;
	}

	return count;
}

bool GameObject::is_under_enemy_turret()
{
	return get_position().is_under_tower(false, true);
}

bool GameObject::is_under_ally_turret()
{
	return get_position().is_under_tower(true, false);
}

float GameObject::get_distance(GameObject* other, bool use_height)
{
	return other ? get_position().distance(other->get_position()) : 0.f;
}

float GameObject::get_distance(const Vec3& pos, bool use_height)
{
	return get_position().distance(pos);
}

void GameObject::move_to(const Vec3& pos)
{
	issue_order(IssueOrderType::MoveTo, pos, nullptr);
}

void GameObject::attack(GameObject* obj)
{
	issue_order(IssueOrderType::AttackTo, obj->get_position(), obj);
}

std::vector<std::unique_ptr<Spell>> registered_spells { };
std::map<SlotId, bool> enabled_spellslots { { SlotId::Q, true }, { SlotId::W, true }, { SlotId::E, true }, { SlotId::R, true } };
float next_spell_cast = 0.f;
bool hooked = false;

void on_cast_spell(SlotId slot_id, Vec3* start_position, Vec3* end_position, GameObject* target, bool* process)
{
	if (slot_id >= SlotId::Q && slot_id <= SlotId::R && local_player->get_spell_state(slot_id) == SpellState::Ready)
	{
		if (!target && game_time->get_time() < next_spell_cast && enabled_spellslots[slot_id])
			*process = false;

		else 
			next_spell_cast = game_time->get_time() + net_client->get_ping() / 1000.f + 0.133f;
	}
}

Spell* SDK::register_spell(SlotId slot, float range, DamageType damage_type)
{
	if (slot == SlotId::Unknown) 
		return nullptr;

	if (!hooked)
	{
		callbacks<EventType::OnCastSpell>::add_callback(on_cast_spell, "SpellSDK");
		hooked = true;
	}

	registered_spells.push_back(std::make_unique<Spell>(slot, range, damage_type));

	return registered_spells.back().get();
}

bool SDK::remove_spell(Spell* spell)
{
	auto const& it = std::find_if(registered_spells.begin(), registered_spells.end(), [spell](const std::unique_ptr<Spell>& x) { return x.get() == spell; });

	if (it == registered_spells.end())
		return false;

	registered_spells.erase(it);
	return true;
}

SpellSlot* Spell::handle()
{
	return local_player->get_spell(this->slot);
}

float Spell::get_damage(GameObject* target, int stage, int stacks)
{
	return dmg_lib->get_spell_damage(local_player, target, this->slot, stage, stacks);
}

bool Spell::is_ready(float time)
{
	const auto spell = local_player->get_spell(this->slot);

	if (!spell || spell->get_level() == 0)
		return false;

	const auto spell_state = local_player->get_spell_state(this->slot);

	if (spell_state == SpellState::NoMana)
	{
		if (is_charged_spell && game_time->get_time() - charging_started_time < .3f)
			return true;

		const auto charge_buff = get_charge_buff();
		return charge_buff && charge_buff->is_active();
	}

	return spell_state == SpellState::Ready;
}

bool Spell::cast()
{
	if (game_time->get_time( ) < last_spell_cast + cast_cooldown)
		return false;

	local_player->cast_spell(this->slot);

	last_spell_cast = game_time->get_time( );
	return true;
}

bool Spell::cast(const Vec3& position)
{
	if (game_time->get_time() < last_spell_cast + cast_cooldown)
		return false;

	if (is_locked())
		return false;

	if (!this->is_charged_spell)
	{
		local_player->cast_spell(slot, position);

		last_spell_cast = game_time->get_time();
		return true;
	}
	if (is_charging() && game_time->get_time() - charging_started_time > 0.f)
	{
		local_player->update_charged_spell(this->slot, position, true);

		last_spell_cast = game_time->get_time();
		return true;
	}

	return start_charging();
}

bool Spell::cast(GameObject* obj)
{
	if (game_time->get_time() < last_spell_cast + cast_cooldown)
		return false;

	if (!is_charged_spell)
	{
		local_player->cast_spell(slot, obj);
		last_spell_cast = game_time->get_time();
		return true;
	}
	if (is_charging() && game_time->get_time() - charging_started_time > 0.f)
	{
		local_player->update_charged_spell(slot, obj->get_position(), true);

		last_spell_cast = game_time->get_time();
		return true;
	}

	return false;
}

void* Spell::texture()
{
	return handle()->get_icon();
}

float Spell::cooldown_time()
{
	if (const auto handle = this->handle())
		return handle->get_cooldown();

	return 0.f;
}

float Spell::range()
{
	if (!is_charged_spell)
		return _range;

	if (is_charging())
		return charged_min_range + fminf(charged_max_range - charged_min_range, (charged_max_range - charged_min_range) * this->charged_percentage());

	return charged_max_range;
}

int Spell::ammo()
{
	if (const auto handle = this->handle())
		return handle->get_ammo();

	return 0;
}

int Spell::level()
{
	if (const auto handle = this->handle())
		return handle->get_level();

	return 0;
}

Buff* Spell::get_charge_buff()
{
	return local_player->get_buff(charge_buff_hash);
}

float Spell::charged_percentage()
{
	const auto buff = get_charge_buff();

	if (buff && buff->is_active())
	{
		return (fmaxf(0.f, fminf(1.f, (game_time->get_time() - buff->get_start_time() + 0.25f) / charge_duration)));
	}

	return fmaxf(0.f, fminf(1.f, is_charging() ? (game_time->get_time() - charging_started_time) / charge_duration : 0.f));
}

bool Spell::is_charging()
{
	if (!is_ready())
		return false;

	if (game_time->get_time() - charged_started_time < .3f)
		return true;

	const auto buff = get_charge_buff();
	return buff && buff->is_active();
}

bool Spell::is_charged()
{
	return is_charging() && charged_percentage() > .975f;
}

bool Spell::start_charging()
{
	return start_charging(local_player->get_position());
}

bool Spell::start_charging(const Vec3& pos)
{
	if (game_time->get_time() < last_spell_cast + cast_cooldown)
		return false;

	if (is_locked())
		return false;

	if (!is_charging() && is_ready())
	{
		if (game_time->get_time() < last_spell_cast + 1.5f)
			return false;

		local_player->cast_spell(slot, local_player->get_position(), pos, nullptr);

		last_spell_cast = game_time->get_time();

		charging_started_time = last_spell_cast - (net_client->get_ping() / 1000.f);
		return true;
	}

	return is_charging();
}

void Spell::set_skillshot(float delay, float radius, float speed, const std::vector<CollisionObject>& collision_objects, SkillshotType type)
{
	this->type = type;
	this->_delay = delay;
	this->_radius = radius;
	this->_speed = speed;
	this->collision_objects = collision_objects;
	this->collision = !collision_objects.empty();

	if (this->slot >= SlotId::Q && this->slot <= SlotId::R)
		lock_enabled = true;
}

void Spell::set_charged(float range_min, float range_max, float charge_duration)
{
	this->charged_min_range = range_min;
	this->charged_max_range = range_max;
	this->charge_duration = charge_duration;
	this->_range = range_max;
	this->is_charged_spell = true;
}

GameObject* Spell::get_target(float extra_range)
{
	return target_selector->get_target(this->range() + extra_range, this->_damage_type);
}

PredictionOutput Spell::get_prediction(GameObject* target, bool aoe, const std::vector<CollisionObject>& collision, float override_range)
{
	PredictionInput input;

	input._from = this->from.is_valid() ? this->from : local_player->get_position();
	input._range_check_from = this->range_check_from.is_valid() ? this->range_check_from : input._from;
	input.unit = target;
	input.delay = this->_delay;
	input.radius = this->_radius;
	input.speed = this->_speed;
	input.collision_objects = collision.empty() ? this->collision_objects : collision;
	input.range = override_range > 0 ? override_range : this->range();
	input.type = this->type;
	input.aoe = aoe;
	input.spell_slot = this->slot;
	input.add_bounding = this->type != SkillshotType::Circle;

	return prediction->get_prediction(&input);
}

PredictionOutput Spell::get_prediction(GameObject* target, const Vec3& origin, const Vec3& range_check_from)
{
	PredictionInput input;
	input._from = origin;
	input._range_check_from = range_check_from;
	input.unit = target;
	input.delay = this->_delay;
	input.radius = this->_radius;
	input.speed = this->_speed;
	input.collision_objects = this->collision_objects;
	input.range = this->range();
	input.type = this->type;
	input.aoe = false;
	input.spell_slot = this->slot;
	input.add_bounding = this->type != SkillshotType::Circle;

	return prediction->get_prediction(&input);
}

PredictionOutput Spell::get_prediction_no_collision(GameObject* target, bool aoe, float override_range)
{
	PredictionInput input;

	input._from = this->from.is_valid() ? this->from : local_player->get_position();
	input._range_check_from = this->range_check_from.is_valid() ? this->range_check_from : input._from;
	input.unit = target;
	input.delay = this->_delay;
	input.radius = this->_radius;
	input.speed = this->_speed;
	input.collision_objects = { };
	input.collision = false;
	input.range = override_range > 0 ? override_range : this->range();
	input.type = this->type;
	input.aoe = aoe;
	input.spell_slot = this->slot;
	input.add_bounding = this->type != SkillshotType::Circle;

	return prediction->get_prediction(&input);
}

bool Spell::is_locked()
{
	if (!lock_enabled)
		return false;

	const auto active_spell = local_player->get_active_spell();
	return active_spell && !active_spell->is_auto() && local_player->is_winding_up();
}

bool SpellData::is_auto_reset()
{
	const auto spell_tags = mSpellTags();
	return std::find(spell_tags.begin(), spell_tags.end(), "Trait_AttackReset") != spell_tags.end();
}

namespace AntiGapcloser
{
	
}