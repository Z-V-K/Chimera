#pragma once

class ShaderManager
{
public:
	void initialize();
	std::string load_shader_file(const std::string& filePath);
	ID3D11PixelShader* create_pixel_shader(ID3D11Device* pDevice, const std::string& filePath);
	ID3D11VertexShader* create_vertex_shader(ID3D11Device* pDevice, const std::string& filePath);
	ID3D11PixelShader* pixel_shader;
	ID3D11VertexShader* vertex_shader;
};

extern ShaderManager* g_shader_manager;