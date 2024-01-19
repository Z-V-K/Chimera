#pragma once
#include "../../../SDK/LUA/LuaTexture.h"
#include "../Impl/Vector/Vector.h"
#include "../Impl/Common/Common.h"
#include "../Framework/Enums/DirectXVersionEnum.h"

class r3dRenderer final
{
public:
	Enums::DirectXVersion get_dx_version();

	inline static HWND game_hwnd;

	static r3dRenderer* instance();

	static bool apply_hooks();
	static void remove_hwnd_hook();

	virtual Vec2 get_renderer_size();
	virtual Vec2 exported_world_to_screen(const Vec3& in);
	virtual Vec2 exported_world_to_minimap(const Vec3& in);
	virtual PVOID get_texture_from_game(const std::string& name);
	LuaTexture get_texture_from_game_lua(const std::string& name);

	static D3DMATRIX calculate_view_projection_matrix();
	static Vec2 world_to_screen(const Vec3& position);
	static Vec2 world_to_minimap(const Vec3& in);
};

extern r3dRenderer* g_renderer;