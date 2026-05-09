#pragma once
#include "BaseObject.h"
#include <d3d11.h>
#include "MyDirectX.h"

class Square : public BaseObject {
private:
	ID3D11Buffer* vertexBuffer = nullptr;
	Vertex vertices[6] = {};
public:
	Square(float leftX, float leftY, float width, float height);
	~Square();

	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};

