#include "../pch.h"
#include "../Impl/Common/Utils.h"

#include "../Imgui/imgui.h"
std::string Utils::to_lower_case(const std::string_view& str)
{
	std::string strLower;
	strLower.resize(str.size());

	std::transform(str.begin(),
		str.end(),
		strLower.begin(),
		::tolower);

	return strLower;
}

bool Utils::is_valid_string(const char* str)
{
	for (int i = 0; i < 10; ++i)
	{
		if (str[i] == 0)
			return true;
		if ((unsigned char)str[i] > 127)
			return false;
	}

	return true;
}

void Utils::message_box_ptr(uintptr_t ptr)
{
	MessageBoxA(nullptr, std::format("{:#x}", ptr).c_str(), "", MB_OK);
}

uint32_t Utils::imcolor_to_hex(ImColor col)
{
	int r = (int) (col.Value.x * 255);
	int g = (int) (col.Value.y * 255);
	int b = (int) (col.Value.z * 255);
	int a = (int) (col.Value.w * 255);

	return D3DCOLOR_ARGB(a, r, g, b);
}