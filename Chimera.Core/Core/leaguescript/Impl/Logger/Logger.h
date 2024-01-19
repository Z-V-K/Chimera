#pragma once

#include "../Impl/Common/Common.h"

class Log
{
public:
	static void init();
	static void un_init();
	static void console();
	static void msg(const char* fmt, ...);
	static void error(const char* fmt, ...);
	static void fatal(const char* fmt, ...);
	static void debug(const char* fmt, ...);
	static void warning(const char* fmt, ...);
private:
	static void init_log();
	static void write_log(const char* Section, const char* Data, bool Error, bool Fatal);
};
