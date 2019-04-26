////Virtual System
#include "VSystem.h"
#include "JGN_SolidSphere.h"

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



void Group::N_types(const unsigned int N_t)
{
	this->_N_types = N_t;
	this->_alltype.reserve(N_t);
}
void VSystem::unsellectAll()
{
	_sellectHistory2undo = -1;
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
					glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
					glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_deffuse);

					glTranslatefvec3(this->group[g].position[i]);
					JGN_SolidSphere(this->group[g].radius[i] / (Svmax + 5), sphStacks, sphSides);
					glTranslatefvec3(-this->group[g].position[i]);
				}
		}
	}

	//Draw simulation box
	this->_drawSimulationBox();
	this->_drawBase();


}

void VSystem::_drawBase()
{
	glLoadIdentity();
	glTranslatef(0.2, 0, 0);
	glLineWidth(5);
	GLfloat mat_ambient[] = { 1,0,0,1 };
	GLfloat mat_deffuse[] = { 1,0,0,1 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_deffuse);

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
	glTranslatef(dipleft, -dipapan+0.1, 0);
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
	glScalef(0.2, 0.2, 0.2);
	glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, indexes);
	mat_ambient[0] = 0;
	mat_deffuse[0] = 0;
	mat_ambient[1] = 1;
	mat_deffuse[1] = 1;
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_deffuse);
	glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, &indexes[2]);
	mat_ambient[1] = 0;
	mat_deffuse[1] = 0;
	mat_ambient[2] = 1;
	mat_deffuse[2] = 1;
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_deffuse);
	glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, &indexes[4]);
	glLoadIdentity();
}

void VSystem::setSimulationBox(int s)
{
	this->_isimulationBox = s;
	this->_updateSimulationBox();
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
