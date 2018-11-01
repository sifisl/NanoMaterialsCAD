#define JGN_COMMANDS_CPP


#include "stdafx.h"
#include "JGN_Windows.h"
#include "JGN_Commands.h"

#include <omp.h>
#include <cuda_runtime.h>
#include <device_launch_parameters.h>


void jgnCommands(LPTSTR ttt, int d)
{
	
	FILE* periodic_table;
	int isngtv = 0;
	//char *test1 = "Vector(";
	for (i = 0; i < 7; i++)
	{
		if (test1[0][i] == ttt[i])
		{

		}
		else
		{
			i = 100;

		}
	}
	if (i == 7)
	{

		okrender = 1;
		CustomSurfacesCount++;

		CustomSurfaces = (float**)realloc(CustomSurfaces, sizeof(float*)*CustomSurfacesCount);
		CustomSurfaces[CustomSurfacesCount - 1] = (float*)malloc(sizeof(float) * 4);
		CustomSurfaces[CustomSurfacesCount - 1][0] = 0;
		CustomSurfaces[CustomSurfacesCount - 1][1] = 0;
		CustomSurfaces[CustomSurfacesCount - 1][2] = 0;
		CustomSurfaces[CustomSurfacesCount - 1][3] = 0;
		help = (char*)(ttt + 7);
		if (help[0] >= 48 && help[0] <= 57)
		{
			crystalh = help[0] - 48;
		}
		else if (help[0] == '-')
		{
			isngtv = 1;
		}
		else
		{
			okrender = 0;
			return;
		}
		help = help + 2;
		loop = 0;
		while (help[0] != ',' && loop < 6)
		{
			loop++;
			if (help[0] >= 48 && help[0] <= 57)
			{
				crystalh = 10 * crystalh + help[0] - 48;
				help += 2;
			}
			else
			{
				okrender = 0;
				return;

			}
		}
		loop = 0;
		if (isngtv)
		{
			crystalh = -crystalh;
		}

		CustomSurfaces[CustomSurfacesCount - 1][0] += ijk[0][0] * crystalh;
		CustomSurfaces[CustomSurfacesCount - 1][1] += ijk[0][1] * crystalh;
		CustomSurfaces[CustomSurfacesCount - 1][2] += ijk[0][2] * crystalh;

		help += 2;
		isngtv = 0;


		if (help[0] >= 48 && help[0] <= 57)
		{
			crystalk = help[0] - 48;
		}
		else if (help[0] == '-')
		{
			isngtv = 1;
		}
		else
		{
			okrender = 0;
			return;
		}
		help = help + 2;
		while (help[0] != ',' && loop < 6)

		{
			loop++;
			if (help[0] >= 48 && help[0] <= 57)
			{
				crystalk = 10 * crystalk + help[0] - 48;
				help += 2;
			}
			else
			{
				okrender = 0;
				return;

			}
		}
		loop = 0;
		if (isngtv)
		{
			crystalk = -crystalk;
		}
		help += 2;
		isngtv = 0;

		CustomSurfaces[CustomSurfacesCount - 1][0] += ijk[1][0] * crystalk;
		CustomSurfaces[CustomSurfacesCount - 1][1] += ijk[1][1] * crystalk;
		CustomSurfaces[CustomSurfacesCount - 1][2] += ijk[1][2] * crystalk;

		if (help[0] >= 48 && help[0] <= 57)
		{
			crystall = help[0] - 48;
		}
		else if (help[0] == '-')
		{
			isngtv = 1;
		}
		else
		{
			okrender = 0;
			return;
		}
		help = help + 2;
		loop = 0;
		while (help[0] != ',' && loop < 6)

		{
			loop++;
			if (help[0] >= 48 && help[0] <= 57)
			{
				crystall = 10 * crystall + help[0] - 48;
				help += 2;
			}
			else
			{
				okrender = 0;
				return;
			}
		}
		loop = 0;
		if (isngtv)
		{
			crystall = -crystall;
		}

		CustomSurfaces[CustomSurfacesCount - 1][0] += ijk[2][0] * crystall;
		CustomSurfaces[CustomSurfacesCount - 1][1] += ijk[2][1] * crystall;
		CustomSurfaces[CustomSurfacesCount - 1][2] += ijk[2][2] * crystall;

		helping1 = CustomSurfaces[CustomSurfacesCount - 1][0];
		helping2 = CustomSurfaces[CustomSurfacesCount - 1][1];
		helping3 = CustomSurfaces[CustomSurfacesCount - 1][2];

		CustomSurfaces[CustomSurfacesCount - 1][0] = CustomSurfaces[CustomSurfacesCount - 1][0] / sqrt(pow(helping1, 2) + pow(helping2, 2) + pow(helping3, 2));
		CustomSurfaces[CustomSurfacesCount - 1][1] = CustomSurfaces[CustomSurfacesCount - 1][1] / sqrt(pow(helping1, 2) + pow(helping2, 2) + pow(helping3, 2));
		CustomSurfaces[CustomSurfacesCount - 1][2] = CustomSurfaces[CustomSurfacesCount - 1][2] / sqrt(pow(helping1, 2) + pow(helping2, 2) + pow(helping3, 2));

		help += 2;
		isngtv = 0;



		if (help[0] >= 48 && help[0] <= 57)
		{
			CustomSurfaces[CustomSurfacesCount - 1][3] = help[0] - 48;
		}
		else if (help[0] == '-')
		{
			isngtv = 1;
		}
		else
		{
			okrender = 0;
			return;

		}
		help = help + 2;
		while (help[0] != ')' && loop < 6)

		{
			loop++;
			if (help[0] >= 48 && help[0] <= 57)
			{
				CustomSurfaces[CustomSurfacesCount - 1][3] = 10 * CustomSurfaces[CustomSurfacesCount - 1][3] + help[0] - 48;
				help += 2;
			}
			else
			{
				okrender = 0;
				return;
			}
		}
		loop = 0;
		if (isngtv)
		{
			CustomSurfaces[CustomSurfacesCount - 1][3] = -CustomSurfaces[CustomSurfacesCount - 1][3];
		}
		help += 2;
		isngtv = 0;


		if (okrender == 0)
		{
			CustomSurfacesCount--;
		}

		goto peintit;


	}
	//render on/off
	for (i = 0; i < 6; i++)
	{
		if (test1[9][i] == ttt[i])
		{

		}
		else
		{
			i = 100;
		}
	}
	if (i == 6)
	{
		okrender = 1;
		help = (char*)(ttt + 7);

		jgn::string option = LPTSTR2string((LPTSTR)help, ')', 2);

		if (option == "on")
		{
			render_is_on = true;
		}
		else if (option == "of")
		{
			render_is_on = false;
		}
		else
		{
			okrender = 0;
			return;
		}
		goto peintit;

	}
	//"rand("
	for (i = 0; i < 5; i++)
	{
		if (test1[8][i] == ttt[i])
		{

		}
		else
		{
			i = 100;
		}
	}
	if (i == 5)
	{
		okrender = 1;

		float r = 0;

		help = (char*)(ttt + 5);

		jgn::string rstr = LPTSTR2string((LPTSTR)help, ')');

		if (rstr.isnumber())
		{
			ole = t * sized[0] * sized[1] * sized[2];

			r = stof(rstr);
			srand(time(NULL));
#pragma omp parallel for firstprivate(ole, r)
			for (int ole1 = 0; ole1 < ole; ole1++)
			{
				crystal[2 + 5 * ole1] += r * (2 * (rand() / (float)RAND_MAX) - 1);
				crystal[3 + 5 * ole1] += r * (2 * (rand() / (float)RAND_MAX) - 1);
				crystal[4 + 5 * ole1] += r * (2 * (rand() / (float)RAND_MAX) - 1);
			}
		}
		else
		{
			okrender = 0;
			return;
		}

		goto peintit;

	}
	//"Plane("
	for (i = 0; i < 6; i++)
	{
		if (test1[4][i] == ttt[i])
		{

		}
		else
		{
			i = 100;
		}
	}
	if (i == 6)
	{

		okrender = 1;
		CustomSurfacesCount++;

		CustomSurfaces = (float**)realloc(CustomSurfaces, sizeof(float*)*CustomSurfacesCount);
		CustomSurfaces[CustomSurfacesCount - 1] = (float*)malloc(sizeof(float) * 4);
		CustomSurfaces[CustomSurfacesCount - 1][0] = 0;
		CustomSurfaces[CustomSurfacesCount - 1][1] = 0;
		CustomSurfaces[CustomSurfacesCount - 1][2] = 0;
		CustomSurfaces[CustomSurfacesCount - 1][3] = 0;
		crystalh = 0;
		crystalk = 0;
		crystall = 0;
		help = (char*)(ttt + 6);
		if (help[0] >= 48 && help[0] <= 57)
		{
			crystalh = help[0] - 48;
		}
		else if (help[0] == '-')
		{
			isngtv = 1;
		}
		else
		{
			okrender = 0;
			return;
		}
		help = help + 2;
		loop = 0;
		while (help[0] != ',' && loop < 6)
		{
			loop++;
			if (help[0] >= 48 && help[0] <= 57)
			{
				crystalh = 10 * crystalh + help[0] - 48;
				help += 2;
			}
			else
			{
				okrender = 0;
				return;


			}
		}
		loop = 0;
		if (isngtv)
		{
			crystalh = -crystalh;
		}




		help += 2;
		isngtv = 0;


		if (help[0] >= 48 && help[0] <= 57)
		{
			crystalk = help[0] - 48;
		}
		else if (help[0] == '-')
		{
			isngtv = 1;
		}
		else
		{
			okrender = 0;
			return;

		}
		help = help + 2;
		while (help[0] != ',' && loop < 6)

		{
			loop++;
			if (help[0] >= 48 && help[0] <= 57)
			{
				crystalk = 10 * crystalk + help[0] - 48;
				help += 2;
			}
			else
			{
				okrender = 0;
				return;

			}
		}
		loop = 0;
		if (isngtv)
		{
			crystalk = -crystalk;
		}
		help += 2;
		isngtv = 0;





		if (help[0] >= 48 && help[0] <= 57)
		{
			crystall = help[0] - 48;
		}
		else if (help[0] == '-')
		{
			isngtv = 1;
		}
		else
		{
			okrender = 0;
			return;
		}
		help = help + 2;
		loop = 0;
		while (help[0] != ',' && loop < 6)

		{
			loop++;
			if (help[0] >= 48 && help[0] <= 57)
			{
				crystall = 10 * crystall + help[0] - 48;
				help += 2;
			}
			else
			{
				okrender = 0;
				return;

			}
		}
		loop = 0;
		if (isngtv)
		{
			crystall = -crystall;
		}

		if (crystalh == 0)
		{
			if (crystalk == 0)
			{
				if (crystall == 0)//000 ok
				{
					CustomSurfacesCount--;
					okrender = 0;
					return;
				}
				else//00l ok
				{
					CustomSurfaces[CustomSurfacesCount - 1][0] = ijk[0][1] * ijk[1][2] - ijk[0][2] * ijk[1][1];
					CustomSurfaces[CustomSurfacesCount - 1][1] = -ijk[0][0] * ijk[1][2] + ijk[0][2] * ijk[1][0];
					CustomSurfaces[CustomSurfacesCount - 1][2] = ijk[0][0] * ijk[1][1] - ijk[0][1] * ijk[1][0];


					CustomSurfaces[CustomSurfacesCount - 1][0] = crystall * CustomSurfaces[CustomSurfacesCount - 1][0];
					CustomSurfaces[CustomSurfacesCount - 1][1] = crystall * CustomSurfaces[CustomSurfacesCount - 1][1];
					CustomSurfaces[CustomSurfacesCount - 1][2] = crystall * CustomSurfaces[CustomSurfacesCount - 1][2];

				}
			}
			else
			{
				if (crystall == 0)//0k0 ok
				{
					CustomSurfaces[CustomSurfacesCount - 1][0] = -ijk[0][1] * ijk[2][2] + ijk[0][2] * ijk[2][1];
					CustomSurfaces[CustomSurfacesCount - 1][1] = ijk[0][0] * ijk[2][2] - ijk[0][2] * ijk[2][0];
					CustomSurfaces[CustomSurfacesCount - 1][2] = -ijk[0][0] * ijk[2][1] + ijk[0][1] * ijk[2][0];

					CustomSurfaces[CustomSurfacesCount - 1][0] = crystalk * CustomSurfaces[CustomSurfacesCount - 1][0];
					CustomSurfaces[CustomSurfacesCount - 1][1] = crystalk * CustomSurfaces[CustomSurfacesCount - 1][1];
					CustomSurfaces[CustomSurfacesCount - 1][2] = crystalk * CustomSurfaces[CustomSurfacesCount - 1][2];

				}
				else//0kl ok
				{
					CustomSurfaces[CustomSurfacesCount - 1][0] = ijk[0][1] * (ijk[1][2] / crystalk - ijk[2][2] / crystall) - ijk[0][2] * (ijk[1][1] / crystalk - ijk[2][1] / crystall);
					CustomSurfaces[CustomSurfacesCount - 1][1] = -ijk[0][0] * (ijk[1][2] / crystalk - ijk[2][2] / crystall) + ijk[0][2] * (ijk[1][0] / crystalk - ijk[2][0] / crystall);
					CustomSurfaces[CustomSurfacesCount - 1][2] = ijk[0][0] * (ijk[1][1] / crystalk - ijk[2][1] / crystall) - ijk[0][1] * (ijk[1][0] / crystalk - ijk[2][0] / crystall);

					CustomSurfaces[CustomSurfacesCount - 1][0] = crystalk * crystall*CustomSurfaces[CustomSurfacesCount - 1][0];
					CustomSurfaces[CustomSurfacesCount - 1][1] = crystalk * crystall*CustomSurfaces[CustomSurfacesCount - 1][1];
					CustomSurfaces[CustomSurfacesCount - 1][2] = crystalk * crystall*CustomSurfaces[CustomSurfacesCount - 1][2];
				}
			}
		}
		else
		{
			if (crystalk == 0)
			{
				if (crystall == 0)//h00 ok
				{
					CustomSurfaces[CustomSurfacesCount - 1][0] = ijk[1][1] * ijk[2][2] - ijk[1][2] * ijk[2][1];
					CustomSurfaces[CustomSurfacesCount - 1][1] = -ijk[1][0] * ijk[2][2] + ijk[1][2] * ijk[2][0];
					CustomSurfaces[CustomSurfacesCount - 1][2] = ijk[1][0] * ijk[2][1] - ijk[1][1] * ijk[2][0];

					CustomSurfaces[CustomSurfacesCount - 1][0] = crystalh * CustomSurfaces[CustomSurfacesCount - 1][0];
					CustomSurfaces[CustomSurfacesCount - 1][1] = crystalh * CustomSurfaces[CustomSurfacesCount - 1][1];
					CustomSurfaces[CustomSurfacesCount - 1][2] = crystalh * CustomSurfaces[CustomSurfacesCount - 1][2];

				}
				else//h0l ok
				{


					CustomSurfaces[CustomSurfacesCount - 1][0] = ijk[1][1] * (ijk[0][2] / crystalh - ijk[2][2] / crystall) - ijk[1][2] * (ijk[0][1] / crystalh - ijk[2][1] / crystall);
					CustomSurfaces[CustomSurfacesCount - 1][1] = -ijk[1][0] * (ijk[0][2] / crystalh - ijk[2][2] / crystall) + ijk[1][2] * (ijk[0][0] / crystalh - ijk[2][0] / crystall);
					CustomSurfaces[CustomSurfacesCount - 1][2] = ijk[1][0] * (ijk[0][1] / crystalh - ijk[2][1] / crystall) - ijk[1][1] * (ijk[0][0] / crystalh - ijk[2][0] / crystall);

					CustomSurfaces[CustomSurfacesCount - 1][0] = -crystalh * crystall*CustomSurfaces[CustomSurfacesCount - 1][0];
					CustomSurfaces[CustomSurfacesCount - 1][1] = -crystalh * crystall*CustomSurfaces[CustomSurfacesCount - 1][1];
					CustomSurfaces[CustomSurfacesCount - 1][2] = -crystalh * crystall*CustomSurfaces[CustomSurfacesCount - 1][2];


				}
			}
			else
			{
				if (crystall == 0)//hk0 ok
				{
					CustomSurfaces[CustomSurfacesCount - 1][0] = ijk[2][1] * (ijk[0][2] / crystalh - ijk[1][2] / crystalk) - ijk[2][2] * (ijk[0][1] / crystalh - ijk[1][1] / crystalk);
					CustomSurfaces[CustomSurfacesCount - 1][1] = -ijk[2][0] * (ijk[0][2] / crystalh - ijk[1][2] / crystalk) + ijk[2][2] * (ijk[0][0] / crystalh - ijk[1][0] / crystalk);
					CustomSurfaces[CustomSurfacesCount - 1][2] = ijk[2][0] * (ijk[0][1] / crystalh - ijk[1][1] / crystalk) - ijk[2][1] * (ijk[0][0] / crystalh - ijk[1][0] / crystalk);

					CustomSurfaces[CustomSurfacesCount - 1][0] = crystalk * crystalh*CustomSurfaces[CustomSurfacesCount - 1][0];
					CustomSurfaces[CustomSurfacesCount - 1][1] = crystalk * crystalh*CustomSurfaces[CustomSurfacesCount - 1][1];
					CustomSurfaces[CustomSurfacesCount - 1][2] = crystalk * crystalh*CustomSurfaces[CustomSurfacesCount - 1][2];
				}
				else//hkl
				{
					CustomSurfaces[CustomSurfacesCount - 1][0] = (ijk[0][1] / crystalh - ijk[2][1] / crystall) * (ijk[0][2] / crystalh - ijk[1][2] / crystalk) - (ijk[0][2] / crystalh - ijk[2][2] / crystall) * (ijk[0][1] / crystalh - ijk[1][1] / crystalk);
					CustomSurfaces[CustomSurfacesCount - 1][1] = -(ijk[0][0] / crystalh - ijk[2][0] / crystall) * (ijk[0][2] / crystalh - ijk[1][2] / crystalk) + (ijk[0][2] / crystalh - ijk[2][2] / crystall) * (ijk[0][0] / crystalh - ijk[1][0] / crystalk);
					CustomSurfaces[CustomSurfacesCount - 1][2] = (ijk[0][0] / crystalh - ijk[2][0] / crystall) * (ijk[0][1] / crystalh - ijk[1][1] / crystalk) - (ijk[0][1] / crystalh - ijk[2][1] / crystall) * (ijk[0][0] / crystalh - ijk[1][0] / crystalk);

					CustomSurfaces[CustomSurfacesCount - 1][0] = -crystall * crystalk*crystalh*CustomSurfaces[CustomSurfacesCount - 1][0];
					CustomSurfaces[CustomSurfacesCount - 1][1] = -crystall * crystalk*crystalh*CustomSurfaces[CustomSurfacesCount - 1][1];
					CustomSurfaces[CustomSurfacesCount - 1][2] = -crystall * crystalk*crystalh*CustomSurfaces[CustomSurfacesCount - 1][2];

				}
			}
		}



		/*if (crystalh == 0)
		{
		if (JGN_Det3x3(ijk[0][0], ijk[0][1], ijk[0][2], ijk[0][2], 0, -ijk[0][0], ijk[0][1], -ijk[0][0], 0) != 0)
		{
		CustomSurfaces[CustomSurfacesCount - 1][0] = JGN_Det3x3(0, ijk[0][1], ijk[0][2], helping1*ijk[0][2] - helping3*ijk[0][0], 0, -ijk[0][0], helping1*ijk[0][1] - helping2*ijk[0][0], -ijk[0][0], 0) / JGN_Det3x3(ijk[0][0], ijk[0][1], ijk[0][2], ijk[0][2], 0, -ijk[0][0], ijk[0][1], -ijk[0][0], 0);
		CustomSurfaces[CustomSurfacesCount - 1][1] = JGN_Det3x3(ijk[0][0], 0, ijk[0][2], ijk[0][2], helping1*ijk[0][2] - helping3*ijk[0][0] , -ijk[0][0], ijk[0][1], helping1*ijk[0][1] - helping2*ijk[0][0], 0) / JGN_Det3x3(ijk[0][0], ijk[0][1], ijk[0][2], ijk[0][2], 0, -ijk[0][0], ijk[0][1], -ijk[0][0], 0);
		CustomSurfaces[CustomSurfacesCount - 1][2] = JGN_Det3x3(ijk[0][0], ijk[0][1], 0, ijk[0][2], 0, helping1*ijk[0][2] - helping3*ijk[0][0] , ijk[0][1], -ijk[0][0], helping1*ijk[0][1] - helping2*ijk[0][0]) / JGN_Det3x3(ijk[0][0], ijk[0][1], ijk[0][2], ijk[0][2], 0, -ijk[0][0], ijk[0][1], -ijk[0][0], 0);
		}
		else if (JGN_Det3x3(0, ijk[0][2], -ijk[0][1], ijk[0][0], ijk[0][1], ijk[0][2], ijk[0][1], -ijk[0][0], 0) != 0)
		{
		CustomSurfaces[CustomSurfacesCount - 1][0] = JGN_Det3x3(helping2*ijk[0][2]-helping3*ijk[0][1], ijk[0][2], -ijk[0][1], 0, ijk[0][1], ijk[0][2], helping1*ijk[0][1]-helping2*ijk[0][0], -ijk[0][0], 0) / JGN_Det3x3(0, ijk[0][2], -ijk[0][1], ijk[0][0], ijk[0][1], ijk[0][2], ijk[0][1], -ijk[0][0], 0);
		CustomSurfaces[CustomSurfacesCount - 1][1] = JGN_Det3x3(0, helping2*ijk[0][2] - helping3*ijk[0][1], -ijk[0][1], ijk[0][0], 0, ijk[0][2], ijk[0][1], helping1*ijk[0][1] - helping2*ijk[0][0] , 0) / JGN_Det3x3(0, ijk[0][2], -ijk[0][1], ijk[0][0], ijk[0][1], ijk[0][2], ijk[0][1], -ijk[0][0], 0);
		CustomSurfaces[CustomSurfacesCount - 1][2] = JGN_Det3x3(0, ijk[0][2], helping2*ijk[0][2] - helping3*ijk[0][1], ijk[0][0], ijk[0][1], 0, ijk[0][1], -ijk[0][0], helping1*ijk[0][1] - helping2*ijk[0][0]) / JGN_Det3x3(0, ijk[0][2], -ijk[0][1], ijk[0][0], ijk[0][1], ijk[0][2], ijk[0][1], -ijk[0][0], 0);
		}
		else if (JGN_Det3x3(0, ijk[0][2], -ijk[0][1], ijk[0][2], 0, -ijk[0][0], ijk[0][0], ijk[0][1], ijk[0][2]) != 0)
		{
		CustomSurfaces[CustomSurfacesCount - 1][0] = JGN_Det3x3(helping2*ijk[0][2] - helping3*ijk[0][1], ijk[0][2], -ijk[0][1], helping1*ijk[0][2] - helping3*ijk[0][0], 0, -ijk[0][0], 0, ijk[0][1], ijk[0][2]) / JGN_Det3x3(0, ijk[0][2], -ijk[0][1], ijk[0][2], 0, -ijk[0][0], ijk[0][0], ijk[0][1], ijk[0][2]);
		CustomSurfaces[CustomSurfacesCount - 1][1] = JGN_Det3x3(0, helping2*ijk[0][2] - helping3*ijk[0][1], -ijk[0][1], ijk[0][2], helping1*ijk[0][2] - helping3*ijk[0][0], -ijk[0][0], ijk[0][0], 0, ijk[0][2]) / JGN_Det3x3(0, ijk[0][2], -ijk[0][1], ijk[0][2], 0, -ijk[0][0], ijk[0][0], ijk[0][1], ijk[0][2]);
		CustomSurfaces[CustomSurfacesCount - 1][2] = JGN_Det3x3(0, ijk[0][2], helping2*ijk[0][2] - helping3*ijk[0][1], ijk[0][2], 0, helping1*ijk[0][2] - helping3*ijk[0][0], ijk[0][0], ijk[0][1], 0) / JGN_Det3x3(0, ijk[0][2], -ijk[0][1], ijk[0][2], 0, -ijk[0][0], ijk[0][0], ijk[0][1], ijk[0][2]);
		}

		}

		helping1 = CustomSurfaces[CustomSurfacesCount - 1][0];
		helping2 = CustomSurfaces[CustomSurfacesCount - 1][1];
		helping3 = CustomSurfaces[CustomSurfacesCount - 1][2];

		if (crystalk == 0)
		{
		if (JGN_Det3x3(ijk[1][0], ijk[1][1], ijk[1][2], ijk[1][2], 0, -ijk[1][0], ijk[1][1], -ijk[1][0], 0) != 0)
		{
		CustomSurfaces[CustomSurfacesCount - 1][0] = JGN_Det3x3(0, ijk[1][1], ijk[1][2], helping1*ijk[1][2] - helping3*ijk[1][0], 0, -ijk[1][0], helping1*ijk[1][1] - helping2*ijk[1][0], -ijk[1][0], 0) / JGN_Det3x3(ijk[1][0], ijk[1][1], ijk[1][2], ijk[1][2], 0, -ijk[1][0], ijk[1][1], -ijk[1][0], 0);
		CustomSurfaces[CustomSurfacesCount - 1][1] = JGN_Det3x3(ijk[1][0], 0, ijk[1][2], ijk[1][2], helping1*ijk[1][2] - helping3*ijk[1][0], -ijk[1][0], ijk[1][1], helping1*ijk[1][1] - helping2*ijk[1][0], 0) / JGN_Det3x3(ijk[1][0], ijk[1][1], ijk[1][2], ijk[1][2], 0, -ijk[1][0], ijk[1][1], -ijk[1][0], 0);
		CustomSurfaces[CustomSurfacesCount - 1][2] = JGN_Det3x3(ijk[1][0], ijk[1][1], 0, ijk[1][2], 0, helping1*ijk[1][2] - helping3*ijk[1][0], ijk[1][1], -ijk[1][0], helping1*ijk[1][1] - helping2*ijk[1][0]) / JGN_Det3x3(ijk[1][0], ijk[1][1], ijk[1][2], ijk[1][2], 0, -ijk[1][0], ijk[1][1], -ijk[1][0], 0);
		}
		else if (JGN_Det3x3(0, ijk[1][2], -ijk[1][1], ijk[1][0], ijk[1][1], ijk[1][2], ijk[1][1], -ijk[1][0], 0) != 0)
		{
		CustomSurfaces[CustomSurfacesCount - 1][0] = JGN_Det3x3(helping2*ijk[1][2] - helping3*ijk[1][1], ijk[1][2], -ijk[1][1], 0, ijk[1][1], ijk[1][2], helping1*ijk[1][1] - helping2*ijk[1][0], -ijk[1][0], 0) / JGN_Det3x3(0, ijk[1][2], -ijk[1][1], ijk[1][0], ijk[1][1], ijk[1][2], ijk[1][1], -ijk[1][0], 0);
		CustomSurfaces[CustomSurfacesCount - 1][1] = JGN_Det3x3(0, helping2*ijk[1][2] - helping3*ijk[1][1], -ijk[1][1], ijk[1][0], 0, ijk[1][2], ijk[1][1], helping1*ijk[1][1] - helping2*ijk[1][0], 0) / JGN_Det3x3(0, ijk[1][2], -ijk[1][1], ijk[1][0], ijk[1][1], ijk[1][2], ijk[1][1], -ijk[1][0], 0);
		CustomSurfaces[CustomSurfacesCount - 1][2] = JGN_Det3x3(0, ijk[1][2], helping2*ijk[1][2] - helping3*ijk[1][1], ijk[1][0], ijk[1][1], 0, ijk[1][1], -ijk[1][0], helping1*ijk[1][1] - helping2*ijk[1][0]) / JGN_Det3x3(0, ijk[1][2], -ijk[1][1], ijk[1][0], ijk[1][1], ijk[1][2], ijk[1][1], -ijk[1][0], 0);
		}
		else if (JGN_Det3x3(0, ijk[1][2], -ijk[1][1], ijk[1][2], 0, -ijk[1][0], ijk[1][0], ijk[1][1], ijk[1][2]) != 0)
		{
		CustomSurfaces[CustomSurfacesCount - 1][0] = JGN_Det3x3(helping2*ijk[1][2] - helping3*ijk[1][1], ijk[1][2], -ijk[1][1], helping1*ijk[1][2] - helping3*ijk[1][0], 0, -ijk[1][0], 0, ijk[1][1], ijk[1][2]) / JGN_Det3x3(0, ijk[1][2], -ijk[1][1], ijk[1][2], 0, -ijk[1][0], ijk[1][0], ijk[1][1], ijk[1][2]);
		CustomSurfaces[CustomSurfacesCount - 1][1] = JGN_Det3x3(0, helping2*ijk[1][2] - helping3*ijk[1][1], -ijk[1][1], ijk[1][2], helping1*ijk[1][2] - helping3*ijk[1][0], -ijk[1][0], ijk[1][0], 0, ijk[1][2]) / JGN_Det3x3(0, ijk[1][2], -ijk[1][1], ijk[1][2], 0, -ijk[1][0], ijk[1][0], ijk[1][1], ijk[1][2]);
		CustomSurfaces[CustomSurfacesCount - 1][2] = JGN_Det3x3(0, ijk[1][2], helping2*ijk[1][2] - helping3*ijk[1][1], ijk[1][2], 0, helping1*ijk[1][2] - helping3*ijk[1][0], ijk[1][0], ijk[1][1], 0) / JGN_Det3x3(0, ijk[1][2], -ijk[1][1], ijk[1][2], 0, -ijk[1][0], ijk[1][0], ijk[1][1], ijk[1][2]);
		}
		}

		helping1 = CustomSurfaces[CustomSurfacesCount - 1][0];
		helping2 = CustomSurfaces[CustomSurfacesCount - 1][1];
		helping3 = CustomSurfaces[CustomSurfacesCount - 1][2];

		if (crystall == 0)
		{
		if (JGN_Det3x3(ijk[2][0], ijk[2][1], ijk[2][2], ijk[2][2], 0, -ijk[2][0], ijk[2][1], -ijk[2][0], 0) != 0)
		{

		CustomSurfaces[CustomSurfacesCount - 1][0] = JGN_Det3x3(0, ijk[2][1], ijk[2][2], helping1*ijk[2][2] - helping3*ijk[2][0], 0, -ijk[2][0], helping1*ijk[2][1] - helping2*ijk[2][0], -ijk[2][0], 0) / JGN_Det3x3(ijk[2][0], ijk[2][1], ijk[2][2], ijk[2][2], 0, -ijk[2][0], ijk[2][1], -ijk[2][0], 0);
		CustomSurfaces[CustomSurfacesCount - 1][1] = JGN_Det3x3(ijk[2][0], 0, ijk[2][2], ijk[2][2], helping1*ijk[2][2] - helping3*ijk[2][0], -ijk[2][0], ijk[2][1], helping1*ijk[2][1] - helping2*ijk[2][0], 0) / JGN_Det3x3(ijk[2][0], ijk[2][1], ijk[2][2], ijk[2][2], 0, -ijk[2][0], ijk[2][1], -ijk[2][0], 0);
		CustomSurfaces[CustomSurfacesCount - 1][2] = JGN_Det3x3(ijk[2][0], ijk[2][1], 0, ijk[2][2], 0, helping1*ijk[2][2] - helping3*ijk[2][0], ijk[2][1], -ijk[2][0], helping1*ijk[2][1] - helping2*ijk[2][0]) / JGN_Det3x3(ijk[2][0], ijk[2][1], ijk[2][2], ijk[2][2], 0, -ijk[2][0], ijk[2][1], -ijk[2][0], 0);
		}
		else if (JGN_Det3x3(0, ijk[2][2], -ijk[2][1], ijk[2][0], ijk[2][1], ijk[2][2], ijk[2][1], -ijk[2][0], 0) != 0)
		{

		CustomSurfaces[CustomSurfacesCount - 1][0] = JGN_Det3x3(helping2*ijk[2][2] - helping3*ijk[2][1], ijk[2][2], -ijk[2][1], 0, ijk[2][1], ijk[2][2], helping1*ijk[2][1] - helping2*ijk[2][0], -ijk[2][0], 0) / JGN_Det3x3(0, ijk[2][2], -ijk[2][1], ijk[2][0], ijk[2][1], ijk[2][2], ijk[2][1], -ijk[2][0], 0);
		CustomSurfaces[CustomSurfacesCount - 1][1] = JGN_Det3x3(0, helping2*ijk[2][2] - helping3*ijk[2][1], -ijk[2][1], ijk[2][0], 0, ijk[2][2], ijk[2][1], helping1*ijk[2][1] - helping2*ijk[2][0], 0) / JGN_Det3x3(0, ijk[2][2], -ijk[2][1], ijk[2][0], ijk[2][1], ijk[2][2], ijk[2][1], -ijk[2][0], 0);
		CustomSurfaces[CustomSurfacesCount - 1][2] = JGN_Det3x3(0, ijk[2][2], helping2*ijk[2][2] - helping3*ijk[2][1], ijk[2][0], ijk[2][1], 0, ijk[2][1], -ijk[2][0], helping1*ijk[2][1] - helping2*ijk[2][0]) / JGN_Det3x3(0, ijk[2][2], -ijk[2][1], ijk[2][0], ijk[2][1], ijk[2][2], ijk[2][1], -ijk[2][0], 0);
		}
		else if (JGN_Det3x3(0, ijk[2][2], -ijk[2][1], ijk[2][2], 0, -ijk[2][0], ijk[2][0], ijk[2][1], ijk[2][2]) != 0)
		{

		CustomSurfaces[CustomSurfacesCount - 1][0] = JGN_Det3x3(helping2*ijk[2][2] - helping3*ijk[2][1], ijk[2][2], -ijk[2][1], helping1*ijk[2][2] - helping3*ijk[2][0], 0, -ijk[2][0], 0, ijk[2][1], ijk[2][2]) / JGN_Det3x3(0, ijk[2][2], -ijk[2][1], ijk[2][2], 0, -ijk[2][0], ijk[2][0], ijk[2][1], ijk[2][2]);
		CustomSurfaces[CustomSurfacesCount - 1][1] = JGN_Det3x3(0, helping2*ijk[2][2] - helping3*ijk[2][1], -ijk[2][1], ijk[2][2], helping1*ijk[2][2] - helping3*ijk[2][0], -ijk[2][0], ijk[2][0], 0, ijk[2][2]) / JGN_Det3x3(0, ijk[2][2], -ijk[2][1], ijk[2][2], 0, -ijk[2][0], ijk[2][0], ijk[2][1], ijk[2][2]);
		CustomSurfaces[CustomSurfacesCount - 1][2] = JGN_Det3x3(0, ijk[2][2], helping2*ijk[2][2] - helping3*ijk[2][1], ijk[2][2], 0, helping1*ijk[2][2] - helping3*ijk[2][0], ijk[2][0], ijk[2][1], 0) / JGN_Det3x3(0, ijk[2][2], -ijk[2][1], ijk[2][2], 0, -ijk[2][0], ijk[2][0], ijk[2][1], ijk[2][2]);
		}
		}*/


		helping1 = CustomSurfaces[CustomSurfacesCount - 1][0];
		helping2 = CustomSurfaces[CustomSurfacesCount - 1][1];
		helping3 = CustomSurfaces[CustomSurfacesCount - 1][2];

		CustomSurfaces[CustomSurfacesCount - 1][0] = CustomSurfaces[CustomSurfacesCount - 1][0] / sqrt(pow(helping1, 2) + pow(helping2, 2) + pow(helping3, 2));
		CustomSurfaces[CustomSurfacesCount - 1][1] = CustomSurfaces[CustomSurfacesCount - 1][1] / sqrt(pow(helping1, 2) + pow(helping2, 2) + pow(helping3, 2));
		CustomSurfaces[CustomSurfacesCount - 1][2] = CustomSurfaces[CustomSurfacesCount - 1][2] / sqrt(pow(helping1, 2) + pow(helping2, 2) + pow(helping3, 2));

		help += 2;
		isngtv = 0;



		if (help[0] >= 48 && help[0] <= 57)
		{
			CustomSurfaces[CustomSurfacesCount - 1][3] = help[0] - 48;
		}
		else if (help[0] == '-')
		{
			isngtv = 1;
		}
		else
		{
			okrender = 0;
			return;
		}
		help = help + 2;
		while (help[0] != ')' && loop < 6)

		{
			loop++;
			if (help[0] >= 48 && help[0] <= 57)
			{
				CustomSurfaces[CustomSurfacesCount - 1][3] = 10 * CustomSurfaces[CustomSurfacesCount - 1][3] + help[0] - 48;
				help += 2;
			}
			else
			{
				okrender = 0;
				return;
			}
		}
		loop = 0;
		if (isngtv)
		{
			CustomSurfaces[CustomSurfacesCount - 1][3] = -CustomSurfaces[CustomSurfacesCount - 1][3];
		}
		help += 2;
		isngtv = 0;


		if (okrender == 0)
		{
			CustomSurfacesCount--;
		}

		goto peintit;


	}



	//"PlaneH("
	/*for (i = 0; i < 7; i++)
	{
	if (test5[i] == ttt[i])
	{

	}
	else
	{
	i = 100;
	}
	}
	if (i == 7)
	{
	okrender = 1;
	CustomSurfacesCount++;

	CustomSurfaces = (float**)realloc(CustomSurfaces, sizeof(float*)*CustomSurfacesCount);
	CustomSurfaces[CustomSurfacesCount - 1] = (float*)malloc(sizeof(float) * 4);
	CustomSurfaces[CustomSurfacesCount - 1][0] = 0;
	CustomSurfaces[CustomSurfacesCount - 1][1] = 0;
	CustomSurfaces[CustomSurfacesCount - 1][2] = 0;
	CustomSurfaces[CustomSurfacesCount - 1][3] = 0;

	int u = 0;
	int v = 0;

	help = (char*)(ttt + 7);
	if (help[0] >= 48 && help[0] <= 57)
	{
	u = help[0] - 48;
	}
	else if (help[0] == '-')
	{
	isngtv = 1;
	}
	else
	{
	okrender = 0;
	}
	help = help + 2;
	loop = 0;
	while (help[0] != ',' && loop<6)
	{
	loop++;
	if (help[0] >= 48 && help[0] <= 57)
	{
	u = 10 * u + help[0] - 48;
	help += 2;
	}
	else
	{
	okrender = 0;


	}
	}
	loop = 0;
	if (isngtv)
	{
	u = -u;
	}
	help += 2;
	isngtv = 0;


	if (help[0] >= 48 && help[0] <= 57)
	{
	v = help[0] - 48;
	}
	else if (help[0] == '-')
	{
	isngtv = 1;
	}
	else
	{
	okrender = 0;

	}
	help = help + 2;
	while (help[0] != ',' && loop<6)

	{
	loop++;
	if (help[0] >= 48 && help[0] <= 57)
	{
	v = 10 * v + help[0] - 48;
	help += 2;
	}
	else
	{
	okrender = 0;


	}
	}
	loop = 0;
	if (isngtv)
	{
	v = -v;
	}
	help += 2;
	isngtv = 0;

	CustomSurfaces[CustomSurfacesCount - 1][0] = u;
	CustomSurfaces[CustomSurfacesCount - 1][1] = u/sqrt(3) + v*2.0 / sqrt(3);

	if (help[0] >= 48 && help[0] <= 57)
	{
	CustomSurfaces[CustomSurfacesCount - 1][2] = help[0] - 48;
	}
	else if (help[0] == '-')
	{
	isngtv = 1;
	}
	else
	{
	okrender = 0;

	}
	help = help + 2;
	while (help[0] != ',' && loop<6)

	{
	loop++;
	if (help[0] >= 48 && help[0] <= 57)
	{
	CustomSurfaces[CustomSurfacesCount - 1][2] = 10 * CustomSurfaces[CustomSurfacesCount - 1][2] + help[0] - 48;
	help += 2;
	}
	else
	{
	okrender = 0;

	}
	}
	loop = 0;
	if (isngtv)
	{
	CustomSurfaces[CustomSurfacesCount - 1][2] = -CustomSurfaces[CustomSurfacesCount - 1][2];
	}
	help += 2;
	isngtv = 0;



	if (help[0] >= 48 && help[0] <= 57)
	{
	CustomSurfaces[CustomSurfacesCount - 1][3] = help[0] - 48;
	}
	else if (help[0] == '-')
	{
	isngtv = 1;
	}
	else
	{
	okrender = 0;

	}
	help = help + 2;
	while (help[0] != ')' && loop<6)

	{
	loop++;
	if (help[0] >= 48 && help[0] <= 57)
	{
	CustomSurfaces[CustomSurfacesCount - 1][3] = 10 * CustomSurfaces[CustomSurfacesCount - 1][3] + help[0] - 48;
	help += 2;
	}
	else
	{
	okrender = 0;

	}
	}
	loop = 0;
	if (isngtv)
	{
	CustomSurfaces[CustomSurfacesCount - 1][3] = -CustomSurfaces[CustomSurfacesCount - 1][3];
	}
	help += 2;
	isngtv = 0;


	if (okrender == 0)
	{
	CustomSurfacesCount--;
	}
	JGN_PostRedisplay();

	goto peintit;

	}*/





	//char *test2 = "Clean";
	for (i = 0; i < 5; i++)
	{
		if (test1[1][i] == ttt[i])
		{

		}
		else
		{
			i = 100;
		}
	}

	if (i == 5)
	{
		okrender = 1;
		CustomSurfacesCount = 0;
		for (i = 0; i < CustomSurfacesCount; i++)
		{
			delete(CustomSurfaces[i]);
		}
		delete(CustomSurfaces);
		CustomSurfaces = NULL;
		goto peintit;



	}

	//char *test3 = "Undo";
	for (i = 0; i < 4; i++)
	{
		if (test1[2][i] == ttt[i])
		{

		}
		else
		{
			i = 100;
		}
	}
	if (i == 4)
	{
		okrender = 1;
		CustomSurfacesCount--;
		if (CustomSurfacesCount < 0)
		{
			CustomSurfacesCount = 0;
		}

		goto peintit;


	}
	//char *test4 = "spheres";
	for (i = 0; i < 7; i++)
	{
		if (test1[6][i] == ttt[i])
		{

		}
		else
		{
			i = 100;
		}
	}
	if (i == 7)
	{
		okrender = 1;
		shperes_on = 1;
		glEnable(GL_LIGHTING);

		sphStacks = 2;
		sphSides = 3;

		goto peintit;

	}

	//char *test4 = "points";
	for (i = 0; i < 6; i++)
	{
		if (test1[7][i] == ttt[i])
		{

		}
		else
		{
			i = 100;
		}
	}
	if (i == 6)
	{
		okrender = 1;
		shperes_on = 0;
		glDisable(GL_LIGHTING);

		goto peintit;

	}

	//char *test4 = "SuperCell(";
	for (i = 0; i < 10; i++)
	{
		if (test1[3][i] == ttt[i])
		{

		}
		else
		{
			i = 100;
		}
	}
	if (i == 10)
	{
		okrender = 1;
		help = (char*)(ttt + 10);
		if (help[0] >= 48 && help[0] <= 57)
		{
			sizedprotector[0] = help[0] - 48;
		}
		else
		{
			okrender = 0;
			return;
		}
		help = help + 2;
		while (help[0] != ',' && loop < 6)
		{
			loop++;
			if (help[0] >= 48 && help[0] <= 57)
			{
				sizedprotector[0] = 10 * sizedprotector[0] + help[0] - 48;
				help += 2;
			}
			else
			{
				okrender = 0;
				return;

			}
		}
		loop = 0;
		help += 2;




		if (help[0] >= 48 && help[0] <= 57)
		{
			sizedprotector[1] = help[0] - 48;
		}
		else
		{
			okrender = 0;
			return;
		}
		help = help + 2;
		while (help[0] != ',' && loop < 6)
		{
			loop++;
			if (help[0] >= 48 && help[0] <= 57)
			{
				sizedprotector[1] = 10 * sizedprotector[1] + help[0] - 48;
				help += 2;
			}
			else
			{
				okrender = 0;
				return;

			}
		}
		loop = 0;
		help += 2;



		if (help[0] >= 48 && help[0] <= 57)
		{
			sizedprotector[2] = help[0] - 48;
		}
		else
		{
			okrender = 0;
			return;
		}
		help = help + 2;
		while (help[0] != ')' && loop < 6)
		{
			loop++;
			if (help[0] >= 48 && help[0] <= 57)
			{
				sizedprotector[2] = 10 * sizedprotector[2] + help[0] - 48;
				help += 2;
			}
			else
			{
				okrender = 0;

				return;
			}
		}
		loop = 0;
		help += 2;



		if (okrender)
		{


			xexe[0] = 0;
			xexe[1] = 0;
			xexe[2] = 0;

			sized[0] = sizedprotector[0];
			sized[1] = sizedprotector[1];
			sized[2] = sizedprotector[2];
			custom_sized[0] = sizedprotector[0];
			custom_sized[1] = sizedprotector[1];
			custom_sized[2] = sizedprotector[2];

			jgn_supercell_xyz[0] = sized[0];
			jgn_supercell_xyz[1] = sized[1];
			jgn_supercell_xyz[2] = sized[2];

			if (sized[0] / 2 != sized[0] / 2.0)
			{
				xexe[0] = 1;
			}

			if (sized[1] / 2 != sized[1] / 2.0)
			{
				xexe[1] = 1;
			}

			if (sized[2] / 2 != sized[2] / 2.0)
			{
				xexe[2] = 1;
			}
			//periodic_table = fopen("periodic_table.jgn", "r");

			crystal = (float*)realloc(NULL, sizeof(float)*(jgn_supercell_xyz[0] * jgn_supercell_xyz[1] * jgn_supercell_xyz[2] * t * 5));
			crystal_backup = (float*)realloc(NULL, sizeof(float)*(jgn_supercell_xyz[0] * jgn_supercell_xyz[1] * jgn_supercell_xyz[2] * t * 5));
			selective_dynamics = (char*)realloc(selective_dynamics, sizeof(char)*(jgn_supercell_xyz[0] * jgn_supercell_xyz[1] * jgn_supercell_xyz[2] * t * 3));

			//	crystal_backup = (float*)realloc(NULL, sizeof(float)*(jgn_supercell_xyz[0] * jgn_supercell_xyz[1] * jgn_supercell_xyz[2] * t * 5));
			//double ttest = omp_get_wtime();

#pragma omp parallel for firstprivate(jgn_supercell_xyz, xexe, my_direct, inptype, uccartesian, ijk, t)
			for (int ole3 = 0; ole3 < t; ole3++) {//for every atom in the unit cell
				for (int ole4 = -jgn_supercell_xyz[2] / 2; ole4 < jgn_supercell_xyz[2] / 2 + xexe[2]; ole4++) {
					for (int ole2 = -jgn_supercell_xyz[1] / 2; ole2 < jgn_supercell_xyz[1] / 2 + xexe[1]; ole2++) {
						for (int ole = -jgn_supercell_xyz[0] / 2; ole < jgn_supercell_xyz[0] / 2 + xexe[0]; ole++) {

							crystal[0 + 5 * (ole3 + t * (ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[0 + 5 * ole3];//atomikos ari8mos
						//	crystal_backup[0 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[0 + 5 * ole3];//atomikos ari8mos
						//selective dynamics
							selective_dynamics[0 + 3 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = selective_dynamics[0 + 3 * (ole3)];
							selective_dynamics[1 + 3 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = selective_dynamics[1 + 3 * (ole3)];
							selective_dynamics[2 + 3 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = selective_dynamics[2 + 3 * (ole3)];

							crystal[1 + 5 * (ole3 + t * (ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[1 + 5 * ole3];//atomiko varos
						//	crystal_backup[1 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[1 + 5 * ole3];//atomiko varos
							if (inptype == 'd')
							{
								//crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][1] = direct[1+5*ole3];
								for (int ole1 = 0; ole1 < 3; ole1++) {
									crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = uccartesian[ole1 + 3 * ole3] + ole * ijk[0][ole1] + ole2 * ijk[1][ole1] + ole4 * ijk[2][ole1];//cartesians
									crystal_backup[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = uccartesian[ole1 + 3 * ole3] + ole * ijk[0][ole1] + ole2 * ijk[1][ole1] + ole4 * ijk[2][ole1];//cartesians

									//if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] < min_xyz[ole1])
									//{
									//	min_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

									//}
									//if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] > max_xyz[ole1])
									//{
									//	max_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

									//}

								}

							}
							else if (inptype == 'c')
							{
								float oleh[3] = { ole,ole2,ole4 };
								for (ole1 = 0; ole1 < 3; ole1++) {
									if (oleh[ole1] >= 0)
										oleh[ole1]++;
									crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[ole1 + 2 + 5 * (ole3)] + ole * ijk[0][ole1] + ole2 * ijk[1][ole1] + ole4 * ijk[2][ole1];//cartesians
									crystal_backup[ole1 + 2 + 5 * (ole3 + t * (ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[ole1 + 2 + 5 * (ole3)] + ole * ijk[0][ole1] + ole2 * ijk[1][ole1] + ole4 * ijk[2][ole1];//cartesians

	/*								if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] < min_xyz[ole1])
									{
										min_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

									}
									if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] > max_xyz[ole1])
									{
										max_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

									}*/

								}
							}


							//rewind(periodic_table);

						}
					}
				}
			}
			//ttest =  omp_get_wtime() - ttest;
			//cout << ttest << endl;
			//fclose(periodic_table);


		}

		goto peintit;

	}


peintit:

	DestroyWindow(CommandTextField);



	CommandTextField = CreateWindow(L"EDIT",
		0, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOHSCROLL,
		0, 735, 300, 40,
		hWndCommandLine, NULL, NULL, NULL);

	oldEditProc = (WNDPROC)SetWindowLongPtr(CommandTextField, GWLP_WNDPROC, (LONG_PTR)WndProcEditBox);

	SendMessage(CommandTextField, WM_SETFONT, (WPARAM)fOnt, TRUE);

peintit1:


	if (okrender)
	{
		SendMessage(CommandTextHistory, EM_SETREADONLY, FALSE, NULL);

		okrender = 0;

		SendMessage(CommandTextHistory, EM_SETSEL, 0, -1);
		SendMessage(CommandTextHistory, EM_SETSEL, -1, 0);

		for (i = 0; i < 50; i++)
		{

			if (i == 0 && ttt[0] == 13)
			{

			}
			else
			{
				if (ttt[i] == 0)
				{
					i = 100;
				}
				else
				{
					SendMessage(CommandTextHistory, WM_CHAR, (TCHAR)ttt[i], 0);


				}
			}
		}

		if (d == 1)
		{
			SendMessage(CommandTextHistory, WM_CHAR, (TCHAR)ucender[0], 0);
		}

		SetFocus(CommandTextField);
		SendMessage(CommandTextHistory, EM_SETREADONLY, TRUE, NULL);

		for (i = 0; i < 50; i++)
		{
			CommandBuffer[i] = 0;

		}

		JGN_PostRedisplay();

	}
	else
	{
		SetFocus(CommandTextField);
	}

}