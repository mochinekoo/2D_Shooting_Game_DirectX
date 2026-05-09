#pragma once
#include <string>

class BaseObject {
protected:
	bool isDead_;
	std::string name_;
private:
public:

	BaseObject(std::string name, bool isDead) {
		name_ = name;
		isDead_ = isDead;
	};
	~BaseObject() {};

	virtual void Initialize() = 0;
	virtual void Draw() = 0;
	virtual void Update() = 0;
	virtual void Release() = 0;

};