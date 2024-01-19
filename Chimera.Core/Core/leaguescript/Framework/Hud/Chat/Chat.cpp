#include "../pch.h"
#include "Chat.h"

#include "../Impl/Hooks/retspoof/x64RetSpoof.h"

Chat* Chat::instance()
{
	return RVA_CAST(Chat*, Addresses::Chat::ChatClient);
}

void* Chat::menu_gui()
{
	return RVA_CAST(Chat*, Addresses::Chat::MenuGui);
}

bool Chat::is_open()
{
	// chat closed -> value = 0. When chat open, value = nb times it was open
	return get_times_open() != 0;
}

void Chat::print_chat(const std::string& message)
{
	typedef void(__fastcall* fnPrintChat)(uintptr_t, const char*, int);
	static fnPrintChat fn = (fnPrintChat) MAKE_RVA(Addresses::Chat::PrintChat);

	x64RetSpoof::spoof_call(fn, (uintptr_t) MAKE_RVA(Addresses::Chat::ChatInstance), message.c_str(), 64);
}

void Chat::send_chat(std::string& message, bool all_chat)
{
	if (all_chat)
		message = std::string(skCrypt("/all ")) + message;

	typedef void(__fastcall* fnSendChat)(uintptr_t, const char*, int);
	static fnSendChat fn = (fnSendChat)MAKE_RVA(Addresses::Chat::SendChat);

	x64RetSpoof::spoof_call(fn, (uintptr_t)menu_gui(), message.c_str(), 0);
}

const Vec2& Chat::get_position()
{
	return RVA_CAST_THIS(Vec2, Structures::Chat::Position);
}

int Chat::get_times_open()
{
	return RVA_CAST_THIS(int, Structures::Chat::TimesOpen);
}