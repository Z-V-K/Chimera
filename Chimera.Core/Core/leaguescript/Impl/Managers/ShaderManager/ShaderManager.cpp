#include "../pch.h"
#include "ShaderManager.h"
#include "../Core/Context/Context.h"
#include "../Impl/DirectX/DirectX.h"

#include <d3dcompiler.h>

ShaderManager* g_shader_manager = new ShaderManager();

void ShaderManager::initialize()
{
	if (g_dx->dx11_device == nullptr)
		return;

	pixel_shader = create_pixel_shader(g_dx->dx11_device, g_ctx->pixel_shader_path);
	vertex_shader = create_vertex_shader(g_dx->dx11_device, g_ctx->vertex_shader_path);

	g_dx->shaders_initialized = true;
}

ID3D11PixelShader* ShaderManager::create_pixel_shader(ID3D11Device* pDevice, const std::string& filePath) {
	std::string shaderCode = load_shader_file(filePath);
	if (shaderCode.empty()) {
		g_ctx->mConsole->log_warning(skCrypt("PixelShader is empty"));
		return nullptr;
	}

	// compile the shader code
	ID3DBlob* pShaderBlob = nullptr;
	ID3DBlob* pErrorBlob = nullptr;
	HRESULT hr = D3DCompile(
		shaderCode.c_str(), shaderCode.length(), nullptr, nullptr, nullptr,
		skCrypt("main"), skCrypt("ps_5_0"), D3DCOMPILE_DEBUG, 0, &pShaderBlob, &pErrorBlob
	);

	if (FAILED(hr)) {
		if (pErrorBlob) {
			const char* errorMessage = static_cast<const char*>(pErrorBlob->GetBufferPointer());
			size_t errorMessageSize = pErrorBlob->GetBufferSize();
			g_ctx->mConsole->log_warning(skCrypt("Failed to compile shader: "));
			g_ctx->mConsole->log_warning(errorMessage, errorMessageSize);
			pErrorBlob->Release();
		}
		return nullptr;
	}

	// create the pixel shader
	ID3D11PixelShader* pPixelShader = nullptr;
	hr = pDevice->CreatePixelShader(pShaderBlob->GetBufferPointer(), pShaderBlob->GetBufferSize(), nullptr, &pPixelShader);
	pShaderBlob->Release();

	if (FAILED(hr)) {
		g_ctx->mConsole->log_warning(skCrypt("Failed to create PixelShader"));
		return nullptr;
	}

	g_ctx->mConsole->log_info(skCrypt("PixelShader created successfully"));
	return pPixelShader;
}

ID3D11VertexShader* ShaderManager::create_vertex_shader(ID3D11Device* pDevice, const std::string& filePath) {
	std::string shaderCode = load_shader_file(filePath);
	if (shaderCode.empty()) {
		g_ctx->mConsole->log_warning(skCrypt("VertexShader is empty"));
		return nullptr;
	}

	// compile the shader code
	ID3DBlob* pShaderBlob = nullptr;
	ID3DBlob* pErrorBlob = nullptr;
	HRESULT hr = D3DCompile(
		shaderCode.c_str(), shaderCode.length(), nullptr, nullptr, nullptr,
		skCrypt("main"), skCrypt("vs_5_0"), 0, 0, &pShaderBlob, &pErrorBlob
	);

	if (FAILED(hr)) {
		if (pErrorBlob) {
			g_ctx->mConsole->log_warning(skCrypt("Failed to compile VertexShader"));
			pErrorBlob->Release();
		}
		return nullptr;
	}

	// create the vertex shader
	ID3D11VertexShader* pVertexShader = nullptr;
	hr = pDevice->CreateVertexShader(pShaderBlob->GetBufferPointer(), pShaderBlob->GetBufferSize(), nullptr, &pVertexShader);
	pShaderBlob->Release();

	if (FAILED(hr)) {
		g_ctx->mConsole->log_warning(skCrypt("Failed to create VertexShader"));
		return nullptr;
	}

	g_ctx->mConsole->log_info(skCrypt("VertexShader created successfully"));
	return pVertexShader;
}

std::string ShaderManager::load_shader_file(const std::string& filePath) {
	std::ifstream file(filePath);
	if (!file.is_open()) {
		g_ctx->mConsole->log_warning(skCrypt("Failed to open file"));
		return "";
	}

	std::string shaderCode((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	return shaderCode;
}