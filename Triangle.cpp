#include "Triangle.h"
#include "BaseObject.h"
#include "MyDirectX.h"
#include "input.h"

using namespace MyDirectX;

Triangle::Triangle(float point1x, float point1y, float point2x, float point2y, float point3x, float point3y)
	: BaseObject("Triangle", false) {
	vertices[0] = { point1x, point1y, 0.0f, 1,1,1,1 };
	vertices[1] = { point2x, point2y, 0.0f, 1,1,1,1 };
	vertices[2] = { point3x, point3y, 0.0f, 1,1,1,1 };
}

Triangle::~Triangle() {
}

void Triangle::Initialize() {
	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = sizeof(vertices);
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = vertices;

	device_->CreateBuffer(&bufferDesc, &initData, &vertexBuffer);
}

void Triangle::Update() {
	context_->UpdateSubresource(vertexBuffer, 0, nullptr, vertices, 0, 0);
}

void Triangle::Draw() {
	float color[4] = { 1, 1, 1, 1.0f };

	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	context_->IASetInputLayout(inputLayout);
	context_->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	context_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	context_->VSSetShader(vertexShader, nullptr, 0);
	context_->PSSetShader(pixelShader, nullptr, 0);

	context_->Draw(3, 0);
}

void Triangle::Release() {
}
