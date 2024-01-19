#pragma once

#include "../Impl/UI/Menu/MenuSettings.h"
#include "../Impl/Vector/Vector.h"
#include "../Impl/Singleton/Singleton.h"
#include "../SDK/LUA/LuaTexture.h"

#define MAKE_COLOR(r,g,b,a) D3DCOLOR_ARGB(a,b,g,r)

#define GET_A(c) ((c>>24)&0xFF)
#define GET_R(c) ((c>>16)&0xFF)
#define GET_G(c) ((c>>8)&0xFF)
#define GET_B(c) (c&255)

class DrawManager
{
public:
	virtual void screen_rectangle(const Vec2& p1, const Vec2& p2, D3DCOLOR col, float rounding = 0.f, float thickness = 1.f, bool filled = false);
	virtual void rectangle_2points(const Vec3& start, const Vec3& end, D3DCOLOR color, const int width, const float rounding = 0.f, const float thickness = 0.f);
	virtual void rectangle_4points(const Vec3& p1, const Vec3& p2, const Vec3& p3, const Vec3& p4, D3DCOLOR color, const float thickness = 1.f);
	virtual void line(const Vec3& p1, const Vec3& p2, D3DCOLOR col, float thickness = 1.f);
	virtual void screen_line(const Vec2& p1, const Vec2& p2, D3DCOLOR col, float thickness = 1.f);
	virtual void screen_text(const Vec2& pos, const std::string& text, D3DCOLOR color, int font_size = MenuSettings::get().font_size);
	virtual void text(const Vec3& pos, const std::string& text, D3DCOLOR color, int font_size);
	virtual void texture(const char* texture_path, const Vec2& pos, const Vec2& size, float rounding, const D3DCOLOR color = 0xFFFFFFFF, const Vec2& uv_min = Vec2(0, 0), const Vec2& uv_max = Vec2(1, 1));
	virtual void texture(std::uint32_t texture_hash, const Vec2& pos, const Vec2& size, float rounding, const D3DCOLOR color = 0xFFFFFFFF, const Vec2& uv_min = Vec2(0, 0), const Vec2& uv_max = Vec2(1, 1));
	virtual void texture(PVOID texture_ptr, const Vec2& pos, const Vec2& size, float rounding, const D3DCOLOR color = 0xFFFFFFFF, const Vec2& uv_min = Vec2(0, 0), const Vec2& uv_max = Vec2(1, 1));
	void texture_lua(LuaTexture texture_ptr, const Vec2& pos, const Vec2& size, float rounding, const D3DCOLOR color = 0xFFFFFFFF, const Vec2& uv_min = Vec2(0, 0), const Vec2& uv_max = Vec2(1, 1));
	uint32_t rgba(int r, int g, int b, int a);
	virtual void screen_circle(const Vec2& center, const float radius, D3DCOLOR color, const float thickness = 1.f, const bool filled = false, const int num_points = 99);
	virtual void screen_circle_minimap(const Vec2& center, const float radius, D3DCOLOR color, const float thickness = 1.f, const int num_points = 99);
	virtual void circle(const Vec3& center, const float radius, D3DCOLOR color, const float thickness = 1.f, bool filled = false, const int num_points = 99);
	virtual void screen_arc(const Vec2& center, const float radius, const float a1, const float a2, const D3DCOLOR color, const float thickness = 1.f);
	virtual void arc(const Vec3& center, const float radius, const float a1, const float a2, const D3DCOLOR color, const float thickness = 1.f);
	virtual Vec2 calc_text_size(const std::string& text, int font_size);

	void menu_text(const Vec2& pos, const std::string& text, D3DCOLOR color, bool permashow = false, bool main_title = false);
};

extern DrawManager* g_draw_manager;