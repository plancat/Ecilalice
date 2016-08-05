#pragma once

#include "stdafx.h"

class Singleton
{
public:
	static Singleton* _instance;
	static Singleton* getInstance();

	b2World* _world;

	bool _isLand = false;

	int _score = 0;
};