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
 ���� �ùķ��̼��� ���ܿ��� �� ���°� ó������ ������ �������� �� ȣ��ȴ�.
 �ش� �ݹ� �Լ����� FALSE �� �����ϸ� ���̾� �߻��ϴ� �̺�Ʈ�� ������ ���� �ִ�.
 �׷��� �ϸ�, preSolve, postSolve �ݹ� �Լ��� ȣ����� ������ �߻��� ��(�浹)��
 ������� �ʴ´�.
 �׷����� end �ݹ� �Լ��� ������ ȣ��ȴ�.

 preSolve	
 �� ���°� ������ ����ϴ� ���� ȣ��ȴ�.
 FALSE�� �����ϸ� �ش� �ùķ��̼� ���ܿ��� ���õǸ�,
 TRUE�� �����ϸ� ���� ó���ȴ�.

 postSolve	
 �� ���°� ����������, �浹�� �̹� ó������ �� ȣ��ȴ�.
 �� �ݹ� �Լ��� �浹���� ����� �� �ִµ� Impulse�� �浹�� ��ݷ��� ���޵Ǿ� �´�.

 End	
 �浹 ��Ȳ�� �̹� ���ܿ��� �������� ��, �� �� �ٵ��� ������ �������� �� ȣ��ȴ�.
*/