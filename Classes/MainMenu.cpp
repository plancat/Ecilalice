#include "MainMenu.h"

Scene* MainMenu::createScene()
{
	auto scene = Scene::create();
	auto layer = MainMenu::create();
	scene->addChild(layer);
	return scene;
}

bool MainMenu::init()
{
	if (!LayerColor::initWithColor(Color4B::WHITE))
		return false;

	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("back.mp3", true);

	// Touch 리스너 등록
	this->setTouchEnabled(true);
	this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);

	// Key 리스너 리스너 등록
	auto listener2 = EventListenerKeyboard::create();
	listener2->onKeyReleased = CC_CALLBACK_2(MainMenu::onKeyReleased, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener2, this);


	Sprite* background = Sprite::create("background1.png");
	background->setPosition(Vec2(D_DESIGN_WIDTH / 2, D_DESIGN_HEIGHT / 2));
	this->addChild(background);

	Sprite* Title = Sprite::create("MainMenu/Title.png");
	Title->setPosition(Vec2(D_DESIGN_WIDTH / 2, D_DESIGN_HEIGHT / 2 + 450));
	this->addChild(Title);

	Sprite* Four = Sprite::create("MainMenu/44.png");
	Four->setPosition(Vec2(304, 694));
	Four->setScale(0.3f);
	this->addChild(Four);

	Four->runAction(RepeatForever::create(RotateBy::create(2, 30)));

	Sprite* Three = Sprite::create("MainMenu/33.png");
	Three->setPosition(Vec2(304, 694));
	Three->setScale(0.35f);
	this->addChild(Three);

	Three->runAction(RepeatForever::create(RotateBy::create(2, -30)));

	Sprite* Two = Sprite::create("MainMenu/22.png");
	Two->setPosition(Vec2(304, 694));
	Two->setScale(0.53f);
	this->addChild(Two);

	Two->runAction(RepeatForever::create(RotateBy::create(2, 30)));

	Sprite* One = Sprite::create("MainMenu/11.png");
	One->setPosition(Vec2(304, 694));
	One->setScale(0.35f);
	this->addChild(One);

	One->runAction(RepeatForever::create(RotateBy::create(2, -30)));


	Sprite* touch = Sprite::create("MainMenu/touch.png");
	touch->setPosition(Vec2(D_DESIGN_WIDTH / 2, D_DESIGN_HEIGHT / 2 - 500));
	this->addChild(touch);

	touch->runAction(RepeatForever::create(Sequence::create(FadeOut::create(1.0f), FadeIn::create(1.5f), NULL)));


	Sprite* Alice = Sprite::create("MainMenu/Alice.png");
	Alice->setScale(0.9f);
	Alice->setPosition(Vec2(606, 346));
	this->addChild(Alice);


	Out = Sprite::create("Out/out.png");
	Out->setPosition(Vec2(D_DESIGN_WIDTH / 2, D_DESIGN_HEIGHT / 2));
	Out->setVisible(false);
	this->addChild(Out);

	No = Sprite::create("Out/no.png");
	No->setVisible(false);
	No->setPosition(Vec2(D_DESIGN_WIDTH / 2 - 100, D_DESIGN_HEIGHT / 2 - 100));
	this->addChild(No);

	Yes = Sprite::create("Out/yes.png");
	Yes->setPosition(Vec2(D_DESIGN_WIDTH / 2 + 100, D_DESIGN_HEIGHT / 2 - 100));
	Yes->setVisible(false);
	this->addChild(Yes);

	isStart = false;

	schedule(schedule_selector(MainMenu::update), 0.0f);
	return true;
}

void MainMenu::update(float dt)
{
	if (isStart)
	{
		this->unschedule(schedule_selector(MainMenu::update));

		/*Tutorial* tutorial = new Tutorial();
		tutorial->init();
		this->addChild(tutorial);*/

		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, Tutorial::createScene()));

		isStart = false;
	}
}

bool MainMenu::onTouchBegan(Touch *touch, Event *unused_event)
{
	if (!activity)
	{
		isStart = true;
	}
	else
	{
		if (Yes->getBoundingBox().containsPoint(touch->getLocation()))
		{
			Director::getInstance()->end();
		}
		else if (No->getBoundingBox().containsPoint(touch->getLocation()))
		{
			activity = false;
			Out->setVisible(false);
			No->setVisible(false);
			Yes->setVisible(false);
		}
	}

	return true;
}

void MainMenu::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	//BACK
	if (keyCode == EventKeyboard::KeyCode::KEY_BACK)
	{
		if (!activity)
		{
			activity = true;
			Out->setVisible(true);
			No->setVisible(true);
			Yes->setVisible(true);
		}
		else
		{
			activity = false;
			Out->setVisible(false);
			No->setVisible(false);
			Yes->setVisible(false);
		}
	}

	//Menu
	if (keyCode == EventKeyboard::KeyCode::KEY_MENU)
	{

	}
}