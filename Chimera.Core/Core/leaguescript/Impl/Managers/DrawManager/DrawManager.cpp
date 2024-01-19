#include "../pch.h"
#include "../Impl/Managers/DrawManager/DrawManager.h"

#include "../Impl/DirectX/DirectX.h"
#include "../Framework/Rendering/r3dRenderer/r3dRenderer.h"
#include "../Framework/Hud/Minimap/Minimap.h"
#include "../Imgui/imgui.h"
#include "../Imgui/imgui_internal.h"
#include "../Impl/Managers/TextureManager/TextureManager.h"
#include "../Impl/UI/Texture/Texture.h"

#include "../Framework/Hash/LeagueHash.h"

DrawManager* g_draw_manager = new DrawManager();

void DrawManager::screen_rectangle(const Vec2& p1, const Vec2& p2, D3DCOLOR col, float rounding, float thickness, bool filled)
{
	if (!p1.is_valid() && !p2.is_valid())
		return;

	ImVec2 coord1{ p1.x, p1.y };
	ImVec2 coord2{ p2.x, p2.y };
	if (!filled)
		ImGui::GetWindowDrawList()->AddRect(coord1, coord2, col, rounding, 0, thickness);
	else
		ImGui::GetWindowDrawList()->AddRectFilled(coord1, coord2, col, rounding, 0);
}

void DrawManager::rectangle_2points(const Vec3& start, const Vec3& end, D3DCOLOR color, const int width, const float rounding, const float thickness)
{
	if (!start.is_valid() && !end.is_valid())
		return;

	auto dir = Vec3(end.x - start.x, 0, end.z - start.z).normalized();

	const auto leftDir = Vec3(dir.x, dir.y, dir.z).rotate_y(90).scale(static_cast<float>(width));
	const auto rightDir = Vec3(dir.x, dir.y, dir.z).rotate_y(-90).scale(static_cast<float>(width));

	auto p1 = Vec3(start.x + leftDir.x, start.y + leftDir.y, start.z + leftDir.z);
	auto p2 = Vec3(end.x + leftDir.x, end.y + leftDir.y, end.z + leftDir.z);
	auto p3 = Vec3(end.x + rightDir.x, end.y + rightDir.y, end.z + rightDir.z);
	auto p4 = Vec3(start.x + rightDir.x, start.y + rightDir.y, start.z + rightDir.z);

	rectangle_4points(p1, p2, p3, p4, color, thickness);
}

void DrawManager::rectangle_4points(const Vec3& p1, const Vec3& p2, const Vec3& p3, const Vec3& p4, D3DCOLOR color, const float thickness)
{
	if (!p1.is_valid() && !p2.is_valid() && !p3.is_valid() && !p4.is_valid())
		return;

	line(p1, p2, color, thickness);
	line(p2, p3, color, thickness);
	line(p3, p4, color, thickness);
	line(p4, p1, color, thickness);
}

void DrawManager::line(const Vec3& p1, const Vec3& p2, D3DCOLOR col, float thickness)
{
	if (!p1.is_valid() && !p2.is_valid())
		return;

	auto w2sp1 = r3dRenderer::world_to_screen(p1);
	auto w2sp2 = r3dRenderer::world_to_screen(p2);

	if (!w2sp1.is_valid() && !w2sp2.is_valid())
		return;

	ImGui::GetWindowDrawList()->AddLine(ImVec2(w2sp1.x, w2sp1.y), ImVec2(w2sp2.x, w2sp2.y), col, thickness);
}

void DrawManager::screen_line(const Vec2& p1, const Vec2& p2, D3DCOLOR col, float thickness)
{
	if (!p1.is_valid() && !p2.is_valid())
		return;

	ImGui::GetWindowDrawList()->AddLine({ p1.x, p1.y }, { p2.x, p2.y }, col, thickness);
}

void DrawManager::screen_circle(const Vec2& center, const float radius, D3DCOLOR color, const float thickness, const bool filled, const int num_points)
{
	if (!center.is_valid())
		return;
	if (filled)
		ImGui::GetWindowDrawList()->AddCircleFilled(ImVec2(center.x, center.y), radius, color, num_points);
	else
		ImGui::GetWindowDrawList()->AddCircle(ImVec2(center.x, center.y), radius, color, num_points, thickness);
}

void DrawManager::screen_circle_minimap(const Vec2& center, const float radius, D3DCOLOR color, const float thickness, const int num_points)
{
	if (!center.is_valid())
		return;

	const auto& minimapSize = Minimap::get_instance()->get_size();
	const auto& minimapPos = Minimap::get_instance()->get_position();

	// get the square size and position from minimap
	ImVec2 squareSize = ImVec2(minimapSize.x, minimapSize.y);
	ImVec2 squarePos = ImVec2(minimapPos.x, minimapPos.y);

	// calculate the bounds of the square
	ImVec2 squareMin = squarePos;
	ImVec2 squareMax = ImVec2(squarePos.x + squareSize.x, squarePos.y + squareSize.y);

	// check if the square is entirely inside the circle
	bool allCornersInside = true;
	ImVec2 corners[4] = { squareMin, ImVec2(squareMax.x, squareMin.y), squareMax, ImVec2(squareMin.x, squareMax.y) };
	for (int i = 0; i < 4; ++i) {
		ImVec2 diff(corners[i].x - center.x, corners[i].y - center.y);
		float distSquared = diff.x * diff.x + diff.y * diff.y;
		if (distSquared > radius * radius) {
			allCornersInside = false;
			break;
		}
	}

	if (allCornersInside) {
		return;
	}

	const float angleIncrement = (2.0f * IM_PI) / num_points;
	// draw the clipped circle using line segments
	for (int i = 0; i < num_points; ++i) {
		float angle = angleIncrement * i;
		ImVec2 temp1(cosf(angle) * radius, sinf(angle) * radius);
		ImVec2 start(center.x + temp1.x, center.y + temp1.y);

		angle = angleIncrement * (i + 1);
		ImVec2 temp2(cosf(angle) * radius, sinf(angle) * radius);
		ImVec2 end(center.x + temp2.x, center.y + temp2.y);

		// check if both start and end points are inside the square
		bool startInside = start.x >= squareMin.x && start.x <= squareMax.x &&
			start.y >= squareMin.y && start.y <= squareMax.y;
		bool endInside = end.x >= squareMin.x && end.x <= squareMax.x &&
			end.y >= squareMin.y && end.y <= squareMax.y;

		// only draw the line segment if both start and end points are inside the square
		if (startInside && endInside) {
			ImGui::GetWindowDrawList()->AddLine(start, end, color, thickness);
		}
	}
}

void DrawManager::circle(const Vec3& center, const float radius, D3DCOLOR color, const float thickness, bool filled, const int num_points)
{
	Vec3 world_pos(center.x, center.y, center.z);
	for (auto i = 0; i <= num_points; i++) {
		auto angle = (float)i * M_PI * 1.98f / 98.0f;
		world_pos.x = center.x + ImCos(angle) * radius;
		world_pos.z = center.z + ImSin(angle) * radius;
		Vec2 pos = r3dRenderer::world_to_screen(world_pos);

		ImGui::GetWindowDrawList()->PathLineTo(ImVec2(pos.x, pos.y));
	}
	if (!filled)
		ImGui::GetWindowDrawList()->PathStroke(color, 0, thickness);
	else
	{
		ImGui::GetWindowDrawList()->PathFillConvex(color);

		for (auto i = 0; i <= num_points; i++) {
			auto angle = (float)i * M_PI * 1.98f / 98.0f;
			world_pos.x = center.x + ImCos(angle) * radius;
			world_pos.z = center.z + ImSin(angle) * radius;
			Vec2 pos = r3dRenderer::world_to_screen(world_pos);

			ImGui::GetWindowDrawList()->PathLineTo(ImVec2(pos.x, pos.y));
		}
		
		ImColor edge_color = color;
		edge_color.Value.w = std::min(edge_color.Value.w + .1f, 1.f);
		ImGui::GetWindowDrawList()->PathStroke(edge_color, 0, 3.f);
	}
}

void DrawManager::screen_text(const Vec2& pos, const std::string& text, D3DCOLOR color, int font_size)
{
	if (!pos.is_valid())
		return;

	int fontIdx = font_size >= g_dx->fonts.size() ? g_dx->fonts.size() - 1 : (font_size < 1 ? 1 : font_size);

	const auto font = g_dx->fonts.at(fontIdx);

	ImGui::PushFont(font);

	ImGui::GetWindowDrawList()->AddText(ImVec2(pos.x - 1, pos.y - 1), ImColor(0, 0, 0, 150),text.c_str());
	ImGui::GetWindowDrawList()->AddText(ImVec2(pos.x + 1, pos.y + 1), ImColor(0, 0, 0, 150),text.c_str());
	ImGui::GetWindowDrawList()->AddText(ImVec2(pos.x - 1, pos.y + 1), ImColor(0, 0, 0, 150),text.c_str());
	ImGui::GetWindowDrawList()->AddText(ImVec2(pos.x + 1, pos.y - 1), ImColor(0, 0, 0, 150),text.c_str());
	ImGui::GetWindowDrawList()->AddText(ImVec2(pos.x, pos.y), color, text.c_str());

	ImGui::PopFont();
}

void DrawManager::text(const Vec3& pos, const std::string& text, D3DCOLOR color, int font_size)
{
	if (!pos.is_valid())
		return;

	int fontIdx = font_size >= g_dx->fonts.size() ? g_dx->fonts.size() - 1 : (font_size < 1 ? 1 : font_size);
	ImGui::PushFont(g_dx->fonts.at(fontIdx));

	auto w2sPos = r3dRenderer::world_to_screen(pos);

	if (!w2sPos.is_valid())
		return;

	ImGui::GetWindowDrawList()->AddText(ImVec2(w2sPos.x - 1, w2sPos.y - 1), ImColor(0, 0, 0, 150), text.c_str());
	ImGui::GetWindowDrawList()->AddText(ImVec2(w2sPos.x + 1, w2sPos.y + 1), ImColor(0, 0, 0, 150), text.c_str());
	ImGui::GetWindowDrawList()->AddText(ImVec2(w2sPos.x - 1, w2sPos.y + 1), ImColor(0, 0, 0, 150), text.c_str());
	ImGui::GetWindowDrawList()->AddText(ImVec2(w2sPos.x + 1, w2sPos.y - 1), ImColor(0, 0, 0, 150), text.c_str());
	ImGui::GetWindowDrawList()->AddText(ImVec2(w2sPos.x, w2sPos.y), color, text.c_str());

	ImGui::PopFont();
}

void DrawManager::texture(const char* texture_path, const Vec2& pos, const Vec2& size, float rounding, const D3DCOLOR color, const Vec2& uv_min, const Vec2& uv_max)
{
	const Texture* image = nullptr;

	for (auto& img : TextureManager::get().texture_list)
		if (league_hash(texture_path) == img->hash)
			image = img;

	if (!image) {
		g_ctx->mConsole->log_warning(skCrypt("Could not find image %s in icons folder."), texture_path);
		return;
	}

	const auto end = pos + size;
	ImGui::GetWindowDrawList()->AddImageRounded(image->resource_view, { pos.x, pos.y }, { end.x, end.y }, ImVec2(uv_min.x, uv_min.y), ImVec2(uv_max.x, uv_max.y), color, rounding);
}

void DrawManager::texture(std::uint32_t textureHash, const Vec2& pos, const Vec2& size, float rounding, const D3DCOLOR color, const Vec2& uv_min, const Vec2& uv_max)
{
	const Texture* image = nullptr;

	for (auto& img : TextureManager::get().texture_list)
		if (textureHash == img->hash)
			image = img;

	if (!image) {
		g_ctx->mConsole->log_warning(skCrypt("Could not find image hash 0x%X in icons"), textureHash);
		return;
	}

	const auto end = pos + size;
	ImGui::GetWindowDrawList()->AddImageRounded(image->resource_view, { pos.x, pos.y }, { end.x, end.y }, ImVec2(uv_min.x, uv_min.y), ImVec2(uv_max.x, uv_max.y), color, rounding);
}

void DrawManager::texture(PVOID texture_ptr, const Vec2& pos, const Vec2& size, float rounding, const D3DCOLOR color, const Vec2& uv_min, const Vec2& uv_max)
{
	if (!texture_ptr)
	{
		g_ctx->mConsole->log_warning(skCrypt("[DrawManager::texture] texture nullptr"));
		return;
	}

	const auto end = pos + size;
	ImGui::GetWindowDrawList()->AddImageRounded(texture_ptr, { pos.x, pos.y }, { end.x, end.y }, ImVec2(uv_min.x, uv_min.y), ImVec2(uv_max.x, uv_max.y), color, rounding);
}

void DrawManager::texture_lua(LuaTexture texture_ptr, const Vec2& pos, const Vec2& size, float rounding, const D3DCOLOR color, const Vec2& uv_min, const Vec2& uv_max)
{
	texture(texture_ptr.texture, pos, size, rounding, color, uv_min, uv_max);
}

uint32_t DrawManager::rgba(int r, int g, int b, int a)
{
	ImColor col(r, g, b, a);
	return (uint32_t) col;
}

Vec2 DrawManager::calc_text_size(const std::string& text, int font_size)
{
	int fontIdx = font_size >= g_dx->fonts.size() ? g_dx->fonts.size() - 1 : (font_size < 1 ? 1 : font_size);
	ImGui::PushFont(g_dx->fonts.at(fontIdx));

	auto ret = ImGui::CalcTextSize(text.c_str());

	ImGui::PopFont();

	return Vec2{ ret.x, ret.y };
}

void DrawManager::screen_arc(const Vec2& center, const float radius, const float a1, const float a2, const D3DCOLOR color, const float thickness)
{
	ImGui::GetWindowDrawList()->PathArcTo({ center.x, center.y }, radius, a1, a2);
	ImGui::GetWindowDrawList()->PathStroke(color, 0, thickness);
}

void DrawManager::arc(const Vec3& center, const float radius, const float a1, const float a2, const D3DCOLOR color, const float thickness)
{

	ImGui::GetWindowDrawList()->PathArcTo({center.x, center.z}, radius, a1, a2);

	ImVector<ImVec2>& path = ImGui::GetWindowDrawList()->_Path;

	for (int i = 0; i < path.size(); ++i)
	{
		Vec3 world_pos = { path[i].x, center.y, path[i].y };
		Vec2 pos = r3dRenderer::world_to_screen(world_pos);
		path[i] = ImVec2(pos.x, pos.y);
	}
	ImGui::GetWindowDrawList()->PathStroke(color, 0, thickness);
}

void DrawManager::menu_text(const Vec2& pos, const std::string& text, D3DCOLOR color, bool permashow, bool main_title)
{	
	if (!pos.is_valid())
		return;

	auto font = permashow ? ImGui::GetIO().Fonts->Fonts[1] : ImGui::GetIO().Fonts->Fonts[0];

	if (main_title)
		font = ImGui::GetIO().Fonts->Fonts[5];

	ImGui::PushFont(font);

	auto title = (const char*)xorstr_(u8"키메라");

	ImGui::GetWindowDrawList()->AddText(ImVec2(pos.x, pos.y), color, main_title ? title : text.c_str());

	ImGui::PopFont();
}
