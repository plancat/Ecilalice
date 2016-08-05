#pragma once

#include "stdafx.h"

class Background : public Layer
{
public:
	bool init()
	{
		Sprite* FirstBack = Sprite::create("background1.png");
		FirstBack->setAnchorPoint(Vec2(0.5f, 0.0f));
		FirstBack->setPosition(Vec2(D_DESIGN_WIDTH / 2, 0));
		this->addChild(FirstBack, 1, "F");

		backgroundl = Sprite::create("background2.png");
		backgroundl->setAnchorPoint(Vec2(0.5f, 0.0f));
		backgroundl->setPosition(Vec2(D_DESIGN_WIDTH / 2, 2400 * -1));
		this->addChild(backgroundl);

		background2 = Sprite::create("background2.png");
		background2->setAnchorPoint(Vec2(0.5f, 0.0f));
		background2->setPosition(Vec2(D_DESIGN_WIDTH / 2, 2400 * -1 * 2));
		this->addChild(background2);

		return true;
	}
	void update(float dt)
	{
		static float createTime = 0.0f;
		createTime += dt;

		this->getChildByName("F")->setPositionY(this->getChildByName("F")->getPosition().y + 3);

		float curBackground1 = backgroundl->getPosition().y;
		float curBackground2 = background2->getPosition().y;

		if (curBackground1 >= D_DESIGN_HEIGHT)
			backgroundl->setPosition(Vec2(D_DESIGN_WIDTH / 2, background2->getPosition().y - 2400));
		else
			backgroundl->setPositionY(backgroundl->getPosition().y + 3);

		if (curBackground2 >= D_DESIGN_HEIGHT)
			background2->setPosition(Vec2(D_DESIGN_WIDTH / 2, backgroundl->getPosition().y - 2400));
		else
			background2->setPositionY(background2->getPosition().y + 3);

		//-------------------------------------------------------------

		if (createTime >= 0.8f)
		{
			createTime -= createTime;
			createObject();
			createObject();
		}

		if (vObject.size())
		{
			for (auto it : vObject)
			{
				it->setPositionY(it->getPosition().y + 5);
			}
		}


	}

	void createObject()
	{
		static auto dist = [=](){
			random_device rd;
			mt19937_64 rng(rd());
			uniform_int_distribution<int> dist1(1, 5);
			return dist1(rng);
		};

		static auto dist2 = [=](){
			random_device rd;
			mt19937_64 rng(rd());
			uniform_int_distribution<int> dist(10, D_DESIGN_WIDTH - 10);
			return dist(rng);
		};

		Sprite* object;
		switch (dist())
		{
		case 1:
			object = Sprite::create("Background/1.png");
			break;
		case 2:
			object = Sprite::create("Background/2.png");
			break;
		case 3:
			object = Sprite::create("Background/3.png");
			break;
		case 4:
			object = Sprite::create("Background/4.png");
			break;
		case 5:
			object = Sprite::create("Background/5.png");
			break;
		}

		object->setPosition(Vec2(dist2(), -30));
		object->setOpacity(150);
		this->addChild(object,5);

		vObject.pushBack(object);
	}

	CREATE_FUNC(Background);

private:
	Sprite* backgroundl;
	Sprite* background2;
	Vector<Sprite*> vObject;
};