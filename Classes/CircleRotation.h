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
	// ���̷� ����
	void ACC(Acceleration* acc, Event* unused_event);
	// �÷��̾�� �� ������ �Ÿ� ����
	float betweenTwoPoint(Vec2, Vec2);
	// �� ����
	void createCircle(float dt);
	// ���� ���� üũ & Ȱ��ȭ
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
