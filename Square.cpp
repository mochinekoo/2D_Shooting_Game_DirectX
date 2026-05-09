#include "Square.h"

using namespace MyDirectX;

Square::Square(float leftX, float leftY, float width, float height)
	: BaseObject("Square", false) {
	vertices[0] = { leftX, leftY, 0.0f, 1,0,0,1 };
	vertices[1] = { leftX + width, leftY, 0.0f, 1,0,0,1 };
	vertices[2] = { leftX + width, leftY + height, 0.0f, 1,0,0,1 };

	vertices[3] = { leftX, leftY, 0.0f, 1,0,0,1 };
	vertices[4] = { leftX + width, leftY + height, 0.0f, 1,0,0,1 };
	vertices[5] = { leftX, leftY + height, 0.0f, 1,0,0,1 };
}

Square::~Square() {
}

void Square::Initialize() {
	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = sizeof(vertices);
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = vertices;

	HRESULT result = {};
	result = device_->CreateBuffer(&bufferDesc, &initData, &vertexBuffer);
}

void Square::Update()
{
}

void Square::Draw() {
	float color[4] = { 1, 0, 0, 1.0f };

	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	context_->IASetInputLayout(inputLayout);
	context_->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	context_->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	context_->VSSetShader(vertexShader, nullptr, 0);
	context_->PSSetShader(pixelShader, nullptr, 0);

	context_->Draw(6, 0);
}

void Square::Release() {
}
