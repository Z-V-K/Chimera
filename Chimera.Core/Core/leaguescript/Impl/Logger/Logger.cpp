#include "../pch.h"
#include "Logger.h"
#include "../Imgui/imgui.h"

#define LOGFILE_NAME skCrypt("internal.log")

#define CHARS_FOR_BUFF 4096
#define CHARS_FOR_PARAMS 3500
char g_LogFile[MAX_PATH];
bool IsConsole = false;
std::ofstream m_Console;

void Log::init()
{
	std::ofstream file;
	file.open(LOGFILE_NAME, std::ios_base::app);
	file.close();
}

void Log::un_init()
{
	FreeConsole();
	m_Console.close();
}

void Log::console()
{
	if (!AttachConsole(GetCurrentProcessId())) AllocConsole();
	SetConsoleTitleW(L"Internal");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);
	m_Console.open(skCrypt("CONOUT$"));
}

void Log::msg(const char* fmt, ...)
{
	char buf[1024];
	va_list args;
	va_start(args, fmt);	
	vsnprintf(buf, IM_ARRAYSIZE(buf), fmt, args);
	buf[IM_ARRAYSIZE(buf) - 1] = 0;
	va_end(args);

	write_log("+", buf, false, false);
}

void Log::error(const char* fmt, ...)
{
	va_list va_alist;
	char chParameters[CHARS_FOR_PARAMS];
	va_start(va_alist, fmt);
	sprintf(chParameters, fmt, va_alist);
	va_end(va_alist);
	write_log("-", chParameters, true, false);
}

void Log::fatal(const char* fmt, ...)
{
	va_list va_alist;
	char chParameters[CHARS_FOR_PARAMS];
	va_start(va_alist, fmt);
	sprintf(chParameters, fmt, va_alist);
	va_end(va_alist);
	write_log("#", chParameters, false, true);
	ExitProcess(0);
}

void Log::debug(const char* fmt, ...)
{
	va_list va_alist;
	char chParameters[CHARS_FOR_PARAMS];
	va_start(va_alist, fmt);
	sprintf(chParameters, fmt, va_alist);
	va_end(va_alist);
	write_log("@", chParameters, false, false);
}

void Log::warning(const char* fmt, ...)
{
	va_list va_alist;
	char chParameters[CHARS_FOR_PARAMS];
	va_start(va_alist, fmt);
	sprintf(chParameters, fmt, va_alist);
	va_end(va_alist);
	write_log("!", chParameters, false, false);
}

void Log::init_log()
{
	char chLogBuff[CHARS_FOR_BUFF];
	char szTimestamp[30];
	tm current_tm;
	time_t current_time = time(NULL);
	localtime_s(&current_tm, &current_time);
	strftime(szTimestamp, sizeof(szTimestamp), skCrypt("[%Y-%m-%d-%H:%M:%S] %s"), &current_tm);
	sprintf_s(chLogBuff, szTimestamp);
	FILE* file;
	if ((fopen_s(&file, g_LogFile, "w")) == 0)
	{
		fprintf_s(file, "%s\n", chLogBuff);
		fclose(file);
	}
	if (IsConsole) console();
	m_Console << chLogBuff << std::endl;
}

void Log::write_log(const char* Section, const char* Data, bool Error, bool Fatal)
{
	char chLogBuff[CHARS_FOR_BUFF];
	char szTimestamp[30];
	struct tm current_tm;
	time_t current_time = time(NULL);
	localtime_s(&current_tm, &current_time);
	strftime(szTimestamp, sizeof(szTimestamp), skCrypt("%Y-%m-%d %H:%M:%S"), &current_tm);
	sprintf_s(chLogBuff, skCrypt("[%s][%s] %s"), szTimestamp, Section, Data);
	std::ofstream file;
	file.open(LOGFILE_NAME, std::ios_base::app);

	file << chLogBuff << "\n";

	if (Error) MessageBoxA(NULL, chLogBuff, skCrypt("ERROR"), MB_ICONERROR);
	if (Fatal) MessageBoxA(NULL, chLogBuff, skCrypt("FATAL ERROR"), MB_ICONERROR);
	if (IsConsole) m_Console << chLogBuff << std::endl;
}
