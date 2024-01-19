#pragma once

namespace Activator
{
	class OffensiveItems : public Singleton<OffensiveItems>
	{
		MenuItem* enable{};
	public:
		void initialize();
		void on_unload();
	};
}