#include "ToolBar.h"


ToolBar::ToolBar()
{
}


ToolBar::~ToolBar()
{
}
void ToolBar::_drawButton(const int i)
{
	glBegin(GL_QUADS);
	glTexCoord2d(0, 1);
	//glVertex2d(dipleft, dipapan);
	glVertex2dvec3(this->position[i][1]);

	glTexCoord2d(1, 1);
	//glVertex2d(dipleft + this->size, dipapan);
	glVertex2dvec3(this->position[i][2]);

	glTexCoord2d(1, 0);
	//glVertex2d(dipleft + this->size, dipapan - this->size);
	glVertex2dvec3(this->position[i][3]);

	glTexCoord2d(0, 0);
	//glVertex2d(dipleft, dipapan - this->size);
	glVertex2dvec3(this->position[i][0]);

	glEnd();
}
void ToolBar::initPositions()
{
	for (int i = 0; i < this->N_tools; i++)
	{
		//1 2
		//0 3
		this->position[i][0] = jgn::vec3(0.01 + dipleft, -this->size  - 0.03 + dipapan + i * (-0.01 - this->size), 6);
		this->position[i][1] = jgn::vec3(0.01 + dipleft,  -0.03 + dipapan + i * (-0.01 - this->size), 6);
		this->position[i][2] = jgn::vec3(0.01 + dipleft + this->size,  -0.03 + dipapan + i * (-0.01 - this->size), 6);
		this->position[i][3] = jgn::vec3(0.01 + dipleft+ this->size,  -this->size-0.03 + dipapan + i * (-0.01 - this->size), 6);
	}
}

void ToolBar::toolclicked(const float x, const float y)
{
	for (int i = 0; i < this->N_tools; i++)
	{
		if (x > tb.position[i][0].x && x < tb.position[i][2].x && y > tb.position[i][0].y && y < tb.position[i][1].y)
		{
			this->selectedTool = static_cast<ToolBar::Tool>(i);
			return;
		}
	}
}


void ToolBar::draw()
{
	glLoadIdentity();
	glDisable(GL_LIGHTING);
	glTranslatef(0, 0, 5);
	glColor3f(.9, .9, .9);
	glBegin(GL_QUADS);
	glVertex2d(dipleft-1, dipapan + 1);
	glVertex2d(dipleft + this->size+0.027, dipapan + 1);
	glVertex2d(dipleft + this->size+0.027, -dipapan  -1);
	glVertex2d(dipleft -1, -dipapan -1);
	glEnd();

	glEnable(GL_TEXTURE_2D);
	for (int i = 0; i < this->N_tools; i++)
	{
		glBindTexture(GL_TEXTURE_2D, cursorToolsImg[i]);
		this->selectedTool == static_cast<ToolBar::Tool>(i) ? glColor3f(0.2, 1, 0.2) : glColor3f(1, 1, 1);
		this->_drawButton(i);
	}
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glLoadIdentity();
}


//////////////////////////////////////
//Utool
bool Utool::_singlesellect()
{
	jgn::vec2 finalclicked = jgn::vec2(-1, -1);//x=group, y=atom
	int iatom = -1;
	int iatomtosellect = -1;
	for (int g = 0; g < vs.N_groups; g++)
	{
		for (int i = 0; i < vs.group[g].N_atoms; i++)
		{
			iatom++;
			jgn::vec3 p1;
			jgn::vec3 p2;
			jgn::vec3 theta_rad;
			jgn::vec3 prevp1;

			p1 = vs.group[g].position[i] / (Svmax + 5);
			theta_rad = jgn::vec3(theta[0] * M_PI / 180, 0, theta[1] * M_PI / 180);


			p2 = p1.translate(jgn::vec3(model_translate[0], model_translate[1], model_translate[2]));
			p1 = p2.rotate(theta_rad);
			p1.z = -p1.z;

			///at this point p1 is the final product


			if (jgn::dist2d(leftClick.finish, &(p1.x)) < vs.group[g].radius[i] / (Svmax + 5))
			{
				if (finalclicked.y == -1)
				{
					finalclicked = jgn::vec2(g, i);
					prevp1 = p1;
					iatomtosellect = iatom;
				}
				else if (p1.z < prevp1.z) {
					finalclicked = jgn::vec2(g, i);
					prevp1 = p1;
					iatomtosellect = iatom;
				}
			}
		}
	}
	if (finalclicked.y != -1)
	{
		vs.group[finalclicked.x].isSelected[finalclicked.y] = true;
		vs._sellectHistory[iatomtosellect].z = vs._sellectHistory2undo;
		return true;
	}
	return false;
}

bool Utool::_multisellect()
{
	bool atLeast1isSellected = false;
	int iatoms = -1;
	for (int g = 0; g < vs.N_groups; g++)
	{
		for (int i = 0; i < vs.group[g].N_atoms; i++)
		{
			iatoms++;
			jgn::vec3 p1;
			jgn::vec3 p2;
			jgn::vec3 theta_rad;

			p1 = vs.group[g].position[i] / (Svmax + 5);
			theta_rad = jgn::vec3(theta[0] * M_PI / 180, 0, theta[1] * M_PI / 180);


			p2 = p1.translate(jgn::vec3(model_translate[0], model_translate[1], model_translate[2]));
			p1 = p2.rotate(theta_rad);
			p1.z = -p1.z;
			

			if ((p1.x<leftClick.start[0] && p1.x > leftClick.finish[0]) || (p1.x > leftClick.start[0] && p1.x < leftClick.finish[0]))
			{
				if ((p1.y<leftClick.start[1] && p1.y > leftClick.finish[1]) || (p1.y > leftClick.start[1] && p1.y < leftClick.finish[1]))
				{
					vs.group[g].isSelected[i] = true;
					atLeast1isSellected = true;
					if(vs._sellectHistory[iatoms].z==-1)
						vs._sellectHistory[iatoms].z = vs._sellectHistory2undo;
				}
			}
		}
	}
	return atLeast1isSellected;
}

int prevMouseStatus = JGN_UP;
int currentMouseStatus = JGN_UP;
bool Utool::sellect()
{
	if (prevMouseStatus == JGN_UP)
	{
		vs._sellectHistory2undo++;
	}
	vs.undoSellect();
	vs._sellectHistory2undo++;
	

	currentMouseStatus = lmb;
	bool atleast1isSellected = false;
			if (leftClick.start[0] == leftClick.finish[0] && leftClick.start[1] == leftClick.finish[1])
			{//click
				atleast1isSellected = this->_singlesellect();
			}
			else
			{//multisellect
				atleast1isSellected = this->_multisellect();
			}
			prevMouseStatus = currentMouseStatus;
			if (JGN_UP == lmb && !atleast1isSellected)
				vs._sellectHistory2undo--;

			return atleast1isSellected;
}

void Utool::distance()
{

}