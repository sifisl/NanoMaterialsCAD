#include "Menu.h"
#include "JGN_StrokeCharacter.h"


Menu::Menu()
{
}


Menu::~Menu()
{
}
void Menu::init()
{
	menu.element[0].str = std::string("Edit Selected");
	menu.element[0].hassubmenu = true;

	menu.element[1].str = std::string("System Information");
	menu.element[1].hassubmenu = false;

}

void Menu::draw()
{
	if (this->show)
	{
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_LIGHTING);
		glColor3f(0, 0, 0);
		glLoadIdentity();
		glTranslatef(this->coords.x, this->coords.y - write::max_height*0.4, 5);
		glBegin(GL_QUADS);
		glVertex2f(0, write::max_height*0.4);
		glVertex2f(0.5, write::max_height*0.4);
		glVertex2f(0.5, -0.01 - (menu.N_options - 1)*(write::max_height*0.4 + 0.02));
		glVertex2f(0, -0.01 - (menu.N_options - 1)*(write::max_height*0.4 + 0.02));
		glEnd();
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, Font);
		glScalef(0.4, 0.4, 0.4);
		glColor3f(1, 0, 0);
		for (int i = 0; i < menu.N_options; i++)
		{
			glLoadIdentity();
			glTranslatef(this->coords.x, this->coords.y -i * (write::max_height*0.4 + 0.02) - write::max_height*0.4, 5);
			glScalef(0.4, 0.4, 0.4);
			write::string(menu.element[i].str.c_str());
			if (menu.element[i].hassubmenu)
			{
				glLoadIdentity();
				glTranslatef(this->coords.x+0.5, this->coords.y -i * (write::max_height*0.4 + 0.02) - write::max_height*0.4, 5);
				glScalef(0.4, 0.4, 0.4);
				write::rtl::character('>');
			}
		}
		glLoadIdentity();
	}
}
