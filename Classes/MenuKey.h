#pragma once

#include "stdafx.h"

class MenuKey : public LayerColor
{
private:
	LayerColor* showLayer;

	Sprite* backKey;
	Sprite* homeKey;
	Sprite* replayKey;

	int nEvent;
	bool close;
	float dtime = 0.0f;

	bool setting = false;
public:
	bool init()
	{
		if (!LayerColor::initWithColor(Color4B(0, 0, 0, 0)))
			return false;

		showLayer = LayerColor::create(Color4B(0, 0, 0, 100));
		showLayer->setAnchorPoint(Vec2::ZERO);
		showLayer->setContentSize(Size(200, D_DESIGN_HEIGHT));
		showLayer->setPosition(Vec2::ZERO);
		this->addChild(showLayer);


		backKey = Sprite::create("Menu/backKey.png");
		backKey->setPosition(Vec2(showLayer->getContentSize().width / 2, D_DESIGN_HEIGHT / 2 + 200));
		backKey->setScale(1.5f);
		this->addChild(backKey);

		replayKey = Sprite::create("Menu/replayKey.png");
		replayKey->setPosition(Vec2(showLayer->getContentSize().width / 2, D_DESIGN_HEIGHT / 2 - 200));
		replayKey->setScale(1.5f);
		this->addChild(replayKey);

		homeKey = Sprite::create("Menu/homeKey.png");
		homeKey->setPosition(Vec2(showLayer->getContentSize().width / 2, D_DESIGN_HEIGHT / 2));
		homeKey->setScale(1.5f);
		this->addChild(homeKey);

		close = false;
		nEvent = 0;

		return true;
	}
	void closeMenu()
	{
		close = true;
	}
	void popup()
	{
		this->setVisible(true);
	}
	int getEvent()
	{
		return nEvent;
	}
	int onTouchStart(Touch* touch)
	{
		if (backKey->getBoundingBox().containsPoint(touch->getLocation()))
			nEvent = 0;
		else if (homeKey->getBoundingBox().containsPoint(touch->getLocation()))
			nEvent = 2;
		else if (replayKey->getBoundingBox().containsPoint(touch->getLocation()))
			nEvent = 3;

		return 0;
	};

	void update(float dt)
	{
		if (close)
		{
			dtime += dt * 3.0f;

			float move = Lerp(showLayer->getPosition().y, (float)D_DESIGN_HEIGHT + 10, dtime);
			showLayer->setPositionY(move);

			float backMove = Lerp(backKey->getPosition().y, (float)D_DESIGN_HEIGHT + 100, dtime);
			backKey->setPositionY(backMove);

			float replayMove = Lerp(replayKey->getPosition().y, (float)D_DESIGN_HEIGHT + 100, dtime);
			replayKey->setPositionY(replayMove);

			float homeMove = Lerp(homeKey->getPosition().y, (float)D_DESIGN_HEIGHT + 100, dtime);
			homeKey->setPositionY(homeMove);


			if (move >= D_DESIGN_HEIGHT)
			{
				close = false;
				dtime = 0.0f;
				nEvent = 0;
			}

		}
	}

	void LEFTsetting()
	{
		showLayer->setPosition(Vec2(D_DESIGN_WIDTH, 0));
		backKey->setPosition(Vec2(D_DESIGN_WIDTH + showLayer->getContentSize().width / 2, D_DESIGN_HEIGHT / 2 + 200));
		replayKey->setPosition(Vec2(D_DESIGN_WIDTH + showLayer->getContentSize().width / 2, D_DESIGN_HEIGHT / 2 - 200));
		homeKey->setPosition(Vec2(D_DESIGN_WIDTH + showLayer->getContentSize().width / 2, D_DESIGN_HEIGHT / 2));
	}

	void RIGHTsetting()
	{
		showLayer->setPosition(Vec2(showLayer->getContentSize().width * -1, 0));
		backKey->setPosition(Vec2(showLayer->getContentSize().width / 2 * -1, D_DESIGN_HEIGHT / 2 + 200));
		replayKey->setPosition(Vec2(showLayer->getContentSize().width / 2 * -1, D_DESIGN_HEIGHT / 2 - 200));
		homeKey->setPosition(Vec2(showLayer->getContentSize().width / 2 * -1, D_DESIGN_HEIGHT / 2));
	}

	void LEFTupdate(float dt)
	{
		popup();

		float layerMove = Lerp(showLayer->getPosition().x, D_DESIGN_WIDTH - showLayer->getContentSize().width, dt);
		showLayer->setPositionX(layerMove);

		float backMove = Lerp(backKey->getPosition().x, D_DESIGN_WIDTH - showLayer->getContentSize().width / 2, dt);
		backKey->setPositionX(backMove);

		float replayMove = Lerp(replayKey->getPosition().x, D_DESIGN_WIDTH - showLayer->getContentSize().width / 2, dt);
		replayKey->setPositionX(replayMove);

		float homeMove = Lerp(homeKey->getPosition().x, D_DESIGN_WIDTH - showLayer->getContentSize().width / 2, dt);
		homeKey->setPositionX(homeMove);

		if (layerMove >= D_DESIGN_WIDTH -1)
		{
			nEvent = 5;
		}
	}

	void RIGHTupdate(float dt)
	{
		popup();

		float layerMove = Lerp(showLayer->getPosition().x, 1.0f, dt);
		showLayer->setPositionX(layerMove);

		float backMove = Lerp(backKey->getPosition().x, showLayer->getContentSize().width / 2, dt);
		backKey->setPositionX(backMove);

		float replayMove = Lerp(replayKey->getPosition().x, showLayer->getContentSize().width / 2, dt);
		replayKey->setPositionX(replayMove);

		float homeMove = Lerp(homeKey->getPosition().x, showLayer->getContentSize().width / 2, dt);
		homeKey->setPositionX(homeMove);

	}

	LayerColor* getLayer()
	{
		return showLayer;
	}

	void setFalse()
	{
		setting = false;
	}

	void setTrue()
	{
		setting = true;
	}

	void onTouchEnd(Touch* touch)
	{

	};
};