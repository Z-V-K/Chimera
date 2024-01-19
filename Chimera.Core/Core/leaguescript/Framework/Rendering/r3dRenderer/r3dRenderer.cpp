#include "../pch.h"
#include "r3dRenderer.h"

#include "../../../Impl/Bypass/Bypass.h"
#include "../../../Impl/Common/Utils.h"
#include "../../../Impl/Managers/AntiGapcloserManager/AntiGapcloserManager.h"
#include "../../../Impl/Managers/OrbwalkerManager/OrbwalkerManager.h"
#include "../../../Impl/Managers/PredictionManager/PredictionManager.h"
#include "../../../SDK/LUA/LuaBootstrap.h"
#include "../Imgui/impl/imgui_impl_dx9.h"
#include "../Imgui/impl/imgui_impl_dx11.h"
#include "../Impl/DirectX/DirectX.h"
#include "../SDK/CPP/DllBootstrap.h"
#include "../Impl/Hooks/Hook.h"
#include "../Impl/Hooks/retspoof/x64RetSpoof.h"
#include "../Impl/EntityList/EntityList.h"
#include "../Impl/Managers/ConfigManager/ConfigManager.h"
#include "../Impl/Managers/DmgLibManager/DamageLibManager.h"
#include "../Impl/Managers/GlowManager/GlowManager.h"
#include "../Impl/Managers/HealthPredManager/HealthPredictionManager.h"
#include "../Impl/Managers/PermashowManager/PermashowManager.h"
#include "../Impl/Managers/ShaderManager/ShaderManager.h"
#include "../Impl/Managers/TargetSelectorManager/TargetSelectorManager.h"
#include "../Impl/Managers/MenuManager/MenuManager.h"
#include "../Impl/Managers/DrawManager/DrawManager.h"
#include "../Impl/Managers/EventManager/EventManager.h"
#include "../Impl/Managers/TextureManager/TextureManager.h"
#include "../Impl/Scheduler/Scheduler.h"
#include "../Framework/Hud/Zoom/Zoom.h"
#include "../Framework/Hud/Minimap/Minimap.h"
#include "../Framework/Hud/Chat/Chat.h"
#include "../Framework/GameEngine/GameTime/GameTime.h"
#include "../Framework/Rendering/r3dTexture/r3dTexture.h"
#include "../Framework/GameObjects/GameObject/GameObject.h"

r3dRenderer* g_renderer = new r3dRenderer();

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

Hook< convention_type::fastcall_t, long, IDirect3DDevice9*, D3DPRESENT_PARAMETERS* > HookReset;
Hook< convention_type::fastcall_t, long, LPDIRECT3DDEVICE9, const RECT*, const RECT*, HWND, const RGNDATA* > HookDX9Present;
Hook< convention_type::fastcall_t, long, IDXGISwapChain*, UINT, UINT > HookDX11Present;
Hook< convention_type::fastcall_t, long, IDXGISwapChain*, UINT, UINT, UINT, DXGI_FORMAT, UINT > HookResizeBuffers;
Hook< convention_type::fastcall_t, int64_t, int64_t, int64_t, int64_t, uint8_t > HookDrawEnvironment;
Hook< convention_type::fastcall_t, int64_t, uint64_t > HookOnGameTick;
Hook< convention_type::fastcall_t, void**, void*, void* > HookOnRenderMouseOvers;
Hook< convention_type::fastcall_t, int64_t, char, int > HookHandleConfirmQuitGame;

void present_routine();

WNDPROC m_wndProc;

static bool hwndInitialized = false;
static bool isWndprocInactive = false;

class Wrapper
{
public:
	static long __stdcall DX9PresentCallee(
		LPDIRECT3DDEVICE9 pDevice, 
		const RECT* pSourceRect, 
		const RECT* pDestRect,
		HWND hDestWindowOverride, 
		const RGNDATA* pDirtyRegion
	) {
		if (!hwndInitialized)
		{
			g_dx->dx9_device = pDevice;

			TextureManager::get().load_textures();

			D3DDEVICE_CREATION_PARAMETERS parameters;
			ZeroMemory(&parameters, sizeof(parameters));
			pDevice->GetCreationParameters(&parameters);
			r3dRenderer::game_hwnd = parameters.hFocusWindow;

			m_wndProc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(r3dRenderer::game_hwnd, GWLP_WNDPROC, reinterpret_cast<uintptr_t>(Wrapper::WndProcCallee)));

			hwndInitialized = true;
		}

		if (!g_dx->ui_initialized) {
			g_dx->init_ui();
		}

		present_routine();

		return HookDX9Present.call_original(pDevice, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
	}

	static long __stdcall DX11PresentCallee(IDXGISwapChain* pThis, UINT syncInterval, UINT flags)
	{
		if (!hwndInitialized)
		{
			g_dx->swap_chain = pThis;
			pThis->GetDevice(__uuidof(g_dx->dx11_device), reinterpret_cast<void**>(&g_dx->dx11_device));
			ID3D11Texture2D* pBackBuffer;
			pThis->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
			g_dx->dx11_device->CreateRenderTargetView(pBackBuffer, NULL, &g_dx->render_target_view);
			pBackBuffer->Release();

			TextureManager::get().load_textures();

			DXGI_SWAP_CHAIN_DESC sd;
			pThis->GetDesc(&sd);
			r3dRenderer::game_hwnd = sd.OutputWindow;;

			m_wndProc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(r3dRenderer::game_hwnd, GWLP_WNDPROC, reinterpret_cast<uintptr_t>(Wrapper::WndProcCallee)));

			hwndInitialized = true;
		}

		if (!g_dx->ui_initialized) {
			g_dx->init_ui();
			//g_shader_manager->initialize();
		}

		present_routine();

		return HookDX11Present.call_original(pThis, syncInterval, flags);
	}

	static long __stdcall ResetCallee(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* pPresentationParameters) {

		ImGui_ImplDX9_InvalidateDeviceObjects();

		HRESULT hResult = HookReset.call_original(device, pPresentationParameters);
		if (hResult != D3DERR_INVALIDCALL)
			ImGui_ImplDX9_CreateDeviceObjects();

		return hResult;
	}

	static long __stdcall ResizeBuffersCallee(IDXGISwapChain* pThis, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT flags)
	{
		if (g_dx->render_target_view)
		{
			g_dx->render_target_view->Release();
			g_dx->render_target_view = nullptr;
		}

		auto hResult = HookResizeBuffers.call_original(pThis, bufferCount, width, height, newFormat, flags);

		ID3D11Texture2D* backbuffer = nullptr;
		pThis->GetBuffer(0, IID_PPV_ARGS(&backbuffer));
		if (backbuffer)
		{
			g_dx->dx11_device->CreateRenderTargetView(backbuffer, NULL, &g_dx->render_target_view);
			backbuffer->Release();
		}

		return hResult;
	}

	static int64_t __fastcall DrawEnvironmentCallee(int64_t thisPtr, int64_t a2, int64_t a3, uint8_t a4)
	{
		int64_t ret = HookDrawEnvironment.call_original(thisPtr, a2, a3, a4);

		if (!g_dx->ui_initialized)
			return ret;

		const auto flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoBackground;

		ImGui::Begin(skCrypt("##overlaydrawenv"), nullptr, flags);

		ImGui::SetWindowPos(ImVec2(0.0f, 0.0f), ImGuiCond_Always);
		ImGui::SetWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y), ImGuiCond_Always);

		if (!MenuManager::hide_drawings->get_bool())
		{
			g_event_manager->trigger(Enums::OnDrawEnvironment);
			g_event_manager->trigger_lua(Enums::OnDrawEnvironment);
		}

		ImGui::End();

		ImGui::Render();
		if(r3dRenderer::instance()->get_dx_version() == Enums::DirectXVersion::Dx9)
			ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
		else
			ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

		return ret;
	}

	static void** __fastcall RenderMouseOversCallee(void* pipeline, void* screen_buffer)
	{
		for (const auto& obj : g_glow_manager->glow_objects)
		{
			typedef void**(__fastcall* fnRenderEffect)(void*, GameObject*, void*, void*, const uint32_t*, int, int);
			static fnRenderEffect fn = (fnRenderEffect)MAKE_RVA(Addresses::r3dRenderer::RenderEffect);

			for (const auto& data : obj.second)
			{
				const uint32_t col = Utils::imcolor_to_hex(data.color);
				x64RetSpoof::spoof_call(fn, screen_buffer, obj.first, (void*) nullptr, (void*) nullptr, &col, data.glow_size, data.glow_blur);
			}
		}

		return x64RetSpoof::spoof_call(HookOnRenderMouseOvers.m_original, pipeline, screen_buffer);
	}

	static LRESULT __stdcall WndProcCallee(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		bool execute = true;

		ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);

		if (uMsg == WM_KEYDOWN)
		{
			if (wParam == VK_DELETE)
			{
				g_ctx->unload = true;
				return 1;
			}
		}

		g_event_manager->trigger(Enums::OnWndProc, hWnd, uMsg, wParam, lParam, &execute);
		g_event_manager->trigger_lua_bool(Enums::OnWndProc, &execute, hWnd, uMsg, wParam, lParam);

		if (!execute)
			return MenuManager::show_menu->get_bool();

		if (MenuManager::show_menu->get_bool() && ((wParam == VK_ESCAPE && !Chat::instance()->is_open()) || wParam == VK_LBUTTON))
		{
			CallWindowProc(m_wndProc, hWnd, WM_ACTIVATE, WA_INACTIVE, 0);
			return MenuManager::show_menu->get_bool();
		}
		else
			CallWindowProc(m_wndProc, hWnd, WM_ACTIVATE, WA_ACTIVE, 0);

		return MenuManager::show_menu->get_bool() ? MenuManager::show_menu->get_bool() : CallWindowProc(m_wndProc, hWnd, uMsg, wParam, lParam);
	}

	static int64_t __fastcall OnGameTickCallee(uint64_t thisPtr)
	{
		static int tick = 0;


		if (GameClock::get_tick_count() - tick > 30)
		{
			g_event_manager->trigger(Enums::OnSlowTick);
			g_event_manager->trigger_lua(Enums::OnSlowTick);
			tick = GameClock::get_tick_count();
		}

		g_event_manager->trigger(Enums::OnGameTick);
		g_event_manager->trigger_lua(Enums::OnGameTick);
		g_scheduler->on_update();

		return x64RetSpoof::spoof_call(HookOnGameTick.m_original, thisPtr);
	}

	static int64_t __fastcall HandleConfirmQuitGameCallee(char a1, int a2)
	{
		g_ctx->unload = true;

		Sleep(5000);

		return x64RetSpoof::spoof_call(HookHandleConfirmQuitGame.m_original, a1, a2);
	}
};

void present_routine()
{
	if (hwndInitialized && g_dx->ui_initialized) {

		static ULONGLONG lastRefresh = 0;

		if (GetAsyncKeyState(VK_F5) && GetTickCount64() - lastRefresh > 1000)
		{ 
			g_scheduler->clear();
			g_event_manager->clear_events();
			g_entityList->remove_callbacks();
			g_permashow_manager->remove_permashows();
			MenuManager::delete_menus();

			MenuManager::init_menu();
			DllBootstrap::reload_dlls();
			LuaBootstrap::reload_scripts();
			g_config_manager->load_config();

			g_entityList->add_callbacks();

			lastRefresh = GetTickCount64();
		}

		g_dx->start_frame();

		MenuManager::on_update();

		if (MenuManager::show_menu->get_bool())
		{
			MenuManager::draw();
		}

		if (MenuManager::show_console->get_bool() && (MenuManager::show_menu->get_bool() || MenuManager::show_console_menu_closed->get_bool()))
		{
			g_ctx->mConsole->render();
		}

		if (!MenuManager::hide_drawings->get_bool())
		{
			g_event_manager->trigger(Enums::OnDraw);
			g_event_manager->trigger_lua(Enums::OnDraw);
			g_permashow_manager->on_draw();
		}

		g_dx->end_frame();

		g_config_manager->save_config();

		// realy cool shader stuff
		
		// if (g_dx->shaders_initialized)
		// {
		// 	ID3D11DeviceContext* context;
		// 	g_dx->dx11_device->GetImmediateContext(&context);
		//
		// 	// Define vertices of the circle
		// 	const int numSegments = 360;
		// 	float circleVertices[(numSegments + 1) * 3];  // +1 for center point
		//
		// 	// Center point
		// 	circleVertices[0] = 0.0f;
		// 	circleVertices[1] = 0.0f;
		// 	circleVertices[2] = 0.0f;
		//
		// 	// Generate vertices for the circle
		// 	for (int i = 0; i <= numSegments; ++i) {
		// 		float angle = static_cast<float>(i) / static_cast<float>(numSegments) * 2.0f * 3.14159f;
		// 		circleVertices[i * 3 + 3] = 0.5f * cosf(angle); // x-coordinate
		// 		circleVertices[i * 3 + 4] = 0.5f * sinf(angle); // y-coordinate
		// 		circleVertices[i * 3 + 5] = 0.0f; // z-coordinate
		// 	}
		//
		// 	UINT vertex_stride = 3 * sizeof(float);
		// 	UINT vertex_offset = 0;
		// 	UINT vertex_count = numSegments + 1;  // +1 for center point
		//
		// 	// Create a vertex buffer for the circle
		// 	D3D11_BUFFER_DESC bufferDesc = {};
		// 	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		// 	bufferDesc.ByteWidth = sizeof(circleVertices);
		// 	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		//
		// 	D3D11_SUBRESOURCE_DATA initData = { 0 };
		// 	initData.pSysMem = circleVertices;
		//
		// 	ID3D11Buffer* pVertexBuffer;
		// 	g_dx->dx11_device->CreateBuffer(&bufferDesc, &initData, &pVertexBuffer);
		//
		// 	// Set primitive topology to draw triangle strip
		// 	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
		//
		// 	// Set the vertex shader
		// 	context->VSSetShader(g_shader_manager->vertex_shader, nullptr, 0);
		//
		// 	// Set the vertex buffer
		// 	context->IASetVertexBuffers(0, 1, &pVertexBuffer, &vertex_stride, &vertex_offset);
		//
		// 	// Set the pixel shader
		// 	context->PSSetShader(g_shader_manager->pixel_shader, nullptr, 0);
		//
		// 	// Draw the circle
		// 	context->Draw(vertex_count, 0);
		//
		// 	// Unbind shaders
		// 	context->PSSetShader(nullptr, nullptr, 0);
		// 	context->VSSetShader(nullptr, nullptr, 0);
		// }
		
	}

	Zoom::set_flag_value(0);
}

r3dRenderer* r3dRenderer::instance() {
	return RVA_CAST(r3dRenderer*, Addresses::r3dRenderer::r3dRendererInstance);
}

D3DMATRIX r3dRenderer::calculate_view_projection_matrix()
{
	D3DMATRIX returnMat{};
	auto viewMat = *(D3DMATRIX*)MAKE_RVA(((uintptr_t)Addresses::r3dRenderer::ViewProjectionMatrix + (uintptr_t)Addresses::r3dRenderer::ViewMatrix));
	auto projMat = *(D3DMATRIX*)MAKE_RVA(((uintptr_t)Addresses::r3dRenderer::ViewProjectionMatrix + (uintptr_t)Addresses::r3dRenderer::ProjectionMatrix));


	__m128 col0 = _mm_load_ps(projMat.m[0]);
	__m128 col1 = _mm_load_ps(projMat.m[1]);
	__m128 col2 = _mm_load_ps(projMat.m[2]);
	__m128 col3 = _mm_load_ps(projMat.m[3]);

	for (int i = 0; i < 4; i++)
	{
		__m128 row = _mm_load_ps(viewMat.m[i]);
		__m128 res = _mm_add_ps(
			_mm_add_ps(
				_mm_mul_ps(_mm_shuffle_ps(row, row, 0x00), col0),
				_mm_mul_ps(_mm_shuffle_ps(row, row, 0x55), col1)),
			_mm_add_ps(
				_mm_mul_ps(_mm_shuffle_ps(row, row, 0xAA), col2),
				_mm_mul_ps(_mm_shuffle_ps(row, row, 0xFF), col3)));

		_mm_store_ps(&returnMat.m[i][0], res);
	}

	return returnMat;
}

Vec2 r3dRenderer::world_to_screen(const Vec3& position) {
	const auto matrix = calculate_view_projection_matrix().m;

	Vec4 clipCoords;
	clipCoords.x = position.x * matrix[0][0] + position.y * matrix[1][0] + position.z * matrix[2][0] + matrix[3][0];
	clipCoords.y = position.x * matrix[0][1] + position.y * matrix[1][1] + position.z * matrix[2][1] + matrix[3][1];
	clipCoords.z = position.x * matrix[0][2] + position.y * matrix[1][2] + position.z * matrix[2][2] + matrix[3][2];
	clipCoords.w = position.x * matrix[0][3] + position.y * matrix[1][3] + position.z * matrix[2][3] + matrix[3][3];

	if (clipCoords.w < 0.01f)
		clipCoords.w = 1.f;

	Vec3 M;
	M.x = clipCoords.x / clipCoords.w;
	M.y = clipCoords.y / clipCoords.w;
	M.z = clipCoords.z / clipCoords.w;

	const Vec2 screen = instance()->get_renderer_size();

	return { (screen.x * 0.5f * M.x) + (M.x + screen.x * 0.5f), -(screen.y * 0.5f * M.y) + (M.y + screen.y * 0.5f) };
}

Vec2 r3dRenderer::world_to_minimap(const Vec3& in)
{
	Vec2 res = { in.x / 14800.f, in.z / 14800.f };

	res.x = Minimap::get_instance()->get_position().x + res.x * Minimap::get_instance()->get_size().x;
	res.y = Minimap::get_instance()->get_position().y + Minimap::get_instance()->get_size().y - (res.y * Minimap::get_instance()->get_size().y);

	return res;
}

bool getD3D9Device(void** pTable, size_t Size)
{
	// no ptable.
	if (!pTable)
		return false;

	IDirect3D9* pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	// Direct3DCreate9 failed.
	if (!pD3D)
		return false;

	D3DPRESENT_PARAMETERS d3dpp = { 0 };
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = GetForegroundWindow();
	d3dpp.Windowed = ((GetWindowLong(d3dpp.hDeviceWindow, GWL_STYLE) & WS_POPUP) != 0) ? FALSE : TRUE;;


	IDirect3DDevice9* pDummyDevice = nullptr;
	HRESULT create_device_ret = pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3dpp.hDeviceWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pDummyDevice);
	if (!pDummyDevice || FAILED(create_device_ret))
	{
		// CreateDevice failed
		pD3D->Release();
		return false;
	}

	memcpy(pTable, *reinterpret_cast<void***>(pDummyDevice), Size);

	pDummyDevice->Release();
	pD3D->Release();

	return true;
}

bool r3dRenderer::apply_hooks()
{
	if(instance()->get_dx_version() == Enums::DirectXVersion::Dx9)
	{
		void* d3d9Device[119];
		while (!getD3D9Device(d3d9Device, sizeof d3d9Device)) {}

		HookReset.apply(d3d9Device[16], Wrapper::ResetCallee);
		HookDX9Present.apply(d3d9Device[17], Wrapper::DX9PresentCallee);
	} else
	{
		DXGI_SWAP_CHAIN_DESC sd{ 0 };
		sd.BufferCount = 1;
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.OutputWindow = GetDesktopWindow();
		sd.Windowed = true;
		sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		sd.SampleDesc.Count = 1;

		ID3D11Device* pDevice = nullptr;
		IDXGISwapChain* pSwapChain = nullptr;

		HRESULT hr = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION, &sd, &pSwapChain, &pDevice, nullptr, nullptr);
		PDWORD64* pSwapChainVT = reinterpret_cast<PDWORD64*>(pSwapChain);
		pSwapChainVT = *reinterpret_cast<PDWORD64**>(pSwapChainVT);

		HookDX11Present.apply(pSwapChainVT[8], Wrapper::DX11PresentCallee);
		HookResizeBuffers.apply(pSwapChainVT[13], Wrapper::ResizeBuffersCallee);
	}

	HookOnGameTick.apply_jmp(MAKE_RVA(Addresses::Game::OnMainLoop), (uintptr_t) Wrapper::OnGameTickCallee, 18);
	HookDrawEnvironment.apply_jmp(MAKE_RVA(Addresses::Game::OnWorldDraw), (uintptr_t) Wrapper::DrawEnvironmentCallee, 15);
	HookOnRenderMouseOvers.apply_jmp(MAKE_RVA(Addresses::r3dRenderer::RenderMouseOvers), (uintptr_t)Wrapper::RenderMouseOversCallee, 15);
	HookHandleConfirmQuitGame.apply_jmp(MAKE_RVA(Addresses::Game::HandleConfirmQuitGame), (uintptr_t)Wrapper::HandleConfirmQuitGameCallee, 16);

	return true;
}

void r3dRenderer::remove_hwnd_hook()
{
	SetWindowLongPtrW(FindWindowA(NULL, skCrypt("League of Legends (TM) Client")), GWLP_WNDPROC, (uintptr_t)m_wndProc);
}

Enums::DirectXVersion r3dRenderer::get_dx_version()
{
	return RVA_CAST_THIS(Enums::DirectXVersion, Structures::r3dRenderer::DxVersion);
}

class StringTexture
{
	const char* str_name;
	size_t str_size;
	size_t str_max_size;
	const char* str;
public:
	StringTexture(const std::string& text) : str_name(text.data()), str_size(text.size()), str_max_size(text.max_size()),
		str(text.c_str())
	{
	}
};

PVOID r3dRenderer::get_texture_from_game(const std::string& name)
{
	typedef int64_t*(__fastcall* fnLoadTexture)(uintptr_t, r3dTexture**, StringTexture*);
	static fnLoadTexture fn = (fnLoadTexture)MAKE_RVA(Addresses::r3dRenderer::LoadTexture);

	r3dTexture* texture = nullptr;
	StringTexture str{ name };

	x64RetSpoof::spoof_call(fn, *(uintptr_t*)MAKE_RVA(Addresses::r3dRenderer::LoadTextureFirstArg), &texture, &str);

	if (!texture)
		return nullptr;

	return texture->get_dx_texture();
}

LuaTexture r3dRenderer::get_texture_from_game_lua(const std::string& name)
{
	return LuaTexture(get_texture_from_game(name));	
}

Vec2 r3dRenderer::get_renderer_size()
{
	const auto inst = instance();

	const auto w = *reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(inst) + static_cast<uintptr_t>(Structures::r3dRenderer::RendererSize));
	const auto h = *reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(inst) + static_cast<uintptr_t>(Structures::r3dRenderer::RendererSize) + 0x4);

	return { (float) w, (float) h };
}

Vec2 r3dRenderer::exported_world_to_minimap(const Vec3& in)
{
	return world_to_minimap(in);
}

Vec2 r3dRenderer::exported_world_to_screen(const Vec3& in)
{
	return world_to_screen(in);
}
