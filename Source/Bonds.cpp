#include "Bonds.h"

//TODO: need to rethink a way to get rid of those buffers
int ibondstartbuf[50000];
int ibondfinbuf[50000];

Bonds::Bonds()
{
}


Bonds::~Bonds()
{
}

void Bonds::CalcBonds(float maxDist)
{
	int maxIt = t * (prev_sized[0])*(prev_sized[1])*(prev_sized[2]);
	maxDist *= maxDist;
	NBonds = 0;

	for (int i = 0; i < maxIt - 1; i++)
	{
		for (int j = i + 1; j < maxIt; j++)
		{
			if (jgn::dist3dSquare(crystal[2 + 5 * i], crystal[2 + 5 * j]) <= maxDist)
			{
				ibondstartbuf[NBonds] = i;
				ibondfinbuf[NBonds] = j;
				this->NBonds++;
			}
		}
	}
	/*this->edges.reserve(NBonds);
	this->edges.reserve(NBonds);

	for (int i = 0; i < this->NBonds; i++)
	{
		edges.emplace_back(crystal[2 + 5 * ibondstartbuf[i]], crystal[3 + 5 * ibondstartbuf[i]], crystal[4 + 5 * ibondstartbuf[i]],
			crystal[2 + 5 * ibondfinbuf[i]], crystal[3 + 5 * ibondfinbuf[i]], crystal[4 + 5 * ibondfinbuf[i]]);
	}*/


}


//void Bonds::drawBonds(float scale)
//{
//	glDrawElements(GL_LINES, this->NBonds, GL_FLOAT, *(bonds.edges[0]));
//
//	glVertexPointer(3, GL_FLOAT, 0, &bonds.start[1]);
//	glNormalPointer(GL_FLOAT, 0, &points[1]);
//
//	glDrawElements(GL_QUAD_STRIP, (numStacks - 2)*numSides * 4, GL_UNSIGNED_INT, &quads_indices[0]);
//}