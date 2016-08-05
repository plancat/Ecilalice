#pragma once

#include "stdafx.h"

class MainMenu : public LayerColor
{
private:
	Sprite* Out;
	Sprite* No;
	Sprite* Yes;
	bool activity = false;
	bool isStart = false;
public:
	static Scene* createScene();
	bool init() override;
	void update(float dt);
	CREATE_FUNC(MainMenu);

public:
	bool onTouchBegan(Touch *touch, Event *unused_event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
};
