#include "BaseScene.h"
#include "RootScene.h"
#include <array>

namespace {
}

RootScene::RootScene()
	: BaseScene("RootScene") {
	sceneCounter_ = 0;
}

RootScene::~RootScene() {
}

void RootScene::Init() {
}

void RootScene::Update() {
}

void RootScene::Draw() {
}

void RootScene::Release() {
}
