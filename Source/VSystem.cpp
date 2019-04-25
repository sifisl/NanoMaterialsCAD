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

void VSystem::draw()
{
	for (int g = 0; g < this->N_groups; g++)
	{
		for (int i = 0; i < this->group[g].N_atoms; i++)
		{
			if (!vsystem.group[g].iscut[i])
			{
				GLfloat mat_ambient[] = vec3ToGlfloat(this->group[g].color[i]);
				GLfloat mat_deffuse[] = vec3ToGlfloat(this->group[g].color[i]);

				glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_deffuse);

				glTranslatefvec3(this->group[g].position[i]);

				JGN_SolidSphere(this->group[g].radius[i] / (Svmax + 5), sphStacks, sphSides);

				glTranslatefvec3(-this->group[g].position[i]);
			}

		}
	}
}
