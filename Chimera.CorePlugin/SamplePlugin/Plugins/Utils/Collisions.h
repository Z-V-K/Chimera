#pragma once

struct Windwall
{
	GameObject* src{};
	GameObject* p1{};
	GameObject* p2{};
	int width{ 90 };
};

class Collisions
{
public:
	static inline int wall_cast_t = 0;
	static inline bool yasuo_in_game = false;
	static inline bool samira_in_game = false;
	static inline std::unordered_map<unsigned int, Windwall> windwalls{ };

	static void initialize();
	static std::vector<GameObject*> get_collision(const std::vector<Vec3>& positions, PredictionInput* input);
	static bool is_collision(const std::vector<Vec3>& positions, PredictionInput* input);
	static bool has_yasuo_windwall_collision(const Vec3& start, const Vec3& end);
	static bool has_yasuo_windwall_collision(const Vec3& start, const Vec3& end, float extra_radius);
	static bool will_die(PredictionInput* input, GameObject* minion, float distance);
	static void on_create(GameObject* obj);
	static void on_delete(GameObject* obj);
	static void on_process_spell_cast(SpellCastInfo* spell);
};