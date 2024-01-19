#pragma once

#include "../Framework/GameObjects/GameObject/GameObject.h"

enum class GapCloserType
{
	Skillshot,
	Targeted,
	Item
};

struct GapCloserInformation
{
	GapCloserType type = GapCloserType::Skillshot;
	GameObject* sender = nullptr;
	GameObject* target = nullptr;

	float start_time = 0.f;
	float end_time = 0.f;
	float speed = 0.f;

	Vec3 start_position{ };
	Vec3 end_position{ };

	bool is_unstoppable = false;
	bool is_cc = false;
};

typedef void(*gapcloser_event)(GapCloserInformation* gap_closer);

class AntiGapcloserManager
{
	typedef GapCloserInformation(*fn_get_gapcloser_information)(GameObject*, bool);
	typedef bool(*fn_add_callback)(gapcloser_event);
private:
	fn_get_gapcloser_information _get_gapcloser_information = nullptr;
	fn_add_callback _add_callback = nullptr;
public:
	virtual void set_callbacks(
		fn_get_gapcloser_information get_gapcloser_information,
		fn_add_callback add_callback
	);

	virtual GapCloserInformation get_gapcloser_information(GameObject* obj, bool all_dash);
	virtual bool add_callback(gapcloser_event gap_closer);

	void remove_callbacks();
};

extern AntiGapcloserManager* g_anti_gapcloser;