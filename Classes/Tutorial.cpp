#include "Tutorial.h"

Scene* Tutorial::createScene()
{
	auto scene = Scene::create();
	auto layer = Tutorial::create();
	scene->addChild(layer);
	return scene;
}

bool Tutorial::init()
{
	if (!LayerColor::initWithColor(Color4B::WHITE))
		return false;

	tutorial = Sprite::create("tutorial.png");
	tutorial->setPosition(Vec2(D_DESIGN_WIDTH / 2, D_DESIGN_HEIGHT / 2));
	this->addChild(tutorial);

	this->schedule(schedule_selector(Tutorial::ChangeScene), 3.0f);

	return true;
}

void Tutorial::ChangeScene(float dt)
{
	this->unschedule(schedule_selector(Tutorial::ChangeScene));
	Director::getInstance()->replaceScene(TransitionFade::create(2.0f, InGame::createScene()));
}