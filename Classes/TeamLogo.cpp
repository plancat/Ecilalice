#include "TeamLogo.h"


Scene* TeamLogo::createScene()
{
	auto scene = Scene::create();
	auto layer = TeamLogo::create();
	scene->addChild(layer);
	return scene;
}

bool TeamLogo::init()
{
	if (!LayerColor::initWithColor(Color4B::WHITE))
		return false;

	Sprite* teamLogo = Sprite::create("Logo.png");
	teamLogo->setPosition(Vec2(D_DESIGN_WIDTH / 2, D_DESIGN_HEIGHT / 2));
	this->addChild(teamLogo);

	schedule(schedule_selector(TeamLogo::changeScene), 1.0f);

	return true;
}

void TeamLogo::changeScene(float dt)
{
	this->unschedule(schedule_selector(TeamLogo::changeScene));
	Director::getInstance()->replaceScene(TransitionFade::create(1.0f, MainMenu::createScene()));
}