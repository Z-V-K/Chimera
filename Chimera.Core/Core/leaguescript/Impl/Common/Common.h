#pragma once

#include "RawCommon.h"
#include "../Addresses/Addresses.h"
#include "../Addresses/Structures.h"
#include "../Core/Context/Context.h"

#pragma warning(push)
#pragma warning(disable:4251)

#define SCRIPT_VERSION skCrypt("Version 13.24.547.9214 [PUBLIC]")

#define MAKE_RVA(address) (static_cast<uintptr_t>(g_ctx->mModuleBase) + static_cast<uintptr_t>(address))
#define RVA_CAST_THIS(T, offset) *reinterpret_cast<T*>((uintptr_t) this + (uintptr_t) (offset))
#define RVA_CAST_THIS_REF(T, offset) reinterpret_cast<T>((uintptr_t) this + (uintptr_t) (offset))
#define RVA_CAST(T, offset) *reinterpret_cast<T*>(MAKE_RVA((uintptr_t)offset))