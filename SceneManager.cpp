#include "BaseScene.h"
#include <map>
#include "RootScene.h"
#include "SceneManager.h"

namespace {
	BaseScene* currentScene_ = nullptr;
	std::map<std::string, BaseScene*> sceneMap;
}

namespace SceneFactory {

	RootScene* CreateRootScene() {
		return new RootScene();
	}

}

namespace SceneManager {

	int SceneManager::InitManager() {
		sceneMap.clear();
		// sceneMap.insert(std::make_pair("RootScene", new RootScene()));
		sceneMap.insert(std::make_pair("RootScene", SceneFactory::CreateRootScene()));

		ChangeScene("RootScene");
		return 0;
	}

	void SceneManager::ReleaseManager() {
	}

	int ChangeScene(std::string name) {
		BaseScene* scene = GetScene(name);
		if (scene == nullptr) return -1;

		//見つかった場合の処理
		currentScene_ = scene;
		currentScene_->Init();

		return -1;
	}

	BaseScene* GetCurrentScene() {
		return currentScene_;
	}

	BaseScene* GetScene(std::string name) {
		auto iterator = sceneMap.find(name);
		if (iterator == sceneMap.end()) return nullptr; //見つからなかった

		return iterator->second;
	}
}