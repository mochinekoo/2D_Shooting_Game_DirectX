#include "RunningScene.h"
#include <array>
#include "Image.h"

namespace {
	Image* image = nullptr;
}

RunningScene::RunningScene()
	: BaseScene("RunningScene") {
	sceneCounter_ = 0;
}

RunningScene::~RunningScene() {
}

void RunningScene::Init() {
	image = new Image("circle.png", 0.5f, 0.5f, 1.0f, 1.0f);
	image->Initialize();
}

void RunningScene::Update() {
	image->Update();
}

void RunningScene::Draw() {
	image->Draw();
}

void RunningScene::Release() {
}