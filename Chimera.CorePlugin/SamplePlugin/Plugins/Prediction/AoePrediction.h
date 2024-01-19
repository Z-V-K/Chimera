#pragma once

struct PossibleTarget
{
	Vec2 position;
	GameObject* unit;
};

class AoePrediction
{
public:
	static PredictionOutput predict(PredictionInput* input);
};