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

	// �� ����, ������Ʈ
	CircleRotation* circle;
	ContactListener* contact;

	// Pause �����̵�
	Vec2 begine;
	Vec2 end;
	SlideState state = SlideState::NORMAL;
	float dtime = 0.0f;

	bool pause = false;
	MenuKey* menuKey;

	// ���
	Background* background;

	Sprite* End;
	Sprite* Re;
	Sprite* Main;
	bool GameOver = false;
public:
    static Scene* createScene();
    bool init() override;
	void update(float dt);
	// ���̷� ����
	void onAcceleration(Acceleration* acc, Event* unused_event);

	// ��ġ
	bool onTouchBegan(Touch* touch, Event* unused_event) override;
	void onTouchMoved(Touch* touch, Event* unused_event) override;
	void onTouchEnded(Touch* touch, Event* unused_event) override;

	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	CREATE_FUNC(InGame);
};