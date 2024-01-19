#include "AntiGapcloserManager.h"

AntiGapcloserManager* g_anti_gapcloser = new AntiGapcloserManager();

void AntiGapcloserManager::set_callbacks(
	fn_get_gapcloser_information get_gapcloser_information,
	fn_add_callback add_callback)
{
	_get_gapcloser_information = get_gapcloser_information;
	_add_callback = add_callback;
}

GapCloserInformation AntiGapcloserManager::get_gapcloser_information(GameObject* obj, bool all_dash)
{
	if (_get_gapcloser_information)
		return _get_gapcloser_information(obj, all_dash);

	return GapCloserInformation();
}

bool AntiGapcloserManager::add_callback(gapcloser_event gap_closer)
{
	if (!_add_callback)
		return false;

	return _add_callback(gap_closer);
}

void AntiGapcloserManager::remove_callbacks()
{
	_get_gapcloser_information = nullptr;
	_add_callback = nullptr;
}