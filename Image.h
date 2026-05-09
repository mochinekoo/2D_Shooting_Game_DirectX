#pragma once
#include "BaseObject.h"
#include <d3d11.h>
#include "MyDirectX.h"
#include <string>
#include <DirectXMath.h>

class Image : public BaseObject {
private:
	ID3D11Buffer* vertexBuffer = nullptr;
	Vertex vertices[6] = {};
	std::string path_;
    UINT width_ = -1, height_ = -1;
public:
	D3D11_TEXTURE2D_DESC textureDesc = {};
	ID3D11Texture2D* texture = nullptr;
	ID3D11ShaderResourceView* textureView = nullptr;
	ID3D11SamplerState* samplerState = nullptr;
	ID3D11RasterizerState* rastState = nullptr;
	D3D11_RASTERIZER_DESC rastDesc = {};

	Image(std::string path, float leftX, float leftY, float width, float height);
	~Image();

	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};

