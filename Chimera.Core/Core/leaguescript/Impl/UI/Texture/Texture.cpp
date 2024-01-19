#include "../pch.h"
#include "Texture.h"

#include "../Core/Context/Context.h"
#include "../Impl/DirectX/DirectX.h"
#include "../Framework/Hash/LeagueHash.h"
#include "../Impl/Logger/Logger.h"
#include "../Framework/Rendering/r3dRenderer/r3dRenderer.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

bool LoadTextureFromFileDX9(const char* filename, PDIRECT3DTEXTURE9* out_texture, int* out_width, int* out_height)
{
	// Load texture from disk
	PDIRECT3DTEXTURE9 texture;
	const HRESULT hr = D3DXCreateTextureFromFileA(g_dx->dx9_device, filename, &texture);
	if (hr != S_OK)
		return false;

	// Retrieve description of the texture surface so we can access its size
	D3DSURFACE_DESC my_image_desc;
	texture->GetLevelDesc(0, &my_image_desc);
	*out_texture = texture;
	*out_width = (int)my_image_desc.Width;
	*out_height = (int)my_image_desc.Height;

	return true;
}

bool LoadTextureFromMemoryDX9(unsigned char* byteArray, PDIRECT3DTEXTURE9* out_texture, int* out_width, int* out_height) {
	// Load texture from disk
	PDIRECT3DTEXTURE9 texture;
	HRESULT hr = D3DXCreateTextureFromFileInMemory(g_dx->dx9_device, byteArray, sizeof(byteArray), &texture);
	if (hr != S_OK)
		return false;

	// Retrieve description of the texture surface so we can access its size
	D3DSURFACE_DESC my_image_desc;
	texture->GetLevelDesc(0, &my_image_desc);
	*out_texture = texture;
	*out_width = (int)my_image_desc.Width;
	*out_height = (int)my_image_desc.Height;

	return true;
}

bool LoadTextureFromMemoryDX11(unsigned char* byteArray, ID3D11ShaderResourceView** out_texture, int* out_width, int* out_height)
{
	// Load from disk into a raw RGBA buffer
	int image_width = 0;
	int image_height = 0;
	unsigned char* image_data = stbi_load_from_memory(byteArray, sizeof(byteArray), &image_width, &image_height, NULL, 4);
	if (image_data == NULL)
		return false;

	// Create texture
	D3D11_TEXTURE2D_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Width = image_width;
	desc.Height = image_height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = 0;

	ID3D11Texture2D* pTexture = NULL;
	D3D11_SUBRESOURCE_DATA subResource;
	subResource.pSysMem = image_data;
	subResource.SysMemPitch = desc.Width * 4;
	subResource.SysMemSlicePitch = 0;
	g_dx->dx11_device->CreateTexture2D(&desc, &subResource, &pTexture);

	// Create texture view
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&srvDesc, sizeof(srvDesc));
	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = desc.MipLevels;
	srvDesc.Texture2D.MostDetailedMip = 0;
	g_dx->dx11_device->CreateShaderResourceView(pTexture, &srvDesc, out_texture);
	pTexture->Release();

	*out_width = image_width;
	*out_height = image_height;
	stbi_image_free(image_data);

	return true;
}

bool LoadTextureFromFileDX11(const char* fileName, ID3D11ShaderResourceView** out_texture, int* out_width, int* out_height)
{
	// Load from disk into a raw RGBA buffer
	int image_width = 0;
	int image_height = 0;
	unsigned char* image_data = stbi_load(fileName, &image_width, &image_height, NULL, 4);
	if (image_data == NULL)
		return false;

	// Create texture
	D3D11_TEXTURE2D_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Width = image_width;
	desc.Height = image_height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = 0;

	ID3D11Texture2D* pTexture = NULL;
	D3D11_SUBRESOURCE_DATA subResource;
	subResource.pSysMem = image_data;
	subResource.SysMemPitch = desc.Width * 4;
	subResource.SysMemSlicePitch = 0;
	g_dx->dx11_device->CreateTexture2D(&desc, &subResource, &pTexture);

	// Create texture view
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&srvDesc, sizeof(srvDesc));
	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = desc.MipLevels;
	srvDesc.Texture2D.MostDetailedMip = 0;
	g_dx->dx11_device->CreateShaderResourceView(pTexture, &srvDesc, out_texture);
	pTexture->Release();

	*out_width = image_width;
	*out_height = image_height;
	stbi_image_free(image_data);

	return true;
}

Texture* Texture::load_from_memory(unsigned char* tex, const std::string& file_name) {
	int my_image_width = 0;
	int my_image_height = 0;

	PDIRECT3DTEXTURE9 my_texture = NULL;
	ID3D11ShaderResourceView* my_dx11_texture = NULL;
	bool ret = false;

	if (r3dRenderer::instance()->get_dx_version() == Enums::DirectXVersion::Dx9)
		ret = LoadTextureFromMemoryDX9(tex, &my_texture, &my_image_width, &my_image_height);
	else
		ret = LoadTextureFromMemoryDX11(tex, &my_dx11_texture, &my_image_width, &my_image_height);

	if (!ret)
		return nullptr;

	Texture* texture = new Texture();

	texture->resource_view = my_texture;
	texture->width = my_image_width;
	texture->height = my_image_height;
	texture->file_path = file_name;
	texture->hash = league_hash(file_name.c_str());

	return texture;
}

Texture* Texture::load_from_file(const std::string& fileName)
{
	int my_image_width = 0;
	int my_image_height = 0;
	PDIRECT3DTEXTURE9 my_texture = NULL;
	ID3D11ShaderResourceView* my_dx11_texture = NULL;
	bool ret = false;

	if (r3dRenderer::instance()->get_dx_version() == Enums::DirectXVersion::Dx9)
		ret = LoadTextureFromFileDX9(fileName.c_str(), &my_texture, &my_image_width, &my_image_height);
	else
		ret = LoadTextureFromFileDX11(fileName.c_str(), &my_dx11_texture, &my_image_width, &my_image_height);

	if (!ret)
		return nullptr;

	Texture* texture = new Texture();

	texture->resource_view = my_texture ? (void*) my_texture : (void*) my_dx11_texture;
	texture->width = my_image_width;
	texture->height = my_image_height;
	texture->file_path = fileName;
	texture->hash = league_hash(fileName.c_str());

	return texture;
}