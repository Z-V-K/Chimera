#include "PredictionManager.h"

PredictionManager* g_prediction_manager = new PredictionManager();

void PredictionManager::set_callbacks(
	fn_get_prediction get_prediction)
{
	_get_prediction = get_prediction;
}

PredictionOutput PredictionManager::get_prediction(PredictionInput* input)
{
	if (_get_prediction)
		return _get_prediction(input);

	return { };
}

void PredictionManager::remove_callbacks()
{
	_get_prediction = nullptr;
}
