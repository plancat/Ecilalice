#include "stdafx.h"

bool Alice::init()
{
	Vec2 location = Vec2(D_DESIGN_WIDTH / 2, 1000);
	alice = Sprite::create("char/falling1.png");
	alice->setPosition(location);
	this->addChild(alice);

	/*alice->autorelease();
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
	circle.m_radius = 1.3f;

	b2FixtureDef fixtureDef;

	fixtureDef.shape = &circle;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.7f;
	fixtureDef.restitution = 0.7f;

	body->CreateFixture(&fixtureDef);*/

	return true;
}

Alice* Alice::create()
{
	/*Alice* alice = new Alice();
	Vec2 location = Vec2(D_DESIGN_WIDTH / 2, 1000);
	if (alice && alice->initWithFile("char/falling1.png"))
	{
		alice->autorelease();
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
		circle.m_radius = 1.3f;

		b2FixtureDef fixtureDef;

		fixtureDef.shape = &circle;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.7f;
		fixtureDef.restitution = 0.7f;

		body->CreateFixture(&fixtureDef);

		return alice;
	}
	CC_SAFE_DELETE(alice);
	return nullptr;*/

	return nullptr;
}