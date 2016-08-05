#include "stdafx.h"

Singleton* Singleton::_instance = nullptr;
Singleton* Singleton::getInstance()
{
	if (!_instance)
		_instance = new Singleton;
	return _instance;
}