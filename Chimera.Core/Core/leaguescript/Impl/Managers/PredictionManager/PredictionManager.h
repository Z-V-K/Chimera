#pragma once

#include "../Framework/GameObjects/GameObject/GameObject.h"

enum class CollisionObject
{
	Minions,
	Heroes,
	Allies,
	YasuoWall, // yasuo, samira
	GameWall,
};

enum class HitChance
{
	OutOfRange,
	Collision,
	Impossible,
	Low,
	Medium,
	High,
	VeryHigh,
	Dashing,
	Immobile
};

enum class SkillshotType : int {
	Line,
	Circle,
	Cone
};

struct PredictionInput
{
	Vec3 _from;
	Vec3 _range_check_from;
	bool add_bounding = true;
	bool aoe;
	bool collision = true;
	std::vector<CollisionObject> collision_objects{ };
	float delay = 0.f;
	float radius = 1.f;
	float range = FLT_MAX;
	float speed = FLT_MAX;
	SkillshotType type = SkillshotType::Line;
	Enums::SpellSlot spell_slot = Enums::SpellSlot::Unknown;
	GameObject* unit = nullptr;

	Vec3 from() const
	{
		return  _from;
	};

	Vec3 range_check_from() const
	{
		return from();
	}

	float real_radius() const
	{
		return !add_bounding ? radius : radius + unit->get_bounding_radius();
	}
};

struct PredictionOutput
{
	PredictionInput* input;

	Vec3 _cast_position;
	Vec3 _unit_position;

	std::vector<GameObject*> collision_objects;
	HitChance hit_chance = HitChance::Impossible;
	std::vector<GameObject*> aoe_targets_hit;
	int _aoe_targets_hit_count = 0;

	int aoe_targets_hit_count() const
	{
		return std::max(_aoe_targets_hit_count, (int)aoe_targets_hit.size());
	}

	Vec3 cast_position() const
	{
		if (_cast_position.is_valid())
			return _cast_position;

		if (input == nullptr)
			return Vec3();

		return input->unit != nullptr ? input->unit->get_path_controller_common()->get_server_pos() : Vec3();
	}

	Vec3 unit_position() const
	{
		if (_unit_position.is_valid())
			return _unit_position;

		if (input == nullptr)
			return Vec3();

		return input->unit != nullptr ? input->unit->get_path_controller_common()->get_server_pos() : Vec3();
	}
};

class PredictionManager
{
private:
	typedef PredictionOutput(*fn_get_prediction)(PredictionInput*);
	fn_get_prediction _get_prediction = nullptr;
public:
	virtual void set_callbacks(
		fn_get_prediction get_prediction
	);

	virtual PredictionOutput get_prediction(PredictionInput* input);

	void remove_callbacks();
};

extern PredictionManager* g_prediction_manager;