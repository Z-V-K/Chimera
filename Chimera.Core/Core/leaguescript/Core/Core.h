#pragma once

class HookManager;

class Core {
public:
	std::shared_ptr<HookManager> m_hookManager;

	Core();

	std::shared_ptr<HookManager> get_hook_manager() const;

	void run();
	bool apply_hooks() const;
	void load_features() const;
	void unload() const;
};

extern std::shared_ptr<Core> m_core;