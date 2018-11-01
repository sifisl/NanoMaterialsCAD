#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#define WIN32_LEAN_AND_MEAN


#ifdef JGN_SOURCE_CPP
#define EXT 
#else
#define EXT extern
#endif //SOURCE_CPP


//TODO: custom surface to buildposcar
//TODO: custom surface and vacum^ to buildlammps


#ifndef _WIN32_IE			// Allow use of features specific to IE 6.0 or later.
#define _WIN32_IE 0x0600
#endif

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#include <iostream>
#include <chrono>
#include <map>
#include <cstring>
#include <string>
#include <ctime>
#include <cctype>
using namespace std;

#include <stdlib.h>
# include <cstdlib>
# include <cmath>
# include <fstream>
# include <iomanip>
//#include ".\include\GL\glew.h"
//# include ".\freeglut\include\GL\freeglut.h"
//# include "./include\GL\glut.h"
#include <stdio.h>
#include <string.h>
#include <setjmp.h>
#include <float.h>



//#pragma comment (lib, "lib/glew32.lib")
//#pragma comment (lib, "lib/glut32.lib")
#pragma comment (lib, "opengl32.lib")
#pragma comment (lib, "libcmtd.lib")



// Windows Header Files:
#include <windows.h>
#include <Windowsx.h>
#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "opengl32.lib")
#include <gl\GL.h>
#include <gl\GLU.h>
//#include "glm\glm.hpp"
#include <commctrl.h>
#include <Shellapi.h>
#include <Shlwapi.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>






char *
ftoa(float f)
#ifdef JGN_SOURCE_CPP
{
	static char        buf[17];
	char *            cp = buf;
	unsigned long    l, rem;

	if (f < 0) {
		*cp++ = '-';
		f = -f;
	}
	l = (unsigned long)f;
	f -= (float)l;
	rem = (unsigned long)(f * 1e6);
	sprintf(cp, "%lu.%6.6lu", l, rem);
	return buf;
}
#else
;
#endif// JGN_SOURCE_CPP




namespace jgn
{
	double atof(char* c)
#ifdef JGN_SOURCE_CPP
	{
		if (c == NULL)
		{
			return -1.11111;
		}
		else
		{
			return std::atof(c);
		}
	}
#else
;
#endif// JGN_SOURCE_CPP



	class string : public std::string {

	public:
		bool isnumber()
		{
			std::string::const_iterator it = this->begin();
			int dotread = 0;
			while (it != this->end() && (std::isdigit(*it) || *it == '.'))
			{
				if (*it == '.')
				{
					dotread++;
				}
				if (dotread == 2)break;

				++it;

			}
			return (!(this->empty()) && it == (this->end()));
		}
	};

}

jgn::string LPTSTR2string(LPTSTR inp, char delimiter, int maxchars = 1000)
#ifdef JGN_SOURCE_CPP
{
	jgn::string out;
	while ((((char*)inp)[0] != delimiter) && maxchars != 0)
	{
		out += ((char*)inp)[0];
		inp = inp + 1;
		maxchars--;
	}
	return out;
}
#else
;
#endif// JGN_SOURCE_CPP



/////////////////////////////////////////////////////////////
//
// cpp global
//


#pragma warning (disable : 4996)

#define DOUBLE_MOD

#ifdef DOUBLE_MOD

#define float double
#define glColor3fv glColor3dv
#define glVertex3fv glVertex3dv
#define printformat 15
#define fl_max DBL_MAX
#define fl_min DBL_MIN

#else

#define printformat 6
#define fl_max FLT_MAX
#define fl_min DBL_MIN


#endif


void myReshape(int w, int h);
void display1();
void spin_image();
void mouse_pasive(int x, int y);
void myinit();
void keyboardgl(int key, int s, int x, int y);
void menuf(int c);
void BuildPoscar(char* a);
void BuildLammps(char* a);
void Sub_Menu(int c);
void mouse_func(int b, int s, int x, int y);
void lines_param();
void jgnCommands(LPTSTR ttt, int d);
void variableinit();
void JGN_QRedisplay();
//
//  Global data.
//

EXT std::size_t found;
EXT char ftype;// p=poscar, l=lammps
#define SBYTES 200


EXT char* NewPC;

EXT char* PCtype;

EXT int lmb;
EXT int wasfullscreenflagin;
EXT int wasfullscreenflagout;
EXT GLuint Font;
EXT GLuint vboId;
EXT float dipleft;
EXT float perspective_on;
EXT GLfloat theta[3];
EXT int flagmax;
EXT GLfloat first;
EXT GLfloat second;
EXT GLfloat third;
EXT GLfloat forth;
EXT GLfloat fifth;
EXT GLfloat sixth;
EXT GLfloat seventh;
EXT GLfloat eighth;
EXT GLfloat nineth;
EXT GLfloat tenth;
EXT GLfloat eleventh;
EXT std::chrono::time_point<std::chrono::steady_clock> cl_start;
EXT std::chrono::time_point<std::chrono::steady_clock> cl_end;
EXT std::chrono::duration<float> cl_duration;
EXT int sphStacks;
EXT int sphSides;
EXT bool qredisplay;
EXT double xyz_range[3];
EXT double xyz_scale;
EXT double xyz_center[3];
EXT int allatoms;
EXT long int sized[3];
EXT long int t/*how many atoms in the unit cell*/;
EXT long int prev_sized[3];
EXT float Truncated_Cube_max[3];
EXT float min_xyz[3];
EXT float max_xyz[3];
EXT int mouse_check;
EXT float mouse_y, mouse_x;
EXT long int ole, ole1, ole2, ole3, ole4, ole5;
EXT float *crystal;
EXT float *crystal_backup;
EXT char *selective_dynamics;
//float tube_rin = 20, tube_rout = 30, tube_param = 80;
EXT float colr[3];
EXT float rad;
EXT char want_cyrcle[5];
EXT int nanotube;
EXT int full;
EXT float zmax100111[3];
EXT float zmax100111_[3];
EXT int Scase;
EXT float figure_1;
EXT float Right_Hexagonal;
EXT float Right_Hexagonal_height;
EXT float *aweights;
EXT float pointsize;
EXT float truepointsize;
EXT bool vacuum;// 0=false, 1=true
EXT int *anumber;//atomic number
EXT char ss[20];
EXT int *aatoms;// real time atoms cound
EXT int Svmax_buckup;
EXT float Rod_like;
EXT int width, height;
EXT int jgn_supercell;
EXT int jgn_supercell_xyz[3];
EXT float *my_direct, *uccartesian;
EXT float ijk[3][3];//ta 3 dianismata symmetrias
				//dn kserw posa diaforetika atoma 9a exei...
				//o kristallos. ypo8etw oti dn 8a einai panw apo 5
				//kai ka8e ena exei 3 bytes gia na xwresei kai to \0

EXT int xexe[3];
EXT int sized_old[3];
EXT int was_supercell;
EXT HWND hWndCommandLine;
EXT HWND hWndList;


EXT char *S1;
EXT char *S2;
EXT char *S3;
EXT char *s1;
EXT bool render_is_on;
EXT int S1v, S2v, S3v;
EXT int S1i[3], S2i[3], S3i[3];
EXT char S1a;
EXT int Svmax;
EXT jmp_buf  build_posc_jmp;
EXT int jgn_file_dropd ;
EXT LPTSTR lpszFile;
EXT char inpf[500];
EXT TCHAR CommandBuffer[500];
EXT INPUT keybinp;
EXT HWND CommandTextHistory;
EXT int my_postmessages_count;
EXT int CustomSurfacesCount;
EXT float **CustomSurfaces;
EXT int CustomSurfacesOn;
EXT HBRUSH brush;
EXT HFONT fOnt;
EXT char *help;
EXT int loop;
EXT int sizedprotector[3];
EXT int anotherokrender;
EXT int wait;
EXT int custom_sized[3];
EXT int itemsel;
EXT int predicted;
EXT wchar_t widechar[50];
EXT char* listboxcurent;
EXT map<int, char*> boxlistmap;					// map hwnd of the parent windows created to an int counter
EXT wchar_t ucender[2];
EXT WNDPROC oldEditProc;
EXT int mainwndsize[2];
EXT int cmdwndh;
EXT long* mnrcpt;
EXT HWND hwndcmdjgn;
EXT HWND mnhwnd;
EXT HWND CommandTextField;
EXT LPRECT glb_rct;


EXT int ball_atoms;
EXT int ballflag;
EXT char *uc_file_input;
EXT float theta_pr[2];
EXT int *atomic_number;
EXT int *new_num_atoms;
EXT int i, j, k;
EXT float fak;
EXT char *shelp;
EXT char *atomshelp;
EXT char* token3;
EXT float sim_box_lo[3];

EXT int shperes_on;// render as spheres or points

#if defined(JGN_COMMANDS_CPP) || defined(JGN_WINDOWS_CPP)

static const int testsc = 10;
static char *test1[testsc] = { "vector(",
"clean",
"undo",
"supercell(",
"plane(",
"fopen(",
"spheres",
"points",
"rand(",
"render "
};
static char *test1low[testsc] = { "vector(",
"clean",
"undo",
"supercell(",
"plane(",
"fopen(",
"spheres",
"points",
"rand(",
"render "
};
static wchar_t *helplist[testsc] = { L"vector(int h,int c,int l,int A)",
L"clean",
L"undo",
L"supercell(int a1,int a2,int a3)",
L"plane(int u,int v,int w,int A)",
L"fopen(char* file path)",
L"spheres",
L"points",
L"rand(float r)",
L"render on/off"
};
#endif	// JGN_SOURCE_CPP



EXT bool selective_dynamics_bool;
EXT char* jgncmdfpath;
EXT FILE* jgncmdfile;
EXT char jgncmdfline[100];
EXT char inptype;
EXT float vec[3];
EXT int crystalh;
EXT int crystalk;
EXT int crystall;
EXT int atomscc;
EXT float* atoms_to_print;
EXT int atoms_to_print_c;
EXT char* atoms;
EXT int a;//a: posa eidi atomwn
EXT float *an_and_aw;
EXT float helping1, helping2, helping3;
EXT float helpme34[3][4];
EXT float helpme14[1][4];
EXT bool shift_down ;
EXT float glob_translate[3];
EXT float glob_translate_prev[3];
EXT int db;

float JGN_Det3x3(float x1, float y1, float z1,
	float x2, float y2, float z2,
	float x3, float y3, float z3)
#ifdef JGN_SOURCE_CPP
{
	float ans = x1 * (y2*z3 - z2 * y3) - y1 * (x2*z3 - x3 * z2) + z1 * (x2*y3 - x3 * y2);

	return ans;

}
#else
	;
#endif //JGN_SOURCE_CPP


////////winproc
EXT HDC hdc;
EXT LARGE_INTEGER lpPerformanceCount;

//QueryPerformanceCounter(&lpPerformanceCount);

EXT int wmId, wmEvent;
EXT char* token, *token1, *s;
EXT int *ea;
EXT FILE* uc_file;

EXT int line, p;//line: gia na kserw se poia gramh eimai
					//p:diksths gia ta dianismata

					//t:ari8mos olwn twn atomwn sto unit cell
					//ole1: voi8itikos
EXT float actor;//actor: einai aytos o pollaplasiasths panw apo ta vectors						


EXT FILE* periodic_table;
EXT int alloena;
EXT int ka8isterimenoflag;
EXT FILE *NewPCF;
EXT int help0;
EXT int help1;




void debug(int num)
#ifdef JGN_SOURCE_CPP
{
	cout << "debug: " << num << endl;
	getchar();
}
#else
;
#endif// JGN_SOURCE_CPP





