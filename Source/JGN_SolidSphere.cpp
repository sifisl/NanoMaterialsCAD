#include "stdafx.h"
#include "JGN_SolidSphere.h"


void JGN_SolidSphere(float radius, int numStacks, int numSides)
{
	//numStacks = 10;
	//numSides = 10;


	//glScalef(0.2*radius / CONST_COE, 0.2*radius / CONST_COE, 0.2*radius / CONST_COE);

	//    vec3 points[sides * (sides-1)];
	GLfloat curRadius, curTheta, curRho, deltaTheta, deltaRho, curX, curY, curZ;
	int curStack, curSlice;
	const int numVerts = (numStacks - 1)*numSides;
	float v[3];
	int curVert = 1;
	int t;

	deltaTheta = (2 * M_PI) / numSides;
	deltaRho = M_PI / numStacks;

	for (curStack = 1; curStack < numStacks; curStack++)
	{
		curRho = (3.141 / 2.0) - curStack * deltaRho;
		curY = sin(curRho) * radius;
		curRadius = cos(curRho) * radius;
		for (curSlice = 0; curSlice < numSides; curSlice++)
		{
			curTheta = curSlice * deltaTheta;
			curX = curRadius * cos(curTheta);
			curZ = -curRadius * sin(curTheta);
			points[curVert++] = vec3{ curX,curY,curZ };
		}
	}

	points[0] = { 0,radius,0 };
	glVertexPointer(3, GL_DOUBLE, 0, &points[0]);
	glNormalPointer(GL_DOUBLE, 0, &points[0]);

	triangles_indices[numSides + 1] = 1;
	glDrawElements(GL_TRIANGLE_FAN, numSides + 2, GL_UNSIGNED_INT, triangles_indices);
	triangles_indices[numSides + 1] = numSides + 1;


	//glBegin(GL_TRIANGLE_FAN);

	//glNormal3d(0, 1, 0);
	//glVertex3d(0, radius, 0);

	//for (int t = 1; t < numSides + 1; t++)
	//{
	//	v[0] = points[t].x;
	//	v[1] = points[t].y;
	//	v[2] = points[t].z;
	//	glNormal3dv(v);
	//	glVertex3dv(v);
	//}
	//v[0] = points[1].x;
	//v[1] = points[1].y;
	//v[2] = points[1].z;
	//glNormal3dv(v);
	//glVertex3dv(v);
	//glEnd();

	for (int i = 0; i < numStacks - 2 ; i++)
	{
		for (int j = 0; j < numSides; j ++)
		{
			quads_indices[j * 2 + i * (numSides * 2 + 2)] = i * numSides + j;
			quads_indices[j * 2 + i * (numSides * 2 + 2) + 1] = i * numSides + j + numSides;
			//cout << j * 2 + i * (numSides * 2 + 2) << endl;
			//cout << j * 2 + i * (numSides * 2 + 2) + 1 << endl;
		}
		//cout << '----' << endl;
		quads_indices[numSides * 2 + i * (numSides * 2 + 2)] = i * numSides;
		quads_indices[numSides * 2 + i * (numSides * 2 + 2) + 1] = i * numSides + numSides;
		//cout << numSides * 2 + i*(numSides * 2 + 2) << endl;
		//cout << numSides * 2 + i * (numSides * 2 + 2) + 1 << endl;


	}



	glVertexPointer(3, GL_DOUBLE, 0, &points[1]);
	glNormalPointer(GL_DOUBLE, 0, &points[1]);

	glDrawElements(GL_QUAD_STRIP, (numStacks - 2)*numSides*4, GL_UNSIGNED_INT, &quads_indices[0]);


	//// part B - draw the 'sides' (quads)
	//int vertIndex;
	//for (int curStack = 0; curStack < numStacks - 2; curStack++)
	//{
	//	vertIndex = curStack * numSides;
	//	glBegin(GL_QUAD_STRIP);

	//	for (int curSlice = 0; curSlice < numSides; curSlice++)
	//	{
	//		v[0] = points[vertIndex + curSlice + 1].x;
	//		v[1] = points[vertIndex + curSlice + 1].y;
	//		v[2] = points[vertIndex + curSlice + 1].z;
	//		glNormal3dv((GLdouble*)v);
	//		glVertex3dv(v);

	//		v[0] = points[vertIndex + numSides + curSlice + 1].x;
	//		v[1] = points[vertIndex + numSides + curSlice + 1].y;
	//		v[2] = points[vertIndex + numSides + curSlice + 1].z;

	//		glNormal3dv((GLdouble*)v);
	//		glVertex3dv(v);
	//	}
	//	glNormal3d(points[vertIndex + 1].x, points[vertIndex + 1].y, points[vertIndex + 1].z);
	//	glVertex3d(points[vertIndex + 1].x, points[vertIndex + 1].y, points[vertIndex + 1].z);
	//	glNormal3d(points[vertIndex + numSides + 1].x, points[vertIndex + numSides + 1].y, points[vertIndex + numSides + 1].z);
	//	glVertex3d(points[vertIndex + numSides + 1].x, points[vertIndex + numSides + 1].y, points[vertIndex + numSides + 1].z);
	//	glEnd();
	//}

	// part C - draw the bottom 'lid' (tris)


	//points[numVerts - numSides] = { 0,-1,0 };

	vec3 backup = points[numVerts - numSides];
	points[numVerts - numSides] = { 0,-radius,0 };
	glVertexPointer(3, GL_DOUBLE, 0, &points[numVerts - numSides]);
	glNormalPointer(GL_DOUBLE, 0, &points[numVerts - numSides]);

	triangles_indices[numSides + 1] = 1;
	glDrawElements(GL_TRIANGLE_FAN, numSides + 2, GL_UNSIGNED_INT, triangles_indices);
	triangles_indices[numSides + 1] = numSides + 1;
	points[numVerts - numSides] = backup;


	//glBegin(GL_TRIANGLE_FAN);
	//////glBegin(GL_POLYGON);
	//glNormal3d(0, -1, 0);
	//glVertex3d(0, -radius, 0);


	//for (int t = 0; t < numSides; t++)
	//	//		for (t = 0; t<8; t++)

	//{

	//	curX = points[numVerts - t].x;
	//	curY = points[numVerts - t].y;
	//	curZ = points[numVerts - t].z;
	//	glNormal3d(curX, curY, curZ);
	//	glVertex3d(curX, curY, curZ);

	//}

	//curX = points[numVerts].x;
	//curY = points[numVerts].y;
	//curZ = points[numVerts].z;
	//glNormal3d(curX, curY, curZ);
	//glVertex3d(curX, curY, curZ);


	//glEnd();

	//glScalef(5 * CONST_COE / radius, 5 * CONST_COE / radius, 5 * CONST_COE / radius);

}

/////////////////////////////////////////////////
/////////////////////////////////////////////////
/////////////////////////////////////////////////
/////////////////////////////////////////////////
/////////////////////////////////////////////////

static std::chrono::time_point<std::chrono::steady_clock> cmd_start;
static std::chrono::time_point<std::chrono::steady_clock> cmd_end;
static std::chrono::duration<float> cmd_duration;
static bool timmer_ended = true;
void JGN_SolidSphereFpsCalibration()
{
	if (cl_duration.count() > 2)
	{

		sphStacks -= 100;
		sphSides -= 100;

		int c = 0;

		if (sphStacks < 2)
		{
			sphStacks = 2;
			c++;
		}
		if (sphSides < 3)
		{
			sphSides = 3;
			c++;
		}
		if (c == 2)
		{
			sph_pnt_flag++;
			if (sph_pnt_flag >= 2)
			{
				if (timmer_ended)
				{
					cmd_start = std::chrono::high_resolution_clock::now();
					timmer_ended = false;
				}
				cmd_end = std::chrono::high_resolution_clock::now();
				cmd_duration = cmd_end - cmd_start;
				if (cmd_duration.count() > 5)
				{
					shperes_on = 0;
					glDisable(GL_LIGHTING);
					timmer_ended = true;
				}
			}


			return;
		}

		JGN_QRedisplay();

	}
	else if (cl_duration.count() > 0.5)
	{

		sphStacks -= 60;
		sphSides -= 60;


		int c = 0;

		if (sphStacks < 2)
		{
			sphStacks = 2;
			c++;
		}
		if (sphSides < 3)
		{
			sphSides = 3;
			c++;
		}
		if (c == 2)
		{
			sph_pnt_flag++;
			if (sph_pnt_flag >= 2)
			{
				if (timmer_ended)
				{
					cmd_start = std::chrono::high_resolution_clock::now();
					timmer_ended = false;
				}
				cmd_end = std::chrono::high_resolution_clock::now();
				cmd_duration = cmd_end - cmd_start;
				if (cmd_duration.count() > 5)
				{
					shperes_on = 0;
					glDisable(GL_LIGHTING);
					timmer_ended = true;
				}
			}

		

			return;
		}

		JGN_QRedisplay();

	}
	else if (cl_duration.count() > 0.06)
	{

		sphStacks -= 30;
		sphSides -= 30;


		int c = 0;

		if (sphStacks < 2)
		{
			sphStacks = 2;
			c++;
		}
		if (sphSides < 3)
		{
			sphSides = 3;
			c++;
		}
		if (c == 2)
		{
			sph_pnt_flag++;
			if (sph_pnt_flag >= 2)
			{
				if (timmer_ended)
				{
					cmd_start = std::chrono::high_resolution_clock::now();
					timmer_ended = false;
				}
				cmd_end = std::chrono::high_resolution_clock::now();
				cmd_duration = cmd_end - cmd_start;
				if (cmd_duration.count() > 5)
				{
					shperes_on = 0;
					glDisable(GL_LIGHTING);
					timmer_ended = true;
				}
			}
		
			return;
		}

		JGN_QRedisplay();

	}
	else if (cl_duration.count() < 0.03)
	{
		timmer_ended = true;
		if (shperes_on == 0 && cl_duration.count() < 0.015)
		{
			shperes_on = 1;
			sphStacks = 2;
			sphSides = 3;
			glEnable(GL_LIGHTING);

		}
		else
		{
			sph_pnt_flag = 0;
			(sphStacks < sphSides) ? sphStacks++ : sphSides++;

			if (sphStacks > 100)
			{
				sphStacks = 100;
				return;

			}
			if (sphSides > 100)
			{
				sphSides = 100;
				return;

			}
		}

		//JGN_QRedisplay();

	}
}