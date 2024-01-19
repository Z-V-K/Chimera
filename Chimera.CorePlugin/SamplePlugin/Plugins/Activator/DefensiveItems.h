#pragma once

namespace Activator
{
	class DefensiveItems : public Singleton<DefensiveItems>
	{
		MenuItem* enable{};
	public:
		void initialize();
		void on_unload();
	};
}