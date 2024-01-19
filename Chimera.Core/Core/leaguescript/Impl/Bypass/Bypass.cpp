#include "Bypass.h"

#include "../Common/Common.h"
#include "../Encryption/Encryption.h"

void Bypass::mainloop_check()
{
	uintptr_t detection_inst = *(uintptr_t*)(MAKE_RVA(Addresses::Bypass::DetectionWatcher2));
	auto encrypted_detection_flag = (EncryptedBuffer<BYTE>*)(detection_inst + 0x8);

	encrypted_detection_flag->ZeroCurrentValue();
}

void Bypass::issueorder_flag(int order_sent)
{
	static DWORD* flag = reinterpret_cast<DWORD*>(MAKE_RVA(Addresses::Bypass::IssueOrderFlag));
	*flag = order_sent + 17;
}

void Bypass::castspell_flag()
{
	byte* castSpellFlag = (byte*)MAKE_RVA(Addresses::Bypass::CastSpellFlag);
	*castSpellFlag = 1;
}