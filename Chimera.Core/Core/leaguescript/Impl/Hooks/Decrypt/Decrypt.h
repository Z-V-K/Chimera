#pragma once

struct ImageSectionInfo
{
	char SectionName[IMAGE_SIZEOF_SHORT_NAME];//the macro is defined WinNT.h
	DWORD SectionAddress;
	DWORD SectionSize;
	ImageSectionInfo(const char* name)
	{
		strcpy_s(SectionName, name);
	}
};


class LeagueDecrypt
{
public:
	static void decrypt(uintptr_t address);
};