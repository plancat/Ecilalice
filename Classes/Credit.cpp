#include "Credit.h"

Scene* Credit::createScene()
{
	auto scene = Scene::create();
	auto layer = Credit::create();
	scene->addChild(layer);
	return scene;
}

bool Credit::init()
{
	if (!LayerColor::initWithColor(Color4B::WHITE))
		return false;



	schedule(schedule_selector(Alice::update), 0.0f);
	return true;
}

void Credit::update(float dt)
{

}

void Credit::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	//BACK
	if (keyCode == EventKeyboard::KeyCode::KEY_BACK)
	{
		Director::getInstance()->popScene();
	}

	//Menu
	if (keyCode == EventKeyboard::KeyCode::KEY_MENU)
	{

	}
}