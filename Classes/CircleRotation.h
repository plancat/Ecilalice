#pragma once

#include "stdafx.h"

class Circle : public Sprite
{
public:
	float getRadius()
	{
		this->getContentSize().width / 2;
	}
	bool getActivity()
	{
		return activity;
	}
	void setActivity(bool ac)
	{
		activity = ac;
	}
	b2Body* body;
	int type;
private:
	bool activity = false;
};

class CircleRotation : public Layer
{
public:
	bool init() override;
	void update(float dt);
public:
	// 자이로 센서
	void ACC(Acceleration* acc, Event* unused_event);
	// 플레이어와 원 사이의 거리 구함
	float betweenTwoPoint(Vec2, Vec2);
	// 원 생성
	void createCircle(float dt);
	// 원의 상태 체크 & 활성화
	void updateCircle(float dt);

	void circle(int ptype);

private:
	Sprite* alice;
	Vec2 circleRot;
	vector<Circle*> vCircle;
	int rands;

	float bigTime = 20.0;
	float middleTime = 0.0;
	float smallTime = 0.0f;

	float playtime = 0;
	float elapscircle = 0;

};
