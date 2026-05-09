#pragma once
#include "BaseObject.h"
#include <d3d11.h>
#include "MyDirectX.h"
#include <DirectXMath.h>

class Triangle : public BaseObject {
private:
	ID3D11Buffer* vertexBuffer = nullptr;
	Vertex vertices[3] = {};
public:

	Triangle(float point1x, float point1y, float point2x, float point2y, float point3x, float point3y);
	~Triangle();

	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};

