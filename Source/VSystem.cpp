////Virtual System
#include "VSystem.h"
#include "JGN_SolidSphere.h"
#include "ToolBar.h"
#include "JGN_StrokeCharacter.h"
#include "JGN_Windows.h"

VSystem::VSystem()
{
}


VSystem::~VSystem()
{
}


void Group::_reserve(const unsigned int r)
{
	this->position.reserve(r);
	this->type.reserve(r);
	this->selective_dynamics.reserve(r);
	this->color.reserve(r);
	this->number.reserve(r);
	this->weight.reserve(r);
	this->radius.reserve(r);
	this->isSelected.reserve(r);
	this->isdeleted.reserve(r);
	this->iscut.reserve(r);

}

jgn::vec2 VSystem::_hoveringAnatom(const jgn::vec2 m)
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


			if (jgn::dist2d((float*)(&(m.x)), &(p1.x)) < vs.group[g].radius[i] / (Svmax + 5))
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
		vs.group[finalclicked.x].ishovered[finalclicked.y] = true;
	}

	vs.hoveredatom = finalclicked;
	if (!(vs.hoveredatom == vs.hoveredatom_prev))
	{
		if(vs.hoveredatom_prev.x!=-1)
			vs.group[vs.hoveredatom_prev.x].ishovered[vs.hoveredatom_prev.y] = false;
		JGN_PostRedisplay();
	}
	vs.hoveredatom_prev = vs.hoveredatom;
	return finalclicked;
}


void Group::N_types(const unsigned int N_t)
{
	this->_N_types = N_t;
	this->_alltype.reserve(N_t);
}
void VSystem::unsellectAll()
{
	_sellectHistory2undo = -1;
	tb._sellectedfordistance[0] = jgn::vec2(-1, -1);
	tb._sellectedfordistance[1] = jgn::vec2(-1, -1);
	for (int g = 0; g < this->N_groups; g++)
	{
		for (int i = 0; i < this->group[g].N_atoms; i++)
		{
			this->group[g].isSelected[i] = false;
			this->_sellectHistory[i].z = -1;
			this->_sellectHistory2undo = -1;
		}
	}
}

void VSystem::draw()
{
	//Draw atoms
	this->_drawatoms();

	//Draw simulation box
	this->_drawSimulationBox();
	this->_drawBase();

	//Draw distance tool line
	this->_drawDistanceToolLine();

	//Draw system info
	this->_drawsysteminfo();

	//Draw group list
	this->grouplist.draw();

}

void VSystem::Grouplist::draw()
{
	glLoadIdentity();
	if (vs.N_groups > 1)
	{
		glEnable(GL_TEXTURE_2D);
		glDisable(GL_LIGHTING);
		if(this->open)
		{ 
			//back ground
			glBindTexture(GL_TEXTURE_2D, button1ID);
			glColor3f(0.2, 0.2, 0.2);
			glBegin(GL_QUADS);
			glTexCoord2d(0, 1);
			glVertex3f(dipleft + tb.size + 0.4, dipapan - 0.01, 5);
			glTexCoord2d(0.99, 0.99);
			glVertex3f(dipleft + tb.size + 0.4, dipapan - 0.3, 5);
			glTexCoord2d(0.99, 0);
			glVertex3f(dipleft + tb.size + 0.05, dipapan - 0.3, 5);
			glTexCoord2d(0, 0);
			glVertex3f(dipleft + tb.size + 0.05, dipapan - 0.01, 5);
			glEnd();
			//write
			glBindTexture(GL_TEXTURE_2D, Font);
			for (int i = 0; i < vs.N_groups; i++)
			{
				this->options.hovering == i ? glColor3f(1, 0.2, 0.2) : glColor3f(0, 0, 0);
				glTranslatef(dipleft + tb.size + 0.13, dipapan - 0.08 -i*0.05, 5);
				glScalef(0.5, 0.5, 0.5);
				write::string("group ");
				write::character(i + 49);
				glLoadIdentity();
			}
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, showlessID);
		}
		else {
			glBindTexture(GL_TEXTURE_2D, showmoreID);
		}
		this->hovering ? glColor3f(0.2, 0.2, 0.2) : glColor3f(0, 0, 0);
		glBegin(GL_QUADS);
		glTexCoord2d(0.99, 0.99);
		glVertex3f(dipleft + tb.size + 0.05 + 0.05, dipapan-0.01 , 5);
		glTexCoord2d(0.99, 0);
		glVertex3f(dipleft + tb.size + 0.05 + 0.05, dipapan - 0.06, 5);
		glTexCoord2d(0, 0);
		glVertex3f(dipleft + tb.size + 0.05, dipapan - 0.06, 5);
		glTexCoord2d(0, 1);
		glVertex3f(dipleft + tb.size + 0.05, dipapan- 0.01, 5);
		glEnd();

		
	}
}

bool VSystem::Grouplist::Options::checkhoverstatus(const jgn::vec2 m)
{
	this->hovering = -1;
	for (int i = 0; i < vs.N_groups; i++)
	{
		if (m.x > dipleft + tb.size + 0.13 && m.x < dipleft + tb.size + 0.3 + 0.05 && m.y>dipapan - 0.08 - i * 0.05 && m.y < dipapan - 0.08 - (i-1) * 0.05)
		{
			this->hovering = i;
			if (this->hovering_prev != i)
				JGN_PostRedisplay();
			this->hovering_prev = this->hovering;
			return true;
		}
	}
	if(this->hovering_prev!=-1)
		JGN_PostRedisplay();
	this->hovering_prev = -1;
		

		return false;
}

bool VSystem::Grouplist::checkhoverstatus(const jgn::vec2 m)
{
	if (m.x > dipleft + tb.size + 0.05 && m.x < dipleft + tb.size + 0.05 + 0.05 && m.y>dipapan - 0.06 && m.y < dipapan - 0.01)
	{
		this->hovering = true;
		if (this->hovering_prev == false)
			JGN_PostRedisplay();
		hovering_prev = hovering;

	}
	else
	{
		this->hovering = false;
		if (this->hovering_prev == true)
			JGN_PostRedisplay();
		hovering_prev = hovering;
	}
		return hovering;
}

void VSystem::_drawatoms()
{
	for (int g = 0; g < this->N_groups; g++)
	{
		for (int i = 0; i < this->group[g].N_atoms; i++)
		{
			if (!vs.group[g].iscut[i])
				if (!vs.group[g].isdeleted[i])
				{
					GLfloat mat_ambient[4];
					GLfloat mat_deffuse[4];
					if (this->group[g].isSelected[i])
					{
						mat_ambient[0] = 0;
						mat_ambient[1] = 0;
						mat_ambient[2] = 0;
						mat_ambient[3] = 1;
						mat_deffuse[0] = 0;
						mat_deffuse[1] = 0;
						mat_deffuse[2] = 0;
						mat_deffuse[3] = 1;
					}
					else
					{
						mat_ambient[0] = this->group[g].color[i].x;
						mat_ambient[1] = this->group[g].color[i].y;
						mat_ambient[2] = this->group[g].color[i].z;
						mat_ambient[3] = 1;
						mat_deffuse[0] = this->group[g].color[i].x;
						mat_deffuse[1] = this->group[g].color[i].y;
						mat_deffuse[2] = this->group[g].color[i].z;
						mat_deffuse[3] = 1;
					}

					if (this->group[g].ishovered[i])
					{
						mat_ambient[0] += 0.3;
						mat_ambient[1] += 0.3;
						mat_ambient[2] += 0.3;
						mat_deffuse[0] += 0.3;
						mat_deffuse[1] += 0.3;
						mat_deffuse[2] += 0.3;
					}
					glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
					glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_deffuse);

					glTranslatefvec3(this->group[g].position[i]);
					JGN_SolidSphere(this->group[g].radius[i] / (Svmax + 5), sphStacks, sphSides);
					glTranslatefvec3(-this->group[g].position[i]);
				}
		}
	}
}

void VSystem::_drawDistanceToolLine()
{
	if (tb._sellectedfordistance[1].y != -1)
	{
		glDisable(GL_LIGHTING);
		jgn::vec3 p1 = vs.group[tb._sellectedfordistance[0].x].position[tb._sellectedfordistance[0].y] / (Svmax + 5);
		jgn::vec3 p2 = vs.group[tb._sellectedfordistance[1].x].position[tb._sellectedfordistance[1].y] / (Svmax + 5);

		glColor3f(0, 1, 0);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, button1ID);
		glBegin(GL_QUADS);
		glTexCoord2d(0, 1);
		glVertex3f(dipleft + tb.size + 0.027, tb.position[static_cast<int>(ToolBar::Tool::DISTANCE)][1].y-0.055, 5);
		glTexCoord2d(1, 1);

		glVertex3f(dipleft + tb.size + 0.36, tb.position[static_cast<int>(ToolBar::Tool::DISTANCE)][1].y - 0.055, 5);
		glTexCoord2d(1, 0);

		glVertex3f(dipleft + tb.size + 0.36, tb.position[static_cast<int>(ToolBar::Tool::DISTANCE)][1].y - 0.125, 5);
		glTexCoord2d(0, 0);

		glVertex3f(dipleft + tb.size + 0.027, tb.position[static_cast<int>(ToolBar::Tool::DISTANCE)][1].y - 0.125, 5);
		glEnd();
		glDisable(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, Font);
		glColor3f(0, 0, 0);
		glTranslatef(dipleft + tb.size + 0.027, tb.position[static_cast<int>(ToolBar::Tool::DISTANCE)][1].y - 0.12, 6);
		glScalef(0.5, 0.5, 0.5);
		float d = sqrt(jgn::dist3dSquare((vs.group[tb._sellectedfordistance[0].x].position[tb._sellectedfordistance[0].y].x), (vs.group[tb._sellectedfordistance[1].x].position[tb._sellectedfordistance[1].y].x)));
		int di = (int)d;
		char dia[30];
		itoa(di, dia, 10);
		write::string(dia);
		write::character('.');
		d -= di;
		write::string(&(jgn::ftoa(d))[2], 5);
		write::character(Angstrom);
		glLoadIdentity();



		glColor3f(0, 0, 0);
		if (CustomSurfacesOn)
		{
			glRotatef(theta[0], 1.0, 0.0, 0.0);
			glRotatef(theta[1], 0.0, 0.0, 1.0);
		}
		else
		{
			glRotatef(theta[0], 1.0, 0.0, 0.0);
			glRotatef(theta[1], 0.0, 1.0, 0.0);
		}
		glTranslatef(model_translate[0], model_translate[1], model_translate[2]);
		glBegin(GL_LINES);
		glVertex3fvec3(p1);
		glVertex3fvec3(p2);
		glEnd();
		glEnable(GL_LIGHTING);
	}
}
void VSystem::_drawsysteminfo()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Font);
	glDisable(GL_LIGHTING);
	int stroke_c = 0;
	//write the element type
	for (int ff = 0; ff < vs.N_types; ff++)
	{
		glLoadIdentity();
		glColor3f(0, 0, 0);
		glTranslatef(-dipleft - 0.4, dipapan - 0.08 - 0.1*ff, 6);
		glScalef(0.5, 0.5, 0.5);
		itoa(vs.N_atoms_per_type[ff], ss, 10);
		stroke_c = 0;
		while (ss[stroke_c] != '\0')
		{
			write::character(ss[stroke_c]);
			stroke_c++;
		}
		stroke_c = 0;
	}
	glEnable(GL_LIGHTING);
	glPointSize(10);
	//draw sphere color and write the number of atoms per type
	for (int ff = 0; ff < vs.N_types; ff++)
	{
		glLoadIdentity();
		glColor3f(0, 0, 0);
		glTranslatef(-dipleft - 0.25, dipapan - 0.1 - 0.1*ff, 6);
		glDisable(GL_LIGHTING);
		write::string(std::string(vs.types[ff]).c_str());
		glEnable(GL_LIGHTING);
		glLoadIdentity();
		if (shperes_on)
		{
			colr[0] = vs.color_per_type[ff].x;
			colr[1] = vs.color_per_type[ff].y;
			colr[2] = vs.color_per_type[ff].z;
			GLfloat mat_ambient[] = { colr[0], colr[1], colr[2], 1.0 };
			GLfloat mat_deffuse[] = { colr[0], colr[1], colr[2], 1.0 };
			glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_deffuse);
			glTranslatef(-dipleft - 0.42, dipapan - 0.06 - 0.1*ff, 6);
			JGN_SolidSphere(20 * 0.001, 32, 32);
		}
		else
		{
			glBegin(GL_POINTS);
			colr[0] = fmod(aweights[ff], 1.5);
			colr[1] = fmod(anumber[ff], 0.92);
			colr[2] = fmod(100 * colr[0] * colr[1], 0.8);
			glColor3fv(colr);
			glVertex3f(-dipleft, float(ff) / float(vs.N_types), 0);
			glEnd();
		}

	}
	////////////write simulation box volume
	glDisable(GL_LIGHTING);
	glLoadIdentity();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, button1ID);
	glColor3f(0, 1, 1);
	glBegin(GL_QUADS);
	glTexCoord2d(0.99, 0.99);
	glVertex3f(-dipleft - 0.4, -dipapan + 2 * dipapan*(36.0 / mainwndsize[1]), 5);
	glTexCoord2d(0.99, 0);
	glVertex3f(-dipleft - 0.4, -dipapan + 2 * dipapan*(36.0 / mainwndsize[1]) + 0.07, 5);
	glTexCoord2d(0, 0);
	glVertex3f(-dipleft, -dipapan + 2 * dipapan*(36.0 / mainwndsize[1]) + 0.07, 5);
	glTexCoord2d(0, 1);
	glVertex3f(-dipleft, -dipapan + 2 * dipapan*(36.0 / mainwndsize[1]), 5);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, Font);
	glColor3f(0, 0, 0);
	glLoadIdentity();
	glTranslatef(-dipleft, -dipapan + 2 * dipapan*(40.0 / mainwndsize[1]), 6);
	glScalef(0.4, 0.4, 0.2);

	glTranslatef(-0.02, 0.06, 0);
	glScalef(0.8, 0.8, 0.8);
	write::rtl::character('3');
	glScalef(1.25, 1.25, 1.25);
	glTranslatef(0.02, -0.06, 0);

	write::rtl::character(Angstrom);
	write::rtl::string(jgn::ftoa(vs.simulationboxVolume));
	glEnable(GL_LIGHTING);
}

void VSystem::_drawBase()
{
	glLoadIdentity();
	glDisable(GL_LIGHTING);
	//glTranslatef(0.2, 0, 0);
	glLineWidth(5);
	//GLfloat mat_ambient[] = { 1,0,0,1 };
	//GLfloat mat_deffuse[] = { 1,0,0,1 };
	//glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_deffuse);

	unsigned int indexes[6] = { 0,1,
								0,2,
								0,3};

	jgn::vec3 sb[4];
	sb[0] = jgn::vec3(0, 0, 0);
	sb[1] = this->group[this->_isimulationBox].primitiveBase[0];
	sb[2] = this->group[this->_isimulationBox].primitiveBase[1];
	sb[3] = this->group[this->_isimulationBox].primitiveBase[2];

	glVertexPointer(3, GL_FLOAT, 0, &sb[0].x);
	glNormalPointer(GL_FLOAT, 0, &sb[0].x);
	glTranslatef(dipleft+0.08, -dipapan + 2*dipapan*(70.0/mainwndsize[1]), 7);
	if (CustomSurfacesOn)
	{
		glRotatef(theta[0], 1.0, 0.0, 0.0);
		glRotatef(theta[1], 0.0, 0.0, 1.0);
	}
	else
	{
		glRotatef(theta[0], 1.0, 0.0, 0.0);
		glRotatef(theta[1], 0.0, 1.0, 0.0);
	}
	glScalef(0.07, 0.07, 0.07);
	//glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, indexes);
	glBegin(GL_LINES);
	glColor4f(0., 0., 0., 1);
	glVertex3fvec3(sb[0]);
	glColor4f(1, 0, 0,1);
	glVertex3fvec3(sb[1]);
	glEnd();

	//glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, indexes);
	glBegin(GL_LINES);
	glColor4f(0., 0., 0., 1);
	glVertex3fvec3(sb[0]);
	glColor4f(0, 1, 0,1);
	glVertex3fvec3(sb[2]);
	glEnd();
	//mat_ambient[1] = 0;
	//mat_deffuse[1] = 0;
	//mat_ambient[2] = 1;
	//mat_deffuse[2] = 1;
	//glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_deffuse);
	//glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, indexes);
	glBegin(GL_LINES);
	glColor4f(0., 0., 0., 1);
	glVertex3fvec3(sb[0]);
	glColor4f(0, 0, 1, 1);
	glVertex3fvec3(sb[3]);
	glEnd();
	glLoadIdentity();

}

void VSystem::setSimulationBox(int s)
{
	this->_isimulationBox = s;
	this->_updateSimulationBox();
	vs.simulationboxVolume = jgn::volume(vs.simulationBoxEdges[1], vs.simulationBoxEdges[2], vs.simulationBoxEdges[3]);
}
void VSystem::undoSellect()
{
	if (_sellectHistory2undo > -1)
	{
		for (int i = 0; i < this->_sellectHistory.capacity(); i++)
		{
			if (this->_sellectHistory[i].z == this->_sellectHistory2undo)
			{
				this->_sellectHistory[i].z = -1;
				this->group[this->_sellectHistory[i].x].isSelected[this->_sellectHistory[i].y] = false;
			}
		}
		this->_sellectHistory2undo--;
	}
}
void VSystem::_updateSimulationBox()
{
	this->simulationBoxEdges[0] = jgn::vec3(0, 0, 0);
	this->simulationBoxEdges[1] = this->group[this->_isimulationBox].primitiveVec[0];
	this->simulationBoxEdges[2] = this->group[this->_isimulationBox].primitiveVec[1];
	this->simulationBoxEdges[3] = this->group[this->_isimulationBox].primitiveVec[2];
	this->simulationBoxEdges[4] = this->group[this->_isimulationBox].primitiveVec[0];
	this->simulationBoxEdges[4] = this->simulationBoxEdges[4] + this->group[this->_isimulationBox].primitiveVec[2];
	this->simulationBoxEdges[5] = this->group[this->_isimulationBox].primitiveVec[1];
	this->simulationBoxEdges[5] = this->simulationBoxEdges[5] + this->group[this->_isimulationBox].primitiveVec[2];
	this->simulationBoxEdges[6] = this->simulationBoxEdges[5] + this->simulationBoxEdges[1];
	this->simulationBoxEdges[7] = this->simulationBoxEdges[2] + this->simulationBoxEdges[1];

}

void VSystem::_drawSimulationBox()
{
	glLineWidth(1);
	GLfloat mat_ambient[] = { 0,0,0,1 };
	GLfloat mat_deffuse[] = { 0,0,0,1 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_deffuse);

	unsigned int indexes[24] = {0,1,
								0,2,
								0,3,
								3,5,
								2,5, 
								3,4,
								4,6,
								5,6,
								2,7,
								7,1,
								4,1,
								6,7 };

	jgn::vec3 sb[8];
	sb[0] = this->simulationBoxEdges[0] / (Svmax + 5);
	sb[1] = this->simulationBoxEdges[1] / (Svmax + 5);
	sb[2] = this->simulationBoxEdges[2] / (Svmax + 5);
	sb[3] = this->simulationBoxEdges[3] / (Svmax + 5);
	sb[4] = this->simulationBoxEdges[4] / (Svmax + 5);
	sb[5] = this->simulationBoxEdges[5] / (Svmax + 5);
	sb[6] = this->simulationBoxEdges[6] / (Svmax + 5);
	sb[7] = this->simulationBoxEdges[7] / (Svmax + 5);
	glVertexPointer(3, GL_FLOAT, 0, &sb[0].x);
	glNormalPointer(GL_FLOAT, 0, &sb[0].x);
	glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, indexes);

}


void VSystem::cut()
{
	for (int g = 0; g < this->N_groups; g++)
	{
		#pragma omp parallel for firstprivate(g, S1v, S2v, S3, S1i, S2i, S3i, CustomSurfacesCount, i, CustomSurfaces, shperes_on, Right_Hexagonal, nanotube, CustomSurfacesOn, vacuum, Right_Hexagonal_height, figure_1, Rod_like)
		for (int ii = 0; ii < this->group[g].N_atoms; ii++)
		{
			float *p = &(this->group[g].position[ii].x);
			if (nanotube)
			{
				this->group[g].iscut[ii] = false;
			}
			else if (want_cyrcle[0] == 'y' || want_cyrcle[0] == 'Y')
			{
				this->group[g].iscut[ii] = false;
			}
			else if (CustomSurfacesOn)
			{

				if (CustomSurfacesCount == 0)
				{
					this->group[g].iscut[ii] = false;
				}
				else
				{
					for (i = 0; i < CustomSurfacesCount; i++)
					{
						if (CustomSurfaces[i][0] * (p[0] - CustomSurfaces[i][0] * CustomSurfaces[i][3]) + CustomSurfaces[i][1] * (p[1] - CustomSurfaces[i][1] * CustomSurfaces[i][3]) + CustomSurfaces[i][2] * (p[2] - CustomSurfaces[i][2] * CustomSurfaces[i][3]) <= 0)
						{

						}
						else
						{
							i = 1000;
						}

					}

					if (i == CustomSurfacesCount)
					{
						this->group[g].iscut[ii] = false;
					}
					else {
						this->group[g].iscut[ii] = true;
					}
				}
			}
			//else if (jgn_supercell)			
			else
			{

				if (Right_Hexagonal == -1)
				{
					if (vacuum ^ (abs(p[2]) < Right_Hexagonal_height && (S1i[0] * abs(p[0]) <= S2v * 0.86602540378) && S2i[0] * abs(p[0]) / 1.73205 + S2i[0] * abs(p[1]) <= S2v &&
						(S1i[0] * abs(p[1]) < S1v *0.86602540378) && S2i[0] * abs(p[0]) + S1i[0] * abs(p[1]) / 1.73205 < S1v))
					{
						for (i = 0; i < CustomSurfacesCount; i++)
						{
							if (CustomSurfaces[i][0] * (p[0] - CustomSurfaces[i][0] * CustomSurfaces[i][3]) + CustomSurfaces[i][1] * (p[1] - CustomSurfaces[i][1] * CustomSurfaces[i][3]) + CustomSurfaces[i][2] * (p[2] - CustomSurfaces[i][2] * CustomSurfaces[i][3]) <= 0)
							{

							}
							else
							{
								i = 1000;
							}

						}

						if (i == CustomSurfacesCount)
						{
							this->group[g].iscut[ii] = false;
						}
						else {
							this->group[g].iscut[ii] = true;
						}
					}
					else {
						this->group[g].iscut[ii] = true;
					}
				}
				else
				{
					if (vacuum ^ ((S1i[0] * figure_1*abs(p[0]) <= S1v) &&
						(S1i[0] * Right_Hexagonal*Rod_like* abs(p[2]) <= S1v) &&
						(S1i[0] * figure_1*abs(p[1]) <= S1v) &&
						Rod_like*(S2i[0] * abs(p[0]) + S2i[0] * Right_Hexagonal* abs(p[2])) <= S2v &&
						S2i[0] * figure_1* abs(p[0]) + S2i[0] * figure_1* abs(p[1]) <= S2v &&
						Rod_like*(S2i[0] * Right_Hexagonal* abs(p[2]) + S2i[0] * abs(p[1])) <= S2v &&
						Right_Hexagonal*(S3i[0] * abs(p[0]) + S3i[1] * abs(p[2]) + S3i[2] * abs(p[1])) <= S3v))
					{
						for (i = 0; i < CustomSurfacesCount; i++)
						{
							if (CustomSurfaces[i][0] * (p[0] - CustomSurfaces[i][0] * CustomSurfaces[i][3]) + CustomSurfaces[i][1] * (p[1] - CustomSurfaces[i][1] * CustomSurfaces[i][3]) + CustomSurfaces[i][2] * (p[2] - CustomSurfaces[i][2] * CustomSurfaces[i][3]) <= 0)
							{

							}
							else
							{
								i = 1000;
							}

						}

						if (i == CustomSurfacesCount)
						{
							this->group[g].iscut[ii] = false;
						}
						else {
							this->group[g].iscut[ii] = true;
						}
					}
					else {
						this->group[g].iscut[ii] = true;
					}

				}
			}
		}
	}
}
