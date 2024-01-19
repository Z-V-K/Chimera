#include "../pch.h"
#include "Context.h"

Context* g_ctx = new Context();

std::string Context::get_root_path()
{
	PWSTR path;
	const auto result = SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, nullptr, &path);

    if (result != S_OK) {
        CoTaskMemFree(path);
        return "";
    }

    char str[256];
    wcstombs(str, path, 256);
    return str + std::string(skCrypt("\\Chimera\\"));
}
