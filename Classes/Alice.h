#pragma once

#include "stdafx.h"

class Alice : public Node
{
public:
	bool init();

	static Alice* create();
private:
	Sprite* alice;

};