#pragma once

#include "stdafx.h"

class Credit : public LayerColor
{
private:
public:
	static Scene* createScene();
	bool init() override;
	void update(float dt);
	CREATE_FUNC(Credit);

public:
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
};