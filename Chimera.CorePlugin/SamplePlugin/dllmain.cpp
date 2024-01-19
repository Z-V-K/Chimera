#include "Plugins/Plugin.h"

SCRIPT_NAME("Core")
SCRIPT_TYPE(ScriptType::Core)
SUPPORTED_CHAMPS(CharacterHash::Unknown)

SCRIPT_EXPORT bool on_load_sdk(SDK* sdk)
{
	if (!sdk->initialize())
		return false;

	Plugin::on_load();

	return true;
}

SCRIPT_EXPORT void on_unload_sdk()
{
	Plugin::on_unload();
}