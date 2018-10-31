#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES

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


namespace jgn
{
	double atof(char* c)
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
{
	jgn::string out;
	while ((((char*)inp)[0] != delimiter) && maxchars!=0)
	{
		out += ((char*)inp)[0];
		inp = inp + 1;
		maxchars--;
	}
	return out;
}

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
//
//  Global data.
//

std::size_t found;
char ftype;// p=poscar, l=lammps
#define SBYTES 200


char* NewPC = (char*)malloc(sizeof(char)*(200));

char* PCtype = (char*)malloc(sizeof(char)*100);

int lmb = 0;
int wasfullscreenflagin = 0, wasfullscreenflagout = -1;
GLuint Font;
GLuint vboId;
float dipleft =- 1000.0 / 800.0;
float perspective_on = 0;
static GLfloat theta[3] = { 0.0, 0.0, 0.0 };
int flagmax = 0;
GLfloat first = 0;
GLfloat second =0;
GLfloat third = 0;
GLfloat forth = 0;
GLfloat fifth = 0;
GLfloat sixth = 0;
GLfloat seventh = 0;
GLfloat eighth =0;
GLfloat nineth = 0;
GLfloat tenth = 0;
GLfloat eleventh = 0;
std::chrono::time_point<std::chrono::steady_clock> cl_start, cl_end;
std::chrono::duration<float> cl_duration;
int sphStacks = 10;
int sphSides = 10;
bool qredisplay = false;
double xyz_range[3];
double xyz_scale;
double xyz_center[3];
int allatoms;
long int sized[3], t = 0/*how many atoms in the unit cell*/;
long int prev_sized[3] = { 1,1,1 };
float Truncated_Cube_max[] = { 0.0 , 0.0, 0.0 };
float min_xyz[3] = { FLT_MAX,FLT_MAX,FLT_MAX }, max_xyz[3] = { FLT_MIN,FLT_MIN,FLT_MIN };
int mouse_check = 0;
float mouse_y, mouse_x;
long int ole, ole1, ole2, ole3, ole4, ole5;
float *crystal = NULL;
float *crystal_backup = NULL;
char *selective_dynamics = NULL;
//float tube_rin = 20, tube_rout = 30, tube_param = 80;
float colr[3], rad = 20;
char want_cyrcle[5] = { 'n','o', 'l','l','l'};
int nanotube = 0;
int full = 0;
float zmax100111[3] = { 0.0,0.0,0.0 };
float zmax100111_[3] = { 0.0,0.0,0.0 };
int Scase = 1000;
float figure_1 = 1.0;
float Right_Hexagonal = 1.0;
float Right_Hexagonal_height = 20.0;
float *aweights;
float pointsize;
float truepointsize;
bool vacuum = false;// 0=false, 1=true
int *anumber;//atomic number
char ss[20];
int *aatoms;// real time atoms cound
int Svmax_buckup;
float Rod_like = 1.0;
int width = 1000, height = 800;
int jgn_supercell = 0;
int jgn_supercell_xyz[3] = { 10,10,10 };
float *my_direct=NULL, *uccartesian=NULL;
float ijk[3][3];//ta 3 dianismata symmetrias
				//dn kserw posa diaforetika atoma 9a exei...
				//o kristallos. ypo8etw oti dn 8a einai panw apo 5
				//kai ka8e ena exei 3 bytes gia na xwresei kai to \0

int xexe[3] = { 0 };
int sized_old[3];
int was_supercell = 0;
HWND hWndCommandLine = NULL;
HWND hWndList = NULL;


char *S1 = (char*)malloc(sizeof(char) * 4);
char *S2 = (char*)malloc(sizeof(char) * 4);
char *S3 = (char*)malloc(sizeof(char) * 4);
char *s1 = (char*)malloc(sizeof(char) * 50);
bool render_is_on = true;
int S1v = 25, S2v = 30, S3v = 40;
int S1i[3] = { 0,0,0 }, S2i[3] = { 0,0,0 }, S3i[3] = { 0,0,0 };
char S1a;
int Svmax = 0;
jmp_buf  build_posc_jmp;
int jgn_file_dropd = 0;
LPTSTR lpszFile = (LPTSTR)malloc(sizeof(char) * 500);
char inpf[500] = { 0 };
TCHAR CommandBuffer[500];
INPUT keybinp;
HWND CommandTextHistory = NULL;
int my_postmessages_count = 0;
int CustomSurfacesCount = 0;
float **CustomSurfaces = NULL;
int CustomSurfacesOn = 0;
HBRUSH brush;
HFONT fOnt;
char *help;
int loop = 0;
int sizedprotector[3] = { 0 };
int anotherokrender = 0;
int wait = 0;
int custom_sized[3] = { 1,1,1 };
int itemsel = -1;
int predicted = 0;
wchar_t widechar[50];
char* listboxcurent = 0;
map<int, char*> boxlistmap;					// map hwnd of the parent windows created to an int counter
wchar_t ucender[2];
WNDPROC oldEditProc;
int mainwndsize[2] = { 1016,858 };
int cmdwndh = 300;
long* mnrcpt;
HWND hwndcmdjgn;
HWND mnhwnd;
HWND CommandTextField = NULL;
LPRECT glb_rct = (LPRECT)malloc(sizeof(RECT));


int ball_atoms = 0;
int ballflag = 0;
char *uc_file_input;
#define pi 3.141592
float theta_pr[2] = { 0,0 };
int *atomic_number=NULL;
int *new_num_atoms=NULL;
int i = 1, j = 1, k = 1;
float fak;
char *shelp = 0;
char *atomshelp = NULL;
char* token3 = 0;
float sim_box_lo[3];

int shperes_on = 1;// render as spheres or points

const int testsc = 10;
char *test1[testsc] = { "vector(",
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
char *test1low[testsc] = { "vector(",
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
wchar_t *helplist[testsc] = { L"vector(int h,int c,int l,int A)",
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
bool selective_dynamics_bool;
char* jgncmdfpath;
FILE* jgncmdfile;
char jgncmdfline[100];
char inptype = '\0';
float vec[3];
int crystalh = 0;
int crystalk = 0;
int crystall = 0;
int atomscc = 0;
float* atoms_to_print = NULL;
int atoms_to_print_c = 0;
char* atoms=NULL;
int a = 0;//a: posa eidi atomwn
float *an_and_aw=NULL;
float helping1, helping2, helping3;
float helpme34[3][4];
float helpme14[1][4];
bool shift_down = false;
float glob_translate[3] = { 0,0,0 };
float glob_translate_prev[3] = { 0,0,0 };
int db = 0;

float JGN_Det3x3(float x1, float y1, float z1, 
				float x2, float y2, float z2, 
				float x3, float y3, float z3)
{
	float ans = x1*(y2*z3 - z2*y3) - y1*(x2*z3 - x3*z2) + z1*(x2*y3 - x3*y2);

	return ans;

}


////////winproc
HDC hdc;
LARGE_INTEGER lpPerformanceCount;

//QueryPerformanceCounter(&lpPerformanceCount);

int wmId, wmEvent;
char* token, *token1, *s;
int *ea=NULL;
FILE* uc_file;

int line = 2, p = 0;//line: gia na kserw se poia gramh eimai
					//p:diksths gia ta dianismata

					//t:ari8mos olwn twn atomwn sto unit cell
					//ole1: voi8itikos
float actor;//actor: einai aytos o pollaplasiasths panw apo ta vectors						


FILE* periodic_table;
int alloena = 0;
int ka8isterimenoflag = 0;
FILE *NewPCF;
int help0;
int help1;




void debug(int num)
{
	cout << "debug: " << num << endl;
	getchar();
}




