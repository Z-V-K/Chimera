#pragma once

class Prediction
{
public:
    static void initialize();

    static PredictionOutput get_prediction(PredictionInput* input);

    static PredictionOutput get_prediction_internal(PredictionInput* input, bool aoe, bool check_collision);
    static bool get_dashing_prediction(PredictionInput* input, PredictionOutput* output);
    static bool get_immobile_prediction(PredictionInput* input, PredictionOutput* output, double remaining_immobile_time);
    static double unit_immobile_until(GameObject* unit);
    static bool get_position_on_path(PredictionInput* input, PredictionOutput* output, std::vector<Vec2> path, const float path_length, float speed = -1.f, bool fix_speed = false);
    static HitChance get_hitchance(GameObject* unit);
};
