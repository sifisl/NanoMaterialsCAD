#pragma once
#include "stdafx.h"
#include <string>

class Menu
{
public:
	Menu();
	~Menu();

	enum Enums
	{
		EDIT_SELECTED,
		SYSTEM_INFO
	};
	class Element
	{
	public:
		std::string str;
		bool hassubmenu;
	};
	int N_options = 2;
	Element element[2];
	bool show = false;
	jgn::vec2 coords;//the top left corner of the menu


	float fontscale = 0.4;
	void init();
	void draw();

}EXT menu;

