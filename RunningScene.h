#pragma once
#include "BaseScene.h"
class RunningScene : public BaseScene {
private:
protected:
public:
	RunningScene();
	~RunningScene();

	void Init() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};

