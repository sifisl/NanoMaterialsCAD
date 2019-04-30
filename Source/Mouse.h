#pragma once
#include "stdafx.h"

class Mouse
{
public:
	Mouse();
	~Mouse();
	float x, y;
	bool isInside(jgn::vec4 sq);

}EXT mouse;

