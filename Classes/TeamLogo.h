#pragma once

#include "stdafx.h"

class TeamLogo : public LayerColor
{
private:
public:
	static Scene* createScene();
	bool init() override;
	void changeScene(float dt);
	CREATE_FUNC(TeamLogo);
};