#pragma once

#include "../Impl/UI/Menu/MenuItem.h"
#include "../Impl/Singleton/Singleton.h"
#include "../Impl/Vector/Vector.h"
#include "../Imgui/imgui.h"

class AMenuComponent;

enum CenteredFlags_ : int
{
    CenteredFlags_None = 0,
    CenteredFlags_HorizontalLeft = 1,
    CenteredFlags_HorizontalCenter = 2,
    CenteredFlags_HorizontalRight = 4,
    CenteredFlags_VerticalUp = 8,
    CenteredFlags_VerticalCenter = 16,
    CenteredFlags_VerticalDown = 32,
}; typedef int CenteredFlags;

struct Rect
{
    Vec2 start;
    float width;
    float height;

    Rect() : start({ }), width(0.f), height(0.f) { }
    Rect(const Vec2& start, const float width, const float height) : start(start), width(width), height(height) { }
    Rect(const Vec2& start, const Vec2& end) : start(start)
    {
        width = abs(end.x - start.x);
        height = abs(end.y - start.y);
    }

    Vec2 end() const
    {
        return { start.x + width, start.y + height };
    }

    Vec2 get_centered_text(const std::string& text, CenteredFlags flags, bool permashow = false, bool main_title = false) const
    {
        Rect r{ };

        if (permashow)
            ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[1]);
        else if (main_title)
            ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[5]);

        const ImVec2 textSize = ImGui::CalcTextSize(text.c_str());
        if (permashow || main_title)
            ImGui::PopFont();

        r.height = textSize.y;
        r.width = textSize.x;
        return get_center(r, flags);
    }

    Vec2 get_center(const Rect& dimensions, CenteredFlags flags) const
    {
        float x = 0;
        float y = 0;
        if (flags & CenteredFlags_HorizontalLeft)
            x = start.x;
        else if (flags & CenteredFlags_HorizontalCenter)
            x = start.x + (width - dimensions.width) / 2;
        else if (flags & CenteredFlags_HorizontalRight)
            x = start.x - dimensions.width;
        if (flags & CenteredFlags_VerticalUp)
            y = start.y;
        else if (flags & CenteredFlags_VerticalCenter)
            y = start.y + (height - dimensions.height) / 2;
        else if (flags & CenteredFlags_VerticalDown)
            y = end().y - dimensions.height;

        return { x, y };
    }
};

class ThemeUtils : public singleton<ThemeUtils>
{
public:
    Rect get_container_rectangle(AMenuComponent* component, bool force = false);
    bool is_cursor_inside(const Rect& rect);
    float calc_item_width(const AMenuComponent* component);
    Vec2 calc_text_size(const std::string& text);
    Rect get_tooltip_rectangle(MenuItem* component);
    void draw_tooltip(MenuItem* component);
    std::string get_keybind_text_from_int(int key);
};
