#include "CircleRotation.h"

#define DEFAULT_DECELERATION    (0.4f)
#define DEFAULT_SENSITIVITY     (3.f)
#define MAX_VELOCITY            (100.0f)

bool CircleRotation::init()
{
	static auto dist = [=](){
		random_device rd;
		mt19937_64 rng(rd());
		uniform_int_distribution<int> dist1(1, 3);
		return dist1(rng);
	};

	rands = dist();

	srand(time(NULL));
	
	return true;
}

void CircleRotation::update(float dt)
{
	playtime += dt;
	createCircle(dt);
	updateCircle(dt);
}

void CircleRotation::ACC(Acceleration* acc, Event* unused_event)
{
	circleRot.x = circleRot.x * DEFAULT_DECELERATION + acc->x * (DEFAULT_SENSITIVITY / 1.0f);
	circleRot.y = circleRot.y * DEFAULT_DECELERATION + acc->y * (DEFAULT_SENSITIVITY / 1.0f);

	if (circleRot.x > MAX_VELOCITY) {
		circleRot.x = MAX_VELOCITY;
	}
	else if (circleRot.x < -MAX_VELOCITY) {
		circleRot.x = -MAX_VELOCITY;
	}
}

float CircleRotation::betweenTwoPoint(Vec2 player, Vec2 circle)
{
	return sqrt(pow(abs(circle.x - player.x), 2) + pow(abs(circle.y - player.x), 2));
}

void CircleRotation::createCircle(float dt)
{
	//static float createTime = 15.0f;
	//createTime += dt * 1.0f;

	//if (createTime >= 15.0f)
	//{
	//	createTime -= createTime;
	//	// 난수 생성 엔진
	//	static auto dist = [=](){
	//		random_device rd;
	//		mt19937_64 rng(rd());
	//		uniform_int_distribution<int> dist1(0, D_DESIGN_WIDTH);
	//		return dist1(rng);
	//	};

	//	Vec2 location = Vec2(D_DESIGN_WIDTH / 2, -D_DESIGN_HEIGHT * 0.5f);

	//	Circle* circle = static_cast<Circle*>(Sprite::create("circle/circle1.png"));
	//	circle->setPosition(location);
	//	this->addChild(circle);

	//	b2BodyDef bodyDef;
	//	bodyDef.type = b2_kinematicBody;
	//	bodyDef.position.Set(location.x / PTM_RATIO, location.y / PTM_RATIO);
	//	bodyDef.userData = nullptr;

	//	circle->body = singleton->_world->CreateBody(&bodyDef);

	//	//b2CircleShape bcircle;
	//	//bcircle.m_radius = 5.f;
	//	//
	//	//b2FixtureDef fixtureDef;
	//	//
	//	//fixtureDef.shape = &bcircle;
	//	//fixtureDef.density = 1.0f;
	//	//fixtureDef.friction = 0.2f;
	//	//fixtureDef.restitution = 0.7f;

	//	circle->body->SetTransform(b2Vec2(location.x / PTM_RATIO, location.y / PTM_RATIO), circle->body->GetAngle());
	//	//circle->body->CreateFixture(&fixtureDef);
	//	BodyParser::getInstance()->parseJsonFile("circle/circle1.json");
	//	BodyParser::getInstance()->b2BodyJson(circle, "circle1", circle->body);

	//	vCircle.push_back(circle);
	//}
	static auto dist = [=](){
		random_device rd;
		mt19937_64 rng(rd());
		uniform_int_distribution<int> dist1(100, D_DESIGN_WIDTH);
		return dist1(rng);
	};

	bigTime += dt;
	middleTime += dt;
	smallTime += dt;

	if (bigTime >= 25.0f)
	{
		bigTime -= bigTime;
		
		Vec2 location = Vec2(D_DESIGN_WIDTH / 2, -D_DESIGN_HEIGHT * 1.1f);

		Circle* circle = static_cast<Circle*>(Sprite::create("circle/circle1.png"));
		circle->setPosition(location);

		for (auto it : vCircle)
		{
			if (it->getBoundingBox().intersectsRect(circle->getBoundingBox()))
			{
				bigTime = 23.0f;
				return;
			}
		}

		this->addChild(circle);

		b2BodyDef bodyDef;
		bodyDef.type = b2_kinematicBody;
		bodyDef.position.Set(location.x / PTM_RATIO, location.y / PTM_RATIO);
		bodyDef.userData = nullptr;

		circle->body = singleton->_world->CreateBody(&bodyDef);

		circle->body->SetTransform(b2Vec2(location.x / PTM_RATIO, location.y / PTM_RATIO), circle->body->GetAngle());
		BodyParser::getInstance()->parseJsonFile("circle/circle1.json");
		BodyParser::getInstance()->b2BodyJson(circle, "circle1", circle->body);

		circle->type = 1;

		vCircle.push_back(circle);

		//-------------------------
		// 3번
		Circle* circle2 = static_cast<Circle*>(Sprite::create("circle/circle2.png"));
		circle2->setPosition(location);
		circle2->setActivity(true);
		this->addChild(circle2);

		b2BodyDef bodyDef2;
		bodyDef2.type = b2_kinematicBody;
		bodyDef2.position.Set(location.x / PTM_RATIO, location.y / PTM_RATIO);
		bodyDef2.userData = nullptr;

		circle2->body = singleton->_world->CreateBody(&bodyDef2);

		circle2->body->SetTransform(b2Vec2(location.x / PTM_RATIO, location.y / PTM_RATIO), circle2->body->GetAngle());
		BodyParser::getInstance()->parseJsonFile("circle/circle2.json");
		BodyParser::getInstance()->b2BodyJson(circle2, "circle2", circle2->body);

		circle2->type = 2;
		vCircle.push_back(circle2);
	}

	if (middleTime >= 9.5f)
	{

		static auto test = [=](){
			random_device rd;
			mt19937_64 rng(rd());
			uniform_int_distribution<int> dist1(200, D_DESIGN_WIDTH - 200);
			return dist1(rng);
		};

		middleTime -= middleTime;

		Vec2 location = Vec2(test(), -D_DESIGN_HEIGHT * 0.35f);

		Circle* circle = static_cast<Circle*>(Sprite::create("circle/circle2.png"));
		circle->setPosition(location);

		for (auto it : vCircle)
		{
			if (it->getBoundingBox().intersectsRect(circle->getBoundingBox()))
			{
				middleTime = 8.0f;
				return;
			}
		}

		this->addChild(circle);

		b2BodyDef bodyDef;
		bodyDef.type = b2_kinematicBody;
		bodyDef.position.Set(location.x / PTM_RATIO, location.y / PTM_RATIO);
		bodyDef.userData = nullptr;

		circle->body = singleton->_world->CreateBody(&bodyDef);

		circle->body->SetTransform(b2Vec2(location.x / PTM_RATIO, location.y / PTM_RATIO), circle->body->GetAngle());
		BodyParser::getInstance()->parseJsonFile("circle/circle2.json");
		BodyParser::getInstance()->b2BodyJson(circle, "circle2", circle->body);


		circle->type = 2;
		vCircle.push_back(circle);

		//----------------------

		int num = rand() % 2 + 1;
		Vec2 location2;

		switch (num)
		{
		case 1:
		location2 = Vec2(circle->getPosition().x + (circle->getContentSize().width / 2) + 30,
			(circle->getPosition().y + circle->getContentSize().width / 2) + 30);
			break;
		case 2:
		location2 = Vec2(circle->getPosition().x - (circle->getContentSize().width / 2) - 30,
			(circle->getPosition().y - circle->getContentSize().width / 2) + 30);
			break;
		}


		Circle* circle2 = static_cast<Circle*>(Sprite::create("circle/circle3.png"));
		circle2->setPosition(location2);
		this->addChild(circle2);

		b2BodyDef bodyDef2;
		bodyDef2.type = b2_kinematicBody;
		bodyDef2.position.Set(location.x / PTM_RATIO, location.y / PTM_RATIO);
		bodyDef2.userData = nullptr;

		circle2->body = singleton->_world->CreateBody(&bodyDef2);

		circle2->body->SetTransform(b2Vec2(location.x / PTM_RATIO, location.y / PTM_RATIO), circle2->body->GetAngle());
		BodyParser::getInstance()->parseJsonFile("circle/circle3.json");
		BodyParser::getInstance()->b2BodyJson(circle2, "circle3", circle2->body);

		circle2->type = 3;
		vCircle.push_back(circle2);
	}

	/* if (smallTime >= 3.0f)
	{

		static auto test = [=](){
			random_device rd;
			mt19937_64 rng(rd());
			uniform_int_distribution<int> dist1(50, D_DESIGN_WIDTH - 50);
			return dist1(rng);
		};


		smallTime -= smallTime;

		Vec2 location = Vec2(test(), -D_DESIGN_HEIGHT * 0.25f);

		Circle* circle = static_cast<Circle*>(Sprite::create("circle/circle3.png"));
		circle->setPosition(location);
		this->addChild(circle);

		b2BodyDef bodyDef;
		bodyDef.type = b2_kinematicBody;
		bodyDef.position.Set(location.x / PTM_RATIO, location.y / PTM_RATIO);
		bodyDef.userData = nullptr;

		circle->body = singleton->_world->CreateBody(&bodyDef);

		circle->body->SetTransform(b2Vec2(location.x / PTM_RATIO, location.y / PTM_RATIO), circle->body->GetAngle());
		BodyParser::getInstance()->parseJsonFile("circle/circle3.json");
		BodyParser::getInstance()->b2BodyJson(circle, "circle3", circle->body);

		circle->type = 3;
		vCircle.push_back(circle);
	}*/


	 static auto NumCircle = [=](){
		 random_device rd;
		 mt19937_64 rng(rd());
		 uniform_int_distribution<int> dist1(3, 3);
		 return dist1(rng);
	 };

	 static float SwitchCreate = 10.0f;
	 SwitchCreate += dt;

	 if (SwitchCreate >= 15.0){
		 SwitchCreate -= SwitchCreate;
		 switch (NumCircle())
		 {
		 case 1:
		 {
			/* static auto test = [=](){
				 random_device rd;
				 mt19937_64 rng(rd());
				 uniform_int_distribution<int> dist1(200, D_DESIGN_WIDTH - 200);
				 return dist1(rng);
			 };

			 middleTime -= middleTime;

			 Vec2 location = Vec2(test(), -D_DESIGN_HEIGHT * 0.35f);

			 Circle* circle = static_cast<Circle*>(Sprite::create("circle/circle2.png"));
			 circle->setPosition(location);
			 this->addChild(circle);

			 b2BodyDef bodyDef;
			 bodyDef.type = b2_kinematicBody;
			 bodyDef.position.Set(location.x / PTM_RATIO, location.y / PTM_RATIO);
			 bodyDef.userData = nullptr;

			 circle->body = singleton->_world->CreateBody(&bodyDef);

			 circle->body->SetTransform(b2Vec2(location.x / PTM_RATIO, location.y / PTM_RATIO), circle->body->GetAngle());
			 BodyParser::getInstance()->parseJsonFile("circle/circle2.json");
			 BodyParser::getInstance()->b2BodyJson(circle, "circle2", circle->body);

			 circle->type = 2;
			 vCircle.push_back(circle);*/
		 }
		 break;
		 case 2:
		 {
			/* static auto test = [=](){
				 random_device rd;
				 mt19937_64 rng(rd());
				 uniform_int_distribution<int> dist1(50, D_DESIGN_WIDTH - 50);
				 return dist1(rng);
			 };


			 smallTime -= smallTime;

			 Vec2 location = Vec2(test(), -D_DESIGN_HEIGHT * 0.25f);

			 Circle* circle = static_cast<Circle*>(Sprite::create("circle/circle3.png"));
			 circle->setPosition(location);
			 this->addChild(circle);

			 b2BodyDef bodyDef;
			 bodyDef.type = b2_kinematicBody;
			 bodyDef.position.Set(location.x / PTM_RATIO, location.y / PTM_RATIO);
			 bodyDef.userData = nullptr;

			 circle->body = singleton->_world->CreateBody(&bodyDef);

			 circle->body->SetTransform(b2Vec2(location.x / PTM_RATIO, location.y / PTM_RATIO), circle->body->GetAngle());
			 BodyParser::getInstance()->parseJsonFile("circle/circle3.json");
			 BodyParser::getInstance()->b2BodyJson(circle, "circle3", circle->body);

			 circle->type = 3;
			 vCircle.push_back(circle);*/
		 }
		 break;
		 case 3:
		 {
			 static auto test = [=](){
				 random_device rd;
				 mt19937_64 rng(rd());
				 uniform_int_distribution<int> dist1(200, D_DESIGN_WIDTH - 200);
				 return dist1(rng);
			 };

			 middleTime -= middleTime;

			 Vec2 location = Vec2(test(), -D_DESIGN_HEIGHT * 0.35f);

			 Circle* circle = static_cast<Circle*>(Sprite::create("circle/circle2.png"));
			 circle->setPosition(location);

			 for (auto it : vCircle)
			 {
				 if (it->getBoundingBox().intersectsRect(circle->getBoundingBox()))
				 {
					 return;
				 }
			 }

			 this->addChild(circle);

			 b2BodyDef bodyDef;
			 bodyDef.type = b2_kinematicBody;
			 bodyDef.position.Set(location.x / PTM_RATIO, location.y / PTM_RATIO);
			 bodyDef.userData = nullptr;

			 circle->body = singleton->_world->CreateBody(&bodyDef);

			 circle->body->SetTransform(b2Vec2(location.x / PTM_RATIO, location.y / PTM_RATIO), circle->body->GetAngle());
			 BodyParser::getInstance()->parseJsonFile("circle/circle2.json");
			 BodyParser::getInstance()->b2BodyJson(circle, "circle2", circle->body);


			 circle->type = 2;
			 vCircle.push_back(circle);

			 //----------------------

			 Vec2 location2 = Vec2(circle->getPosition().x + (circle->getContentSize().width / 2) + 10,
				 (circle->getPosition().y + circle->getContentSize().width / 2) + 10);

			 Circle* circle2 = static_cast<Circle*>(Sprite::create("circle/Circle4.png"));
			 circle2->setPosition(location2);
			 this->addChild(circle2);

			 b2BodyDef bodyDef2;
			 bodyDef2.type = b2_kinematicBody;
			 bodyDef2.position.Set(location.x / PTM_RATIO, location.y / PTM_RATIO);
			 bodyDef2.userData = nullptr;

			 circle2->body = singleton->_world->CreateBody(&bodyDef2);

			 circle2->body->SetTransform(b2Vec2(location.x / PTM_RATIO, location.y / PTM_RATIO), circle2->body->GetAngle());
			 BodyParser::getInstance()->parseJsonFile("circle/Circle4.json");
			 BodyParser::getInstance()->b2BodyJson(circle2, "circle4", circle2->body);

			 circle2->type = 3;
			 vCircle.push_back(circle2);
		 }
		 break;
		 }
	 }
}

void CircleRotation::updateCircle(float dt)
{
	// 계산 과정을 0.5초에 한번씩
	static float calculatorTime = 0.0f;
	calculatorTime += dt;

	//---------------------------
	//---------------------------
	// 원이 올라감
	for (auto it : vCircle)
	{
		it->setPositionY(it->getPositionY() + 4.f);
	}


	//---------------------------
	//---------------------------
	// 원과 플레이어 사이의 거리를 구함

	/*
	if (calculatorTime >= 0.5f)
	{
		calculatorTime -= calculatorTime;
		// 최소 거리 1280
		static float distance = 300;

		if (vCircle.size())
		{
			for (auto it : vCircle)
			{
				// 플레이어와 원 사이의 거리 구함
				float temp = betweenTwoPoint(alice->getPosition(), it->getPosition());
				log("%.f", temp);

				// 지금 현재 가장 작은 원의 거리가 됨
				if (distance >= temp)
				{
					distance = temp;
					// 현재 원을 활성화
					it->setActivity(true);

					// 제일 작은 원을 제외한 나머지는 activity를 false로 정함
					for (auto ij : vCircle)
					{
						// 지금 원을 제외
						if (ij == it)
							continue;
						// 나머지 원을 비활성화
						else
						{
							ij->setActivity(false);
						}
					}
				}
			}
		}
		}
		*/

	if (vCircle.size())
	{
		for (auto it : vCircle)
		{
			switch (it->type)
			{
			case 1:
				it->setActivity(true);
				break;
			case 2:
				if (it->getPositionY() >= 100)
				{
					it->setActivity(true);
				}
				break;
			case 3:
				if (it->getPositionY() >= 200)
				{
					it->setActivity(true);
				}
			}
		}
	}

	//---------------------------
	//---------------------------
	// 원의 Rotation을 수정
	for (auto it : vCircle)
	{
		if (it->getActivity())
		{
			float temp = it->getRotation();
			
			temp += circleRot.x;
			it->setRotation(temp);
		}
	}

	for (auto it : vCircle)
	{
		if (it->getPositionY() > D_DESIGN_HEIGHT)
		{
			elapscircle++;
		}

		it->body->SetTransform(b2Vec2(it->getPosition().x / PTM_RATIO, it->getPosition().y / PTM_RATIO), CC_DEGREES_TO_RADIANS(it->getRotation()));
	}

	singleton->_score = elapscircle * playtime * 20;
	log("%d", singleton->_score);
}

void CircleRotation::circle(int ptype)
{
	Vec2 location;

	static auto dist = [=](){
		random_device rd;
		mt19937_64 rng(rd());
		uniform_int_distribution<int> dist1(0, D_DESIGN_WIDTH);
		return dist1(rng);
	};

	switch (rands)
	{
	case 1:
		location = Vec2(dist(), -D_DESIGN_HEIGHT * 0.5f);
		break;
	case 2:
		location = Vec2(dist(), -D_DESIGN_HEIGHT * 0.35f);
		break;
	case 3:
		location = Vec2(dist(), -D_DESIGN_HEIGHT * 0.15);
		break;
	}

	Circle* circle = static_cast<Circle*>(Sprite::create(String::createWithFormat("circle/circle%d.png", ptype)->getCString()));
	circle->setPosition(location);
	_parent->addChild(circle);

	b2BodyDef bodyDef;
	bodyDef.type = b2_kinematicBody;
	bodyDef.position.Set(location.x / PTM_RATIO, location.y / PTM_RATIO);
	bodyDef.userData = nullptr;

	circle->body = singleton->_world->CreateBody(&bodyDef);

	circle->body->SetTransform(b2Vec2(location.x / PTM_RATIO, location.y / PTM_RATIO), circle->body->GetAngle());

	BodyParser::getInstance()->parseJsonFile(String::createWithFormat("circle/circle%d.json", ptype)->getCString());
	BodyParser::getInstance()->b2BodyJson(circle, String::createWithFormat("circle%d", ptype)->getCString(), circle->body);

	circle->type = ptype;

	vCircle.push_back(circle);
}
