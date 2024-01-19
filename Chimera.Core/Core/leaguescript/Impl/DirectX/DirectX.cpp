#include "../pch.h"
#include "../Impl/DirectX/DirectX.h"

#include "../Framework/Rendering/r3dRenderer/r3dRenderer.h"

#include "../Imgui/impl/imgui_impl_dx9.h"
#include "../Imgui/impl/imgui_impl_dx11.h"
#include "../Imgui/impl/imgui_impl_win32.h"
#include "../Imgui/Fontawesome5Icons.h"

#include "../Assets/fa.h"
#include "../Assets/museosanscyrl-500.h"
#include "../Assets/cascadia_semibold.h"
#include "../Assets/nanum.h"

#include "../Impl/Managers/DrawManager/DrawManager.h"
#include "../Impl/Managers/ShaderManager/ShaderManager.h"

DirectXUI* g_dx = new DirectXUI();

void DirectXUI::initialize()
{
	ImGui::StyleColorsDark();
	ImGui::GetStyle().AntiAliasedLines = true;

	ImGuiIO& io = ImGui::GetIO();

	ImFontConfig font_config;
	font_config.OversampleH = 1;
	font_config.OversampleV = 1;
	font_config.FontBuilderFlags = 1;

	const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
	ImFontConfig icons_config;
	icons_config.MergeMode = true;
	icons_config.PixelSnapH = true;
	icons_config.FontDataOwnedByAtlas = false;

	// 0
	io.Fonts->AddFontFromMemoryTTF((void*)roboto, sizeof(roboto), 14.0f, &font_config);
	io.Fonts->AddFontFromMemoryTTF((void*)fa, sizeof(fa), 14.0f, &icons_config, icons_ranges);
	menu_font = io.Fonts->Fonts[0];

	// 1
	io.Fonts->AddFontFromMemoryTTF((void*)roboto, sizeof(roboto), 14.0f, &font_config);
	io.Fonts->AddFontFromMemoryTTF((void*)fa, sizeof(fa), 5.f, &icons_config, icons_ranges);

	// 2
	io.Fonts->AddFontFromMemoryTTF((void*)roboto, sizeof(roboto), 18.0f, &font_config);

	// 3
	io.Fonts->AddFontFromMemoryTTF((void*)roboto, sizeof(roboto), 11.0f, &font_config);
	io.Fonts->AddFontFromMemoryTTF((void*)fa, sizeof(fa), 18.0f, &icons_config, icons_ranges);

	// 4 - Console font
	io.Fonts->AddFontFromMemoryTTF((void*)cascadia_semibold, sizeof(cascadia_semibold), 15.f, &font_config);
	io.Fonts->AddFontFromMemoryTTF((void*)fa, sizeof(fa), 14.f, &icons_config, icons_ranges);

	// 5 - Korean font
	io.Fonts->AddFontFromMemoryTTF((void*)nanum, sizeof(nanum), 30.f, NULL, io.Fonts->GetGlyphRangesKorean());
	//io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesKorean());

	for(int i = 1; i < 32; i++)
	{
		const auto f = io.Fonts->AddFontFromMemoryTTF((void*)roboto, sizeof(roboto), static_cast<float>(i));

		fonts.insert({ i, f });
	}

	io.Fonts->AddFontFromMemoryTTF((void*)roboto, sizeof(roboto), 16.0f, &font_config);

	io.Fonts->Build();

	ui_initialized = true;
}

void DirectXUI::init_ui()
{
	ImGui::CreateContext();
	ImGui_ImplWin32_Init(r3dRenderer::game_hwnd);

	if (r3dRenderer::instance()->get_dx_version() == Enums::DirectXVersion::Dx9)
	{
		ImGui_ImplDX9_Init(dx9_device);
	}
	else
	{
		ID3D11DeviceContext* context;
		g_dx->dx11_device->GetImmediateContext(&context);
		ImGui_ImplDX11_Init(dx11_device, context);
	}

	g_dx->initialize();
}

void DirectXUI::start_frame(bool new_frame)
{
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	if (r3dRenderer::instance()->get_dx_version() == Enums::DirectXVersion::Dx9)
		ImGui_ImplDX9_NewFrame();
	else
		ImGui_ImplDX11_NewFrame();

	ImGui_ImplWin32_NewFrame();

	ImGui::NewFrame();

	const auto flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoBackground;

	ImGui::Begin(skCrypt("##overlay"), nullptr, flags);

	ImGui::SetWindowPos(ImVec2(0.0f, 0.0f), ImGuiCond_Always);
	ImGui::SetWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y), ImGuiCond_Always);
}

void DirectXUI::end_frame()
{
	ImGui::GetForegroundDrawList()->PushClipRectFullScreen();
	ImGui::End();
	ImGui::EndFrame();
	ImGui::Render();

	if(r3dRenderer::instance()->get_dx_version() == Enums::DirectXVersion::Dx9)
	{
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
	}
	else
	{
		ID3D11DeviceContext* context;
		g_dx->dx11_device->GetImmediateContext(&context);
		context->OMSetRenderTargets(1, &g_dx->render_target_view, NULL);
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}

}