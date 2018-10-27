#pragma once

#include "JGN_Resource.h"
#include "stdafx.h"


void JGN_DropFile()
{
	if (ftype == 'p')
	{
		///line 1
		fgets(s, SBYTES, uc_file);
		while (strtok(s, "\t ")[0] == '\n')
		{
			fgets(s, SBYTES, uc_file);
		}

		//tsekarw posa einai ta eidi twn atomwn xrhsimopoiwdas ta kena gia na xrhsimopoihsw thn malloc
		//h malloc me voleyei giati dn kserw posa eidi atomwn exw eksarxhs



		///grammh 2
		fgets(s, SBYTES, uc_file);
		token = strtok(s, "\t ");
		while (token[0] == '\n')
		{
			fgets(s, SBYTES, uc_file);
			token = strtok(s, "\t ");

		}

		actor = std::atof(token);//pairnei thn timh sthn grammh 2



							///grammh 3
		fgets(s, SBYTES, uc_file);
		token = strtok(s, "\t ");
		while (token[0] == '\n')
		{
			fgets(s, SBYTES, uc_file);
			token = strtok(s, "\t ");

		}


		line++;		//synistwsa i


		for (p = 0; p < 3; p++)
		{
			ijk[0][p] = std::atof(token);
			ijk[0][p] = ijk[0][p] * actor;//pollaplasiazw me ton pollaplasiastiko paragoda
			token = strtok(NULL, "\t ");
		}


		///grammh 4
		fgets(s, SBYTES, uc_file);
		token = strtok(s, "\t ");
		while (token[0] == '\n')
		{
			fgets(s, SBYTES, uc_file);
			token = strtok(s, "\t ");

		}
		line++;	//synistwsa j

		for (p = 0; p < 3; p++)
		{
			ijk[1][p] = std::atof(token);
			ijk[1][p] = ijk[1][p] * actor;//pollaplasiazw me ton pollaplasiastiko paragoda
			token = strtok(NULL, "\t ");
		}



		///grammh 5
		fgets(s, SBYTES, uc_file);
		token = strtok(s, "\t ");
		while (token[0] == '\n')
		{
			fgets(s, SBYTES, uc_file);
			token = strtok(s, "\t ");

		}
		line++;		//synistwsa k


		for (p = 0; p < 3; p++)
		{
			ijk[2][p] = std::atof(token);
			ijk[2][p] = ijk[2][p] * actor;//pollaplasiazw me ton pollaplasiastiko paragoda
			token = strtok(NULL, "\t ");
		}

		///grammh 6			
		fgets(s, SBYTES, uc_file);
		token = strtok(s, "\t ");
		while (token[0] == '\n')
		{
			fgets(s, SBYTES, uc_file);
			token = strtok(s, "\t ");

		}
		shelp = new char[SBYTES];

		for (int i = 0; i < SBYTES; i++)
		{
			shelp[i] = s[i];
		}

		line++;		//vlepei poia einai ta stoixeia kai ta apo8ikeyei				


		a = 0;



		//a = number of atom types
		while (token != NULL) {
			if ((token[0] > 64 && token[0] < 91))
			{


				a++;
			}
			token = strtok(NULL, "\t ");


		}




		new_num_atoms = (int*)realloc(NULL, a * sizeof(int));
		for (int i = 0; i < a; i++)
		{
			new_num_atoms[i] = 0;
		}
		atomic_number = (int*)realloc(NULL, a * sizeof(int));
		for (int i = 0; i < a; i++)
		{
			atomic_number[i] = 0;
		}
		an_and_aw = (float*)realloc(NULL, sizeof(float)*a * 2);

		atoms = (char*)realloc(NULL, sizeof(char)*(a * 3 + 1)); atoms[0] = '\0';
		atomshelp = (char*)realloc(NULL, sizeof(char)*(a * 3 + 1)); atomshelp[0] = '\0';
		//voi8itikos
		//etsi twra borw na dilwsw tous pinakes me ta dedomena m alliws meta dn 8a borousa mesa stis if
		//ta declares mesa sta if exoune range mono mesa sto idio to if
		//3 xaraktires to poly 2 grammata gia to ka8e stoixeio + to \0
		ea = (int*)realloc(NULL, sizeof(int)*a); 		//ea: posa atoma ana eidos

		delete s;

		s = shelp;
		// remove '\0' that strtok added (if he did (a>1) )
		if (a > 1)
		{
			ole1 = 0;
			ole = 0;
			while (ole == 0)
			{
				if (s[ole1] == '\0')
				{
					s[ole1] = ' ';
					ole = 1;
				}
				ole1++;
			}
		}

		ole = 0;
		token = strtok(s, " \t");

		//save atoms in an char array
		while (token != NULL) {
			if ((token[0] > 64 && token[0] < 91))
			{  //twra kserw poia atoma symmetexoun 8a m xrhsimeysei meta poy 8a parw ta directs
				strcat(atoms, token);

				strcat(atoms, " ");
				for (ole1 = 0; ole1 < 3; ole1++) {
					if (atoms[ole1 + 3 * ole] == '\n') {
						atoms[ole1 + 3 * ole] = '\0';//giati sto teleytaio pou 8a dei sto line to atoms[ole][ole1] 8a parei thn timh \n kai oxi thn \0 poy 8elw
						ole1 = 100;
					}
				}

				ole++;
			}
			token = strtok(NULL, " \t");

		}
		strcat(atoms, "\0");



		//extra buffer for atoms char array
		for (int i = 0; i < 3 * a + 1; i++)
		{
			atomshelp[i] = atoms[i];
		}
		//atomshelp[3 * a - 1] = ' ';

		///grammh7		
		fgets(s, SBYTES, uc_file);
		token = strtok(s, "\t ");
		while (token[0] == '\n')
		{
			fgets(s, SBYTES, uc_file);
			token = strtok(s, "\t ");

		}
		line++;	//posa atoma tou ka8e stoixeiou ana cell?			

		ole = 0;
		t = 0;
		while (token != NULL) {
			ea[ole] = atoi(token);
			token = strtok(NULL, "\t ");
			t = t + ea[ole];//tosa atoma ana unit cell
			ole++;
			if (ole == a) break;
		}

		//debuging print
		//#define MY_DEBUG_1
#ifdef MY_DEBUG_1
		cout << actor << endl;
		cout << ijk[0][0] << '\t' << ijk[0][1] << '\t' << ijk[0][2] << endl;
		cout << ijk[1][0] << '\t' << ijk[1][1] << '\t' << ijk[1][2] << endl;
		cout << ijk[2][0] << '\t' << ijk[2][1] << '\t' << ijk[2][2] << endl;
		for (int i = 0; i < a; i++)
		{
			cout << ea[i] << '\t';
		}
		cout << endl;
		cout << "yeah 1" << endl;
#endif


		///gramh 8			

		// "direct" "cartasian" or "selective dynamics" ?
		fgets(s, SBYTES, uc_file);
		token = strtok(s, "\t ");
		while (token[0] == '\n')
		{
			fgets(s, SBYTES, uc_file);
			token = strtok(s, "\t ");

		}

		//check if we have "selective dynamics"
		selective_dynamics_bool = false;
		if (token[0] == 's' || token[0] == 'S')
		{
			selective_dynamics_bool = true;
			// "direct" or "cartasian" ?
			fgets(s, SBYTES, uc_file);
			token = strtok(s, "\t ");
			while (token[0] == '\n')
			{
				fgets(s, SBYTES, uc_file);
				token = strtok(s, "\t ");

			}
		}
		line++;



		my_direct = (float*)realloc(NULL, sizeof(float)*(t * 5));//t einai ola ta atoma tou unit cell.. 3 gia h,c,l kai dio gia atomiko ari8mo kai varos
		periodic_table = fopen("periodic_table.jgn", "r");
		aweights = (float*)realloc(NULL, sizeof(float)*a);
		aatoms = (int*)realloc(NULL, sizeof(int)*a);
		anumber = (int*)realloc(NULL, sizeof(int)*a);

		for (ole = 0; ole < a; ole++)
		{
			aweights[ole] = -1.;
			anumber[ole] = -1;
		}




		///gammh 9 kai meta	
		if (token[0] == 'd' || token[0] == 'D')
		{
			inptype = 'd';
		}
		else if (token[0] == 'c' || token[0] == 'C')
		{
			inptype = 'c';
		}

		ole2 = 0;
		ole3 = 0;
		token3 = strtok(atoms, " ");

		alloena = 0;
		ka8isterimenoflag = 0;
		selective_dynamics = (char*)realloc(NULL, sizeof(char)*(t * 3));

		for (ole = 0; ole < t; ole++) {


			fgets(s, SBYTES, uc_file);
			token = strtok(s, "\t ");
			while (token[0] == '\n')
			{
				fgets(s, SBYTES, uc_file);
				token = strtok(s, "\t ");

			}

			ole2++;


			for (ole1 = 0; ole1 < 3; ole1++) {

				my_direct[ole1 + 2 + 5 * ole] = std::atof(token);


				token = strtok(NULL, "\t ");

			}

			if (selective_dynamics_bool)
			{
				for (ole1 = 0; ole1 < 3; ole1++)
				{
					selective_dynamics[ole1 + 3 * ole] = token[0];

					token = strtok(NULL, "\t ");
				}
			}


			ole1 = 0;

			while (ole1 == 0) {

				fgets(s1, 50, periodic_table);
				token1 = strtok(s1, " ");


				if (strcmp(token3, token1) == 0) {


					token1 = strtok(NULL, " ");
					my_direct[0 + 5 * ole] = std::atof(token1);
					if (alloena == 0)
					{
						an_and_aw[alloena * 2] = std::atof(token1);
						//cout << 1 << "\n";
					}
					else if (an_and_aw[alloena * 2 - 2] != std::atof(token1))
					{
						//cout << an_and_aw[alloena * 2 - 2] << " " << std::atof(token1); getchar();
						an_and_aw[alloena * 2] = std::atof(token1);
						ka8isterimenoflag = 1;

						//cout << 2 << "\n";

					}


					token1 = strtok(NULL, " ");
					my_direct[1 + 5 * ole] = std::atof(token1);
					for (int ii = 0; ii < a; ii++)
					{
						if (aweights[ii] == my_direct[1 + 5 * ole])
						{
							ii = 9000;
						}
						else if (aweights[ii] == -1.)
						{
							aweights[ii] = my_direct[1 + 5 * ole];
							anumber[ii] = my_direct[0 + 5 * ole];
							ii = 9000;

						}
					}
					if (alloena == 0)
					{
						an_and_aw[alloena * 2 + 1] = std::atof(token1);
						alloena++;
						//cout << 3 << "\n";

					}

					else if (ka8isterimenoflag == 1)
					{
						an_and_aw[alloena * 2 + 1] = std::atof(token1);
						alloena++;
						ka8isterimenoflag = 0;
						//cout << 4 << "\n";
					}


					ole1 = 1;

				}


			}

			if (ole2 == ea[ole3])
			{

				token3 = strtok(token3 + strlen(token3) + 1, " ");
				ole3++;
				ole2 = 0;
			}

			rewind(periodic_table);
		}

		atoms = atomshelp;


		fclose(uc_file);


		//#define MY_DEBUG_2
#ifdef MY_DEBUG_2
		for (ole = 0; ole < t; ole++)
		{
			cout << selective_dynamics[0 + 3 * ole] << ' ' << selective_dynamics[1 + 3 * ole] << " " << selective_dynamics[2 + 3 * ole] << endl;
		}
		getchar();
#endif


		if (inptype == 'd')
		{
			uccartesian = (float*)realloc(NULL, sizeof(float)*(3 * t));//ta atoma toy unit cell se kartasiano
#ifdef DOUBLE_MOD
			__asm {
				mov esi, [t]
				imul esi, 40
				mov ebx, 0//ole1
				mov ecx, 0//ole*5

				/**/jmp loop2_b
				/**/loop2_s :
				/**/	/**/jmp loop1_b
					/**/	/**/loop1_s :
				/**/	/**/	/**/mov eax, ecx
					/**/	/**/	/**/mov edx, 0
					/**/	/**/	/**/mov edi, 5
					/**/	/**/	/**/div edi
					/**/	/**/	/**/mov edi, 3
					/**/	/**/	/**/mul edi//eax=ele*3+ole1
					/**/	/**/	/**/add eax, ebx
					/**/	/**/	/**/
					/**/	/**/	/**/movsd xmm0, [ijk + ebx]
					/**/	/**/	/**/mov edx, [my_direct]
					/**/	/**/	/**/mulsd xmm0, [edx + 16 + ecx]
					/**/	/**/	/**/movsd xmm1, [ijk + 24 + ebx]
					/**/	/**/	/**/mulsd xmm1, [edx + 24 + ecx]
					/**/	/**/	/**/addsd xmm0, xmm1
					/**/	/**/	/**/movsd xmm1, [ijk + 48 + ebx]
					/**/	/**/	/**/mulsd xmm1, [edx + 32 + ecx]
					/**/	/**/	/**/addsd xmm0, xmm1
					/**/	/**/	/**/mov edx, [uccartesian]
					/**/	/**/	/**/movsd[edx + eax], xmm0
					/**/	/**/	/**/
					/**/	/**/	/**/add ebx, 8
					/**/	/**/
					/**/	/**/loop1_b:
				/**/	/**/cmp ebx, 24
					/**/	/**/jge loop1_out
					/**/	/**/jmp loop1_s
					/**/	/**/loop1_out :
				/**/
				/**/	/**/mov ebx, 0
					/**/	/**/add ecx, 40
					/**/
					/**/loop2_b :
					/**/cmp ecx, esi
					/**/jge loop2_out
					/**/jmp loop2_s
					/**/loop2_out :


			}
#else
			__asm {
				mov esi, [t]
				imul esi, 20
				mov ebx, 0//ole1
				mov ecx, 0//ole*5

				/**/jmp loop2_b
				/**/loop2_s :
				/**/	/**/jmp loop1_b
					/**/	/**/loop1_s :
				/**/	/**/	/**/mov eax, ecx
					/**/	/**/	/**/mov edx, 0
					/**/	/**/	/**/mov edi, 5
					/**/	/**/	/**/div edi
					/**/	/**/	/**/mov edi, 3
					/**/	/**/	/**/mul edi//eax=ele*3+ole1
					/**/	/**/	/**/add eax, ebx
					/**/	/**/	/**/
					/**/	/**/	/**/movss xmm0, [ijk + ebx]
					/**/	/**/	/**/mov edx, [my_direct]
					/**/	/**/	/**/mulss xmm0, [edx + 8 + ecx]
					/**/	/**/	/**/movss xmm1, [ijk + 12 + ebx]
					/**/	/**/	/**/mulss xmm1, [edx + 12 + ecx]
					/**/	/**/	/**/addss xmm0, xmm1
					/**/	/**/	/**/movss xmm1, [ijk + 24 + ebx]
					/**/	/**/	/**/mulss xmm1, [edx + 16 + ecx]
					/**/	/**/	/**/addss xmm0, xmm1
					/**/	/**/	/**/mov edx, [uccartesian]
					/**/	/**/	/**/movss[edx + eax], xmm0
					/**/	/**/	/**/
					/**/	/**/	/**/add ebx, 4
					/**/	/**/
					/**/	/**/loop1_b:
				/**/	/**/cmp ebx, 12
					/**/	/**/jge loop1_out
					/**/	/**/jmp loop1_s
					/**/	/**/loop1_out :
				/**/
				/**/	/**/mov ebx, 0
					/**/	/**/add ecx, 20
					/**/
					/**/loop2_b :
					/**/cmp ecx, esi
					/**/jge loop2_out
					/**/jmp loop2_s
					/**/loop2_out :


			}
#endif
		}
		else if (inptype == 'c')
		{
			free(uccartesian);
			uccartesian = my_direct;
		}


		sized[0] = 1;
		sized[1] = 1;
		sized[2] = 1;

		crystal = (float*)realloc(NULL, sizeof(float)*(sized[0] * sized[1] * sized[2] * t * 5));
		crystal_backup = (float*)realloc(NULL, sizeof(float)*(sized[0] * sized[1] * sized[2] * t * 5));
		selective_dynamics = (char*)realloc(selective_dynamics, sizeof(char)*(sized[0] * sized[1] * sized[2] * t * 3));
		//	float crystal[sized[0]][sized[1]][sized[2]][t][5];//mas leei se poio unit cell eimaste size[0]][size[1]][size[2]]
		//poio atomo sto unit cell t;
		//atomikos ari8mos kai varos [2];
		//kai tis kartesianes tou xyz[3]

		//crystal[5+5*(t+t*(sized[2]+sized[2](sized[1]+sized[1]*sized[0])))];






		for (int i = 0; i < 500; i++)
		{
			if (lpszFile[i] == '\0')
			{
				for (int j = i; j > 0; j--)
				{
					if (lpszFile[j] == '\\')
					{
						for (k = j + 1; k < i + 1; k++)
						{
							PCtype[k - j - 1] = lpszFile[k];
						}
						j = 0;
					}
				}
				i = 1000;
			}
		}
		for (int i = 0; i < 100; i++)
		{
			if (PCtype[i] == '.')
			{
				PCtype[i] = '_';
			}
		}

		NewPC[0] = '\0';
		strcat(NewPC, PCtype);
		strcat(NewPC, "_NIKOULIS_");


		if (want_cyrcle[0] == 'y' || want_cyrcle[0] == 'Y')
		{
			char S[50];
			itoa(rad, S, 10);
			strcat(NewPC, "(sphere");
			strcat(NewPC, S);
			strcat(NewPC, ")");
		}
		else
		{
			if (S1v != 0)
			{
				char S[50];
				itoa(S1v, S, 10);
				strcat(NewPC, "(100");
				strcat(NewPC, S);
				strcat(NewPC, ")");
			}
			if (S2v != 0)
			{
				char S[50];
				itoa(S2v, S, 10);
				strcat(NewPC, "(110");
				strcat(NewPC, S);
				strcat(NewPC, ")");
			}
			if (S3v != 0)
			{
				char S[50];
				itoa(S3v, S, 10);
				strcat(NewPC, "(111");
				strcat(NewPC, S);
				strcat(NewPC, ")");
			}
		}
		//NewPCF = fopen(NewPC, "w");




		uc_file = fopen(inpf, "r");


		for (ole4 = -sized[2] / 2.0; ole4 < sized[2] / 2.0; ole4++) {
			for (ole2 = -sized[1] / 2.0; ole2 < sized[1] / 2.0; ole2++) {
				for (ole = -sized[0] / 2.0; ole < sized[0] / 2.0; ole++) {
					for (ole3 = 0; ole3 < t; ole3++) {
						crystal[0 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = my_direct[0 + 5 * ole3];//atomikos ari8mos
						crystal_backup[0 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = my_direct[0 + 5 * ole3];//atomikos ari8mos

																																												  //selective dynamics
						selective_dynamics[0 + 3 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = selective_dynamics[0 + 3 * (ole3)];
						selective_dynamics[1 + 3 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = selective_dynamics[1 + 3 * (ole3)];
						selective_dynamics[2 + 3 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = selective_dynamics[2 + 3 * (ole3)];

						//crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][0] = direct[0+5*ole3];
						crystal[1 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = my_direct[1 + 5 * ole3];//atomiko varos
						crystal_backup[1 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = my_direct[1 + 5 * ole3];//atomiko varos

						if (inptype == 'd')
						{
							//crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][1] = direct[1+5*ole3];
							for (ole1 = 0; ole1 < 3; ole1++) {
								crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = uccartesian[ole1 + 3 * ole3] + ole * ijk[0][ole1] + ole2 * ijk[1][ole1] + ole4 * ijk[2][ole1];//cartesians
								crystal_backup[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = uccartesian[ole1 + 3 * ole3] + ole * ijk[0][ole1] + ole2 * ijk[1][ole1] + ole4 * ijk[2][ole1];//cartesians

								if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] < min_xyz[ole1])
								{
									min_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

								}
								if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] > max_xyz[ole1])
								{
									max_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

								}

							}

						}
						else if (inptype == 'c')
						{
							for (ole1 = 0; ole1 < 3; ole1++) {
								crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = my_direct[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];//cartesians
								crystal_backup[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = my_direct[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];//cartesians

								if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] < min_xyz[ole1])
								{
									min_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

								}
								if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] > max_xyz[ole1])
								{
									max_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

								}

							}
						}
						rewind(periodic_table);


					}

				}
			}
		}



		ole4 = 0;
		//atom. ar. twn atomwn
		for (ole5 = 0; ole5 < t; ole5++)
		{

			if (ole4 == 0)
			{
				atomic_number[ole4] = crystal[0 + 5 * ole5];
				ole4++;

			}
			else if (atomic_number[ole4] == 0 && atomic_number[ole4 - 1] != crystal[0 + 5 * ole5])
			{

				atomic_number[ole4] = crystal[0 + 5 * ole5];
				ole4++;
			}



		}


		allatoms = sized[0] * sized[1] * sized[2] * t;
		//diavazw to arxeio


		cout << "\n";
		cout << "The number of atoms are " << allatoms << "\n";




		xyz_range[0] = max_xyz[0] - min_xyz[0];//
		xyz_range[1] = max_xyz[1] - min_xyz[1];//ogos
		xyz_range[2] = max_xyz[2] - min_xyz[2];//

		cout << "\n";
		cout << "  Minimum: " << min_xyz[0]
			<< "  " << min_xyz[1]
			<< "  " << min_xyz[2] << "\n";
		cout << "  Maximum: " << max_xyz[0]
			<< "  " << max_xyz[1]
			<< "  " << max_xyz[2] << "\n";
		cout << "  Range:   " << xyz_range[0]
			<< "  " << xyz_range[1]
			<< "  " << xyz_range[2] << "\n";

		if (Svmax == 0)
		{
			Svmax = max_xyz[0];
			if (Svmax < max_xyz[1])
			{
				Svmax = max_xyz[1];
			}

			if (Svmax < max_xyz[2])
			{
				Svmax = max_xyz[2];
			}
			Svmax = Svmax * 2;
		}

		pointsize = truepointsize / (Svmax + 5);



		/*
		if (want_cyrcle[0] == 'y')
		{

		for (ole = 0; ole < t*sized[0] * sized[1] * sized[2]; ole++)
		{

		if (sqrt(crystal[2 + 5 * ole] * crystal[2 + 5 * ole] + crystal[3 + 5 * ole] * crystal[3 + 5 * ole] + crystal[4 + 5 * ole] * crystal[4 + 5 * ole]) <= rad)
		{
		for (ole1 = 0; ole1 < a; ole1++)
		{
		if (atomic_number[ole1] == (int)crystal[0 + 5 * ole])
		{
		new_num_atoms[ole1] = new_num_atoms[ole1] + 1;
		atomscc++;

		}

		}

		}

		}

		for (ole = 0; ole < a; ole++)
		{
		//fprintf(NewPCF, "%d ", new_num_atoms[ole]);

		}
		//fprintf(NewPCF, "\n");

		}
		else
		{


		for (ole = 0; ole < t*sized[0] * sized[1] * sized[2]; ole++)
		{

		if ((S1i[0] * abs(crystal[2 + 5 * ole]) <= S1v) && (S1i[0] * abs(crystal[3 + 5 * ole]) <= S1v) && (S1i[0] * abs(crystal[4 + 5 * ole]) <= S1v) && S2i[0] * abs(crystal[2 + 5 * ole]) + S2i[1] * abs(crystal[3 + 5 * ole]) <= S2v && S2i[0] * abs(crystal[2 + 5 * ole]) + S2i[1] * abs(crystal[4 + 5 * ole]) <= S2v && S2i[0] * abs(crystal[3 + 5 * ole]) + S2i[1] * abs(crystal[4 + 5 * ole]) <= S2v && S3i[0] * abs(crystal[2 + 5 * ole]) + S3i[1] * abs(crystal[3 + 5 * ole]) + S3i[2] * abs(crystal[4 + 5 * ole]) <= S3v)
		{

		for (ole1 = 0; ole1 < a; ole1++)
		{
		if (atomic_number[ole1] == (int)crystal[0 + 5 * ole])
		{
		new_num_atoms[ole1] = new_num_atoms[ole1] + 1;
		atomscc++;


		}

		}

		}

		}

		for (ole = 0; ole < a; ole++)
		{
		//fprintf(NewPCF, "%d ", new_num_atoms[ole]);

		}
		//fprintf(NewPCF, "\n");


		}

		*/


		fclose(uc_file);


		/*
		atoms_to_print = (float*)realloc(atoms_to_print, sizeof(float)*atomscc * 4);





		if (want_cyrcle[0] == 'y') {

		for (ole5 = 0; ole5 < a; ole5++) {
		for (ole4 = -sized[2] / 2; ole4 < sized[2] / 2; ole4++) {
		for (ole2 = -sized[1] / 2; ole2 < sized[1] / 2; ole2++) {
		for (ole = -sized[0] / 2; ole < sized[0] / 2; ole++) {
		for (ole3 = 0; ole3 < t; ole3++) {
		if (rad >= sqrt(crystal[0 + 2 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] * crystal[0 + 2 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] + crystal[1 + 2 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] * crystal[1 + 2 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] + crystal[2 + 2 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] * crystal[2 + 2 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]))
		{

		//crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][1] = direct[1+5*ole3];
		for (ole1 = 0; ole1 < 3; ole1++) {

		if (crystal[0 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] == atomic_number[ole5])
		{
		atoms_to_print[atoms_to_print_c + ole1] = crystal[ole1 + 2 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];
		//fprintf(NewPCF, "%f ", -min_xyz[ole1] + crystal[ole1 + 2 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]);
		}
		}
		if (crystal[0 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] == atomic_number[ole5])
		{
		atoms_to_print[atoms_to_print_c + 3] = atomic_number[ole5];
		atoms_to_print_c = atoms_to_print_c + 4;
		}
		}
		if (rad >= sqrt(crystal[0 + 2 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] * crystal[0 + 2 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] + crystal[1 + 2 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] * crystal[1 + 2 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] + crystal[2 + 2 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] * crystal[2 + 2 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))])) {
		if (crystal[0 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] == atomic_number[ole5])
		{
		//fprintf(NewPCF, "\n");
		}
		}

		}
		}
		}
		}
		}



		}
		else {
		for (ole5 = 0; ole5 < a; ole5++) {
		for (ole4 = -sized[2] / 2; ole4 < sized[2] / 2; ole4++) {
		for (ole2 = -sized[1] / 2; ole2 < sized[1] / 2; ole2++) {
		for (ole = -sized[0] / 2; ole < sized[0] / 2; ole++) {
		for (ole3 = 0; ole3 < t; ole3++) {
		if ((S1i[0] * abs(crystal[2 + 0 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]) <= S1v) && (S1i[0] * abs(crystal[2 + 1 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]) <= S1v) && (S1i[0] * abs(crystal[2 + 2 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]) <= S1v) && S2i[0] * abs(crystal[2 + 0 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]) + S2i[1] * abs(crystal[2 + 1 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]) <= S2v && S2i[0] * abs(crystal[2 + 0 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]) + S2i[1] * abs(crystal[2 + 2 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]) <= S2v && S2i[0] * abs(crystal[2 + 1 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]) + S2i[1] * abs(crystal[2 + 2 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]) <= S2v && S3i[0] * abs(crystal[2 + 0 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]) + S3i[1] * abs(crystal[2 + 1 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]) + S3i[2] * abs(crystal[2 + 2 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]) <= S3v)

		{

		//crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][1] = direct[1+5*ole3];
		for (ole1 = 0; ole1 < 3; ole1++) {

		if (crystal[0 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] == atomic_number[ole5])
		{
		atoms_to_print[atoms_to_print_c + ole1] = crystal[ole1 + 2 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];
		//cout << -min_xyz[ole1] + atoms_to_print[atoms_to_print_c + ole1] << " ";
		//fprintf(NewPCF, "%f ", -min_xyz[ole1] + crystal[ole1 + 2 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]);
		//cout << min_xyz[ole1] << endl;
		}
		}
		if (crystal[0 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] == atomic_number[ole5])
		{
		atoms_to_print[atoms_to_print_c + 3] = atomic_number[ole5];
		//cout << atoms_to_print[atoms_to_print_c + 3] << "\n";
		atoms_to_print_c = atoms_to_print_c + 4;
		}

		}
		if ((S1i[0] * abs(crystal[2 + 0 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]) <= S1v) && (S1i[0] * abs(crystal[2 + 1 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]) <= S1v) && (S1i[0] * abs(crystal[2 + 2 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]) <= S1v) && S2i[0] * abs(crystal[2 + 0 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]) + S2i[1] * abs(crystal[2 + 1 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]) <= S2v && S2i[0] * abs(crystal[2 + 0 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]) + S2i[1] * abs(crystal[2 + 2 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]) <= S2v && S2i[0] * abs(crystal[2 + 1 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]) + S2i[1] * abs(crystal[2 + 2 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]) <= S2v && S3i[0] * abs(crystal[2 + 0 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]) + S3i[1] * abs(crystal[2 + 1 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]) + S3i[2] * abs(crystal[2 + 2 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]) <= S3v)

		{
		if (crystal[0 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] == atomic_number[ole5])
		{
		//fprintf(NewPCF, "\n");
		}
		}

		}
		}
		}
		}
		full = 1;
		}

		}
		*/
		atoms_to_print_c = 0;
		//fclose(NewPCF);

		fclose(periodic_table);




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
				else if ((S2v >= 2 * S1v && figure_1 != -1) || S3v <= S2v)
				{
					Scase = 3;
				}
				else if ((float(S3v) >= (float(S2v) * 3) / 2 && figure_1 != -1) || (figure_1 == -1 && S3v >= 2 * S2v))
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






		if (jgn_supercell)
		{
			was_supercell = 1;
			jgn_supercell = 1;
			Right_Hexagonal = 1;
			figure_1 = 1;
			Rod_like = 1;

			sized[0] = jgn_supercell_xyz[0];
			sized[1] = jgn_supercell_xyz[1];
			sized[2] = jgn_supercell_xyz[2];


			periodic_table = fopen("periodic_table.jgn", "r");

			crystal = (float*)realloc(crystal, sizeof(float)*(jgn_supercell_xyz[0] * jgn_supercell_xyz[1] * jgn_supercell_xyz[2] * t * 5));
			selective_dynamics = (char*)realloc(selective_dynamics, sizeof(char)*(jgn_supercell_xyz[0] * jgn_supercell_xyz[1] * jgn_supercell_xyz[2] * t * 3));
			//crystal_backup = (float*)realloc(crystal, sizeof(float)*(jgn_supercell_xyz[0] * jgn_supercell_xyz[1] * jgn_supercell_xyz[2] * t * 5));

			for (ole4 = -jgn_supercell_xyz[2] / 2; ole4 < jgn_supercell_xyz[2] / 2 + xexe[2]; ole4++) {
				for (ole2 = -jgn_supercell_xyz[1] / 2; ole2 < jgn_supercell_xyz[1] / 2 + xexe[1]; ole2++) {
					for (ole = -jgn_supercell_xyz[0] / 2; ole < jgn_supercell_xyz[0] / 2 + xexe[0]; ole++) {
						for (ole3 = 0; ole3 < t; ole3++) {
							crystal[0 + 5 * (ole3 + t * (ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[0 + 5 * ole3];//atomikos ari8mos
																																																										   //crystal_backup[0 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[0 + 5 * ole3];//atomikos ari8mos

																																																										   //crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][0] = direct[0+5*ole3];
							crystal[1 + 5 * (ole3 + t * (ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[1 + 5 * ole3];//atomiko varos
																																																										   //crystal_backup[1 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[1 + 5 * ole3];//atomiko varos

																																																										   //selective dynamics
							selective_dynamics[0 + 3 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = selective_dynamics[0 + 3 * (ole3)];
							selective_dynamics[1 + 3 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = selective_dynamics[1 + 3 * (ole3)];
							selective_dynamics[2 + 3 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = selective_dynamics[2 + 3 * (ole3)];

							sim_box_lo[0] = max;
							sim_box_lo[1] = max;
							sim_box_lo[2] = max;

							if (inptype == 'd')
							{

								//crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][1] = direct[1+5*ole3];
								for (ole1 = 0; ole1 < 3; ole1++) {
									crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = uccartesian[ole1 + 3 * ole3] + ole * ijk[0][ole1] + ole2 * ijk[1][ole1] + ole4 * ijk[2][ole1];//cartesians
																																																																	//crystal_backup[ole1 + 2 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = uccartesian[ole1 + 3 * ole3] + ole*ijk[0][ole1] + ole2*ijk[1][ole1] + ole4*ijk[2][ole1];//cartesians

									if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] < min_xyz[ole1])
									{
										min_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

									}
									if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] > max_xyz[ole1])
									{
										max_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

									}

								}
								if (crystal[0 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] < sim_box_lo[0])
								{
									sim_box_lo[0] = crystal[0 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];
									sim_box_lo[1] = crystal[1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];
									sim_box_lo[2] = crystal[2 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

								}
								else if (crystal[0 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] == sim_box_lo[0])
								{
									if (crystal[1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] < sim_box_lo[1])
									{
										sim_box_lo[0] = crystal[0 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];
										sim_box_lo[1] = crystal[1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];
										sim_box_lo[2] = crystal[2 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

									}
									else if (crystal[1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] == sim_box_lo[1])
									{
										if (crystal[2 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] < sim_box_lo[2])
										{
											sim_box_lo[0] = crystal[0 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];
											sim_box_lo[1] = crystal[1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];
											sim_box_lo[2] = crystal[2 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

										}

									}

								}


							}
							else if (inptype == 'c')
							{
								for (ole1 = 0; ole1 < 3; ole1++) {
									crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = my_direct[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];//cartesians
									crystal_backup[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = my_direct[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];//cartesians


																																																																											   //crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][ole1 + 2] = uccartesian[ole1+3*ole3] + ole*ijk[0][ole1] + ole2*ijk[1][ole1] + ole4*ijk[2][ole1];
									if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] < min_xyz[ole1])
									{
										min_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

									}
									if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] > max_xyz[ole1])
									{
										max_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

									}

								}
							}	if (crystal[0 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] < sim_box_lo[0])
							{
								sim_box_lo[0] = crystal[0 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];
								sim_box_lo[1] = crystal[1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];
								sim_box_lo[2] = crystal[2 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

							}
							else if (crystal[0 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] == sim_box_lo[0])
							{
								if (crystal[1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] < sim_box_lo[1])
								{
									sim_box_lo[0] = crystal[0 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];
									sim_box_lo[1] = crystal[1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];
									sim_box_lo[2] = crystal[2 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

								}
								else if (crystal[1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] == sim_box_lo[1])
								{
									if (crystal[2 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] < sim_box_lo[2])
									{
										sim_box_lo[0] = crystal[0 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];
										sim_box_lo[1] = crystal[1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];
										sim_box_lo[2] = crystal[2 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

									}

								}

							}


							rewind(periodic_table);

						}
					}
				}
			}


			fclose(periodic_table);


		}

	}
	else if (ftype == 'l')
	{

		///line 1
		fgets(s, SBYTES, uc_file);
		while (strtok(s, "\t ")[0] == '\n')
		{
			fgets(s, SBYTES, uc_file);
		}

		//tsekarw posa einai ta eidi twn atomwn xrhsimopoiwdas ta kena gia na xrhsimopoihsw thn malloc
		//h malloc me voleyei giati dn kserw posa eidi atomwn exw eksarxhs



		///grammh 2 read t
		fgets(s, SBYTES, uc_file);
		token = strtok(s, "\t ");
		while (token[0] == '\n')
		{
			fgets(s, SBYTES, uc_file);
			token = strtok(s, "\t ");

		}
		t = atoi(token);
		actor = 1.0;


		///grammh 3
		fgets(s, SBYTES, uc_file);
		token = strtok(s, "\t ");
		while (token[0] == '\n')
		{
			fgets(s, SBYTES, uc_file);
			token = strtok(s, "\t ");

		}


		a = atoi(token);

		float xlo, xhi, ylo, yhi, zlo, zhi;
		///grammh 4 xlo xhi
		fgets(s, SBYTES, uc_file);
		token = strtok(s, "\t ");
		while (token[0] == '\n')
		{
			fgets(s, SBYTES, uc_file);
			token = strtok(s, "\t ");

		}
		line++;	
		xlo = std::atof(token);
		token = strtok(NULL, "\t ");
		xhi = std::atof(token);


		ijk[0][0] = xhi - xlo;
		ijk[0][1] = 0;
		ijk[0][2] = 0;


		///grammh 5 yhi ylo
		fgets(s, SBYTES, uc_file);
		token = strtok(s, "\t ");
		while (token[0] == '\n')
		{
			fgets(s, SBYTES, uc_file);
			token = strtok(s, "\t ");

		}
		line++;		

		ylo = std::atof(token);
		token = strtok(NULL, "\t ");
		yhi = std::atof(token);

		ijk[1][0] = 0;
		ijk[1][1] = yhi - ylo;
		ijk[1][2] = 0;


		///grammh 6 zlo zhi	
		fgets(s, SBYTES, uc_file);
		token = strtok(s, "\t ");
		while (token[0] == '\n')
		{
			fgets(s, SBYTES, uc_file);
			token = strtok(s, "\t ");

		}
		line++;

		zlo = std::atof(token);
		token = strtok(NULL, "\t ");
		zhi = std::atof(token);


		ijk[2][0] = 0;
		ijk[2][1] = 0;
		ijk[2][2] = zhi - zlo;


		new_num_atoms = (int*)realloc(NULL, a * sizeof(int));
		for (int i = 0; i < a; i++)
		{
			new_num_atoms[i] = 0;
		}
		atomic_number = (int*)realloc(NULL, a * sizeof(int));
		for (int i = 0; i < a; i++)
		{
			atomic_number[i] = 0;
		}
		an_and_aw = (float*)realloc(NULL, sizeof(float)*a * 2);

		atoms = (char*)realloc(NULL, sizeof(char)*a * 3); atoms[0] = '\0';
		atomshelp = (char*)realloc(NULL, sizeof(char)*a * 3); atomshelp[0] = '\0';
		//voi8itikos
		//etsi twra borw na dilwsw tous pinakes me ta dedomena m alliws meta dn 8a borousa mesa stis if
		//ta declares mesa sta if exoune range mono mesa sto idio to if
		//3 xaraktires to poly 2 grammata gia to ka8e stoixeio + to \0
		ea = (int*)realloc(NULL, sizeof(int)*a); 		//ea: posa atoma ana eidos
		aweights = (float*)realloc(NULL, sizeof(float)*a);
		aatoms = (int*)realloc(NULL, sizeof(int)*a);
		anumber = (int*)realloc(NULL, sizeof(int)*a);


		///grammh 7 xy xz yz (if it exists), Masses if exist, Atoms
		fgets(s, SBYTES, uc_file);
		token = strtok(s, "\t ");
		while (token[0] == '\n')
		{
			fgets(s, SBYTES, uc_file);
			token = strtok(s, "\t ");

		}
		line++;

		if (token[0] == 'M' || token[0] == 'm')
		{

			if (token[0] == 'M' || token[0] == 'm')
			{
				periodic_table = fopen("periodic_table.jgn", "r");

				for (i = 0; i < a; i++)
				{
					found = false;
					fgets(s, SBYTES, uc_file);
					token = strtok(s, "\t ");
					while (token[0] == '\n')
					{
						fgets(s, SBYTES, uc_file);
						token = strtok(s, "\t ");

					}
					token = strtok(NULL, "\t ");
					while (!found)
					{
						fgets(s1, SBYTES, periodic_table);
						token1 = strtok(s1, " ");
						strcat(atoms, token1);
						strcat(atoms, " ");

						token1 = strtok(NULL, " ");
						anumber[i] = atoi(token1);

						token1 = strtok(NULL, " ");
						aweights[i] = std::atof(token1);

						if (int(10 * std::atof(token1)) == int(10 * std::atof(token)))
						{
							found = true;
							for (ole1 = 0; ole1 < 3; ole1++) {
								if (atoms[ole1 + 3 * i] == '\n') {
									atoms[ole1 + 3 * i] = '\0';//giati sto teleytaio pou 8a dei sto line to atoms[ole][ole1] 8a parei thn timh \n kai oxi thn \0 poy 8elw
									ole1 = 100;
								}
							}
						}
						else
						{
							atoms[i * 3] = '\0';
						}
					}
					rewind(periodic_table);
				}

				strcat(atoms, " ");

			}
			else
			{
				for (i = 0; i < a; i++)
				{
					itoa(i + 1, &atoms[i * 3], 10);
					atoms[1 + i * 3] = ' ';
					atoms[2 + i * 3] = ' ';
				}
				atoms[i * 3] = '\0';

			}
		}
		else
		{
			ijk[1][0] = std::atof(token);

			token = strtok(NULL, "\t ");
			ijk[2][0] = std::atof(token);

			token = strtok(NULL, "\t ");
			ijk[2][1] = std::atof(token);

			fgets(s, SBYTES, uc_file);
			token = strtok(s, "\t ");
			while (token[0] == '\n')
			{
				fgets(s, SBYTES, uc_file);
				token = strtok(s, "\t ");

			}
			line++;

			if (token[0] == 'M' || token[0] == 'm')
			{
				periodic_table = fopen("periodic_table.jgn", "r");

				for (i = 0; i < a; i++)
				{
					found = false;
					fgets(s, SBYTES, uc_file);
					token = strtok(s, "\t ");
					while (token[0] == '\n')
					{
						fgets(s, SBYTES, uc_file);
						token = strtok(s, "\t ");

					}
					token = strtok(NULL, "\t ");
					while (!found)
					{
						fgets(s1, SBYTES, periodic_table);
						token1 = strtok(s1, " ");
						strcat(atoms, token1);
						strcat(atoms, " ");

						token1 = strtok(NULL, " ");
						anumber[i] = atoi(token1);

						token1 = strtok(NULL, " ");
						aweights[i] = std::atof(token1);
						cout << atoms << endl;
						if (int(10 * std::atof(token1)) == int(10 * std::atof(token)))
						{
							found = true;
							for (ole1 = 0; ole1 < 3; ole1++) {
								if (atoms[ole1 + 3 * i] == '\n') {
									atoms[ole1 + 3 * i] = '\0';//giati sto teleytaio pou 8a dei sto line to atoms[ole][ole1] 8a parei thn timh \n kai oxi thn \0 poy 8elw
									ole1 = 100;
								}
							}
						}
						else
						{
							atoms[strlen(atoms) - 1] = '\0';
							if(atoms[strlen(atoms) - 1] != ' ')
								atoms[strlen(atoms) - 1] = '\0';
							if (atoms[strlen(atoms) - 1] != ' ')
								atoms[strlen(atoms) - 1] = '\0';

						}
					}
					rewind(periodic_table);
				}

				strcat(atoms, " ");
				strcat(atoms, "\0");


			}
			else
			{
				for (i = 0; i < a; i++)
				{
					itoa(i + 1, &atoms[i * 3], 10);
					atoms[1 + i * 3] = ' ';
					atoms[2 + i * 3] = ' ';
				}
				atoms[i * 3] = '\0';

			}
		}


		///////////////////



		//debuging print
		//#define MY_DEBUG_1
#ifdef MY_DEBUG_1
		cout << actor << endl;
		cout << ijk[0][0] << '\t' << ijk[0][1] << '\t' << ijk[0][2] << endl;
		cout << ijk[1][0] << '\t' << ijk[1][1] << '\t' << ijk[1][2] << endl;
		cout << ijk[2][0] << '\t' << ijk[2][1] << '\t' << ijk[2][2] << endl;
		for (int i = 0; i < a; i++)
		{
			cout << ea[i] << '\t';
		}
		cout << endl;
		cout << "yeah 1" << endl;
#endif
		my_direct = (float*)realloc(NULL, sizeof(float)*(t * 5));//t einai ola ta atoma tou unit cell.. 3 gia h,c,l kai dio gia atomiko ari8mo kai varos

		///gammh 9 kai meta	
		inptype = 'c';

		fgets(s, SBYTES, uc_file);
		token = strtok(s, "\t ");
		while (token[0] == '\n')
		{
			fgets(s, SBYTES, uc_file);
			token = strtok(s, "\t ");

		}


		ole2 = 0;
		ole3 = 0;
		//token3 = strtok(atoms, " ");

		alloena = 0;
		ka8isterimenoflag = 0;
		selective_dynamics = (char*)realloc(NULL, sizeof(char)*(t * 3));

		for (ole = 0; ole < t; ole++) {


			fgets(s, SBYTES, uc_file);
			token = strtok(s, "\t ");
			while (token[0] == '\n')
			{
				fgets(s, SBYTES, uc_file);
				token = strtok(s, "\t ");

			}

			ole2++;

			token = strtok(NULL, "\t ");
			my_direct[0 + 5 * ole] = anumber[atoi(token) - 1];//atomicos ari8os
			my_direct[1 + 5 * ole] = aweights[atoi(token) - 1];//atomicos varos


			token = strtok(NULL, "\t ");

			for (ole1 = 0; ole1 < 3; ole1++) {

				my_direct[ole1 + 2 + 5 * ole] = std::atof(token);


				token = strtok(NULL, "\t ");

			}


			ole1 = 0;


			//if (ole2 == ea[ole3])
			//{

			//	token3 = strtok(token3 + strlen(token3) + 1, " ");
			//	ole3++;
			//	ole2 = 0;
			//}

		}


		//atoms = atomshelp;


		fclose(uc_file);


		//#define MY_DEBUG_2
#ifdef MY_DEBUG_2
		for (ole = 0; ole < t; ole++)
		{
			cout << selective_dynamics[0 + 3 * ole] << ' ' << selective_dynamics[1 + 3 * ole] << " " << selective_dynamics[2 + 3 * ole] << endl;
		}
		getchar();
#endif


		if (inptype == 'd')
		{
		}
		else if (inptype == 'c')
		{
			free(uccartesian);
			uccartesian = my_direct;
		}


		sized[0] = 1;
		sized[1] = 1;
		sized[2] = 1;

		crystal = (float*)realloc(NULL, sizeof(float)*(sized[0] * sized[1] * sized[2] * t * 5));
		crystal_backup = (float*)realloc(NULL, sizeof(float)*(sized[0] * sized[1] * sized[2] * t * 5));
		selective_dynamics = (char*)realloc(selective_dynamics, sizeof(char)*(sized[0] * sized[1] * sized[2] * t * 3));
		//	float crystal[sized[0]][sized[1]][sized[2]][t][5];//mas leei se poio unit cell eimaste size[0]][size[1]][size[2]]
		//poio atomo sto unit cell t;
		//atomikos ari8mos kai varos [2];
		//kai tis kartesianes tou xyz[3]

		//crystal[5+5*(t+t*(sized[2]+sized[2](sized[1]+sized[1]*sized[0])))];






		for (int i = 0; i < 500; i++)
		{
			if (lpszFile[i] == '\0')
			{
				for (int j = i; j > 0; j--)
				{
					if (lpszFile[j] == '\\')
					{
						for (k = j + 1; k < i + 1; k++)
						{
							PCtype[k - j - 1] = lpszFile[k];
						}
						j = 0;
					}
				}
				i = 1000;
			}
		}
		for (int i = 0; i < 100; i++)
		{
			if (PCtype[i] == '.')
			{
				PCtype[i] = '_';
			}
		}

		NewPC[0] = '\0';
		strcat(NewPC, PCtype);
		strcat(NewPC, "_NIKOULIS_");


		if (want_cyrcle[0] == 'y' || want_cyrcle[0] == 'Y')
		{
			char S[50];
			itoa(rad, S, 10);
			strcat(NewPC, "(sphere");
			strcat(NewPC, S);
			strcat(NewPC, ")");
		}
		else
		{
			if (S1v != 0)
			{
				char S[50];
				itoa(S1v, S, 10);
				strcat(NewPC, "(100");
				strcat(NewPC, S);
				strcat(NewPC, ")");
			}
			if (S2v != 0)
			{
				char S[50];
				itoa(S2v, S, 10);
				strcat(NewPC, "(110");
				strcat(NewPC, S);
				strcat(NewPC, ")");
			}
			if (S3v != 0)
			{
				char S[50];
				itoa(S3v, S, 10);
				strcat(NewPC, "(111");
				strcat(NewPC, S);
				strcat(NewPC, ")");
			}
		}
		//NewPCF = fopen(NewPC, "w");



		uc_file = fopen(inpf, "r");


		for (ole4 = -sized[2] / 2.0; ole4 < sized[2] / 2.0; ole4++) {
			for (ole2 = -sized[1] / 2.0; ole2 < sized[1] / 2.0; ole2++) {
				for (ole = -sized[0] / 2.0; ole < sized[0] / 2.0; ole++) {
					for (ole3 = 0; ole3 < t; ole3++) {
						crystal[0 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = my_direct[0 + 5 * ole3];//atomikos ari8mos
						crystal_backup[0 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = my_direct[0 + 5 * ole3];//atomikos ari8mos

																																												  //selective dynamics
						selective_dynamics[0 + 3 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = selective_dynamics[0 + 3 * (ole3)];
						selective_dynamics[1 + 3 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = selective_dynamics[1 + 3 * (ole3)];
						selective_dynamics[2 + 3 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = selective_dynamics[2 + 3 * (ole3)];

						//crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][0] = direct[0+5*ole3];
						crystal[1 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = my_direct[1 + 5 * ole3];//atomiko varos
						crystal_backup[1 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = my_direct[1 + 5 * ole3];//atomiko varos

						if (inptype == 'd')
						{
							//crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][1] = direct[1+5*ole3];
							for (ole1 = 0; ole1 < 3; ole1++) {
								crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = uccartesian[ole1 + 3 * ole3] + ole * ijk[0][ole1] + ole2 * ijk[1][ole1] + ole4 * ijk[2][ole1];//cartesians
								crystal_backup[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = uccartesian[ole1 + 3 * ole3] + ole * ijk[0][ole1] + ole2 * ijk[1][ole1] + ole4 * ijk[2][ole1];//cartesians

								if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] < min_xyz[ole1])
								{
									min_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

								}
								if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] > max_xyz[ole1])
								{
									max_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

								}

							}

						}
						else if (inptype == 'c')
						{
							for (ole1 = 0; ole1 < 3; ole1++) {
								crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = my_direct[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];//cartesians
								crystal_backup[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = my_direct[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];//cartesians

								if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] < min_xyz[ole1])
								{
									min_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

								}
								if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] > max_xyz[ole1])
								{
									max_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

								}

							}
						}
						rewind(periodic_table);


					}

				}
			}
		}



		ole4 = 0;
		//atom. ar. twn atomwn
		for (ole5 = 0; ole5 < t; ole5++)
		{

			if (ole4 == 0)
			{
				atomic_number[ole4] = crystal[0 + 5 * ole5];
				ole4++;

			}
			else if (atomic_number[ole4] == 0 && atomic_number[ole4 - 1] != crystal[0 + 5 * ole5])
			{

				atomic_number[ole4] = crystal[0 + 5 * ole5];
				ole4++;
			}



		}


		allatoms = sized[0] * sized[1] * sized[2] * t;
		//diavazw to arxeio


		cout << "\n";
		cout << "The number of atoms are " << allatoms << "\n";




		xyz_range[0] = max_xyz[0] - min_xyz[0];//
		xyz_range[1] = max_xyz[1] - min_xyz[1];//ogos
		xyz_range[2] = max_xyz[2] - min_xyz[2];//

		cout << "\n";
		cout << "  Minimum: " << min_xyz[0]
			<< "  " << min_xyz[1]
			<< "  " << min_xyz[2] << "\n";
		cout << "  Maximum: " << max_xyz[0]
			<< "  " << max_xyz[1]
			<< "  " << max_xyz[2] << "\n";
		cout << "  Range:   " << xyz_range[0]
			<< "  " << xyz_range[1]
			<< "  " << xyz_range[2] << "\n";

		if (Svmax == 0)
		{
			Svmax = max_xyz[0];
			if (Svmax < max_xyz[1])
			{
				Svmax = max_xyz[1];
			}

			if (Svmax < max_xyz[2])
			{
				Svmax = max_xyz[2];
			}
			Svmax = Svmax * 2;
		}

		pointsize = truepointsize / (Svmax + 5);



		/*
		if (want_cyrcle[0] == 'y')
		{

		for (ole = 0; ole < t*sized[0] * sized[1] * sized[2]; ole++)
		{

		if (sqrt(crystal[2 + 5 * ole] * crystal[2 + 5 * ole] + crystal[3 + 5 * ole] * crystal[3 + 5 * ole] + crystal[4 + 5 * ole] * crystal[4 + 5 * ole]) <= rad)
		{
		for (ole1 = 0; ole1 < a; ole1++)
		{
		if (atomic_number[ole1] == (int)crystal[0 + 5 * ole])
		{
		new_num_atoms[ole1] = new_num_atoms[ole1] + 1;
		atomscc++;

		}

		}

		}

		}

		for (ole = 0; ole < a; ole++)
		{
		//fprintf(NewPCF, "%d ", new_num_atoms[ole]);

		}
		//fprintf(NewPCF, "\n");

		}
		else
		{


		for (ole = 0; ole < t*sized[0] * sized[1] * sized[2]; ole++)
		{

		if ((S1i[0] * abs(crystal[2 + 5 * ole]) <= S1v) && (S1i[0] * abs(crystal[3 + 5 * ole]) <= S1v) && (S1i[0] * abs(crystal[4 + 5 * ole]) <= S1v) && S2i[0] * abs(crystal[2 + 5 * ole]) + S2i[1] * abs(crystal[3 + 5 * ole]) <= S2v && S2i[0] * abs(crystal[2 + 5 * ole]) + S2i[1] * abs(crystal[4 + 5 * ole]) <= S2v && S2i[0] * abs(crystal[3 + 5 * ole]) + S2i[1] * abs(crystal[4 + 5 * ole]) <= S2v && S3i[0] * abs(crystal[2 + 5 * ole]) + S3i[1] * abs(crystal[3 + 5 * ole]) + S3i[2] * abs(crystal[4 + 5 * ole]) <= S3v)
		{

		for (ole1 = 0; ole1 < a; ole1++)
		{
		if (atomic_number[ole1] == (int)crystal[0 + 5 * ole])
		{
		new_num_atoms[ole1] = new_num_atoms[ole1] + 1;
		atomscc++;


		}

		}

		}

		}

		for (ole = 0; ole < a; ole++)
		{
		//fprintf(NewPCF, "%d ", new_num_atoms[ole]);

		}
		//fprintf(NewPCF, "\n");


		}

		*/


		fclose(uc_file);


		/*
		atoms_to_print = (float*)realloc(atoms_to_print, sizeof(float)*atomscc * 4);





		if (want_cyrcle[0] == 'y') {

		for (ole5 = 0; ole5 < a; ole5++) {
		for (ole4 = -sized[2] / 2; ole4 < sized[2] / 2; ole4++) {
		for (ole2 = -sized[1] / 2; ole2 < sized[1] / 2; ole2++) {
		for (ole = -sized[0] / 2; ole < sized[0] / 2; ole++) {
		for (ole3 = 0; ole3 < t; ole3++) {
		if (rad >= sqrt(crystal[0 + 2 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] * crystal[0 + 2 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] + crystal[1 + 2 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] * crystal[1 + 2 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] + crystal[2 + 2 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] * crystal[2 + 2 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]))
		{

		//crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][1] = direct[1+5*ole3];
		for (ole1 = 0; ole1 < 3; ole1++) {

		if (crystal[0 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] == atomic_number[ole5])
		{
		atoms_to_print[atoms_to_print_c + ole1] = crystal[ole1 + 2 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];
		//fprintf(NewPCF, "%f ", -min_xyz[ole1] + crystal[ole1 + 2 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]);
		}
		}
		if (crystal[0 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] == atomic_number[ole5])
		{
		atoms_to_print[atoms_to_print_c + 3] = atomic_number[ole5];
		atoms_to_print_c = atoms_to_print_c + 4;
		}
		}
		if (rad >= sqrt(crystal[0 + 2 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] * crystal[0 + 2 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] + crystal[1 + 2 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] * crystal[1 + 2 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] + crystal[2 + 2 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] * crystal[2 + 2 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))])) {
		if (crystal[0 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] == atomic_number[ole5])
		{
		//fprintf(NewPCF, "\n");
		}
		}

		}
		}
		}
		}
		}



		}
		else {
		for (ole5 = 0; ole5 < a; ole5++) {
		for (ole4 = -sized[2] / 2; ole4 < sized[2] / 2; ole4++) {
		for (ole2 = -sized[1] / 2; ole2 < sized[1] / 2; ole2++) {
		for (ole = -sized[0] / 2; ole < sized[0] / 2; ole++) {
		for (ole3 = 0; ole3 < t; ole3++) {
		if ((S1i[0] * abs(crystal[2 + 0 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]) <= S1v) && (S1i[0] * abs(crystal[2 + 1 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]) <= S1v) && (S1i[0] * abs(crystal[2 + 2 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]) <= S1v) && S2i[0] * abs(crystal[2 + 0 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]) + S2i[1] * abs(crystal[2 + 1 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]) <= S2v && S2i[0] * abs(crystal[2 + 0 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]) + S2i[1] * abs(crystal[2 + 2 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]) <= S2v && S2i[0] * abs(crystal[2 + 1 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]) + S2i[1] * abs(crystal[2 + 2 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]) <= S2v && S3i[0] * abs(crystal[2 + 0 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]) + S3i[1] * abs(crystal[2 + 1 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]) + S3i[2] * abs(crystal[2 + 2 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]) <= S3v)

		{

		//crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][1] = direct[1+5*ole3];
		for (ole1 = 0; ole1 < 3; ole1++) {

		if (crystal[0 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] == atomic_number[ole5])
		{
		atoms_to_print[atoms_to_print_c + ole1] = crystal[ole1 + 2 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];
		//cout << -min_xyz[ole1] + atoms_to_print[atoms_to_print_c + ole1] << " ";
		//fprintf(NewPCF, "%f ", -min_xyz[ole1] + crystal[ole1 + 2 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]);
		//cout << min_xyz[ole1] << endl;
		}
		}
		if (crystal[0 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] == atomic_number[ole5])
		{
		atoms_to_print[atoms_to_print_c + 3] = atomic_number[ole5];
		//cout << atoms_to_print[atoms_to_print_c + 3] << "\n";
		atoms_to_print_c = atoms_to_print_c + 4;
		}

		}
		if ((S1i[0] * abs(crystal[2 + 0 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]) <= S1v) && (S1i[0] * abs(crystal[2 + 1 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]) <= S1v) && (S1i[0] * abs(crystal[2 + 2 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]) <= S1v) && S2i[0] * abs(crystal[2 + 0 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]) + S2i[1] * abs(crystal[2 + 1 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]) <= S2v && S2i[0] * abs(crystal[2 + 0 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]) + S2i[1] * abs(crystal[2 + 2 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]) <= S2v && S2i[0] * abs(crystal[2 + 1 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]) + S2i[1] * abs(crystal[2 + 2 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]) <= S2v && S3i[0] * abs(crystal[2 + 0 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]) + S3i[1] * abs(crystal[2 + 1 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]) + S3i[2] * abs(crystal[2 + 2 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))]) <= S3v)

		{
		if (crystal[0 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] == atomic_number[ole5])
		{
		//fprintf(NewPCF, "\n");
		}
		}

		}
		}
		}
		}
		full = 1;
		}

		}
		*/
		atoms_to_print_c = 0;
		//fclose(NewPCF);

		fclose(periodic_table);




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
				else if ((S2v >= 2 * S1v && figure_1 != -1) || S3v <= S2v)
				{
					Scase = 3;
				}
				else if ((float(S3v) >= (float(S2v) * 3) / 2 && figure_1 != -1) || (figure_1 == -1 && S3v >= 2 * S2v))
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






		if (jgn_supercell)
		{
			was_supercell = 1;
			jgn_supercell = 1;
			Right_Hexagonal = 1;
			figure_1 = 1;
			Rod_like = 1;

			sized[0] = jgn_supercell_xyz[0];
			sized[1] = jgn_supercell_xyz[1];
			sized[2] = jgn_supercell_xyz[2];


			periodic_table = fopen("periodic_table.jgn", "r");

			crystal = (float*)realloc(crystal, sizeof(float)*(jgn_supercell_xyz[0] * jgn_supercell_xyz[1] * jgn_supercell_xyz[2] * t * 5));
			selective_dynamics = (char*)realloc(selective_dynamics, sizeof(char)*(jgn_supercell_xyz[0] * jgn_supercell_xyz[1] * jgn_supercell_xyz[2] * t * 3));
			//crystal_backup = (float*)realloc(crystal, sizeof(float)*(jgn_supercell_xyz[0] * jgn_supercell_xyz[1] * jgn_supercell_xyz[2] * t * 5));

			for (ole4 = -jgn_supercell_xyz[2] / 2; ole4 < jgn_supercell_xyz[2] / 2 + xexe[2]; ole4++) {
				for (ole2 = -jgn_supercell_xyz[1] / 2; ole2 < jgn_supercell_xyz[1] / 2 + xexe[1]; ole2++) {
					for (ole = -jgn_supercell_xyz[0] / 2; ole < jgn_supercell_xyz[0] / 2 + xexe[0]; ole++) {
						for (ole3 = 0; ole3 < t; ole3++) {
							crystal[0 + 5 * (ole3 + t * (ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[0 + 5 * ole3];//atomikos ari8mos
																																																										   //crystal_backup[0 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[0 + 5 * ole3];//atomikos ari8mos

																																																										   //crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][0] = direct[0+5*ole3];
							crystal[1 + 5 * (ole3 + t * (ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[1 + 5 * ole3];//atomiko varos
																																																										   //crystal_backup[1 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[1 + 5 * ole3];//atomiko varos

																																																										   //selective dynamics
							selective_dynamics[0 + 3 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = selective_dynamics[0 + 3 * (ole3)];
							selective_dynamics[1 + 3 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = selective_dynamics[1 + 3 * (ole3)];
							selective_dynamics[2 + 3 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = selective_dynamics[2 + 3 * (ole3)];

							if (inptype == 'd')
							{
								//crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][1] = direct[1+5*ole3];
								for (ole1 = 0; ole1 < 3; ole1++) {
									crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = uccartesian[ole1 + 3 * ole3] + ole * ijk[0][ole1] + ole2 * ijk[1][ole1] + ole4 * ijk[2][ole1];//cartesians
																																																																	//crystal_backup[ole1 + 2 + 5 * (ole3 + t*(ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = uccartesian[ole1 + 3 * ole3] + ole*ijk[0][ole1] + ole2*ijk[1][ole1] + ole4*ijk[2][ole1];//cartesians

									if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] < min_xyz[ole1])
									{
										min_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

									}
									if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] > max_xyz[ole1])
									{
										max_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

									}

								}

							}
							else if (inptype == 'c')
							{
								for (ole1 = 0; ole1 < 3; ole1++) {
									crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = my_direct[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];//cartesians
									crystal_backup[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = my_direct[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];//cartesians

																																																																											   //crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][ole1 + 2] = uccartesian[ole1+3*ole3] + ole*ijk[0][ole1] + ole2*ijk[1][ole1] + ole4*ijk[2][ole1];
									if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] < min_xyz[ole1])
									{
										min_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

									}
									if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] > max_xyz[ole1])
									{
										max_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

									}

								}
							}


							rewind(periodic_table);

						}
					}
				}
			}


			fclose(periodic_table);


		}
	}
	
}