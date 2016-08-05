#pragma once

#include "stdafx.h"

class Tutorial : public LayerColor
{
private:
	Sprite* tutorial;
public:
	static Scene* createScene();
	bool init() override;
	void ChangeScene(float dt);
	CREATE_FUNC(Tutorial);

public:
};