#include "stdafx.h"

Scene* InGame::createScene()
{
	auto scene = Scene::create();
	auto layer = InGame::create();
	scene->addChild(layer);
	return scene;
}

bool InGame::init()
{
	if (!LayerColor::initWithColor(Color4B::WHITE))
		return false;

	// 자이로 센서
	this->setAccelerometerEnabled(true);

	// 터치 리스너
	this->setTouchEnabled(true);
	this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);


	// Key 리스너 리스너 등록
	auto listener2 = EventListenerKeyboard::create();
	listener2->onKeyReleased = CC_CALLBACK_2(InGame::onKeyReleased, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener2, this);

	// 배경
	background = new Background();
	background->init();
	this->addChild(background);

	// 원 초기화
	circle = new CircleRotation();
	circle->init();
	this->addChild(circle);

	//MenuKey
	menuKey = new MenuKey();
	menuKey->init();
	menuKey->setVisible(false);
	pause = false;
	this->addChild(menuKey, 3);

	// Box2D 중력
	b2Vec2 gravity = b2Vec2(0.f, -0.05f);

	singleton->_world = new b2World(gravity);
	singleton->_world->SetAllowSleeping(true);
	singleton->_world->SetContinuousPhysics(true);

	contact = new ContactListener();
	singleton->_world->SetContactListener((b2ContactListener*)contact);

	// 엘리스 초기화
	/*alice = new Alice();
	alice->init();
	this->addChild(alice);*/

	Vec2 location = Vec2(D_DESIGN_WIDTH / 2, 1000);
	alice = Sprite::create("char/falling1.png");
	alice->setPosition(location);
	//alice->setAnchorPoint(Vec2(0.5, 0));
	this->addChild(alice);

	alice->setPosition(location);
	alice->setName("DONTROT");
	alice->setScale(1.35f);

	Animation* animation = Animation::create();
	animation->setDelayPerUnit((0.2f));
	animation->addSpriteFrameWithFile("char/falling1.png");
	animation->addSpriteFrameWithFile("char/falling2.png");
	animation->addSpriteFrameWithFile("char/falling3.png");
	animation->addSpriteFrameWithFile("char/falling4.png");
	animation->addSpriteFrameWithFile("char/falling5.png");

	Animate* animate = Animate::create(animation);
	alice->runAction(RepeatForever::create(Sequence::create(animate, DelayTime::create(0.3f), NULL)));

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(location.x / PTM_RATIO, location.y / PTM_RATIO);
	bodyDef.userData = alice;

	b2Body* body = singleton->_world->CreateBody(&bodyDef);

	b2CircleShape circle;
	circle.m_radius = 1.f;

	b2FixtureDef fixtureDef;

	fixtureDef.shape = &circle;
	fixtureDef.density = 24.2f;
	fixtureDef.friction = 1.0f;
	fixtureDef.restitution = 0.0f;

	body->CreateFixture(&fixtureDef);
	//------------------------------

	End = Sprite::create("game_over_popup.png");
	End->setVisible(false);
	End->setPosition(Vec2(D_DESIGN_WIDTH / 2, D_DESIGN_HEIGHT / 2));
	this->addChild(End);

	Re = Sprite::create("Re.png");
	Re->setPosition(Vec2(D_DESIGN_WIDTH / 2+200, D_DESIGN_HEIGHT / 2-500));
	Re->setVisible(false);
	this->addChild(Re);

	Main = Sprite::create("Main.png");
	Main->setPosition(Vec2(D_DESIGN_WIDTH / 2 -200, D_DESIGN_HEIGHT / 2-500));
	Main->setVisible(false);
	this->addChild(Main);

	GameOver = false;

	this->schedule(schedule_selector(InGame::update));
	return true;
}

void InGame::update(float dt)
{
	if (!GameOver)
	{
		if (!pause)
		{
			singleton->_world->Step(dt, 8, 3);

			if (singleton->_world->GetBodyList()){
				for (b2Body* b = singleton->_world->GetBodyList(); b; b = b->GetNext())
				{
					if (b->GetUserData() != nullptr)
					{
						Sprite* spriteData = (Sprite*)b->GetUserData();
						spriteData->setPosition(Vec2(b->GetPosition().x * PTM_RATIO, b->GetPosition().y * PTM_RATIO));
						if (spriteData->getName() != "DONTROT")
							spriteData->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
					}
				}
			}
			circle->update(dt);

			//----------------
			// 화면 밖 = 아웃
			if (alice->getPosition().x <= 0)
				GameOver = true;
			else if (alice->getPosition().x >= D_DESIGN_WIDTH)
				GameOver = true;
			else if (alice->getPosition().y <= 0)
				GameOver = true;
			else if (alice->getPosition().y >= D_DESIGN_HEIGHT)
				GameOver = true;


			if (GameOver)
			{
				End->setVisible(true);
				Re->setVisible(true);
				Main->setVisible(true);

				char temp[255];
				sprintf(temp, "%d", singleton->_score);
				Label* score = Label::create(temp, "Ariel", 100);
				score->setColor(Color3B::WHITE);
				score->setPosition(Vec2(D_DESIGN_WIDTH / 2, D_DESIGN_HEIGHT / 2 - 150));
				this->addChild(score);
			}
		}

		if (state != SlideState::NORMAL)
		{
			// 왼쪽
			if (state == SlideState::LEFT)
			{
				dtime += dt * 3.0f;
				// Lerp를 사용한 Pause버튼 구현
				menuKey->LEFTupdate(dtime);
			}
			// 오른쪽
			else if (state == SlideState::RIGHT)
			{
				dtime += dt * 3.0f;
				// Lerp를 사용한 Pause버튼 구현
				menuKey->RIGHTupdate(dtime);
			}
		}

		// Pause 업데이트
		menuKey->update(dt);

		if (!pause)
		{
			// Background 업데이트
			background->update(dt);
		}
	}
}

bool InGame::onTouchBegan(Touch* touch, Event* unused_event)
{
	begine = touch->getLocation();
	end = touch->getLocation();

	if (GameOver)
	{
		if (Re->getBoundingBox().containsPoint(touch->getLocation()))
		{
			Director::getInstance()->replaceScene(TransitionFade::create(1.0f, InGame::createScene()));
		}
		if (Main->getBoundingBox().containsPoint(touch->getLocation()))
		{
			Director::getInstance()->replaceScene(TransitionFade::create(1.0f, MainMenu::createScene()));
		}
	}
	return true;
}

void InGame::onTouchMoved(Touch* touch, Event* unused_event)
{
	if (!pause)
		end = touch->getLocation();
}

void InGame::onTouchEnded(Touch* touch, Event* unused_event)
{
	// 슬라이드
	// 왼쪽
	if (!pause)
	{
		if (begine.x - 100 >= end.x)
		{
			menuKey->popup();
			state = SlideState::LEFT;
			dtime = 0.0f;
			pause = true;
			menuKey->LEFTsetting();
		}
		// 오른쪽
		else if (begine.x + 100 <= end.x)
		{
			menuKey->popup();
			state = SlideState::RIGHT;
			dtime = 0.0f;
			pause = true;
			menuKey->RIGHTsetting();
		}
	}
	else
	{
		menuKey->onTouchStart(touch);
		switch (menuKey->getEvent())
		{
		case 0:
			pause = false;
			menuKey->closeMenu();
			break;
		case 1:
			break;
		case 2:
			Director::getInstance()->replaceScene(TransitionFade::create(1.5f, MainMenu::createScene()));
			break;
		case 3:
			Director::getInstance()->replaceScene(TransitionFade::create(1.5f, InGame::createScene()));
			break;
		}
		state = SlideState::NORMAL;
	}
}

void InGame::onAcceleration(Acceleration* acc, Event* unused_event)
{
	circle->ACC(acc, unused_event);
}


void InGame::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	//BACK
	if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		Acceleration acc;
		acc.x = -0.2;
		acc.y = 0;

		circle->ACC(&acc, event);
	}

	//Menu
	if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		Acceleration acc;
		acc.x = 0.2;
		acc.y = 0;

		circle->ACC(&acc, event);
	}
}