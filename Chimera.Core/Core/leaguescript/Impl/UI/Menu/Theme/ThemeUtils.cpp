#include "../Impl/UI/Menu/Theme/ThemeUtils.h"

#include "../Impl/UI/Menu/AMenuComponent.h"
#include "../Impl/DirectX/DirectX.h"
#include "../Impl/Managers/DrawManager/DrawManager.h"
#include "../Impl/UI/Menu/MenuSettings.h"

inline const char* KeyNames[] = {
    "None",
    "MB1",
    "MB2",
    "CANCEL",
    "MB3",
    "MB4",
    "MB5",
    "Unk",
    "BACK",
    "TAB",
    "Unk",
    "Unk",
    "CLEAR",
    "RETN",
    "Unk",
    "Unk",
    "SHIFT",
    "CTL",
    "ALT",
    "PAUSE",
    "CPTL",
    "KANA",
    "Unk",
    "JUNJA",
    "FINAL",
    "KANJI",
    "Unk",
    "ESC",
    "CONVERT",
    "NONCONVERT",
    "ACCEPT",
    "MODECHANGE",
    "SPACE",
    "PRIOR",
    "NEXT",
    "END",
    "HOME",
    "LEFT",
    "UP",
    "RIGHT",
    "DOWN",
    "SELECT",
    "PRINT",
    "EXCE",
    "SNAP",
    "INS",
    "DEL",
    "HELP",
    "0",
    "1",
    "2",
    "3",
    "4",
    "5",
    "6",
    "7",
    "8",
    "9",
    "Unk",
    "Unk",
    "Unk",
    "Unk",
    "Unk",
    "Unk",
    "Unk",
    "A",
    "B",
    "C",
    "D",
    "E",
    "F",
    "G",
    "H",
    "I",
    "J",
    "K",
    "L",
    "M",
    "N",
    "O",
    "P",
    "Q",
    "R",
    "S",
    "T",
    "U",
    "V",
    "W",
    "X",
    "Y",
    "Z",
    "LWIN",
    "RWIN",
    "APPS",
    "Unk",
    "SLEEP",
    "NUM0",
    "NUM1",
    "NUM2",
    "NUM3",
    "NUM4",
    "NUM5",
    "NUM6",
    "NUM7",
    "NUM8",
    "NUM9",
    "MULT",
    "ADD",
    "SEP",
    "SUB",
    "DEC",
    "DIV",
    "F1",
    "F2",
    "F3",
    "F4",
    "F5",
    "F6",
    "F7",
    "F8",
    "F9",
    "F10",
    "F11",
    "F12",
    "F13",
    "F14",
    "F15",
    "F16",
    "F17",
    "F18",
    "F19",
    "F20",
    "F21",
    "F22",
    "F23",
    "F24",
    "Unk",
    "Unk",
    "Unk",
    "Unk",
    "Unk",
    "Unk",
    "Unk",
    "Unk",
    "NUMLOCK",
    "SCROLL",
    "NEC_EQUAL",
    "FJ_MASSHOU",
    "FJ_TOUROKU",
    "FJ_LOYA",
    "FJ_ROYA",
    "Unk",
    "Unk",
    "Unk",
    "Unk",
    "Unk",
    "Unk",
    "Unk",
    "Unk",
    "Unk",
    "LSHFT",
    "RSHFT",
    "LCTL",
    "RCTL",
    "LMENU",
    "RMENU"
};

Rect ThemeUtils::get_container_rectangle(AMenuComponent* component, bool force)
{
    return { { component->position.x, component->position.y }, component->get_menu_width(force), MenuSettings::get().container_height };
}

bool ThemeUtils::is_cursor_inside(const Rect& rect)
{
    const auto cursorPos = ImGui::GetMousePos();
    return cursorPos.x >= rect.start.x && cursorPos.x <= rect.end().x && cursorPos.y >= rect.start.y && cursorPos.y <= rect.end().y;
}

float ThemeUtils::calc_item_width(const AMenuComponent* component)
{
    return calc_text_size(component->display_name).x + MenuSettings::get().container_text_offset + 10.f;
}

Vec2 ThemeUtils::calc_text_size(const std::string& text)
{
    ImGui::PushFont(g_dx->menu_font);
    ImVec2 ret = ImGui::CalcTextSize(text.c_str());
    ImGui::PopFont();

    return { ret.x, ret.y };
}

Rect ThemeUtils::get_tooltip_rectangle(MenuItem* component)
{
    const auto container = get_container_rectangle(component);

    const float textWidth = calc_text_size(component->tooltip).x + MenuSettings::get().container_text_offset + 10.f;
    const float xStart = container.end().x + MenuSettings::get().tabs_margin;
    return { { xStart, container.start.y }, textWidth + 10.f, MenuSettings::get().container_height };
}

void ThemeUtils::draw_tooltip(MenuItem* component)
{
    const Rect tooltipRect = ThemeUtils::get().get_tooltip_rectangle(component);
    g_draw_manager->screen_rectangle(tooltipRect.start, tooltipRect.end(), MenuSettings::get().tab_color->get_color(), 2, 1, true);
    g_draw_manager->screen_rectangle(tooltipRect.start, tooltipRect.end(), MenuSettings::get().tab_border_color->get_color(), 2, MenuSettings::get().border_width);

    const auto centeredInTooltip = tooltipRect.get_centered_text(component->tooltip, CenteredFlags_HorizontalCenter | CenteredFlags_VerticalCenter);
    g_draw_manager->menu_text({ tooltipRect.start.x + MenuSettings::get().container_icon_offset, centeredInTooltip.y + 1.f }, ICON_FA_INFO_CIRCLE, MenuSettings::get().text_color->get_color());
    g_draw_manager->menu_text({ tooltipRect.start.x + MenuSettings::get().container_text_offset, centeredInTooltip.y }, component->tooltip, MenuSettings::get().text_color->get_color());
}

std::string ThemeUtils::get_keybind_text_from_int(int key)
{
    return KeyNames[key];
}