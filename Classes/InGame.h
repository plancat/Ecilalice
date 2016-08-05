#pragma once

#include "stdafx.h"
#define singleton Singleton::getInstance()

enum class SlideState
{
	NORMAL,
	LEFT,
	RIGHT
};

class CircleRotation;
class InGame : public LayerColor
{
private:
	Sprite* alice;

	// 공 생성, 업데이트
	CircleRotation* circle;
	ContactListener* contact;

	// Pause 슬라이드
	Vec2 begine;
	Vec2 end;
	SlideState state = SlideState::NORMAL;
	float dtime = 0.0f;

	bool pause = false;
	MenuKey* menuKey;

	// 배경
	Background* background;

	Sprite* End;
	Sprite* Re;
	Sprite* Main;
	bool GameOver = false;
public:
    static Scene* createScene();
    bool init() override;
	void update(float dt);
	// 자이로 센서
	void onAcceleration(Acceleration* acc, Event* unused_event);

	// 터치
	bool onTouchBegan(Touch* touch, Event* unused_event) override;
	void onTouchMoved(Touch* touch, Event* unused_event) override;
	void onTouchEnded(Touch* touch, Event* unused_event) override;

	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	CREATE_FUNC(InGame);
};