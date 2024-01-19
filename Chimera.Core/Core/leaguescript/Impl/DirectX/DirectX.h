#pragma once

#include "../Imgui/imgui.h"

class DirectXUI
{
public:
	void initialize();

	void init_ui();
	void start_frame(bool new_frame = true);
	void end_frame();

	LPDIRECT3DDEVICE9 dx9_device;
	IDXGISwapChain* swap_chain;
	ID3D11Device* dx11_device;
	ID3D11RenderTargetView* render_target_view;

	bool ui_initialized = false;
	bool shaders_initialized = false;

	ImFont* menu_font = nullptr;
	std::map<unsigned int, ImFont*> fonts;
};

extern DirectXUI* g_dx;