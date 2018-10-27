#pragma once
#include "stdafx.h"
//https://stackoverflow.com/questions/28806871/how-to-render-sphere-using-open-gl-c-and-not-glut-glu
//hint: use GL_NORMALIZE

#define CONST_COE 0.0222222222


typedef struct {
	GLdouble x, y, z;
}vec3;

vec3 points[90];

void JGN_SolidSphere(float radius, int numStacks, int numSides)
{
	//glScalef(0.2*radius / CONST_COE, 0.2*radius / CONST_COE, 0.2*radius / CONST_COE);

	//    vec3 points[sides * (sides-1)];
	GLfloat curRadius, curTheta, curRho, deltaTheta, deltaRho, curX, curY, curZ;
	int curStack, curSlice;
	const int numVerts = (numStacks - 1)*numSides;
	float v[3];
	int curVert = 0;
	int t;

	deltaTheta = (2 * M_PI) / numSides;
	deltaRho = M_PI / numStacks;

	for (curStack = 1; curStack<numStacks; curStack++)
	{
		curRho = (3.141 / 2.0) - curStack * deltaRho;
		curY = sin(curRho) * radius;
		curRadius = cos(curRho) * radius;
		for (curSlice = 0; curSlice<numSides; curSlice++)
		{
			curTheta = curSlice * deltaTheta;
			curX = curRadius * cos(curTheta);
			curZ = -curRadius * sin(curTheta);
			points[curVert++] = vec3{ curX,curY,curZ };
		}
	}

	// option 1 - points only
	/*
	glBegin(GL_POINTS);
	glNormal3d(0,1,0);
	glVertex3d(0,radius,0);
	for (t=0; t<numVerts; t++)
	{
	curX = points[t].x;
	curY = points[t].y;
	curZ = points[t].z;
	glNormal3d(curX, curY, curZ);
	glVertex3d(curX, curY, curZ);
	}
	glNormal3d(0,-1,0);
	glVertex3d(0,-radius,0);
	glEnd();
	*/

	///////////////////////////////
	// option 2 - solid
	///////////////////////////////
	// part A - draw the top 'lid' (tris)
	//glBegin(GL_POLYGON);

	glBegin(GL_TRIANGLE_FAN);

	glNormal3d(0, 1, 0);
	glVertex3d(0, radius, 0);
	for (t = 0; t<numSides; t++)
	{
		v[0] = points[t].x;
		v[1] = points[t].y;
		v[2] = points[t].z;
		glNormal3dv(v);
		glVertex3dv(v);
	}
	v[0] = points[0].x;
	v[1] = points[0].y;
	v[2] = points[0].z;
	glNormal3dv(v);
	glVertex3dv(v);
	glEnd();

	// part B - draw the 'sides' (quads)
	int vertIndex;
	for (curStack = 0; curStack<numStacks - 2; curStack++)
	{
		vertIndex = curStack * numSides;
		glBegin(GL_QUAD_STRIP);

		for (curSlice = 0; curSlice<numSides; curSlice++)
		{
			v[0] = points[vertIndex + curSlice].x;
			v[1] = points[vertIndex + curSlice].y;
			v[2] = points[vertIndex + curSlice].z;
			glNormal3dv((GLdouble*)v);
			glVertex3dv(v);

			v[0] = points[vertIndex + numSides + curSlice].x;
			v[1] = points[vertIndex + numSides + curSlice].y;
			v[2] = points[vertIndex + numSides + curSlice].z;

			glNormal3dv((GLdouble*)v);
			glVertex3dv(v);
		}
		glNormal3d(points[vertIndex].x, points[vertIndex].y, points[vertIndex].z);
		glVertex3d(points[vertIndex].x, points[vertIndex].y, points[vertIndex].z);
		glNormal3d(points[vertIndex + numSides].x, points[vertIndex + numSides].y, points[vertIndex + numSides].z);
		glVertex3d(points[vertIndex + numSides].x, points[vertIndex + numSides].y, points[vertIndex + numSides].z);
		glEnd();
	}

	// part C - draw the bottom 'lid' (tris)
	glBegin(GL_TRIANGLE_FAN);
	//glBegin(GL_POLYGON);
	glNormal3d(0, -1, 0);
	glVertex3d(0, -radius, 0);



	for (t = 0; t<numSides - 1; t++)
//		for (t = 0; t<8; t++)

	{
		curX = points[numVerts - 1 - t].x;
		curY = points[numVerts - 1 - t].y;
		curZ = points[numVerts - 1 - t].z;
		glNormal3d(curX, curY, curZ);
		glVertex3d(curX, curY, curZ);
	}
	glNormal3d(points[(numStacks - 2)*numSides].x, points[(numStacks - 2)*numSides].y, points[(numStacks - 2)*numSides].z);
	glVertex3d(points[(numStacks - 2)*numSides].x, points[(numStacks - 2)*numSides].y, points[(numStacks - 2)*numSides].z);
	
		
		curX = points[numVerts - 1].x;
		curY = points[numVerts - 1].y;
		curZ = points[numVerts - 1].z;
		glNormal3d(curX, curY, curZ);
		glVertex3d(curX, curY, curZ);
	glEnd();

	//glScalef(5 * CONST_COE / radius, 5 * CONST_COE / radius, 5 * CONST_COE / radius);

}

/////////////////////////////////////////////////
