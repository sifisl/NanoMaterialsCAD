#pragma once
#include "stdafx.h"

class Bonds
{
public:
	Bonds();
	~Bonds();

	std::vector<jgn::vec6d> edges;// starting and fin vector for bond



	int NBonds = 0;// Number of bonds
	void CalcBonds(float maxDist);// Calculate the bonds
	void drawBonds(float scale);// Draw all bonds (OpenGL) with a scale factor which works like glscale
}EXT bonds;

