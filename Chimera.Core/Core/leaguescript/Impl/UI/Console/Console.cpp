#include "../pch.h"
#include "Console.h"

#include "../Imgui/imgui.h"
#include "../Imgui/Fontawesome5Icons.h"

std::string getHourMinutesSeconds() {
	struct tm tstruct;
	time_t now = time(0);
	localtime_s(&tstruct, &now);

	char buf[10];
	std::strftime(buf, sizeof(buf), skCrypt("%H:%M:%S"), &tstruct);

	return buf;
}

ImVec4 rgbaToVec4(float r, float g, float b, float a) {
	return ImVec4(r / 255.f, g / 255.f, b / 255.f, a / 255.f);
}

float clamp(float n, float min, float max) {
	return (std::max)(min, (std::min)(n, max));
}

void Console::render_log(Output& output) {
	if (output.type != MessageType::Log) return;
	std::string& print = output.text;
	if (output.draw_time) print = "[" + output.time + "] " + print;

	ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[4]);
	ImGui::TextUnformatted(print.c_str());
	ImGui::PopFont();
}
void Console::render_log_error(Output& output) {
	if (output.type != MessageType::Error) return;
	std::string& print = output.text;
	if (output.draw_time) print = "[" + output.time + "] " ICON_FA_TIMES_CIRCLE + " " + print;
	ImVec4 color = rgbaToVec4(255, 152, 172, 255);

	ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[4]);
	ImGui::PushStyleColor(ImGuiCol_Text, color);
	ImGui::TextUnformatted(print.c_str());
	ImGui::PopStyleColor();
	ImGui::PopFont();
}

void Console::render_log_info(Output& output) {
	if (output.type != MessageType::Info) return;
	std::string print = output.text;
	if (output.draw_time) print = "[" + output.time + "] " ICON_FA_INFO_CIRCLE + " " + print;
	ImVec4 color = rgbaToVec4(122, 202, 242, 255);

	ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[4]);
	ImGui::PushStyleColor(ImGuiCol_Text, color);
	ImGui::TextUnformatted(print.c_str());
	ImGui::PopStyleColor();
	ImGui::PopFont();
}

void Console::render_log_warning(Output& output) {
	if (output.type != MessageType::Warning) return;
	std::string& print = output.text;
	if (output.draw_time) print = "[" + output.time + "] " ICON_FA_EXCLAMATION_CIRCLE + " " + print;
	ImVec4 color = rgbaToVec4(234, 143, 28, 255);

	ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[4]);
	ImGui::PushStyleColor(ImGuiCol_Text, color);
	ImGui::TextUnformatted(print.c_str());
	ImGui::PopStyleColor();
	ImGui::PopFont();
}

void Console::render_log_debug(Output& output) {
	if (output.type != MessageType::Debug) return;
	std::string& print = output.text;
	if (output.draw_time) print = "[" + output.time + "] " ICON_FA_CODE + " " + print;
	ImVec4 color = rgbaToVec4(172, 126, 247, 255);

	ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[4]);
	ImGui::PushStyleColor(ImGuiCol_Text, color);
	ImGui::TextUnformatted(print.c_str());
	ImGui::PopStyleColor();
	ImGui::PopFont();
}

void Console::render() {
	if (!DRAW_CONSOLE) return;

	ImGui::PushStyleColor(ImGuiCol_ResizeGrip, (ImVec4)Colors::AccentPrimaryDisabled);
	ImGui::PushStyleColor(ImGuiCol_ResizeGripActive, (ImVec4)Colors::AccentPrimary);
	ImGui::PushStyleColor(ImGuiCol_ResizeGripHovered, (ImVec4)Colors::AccentPrimary);

	ImGui::SetNextWindowSize({ 500, 400 }, ImGuiCond_FirstUseEver);
	ImGui::Begin("   ", 0, ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);

	ImGui::BeginChild(skCrypt("ScrollingRegion"), ImVec2(0, 0), true, ImGuiWindowFlags_HorizontalScrollbar);
	{
		for (int i = 0; i < output_arr.size(); i++) { // draw output
			Output output = output_arr.at(i);

			render_log(output);
			render_log_error(output);
			render_log_info(output);
			render_log_debug(output);
			render_log_warning(output);
		}

		if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY()) ImGui::SetScrollHereY(1.0f); // scroll down automatically
	}
	ImGui::EndChild();
	ImGui::End();

	ImGui::PopStyleColor(3);
}

void Console::clear()
{
	output_arr.clear();
}

void Console::log(const char* text, ...) 
{
	char buf[1024];
	va_list args;
	va_start(args, text);
	vsnprintf(buf, IM_ARRAYSIZE(buf), text, args);
	buf[IM_ARRAYSIZE(buf) - 1] = 0;
	va_end(args);

	Output output{ buf, true, MessageType::Log };
	output.time = getHourMinutesSeconds();

	if (output_arr.size() > 500)
		output_arr.erase(output_arr.begin());

	output_arr.push_back(output);
}

void Console::log_warning(const char* text, ...) {
	char buf[1024];
	va_list args;
	va_start(args, text);
	vsnprintf(buf, IM_ARRAYSIZE(buf), text, args);
	buf[IM_ARRAYSIZE(buf) - 1] = 0;
	va_end(args);

	Output output{ std::string{buf}, true, MessageType::Warning };
	output.time = getHourMinutesSeconds();

	if (output_arr.size() > 500)
		output_arr.erase(output_arr.begin());

	output_arr.push_back(output);
}

void Console::log_error(const char* text, ...) {
	char buf[1024];
	va_list args;
	va_start(args, text);
	vsnprintf(buf, IM_ARRAYSIZE(buf), text, args);
	buf[IM_ARRAYSIZE(buf) - 1] = 0;
	va_end(args);

	Output output{ std::string{buf}, true, MessageType::Error };
	output.time = getHourMinutesSeconds();

	if (output_arr.size() > 500)
		output_arr.erase(output_arr.begin());

	output_arr.push_back(output);
}

void Console::log_debug(const char* text, ...) {
	char buf[1024];
	va_list args;
	va_start(args, text);
	vsnprintf(buf, IM_ARRAYSIZE(buf), text, args);
	buf[IM_ARRAYSIZE(buf) - 1] = 0;
	va_end(args);

	Output output{ std::string{buf}, true, MessageType::Debug };
	output.time = getHourMinutesSeconds();

	if (output_arr.size() > 500)
		output_arr.erase(output_arr.begin());

	output_arr.push_back(output);
}

void Console::log_info(const char* text, ...) {
	char buf[1024];
	va_list args;
	va_start(args, text);
	vsnprintf(buf, IM_ARRAYSIZE(buf), text, args);
	buf[IM_ARRAYSIZE(buf) - 1] = 0;
	va_end(args);

	Output output{ std::string{buf}, true, MessageType::Info };
	output.time = getHourMinutesSeconds();

	if (output_arr.size() > 500)
		output_arr.erase(output_arr.begin());

	output_arr.push_back(output);
}

void Console::__EXPORTlog(const std::string& msg)
{
	log(msg.c_str());
}

void Console::__EXPORTdbg(const std::string& msg)
{
	log_debug(msg.c_str());
}

void Console::__EXPORTerr(const std::string& msg)
{
	log_error(msg.c_str());
}

void Console::__EXPORTwarn(const std::string& msg)
{
	log_warning(msg.c_str());
}

void Console::__EXPORTinfo(const std::string& msg)
{
	log_info(msg.c_str());
}