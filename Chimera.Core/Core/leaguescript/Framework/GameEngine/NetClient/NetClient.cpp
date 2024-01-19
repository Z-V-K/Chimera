#include "../pch.h"
#include "NetClient.h"

#include "../Impl/Hooks/retspoof/x64RetSpoof.h"

NetClient* NetClient::get_instance()
{
	return RVA_CAST(NetClient*, Addresses::NetClient::Instance);
}

int NetClient::get_ping()
{
	typedef int64_t(__fastcall* fnGetPing)(uintptr_t);
	static fnGetPing fn = (fnGetPing)MAKE_RVA(Addresses::NetClient::GetPing);

	return x64RetSpoof::spoof_call(fn, (uintptr_t)get_instance());
}