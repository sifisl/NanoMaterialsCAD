#include "Cammera.h"



Cammera::Cammera()
{
}


Cammera::~Cammera()
{
}

void Cammera::loadperspectivematrix()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, width, height);//(first 2 sets the lower left corner of the window w h sets width height of the window

	float permatrix[16];
	float ymax = height, xmax = width;
	if (width <= height)
	{

		xmax = 0.005;
		ymax = 0.005*height / width;
	}
	else
	{
		xmax = 0.005*width / height;
		ymax = 0.005;
	}

	float temp, temp2, temp3, temp4;
	float znear = 0.01;
	float fovyInDegrees = 60;
	// ymin = -ymax;
	// xmin = -ymax * aspectRatio;
	float left = -xmax;
	float right = xmax;
	float top = ymax;
	float bottom = -ymax;
	float zfar = 100;

	temp = 2.0 * znear;
	temp2 = right - left;
	temp3 = top - bottom;
	temp4 = zfar - znear;

	permatrix[0] = temp / temp2;
	permatrix[1] = 0.0;
	permatrix[2] = 0.0;
	permatrix[3] = 0.0;
	permatrix[4] = 0.0;
	permatrix[5] = temp / temp3;
	permatrix[6] = 0.0;
	permatrix[7] = 0.0;
	permatrix[8] = (right + left) / temp2;
	permatrix[9] = (top + bottom) / temp3;
	permatrix[10] = (-zfar - znear) / temp4;
	permatrix[11] = -1.0;
	permatrix[12] = 0.0;
	permatrix[13] = 0.0;
	permatrix[14] = (-temp * zfar) / temp4;
	permatrix[15] = 0.0;
	glMultMatrixf(permatrix);
	glTranslated(0, 0, -3);
	glMatrixMode(GL_MODELVIEW);

}
void Cammera::loadorthmatrix()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (width <= height)
	{
		glOrtho(
			-1.05, +1.05,
			-1.05 * (GLfloat)height / (GLfloat)width, +1.05 * (GLfloat)height / (GLfloat)width,
			-10.0, 10.0);
		dipleft = -1.05;
		dipapan = 1.05*(GLfloat)height / (GLfloat)width;

	}
	else
	{
		glOrtho(
			-1.05 * (GLfloat)width / (GLfloat)height, +1.05 * (GLfloat)width / (GLfloat)height,
			-1.05, +1.05,
			-10.0, 10.0);
		dipleft = -1.05*(GLfloat)width / (GLfloat)height;
		dipapan = 1.05;

	}
	glMatrixMode(GL_MODELVIEW);

}