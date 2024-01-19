#include "../pch.h"
#include "Zoom.h"

#include "../Impl/Common/Common.h"
#include "../Framework/Hud/Hud/Hud.h"

Zoom* Zoom::get_instance()
{
	return RVA_CAST(Zoom*, Addresses::Zoom::Instance);
}

Zoom* Zoom::get_instance_from_hud()
{
	return *reinterpret_cast<Zoom**>((uintptr_t)Hud::get_instance() + static_cast<uintptr_t>(Structures::Hud::Camera));
}

void Zoom::set_flag_value(int val)
{
	*reinterpret_cast<byte*>(MAKE_RVA(Addresses::r3dRenderer::ZoomCheatDetectionFlag)) = val;
}

float Zoom::get_max_value()
{
	
	return *reinterpret_cast<float*>((uintptr_t)get_instance() + static_cast<uintptr_t>(Structures::Zoom::MaxValue));
}

float Zoom::get_value()
{
	return *reinterpret_cast<float*>((uintptr_t) get_instance_from_hud() + static_cast<uintptr_t>(Structures::Zoom::Value));
}

float Zoom::get_camera_angle()
{
	return *reinterpret_cast<float*>((uintptr_t)get_instance_from_hud() + static_cast<uintptr_t>(Structures::Zoom::CameraAngle));
}

void Zoom::set_camera_angle(float f)
{
	return;

	if (f >= 150.f) f = 150;
	if (f <= 40.f) f = 40;

	float* pCameraAngle = reinterpret_cast<float*>((uintptr_t)get_instance_from_hud() + static_cast<uintptr_t>(Structures::Zoom::CameraAngle));
	*pCameraAngle = f;
	
	set_flag_value(0);
}

void Zoom::set_value(float f)
{
	*reinterpret_cast<float*>((uintptr_t) get_instance_from_hud() + static_cast<uintptr_t>(Structures::Zoom::Value)) = f;
}

void Zoom::set_max_zoom(float f)
{
	if (f > 2000.f) f = 2000.f;
	if (f < 600.f) f = 600.f;

	*reinterpret_cast<float*>((uintptr_t)get_instance() + (uintptr_t) Structures::Zoom::OtherMaxValue) = f;

	// bypass detection | 13.15 OK
	set_flag_value(0);
}