#include "stdafx.h"

ContactListener::ContactListener() {
}

ContactListener::~ContactListener() {
}

void ContactListener::BeginContact(b2Contact *contact)
{
	_Contact _contact = { contact->GetFixtureA(), contact->GetFixtureB() };
	_vContact.push_back(_contact);
}

void ContactListener::EndContact(b2Contact *contact)
{
	_Contact _contact = { contact->GetFixtureA(), contact->GetFixtureB() };
	if (((Sprite*)contact->GetFixtureB()->GetBody()->GetUserData()) != NULL)
	{
		Sprite* spr = ((Sprite*)contact->GetFixtureB()->GetBody()->GetUserData());
		std::string str = spr->getName();

		if (str == "DONTROT" && singleton->_isLand == true)
		{
			if (rand() % 1)
				spr->setTexture("char/grade1.png");
			else
				spr->setTexture("char/grade2.png");

			singleton->_isLand == false;
		}

	}
	vector<_Contact>::iterator pos;
	pos = find(_vContact.begin(), _vContact.end(), _contact);
	if (pos != _vContact.end()){
		_vContact.erase(pos);
	}
}

void ContactListener::PreSolve(b2Contact *contact, const b2Manifold *oldManifold)
{

}

void ContactListener::PostSolve(b2Contact *contact, const b2ContactImpulse *impulse)
{
	b2Fixture *fixA = contact->GetFixtureA();
	b2Fixture *fixB = contact->GetFixtureB();

	b2Body *bodyA = fixA->GetBody();
	b2Body *bodyB = fixB->GetBody();
	if (((Sprite*)bodyB->GetUserData()) != NULL)
	{
		Sprite* spr = (Sprite*)bodyB->GetUserData();
		std::string str = spr->getName();

		if (str == "DONTROT" && singleton->_isLand == false)
		{
			spr->stopAllActions();

			Animation* animation = Animation::create();
			animation->setDelayPerUnit((0.2f));
			animation->addSpriteFrameWithFile("char/land1.png");
			animation->addSpriteFrameWithFile("char/land2.png");
			animation->addSpriteFrameWithFile("char/land3.png");
			animation->addSpriteFrameWithFile("char/land4.png");

			Animate* animate = Animate::create(animation);
			spr->runAction(animate);

			singleton->_isLand = true;
		}
	}
}

/*
 Begin	
 물리 시뮬레이션의 스텝에서 두 형태가 처음으로 접촉을 시작했을 때 호출된다.
 해당 콜백 함수에서 FALSE 를 리턴하면 뒤이어 발생하는 이벤트를 무시할 수도 있다.
 그렇게 하면, preSolve, postSolve 콜백 함수는 호출되지 않으며 발생한 힘(충돌)을
 계산하지 않는다.
 그렇지만 end 콜백 함수는 여전히 호출된다.

 preSolve	
 두 형태가 접촉을 계속하는 동안 호출된다.
 FALSE를 리턴하면 해당 시뮬레이션 스텝에서 무시되며,
 TRUE를 리턴하면 정상 처리된다.

 postSolve	
 두 형태가 접촉했으며, 충돌을 이미 처리했을 때 호출된다.
 이 콜백 함수로 충돌력을 계산할 수 있는데 Impulse에 충돌의 충격량이 전달되어 온다.

 End	
 충돌 상황이 이번 스텝에서 해제됐을 때, 즉 두 바디의 접촉이 떨어졌을 때 호출된다.
*/