#pragma once
#include "stdafx.h"
#include "VSystem.h"
#include "JGN_Resource.h"

class Utool
{//use tool
public:
	bool sellect();
	void distance();
	bool _singlesellect();//single select and returns if there are any sellected items
	bool _multisellect();//real time select and returns if there are any sellected items
};

class ToolBar
{
public:
	ToolBar();
	~ToolBar();

	enum class Tool
	{
		ROTATE,
		SELECT,
		TRANSLATE,
		DISTANCE
	};
	const int N_tools = 4;//Number of tools
	jgn::vec3 position[4/*N_tools*/][4];//top left corner of the button
	const float size = 0.15;
	Tool selectedTool = Tool::ROTATE;//0=rotate 1=
	Utool usetool;

	void draw();
	void _drawButton(const int i);
	void initPositions();
	void toolclicked(const float x, const float y);//takes the mouse parameters 
}EXT tb;

