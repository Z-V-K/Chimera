#include "Debug.h"

#include "../Awareness/Colors.h"
#include "../Prediction/Prediction.h"

Spell *Q, *W, *E, *R;
Vec3 last_cast_spell_pos;

void Debug::initialize()
{
	callbacks<EventType::OnTick>::add_callback(on_tick, "Debug");
	callbacks<EventType::OnDraw>::add_callback(on_draw, "Debug");

	Q = sdk->register_spell(SlotId::Q, 1000, DamageType::Physical);
	Q->set_skillshot(.25f + .528f, 125.f / 2.f, FLT_MAX, { CollisionObject::Heroes, CollisionObject::Minions, CollisionObject::YasuoWall }, SkillshotType::Line);

	W = sdk->register_spell(SlotId::W, 1200, DamageType::Physical);
	W->set_skillshot(.25f, 120.f / 2.f, 2000.f, { CollisionObject::Heroes, CollisionObject::Minions, CollisionObject::YasuoWall }, SkillshotType::Line);

	E = sdk->register_spell(SlotId::E, 1200, DamageType::Physical);
	R = sdk->register_spell(SlotId::R, 1200, DamageType::Physical);
}

void Debug::on_unload()
{

}

void Debug::on_tick()
{
	
}

const char* hitchance_str[]
{
	"OutOfRange",
	"Collision",
	"Impossible",
	"Low",
	"Medium",
	"High",
	"VeryHigh",
	"Dashing",
	"Immobile"
};

void Debug::on_draw()
{
	const auto target = target_selector->get_target(Q->range(), DamageType::Physical);

	if (!target)
		return;

	const auto pred = Q->get_prediction(target);

	//draw_manager->rectangle_2points(local_player->get_position(), pred.cast_position(), Colors::SpellTracker::lime, Q->_radius, 4.f);
	draw_manager->circle(pred.cast_position(), Q->_radius, Color(255, 255, 0, 90), 1, true);
	draw_manager->circle(pred.unit_position(), 50.f, Color(255, 0, 0, 90), 2, false);
	draw_manager->text(target->get_position(), hitchance_str[(int) pred.hit_chance], Color(255, 255, 255), 16.f);

	Vec2 pos = target->get_health_bar_screen_position() + Vec2{ 80, 0.f };
	draw_manager->screen_text(pos, std::format("[Q] {:.2f}", Q->get_damage(target)), Color(255, 255, 255), 15.f);
	draw_manager->screen_text(pos + Vec2{ 0, 15.f }, std::format("[W] {:.0f}", W->get_damage(target)), Color(255, 255, 255), 15.f);
	draw_manager->screen_text(pos + Vec2{ 0, 30.f }, std::format("[E] {:.0f}", E->get_damage(target)), Color(255, 255, 255), 15.f);
	draw_manager->screen_text(pos + Vec2{ 0, 45.f }, std::format("[R] {:.0f}", R->get_damage(target)), Color(255, 255, 255), 15.f);
	draw_manager->screen_text(pos + Vec2{ 0, 60.f }, std::format("[Auto] {:.0f}", (double) dmg_lib->get_auto_attack_damage(local_player, target)), Color(255, 255, 255), 15.f);

	if (Q->is_ready() && pred.hit_chance >= HitChance::High && orbwalker->get_mode() == OrbwalkerMode::Flee)
	{
		//local_player->update_charged_spell(Q->slot, pred.cast_position(), true);
		Q->cast(pred.cast_position());
		//console->log("release!");
	}

	if (last_cast_spell_pos.is_valid())
	{
		draw_manager->circle(last_cast_spell_pos, 20.f, Color(255, 255, 255, 120), 3.f, true);
		draw_manager->text(last_cast_spell_pos, "last_cast", Color(255, 255, 255, 120), 12);
	}
}