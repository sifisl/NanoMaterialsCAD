
#include "stdafx.h"

#include "JGN_Build.h"
#include "JGN_Windows.h"
#include "JGN_SolidSphere.h"
#include "JGN_bmpLoader.h"
#include "JGN_StrokeCharacter.h"

#define glutSolidSphere JGN_SolidSphere
// TODO: make a class instead of the crystal array
//test

int main(int argc, char *argv[])
{
	

#if NDEBUG
	FreeConsole();
#endif

	char s[200];


	sized[0] = 1;
	sized[1] = 1;
	sized[2] = 1;
	sized_old[0] = 1;
	sized_old[1] = 1;
	sized_old[2] = 1;


	JGN_Init();
	JGN_InitWindowPosition(GetSystemMetrics(SM_CXSCREEN)/2 - 500, GetSystemMetrics(SM_CYSCREEN) / 2 - 400);
	JGN_InitWindowSize(1000, 800);
	JGN_CreateWindow("Ptyxiakh v1.0a");



	JGN_ReshapeFunc(myReshape);//gia to window reshape
	JGN_DisplayFunc(display1);
	JGN_KeyboardFunc(keyboardgl);
	

	JGN_PassiveMotionFunc(mouse_pasive);
	JGN_MouseFunc(mouse_func);


	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_NORMALIZE);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	myinit();

	jgn_initcmd();
	JGN_PostRedisplay();

	CustomSurfacesOn = 1;

	JGN_bmpLoad("JGN_Font.bmp", JGN_RGBA);


	glGenTextures(1, &Font);
	glBindTexture(GL_TEXTURE_2D, Font);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, JGN_bmpWidth, JGN_bmpHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, JGN_bmpData);

	openfont("JGN_Font.fnt");


	JGN_MainLoop();
	//  Free memory.
	//delete[] xyz;
	closefont();


	return 0;
}



void myReshape(int w, int h)// window reshape
{
	width = w;
	height = h;

	glViewport(0, 0, width, height);//(first 2 sets the lower left corner of the window w h sets width height of the window
	glMatrixMode(GL_PROJECTION);// defines the camera behavior projection is the view point of me

	glLoadIdentity();//load the origin matrix the original place view point etc...
					 // gia na mhn allwienetai h eikona kanw to if
					 //multiply the current matrix with an orthographic matrix
					 //glOrtho(Specify the coordinates for the left and right vertical clipping planes
					 //Specify the coordinates for the bottom and top horizontal clipping planes.
					 //Specify the distances to the nearest and farthest depth clipping planes)
	//cout << w << "X" << h << endl;
	if (perspective_on)
	{
		//gluPerspective(60, (float)w / (float)h, 0.001, 100);
	}
	else
	{
		if (w <= h)
		{
			glOrtho(
				-1.05, +1.05,
				-1.05 * (GLfloat)h / (GLfloat)w, +1.05 * (GLfloat)h / (GLfloat)w,
				-10.0, 10.0);
			dipleft = -1;

		}
		else
		{
			glOrtho(
				-1.05 * (GLfloat)w / (GLfloat)h, +1.05 * (GLfloat)w / (GLfloat)h,
				-1.05, +1.05,
				-10.0, 10.0);
			dipleft = -(GLfloat)w / (GLfloat)h;

		}
	}

	glMatrixMode(GL_MODELVIEW);//modelview would be the manipulation of the object

	//JGN_PostRedisplay();

	return;
}


char *s1itoa = (char*)malloc(sizeof(char) * 5);
int Scounter = 0;
int stroke_c = 0;


void display1(void)//generates the graphics output.
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	for (int ii = 0; ii < a; ii++)
	{
		aatoms[ii] = 0;
	}



	if (perspective_on)
	{
		glViewport(0, 0, width, height);//(first 2 sets the lower left corner of the window w h sets width height of the window
		glMatrixMode(GL_PROJECTION);// defines the camera behavior projection is the view point of me
		glLoadIdentity();
		if (width <= height)
		{
			glOrtho(
				-1.05, +1.05,
				-1.05 * (GLfloat)height / (GLfloat)width, +1.05 * (GLfloat)height / (GLfloat)width,
				-10.0, 10.0);
			dipleft = -1;


		}
		else
		{
			glOrtho(
				-1.05 * (GLfloat)width / (GLfloat)height, +1.05 * (GLfloat)width / (GLfloat)height,
				-1.05, +1.05,
				-10.0, 10.0);
			dipleft = -(GLfloat)width / (GLfloat)height;

		}
		glMatrixMode(GL_MODELVIEW);
	}
	glPointSize(pointsize);

	stroke_c = 0;
	if (perspective_on)
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		//gluPerspective(60, (float)width / (float)height, 0.001, 100);
		glMatrixMode(GL_MODELVIEW);
	}
	glLoadIdentity();

	/////////////////
	float p[3];
	//int point;

	//  indicates default buffers



	glLoadIdentity();
	//glRotatef(theta[0], cos((pi*theta[1]) / 180), 0.0, sin((pi*theta[1]) / 180));
	glTranslatef(0, .3, 0);
	if (perspective_on)
	{
		glTranslated(0, 0, -3);
		if (Rod_like == -1)
		{
			glTranslated(0, 0, 1);

		}
	}
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
	//if (mouse_check == 1 ) {
	//	glRotatef(sqrt(theta[1] * theta[1] + theta[0] * theta[0]), theta[0] - theta_pr[0], theta[1] - theta_pr[1], 0.0);
	//}
	//cout << theta[0] - theta_pr[0] << " " << theta[1] - theta_pr[1] << "\n";
	//theta_pr[0] = theta[0];
	//theta_pr[1] = theta[1];

	//glRotatef(theta[0], cos((pi*theta[1])/180), sin((pi*theta[1])/180)*cos((pi*theta[0])/180), sin((pi*theta[0])/180)*sin((pi*theta[1])/180));
	//glRotatef(theta[1], sin((pi*theta[0]) / 180)*sin((pi*theta[1]) / 180), cos((pi*theta[0])/180), -sin((pi*theta[0])/180)*cos((pi*theta[1]) / 180));


		ball_atoms = 0;

		int ajklsdfl = t * (sized[0])*(sized[1])*(sized[2]);
		for (ole3 = 0; ole3 < ajklsdfl; ole3++)
		{
			if (nanotube)
			{
				p[0] = crystal[2 + 5 * ole3];
				p[1] = crystal[3 + 5 * ole3];
				p[2] = crystal[4 + 5 * ole3];

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

				//if (i == CustomSurfacesCount)
				if (true)
				{
					for (int ii = 0; ii < a; ii++)
					{
						if (crystal[5 * ole3] == anumber[ii])
						{
							aatoms[ii]++;
						}
					}
					if (render_is_on)
					{
						colr[0] = fmod(crystal[1 + 5 * ole3], 1.5);
						colr[1] = fmod(crystal[5 * ole3], 0.92);
						colr[2] = fmod(100 * colr[0] * colr[1], 0.8);
						glColor3fv(colr);
						//glColor3f(1, 0.7, 0);
						ball_atoms++;

						p[0] = crystal[2 + 5 * ole3] / (Svmax + 5);
						p[1] = crystal[3 + 5 * ole3] / (Svmax + 5);
						p[2] = crystal[4 + 5 * ole3] / (Svmax + 5);


						if (shperes_on)
						{
							GLfloat mat_ambient[] = { colr[0], colr[1], colr[2], 1.0 };
							GLfloat mat_deffuse[] = { colr[0], colr[1], colr[2], 1.0 };

							glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
							glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_deffuse);

							glTranslatef(p[0], p[1], p[2]);

							glutSolidSphere(pointsize*0.001, 10, 10);

							glTranslatef(-p[0], -p[1], -p[2]);
						}
						else
						{
							glBegin(GL_POINTS);


							glVertex3fv(p);


							glEnd();
						}
					}
				}
			}
			else if (want_cyrcle[0] == 'y' || want_cyrcle[0] == 'Y')
			{
				if (vacuum ^ (rad >= sqrt(crystal[2 + 5 * ole3] * crystal[2 + 5 * ole3] + crystal[3 + 5 * ole3] * crystal[3 + 5 * ole3] + crystal[4 + 5 * ole3] * crystal[4 + 5 * ole3])))
				{
					p[0] = crystal[2 + 5 * ole3];
					p[1] = crystal[3 + 5 * ole3];
					p[2] = crystal[4 + 5 * ole3];

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
						for (int ii = 0; ii < a; ii++)
						{
							if (crystal[5 * ole3] == anumber[ii])
							{
								aatoms[ii]++;
							}
						}
						if (render_is_on)
						{
							colr[0] = fmod(crystal[1 + 5 * ole3], 1.5);
							colr[1] = fmod(crystal[5 * ole3], 0.92);
							colr[2] = fmod(100 * colr[0] * colr[1], 0.8);
							glColor3fv(colr);

							ball_atoms++;

							p[0] = crystal[2 + 5 * ole3] / (Svmax + 5);
							p[2] = crystal[3 + 5 * ole3] / (Svmax + 5);
							p[1] = crystal[4 + 5 * ole3] / (Svmax + 5);

							if (shperes_on)
							{
								GLfloat mat_ambient[] = { colr[0], colr[1], colr[2], 1.0 };
								GLfloat mat_deffuse[] = { colr[0], colr[1], colr[2], 1.0 };

								glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
								glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_deffuse);

								glTranslatef(p[0], p[1], p[2]);

								glutSolidSphere(pointsize*0.001, 10, 10);

								glTranslatef(-p[0], -p[1], -p[2]);
							}
							else
							{
								glBegin(GL_POINTS);


								glVertex3fv(p);


								glEnd();
							}
						}
					}
				}
			}
			else if (CustomSurfacesOn)
			{
				if (CustomSurfacesCount == 0)
				{
					for (int ii = 0; ii < a; ii++)
					{
						if (crystal[5 * ole3] == anumber[ii])
						{
							aatoms[ii]++;
						}
					}
					if (render_is_on)
					{
						colr[0] = fmod(crystal[1 + 5 * ole3], 1.5);
						colr[1] = fmod(crystal[5 * ole3], 0.92);
						colr[2] = fmod(100 * colr[0] * colr[1], 0.8);
						glColor3fv(colr);

						ball_atoms++;
						p[0] = crystal[2 + 5 * ole3] / (Svmax + 5);
						p[1] = crystal[3 + 5 * ole3] / (Svmax + 5);
						p[2] = crystal[4 + 5 * ole3] / (Svmax + 5);

						if (shperes_on)
						{
							GLfloat mat_ambient[] = { colr[0], colr[1], colr[2], 1.0 };
							GLfloat mat_deffuse[] = { colr[0], colr[1], colr[2], 1.0 };

							glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
							glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_deffuse);

							glTranslatef(p[0], p[1], p[2]);

							glutSolidSphere(pointsize*0.001, 10, 10);

							glTranslatef(-p[0], -p[1], -p[2]);
						}
						else
						{





							glBegin(GL_POINTS);


							glVertex3fv(p);


							glEnd();
						}
					}
				}
				else
				{
					p[0] = crystal[2 + 5 * ole3];
					p[1] = crystal[3 + 5 * ole3];
					p[2] = crystal[4 + 5 * ole3];

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
						for (int ii = 0; ii < a; ii++)
						{
							if (crystal[5 * ole3] == anumber[ii])
							{
								aatoms[ii]++;
							}
						}
						if (render_is_on)
						{
							p[0] = p[0] / (Svmax + 5);
							p[2] = p[2] / (Svmax + 5);
							p[1] = p[1] / (Svmax + 5);

							colr[0] = fmod(crystal[1 + 5 * ole3], 1.5);
							colr[1] = fmod(crystal[5 * ole3], 0.92);
							colr[2] = fmod(100 * colr[0] * colr[1], 0.8);
							glColor3fv(colr);

							ball_atoms++;

							if (shperes_on)
							{
								GLfloat mat_ambient[] = { colr[0], colr[1], colr[2], 1.0 };
								GLfloat mat_deffuse[] = { colr[0], colr[1], colr[2], 1.0 };

								glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
								glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_deffuse);

								glTranslatef(p[0], p[1], p[2]);

								glutSolidSphere(pointsize*0.001, 10, 10);

								glTranslatef(-p[0], -p[1], -p[2]);
							}
							else
							{
								glBegin(GL_POINTS);

								glVertex3fv(p);


								glEnd();
							}
						}
					}
				}

			}
			else if (jgn_supercell)
			{
				for (int ii = 0; ii < a; ii++)
				{
					if (crystal[5 * ole3] == anumber[ii])
					{
						aatoms[ii]++;
					}
				}
				if (render_is_on)
				{
					colr[0] = fmod(crystal[1 + 5 * ole3], 1.5);
					colr[1] = fmod(crystal[5 * ole3], 0.92);
					colr[2] = fmod(100 * colr[0] * colr[1], 0.8);
					glColor3fv(colr);
					ball_atoms++;

					p[0] = crystal[2 + 5 * ole3] / (Svmax + 5);
					p[2] = crystal[3 + 5 * ole3] / (Svmax + 5);
					p[1] = crystal[4 + 5 * ole3] / (Svmax + 5);

					if (shperes_on)
					{
						GLfloat mat_ambient[] = { colr[0], colr[1], colr[2], 1.0 };
						GLfloat mat_deffuse[] = { colr[0], colr[1], colr[2], 1.0 };

						glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
						glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_deffuse);

						glTranslatef(p[0], p[1], p[2]);

						glutSolidSphere(pointsize*0.001, 10, 10);

						glTranslatef(-p[0], -p[1], -p[2]);
					}
					else
					{
						glBegin(GL_POINTS);


						glVertex3fv(p);


						glEnd();
					}
				}
			}
			else
			{

				if (Right_Hexagonal == -1)
				{
					///if ((S1i[0] * figure_1*abs(crystal[2 + 0 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]) <= S1v) && (S1i[0] * Right_Hexagonal*Rod_like* abs(crystal[2 + 2 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]) <= S1v) && (S1i[0] * figure_1*Right_Hexagonal*abs(crystal[2 + 1 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]) <= S1v) && S2i[0] * figure_1* abs(crystal[2 + 0 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]) + S2i[0] * figure_1* 2*abs(crystal[2 + 1 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]) <= S2v)
					if (vacuum ^ (abs(crystal[4 + 5 * ole3]) < Right_Hexagonal_height && (S1i[0] * abs(crystal[2 + 5 * ole3]) <= S2v * 0.86602540378) && S2i[0] * abs(crystal[2 + 5 * ole3]) / 1.73205 + S2i[0] * abs(crystal[3 + 5 * ole3]) <= S2v &&
						(S1i[0] * abs(crystal[3 + 5 * ole3]) < S1v *0.86602540378) && S2i[0] * abs(crystal[2 + 5 * ole3]) + S1i[0] * abs(crystal[3 + 5 * ole3]) / 1.73205 < S1v))

					{
						p[0] = crystal[2 + 5 * ole3];
						p[1] = crystal[3 + 5 * ole3];
						p[2] = crystal[4 + 5 * ole3];

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
							for (int ii = 0; ii < a; ii++)
							{
								if (crystal[5 * ole3] == anumber[ii])
								{
									aatoms[ii]++;
								}
							}
							if (render_is_on)
							{
								colr[0] = fmod(crystal[1 + 5 * ole3], 1.5);
								colr[1] = fmod(crystal[5 * ole3], 0.92);
								colr[2] = fmod(100 * colr[0] * colr[1], 0.8);
								glColor3fv(colr);
								ball_atoms++;

								p[0] = crystal[2 + 5 * ole3] / (Svmax + 5);
								p[2] = crystal[3 + 5 * ole3] / (Svmax + 5);
								p[1] = crystal[4 + 5 * ole3] / (Svmax + 5);


								if (shperes_on)
								{
									GLfloat mat_ambient[] = { colr[0], colr[1], colr[2], 1.0 };
									GLfloat mat_deffuse[] = { colr[0], colr[1], colr[2], 1.0 };

									glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
									glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_deffuse);

									glTranslatef(p[0], p[1], p[2]);

									glutSolidSphere(pointsize*0.001, 10, 10);

									glTranslatef(-p[0], -p[1], -p[2]);
								}
								else
								{
									glBegin(GL_POINTS);

									glVertex3fv(p);
									glEnd();
								}

							}
						}
					}


				}
				else
				{
					if (vacuum ^ ((S1i[0] * figure_1*abs(crystal[2 + 5 * ole3]) <= S1v) &&
						(S1i[0] * Right_Hexagonal*Rod_like* abs(crystal[4 + 5 * ole3]) <= S1v) &&
						(S1i[0] * figure_1*abs(crystal[3 + 5 * ole3]) <= S1v) &&
						Rod_like*(S2i[0] * abs(crystal[2 + 5 * ole3]) + S2i[0] * Right_Hexagonal* abs(crystal[4 + 5 * ole3])) <= S2v &&
						S2i[0] * figure_1* abs(crystal[2 + 5 * ole3]) + S2i[0] * figure_1* abs(crystal[3 + 5 * ole3]) <= S2v &&
						Rod_like*(S2i[0] * Right_Hexagonal* abs(crystal[4 + 5 * ole3]) + S2i[0] * abs(crystal[3 + 5 * ole3])) <= S2v &&
						Right_Hexagonal*(S3i[0] * abs(crystal[2 + 5 * ole3]) + S3i[1] * abs(crystal[4 + 5 * ole3]) + S3i[2] * abs(crystal[3 + 5 * ole3])) <= S3v))
					{
						p[0] = crystal[2 + 5 * ole3];
						p[1] = crystal[3 + 5 * ole3];
						p[2] = crystal[4 + 5 * ole3];

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
							for (int ii = 0; ii < a; ii++)
							{
								if (crystal[5 * ole3] == anumber[ii])
								{
									aatoms[ii]++;
								}
							}
							if (render_is_on)
							{
								colr[0] = fmod(crystal[1 + 5 * ole3], 1.5);
								colr[1] = fmod(crystal[5 * ole3], 0.92);
								colr[2] = fmod(100 * colr[0] * colr[1], 0.8);
								glColor3fv(colr);

								ball_atoms++;

								p[0] = crystal[2 + 5 * ole3] / (Svmax + 5);
								p[2] = crystal[3 + 5 * ole3] / (Svmax + 5);
								p[1] = crystal[4 + 5 * ole3] / (Svmax + 5);
								if (shperes_on)
								{
									GLfloat mat_ambient[] = { colr[0], colr[1], colr[2], 1.0 };
									GLfloat mat_deffuse[] = { colr[0], colr[1], colr[2], 1.0 };

									glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
									glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_deffuse);

									glTranslatef(p[0], p[1], p[2]);

									glutSolidSphere(pointsize*0.001, 10, 10);

									glTranslatef(-p[0], -p[1], -p[2]);
								}
								else
								{
									glBegin(GL_POINTS);

									glVertex3fv(p);
									glEnd();
								}
							}
						}
					}

				}







			}
		}

	if (CustomSurfacesOn)
	{
		if (shperes_on)
			glDisable(GL_LIGHTING);
		glBegin(GL_LINES);
		
		glColor3f(1, 0, 0);
		glVertex3f(0, 0, 0);
		vec[0] = 10000 * ijk[0][0];
		vec[1] = 10000 * ijk[0][1];
		vec[2] = 10000 * ijk[0][2];
		glVertex3fv(vec);

		glColor3f(0, 1, 0);
		glVertex3f(0, 0, 0);
		vec[0] = 10000 * ijk[1][0];
		vec[1] = 10000 * ijk[1][1];
		vec[2] = 10000 * ijk[1][2];
		glVertex3fv(vec);



		glColor3f(0, 0, 1);
		glVertex3f(0, 0, 0);
		vec[0] = 10000 * ijk[2][0];
		vec[1] = 10000 * ijk[2][1];
		vec[2] = 10000 * ijk[2][2];
		glVertex3fv(vec);

		glEnd();

		if (shperes_on)
			glEnable(GL_LIGHTING);
	}
	
	glColor3f(0.0, 0.0, 0.0);


	glBegin(GL_LINES);
//	//simumation box
//	vec[0] = sim_box_lo[0] / (Svmax + 5);
//	vec[1] = sim_box_lo[1] / (Svmax + 5);
//	vec[2] = sim_box_lo[2] / (Svmax + 5);
//	glVertex3fv(vec);//000
//	vec[0] = (ijk[0][0] * sized[0] + sim_box_lo[0]) / (Svmax + 5);
//	vec[1] = (ijk[0][1] * sized[1] + sim_box_lo[1]) / (Svmax + 5);
//	vec[2] = (ijk[0][2] * sized[2] + sim_box_lo[2]) / (Svmax + 5);
//	glVertex3fv(vec);//+x
//
//
//	glVertex3fv(vec);//+x
//	vec[0] = ((ijk[1][0] + ijk[0][0]) * sized[0] + sim_box_lo[0]) / (Svmax + 5);
//	vec[1] = ((ijk[1][1] + ijk[0][1]) * sized[1] + sim_box_lo[1]) / (Svmax + 5);
//	vec[2] = ((ijk[1][2] + ijk[0][2]) * sized[2] + sim_box_lo[2]) / (Svmax + 5);
//	glVertex3fv(vec);//+x+y
//
//	glVertex3fv(vec);//+x+y
//	vec[0] = (ijk[1][0] * sized[0] + sim_box_lo[0]) / (Svmax + 5);
//	vec[1] = (ijk[1][1] * sized[1] + sim_box_lo[1]) / (Svmax + 5);
//	vec[2] = (ijk[1][2] * sized[2] + sim_box_lo[2]) / (Svmax + 5);
//	glVertex3fv(vec);//+y
//
//	glVertex3fv(vec);//+y
//	vec[0] = sim_box_lo[0] / (Svmax + 5);
//	vec[1] = sim_box_lo[1] / (Svmax + 5);
//	vec[2] = sim_box_lo[2] / (Svmax + 5);
//	glVertex3fv(vec);//000
///////////////////////
//	vec[0] = (sim_box_lo[0] + ijk[2][0] * sized[0]) / (Svmax + 5);
//	vec[1] = (sim_box_lo[1] + ijk[2][1] * sized[1]) / (Svmax + 5);
//	vec[2] = (sim_box_lo[2] + ijk[2][2] * sized[2]) / (Svmax + 5);
//	glVertex3fv(vec);//+z
//	vec[0] = ((ijk[0][0] + ijk[2][0] + ijk[2][0]) * sized[0] + sim_box_lo[0]) / (Svmax + 5);
//	vec[1] = ((ijk[0][1] + ijk[2][1] + ijk[2][1]) * sized[1] + sim_box_lo[1]) / (Svmax + 5);
//	vec[2] = ((ijk[0][2] + ijk[2][2] + ijk[2][1]) * sized[2] + sim_box_lo[2]) / (Svmax + 5);
//	glVertex3fv(vec);//+x+z
//
//
//	glVertex3fv(vec);//+x+z
//	vec[0] = ((ijk[1][0] + ijk[0][0] + ijk[2][0]) * sized[0] + sim_box_lo[0]) / (Svmax + 5);
//	vec[1] = ((ijk[1][1] + ijk[0][1] + ijk[2][1]) * sized[1] + sim_box_lo[1]) / (Svmax + 5);
//	vec[2] = ((ijk[1][2] + ijk[0][2] + ijk[2][2]) * sized[2] + sim_box_lo[2]) / (Svmax + 5);
//	glVertex3fv(vec);//+x+y+z
//
//	glVertex3fv(vec);//+x+y+z
//	vec[0] = ((ijk[1][0] + ijk[2][0]) * sized[0] + sim_box_lo[0]) / (Svmax + 5);
//	vec[1] = ((ijk[1][1] + ijk[2][1]) * sized[1] + sim_box_lo[1]) / (Svmax + 5);
//	vec[2] = ((ijk[1][2] + ijk[2][2]) * sized[2] + sim_box_lo[2]) / (Svmax + 5);
//	glVertex3fv(vec);//+y+z
//
//	glVertex3fv(vec);//+y+z
//	vec[0] = (sim_box_lo[0] + ijk[2][0] * sized[0]) / (Svmax + 5);
//	vec[1] = (sim_box_lo[1] + ijk[2][1] * sized[1]) / (Svmax + 5);
//	vec[2] = (sim_box_lo[2] + ijk[2][2] * sized[2]) / (Svmax + 5);
//	glVertex3fv(vec);//+z
/////////
//	glVertex3fv(vec);//+z
//	vec[0] = sim_box_lo[0] / (Svmax + 5);
//	vec[1] = sim_box_lo[1] / (Svmax + 5);
//	vec[2] = sim_box_lo[2] / (Svmax + 5);
//	glVertex3fv(vec);//000
//
//	vec[0] = ((ijk[0][0] + ijk[2][0] + ijk[2][0]) * sized[0] + sim_box_lo[0]) / (Svmax + 5);
//	vec[1] = ((ijk[0][1] + ijk[2][1] + ijk[2][1]) * sized[1] + sim_box_lo[1]) / (Svmax + 5);
//	vec[2] = ((ijk[0][2] + ijk[2][2] + ijk[2][1]) * sized[2] + sim_box_lo[2]) / (Svmax + 5);
//	glVertex3fv(vec);//+x+z
//	vec[0] = (ijk[0][0] * sized[0] + sim_box_lo[0]) / (Svmax + 5);
//	vec[1] = (ijk[0][1] * sized[1] + sim_box_lo[1]) / (Svmax + 5);
//	vec[2] = (ijk[0][2] * sized[2] + sim_box_lo[2]) / (Svmax + 5);
//	glVertex3fv(vec);//+x
//
//	vec[0] = ((ijk[1][0] + ijk[0][0] + ijk[2][0]) * sized[0] + sim_box_lo[0]) / (Svmax + 5);
//	vec[1] = ((ijk[1][1] + ijk[0][1] + ijk[2][1]) * sized[1] + sim_box_lo[1]) / (Svmax + 5);
//	vec[2] = ((ijk[1][2] + ijk[0][2] + ijk[2][2]) * sized[2] + sim_box_lo[2]) / (Svmax + 5);
//	glVertex3fv(vec);//+x+y+z
//	vec[0] = ((ijk[1][0] + ijk[0][0]) * sized[0] + sim_box_lo[0]) / (Svmax + 5);
//	vec[1] = ((ijk[1][1] + ijk[0][1]) * sized[1] + sim_box_lo[1]) / (Svmax + 5);
//	vec[2] = ((ijk[1][2] + ijk[0][2]) * sized[2] + sim_box_lo[2]) / (Svmax + 5);
//	glVertex3fv(vec);//+x+y
//
//	vec[0] = ((ijk[1][0] + ijk[2][0]) * sized[0] + sim_box_lo[0]) / (Svmax + 5);
//	vec[1] = ((ijk[1][1] + ijk[2][1]) * sized[1] + sim_box_lo[1]) / (Svmax + 5);
//	vec[2] = ((ijk[1][2] + ijk[2][2]) * sized[2] + sim_box_lo[2]) / (Svmax + 5);
//	glVertex3fv(vec);//+y+z
//	vec[0] = (ijk[1][0] * sized[0] + sim_box_lo[0]) / (Svmax + 5);
//	vec[1] = (ijk[1][1] * sized[1] + sim_box_lo[1]) / (Svmax + 5);
//	vec[2] = (ijk[1][2] * sized[2] + sim_box_lo[2]) / (Svmax + 5);
//	glVertex3fv(vec);//+y
//


	if (jgn_supercell || nanotube)
	{


	}
	else if (CustomSurfacesOn)
	{

	}
	else if (want_cyrcle[0] == 'y' || want_cyrcle[0] == 'Y')
	{
		glColor3f(0, 0, 0);

		vec[0] = 0;
		vec[1] = (rad + 5) / (Svmax + 5);
		vec[2] = 0;

		glVertex3fv(vec);
		vec[1] = -(rad + 5) / (Svmax + 5);
		glVertex3fv(vec);

		vec[0] = (rad + 5) / (Svmax + 5);
		vec[1] = 0;
		glVertex3fv(vec);
		vec[0] = -(rad + 5) / (Svmax + 5);

		glVertex3fv(vec);
	}
	else if (figure_1 == -1)
	{
		int S1vb = S1v;
		int S2vb = S2v;
		int S3vb = S3v;



		if (2 * S2v - S3v >= S1v)
		{
			if (S3v < S2v)
			{
				S2v = S3v;
			}
			if (S3v < S1v)
			{
				S1v = S3v;
			}
			
			i = 1;
			j = 1;
			k = 1;

			glVertex3f(i*first, j*third, k*second);
			glVertex3f(i*first, 0, k*forth);

			glVertex3f(i*first, 0, k*forth);
			glVertex3f(0, 0, k*forth);

			glVertex3f(i*first, 0, k*forth);
			glVertex3f(i*forth, 0, k*first);

			glVertex3f(i*forth, 0, k*first);
			glVertex3f(i*second, j*third, k*first);

			glVertex3f(i*second, j*third, k*first);
			glVertex3f(i*first, j*third, k*second);

			glVertex3f(i*forth, 0, k*first);
			glVertex3f(i*forth, 0, 0);

			glVertex3f(i*first, j*third, k*second);
			glVertex3f(0, j*third, k*second);

			glVertex3f(i*second, j*third, k*first);
			glVertex3f(i*second, j*third, 0);

			i = -1;
			j = 1;
			k = 1;
			glVertex3f(i*first, j*third, k*second);
			glVertex3f(i*first, 0, k*forth);

			glVertex3f(i*first, 0, k*forth);
			glVertex3f(0, 0, k*forth);

			glVertex3f(i*first, 0, k*forth);
			glVertex3f(i*forth, 0, k*first);

			glVertex3f(i*forth, 0, k*first);
			glVertex3f(i*second, j*third, k*first);

			glVertex3f(i*second, j*third, k*first);
			glVertex3f(i*first, j*third, k*second);

			glVertex3f(i*forth, 0, k*first);
			glVertex3f(i*forth, 0, 0);

			glVertex3f(i*first, j*third, k*second);
			glVertex3f(0, j*third, k*second);

			glVertex3f(i*second, j*third, k*first);
			glVertex3f(i*second, j*third, 0);
			i = 1;
			j = -1;
			k = 1;
			glVertex3f(i*first, j*third, k*second);
			glVertex3f(i*first, 0, k*forth);

			glVertex3f(i*first, 0, k*forth);
			glVertex3f(0, 0, k*forth);

			glVertex3f(i*first, 0, k*forth);
			glVertex3f(i*forth, 0, k*first);

			glVertex3f(i*forth, 0, k*first);
			glVertex3f(i*second, j*third, k*first);

			glVertex3f(i*second, j*third, k*first);
			glVertex3f(i*first, j*third, k*second);

			glVertex3f(i*forth, 0, k*first);
			glVertex3f(i*forth, 0, 0);

			glVertex3f(i*first, j*third, k*second);
			glVertex3f(0, j*third, k*second);

			glVertex3f(i*second, j*third, k*first);
			glVertex3f(i*second, j*third, 0);
			i = 1;
			j = 1;
			k = -1;
			glVertex3f(i*first, j*third, k*second);
			glVertex3f(i*first, 0, k*forth);

			glVertex3f(i*first, 0, k*forth);
			glVertex3f(0, 0, k*forth);

			glVertex3f(i*first, 0, k*forth);
			glVertex3f(i*forth, 0, k*first);

			glVertex3f(i*forth, 0, k*first);
			glVertex3f(i*second, j*third, k*first);

			glVertex3f(i*second, j*third, k*first);
			glVertex3f(i*first, j*third, k*second);

			glVertex3f(i*forth, 0, k*first);
			glVertex3f(i*forth, 0, 0);

			glVertex3f(i*first, j*third, k*second);
			glVertex3f(0, j*third, k*second);

			glVertex3f(i*second, j*third, k*first);
			glVertex3f(i*second, j*third, 0);
			i = -1;
			j = -1;
			k = 1;
			glVertex3f(i*first, j*third, k*second);
			glVertex3f(i*first, 0, k*forth);

			glVertex3f(i*first, 0, k*forth);
			glVertex3f(0, 0, k*forth);

			glVertex3f(i*first, 0, k*forth);
			glVertex3f(i*forth, 0, k*first);

			glVertex3f(i*forth, 0, k*first);
			glVertex3f(i*second, j*third, k*first);

			glVertex3f(i*second, j*third, k*first);
			glVertex3f(i*first, j*third, k*second);

			glVertex3f(i*forth, 0, k*first);
			glVertex3f(i*forth, 0, 0);

			glVertex3f(i*first, j*third, k*second);
			glVertex3f(0, j*third, k*second);

			glVertex3f(i*second, j*third, k*first);
			glVertex3f(i*second, j*third, 0);
			i = -1;
			j = 1;
			k = -1;
			glVertex3f(i*first, j*third, k*second);
			glVertex3f(i*first, 0, k*forth);

			glVertex3f(i*first, 0, k*forth);
			glVertex3f(0, 0, k*forth);

			glVertex3f(i*first, 0, k*forth);
			glVertex3f(i*forth, 0, k*first);

			glVertex3f(i*forth, 0, k*first);
			glVertex3f(i*second, j*third, k*first);

			glVertex3f(i*second, j*third, k*first);
			glVertex3f(i*first, j*third, k*second);

			glVertex3f(i*forth, 0, k*first);
			glVertex3f(i*forth, 0, 0);

			glVertex3f(i*first, j*third, k*second);
			glVertex3f(0, j*third, k*second);

			glVertex3f(i*second, j*third, k*first);
			glVertex3f(i*second, j*third, 0);
			i = 1;
			j = -1;
			k = -1;
			glVertex3f(i*first, j*third, k*second);
			glVertex3f(i*first, 0, k*forth);

			glVertex3f(i*first, 0, k*forth);
			glVertex3f(0, 0, k*forth);

			glVertex3f(i*first, 0, k*forth);
			glVertex3f(i*forth, 0, k*first);

			glVertex3f(i*forth, 0, k*first);
			glVertex3f(i*second, j*third, k*first);

			glVertex3f(i*second, j*third, k*first);
			glVertex3f(i*first, j*third, k*second);

			glVertex3f(i*forth, 0, k*first);
			glVertex3f(i*forth, 0, 0);

			glVertex3f(i*first, j*third, k*second);
			glVertex3f(0, j*third, k*second);

			glVertex3f(i*second, j*third, k*first);
			glVertex3f(i*second, j*third, 0);
			i = -1;
			j = -1;
			k = -1;
			glVertex3f(i*first, j*third, k*second);
			glVertex3f(i*first, 0, k*forth);

			glVertex3f(i*first, 0, k*forth);
			glVertex3f(0, 0, k*forth);

			glVertex3f(i*first, 0, k*forth);
			glVertex3f(i*forth, 0, k*first);

			glVertex3f(i*forth, 0, k*first);
			glVertex3f(i*second, j*third, k*first);

			glVertex3f(i*second, j*third, k*first);
			glVertex3f(i*first, j*third, k*second);

			glVertex3f(i*forth, 0, k*first);
			glVertex3f(i*forth, 0, 0);

			glVertex3f(i*first, j*third, k*second);
			glVertex3f(0, j*third, k*second);

			glVertex3f(i*second, j*third, k*first);
			glVertex3f(i*second, j*third, 0);
			S1v = S1vb;
			S2v = S2vb;
		}
		else
		{
			if (2 * S2v < S3v)
			{
				S3v = S2v*2;

			}
			if (S2v < S1v)
			{
				S1v = S2v;
			}

			i = 1;
			j = 1;
			k = 1;
	


			glVertex3f(i*first, j*fifth, k*first);
			glVertex3f(i*first, 0, k*forth);

			glVertex3f(i*first, 0, k*forth);
			glVertex3f(0, 0, k*forth);


			glVertex3f(i*first, j*fifth, k*first);
			glVertex3f(i*forth, 0, k*first);

			glVertex3f(i*forth, 0, k*first);
			glVertex3f(i*forth, 0, 0);

			glVertex3f(i*forth, 0, k*first);
			glVertex3f(i*first, 0, k*forth);

			glVertex3f(i*first, j*fifth, k*first);
			glVertex3f(i*second, j*third, k*second);

			glVertex3f(i*second, j*third, k*second);
			glVertex3f(0, j*third, k*second);

			glVertex3f(i*second, j*third, k*second);
			glVertex3f(i*second, j*third, 0);

			i = -1;
			j = 1;
			k = 1;

			glVertex3f(i*first, j*fifth, k*first);
			glVertex3f(i*first, 0, k*forth);

			glVertex3f(i*first, 0, k*forth);
			glVertex3f(0, 0, k*forth);


			glVertex3f(i*first, j*fifth, k*first);
			glVertex3f(i*forth, 0, k*first);

			glVertex3f(i*forth, 0, k*first);
			glVertex3f(i*forth, 0, 0);

			glVertex3f(i*forth, 0, k*first);
			glVertex3f(i*first, 0, k*forth);

			glVertex3f(i*first, j*fifth, k*first);
			glVertex3f(i*second, j*third, k*second);

			glVertex3f(i*second, j*third, k*second);
			glVertex3f(0, j*third, k*second);

			glVertex3f(i*second, j*third, k*second);
			glVertex3f(i*second, j*third, 0);
			i = 1;
			j = -1;
			k = 1;

			glVertex3f(i*first, j*fifth, k*first);
			glVertex3f(i*first, 0, k*forth);

			glVertex3f(i*first, 0, k*forth);
			glVertex3f(0, 0, k*forth);


			glVertex3f(i*first, j*fifth, k*first);
			glVertex3f(i*forth, 0, k*first);

			glVertex3f(i*forth, 0, k*first);
			glVertex3f(i*forth, 0, 0);

			glVertex3f(i*forth, 0, k*first);
			glVertex3f(i*first, 0, k*forth);

			glVertex3f(i*first, j*fifth, k*first);
			glVertex3f(i*second, j*third, k*second);

			glVertex3f(i*second, j*third, k*second);
			glVertex3f(0, j*third, k*second);

			glVertex3f(i*second, j*third, k*second);
			glVertex3f(i*second, j*third, 0);
			i = 1;
			j = 1;
			k = -1;

			glVertex3f(i*first, j*fifth, k*first);
			glVertex3f(i*first, 0, k*forth);

			glVertex3f(i*first, 0, k*forth);
			glVertex3f(0, 0, k*forth);


			glVertex3f(i*first, j*fifth, k*first);
			glVertex3f(i*forth, 0, k*first);

			glVertex3f(i*forth, 0, k*first);
			glVertex3f(i*forth, 0, 0);

			glVertex3f(i*forth, 0, k*first);
			glVertex3f(i*first, 0, k*forth);

			glVertex3f(i*first, j*fifth, k*first);
			glVertex3f(i*second, j*third, k*second);

			glVertex3f(i*second, j*third, k*second);
			glVertex3f(0, j*third, k*second);

			glVertex3f(i*second, j*third, k*second);
			glVertex3f(i*second, j*third, 0);
			i = -1;
			j = -1;
			k = 1;

			glVertex3f(i*first, j*fifth, k*first);
			glVertex3f(i*first, 0, k*forth);

			glVertex3f(i*first, 0, k*forth);
			glVertex3f(0, 0, k*forth);


			glVertex3f(i*first, j*fifth, k*first);
			glVertex3f(i*forth, 0, k*first);

			glVertex3f(i*forth, 0, k*first);
			glVertex3f(i*forth, 0, 0);

			glVertex3f(i*forth, 0, k*first);
			glVertex3f(i*first, 0, k*forth);

			glVertex3f(i*first, j*fifth, k*first);
			glVertex3f(i*second, j*third, k*second);

			glVertex3f(i*second, j*third, k*second);
			glVertex3f(0, j*third, k*second);

			glVertex3f(i*second, j*third, k*second);
			glVertex3f(i*second, j*third, 0);
			i = -1;
			j = 1;
			k = -1;

			glVertex3f(i*first, j*fifth, k*first);
			glVertex3f(i*first, 0, k*forth);

			glVertex3f(i*first, 0, k*forth);
			glVertex3f(0, 0, k*forth);


			glVertex3f(i*first, j*fifth, k*first);
			glVertex3f(i*forth, 0, k*first);

			glVertex3f(i*forth, 0, k*first);
			glVertex3f(i*forth, 0, 0);

			glVertex3f(i*forth, 0, k*first);
			glVertex3f(i*first, 0, k*forth);

			glVertex3f(i*first, j*fifth, k*first);
			glVertex3f(i*second, j*third, k*second);

			glVertex3f(i*second, j*third, k*second);
			glVertex3f(0, j*third, k*second);

			glVertex3f(i*second, j*third, k*second);
			glVertex3f(i*second, j*third, 0);
			i = 1;
			j = -1;
			k = -1;

			glVertex3f(i*first, j*fifth, k*first);
			glVertex3f(i*first, 0, k*forth);

			glVertex3f(i*first, 0, k*forth);
			glVertex3f(0, 0, k*forth);


			glVertex3f(i*first, j*fifth, k*first);
			glVertex3f(i*forth, 0, k*first);

			glVertex3f(i*forth, 0, k*first);
			glVertex3f(i*forth, 0, 0);

			glVertex3f(i*forth, 0, k*first);
			glVertex3f(i*first, 0, k*forth);

			glVertex3f(i*first, j*fifth, k*first);
			glVertex3f(i*second, j*third, k*second);

			glVertex3f(i*second, j*third, k*second);
			glVertex3f(0, j*third, k*second);

			glVertex3f(i*second, j*third, k*second);
			glVertex3f(i*second, j*third, 0);
			i = -1;
			j =- 1;
			k = -1;

			glVertex3f(i*first, j*fifth, k*first);
			glVertex3f(i*first, 0, k*forth);

			glVertex3f(i*first, 0, k*forth);
			glVertex3f(0, 0, k*forth);


			glVertex3f(i*first, j*fifth, k*first);
			glVertex3f(i*forth, 0, k*first);

			glVertex3f(i*forth, 0, k*first);
			glVertex3f(i*forth, 0, 0);

			glVertex3f(i*forth, 0, k*first);
			glVertex3f(i*first, 0, k*forth);

			glVertex3f(i*first, j*fifth, k*first);
			glVertex3f(i*second, j*third, k*second);

			glVertex3f(i*second, j*third, k*second);
			glVertex3f(0, j*third, k*second);

			glVertex3f(i*second, j*third, k*second);
			glVertex3f(i*second, j*third, 0);

			S1v = S1vb;
			S2v = S2vb;
			S3v = S3vb;

		}

		
	}
	else if (Rod_like == -1)
	{
		int S1vb = S1v;
		int S2vb = S2v;

		if (S3v < S2v)
		{
			S2v = S3v;
		}
		if (S2v < S1v)
		{
			S1v = S2v;
		}
		if (2 * S1v < S2v)
		{
			S2v = 2 * S1v;

		}
		

		i = 1;
		j = 1;
		k = 1;

		glVertex3f(i*second, j*first, k*third);
		glVertex3f(i*second, 0, k*third);

		glVertex3f(i*second, j*first, k*third);
		glVertex3f(0, j*sixth, k*third);

		glVertex3f(0, j*sixth, k*third);
		glVertex3f(0, j*eighth, 0);

		glVertex3f(i*third, j*first, k*second);
		glVertex3f(i*second, j*first, k*third);

		glVertex3f(i*third, j*first, k*second);
		glVertex3f(i*third, 0, k*second);

		glVertex3f(i*third, j*first, k*second);
		glVertex3f(i*third, j*sixth, 0);

		glVertex3f(i*third, j*sixth, 0);
		glVertex3f(0, j*eighth, 0);



		i = -1;
		j = 1;
		k = 1;
		glVertex3f(i*second, j*first, k*third);
		glVertex3f(i*second, 0, k*third);

		glVertex3f(i*second, j*first, k*third);
		glVertex3f(0, j*sixth, k*third);

		glVertex3f(0, j*sixth, k*third);
		glVertex3f(0, j*eighth, 0);

		glVertex3f(i*third, j*first, k*second);
		glVertex3f(i*second, j*first, k*third);

		glVertex3f(i*third, j*first, k*second);
		glVertex3f(i*third, 0, k*second);

		glVertex3f(i*third, j*first, k*second);
		glVertex3f(i*third, j*sixth, 0);

		glVertex3f(i*third, j*sixth, 0);
		glVertex3f(0, j*eighth, 0);

		i = 1;
		j = -1;
		k = 1;
		glVertex3f(i*second, j*first, k*third);
		glVertex3f(i*second, 0, k*third);

		glVertex3f(i*second, j*first, k*third);
		glVertex3f(0, j*sixth, k*third);

		glVertex3f(0, j*sixth, k*third);
		glVertex3f(0, j*eighth, 0);

		glVertex3f(i*third, j*first, k*second);
		glVertex3f(i*second, j*first, k*third);

		glVertex3f(i*third, j*first, k*second);
		glVertex3f(i*third, 0, k*second);

		glVertex3f(i*third, j*first, k*second);
		glVertex3f(i*third, j*sixth, 0);

		glVertex3f(i*third, j*sixth, 0);
		glVertex3f(0, j*eighth, 0);
		i = 1;
		j = 1;
		k = -1;
		glVertex3f(i*second, j*first, k*third);
		glVertex3f(i*second, 0, k*third);

		glVertex3f(i*second, j*first, k*third);
		glVertex3f(0, j*sixth, k*third);

		glVertex3f(0, j*sixth, k*third);
		glVertex3f(0, j*eighth, 0);

		glVertex3f(i*third, j*first, k*second);
		glVertex3f(i*second, j*first, k*third);

		glVertex3f(i*third, j*first, k*second);
		glVertex3f(i*third, 0, k*second);

		glVertex3f(i*third, j*first, k*second);
		glVertex3f(i*third, j*sixth, 0);

		glVertex3f(i*third, j*sixth, 0);
		glVertex3f(0, j*eighth, 0);
		i = -1;
		j = -1;
		k = 1;
		glVertex3f(i*second, j*first, k*third);
		glVertex3f(i*second, 0, k*third);

		glVertex3f(i*second, j*first, k*third);
		glVertex3f(0, j*sixth, k*third);

		glVertex3f(0, j*sixth, k*third);
		glVertex3f(0, j*eighth, 0);

		glVertex3f(i*third, j*first, k*second);
		glVertex3f(i*second, j*first, k*third);

		glVertex3f(i*third, j*first, k*second);
		glVertex3f(i*third, 0, k*second);

		glVertex3f(i*third, j*first, k*second);
		glVertex3f(i*third, j*sixth, 0);

		glVertex3f(i*third, j*sixth, 0);
		glVertex3f(0, j*eighth, 0);
		i = -1;
		j = 1;
		k = -1;
		glVertex3f(i*second, j*first, k*third);
		glVertex3f(i*second, 0, k*third);

		glVertex3f(i*second, j*first, k*third);
		glVertex3f(0, j*sixth, k*third);

		glVertex3f(0, j*sixth, k*third);
		glVertex3f(0, j*eighth, 0);

		glVertex3f(i*third, j*first, k*second);
		glVertex3f(i*second, j*first, k*third);

		glVertex3f(i*third, j*first, k*second);
		glVertex3f(i*third, 0, k*second);

		glVertex3f(i*third, j*first, k*second);
		glVertex3f(i*third, j*sixth, 0);

		glVertex3f(i*third, j*sixth, 0);
		glVertex3f(0, j*eighth, 0);
		i = 1;
		j = -1;
		k = -1;
		glVertex3f(i*second, j*first, k*third);
		glVertex3f(i*second, 0, k*third);

		glVertex3f(i*second, j*first, k*third);
		glVertex3f(0, j*sixth, k*third);

		glVertex3f(0, j*sixth, k*third);
		glVertex3f(0, j*eighth, 0);

		glVertex3f(i*third, j*first, k*second);
		glVertex3f(i*second, j*first, k*third);

		glVertex3f(i*third, j*first, k*second);
		glVertex3f(i*third, 0, k*second);

		glVertex3f(i*third, j*first, k*second);
		glVertex3f(i*third, j*sixth, 0);

		glVertex3f(i*third, j*sixth, 0);
		glVertex3f(0, j*eighth, 0);
		i = -1;
		j = -1;
		k = -1;
		glVertex3f(i*second, j*first, k*third);
		glVertex3f(i*second, 0, k*third);

		glVertex3f(i*second, j*first, k*third);
		glVertex3f(0, j*sixth, k*third);

		glVertex3f(0, j*sixth, k*third);
		glVertex3f(0, j*eighth, 0);

		glVertex3f(i*third, j*first, k*second);
		glVertex3f(i*second, j*first, k*third);

		glVertex3f(i*third, j*first, k*second);
		glVertex3f(i*third, 0, k*second);

		glVertex3f(i*third, j*first, k*second);
		glVertex3f(i*third, j*sixth, 0);

		glVertex3f(i*third, j*sixth, 0);
		glVertex3f(0, j*eighth, 0);

		S1v = S1vb;
		S2v = S2vb;
		
	}
	else if (Right_Hexagonal == -1)
	{
		int S1vb = S1v;
		int S2vb = S2v;

		float asdf = (Right_Hexagonal_height + 0.5) / (Svmax + 5);


		if (float(S1v) / float(S2v) > 1.14814814815)
		{
			for (i = -1; i < 2; i = i + 2)
			{
				for (j = -1; j < 2; j = j + 2)
				{


					for (k = -1; k < 2; k = k + 2)
					{
						glVertex3f(i*float(S2v*0.866025404) / (Svmax + 5), j*asdf, k*0.88*float(S2v / 0.866025404 - 2 * S2v *0.866025404) / ( (Svmax + 5)));
						glVertex3f(i*float(S2v *0.866025404) / (Svmax + 5), j*asdf, 0);

						glVertex3f(i*float(S2v *0.866025404) / (Svmax + 5), j*asdf, k*0.88*float(S2v / 0.866025404 - 2 * S2v *0.866025404) / ( (Svmax + 5)));
						glVertex3f(i*float(S2v *0.866025404) / (Svmax + 5), 0, k*0.88*float(S2v / 0.866025404 - 2 * S2v *0.866025404) / ((Svmax + 5)));


						glVertex3f(0, j*asdf, k*float(S2v) / ((Svmax + 5)));
						glVertex3f(i*float(S2v *0.866025404) / (Svmax + 5), j*asdf, -k*0.88*float(S2v / 0.866025404 - 2 * S2v *0.866025404) / ((Svmax + 5)));

						glVertex3f(0, j*asdf, k*float(S2v) / ( (Svmax + 5)));
						glVertex3f(0, 0, k*float(S2v) / ( (Svmax + 5)));
					}
				}
			}

		}
		else if (float(S1v) / float(S2v) < 0.86842105263)
		{
			for (i = -1; i < 2; i = i + 2)
			{
				for (j = -1; j < 2; j = j + 2)
				{
					for (k = -1; k < 2; k = k + 2)
					{
						glVertex3f(k*0.86*float(S1v/ 0.866025404 - 2*S1v *0.866025404) / ( (Svmax + 5)), j*asdf, i*float(S1v *0.866025404) / (Svmax + 5));
						glVertex3f(0, j*asdf, i*float(S1v *0.866025404) / (Svmax + 5));

						glVertex3f(k*0.86*float(S1v / 0.866025404 - 2 * S1v *0.866025404) / ((Svmax + 5)), j*asdf, i*float(S1v *0.866025404) / (Svmax + 5));
						glVertex3f(k*0.86*float(S1v / 0.866025404 - 2 * S1v *0.866025404) / ((Svmax + 5)), 0, i*float(S1v *0.866025404) / (Svmax + 5));


						glVertex3f(k*float(S1v) / ( (Svmax + 5)), j*asdf, 0);
						glVertex3f(-k*0.86*float(S1v / 0.866025404 - 2 * S1v *0.866025404) / ((Svmax + 5)), j*asdf, i*float(S1v *0.866025404) / (Svmax + 5));

						glVertex3f(k*float(S1v) / ((Svmax + 5)), j*asdf, 0);
						glVertex3f(k*float(S1v) / ((Svmax + 5)), 0, 0);
					}
				}
			}
		
		}
		else
		{
			for (i = -1; i < 2; i = i + 2)
			{
				for (j = -1; j < 2; j = j + 2)
				{


					for (k = -1; k < 2; k = k + 2)
					{
						glVertex3f(i*0.94*float(4 * S1v - 2 * S2v) / (3 * (Svmax + 5)), j*asdf, k*0.967*float((S2v)-(2 * S1v - S2v) / 3.0) / float((Svmax + 5)));
						glVertex3f(i*0.88*(float(2 * S2v - 2 * S1v *0.866025404)) / (Svmax + 5), j*asdf, k*(float(S1v) *0.866025404) / (Svmax + 5));


						glVertex3f(i*0.94*float(4 * S1v - 2 * S2v) / (3 * (Svmax + 5)), j*asdf, k*0.967*float((S2v)-(2 * S1v - S2v) / 3.0) / float((Svmax + 5)));
						glVertex3f(i*(float(S2v) *0.866025404) / (Svmax + 5), j*asdf, k*0.88*float(2 * S1v - 2 * (S2v)*0.866025404) / (Svmax + 5));

						glVertex3f(i*0.94*float(4 * S1v - 2 * S2v) / (3 * (Svmax + 5)), j*asdf, k*0.967*float((S2v)-(2 * S1v - S2v) / 3.0) / float((Svmax + 5)));
						glVertex3f(i*0.94*float(4 * S1v - 2 * S2v) / (3 * (Svmax + 5)), 0, k*0.967*float((S2v)-(2 * S1v - S2v) / 3.0) / float((Svmax + 5)));


						glVertex3f(i*float(S2v *0.866025404) / (Svmax + 5), j*asdf, 0);
						glVertex3f(i*(float(S2v) *0.866025404) / (Svmax + 5), j*asdf, k*0.88*float(2*S1v - 2 * (S2v)*0.866025404) / (Svmax + 5));



						
						glVertex3f(i*(float(S2v) *0.866025404) / (Svmax + 5), j*asdf, k*0.88*float(2*S1v - 2 * (S2v)*0.866025404) / (Svmax + 5));
						glVertex3f(i*(float(S2v) *0.866025404) / (Svmax + 5), 0, k*0.88*float(2*S1v - 2 * (S2v)*0.866025404) / (Svmax + 5));


						glVertex3f(i*0.88*(float(2*S2v - 2 * S1v *0.866025404)) / (Svmax + 5), j*asdf, k*(float(S1v) *0.866025404) / (Svmax + 5));
						glVertex3f(0, j*asdf, k*(float(S1v) *0.866025404) / (Svmax + 5));


						glVertex3f(i*0.88*(float(2*S2v - 2 * S1v *0.866025404)) / (Svmax + 5), j*asdf, k*(float(S1v) *0.866025404) / (Svmax + 5));
						glVertex3f(i*0.88*(float(2*S2v - 2 * S1v *0.866025404)) / (Svmax + 5), 0, k*(float(S1v) *0.866025404) / (Svmax + 5));

					}
				}
			}

		}



		S1v = S1vb;
		S2v = S2vb;

	}
	else if (Scase == 1)
	{


		if (2 * S2v - S3v >= S1v)
		{



			i = 1;
			j = 1;
			k = 1;


			glVertex3f(i*first, j*second, k*third);
			glVertex3f(i*second, j*first, k*third);


			glVertex3f(i*first, j*second, k*third);
			glVertex3f(0, j*second, k*third);

			glVertex3f(i*second, j*first, k*third);
			glVertex3f(i*second, 0, k*third);

			glVertex3f(i*first, j*second, k*third);
			glVertex3f(i*first, j*third, k*second);


			glVertex3f(i*second, j*third, k*first);
			glVertex3f(i*first, j*third, k*second);

			glVertex3f(i*second, j*third, k*first);
			glVertex3f(i*second, j*third, 0);


			glVertex3f(i*first, j*third, k*second);
			glVertex3f(0, j*third, k*second);

			glVertex3f(i*third, j*first, k*second);
			glVertex3f(i*second, j*first, k*third);

			glVertex3f(i*third, j*first, k*second);
			glVertex3f(i*third, 0, k*second);

			glVertex3f(i*third, j*first, k*second);
			glVertex3f(i*third, j*second, k*first);

			glVertex3f(i*third, j*second, k*first);
			glVertex3f(i*third, j*second, 0);

			glVertex3f(i*third, j*second, k*first);
			glVertex3f(i*second, j*third, k*first);


			i = -1;
			j = 1;
			k = 1;
			glVertex3f(i*first, j*second, k*third);
			glVertex3f(i*second, j*first, k*third);


			glVertex3f(i*first, j*second, k*third);
			glVertex3f(0, j*second, k*third);

			glVertex3f(i*second, j*first, k*third);
			glVertex3f(i*second, 0, k*third);

			glVertex3f(i*first, j*second, k*third);
			glVertex3f(i*first, j*third, k*second);


			glVertex3f(i*second, j*third, k*first);
			glVertex3f(i*first, j*third, k*second);

			glVertex3f(i*second, j*third, k*first);
			glVertex3f(i*second, j*third, 0);


			glVertex3f(i*first, j*third, k*second);
			glVertex3f(0, j*third, k*second);

			glVertex3f(i*third, j*first, k*second);
			glVertex3f(i*second, j*first, k*third);

			glVertex3f(i*third, j*first, k*second);
			glVertex3f(i*third, 0, k*second);

			glVertex3f(i*third, j*first, k*second);
			glVertex3f(i*third, j*second, k*first);

			glVertex3f(i*third, j*second, k*first);
			glVertex3f(i*third, j*second, 0);

			glVertex3f(i*third, j*second, k*first);
			glVertex3f(i*second, j*third, k*first);

			i = 1;
			j = -1;
			k = 1;
			glVertex3f(i*first, j*second, k*third);
			glVertex3f(i*second, j*first, k*third);


			glVertex3f(i*first, j*second, k*third);
			glVertex3f(0, j*second, k*third);

			glVertex3f(i*second, j*first, k*third);
			glVertex3f(i*second, 0, k*third);

			glVertex3f(i*first, j*second, k*third);
			glVertex3f(i*first, j*third, k*second);


			glVertex3f(i*second, j*third, k*first);
			glVertex3f(i*first, j*third, k*second);

			glVertex3f(i*second, j*third, k*first);
			glVertex3f(i*second, j*third, 0);


			glVertex3f(i*first, j*third, k*second);
			glVertex3f(0, j*third, k*second);

			glVertex3f(i*third, j*first, k*second);
			glVertex3f(i*second, j*first, k*third);

			glVertex3f(i*third, j*first, k*second);
			glVertex3f(i*third, 0, k*second);

			glVertex3f(i*third, j*first, k*second);
			glVertex3f(i*third, j*second, k*first);

			glVertex3f(i*third, j*second, k*first);
			glVertex3f(i*third, j*second, 0);

			glVertex3f(i*third, j*second, k*first);
			glVertex3f(i*second, j*third, k*first);
			i = 1;
			j = 1;
			k = -1;
			glVertex3f(i*first, j*second, k*third);
			glVertex3f(i*second, j*first, k*third);


			glVertex3f(i*first, j*second, k*third);
			glVertex3f(0, j*second, k*third);

			glVertex3f(i*second, j*first, k*third);
			glVertex3f(i*second, 0, k*third);

			glVertex3f(i*first, j*second, k*third);
			glVertex3f(i*first, j*third, k*second);


			glVertex3f(i*second, j*third, k*first);
			glVertex3f(i*first, j*third, k*second);

			glVertex3f(i*second, j*third, k*first);
			glVertex3f(i*second, j*third, 0);


			glVertex3f(i*first, j*third, k*second);
			glVertex3f(0, j*third, k*second);

			glVertex3f(i*third, j*first, k*second);
			glVertex3f(i*second, j*first, k*third);

			glVertex3f(i*third, j*first, k*second);
			glVertex3f(i*third, 0, k*second);

			glVertex3f(i*third, j*first, k*second);
			glVertex3f(i*third, j*second, k*first);

			glVertex3f(i*third, j*second, k*first);
			glVertex3f(i*third, j*second, 0);

			glVertex3f(i*third, j*second, k*first);
			glVertex3f(i*second, j*third, k*first);
			i = -1;
			j = -1;
			k = 1;
			glVertex3f(i*first, j*second, k*third);
			glVertex3f(i*second, j*first, k*third);


			glVertex3f(i*first, j*second, k*third);
			glVertex3f(0, j*second, k*third);

			glVertex3f(i*second, j*first, k*third);
			glVertex3f(i*second, 0, k*third);

			glVertex3f(i*first, j*second, k*third);
			glVertex3f(i*first, j*third, k*second);


			glVertex3f(i*second, j*third, k*first);
			glVertex3f(i*first, j*third, k*second);

			glVertex3f(i*second, j*third, k*first);
			glVertex3f(i*second, j*third, 0);


			glVertex3f(i*first, j*third, k*second);
			glVertex3f(0, j*third, k*second);

			glVertex3f(i*third, j*first, k*second);
			glVertex3f(i*second, j*first, k*third);

			glVertex3f(i*third, j*first, k*second);
			glVertex3f(i*third, 0, k*second);

			glVertex3f(i*third, j*first, k*second);
			glVertex3f(i*third, j*second, k*first);

			glVertex3f(i*third, j*second, k*first);
			glVertex3f(i*third, j*second, 0);

			glVertex3f(i*third, j*second, k*first);
			glVertex3f(i*second, j*third, k*first);
			i = -1;
			j = 1;
			k = -1;
			glVertex3f(i*first, j*second, k*third);
			glVertex3f(i*second, j*first, k*third);


			glVertex3f(i*first, j*second, k*third);
			glVertex3f(0, j*second, k*third);

			glVertex3f(i*second, j*first, k*third);
			glVertex3f(i*second, 0, k*third);

			glVertex3f(i*first, j*second, k*third);
			glVertex3f(i*first, j*third, k*second);


			glVertex3f(i*second, j*third, k*first);
			glVertex3f(i*first, j*third, k*second);

			glVertex3f(i*second, j*third, k*first);
			glVertex3f(i*second, j*third, 0);


			glVertex3f(i*first, j*third, k*second);
			glVertex3f(0, j*third, k*second);

			glVertex3f(i*third, j*first, k*second);
			glVertex3f(i*second, j*first, k*third);

			glVertex3f(i*third, j*first, k*second);
			glVertex3f(i*third, 0, k*second);

			glVertex3f(i*third, j*first, k*second);
			glVertex3f(i*third, j*second, k*first);

			glVertex3f(i*third, j*second, k*first);
			glVertex3f(i*third, j*second, 0);

			glVertex3f(i*third, j*second, k*first);
			glVertex3f(i*second, j*third, k*first);
			i = 1;
			j = -1;
			k = -1;
			glVertex3f(i*first, j*second, k*third);
			glVertex3f(i*second, j*first, k*third);


			glVertex3f(i*first, j*second, k*third);
			glVertex3f(0, j*second, k*third);

			glVertex3f(i*second, j*first, k*third);
			glVertex3f(i*second, 0, k*third);

			glVertex3f(i*first, j*second, k*third);
			glVertex3f(i*first, j*third, k*second);


			glVertex3f(i*second, j*third, k*first);
			glVertex3f(i*first, j*third, k*second);

			glVertex3f(i*second, j*third, k*first);
			glVertex3f(i*second, j*third, 0);


			glVertex3f(i*first, j*third, k*second);
			glVertex3f(0, j*third, k*second);

			glVertex3f(i*third, j*first, k*second);
			glVertex3f(i*second, j*first, k*third);

			glVertex3f(i*third, j*first, k*second);
			glVertex3f(i*third, 0, k*second);

			glVertex3f(i*third, j*first, k*second);
			glVertex3f(i*third, j*second, k*first);

			glVertex3f(i*third, j*second, k*first);
			glVertex3f(i*third, j*second, 0);

			glVertex3f(i*third, j*second, k*first);
			glVertex3f(i*second, j*third, k*first);
			i = -1;
			j = -1;
			k = -1;
			glVertex3f(i*first, j*second, k*third);
			glVertex3f(i*second, j*first, k*third);


			glVertex3f(i*first, j*second, k*third);
			glVertex3f(0, j*second, k*third);

			glVertex3f(i*second, j*first, k*third);
			glVertex3f(i*second, 0, k*third);

			glVertex3f(i*first, j*second, k*third);
			glVertex3f(i*first, j*third, k*second);


			glVertex3f(i*second, j*third, k*first);
			glVertex3f(i*first, j*third, k*second);

			glVertex3f(i*second, j*third, k*first);
			glVertex3f(i*second, j*third, 0);


			glVertex3f(i*first, j*third, k*second);
			glVertex3f(0, j*third, k*second);

			glVertex3f(i*third, j*first, k*second);
			glVertex3f(i*second, j*first, k*third);

			glVertex3f(i*third, j*first, k*second);
			glVertex3f(i*third, 0, k*second);

			glVertex3f(i*third, j*first, k*second);
			glVertex3f(i*third, j*second, k*first);

			glVertex3f(i*third, j*second, k*first);
			glVertex3f(i*third, j*second, 0);

			glVertex3f(i*third, j*second, k*first);
			glVertex3f(i*second, j*third, k*first);
		}

		else
		{
			i = 1;
			j = 1;
			k = 1;
			glVertex3f(i*third, j*second, k*second);
			glVertex3f(i*fifth, j*first, k*first);


			glVertex3f(i*second, j*third, k*second);
			glVertex3f(i*first, j*fifth, k*first);


			glVertex3f(i*second, j*second, k*third);
			glVertex3f(i*first, j*first, k*fifth);


			glVertex3f(i*third, j*second, k*second);
			glVertex3f(i*third, j*second, 0);

			glVertex3f(i*third, j*second, k*second);
			glVertex3f(i*third, 0, k*second);

			glVertex3f(i*second, j*third, k*second);
			glVertex3f(0, j*third, k*second);

			glVertex3f(i*second, j*third, k*second);
			glVertex3f(i*second, j*third, 0);

			glVertex3f(i*second, j*second, k*third);
			glVertex3f(0, j*second, k*third);

			glVertex3f(i*second, j*second, k*third);
			glVertex3f(i*second, 0, k*third);

			glVertex3f(i*first, j*first, k*fifth);
			glVertex3f(i*first, j*fifth, k*first);

			glVertex3f(i*first, j*first, k*fifth);
			glVertex3f(i*fifth, j*first, k*first);

			glVertex3f(i*fifth, j*first, k*first);
			glVertex3f(i*first, j*fifth, k*first);


			i = -1;
			j = 1;
			k = 1;
			glVertex3f(i*third, j*second, k*second);
			glVertex3f(i*fifth, j*first, k*first);


			glVertex3f(i*second, j*third, k*second);
			glVertex3f(i*first, j*fifth, k*first);


			glVertex3f(i*second, j*second, k*third);
			glVertex3f(i*first, j*first, k*fifth);


			glVertex3f(i*third, j*second, k*second);
			glVertex3f(i*third, j*second, 0);

			glVertex3f(i*third, j*second, k*second);
			glVertex3f(i*third, 0, k*second);

			glVertex3f(i*second, j*third, k*second);
			glVertex3f(0, j*third, k*second);

			glVertex3f(i*second, j*third, k*second);
			glVertex3f(i*second, j*third, 0);

			glVertex3f(i*second, j*second, k*third);
			glVertex3f(0, j*second, k*third);

			glVertex3f(i*second, j*second, k*third);
			glVertex3f(i*second, 0, k*third);

			glVertex3f(i*first, j*first, k*fifth);
			glVertex3f(i*first, j*fifth, k*first);

			glVertex3f(i*first, j*first, k*fifth);
			glVertex3f(i*fifth, j*first, k*first);

			glVertex3f(i*fifth, j*first, k*first);
			glVertex3f(i*first, j*fifth, k*first);
			i = 1;
			j = -1;
			k = 1;
			glVertex3f(i*third, j*second, k*second);
			glVertex3f(i*fifth, j*first, k*first);


			glVertex3f(i*second, j*third, k*second);
			glVertex3f(i*first, j*fifth, k*first);


			glVertex3f(i*second, j*second, k*third);
			glVertex3f(i*first, j*first, k*fifth);


			glVertex3f(i*third, j*second, k*second);
			glVertex3f(i*third, j*second, 0);

			glVertex3f(i*third, j*second, k*second);
			glVertex3f(i*third, 0, k*second);

			glVertex3f(i*second, j*third, k*second);
			glVertex3f(0, j*third, k*second);

			glVertex3f(i*second, j*third, k*second);
			glVertex3f(i*second, j*third, 0);

			glVertex3f(i*second, j*second, k*third);
			glVertex3f(0, j*second, k*third);

			glVertex3f(i*second, j*second, k*third);
			glVertex3f(i*second, 0, k*third);

			glVertex3f(i*first, j*first, k*fifth);
			glVertex3f(i*first, j*fifth, k*first);

			glVertex3f(i*first, j*first, k*fifth);
			glVertex3f(i*fifth, j*first, k*first);

			glVertex3f(i*fifth, j*first, k*first);
			glVertex3f(i*first, j*fifth, k*first);
			i = 1;
			j = 1;
			k = -1;
			glVertex3f(i*third, j*second, k*second);
			glVertex3f(i*fifth, j*first, k*first);


			glVertex3f(i*second, j*third, k*second);
			glVertex3f(i*first, j*fifth, k*first);


			glVertex3f(i*second, j*second, k*third);
			glVertex3f(i*first, j*first, k*fifth);


			glVertex3f(i*third, j*second, k*second);
			glVertex3f(i*third, j*second, 0);

			glVertex3f(i*third, j*second, k*second);
			glVertex3f(i*third, 0, k*second);

			glVertex3f(i*second, j*third, k*second);
			glVertex3f(0, j*third, k*second);

			glVertex3f(i*second, j*third, k*second);
			glVertex3f(i*second, j*third, 0);

			glVertex3f(i*second, j*second, k*third);
			glVertex3f(0, j*second, k*third);

			glVertex3f(i*second, j*second, k*third);
			glVertex3f(i*second, 0, k*third);

			glVertex3f(i*first, j*first, k*fifth);
			glVertex3f(i*first, j*fifth, k*first);

			glVertex3f(i*first, j*first, k*fifth);
			glVertex3f(i*fifth, j*first, k*first);

			glVertex3f(i*fifth, j*first, k*first);
			glVertex3f(i*first, j*fifth, k*first);
			i = -1;
			j = -1;
			k = 1;
			glVertex3f(i*third, j*second, k*second);
			glVertex3f(i*fifth, j*first, k*first);


			glVertex3f(i*second, j*third, k*second);
			glVertex3f(i*first, j*fifth, k*first);


			glVertex3f(i*second, j*second, k*third);
			glVertex3f(i*first, j*first, k*fifth);


			glVertex3f(i*third, j*second, k*second);
			glVertex3f(i*third, j*second, 0);

			glVertex3f(i*third, j*second, k*second);
			glVertex3f(i*third, 0, k*second);

			glVertex3f(i*second, j*third, k*second);
			glVertex3f(0, j*third, k*second);

			glVertex3f(i*second, j*third, k*second);
			glVertex3f(i*second, j*third, 0);

			glVertex3f(i*second, j*second, k*third);
			glVertex3f(0, j*second, k*third);

			glVertex3f(i*second, j*second, k*third);
			glVertex3f(i*second, 0, k*third);

			glVertex3f(i*first, j*first, k*fifth);
			glVertex3f(i*first, j*fifth, k*first);

			glVertex3f(i*first, j*first, k*fifth);
			glVertex3f(i*fifth, j*first, k*first);

			glVertex3f(i*fifth, j*first, k*first);
			glVertex3f(i*first, j*fifth, k*first);
			i = -1;
			j = 1;
			k = -1;
			glVertex3f(i*third, j*second, k*second);
			glVertex3f(i*fifth, j*first, k*first);


			glVertex3f(i*second, j*third, k*second);
			glVertex3f(i*first, j*fifth, k*first);


			glVertex3f(i*second, j*second, k*third);
			glVertex3f(i*first, j*first, k*fifth);


			glVertex3f(i*third, j*second, k*second);
			glVertex3f(i*third, j*second, 0);

			glVertex3f(i*third, j*second, k*second);
			glVertex3f(i*third, 0, k*second);

			glVertex3f(i*second, j*third, k*second);
			glVertex3f(0, j*third, k*second);

			glVertex3f(i*second, j*third, k*second);
			glVertex3f(i*second, j*third, 0);

			glVertex3f(i*second, j*second, k*third);
			glVertex3f(0, j*second, k*third);

			glVertex3f(i*second, j*second, k*third);
			glVertex3f(i*second, 0, k*third);

			glVertex3f(i*first, j*first, k*fifth);
			glVertex3f(i*first, j*fifth, k*first);

			glVertex3f(i*first, j*first, k*fifth);
			glVertex3f(i*fifth, j*first, k*first);

			glVertex3f(i*fifth, j*first, k*first);
			glVertex3f(i*first, j*fifth, k*first);
			i = 1;
			j = -1;
			k = -1;
			glVertex3f(i*third, j*second, k*second);
			glVertex3f(i*fifth, j*first, k*first);


			glVertex3f(i*second, j*third, k*second);
			glVertex3f(i*first, j*fifth, k*first);


			glVertex3f(i*second, j*second, k*third);
			glVertex3f(i*first, j*first, k*fifth);


			glVertex3f(i*third, j*second, k*second);
			glVertex3f(i*third, j*second, 0);

			glVertex3f(i*third, j*second, k*second);
			glVertex3f(i*third, 0, k*second);

			glVertex3f(i*second, j*third, k*second);
			glVertex3f(0, j*third, k*second);

			glVertex3f(i*second, j*third, k*second);
			glVertex3f(i*second, j*third, 0);

			glVertex3f(i*second, j*second, k*third);
			glVertex3f(0, j*second, k*third);

			glVertex3f(i*second, j*second, k*third);
			glVertex3f(i*second, 0, k*third);

			glVertex3f(i*first, j*first, k*fifth);
			glVertex3f(i*first, j*fifth, k*first);

			glVertex3f(i*first, j*first, k*fifth);
			glVertex3f(i*fifth, j*first, k*first);

			glVertex3f(i*fifth, j*first, k*first);
			glVertex3f(i*first, j*fifth, k*first);
			i = -1;
			j = -1;
			k = -1;
			glVertex3f(i*third, j*second, k*second);
			glVertex3f(i*fifth, j*first, k*first);


			glVertex3f(i*second, j*third, k*second);
			glVertex3f(i*first, j*fifth, k*first);


			glVertex3f(i*second, j*second, k*third);
			glVertex3f(i*first, j*first, k*fifth);


			glVertex3f(i*third, j*second, k*second);
			glVertex3f(i*third, j*second, 0);

			glVertex3f(i*third, j*second, k*second);
			glVertex3f(i*third, 0, k*second);

			glVertex3f(i*second, j*third, k*second);
			glVertex3f(0, j*third, k*second);

			glVertex3f(i*second, j*third, k*second);
			glVertex3f(i*second, j*third, 0);

			glVertex3f(i*second, j*second, k*third);
			glVertex3f(0, j*second, k*third);

			glVertex3f(i*second, j*second, k*third);
			glVertex3f(i*second, 0, k*third);

			glVertex3f(i*first, j*first, k*fifth);
			glVertex3f(i*first, j*fifth, k*first);

			glVertex3f(i*first, j*first, k*fifth);
			glVertex3f(i*fifth, j*first, k*first);

			glVertex3f(i*fifth, j*first, k*first);
			glVertex3f(i*first, j*fifth, k*first);

		}

	}
	else if (Scase == 2)
	{
		i = 1;
		j = 1;
		k = 1;
		glVertex3f(i*third, j*second, k*second);
		glVertex3f(i*seventh, j*forth / 2, k*forth / 2);

		glVertex3f(i*second, j*third, k*second);
		glVertex3f(i*seventh, j*seventh, k*seventh);

		glVertex3f(i*second, j*second, k*third);
		glVertex3f(i*seventh, j*seventh, k*seventh);

		glVertex3f(i*third, j*second, k*second);
		glVertex3f(i*third, j*second, 0);

		glVertex3f(i*third, j*second, k*second);
		glVertex3f(i*third, 0, k*second);

		glVertex3f(i*second, j*third, k*second);
		glVertex3f(0, j*third, k*second);

		glVertex3f(i*second, j*third, k*second);
		glVertex3f(i*second, j*third, 0);

		glVertex3f(i*second, j*second, k*third);
		glVertex3f(0, j*second, k*third);

		glVertex3f(i*second, j*second, k*third);
		glVertex3f(i*second, 0, k*third);
		i = -1;
		j = 1;
		k = 1;
		glVertex3f(i*third, j*second, k*second);
		glVertex3f(i*seventh, j*forth / 2, k*forth / 2);

		glVertex3f(i*second, j*third, k*second);
		glVertex3f(i*seventh, j*seventh, k*seventh);

		glVertex3f(i*second, j*second, k*third);
		glVertex3f(i*seventh, j*seventh, k*seventh);

		glVertex3f(i*third, j*second, k*second);
		glVertex3f(i*third, j*second, 0);

		glVertex3f(i*third, j*second, k*second);
		glVertex3f(i*third, j*second, 0);

		glVertex3f(i*third, j*second, k*second);
		glVertex3f(i*third, 0, k*second);

		glVertex3f(i*second, j*third, k*second);
		glVertex3f(0, j*third, k*second);

		glVertex3f(i*second, j*third, k*second);
		glVertex3f(i*second, j*third, 0);

		glVertex3f(i*second, j*second, k*third);
		glVertex3f(0, j*second, k*third);

		glVertex3f(i*second, j*second, k*third);
		glVertex3f(i*second, 0, k*third);
		i = 1;
		j = -1;
		k = 1;
		glVertex3f(i*third, j*second, k*second);
		glVertex3f(i*seventh, j*forth / 2, k*forth / 2);

		glVertex3f(i*second, j*third, k*second);
		glVertex3f(i*seventh, j*seventh, k*seventh);

		glVertex3f(i*second, j*second, k*third);
		glVertex3f(i*seventh, j*seventh, k*seventh);

		glVertex3f(i*third, j*second, k*second);
		glVertex3f(i*third, j*second, 0);

		glVertex3f(i*third, j*second, k*second);
		glVertex3f(i*third, j*second, 0);

		glVertex3f(i*third, j*second, k*second);
		glVertex3f(i*third, 0, k*second);

		glVertex3f(i*second, j*third, k*second);
		glVertex3f(0, j*third, k*second);

		glVertex3f(i*second, j*third, k*second);
		glVertex3f(i*second, j*third, 0);

		glVertex3f(i*second, j*second, k*third);
		glVertex3f(0, j*second, k*third);

		glVertex3f(i*second, j*second, k*third);
		glVertex3f(i*second, 0, k*third);
		i = 1;
		j = 1;
		k = -1;
		glVertex3f(i*third, j*second, k*second);
		glVertex3f(i*seventh, j*forth / 2, k*forth / 2);

		glVertex3f(i*second, j*third, k*second);
		glVertex3f(i*seventh, j*seventh, k*seventh);

		glVertex3f(i*second, j*second, k*third);
		glVertex3f(i*seventh, j*seventh, k*seventh);

		glVertex3f(i*third, j*second, k*second);
		glVertex3f(i*third, j*second, 0);

		glVertex3f(i*third, j*second, k*second);
		glVertex3f(i*third, j*second, 0);

		glVertex3f(i*third, j*second, k*second);
		glVertex3f(i*third, 0, k*second);

		glVertex3f(i*second, j*third, k*second);
		glVertex3f(0, j*third, k*second);

		glVertex3f(i*second, j*third, k*second);
		glVertex3f(i*second, j*third, 0);

		glVertex3f(i*second, j*second, k*third);
		glVertex3f(0, j*second, k*third);

		glVertex3f(i*second, j*second, k*third);
		glVertex3f(i*second, 0, k*third);
		i = -1;
		j = -1;
		k = 1;
		glVertex3f(i*third, j*second, k*second);
		glVertex3f(i*seventh, j*forth / 2, k*forth / 2);

		glVertex3f(i*second, j*third, k*second);
		glVertex3f(i*seventh, j*seventh, k*seventh);

		glVertex3f(i*second, j*second, k*third);
		glVertex3f(i*seventh, j*seventh, k*seventh);

		glVertex3f(i*third, j*second, k*second);
		glVertex3f(i*third, j*second, 0);

		glVertex3f(i*third, j*second, k*second);
		glVertex3f(i*third, j*second, 0);

		glVertex3f(i*third, j*second, k*second);
		glVertex3f(i*third, 0, k*second);

		glVertex3f(i*second, j*third, k*second);
		glVertex3f(0, j*third, k*second);

		glVertex3f(i*second, j*third, k*second);
		glVertex3f(i*second, j*third, 0);

		glVertex3f(i*second, j*second, k*third);
		glVertex3f(0, j*second, k*third);

		glVertex3f(i*second, j*second, k*third);
		glVertex3f(i*second, 0, k*third);
		i = -1;
		j = 1;
		k = -1;
		glVertex3f(i*third, j*second, k*second);
		glVertex3f(i*seventh, j*forth / 2, k*forth / 2);

		glVertex3f(i*second, j*third, k*second);
		glVertex3f(i*seventh, j*seventh, k*seventh);

		glVertex3f(i*second, j*second, k*third);
		glVertex3f(i*seventh, j*seventh, k*seventh);

		glVertex3f(i*third, j*second, k*second);
		glVertex3f(i*third, j*second, 0);

		glVertex3f(i*third, j*second, k*second);
		glVertex3f(i*third, j*second, 0);

		glVertex3f(i*third, j*second, k*second);
		glVertex3f(i*third, 0, k*second);

		glVertex3f(i*second, j*third, k*second);
		glVertex3f(0, j*third, k*second);

		glVertex3f(i*second, j*third, k*second);
		glVertex3f(i*second, j*third, 0);

		glVertex3f(i*second, j*second, k*third);
		glVertex3f(0, j*second, k*third);

		glVertex3f(i*second, j*second, k*third);
		glVertex3f(i*second, 0, k*third);
		i = 1;
		j = -1;
		k = -1;
		glVertex3f(i*third, j*second, k*second);
		glVertex3f(i*seventh, j*forth / 2, k*forth / 2);

		glVertex3f(i*second, j*third, k*second);
		glVertex3f(i*seventh, j*seventh, k*seventh);

		glVertex3f(i*second, j*second, k*third);
		glVertex3f(i*seventh, j*seventh, k*seventh);

		glVertex3f(i*third, j*second, k*second);
		glVertex3f(i*third, j*second, 0);

		glVertex3f(i*third, j*second, k*second);
		glVertex3f(i*third, j*second, 0);

		glVertex3f(i*third, j*second, k*second);
		glVertex3f(i*third, 0, k*second);

		glVertex3f(i*second, j*third, k*second);
		glVertex3f(0, j*third, k*second);

		glVertex3f(i*second, j*third, k*second);
		glVertex3f(i*second, j*third, 0);

		glVertex3f(i*second, j*second, k*third);
		glVertex3f(0, j*second, k*third);

		glVertex3f(i*second, j*second, k*third);
		glVertex3f(i*second, 0, k*third);
		i = -1;
		j = -1;
		k = -1;
		glVertex3f(i*third, j*second, k*second);
		glVertex3f(i*seventh, j*forth / 2, k*forth / 2);

		glVertex3f(i*second, j*third, k*second);
		glVertex3f(i*seventh, j*seventh, k*seventh);

		glVertex3f(i*second, j*second, k*third);
		glVertex3f(i*seventh, j*seventh, k*seventh);

		glVertex3f(i*third, j*second, k*second);
		glVertex3f(i*third, j*second, 0);

		glVertex3f(i*third, j*second, k*second);
		glVertex3f(i*third, j*second, 0);

		glVertex3f(i*third, j*second, k*second);
		glVertex3f(i*third, 0, k*second);

		glVertex3f(i*second, j*third, k*second);
		glVertex3f(0, j*third, k*second);

		glVertex3f(i*second, j*third, k*second);
		glVertex3f(i*second, j*third, 0);

		glVertex3f(i*second, j*second, k*third);
		glVertex3f(0, j*second, k*third);

		glVertex3f(i*second, j*second, k*third);
		glVertex3f(i*second, 0, k*third);
	}
	else if (Scase == 3)
	{
		if (2 * S1v >= S3v)
		{
			i = 1;
			j = 1;
			k = 1;
			glVertex3f(i*third, j*sixth, 0);
			glVertex3f(i*third, 0, k*sixth);

			glVertex3f(i*third, j*sixth, 0);
			glVertex3f(i*sixth, j*third, 0);

			glVertex3f(0, j*third, k*sixth);
			glVertex3f(i*sixth, j*third, 0);

			glVertex3f(0, j*third, k*sixth);
			glVertex3f(0, j*sixth, k*third);

			glVertex3f(0, j*sixth, k*third);
			glVertex3f(i*sixth, 0, k*third);

			glVertex3f(i*sixth, 0, k*third);
			glVertex3f(i*third, 0, k*sixth);

			i = -1;
			j = 1;
			k = 1;
			glVertex3f(i*third, j*sixth, 0);
			glVertex3f(i*third, 0, k*sixth);

			glVertex3f(i*third, j*sixth, 0);
			glVertex3f(i*sixth, j*third, 0);

			glVertex3f(0, j*third, k*sixth);
			glVertex3f(i*sixth, j*third, 0);

			glVertex3f(0, j*third, k*sixth);
			glVertex3f(0, j*sixth, k*third);

			glVertex3f(0, j*sixth, k*third);
			glVertex3f(i*sixth, 0, k*third);

			glVertex3f(i*sixth, 0, k*third);
			glVertex3f(i*third, 0, k*sixth);
			i = 1;
			j = -1;
			k = 1;
			glVertex3f(i*third, j*sixth, 0);
			glVertex3f(i*third, 0, k*sixth);

			glVertex3f(i*third, j*sixth, 0);
			glVertex3f(i*sixth, j*third, 0);

			glVertex3f(0, j*third, k*sixth);
			glVertex3f(i*sixth, j*third, 0);

			glVertex3f(0, j*third, k*sixth);
			glVertex3f(0, j*sixth, k*third);

			glVertex3f(0, j*sixth, k*third);
			glVertex3f(i*sixth, 0, k*third);

			glVertex3f(i*sixth, 0, k*third);
			glVertex3f(i*third, 0, k*sixth);
			i = 1;
			j = 1;
			k = -1;
			glVertex3f(i*third, j*sixth, 0);
			glVertex3f(i*third, 0, k*sixth);

			glVertex3f(i*third, j*sixth, 0);
			glVertex3f(i*sixth, j*third, 0);

			glVertex3f(0, j*third, k*sixth);
			glVertex3f(i*sixth, j*third, 0);

			glVertex3f(0, j*third, k*sixth);
			glVertex3f(0, j*sixth, k*third);

			glVertex3f(0, j*sixth, k*third);
			glVertex3f(i*sixth, 0, k*third);

			glVertex3f(i*sixth, 0, k*third);
			glVertex3f(i*third, 0, k*sixth);
			i = -1;
			j = -1;
			k = 1;
			glVertex3f(i*third, j*sixth, 0);
			glVertex3f(i*third, 0, k*sixth);

			glVertex3f(i*third, j*sixth, 0);
			glVertex3f(i*sixth, j*third, 0);

			glVertex3f(0, j*third, k*sixth);
			glVertex3f(i*sixth, j*third, 0);

			glVertex3f(0, j*third, k*sixth);
			glVertex3f(0, j*sixth, k*third);

			glVertex3f(0, j*sixth, k*third);
			glVertex3f(i*sixth, 0, k*third);

			glVertex3f(i*sixth, 0, k*third);
			glVertex3f(i*third, 0, k*sixth);
			i = -1;
			j = 1;
			k = -1;
			glVertex3f(i*third, j*sixth, 0);
			glVertex3f(i*third, 0, k*sixth);

			glVertex3f(i*third, j*sixth, 0);
			glVertex3f(i*sixth, j*third, 0);

			glVertex3f(0, j*third, k*sixth);
			glVertex3f(i*sixth, j*third, 0);

			glVertex3f(0, j*third, k*sixth);
			glVertex3f(0, j*sixth, k*third);

			glVertex3f(0, j*sixth, k*third);
			glVertex3f(i*sixth, 0, k*third);

			glVertex3f(i*sixth, 0, k*third);
			glVertex3f(i*third, 0, k*sixth);
			i = 1;
			j = -1;
			k = -1;
			glVertex3f(i*third, j*sixth, 0);
			glVertex3f(i*third, 0, k*sixth);

			glVertex3f(i*third, j*sixth, 0);
			glVertex3f(i*sixth, j*third, 0);

			glVertex3f(0, j*third, k*sixth);
			glVertex3f(i*sixth, j*third, 0);

			glVertex3f(0, j*third, k*sixth);
			glVertex3f(0, j*sixth, k*third);

			glVertex3f(0, j*sixth, k*third);
			glVertex3f(i*sixth, 0, k*third);

			glVertex3f(i*sixth, 0, k*third);
			glVertex3f(i*third, 0, k*sixth);
			i = -1;
			j = -1;
			k = -1;
			glVertex3f(i*third, j*sixth, 0);
			glVertex3f(i*third, 0, k*sixth);

			glVertex3f(i*third, j*sixth, 0);
			glVertex3f(i*sixth, j*third, 0);

			glVertex3f(0, j*third, k*sixth);
			glVertex3f(i*sixth, j*third, 0);

			glVertex3f(0, j*third, k*sixth);
			glVertex3f(0, j*sixth, k*third);

			glVertex3f(0, j*sixth, k*third);
			glVertex3f(i*sixth, 0, k*third);

			glVertex3f(i*sixth, 0, k*third);
			glVertex3f(i*third, 0, k*sixth);

		}
		else {
			i = 1;
			j = 1;
			k = 1;
			glVertex3f(i*nineth, j*tenth, k*third);
			glVertex3f(i*third, j*nineth, k*third);

			glVertex3f(i*third, j*third, k*nineth);
			glVertex3f(i*third, j*nineth, k*third);

			glVertex3f(i*nineth, j*third, k*third);
			glVertex3f(i*third, j*third, k*nineth);

			glVertex3f(i*third, j*nineth, k*third);
			glVertex3f(i*third, 0, k*third);

			glVertex3f(i*nineth, j*tenth, k*third);
			glVertex3f(0, j*tenth, k*third);

			glVertex3f(i*third, j*third, k*nineth);
			glVertex3f(i*third, j*third, 0);



			i = -1;
			j = 1;
			k = 1;
			glVertex3f(i*nineth, j*tenth, k*third);
			glVertex3f(i*third, j*nineth, k*third);

			glVertex3f(i*third, j*third, k*nineth);
			glVertex3f(i*third, j*nineth, k*third);

			glVertex3f(i*nineth, j*third, k*third);
			glVertex3f(i*third, j*third, k*nineth);

			glVertex3f(i*third, j*nineth, k*third);
			glVertex3f(i*third, 0, k*third);

			glVertex3f(i*nineth, j*tenth, k*third);
			glVertex3f(0, j*tenth, k*third);

			glVertex3f(i*third, j*third, k*nineth);
			glVertex3f(i*third, j*third, 0);
			i = 1;
			j = -1;
			k = 1;
			glVertex3f(i*nineth, j*tenth, k*third);
			glVertex3f(i*third, j*nineth, k*third);

			glVertex3f(i*third, j*third, k*nineth);
			glVertex3f(i*third, j*nineth, k*third);

			glVertex3f(i*nineth, j*third, k*third);
			glVertex3f(i*third, j*third, k*nineth);

			glVertex3f(i*third, j*nineth, k*third);
			glVertex3f(i*third, 0, k*third);

			glVertex3f(i*nineth, j*tenth, k*third);
			glVertex3f(0, j*tenth, k*third);

			glVertex3f(i*third, j*third, k*nineth);
			glVertex3f(i*third, j*third, 0);
			i = 1;
			j = 1;
			k = -1;
			glVertex3f(i*nineth, j*tenth, k*third);
			glVertex3f(i*third, j*nineth, k*third);

			glVertex3f(i*third, j*third, k*nineth);
			glVertex3f(i*third, j*nineth, k*third);

			glVertex3f(i*nineth, j*third, k*third);
			glVertex3f(i*third, j*third, k*nineth);

			glVertex3f(i*third, j*nineth, k*third);
			glVertex3f(i*third, 0, k*third);

			glVertex3f(i*nineth, j*tenth, k*third);
			glVertex3f(0, j*tenth, k*third);

			glVertex3f(i*third, j*third, k*nineth);
			glVertex3f(i*third, j*third, 0);
			i = -1;
			j = -1;
			k = 1;
			glVertex3f(i*nineth, j*tenth, k*third);
			glVertex3f(i*third, j*nineth, k*third);

			glVertex3f(i*third, j*third, k*nineth);
			glVertex3f(i*third, j*nineth, k*third);

			glVertex3f(i*nineth, j*third, k*third);
			glVertex3f(i*third, j*third, k*nineth);

			glVertex3f(i*third, j*nineth, k*third);
			glVertex3f(i*third, 0, k*third);

			glVertex3f(i*nineth, j*tenth, k*third);
			glVertex3f(0, j*tenth, k*third);

			glVertex3f(i*third, j*third, k*nineth);
			glVertex3f(i*third, j*third, 0);
			i = -1;
			j = 1;
			k = -1;
			glVertex3f(i*nineth, j*tenth, k*third);
			glVertex3f(i*third, j*nineth, k*third);

			glVertex3f(i*third, j*third, k*nineth);
			glVertex3f(i*third, j*nineth, k*third);

			glVertex3f(i*nineth, j*third, k*third);
			glVertex3f(i*third, j*third, k*nineth);

			glVertex3f(i*third, j*nineth, k*third);
			glVertex3f(i*third, 0, k*third);

			glVertex3f(i*nineth, j*tenth, k*third);
			glVertex3f(0, j*tenth, k*third);

			glVertex3f(i*third, j*third, k*nineth);
			glVertex3f(i*third, j*third, 0);
			i = 1;
			j = -1;
			k = -1;
			glVertex3f(i*nineth, j*tenth, k*third);
			glVertex3f(i*third, j*nineth, k*third);

			glVertex3f(i*third, j*third, k*nineth);
			glVertex3f(i*third, j*nineth, k*third);

			glVertex3f(i*nineth, j*third, k*third);
			glVertex3f(i*third, j*third, k*nineth);

			glVertex3f(i*third, j*nineth, k*third);
			glVertex3f(i*third, 0, k*third);

			glVertex3f(i*nineth, j*tenth, k*third);
			glVertex3f(0, j*tenth, k*third);

			glVertex3f(i*third, j*third, k*nineth);
			glVertex3f(i*third, j*third, 0);
			i = -1;
			j = -1;
			k = -1;
			glVertex3f(i*nineth, j*tenth, k*third);
			glVertex3f(i*third, j*nineth, k*third);

			glVertex3f(i*third, j*third, k*nineth);
			glVertex3f(i*third, j*nineth, k*third);

			glVertex3f(i*nineth, j*third, k*third);
			glVertex3f(i*third, j*third, k*nineth);

			glVertex3f(i*third, j*nineth, k*third);
			glVertex3f(i*third, 0, k*third);

			glVertex3f(i*nineth, j*tenth, k*third);
			glVertex3f(0, j*tenth, k*third);

			glVertex3f(i*third, j*third, k*nineth);
			glVertex3f(i*third, j*third, 0);

		}
	}
	else if (Scase == 4)
	{
		i = 1;
		j = 1;
		k = 1;
		glVertex3f(i*third, j*third, k*third);
		glVertex3f(0, j*third, k*third);

		glVertex3f(i*third, j*third, k*third);
		glVertex3f(i*third, 0, k*third);

		glVertex3f(i*third, j*third, k*third);
		glVertex3f(i*third, j*third, 0);
		i = -1;
		j = 1;
		k = 1;
		glVertex3f(i*third, j*third, k*third);
		glVertex3f(0, j*third, k*third);

		glVertex3f(i*third, j*third, k*third);
		glVertex3f(i*third, 0, k*third);

		glVertex3f(i*third, j*third, k*third);
		glVertex3f(i*third, j*third, 0);
		i = 1;
		j = -1;
		k = 1;
		glVertex3f(i*third, j*third, k*third);
		glVertex3f(0, j*third, k*third);

		glVertex3f(i*third, j*third, k*third);
		glVertex3f(i*third, 0, k*third);

		glVertex3f(i*third, j*third, k*third);
		glVertex3f(i*third, j*third, 0);
		i = 1;
		j = 1;
		k = -1;
		glVertex3f(i*third, j*third, k*third);
		glVertex3f(0, j*third, k*third);

		glVertex3f(i*third, j*third, k*third);
		glVertex3f(i*third, 0, k*third);

		glVertex3f(i*third, j*third, k*third);
		glVertex3f(i*third, j*third, 0);
		i = -1;
		j = -1;
		k = 1;
		glVertex3f(i*third, j*third, k*third);
		glVertex3f(0, j*third, k*third);

		glVertex3f(i*third, j*third, k*third);
		glVertex3f(i*third, 0, k*third);

		glVertex3f(i*third, j*third, k*third);
		glVertex3f(i*third, j*third, 0);
		i = -1;
		j = 1;
		k = -1;
		glVertex3f(i*third, j*third, k*third);
		glVertex3f(0, j*third, k*third);

		glVertex3f(i*third, j*third, k*third);
		glVertex3f(i*third, 0, k*third);

		glVertex3f(i*third, j*third, k*third);
		glVertex3f(i*third, j*third, 0);
		i = 1;
		j = -1;
		k = -1;
		glVertex3f(i*third, j*third, k*third);
		glVertex3f(0, j*third, k*third);

		glVertex3f(i*third, j*third, k*third);
		glVertex3f(i*third, 0, k*third);

		glVertex3f(i*third, j*third, k*third);
		glVertex3f(i*third, j*third, 0);
		i = -1;
		j = -1;
		k = -1;
		glVertex3f(i*third, j*third, k*third);
		glVertex3f(0, j*third, k*third);

		glVertex3f(i*third, j*third, k*third);
		glVertex3f(i*third, 0, k*third);

		glVertex3f(i*third, j*third, k*third);
		glVertex3f(i*third, j*third, 0);
	}
	else if (Scase == 5)
	{
		i = 1;
		j = 1;
		k = 1;
		glVertex3f(0, 0, k*forth);
		glVertex3f(i*first, j*first, k*fifth);

		glVertex3f(i*first, j*first, k*fifth);
		glVertex3f(i*first, j*fifth, k*first);

		glVertex3f(i*first, j*first, k*fifth);
		glVertex3f(i*fifth, j*first, k*first);

		glVertex3f(i*fifth, j*first, k*first);
		glVertex3f(i*first, j*fifth, k*first);

		glVertex3f(i*first, j*fifth, k*first);
		glVertex3f(0, j*forth, 0);

		glVertex3f(i*fifth, j*first, k*first);
		glVertex3f(i*forth, 0, 0);
		i = -1;
		j = 1;
		k = 1;
		glVertex3f(0, 0, k*forth);
		glVertex3f(i*first, j*first, k*fifth);

		glVertex3f(i*first, j*first, k*fifth);
		glVertex3f(i*first, j*fifth, k*first);

		glVertex3f(i*first, j*first, k*fifth);
		glVertex3f(i*fifth, j*first, k*first);

		glVertex3f(i*fifth, j*first, k*first);
		glVertex3f(i*first, j*fifth, k*first);

		glVertex3f(i*first, j*fifth, k*first);
		glVertex3f(0, j*forth, 0);

		glVertex3f(i*fifth, j*first, k*first);
		glVertex3f(i*forth, 0, 0);
		i = 1;
		j = -1;
		k = 1;
		glVertex3f(0, 0, k*forth);
		glVertex3f(i*first, j*first, k*fifth);

		glVertex3f(i*first, j*first, k*fifth);
		glVertex3f(i*first, j*fifth, k*first);

		glVertex3f(i*first, j*first, k*fifth);
		glVertex3f(i*fifth, j*first, k*first);

		glVertex3f(i*fifth, j*first, k*first);
		glVertex3f(i*first, j*fifth, k*first);

		glVertex3f(i*first, j*fifth, k*first);
		glVertex3f(0, j*forth, 0);

		glVertex3f(i*fifth, j*first, k*first);
		glVertex3f(i*forth, 0, 0);
		i = 1;
		j = 1;
		k = -1;
		glVertex3f(0, 0, k*forth);
		glVertex3f(i*first, j*first, k*fifth);

		glVertex3f(i*first, j*first, k*fifth);
		glVertex3f(i*first, j*fifth, k*first);

		glVertex3f(i*first, j*first, k*fifth);
		glVertex3f(i*fifth, j*first, k*first);

		glVertex3f(i*fifth, j*first, k*first);
		glVertex3f(i*first, j*fifth, k*first);

		glVertex3f(i*first, j*fifth, k*first);
		glVertex3f(0, j*forth, 0);

		glVertex3f(i*fifth, j*first, k*first);
		glVertex3f(i*forth, 0, 0);
		i = -1;
		j = -1;
		k = 1;
		glVertex3f(0, 0, k*forth);
		glVertex3f(i*first, j*first, k*fifth);

		glVertex3f(i*first, j*first, k*fifth);
		glVertex3f(i*first, j*fifth, k*first);

		glVertex3f(i*first, j*first, k*fifth);
		glVertex3f(i*fifth, j*first, k*first);

		glVertex3f(i*fifth, j*first, k*first);
		glVertex3f(i*first, j*fifth, k*first);

		glVertex3f(i*first, j*fifth, k*first);
		glVertex3f(0, j*forth, 0);

		glVertex3f(i*fifth, j*first, k*first);
		glVertex3f(i*forth, 0, 0);
		i = -1;
		j = 1;
		k = -1;
		glVertex3f(0, 0, k*forth);
		glVertex3f(i*first, j*first, k*fifth);

		glVertex3f(i*first, j*first, k*fifth);
		glVertex3f(i*first, j*fifth, k*first);

		glVertex3f(i*first, j*first, k*fifth);
		glVertex3f(i*fifth, j*first, k*first);

		glVertex3f(i*fifth, j*first, k*first);
		glVertex3f(i*first, j*fifth, k*first);

		glVertex3f(i*first, j*fifth, k*first);
		glVertex3f(0, j*forth, 0);

		glVertex3f(i*fifth, j*first, k*first);
		glVertex3f(i*forth, 0, 0);
		i = 1;
		j = -1;
		k = -1;
		glVertex3f(0, 0, k*forth);
		glVertex3f(i*first, j*first, k*fifth);

		glVertex3f(i*first, j*first, k*fifth);
		glVertex3f(i*first, j*fifth, k*first);

		glVertex3f(i*first, j*first, k*fifth);
		glVertex3f(i*fifth, j*first, k*first);

		glVertex3f(i*fifth, j*first, k*first);
		glVertex3f(i*first, j*fifth, k*first);

		glVertex3f(i*first, j*fifth, k*first);
		glVertex3f(0, j*forth, 0);

		glVertex3f(i*fifth, j*first, k*first);
		glVertex3f(i*forth, 0, 0);
		i = -1;
		j = -1;
		k = -1;
		glVertex3f(0, 0, k*forth);
		glVertex3f(i*first, j*first, k*fifth);

		glVertex3f(i*first, j*first, k*fifth);
		glVertex3f(i*first, j*fifth, k*first);

		glVertex3f(i*first, j*first, k*fifth);
		glVertex3f(i*fifth, j*first, k*first);

		glVertex3f(i*fifth, j*first, k*first);
		glVertex3f(i*first, j*fifth, k*first);

		glVertex3f(i*first, j*fifth, k*first);
		glVertex3f(0, j*forth, 0);

		glVertex3f(i*fifth, j*first, k*first);
		glVertex3f(i*forth, 0, 0);
	}
	else if (Scase == 6)
	{
		i = 1;
		j = 1;
		k = 1;
		glVertex3f(i*forth, 0, 0);
		glVertex3f(i*eleventh, j*eleventh, k*eleventh);

		glVertex3f(0, j*forth, 0);
		glVertex3f(i*eleventh, j*eleventh, k*eleventh);

		glVertex3f(0, 0, k*forth);
		glVertex3f(i*eleventh, j*eleventh, k*eleventh);

		i = -1;
		j = 1;
		k = 1;
		glVertex3f(i*forth, 0, 0);
		glVertex3f(i*eleventh, j*eleventh, k*eleventh);

		glVertex3f(0, j*forth, 0);
		glVertex3f(i*eleventh, j*eleventh, k*eleventh);

		glVertex3f(0, 0, k*forth);
		glVertex3f(i*eleventh, j*eleventh, k*eleventh);


		i = 1;
		j = -1;
		k = 1;
		glVertex3f(i*forth, 0, 0);
		glVertex3f(i*eleventh, j*eleventh, k*eleventh);

		glVertex3f(0, j*forth, 0);
		glVertex3f(i*eleventh, j*eleventh, k*eleventh);

		glVertex3f(0, 0, k*forth);
		glVertex3f(i*eleventh, j*eleventh, k*eleventh);

		i = 1;
		j = 1;
		k = -1;
		glVertex3f(i*forth, 0, 0);
		glVertex3f(i*eleventh, j*eleventh, k*eleventh);

		glVertex3f(0, j*forth, 0);
		glVertex3f(i*eleventh, j*eleventh, k*eleventh);

		glVertex3f(0, 0, k*forth);
		glVertex3f(i*eleventh, j*eleventh, k*eleventh);

		i = -1;
		j = -1;
		k = 1;
		glVertex3f(i*forth, 0, 0);
		glVertex3f(i*eleventh, j*eleventh, k*eleventh);

		glVertex3f(0, j*forth, 0);
		glVertex3f(i*eleventh, j*eleventh, k*eleventh);

		glVertex3f(0, 0, k*forth);
		glVertex3f(i*eleventh, j*eleventh, k*eleventh);

		i = -1;
		j = 1;
		k = -1;
		glVertex3f(i*forth, 0, 0);
		glVertex3f(i*eleventh, j*eleventh, k*eleventh);

		glVertex3f(0, j*forth, 0);
		glVertex3f(i*eleventh, j*eleventh, k*eleventh);

		glVertex3f(0, 0, k*forth);
		glVertex3f(i*eleventh, j*eleventh, k*eleventh);

		i = 1;
		j = -1;
		k = -1;
		glVertex3f(i*forth, 0, 0);
		glVertex3f(i*eleventh, j*eleventh, k*eleventh);

		glVertex3f(0, j*forth, 0);
		glVertex3f(i*eleventh, j*eleventh, k*eleventh);

		glVertex3f(0, 0, k*forth);
		glVertex3f(i*eleventh, j*eleventh, k*eleventh);

		i = -1;
		j = -1;
		k = -1;
		glVertex3f(i*forth, 0, 0);
		glVertex3f(i*eleventh, j*eleventh, k*eleventh);

		glVertex3f(0, j*forth, 0);
		glVertex3f(i*eleventh, j*eleventh, k*eleventh);

		glVertex3f(0, 0, k*forth);
		glVertex3f(i*eleventh, j*eleventh, k*eleventh);
	}
	else if (Scase == 7)
	{
		i = 1;
		j = 1;
		k = 1;
		glVertex3f(0, 0, k*eighth);
		glVertex3f(0, j*eighth, 0);

		glVertex3f(0, 0, k*eighth);
		glVertex3f(i*eighth, 0, 0);

		glVertex3f(0, j*eighth, 0);
		glVertex3f(i*eighth, 0, 0);

		i = -1;
		j = 1;
		k = 1;
		glVertex3f(0, 0, k*eighth);
		glVertex3f(0, j*eighth, 0);

		glVertex3f(0, 0, k*eighth);
		glVertex3f(i*eighth, 0, 0);

		glVertex3f(0, j*eighth, 0);
		glVertex3f(i*eighth, 0, 0);
		i = 1;
		j = -1;
		k = 1;
		glVertex3f(0, 0, k*eighth);
		glVertex3f(0, j*eighth, 0);

		glVertex3f(0, 0, k*eighth);
		glVertex3f(i*eighth, 0, 0);

		glVertex3f(0, j*eighth, 0);
		glVertex3f(i*eighth, 0, 0);
		i = 1;
		j = 1;
		k = -1;
		glVertex3f(0, 0, k*eighth);
		glVertex3f(0, j*eighth, 0);

		glVertex3f(0, 0, k*eighth);
		glVertex3f(i*eighth, 0, 0);

		glVertex3f(0, j*eighth, 0);
		glVertex3f(i*eighth, 0, 0);
		i = -1;
		j = -1;
		k = 1;
		glVertex3f(0, 0, k*eighth);
		glVertex3f(0, j*eighth, 0);

		glVertex3f(0, 0, k*eighth);
		glVertex3f(i*eighth, 0, 0);

		glVertex3f(0, j*eighth, 0);
		glVertex3f(i*eighth, 0, 0);
		i = -1;
		j = 1;
		k = -1;
		glVertex3f(0, 0, k*eighth);
		glVertex3f(0, j*eighth, 0);

		glVertex3f(0, 0, k*eighth);
		glVertex3f(i*eighth, 0, 0);

		glVertex3f(0, j*eighth, 0);
		glVertex3f(i*eighth, 0, 0);
		i = 1;
		j = -1;
		k = -1;
		glVertex3f(0, 0, k*eighth);
		glVertex3f(0, j*eighth, 0);

		glVertex3f(0, 0, k*eighth);
		glVertex3f(i*eighth, 0, 0);

		glVertex3f(0, j*eighth, 0);
		glVertex3f(i*eighth, 0, 0);
		i = -1;
		j = -1;
		k = -1;
		glVertex3f(0, 0, k*eighth);
		glVertex3f(0, j*eighth, 0);

		glVertex3f(0, 0, k*eighth);
		glVertex3f(i*eighth, 0, 0);

		glVertex3f(0, j*eighth, 0);
		glVertex3f(i*eighth, 0, 0);
	}
	else if (Scase == 0)
	{

	}

	glEnd();

//// aatoms print
	if (perspective_on)
	{
		glViewport(0, 0, width, height);//(first 2 sets the lower left corner of the window w h sets width height of the window
		glMatrixMode(GL_PROJECTION);// defines the camera behavior projection is the view point of me
		glLoadIdentity();
		if (width <= height)
		{
			glOrtho(
				-1.05, +1.05,
				-1.05 * (GLfloat)height / (GLfloat)width, +1.05 * (GLfloat)height / (GLfloat)width,
				-10.0, 10.0);
			dipleft = -1;


		}
		else
		{
			glOrtho(
				-1.05 * (GLfloat)width / (GLfloat)height, +1.05 * (GLfloat)width / (GLfloat)height,
				-1.05, +1.05,
				-10.0, 10.0);
			dipleft = -(GLfloat)width / (GLfloat)height;

		}
		glMatrixMode(GL_MODELVIEW);
	}
//
	for (int ff = 0; ff < a; ff++)
	{
		glLoadIdentity();
		glColor3f(0, 0, 0);

		glTranslatef(-dipleft - 0.2, float(ff) / float(a) - 0.1, 0);

		glScalef(0.5, 0.5, 0.5);
		itoa(aatoms[ff], ss, 10);

		stroke_c = 0;
		while (ss[stroke_c] != '\0')
		{
			JGN_StrokeCharacter(ss[stroke_c]);
			stroke_c++;

		}

		stroke_c = 0;

	}


	glPointSize(10);
	for (int ff = 0; ff < a; ff++)
	{
		glLoadIdentity();
		glColor3f(0, 0, 0);

		glTranslatef(-dipleft - 0.2, float(ff) / float(a), 0);


		while (atoms[stroke_c] != ' ')
		{
			JGN_StrokeCharacter(atoms[stroke_c]);
			stroke_c++;

		}
		stroke_c++;

		glLoadIdentity();

		if (shperes_on)
		{
			colr[0] = fmod(aweights[ff], 1.5);
			colr[1] = fmod(anumber[ff], 0.92);
			colr[2] = fmod(100 * colr[0] * colr[1], 0.8);

			GLfloat mat_ambient[] = { colr[0], colr[1], colr[2], 1.0 };
			GLfloat mat_deffuse[] = { colr[0], colr[1], colr[2], 1.0 };

			glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_deffuse);


			glTranslated(-dipleft, float(ff) / float(a), 0);

			glutSolidSphere(20 * 0.001, 10, 10);

			glTranslated(dipleft, -float(ff) / float(a), 0);

		}
		else
		{
			glBegin(GL_POINTS);

			colr[0] = fmod(aweights[ff], 1.5);
			colr[1] = fmod(anumber[ff], 0.92);
			colr[2] = fmod(100 * colr[0] * colr[1], 0.8);
			glColor3fv(colr);

			glVertex3f(-dipleft, float(ff) / float(a), 0);



			glEnd();
		}

	}

	if (shperes_on)
		glDisable(GL_LIGHTING);

	if (nanotube)
	{


		glLoadIdentity();

		glTranslatef(dipleft, 0.8, 0);
		JGN_StrokeCharacter('R');
		JGN_StrokeCharacter('1');
		JGN_StrokeCharacter(' ');




		itoa(S1v, s1itoa, 10);

		for (Scounter = 0; Scounter < 5; Scounter++)
		{
			JGN_StrokeCharacter(s1itoa[Scounter]);
			if (s1itoa[Scounter] == '\0')
			{
				break;
			}
		}
		JGN_StrokeCharacter(Angstrom);


		glLoadIdentity();

		glTranslatef(dipleft, 0.6, 0);


		JGN_StrokeCharacter('R');
		JGN_StrokeCharacter('2');
		JGN_StrokeCharacter(' ');


		itoa(S2v, s1itoa, 10);

		for (Scounter = 0; Scounter < 5; Scounter++)
		{

			JGN_StrokeCharacter(s1itoa[Scounter]);
			if (s1itoa[Scounter] == '\0')
			{
				break;
			}
		}
		JGN_StrokeCharacter(Angstrom);

	}
	/*else if (jgn_supercell)
	{
	glLoadIdentity();

	glColor3f(0, 0, 0);

	glTranslatef(dipleft, 0.8, 0);
	glScalef(1.0 / 1000.0,
	1.0 / 1000.0,
	1.0 / 1000.0);

	glLineWidth(2);
	glutStrokeCharacter(GLUT_STROKE_ROMAN, 'a');
	glutStrokeCharacter(GLUT_STROKE_ROMAN, '1');
	glutStrokeCharacter(GLUT_STROKE_ROMAN, ' ');

	itoa(jgn_supercell_xyz[0], s1itoa, 10);

	for (Scounter = 0; Scounter < 5; Scounter++)
	{

	glutStrokeCharacter(GLUT_STROKE_ROMAN, s1itoa[Scounter]);
	if (s1itoa[Scounter] == '\0')
	{
	break;
	}
	}

	glLoadIdentity();

	glColor3f(0, 0, 0);



	glTranslatef(dipleft, 0.6, 0);
	glScalef(1.0 / 1000.0,
	1.0 / 1000.0,
	1.0 / 1000.0);

	glLineWidth(2);
	glutStrokeCharacter(GLUT_STROKE_ROMAN, 'a');
	glutStrokeCharacter(GLUT_STROKE_ROMAN, '2');
	glutStrokeCharacter(GLUT_STROKE_ROMAN, ' ');

	itoa(jgn_supercell_xyz[1], s1itoa, 10);

	for (Scounter = 0; Scounter < 5; Scounter++)
	{

	glutStrokeCharacter(GLUT_STROKE_ROMAN, s1itoa[Scounter]);
	if (s1itoa[Scounter] == '\0')
	{
	break;
	}
	}

	glLoadIdentity();


	glTranslatef(dipleft, 0.4, 0);
	glScalef(1.0 / 1000.0,
	1.0 / 1000.0,
	1.0 / 1000.0);

	glColor3f(0, 0, 0);
	glLineWidth(2);
	glutStrokeCharacter(GLUT_STROKE_ROMAN, 'a');
	glutStrokeCharacter(GLUT_STROKE_ROMAN, '3');
	glutStrokeCharacter(GLUT_STROKE_ROMAN, ' ');

	itoa(jgn_supercell_xyz[2], s1itoa, 10);

	for (Scounter = 0; Scounter < 5; Scounter++)
	{

	glutStrokeCharacter(GLUT_STROKE_ROMAN, s1itoa[Scounter]);
	if (s1itoa[Scounter] == '\0')
	{
	break;
	}
	}
	}*/
	else if (CustomSurfacesOn)
	{

	}
	else if (Rod_like == -1)
	{
		//
		glLoadIdentity();
		if (S1v >= S2v || S1v >= S3v)
		{
			glColor3f(.8, .8, .8);
		}
		else
		{
			glColor3f(0, 0, 0);

		}
		glTranslatef(dipleft, 0.8, 0);

		JGN_StrokeCharacter('{');
		JGN_StrokeCharacter('1');
		JGN_StrokeCharacter('0');
		JGN_StrokeCharacter('0');
		JGN_StrokeCharacter('}');
		JGN_StrokeCharacter(' ');

		itoa(S1v, s1itoa, 10);

		for (Scounter = 0; Scounter < 5; Scounter++)
		{

			JGN_StrokeCharacter(s1itoa[Scounter]);
			if (s1itoa[Scounter] == '\0')
			{
				break;
			}
		}
		JGN_StrokeCharacter(Angstrom);



		glLoadIdentity();

		if (S2v >= 2 * S1v || S3v <= S2v)
		{
			glColor3f(.8, .8, .8);
		}
		else
		{
			glColor3f(0, 0, 0);
		}


		glTranslatef(dipleft, 0.6, 0);

		JGN_StrokeCharacter('{');
		JGN_StrokeCharacter('1');
		JGN_StrokeCharacter('1');
		JGN_StrokeCharacter('0');
		JGN_StrokeCharacter('}');
		JGN_StrokeCharacter(' ');

		itoa(S2v, s1itoa, 10);

		for (Scounter = 0; Scounter < 5; Scounter++)
		{

			JGN_StrokeCharacter(s1itoa[Scounter]);
			if (s1itoa[Scounter] == '\0')
			{
				break;
			}
		}
		JGN_StrokeCharacter(Angstrom);

		glLoadIdentity();


		glTranslatef(dipleft, 0.4, 0);

		glColor3f(0, 0, 0);
		JGN_StrokeCharacter('{');
		JGN_StrokeCharacter('1');
		JGN_StrokeCharacter('1');
		JGN_StrokeCharacter('1');
		JGN_StrokeCharacter('}');
		JGN_StrokeCharacter(' ');

		itoa(S3v, s1itoa, 10);

		for (Scounter = 0; Scounter < 5; Scounter++)
		{

			JGN_StrokeCharacter(s1itoa[Scounter]);
			if (s1itoa[Scounter] == '\0')
			{
				break;
			}
		}
		JGN_StrokeCharacter(Angstrom);

	}
	else if (Right_Hexagonal == -1)
	{
		glLoadIdentity();
		glTranslatef(dipleft, 0.8, 0);
		if (float(S1v) / float(S2v) > 1.14814814815)

		{
			glColor3f(.8, .8, .8);
		}
		else
		{
			glColor3f(0, 0, 0);

		}

		JGN_StrokeCharacter('{');
		JGN_StrokeCharacter('1');
		JGN_StrokeCharacter('0');
		JGN_StrokeCharacter(one_bar);
		JGN_StrokeCharacter('0');
		JGN_StrokeCharacter('}');
		JGN_StrokeCharacter(' ');

		itoa(S1v, s1itoa, 10);

		for (Scounter = 0; Scounter < 5; Scounter++)
		{

			JGN_StrokeCharacter(s1itoa[Scounter]);
			if (s1itoa[Scounter] == '\0')
			{
				break;
			}
		}
		JGN_StrokeCharacter(Angstrom);



		glLoadIdentity();

		glTranslatef(dipleft, 0.6, 0);


		if (float(S1v) / float(S2v) < 0.86842105263)
		{
			glColor3f(.8, .8, .8);

		}
		else
		{

			glColor3f(0, 0, 0);
		}


		JGN_StrokeCharacter('{');
		JGN_StrokeCharacter('1');
		JGN_StrokeCharacter('1');
		JGN_StrokeCharacter(two_bar);
		JGN_StrokeCharacter('0');
		JGN_StrokeCharacter('}');
		JGN_StrokeCharacter(' ');

		itoa(S2v, s1itoa, 10);

		for (Scounter = 0; Scounter < 5; Scounter++)
		{

			JGN_StrokeCharacter(s1itoa[Scounter]);
			if (s1itoa[Scounter] == '\0')
			{
				break;
			}
		}
		JGN_StrokeCharacter(Angstrom);


		glLoadIdentity();


		glTranslatef(dipleft, 0.4, 0);


		glColor3f(0, 0, 0);

		JGN_StrokeCharacter('{');
		JGN_StrokeCharacter('0');
		JGN_StrokeCharacter('0');
		JGN_StrokeCharacter('0');
		JGN_StrokeCharacter('1');
		JGN_StrokeCharacter('}');
		JGN_StrokeCharacter(' ');

		itoa(Right_Hexagonal_height, s1itoa, 10);

		for (Scounter = 0; Scounter < 5; Scounter++)
		{

			JGN_StrokeCharacter(s1itoa[Scounter]);
			if (s1itoa[Scounter] == '\0')
			{
				break;
			}
		}
		JGN_StrokeCharacter(Angstrom);
	}
	else if (want_cyrcle[0] == 'y')
	{
		glLoadIdentity();
		glTranslatef(dipleft, 0.8, 0);

		glColor3f(0, 0, 0);

		JGN_StrokeCharacter('R');
		JGN_StrokeCharacter(' ');


		itoa((int)rad, s1itoa, 10);

		for (Scounter = 0; Scounter < 5; Scounter++)
		{

			JGN_StrokeCharacter(s1itoa[Scounter]);
			if (s1itoa[Scounter] == '\0')
			{
				break;
			}
		}
		JGN_StrokeCharacter(Angstrom);

	}
	else
	{
		if (S1[0] != '0')
		{
			glLoadIdentity();
			glTranslatef(dipleft, 0.8, 0);


			if (Scase == 1 || Scase == 2 || Scase == 3 || Scase == 4)
			{

				glColor3f(0, 0, 0);
			}
			else
			{
				glColor3f(0.8, 0.8, 0.8);

			}

			JGN_StrokeCharacter('{');
			JGN_StrokeCharacter('1');
			JGN_StrokeCharacter('0');
			JGN_StrokeCharacter('0');
			JGN_StrokeCharacter('}');
			JGN_StrokeCharacter(' ');

			itoa(S1v, s1itoa, 10);

			for (Scounter = 0; Scounter < 5; Scounter++)
			{

				JGN_StrokeCharacter(s1itoa[Scounter]);
				if (s1itoa[Scounter] == '\0')
				{
					break;
				}
			}
			JGN_StrokeCharacter(Angstrom);
		}

		if (S2[0] != '0')
		{

			glLoadIdentity();

			glTranslatef(dipleft, 0.6, 0);


			if (Scase == 1 || Scase == 2 || Scase == 5 || Scase == 6)
			{
				glColor3f(0, 0, 0);

			}
			else
			{
				glColor3f(0.8, 0.8, 0.8);

			}

			JGN_StrokeCharacter('{');
			JGN_StrokeCharacter('1');
			JGN_StrokeCharacter('1');
			JGN_StrokeCharacter('0');
			JGN_StrokeCharacter('}');
			JGN_StrokeCharacter(' ');

			itoa(S2v, s1itoa, 10);

			for (Scounter = 0; Scounter < 5; Scounter++)
			{

				JGN_StrokeCharacter(s1itoa[Scounter]);
				if (s1itoa[Scounter] == '\0')
				{
					break;
				}
			}
			JGN_StrokeCharacter(Angstrom);
		}
		if (S3[0] != '0')
		{
			glLoadIdentity();


			glTranslatef(dipleft, 0.4, 0);


			if (Scase == 1 || Scase == 3 || Scase == 5 || Scase == 7)
			{
				glColor3f(0, 0, 0);

			}
			else
			{
				glColor3f(0.8, 0.8, 0.8);

			}

			JGN_StrokeCharacter('{');
			JGN_StrokeCharacter('1');
			JGN_StrokeCharacter('1');
			JGN_StrokeCharacter('1');
			JGN_StrokeCharacter('}');
			JGN_StrokeCharacter(' ');

			itoa(S3v, s1itoa, 10);

			for (Scounter = 0; Scounter < 5; Scounter++)
			{

				JGN_StrokeCharacter(s1itoa[Scounter]);
				if (s1itoa[Scounter] == '\0')
				{
					break;
				}
			}
			JGN_StrokeCharacter(Angstrom);
		}
	}
	if (shperes_on)
		glEnable(GL_LIGHTING);

	return;

}


void spin_image()

{

}

float theta_start[2];
float theta_prev[2] = { 0,0 };







void myinit(void)//initialize OpenGL

{
	glLineWidth(4.0);

	//  Set the background color
	glClearColor(0.9, 0.9, 0.9, 1.0);
	//  The default size is 1.0.

	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_ambient[] = { 1.0, 0.0, 0.0, 1.0 };
	GLfloat mat_deffuse[] = {1.0, 0.0, 0.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
	glShadeModel(GL_SMOOTH);

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_deffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//glEnable(GL_DEPTH_TEST);

	truepointsize = 1000.0;
	pointsize = truepointsize / (Svmax + 5);
	glPointSize(pointsize);



	return;
}

int ctrl_down = 0;
int s_down = 0;

void keyboardgl(int key, int s, int x, int y)
{
	if (key == VK_CONTROL)
	{
		if (s == JGN_DOWN)
		{
			ctrl_down = JGN_DOWN;
		}
		else
		{
			ctrl_down = JGN_UP;
		}
		
	}

	if (key == 's' || key == 'S')
	{
		if (s == JGN_DOWN)
		{
			s_down = JGN_DOWN;
		}
		else
		{
			s_down = JGN_UP;
		}

	}
	if (ctrl_down && s_down)
	{
		ctrl_down = 0;
		s_down = 0;
		DialogBox(hInst, MAKEINTRESOURCE(IDD_CHOOSE_OUT), jgn_help_to_map_the_draw_func, Choose_Format);


		DialogBox(hInst, MAKEINTRESOURCE(IDD_BUILD_POSCAR), jgn_help_to_map_the_draw_func, Poscar_Build);


	}
	else
	{
		int check_if_to_redisplay = 0;
		if ((key == 'q' || key == 'Q') && s == JGN_DOWN)
		{
			if (jgn_supercell)
			{
				jgn_supercell_xyz[0]++;
				sized[0]++;

				FILE* periodic_table = fopen("periodic_table.jgn", "r");

				crystal = (float*)realloc(NULL, sizeof(float)*(jgn_supercell_xyz[0] * jgn_supercell_xyz[1] * jgn_supercell_xyz[2] * t * 5));

				if (jgn_supercell_xyz[0] / 2 == jgn_supercell_xyz[0] / 2.0)
				{
					xexe[0] = 0;
				}
				else
				{
					xexe[0] = 1;
				}

				for (ole4 = -jgn_supercell_xyz[2] / 2; ole4 < jgn_supercell_xyz[2] / 2 + xexe[2]; ole4++) {
					for (ole2 = -jgn_supercell_xyz[1] / 2; ole2 < jgn_supercell_xyz[1] / 2 + xexe[1]; ole2++) {
						for (ole = -jgn_supercell_xyz[0] / 2; ole < jgn_supercell_xyz[0] / 2 + xexe[0]; ole++) {
							for (ole3 = 0; ole3 < t; ole3++) {
								crystal[0 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[0 + 5 * ole3];//atomikos ari8mos


																																												 //crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][0] = direct[0+5*ole3];
								crystal[1 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[1 + 5 * ole3];//atomiko varos
																																												 //crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][1] = direct[1+5*ole3];
								for (ole1 = 0; ole1 < 3; ole1++) {
									crystal[ole1 + 2 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = uccartesian[ole1 + 3 * ole3] + ole*ijk[0][ole1] + ole2*ijk[1][ole1] + ole4*ijk[2][ole1];//cartesians
																																																															//crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][ole1 + 2] = uccartesian[ole1+3*ole3] + ole*ijk[0][ole1] + ole2*ijk[1][ole1] + ole4*ijk[2][ole1];
									if (crystal[ole1 + 2 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] < min_xyz[ole1])
									{
										min_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))];

									}
									if (crystal[ole1 + 2 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] > max_xyz[ole1])
									{
										max_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))];

									}

								}


								rewind(periodic_table);

							}
						}
					}
				}


				std::fclose(periodic_table);

			}
			else
			{
				rad++;
				S1v = S1v + 1;
				if (nanotube)
				{
					MakeScroll();
				}
			}
			check_if_to_redisplay = 1;

		}
		if ((key == 'v' || key == 'V') && s == JGN_DOWN)
		{
			vacuum = vacuum ^ true;
			JGN_PostRedisplay();
		}
		if (key == VK_SHIFT && s == JGN_DOWN)
		{
			shift_down = true;
		}
		else if (key == VK_SHIFT && s == JGN_UP)
		{
			shift_down = false;
		}
		if (key == VK_ADD && s == JGN_DOWN)
		{


			truepointsize = truepointsize + 100;
			pointsize = truepointsize / (Svmax + 5);
			glPointSize(pointsize);
			JGN_PostRedisplay();
		}
		else if (key == VK_SUBTRACT && s == JGN_DOWN)
		{
			truepointsize = truepointsize - 100;
			if (truepointsize < 0)
				truepointsize = 0;
			pointsize = truepointsize / (Svmax + 5);

			glPointSize(pointsize);
			JGN_PostRedisplay();
		}	
		else if (key == '1' || key == VK_NUMPAD1)
		{
			glClearColor(0.5, 0.5, 0.5, 1);
			JGN_PostRedisplay();
		}
		else if (key == '2' || key == VK_NUMPAD2)
		{
			glClearColor(0.9, 0.9, 0.9, 1);
			JGN_PostRedisplay();
		}
		else if (key == '3' || key == VK_NUMPAD3)
		{
			glClearColor(1, 1, 1, 1);
			JGN_PostRedisplay();
		}
		if ((key == 'w' || key == 'W') && s == JGN_DOWN)
		{
			if (jgn_supercell)
			{
				jgn_supercell_xyz[0]--;
				if (jgn_supercell_xyz[0] < 0)
				{
					jgn_supercell_xyz[0] = 0;
				}
				sized[0]= jgn_supercell_xyz[0];


				FILE* periodic_table = fopen("periodic_table.jgn", "r");

				crystal = (float*)realloc(NULL, sizeof(float)*(jgn_supercell_xyz[0] * jgn_supercell_xyz[1] * jgn_supercell_xyz[2] * t * 5));

				if (jgn_supercell_xyz[0] / 2 == jgn_supercell_xyz[0] / 2.0)
				{
					xexe[0] = 0;
				}
				else
				{
					xexe[0] = 1;
				}

				for (ole4 = -jgn_supercell_xyz[2] / 2; ole4 < jgn_supercell_xyz[2] / 2 + xexe[2]; ole4++) {
					for (ole2 = -jgn_supercell_xyz[1] / 2; ole2 < jgn_supercell_xyz[1] / 2 + xexe[1]; ole2++) {
						for (ole = -jgn_supercell_xyz[0] / 2; ole < jgn_supercell_xyz[0] / 2 + xexe[0]; ole++) {
							for (ole3 = 0; ole3 < t; ole3++) {
								crystal[0 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[0 + 5 * ole3];//atomikos ari8mos


																																																											 //crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][0] = direct[0+5*ole3];
								crystal[1 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[1 + 5 * ole3];//atomiko varos
																																																											 //crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][1] = direct[1+5*ole3];
								for (ole1 = 0; ole1 < 3; ole1++) {
									crystal[ole1 + 2 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = uccartesian[ole1 + 3 * ole3] + ole*ijk[0][ole1] + ole2*ijk[1][ole1] + ole4*ijk[2][ole1];//cartesians
																																																																														//crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][ole1 + 2] = uccartesian[ole1+3*ole3] + ole*ijk[0][ole1] + ole2*ijk[1][ole1] + ole4*ijk[2][ole1];
									if (crystal[ole1 + 2 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] < min_xyz[ole1])
									{
										min_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))];

									}
									if (crystal[ole1 + 2 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] > max_xyz[ole1])
									{
										max_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))];

									}

								}


								rewind(periodic_table);

							}
						}
					}
				}


				std::fclose(periodic_table);

			}
			else
			{
				rad--;
				S1v = S1v - 1;
				if (S1v < 0)
				{
					S1v = 0;
				}
				if (rad < 0)
				{
					rad = 0;
				}
				if (nanotube)
				{
					MakeScroll();
				}

			}
			check_if_to_redisplay = 1;

		}
		if ((key == 'a' || key == 'A') && s == JGN_DOWN)
		{
			if (jgn_supercell)
			{
				jgn_supercell_xyz[1]++;
				sized[1]++;


				FILE* periodic_table = fopen("periodic_table.jgn", "r");

				crystal = (float*)realloc(NULL, sizeof(float)*(jgn_supercell_xyz[0] * jgn_supercell_xyz[1] * jgn_supercell_xyz[2] * t * 5));

				if (jgn_supercell_xyz[1] / 2 == jgn_supercell_xyz[1] / 2.0)
				{
					xexe[1] = 0;
				}
				else
				{
					xexe[1] = 1;
				}

				for (ole4 = -jgn_supercell_xyz[2] / 2; ole4 < jgn_supercell_xyz[2] / 2 + xexe[2]; ole4++) {
					for (ole2 = -jgn_supercell_xyz[1] / 2; ole2 < jgn_supercell_xyz[1] / 2 + xexe[1]; ole2++) {
						for (ole = -jgn_supercell_xyz[0] / 2; ole < jgn_supercell_xyz[0] / 2 + xexe[0]; ole++) {
							for (ole3 = 0; ole3 < t; ole3++) {
								crystal[0 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[0 + 5 * ole3];//atomikos ari8mos


																																																											 //crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][0] = direct[0+5*ole3];
								crystal[1 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[1 + 5 * ole3];//atomiko varos
																																																											 //crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][1] = direct[1+5*ole3];
								for (ole1 = 0; ole1 < 3; ole1++) {
									crystal[ole1 + 2 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = uccartesian[ole1 + 3 * ole3] + ole*ijk[0][ole1] + ole2*ijk[1][ole1] + ole4*ijk[2][ole1];//cartesians
																																																																														//crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][ole1 + 2] = uccartesian[ole1+3*ole3] + ole*ijk[0][ole1] + ole2*ijk[1][ole1] + ole4*ijk[2][ole1];
									if (crystal[ole1 + 2 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] < min_xyz[ole1])
									{
										min_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))];

									}
									if (crystal[ole1 + 2 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] > max_xyz[ole1])
									{
										max_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))];

									}

								}


								rewind(periodic_table);

							}
						}
					}
				}


				std::fclose(periodic_table);

			}
			else
			{
				S2v = S2v + 1;
				if (nanotube)
				{
					MakeScroll();
				}

			}
			check_if_to_redisplay = 1;

		}
		if ((key == 's' || key == 'S') && s == JGN_DOWN)
		{
			if (jgn_supercell)
			{
				jgn_supercell_xyz[1]--;
				if (jgn_supercell_xyz[1] < 0)
				{
					jgn_supercell_xyz[1] = 0;
				}
				sized[1] = jgn_supercell_xyz[1];



				FILE* periodic_table = fopen("periodic_table.jgn", "r");

				crystal = (float*)realloc(NULL, sizeof(float)*(jgn_supercell_xyz[0] * jgn_supercell_xyz[1] * jgn_supercell_xyz[2] * t * 5));

				if (jgn_supercell_xyz[1] / 2 == jgn_supercell_xyz[1] / 2.0)
				{
					xexe[1] = 0;
				}
				else
				{
					xexe[1] = 1;
				}

				for (ole4 = -jgn_supercell_xyz[2] / 2; ole4 < jgn_supercell_xyz[2] / 2 + xexe[2]; ole4++) {
					for (ole2 = -jgn_supercell_xyz[1] / 2; ole2 < jgn_supercell_xyz[1] / 2 + xexe[1]; ole2++) {
						for (ole = -jgn_supercell_xyz[0] / 2; ole < jgn_supercell_xyz[0] / 2 + xexe[0]; ole++) {
							for (ole3 = 0; ole3 < t; ole3++) {
								crystal[0 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[0 + 5 * ole3];//atomikos ari8mos


																																																											 //crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][0] = direct[0+5*ole3];
								crystal[1 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[1 + 5 * ole3];//atomiko varos
																																																											 //crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][1] = direct[1+5*ole3];
								for (ole1 = 0; ole1 < 3; ole1++) {
									crystal[ole1 + 2 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = uccartesian[ole1 + 3 * ole3] + ole*ijk[0][ole1] + ole2*ijk[1][ole1] + ole4*ijk[2][ole1];//cartesians
																																																																														//crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][ole1 + 2] = uccartesian[ole1+3*ole3] + ole*ijk[0][ole1] + ole2*ijk[1][ole1] + ole4*ijk[2][ole1];
									if (crystal[ole1 + 2 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] < min_xyz[ole1])
									{
										min_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))];

									}
									if (crystal[ole1 + 2 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] > max_xyz[ole1])
									{
										max_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))];

									}

								}


								rewind(periodic_table);

							}
						}
					}
				}


				std::fclose(periodic_table);

			}
			else
			{
				S2v = S2v - 1;
				if (S2v < 0)
				{
					S2v = 0;
				}
				if (nanotube)
				{
					MakeScroll();
				}

			}
			check_if_to_redisplay = 1;

		}
		if ((key == 'z' || key == 'Z') && s == JGN_DOWN)
		{
			if (jgn_supercell)
			{
				jgn_supercell_xyz[2]++;
				sized[2]++;


				FILE* periodic_table = fopen("periodic_table.jgn", "r");

				crystal = (float*)realloc(NULL, sizeof(float)*(jgn_supercell_xyz[0] * jgn_supercell_xyz[1] * jgn_supercell_xyz[2] * t * 5));

				if (jgn_supercell_xyz[2] / 2 == jgn_supercell_xyz[2] / 2.0)
				{
					xexe[2] = 0;
				}
				else
				{
					xexe[2] = 1;
				}

				for (ole4 = -jgn_supercell_xyz[2] / 2; ole4 < jgn_supercell_xyz[2] / 2 + xexe[2]; ole4++) {
					for (ole2 = -jgn_supercell_xyz[1] / 2; ole2 < jgn_supercell_xyz[1] / 2 + xexe[1]; ole2++) {
						for (ole = -jgn_supercell_xyz[0] / 2; ole < jgn_supercell_xyz[0] / 2 + xexe[0]; ole++) {
							for (ole3 = 0; ole3 < t; ole3++) {
								crystal[0 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[0 + 5 * ole3];//atomikos ari8mos


																																																											 //crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][0] = direct[0+5*ole3];
								crystal[1 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[1 + 5 * ole3];//atomiko varos
																																																											 //crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][1] = direct[1+5*ole3];
								for (ole1 = 0; ole1 < 3; ole1++) {
									crystal[ole1 + 2 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = uccartesian[ole1 + 3 * ole3] + ole*ijk[0][ole1] + ole2*ijk[1][ole1] + ole4*ijk[2][ole1];//cartesians
																																																																														//crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][ole1 + 2] = uccartesian[ole1+3*ole3] + ole*ijk[0][ole1] + ole2*ijk[1][ole1] + ole4*ijk[2][ole1];
									if (crystal[ole1 + 2 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] < min_xyz[ole1])
									{
										min_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))];

									}
									if (crystal[ole1 + 2 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] > max_xyz[ole1])
									{
										max_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))];

									}

								}


								rewind(periodic_table);

							}
						}
					}
				}


				std::fclose(periodic_table);

			}
			else
			{
				Right_Hexagonal_height++;
				S3v = S3v + 1;
				if (nanotube)
				{
					MakeScroll();
				}

			}
			check_if_to_redisplay = 1;

		}
		if ((key == 'x' || key == 'X') && s == JGN_DOWN)
		{
			if (jgn_supercell)
			{
				jgn_supercell_xyz[2]--;
				if (jgn_supercell_xyz[2] < 0)
				{
					jgn_supercell_xyz[2] = 0;
				}
				sized[2] = jgn_supercell_xyz[2];



				FILE* periodic_table = fopen("periodic_table.jgn", "r");

				crystal = (float*)realloc(NULL, sizeof(float)*(jgn_supercell_xyz[0] * jgn_supercell_xyz[1] * jgn_supercell_xyz[2] * t * 5));

				if (jgn_supercell_xyz[2] / 2 == jgn_supercell_xyz[2] / 2.0)
				{
					xexe[2] = 0;
				}
				else
				{
					xexe[2] = 1;
				}

				for (ole4 = -jgn_supercell_xyz[2] / 2; ole4 < jgn_supercell_xyz[2] / 2 + xexe[2]; ole4++) {
					for (ole2 = -jgn_supercell_xyz[1] / 2; ole2 < jgn_supercell_xyz[1] / 2 + xexe[1]; ole2++) {
						for (ole = -jgn_supercell_xyz[0] / 2; ole < jgn_supercell_xyz[0] / 2 + xexe[0]; ole++) {
							for (ole3 = 0; ole3 < t; ole3++) {
								crystal[0 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[0 + 5 * ole3];//atomikos ari8mos


																																																											 //crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][0] = direct[0+5*ole3];
								crystal[1 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[1 + 5 * ole3];//atomiko varos
																																																											 //crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][1] = direct[1+5*ole3];
								for (ole1 = 0; ole1 < 3; ole1++) {
									crystal[ole1 + 2 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = uccartesian[ole1 + 3 * ole3] + ole*ijk[0][ole1] + ole2*ijk[1][ole1] + ole4*ijk[2][ole1];//cartesians
																																																																														//crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][ole1 + 2] = uccartesian[ole1+3*ole3] + ole*ijk[0][ole1] + ole2*ijk[1][ole1] + ole4*ijk[2][ole1];
									if (crystal[ole1 + 2 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] < min_xyz[ole1])
									{
										min_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))];

									}
									if (crystal[ole1 + 2 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] > max_xyz[ole1])
									{
										max_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))];

									}

								}


								rewind(periodic_table);

							}
						}
					}
				}


				std::fclose(periodic_table);

			}
			else
			{

					Right_Hexagonal_height--;
					if (Right_Hexagonal_height < 0)
					{
						Right_Hexagonal_height = 0;
					}
					S3v = S3v - 1;
					if (S3v < 0)
					{
						S3v = 0;
					}
					if (nanotube)
					{
						MakeScroll();
					}

				}
			check_if_to_redisplay = 1;

		}


		if (S1[0] == '1')
		{
			if (S2[0] == '1')
			{
				if (S3[0] == '1') {/*100 110 111*/Scase = 1;
				if (2 * S1v <= S2v && S3v >= 3 * S1v && figure_1 != -1)
				{
					Scase = 4;
				}
				else if (S1v >= S2v && float(S3v) >= (float(S2v) * 3) / 2)
				{
					Scase = 6;
				}
				else if (S1v >= S3v && S3v <= S2v)
				{
					Scase = 7;
				}
				else if (S1v >= S2v)
				{///////
					Scase = 5;
				}
				else if ((S2v >= 2 * S1v && figure_1 != -1)|| S3v <= S2v)
				{
					Scase = 3;
				}
				else if ((float(S3v) >= (float(S2v) * 3) / 2 && figure_1 != -1) || (figure_1 == -1 && S3v>=2*S2v))
				{

					Scase = 2;
				}

				}
				else {/* 100 110*/Scase = 2;/*done*/
				if (S1v >= S2v)
				{
					Scase = 6;
				}
				else if (S2v >= 2 * S1v)
				{
					Scase = 4;
				}


				}
			}
			else {
				if (S3[0] == '1') {/*100 111*/Scase = 3;/*done*/
				if (S1v >= S3v)
				{
					Scase = 7;
				}
				else if (S3v >= 3 * S1v)
				{
					Scase = 4;
				}

				}
				else {/* 100*/Scase = 4;/*done*/


				}
			}
		}
		else {
			if (S2[0] == '1')
			{
				if (S3[0] == '1') {/*110 111*/Scase = 5;/*done*/
				if (float(S3v) >= (float(S2v) * 3) / 2)
				{

					Scase = 6;
				}
				else if (S3v <= S2v) {
					Scase = 7;
				}
				}
				else {/*110*/Scase = 6;/*done*/


				}
			}
			else {
				if (S3[0] == '1') {/*111*/Scase = 7;/*done*/

				}
				else {/**/Scase = 0;


				}
			}
		}


		lines_param();

	
		if (check_if_to_redisplay)
		{
			JGN_PostRedisplay();
		}
		
	}

	
}


void lines_param()
{
	if (figure_1 == -1)
	{
		int S1vb = S1v;
		int S2vb = S2v;
		int S3vb = S3v;





		if (2 * S2v - S3v >= S1v)
		{
			if (S3v < S2v)
			{
				S2v = S3v;
			}
			if (S3v < S1v)
			{
				S1v = S3v;
			}


			first = (GLfloat)1.0*float(S3v - S2v) / (Svmax + 5);
			second = (GLfloat)1.0*float(S2v - S1v) / (Svmax + 5);
			third = (GLfloat)1.0*float(S1v) / (Svmax + 5);
			forth = (GLfloat)1.0*float(S2v) / (Svmax + 5);
			fifth = (GLfloat)1.0*float(2 * S2v - S3v) / (Svmax + 5);
			sixth = (GLfloat)1.0*float(S3v - S1v) / (Svmax + 5);



		}
		else
		{
			if (2 * S2v < S3v)
			{
				S3v = S2v * 2;

			}
			if (S2v < S1v)
			{
				S1v = S2v;
			}


			first = (GLfloat)1.0*float(S3v - S2v) / (Svmax + 5);
			second = (GLfloat)1.0*float(S2v - S1v) / (Svmax + 5);
			third = (GLfloat)1.0*float(S1v) / (Svmax + 5);
			forth = (GLfloat)1.0*float(S2v) / (Svmax + 5);
			fifth = (GLfloat)1.0*float(2 * S2v - S3v) / (Svmax + 5);
			sixth = (GLfloat)1.0*float(S3v - S1v) / (Svmax + 5);







		}


		S1v = S1vb;
		S2v = S2vb;
		S3v = S3vb;

	}
	else if (Rod_like == -1)
	{
		int S1vb = S1v;
		int S2vb = S2v;

		if (S3v < S2v)
		{
			S2v = S3v;
		}
		if (S2v < S1v)
		{
			S1v = S2v;
		}
		if (2 * S1v < S2v)
		{
			S2v = 2 * S1v;

		}


		first = (GLfloat)1.0*float(S3v - S2v) / (Svmax + 5);
		second = (GLfloat)1.0*float(S2v - S1v) / (Svmax + 5);
		third = (GLfloat)1.0*float(S1v) / (Svmax + 5);


		sixth = (GLfloat)1.0*float(S3v - S1v) / (Svmax + 5);

		eighth = (GLfloat)1.0*float(S3v) / (Svmax + 5);



		S1v = S1vb;
		S2v = S2vb;

	}
	else if (Right_Hexagonal == -1)
	{
		int S1vb = S1v;
		int S2vb = S2v;


		S1v = S1vb;
		S2v = S2vb;

	}
	else if (Scase == 1)
	{
		first = (GLfloat)1.0*float(S3v - S2v) / (Svmax + 5);
		second = (GLfloat)1.0*float(S2v - S1v) / (Svmax + 5);
		third = (GLfloat)1.0*float(S1v) / (Svmax + 5);

		fifth = (GLfloat)1.0*float(2 * S2v - S3v) / (Svmax + 5);


	}
	else if (Scase == 2)
	{

		second = (GLfloat)1.0*float(S2v - S1v) / (Svmax + 5);
		third = (GLfloat)1.0*float(S1v) / (Svmax + 5);
		forth = (GLfloat)1.0*float(S2v) / (Svmax + 5);


		seventh = (GLfloat)1.0*float(S2v) / 2 / (Svmax + 5);
	}
	else if (Scase == 3)
	{


		third = (GLfloat)1.0*float(S1v) / (Svmax + 5);


		sixth = (GLfloat)1.0*float(S3v - S1v) / (Svmax + 5);
		nineth = (GLfloat)1.0*float(S3v - 2 * S1v) / (Svmax + 5);
		tenth = (GLfloat)1.0*float((S1v)) / (Svmax + 5);


	}
	else if (Scase == 4)
	{


		third = (GLfloat)1.0*float(S1v) / (Svmax + 5);




	}
	else if (Scase == 5)
	{
		first = (GLfloat)1.0*float(S3v - S2v) / (Svmax + 5);


		forth = (GLfloat)1.0*float(S2v) / (Svmax + 5);
		fifth = (GLfloat)1.0*float(2 * S2v - S3v) / (Svmax + 5);


	}
	else if (Scase == 6)
	{
		first = (GLfloat)1.0*float(S3v - S2v) / (Svmax + 5);


		forth = (GLfloat)1.0*float(S2v) / (Svmax + 5);

		eleventh = 1.0*float(S2v) / ((Svmax + 5) * 2);



	}
	else if (Scase == 7)
	{






		eighth = (GLfloat)1.05*float(S3v) / (Svmax + 5);
	}
	else if (Scase == 0)
	{
		first = (GLfloat)1.0*float(S3v - S2v) / (Svmax + 5);
		second = (GLfloat)1.0*float(S2v - S1v) / (Svmax + 5);
		third = (GLfloat)1.0*float(S1v) / (Svmax + 5);
		forth = (GLfloat)1.0*float(S2v) / (Svmax + 5);
		fifth = (GLfloat)1.0*float(2 * S2v - S3v) / (Svmax + 5);
		sixth = (GLfloat)1.0*float(S3v - S1v) / (Svmax + 5);
		seventh = (GLfloat)1.0*float(S2v) / 2 / (Svmax + 5);
		eighth = (GLfloat)1.0*float(S3v) / (Svmax + 5);
	}


}

void menuf(int c)
{
	if (c == 0)
	{
		BuildPoscar(NewPC);
	}
	if (c == 1)
	{

		if (perspective_on)
		{
			truepointsize = 1000.0;
			pointsize = truepointsize / (Svmax + 5);
			glPointSize(pointsize);

			perspective_on = 0;
			glViewport(0, 0, width, height);//(first 2 sets the lower left corner of the window w h sets width height of the window
			glMatrixMode(GL_PROJECTION);// defines the camera behavior projection is the view point of me
			glLoadIdentity();
			if (width <= height)
			{
				glOrtho(
					-1.05, +1.05,
					-1.05 * (GLfloat)height / (GLfloat)width, +1.05 * (GLfloat)height / (GLfloat)width,
					-10.0, 10.0);
				dipleft = -1;


			}
			else
			{
				glOrtho(
					-1.05 * (GLfloat)width / (GLfloat)height, +1.05 * (GLfloat)width / (GLfloat)height,
					-1.05, +1.05,
					-10.0, 10.0);
				dipleft = -(GLfloat)width / (GLfloat)height;

			}
			glMatrixMode(GL_MODELVIEW);


		}
		else
		{
			perspective_on = 1;

			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			//gluPerspective(60, (float)width / (float)height, 0.001, 100);
			glMatrixMode(GL_MODELVIEW);
			truepointsize = 1000.0;
			pointsize = truepointsize / (Svmax + 5);
			glPointSize(pointsize);

		}

		
	}

	JGN_PostRedisplay();
}

void Sub_Menu(int c)
{
	if (c == 1)
	{
		Rod_like = 1;
		figure_1 = 1;
		Right_Hexagonal = -1 ;
		Svmax = 50;
		S1v = 25;
		S2v = 35;
		S1i[0] = 1;
		S2i[0] = 1;
		S3i[0] = 0;
		S1 = "100";
		S2 = "110";
		S3 = "000";

	}
	if (c == 2)
	{
		Right_Hexagonal = 1;
		figure_1 = 1;
		Rod_like = -1;
		Svmax = 50;
		S1v = 11;
		S2v = 17;
		S3v = 23;
		S1i[0] = 1;
		S2i[0] = 1;
		S3i[0] = 1;
		S1 = "100";
		S2 = "110";
		S3 = "111";
	}
	if (c == 3)
	{
		figure_1 = -1;
		Right_Hexagonal = 1;
		Rod_like = 1;
		Svmax = 50;
		S1v = 15;
		S2v = 30;
		S3v = 40;
		S1i[0] = 1;
		S2i[0] = 1;
		S3i[0] = 1;
		S1 = "100";
		S2 = "110";
		S3 = "111";

	}

	JGN_PostRedisplay();


}


void mouse_pasive(int x, int y)
{
	if (lmb == JGN_UP)
	{

		theta_prev[0] = -theta[0];
		theta_prev[1] = -theta[1];
		
		mouse_check = 0;
		mouse_x = x;
		mouse_y = y;
	}
	else
	{
		if (mouse_check == 0)
		{
			theta_start[0] = y*0.2 + theta_prev[0];
			theta_start[1] = 0.2*x + theta_prev[1];
		}
		mouse_check = 1;

		theta[0] = y*.2 - theta_start[0];
		theta[1] = x*.2 - theta_start[1];

		JGN_PostRedisplay();
	}
}


void mouse_func(int b, int s, int x, int y)
{
	if (b == JGN_LEFT_MOUSE_BUTTON)
	{
		lmb = s;
	}
	

	if (b == JGN_MOUSE_WHEEL && s == JGN_UP)//zoom out
	{
		Svmax = Svmax - 5;
		if (Svmax < 0)
		{
			Svmax = 0;
		}
		pointsize = truepointsize/(Svmax + 5);

	}
	else if (b == JGN_MOUSE_WHEEL)//zoom in
	{

		Svmax = Svmax + 5;

		pointsize = truepointsize/(Svmax + 5);


	}




	lines_param();



	//cout << Svmax << endl;
	JGN_PostRedisplay();

}




