#include "../pch.h"
#include "../Impl/Input/Input.h"

#include "../../Framework/Hud/Hud/Hud.h"
#include "../../Framework/Rendering/r3dRenderer/r3dRenderer.h"
#include "../Framework/Hud/Chat/Chat.h"

#include "../Imgui/imgui.h"

Input* g_input = new Input();

bool Input::is_key_down(uint32_t key)
{
	return core_is_key_down(key);
}

bool Input::is_key_up(uint32_t key)
{
	return core_is_key_up(key);
}

bool Input::is_key_pressed(uint32_t key)
{
	return core_is_key_pressed(key);
}

Vec2 Input::get_cursor_screen_position()
{
	return core_get_cursor_screen_position();
}

bool Input::core_is_key_down(uint32_t key)
{
	if (Chat::instance()->is_open())
		return false;

	if (key < 0x01)
		return false;

	if (key >= 0x01 && key <= 0x06)
	{
		switch (key)
		{
		case 0x01:
			return ImGui::IsMouseDown(0);
		case 0x02:
			return ImGui::IsMouseDown(1);
		case 0x04:
			return ImGui::IsMouseDown(2);
		case 0x05:
			return ImGui::IsMouseDown(3);
		case 0x06:
			return ImGui::IsMouseDown(4);
		}
	}

	return ImGui::IsKeyDown(key);
}

bool Input::core_is_key_pressed(uint32_t key)
{
	if (Chat::instance()->is_open())
		return false;

	if (key < 0x01)
		return false;

	if (key >= 0x01 && key <= 0x06)
	{
		switch (key)
		{
		case 0x01:
			return ImGui::IsMouseClicked(0);
		case 0x02:
			return ImGui::IsMouseClicked(1);
		case 0x04:
			return ImGui::IsMouseClicked(2);
		case 0x05:
			return ImGui::IsMouseClicked(3);
		case 0x06:
			return ImGui::IsMouseClicked(4);
		}
	}

	return ImGui::IsKeyPressed(key);
}

bool Input::core_is_key_up(uint32_t key)
{
	if (Chat::instance()->is_open())
		return false;

	if (key < 0x01)
		return false;

	if (key >= 0x01 && key <= 0x06)
	{
		switch (key)
		{
		case 0x01:
			return ImGui::IsMouseReleased(0);
		case 0x02:
			return ImGui::IsMouseReleased(1);
		case 0x04:
			return ImGui::IsMouseReleased(2);
		case 0x05:
			return ImGui::IsMouseReleased(3);
		case 0x06:
			return ImGui::IsMouseReleased(4);
		}
	}

	return ImGui::IsKeyReleased(key);
}

Vec2 Input::core_get_cursor_screen_position()
{
	const auto iPos = ImGui::GetMousePos();
	Vec2 pos{ iPos.x, iPos.y };

	return pos.is_visible_on_screen() ? pos : Vec2{ 0.f, 0.f };
}