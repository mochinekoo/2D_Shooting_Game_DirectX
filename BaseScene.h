#pragma once
#include <string>

class BaseScene {
private:
protected:
	std::string name_;
	int sceneCounter_;
public:
	BaseScene(std::string name) {
		sceneCounter_ = 0;
		name_ = name;
	};
	~BaseScene() {};

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Release() = 0;

	std::string GetName() {
		return name_;
	};
};