#pragma once

namespace Activator
{
	class Misc : public Singleton<Misc>
	{
		MenuItem* enable{};
	public:
		void initialize();
		void on_unload();
	};
}