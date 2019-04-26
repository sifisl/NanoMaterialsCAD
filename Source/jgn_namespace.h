#pragma once
#include "JGN_bmpLoader.h"
extern float *crystal;
extern float *crystal_backup;
extern char *selective_dynamics;
extern bool *isSelected;
extern long int t;
extern long int sized[3];
extern bool *isSelected;
extern bool *isdeleted;
extern int *deletedHistory;
extern bool *isdeleted;
extern int *deletedHistory;
extern int jgn_supercell_xyz[3];


namespace jgn
{
	///////////////////////////////////////////////////////////////////////char[] to float
	float atof(char* c)
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

	///////////////////////////////////////////////////////////////////////float to char[]
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

	///////////////////////////////////////////////////////////////////////3x3 determinant

	float Det3x3(float x1, float y1, float z1,
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

	///////////////////////////////////////////////////////////////////////3d space rotation operation

	void cpu_rotate(float p[3], float a[3], float *out)
#ifdef JGN_SOURCE_CPP

	{
		float p_bck1[3];
		float p_bck2[3];

		//z rotation
		p_bck1[0] = cos(a[2])*p[0] - sin(a[2])*p[1];
		p_bck1[1] = sin(a[2])*p[0] + cos(a[2])*p[1];
		p_bck1[2] = p[2];

		//x rotation
		p_bck2[0] = p_bck1[0];
		p_bck2[1] = cos(a[0])*p_bck1[1] - sin(a[0])*p_bck1[2];
		p_bck2[2] = sin(a[0])*p_bck1[1] + cos(a[0])*p_bck1[2];

		//y rotation
		out[0] = cos(a[1])*p_bck2[0] + sin(a[1])*p_bck2[2];
		out[1] = p_bck2[1];
		out[2] = -sin(a[1])*p_bck2[0] + cos(a[2])*p_bck2[2];



	}
#else
		;
#endif //JGN_SOURCE_CPP

	///////////////////////////////////////////////////////////////////////3d space translation operation
	void cpu_translate(float p[3], float a[3], float *out)
#ifdef JGN_SOURCE_CPP

	{
		out[0] = p[0] + a[0];
		out[1] = p[1] + a[1];
		out[2] = p[2] + a[2];
	}
#else
		;
#endif //JGN_SOURCE_CPP

	///////////////////////////////////////////////////////////////////////2d distance between 2 points
	float dist2d(float* p1, float* p2)
#ifdef JGN_SOURCE_CPP

	{
		return sqrt((p1[0] - p2[0])*(p1[0] - p2[0]) + (p1[1] - p2[1])*(p1[1] - p2[1]));
	}
#else
		;
#endif //JGN_SOURCE_CPP

	///////////////////////////////////////////////////////////////////////3d -power of 2- distance between 2 points 
	float dist3dSquare(float& p1, float& p2)//I don't use sqrt for optimization
#ifdef JGN_SOURCE_CPP

	{
		return /*sqrt(*/((&p1)[0] - (&p2)[0])*((&p1)[0] - (&p2)[0]) + ((&p1)[1] - (&p2)[1])*((&p1)[1] - (&p2)[1]) + ((&p1)[2] - (&p2)[2])*((&p1)[2] - (&p2)[2])/*)*/;
	}
#else
		;
#endif //JGN_SOURCE_CPP

	//TODO:redo all that with vectors
	///////////////////////////////////////////////////////////////////////heap allocations
	void heapRealloc()
#ifdef JGN_SOURCE_CPP
	{
		crystal = (float*)realloc(crystal, sizeof(float)*(jgn_supercell_xyz[0] * jgn_supercell_xyz[1] * jgn_supercell_xyz[2] * t * 5));
		crystal_backup = (float*)realloc(NULL, sizeof(float)*(sized[0] * sized[1] * sized[2] * t * 5));
		selective_dynamics = (char*)realloc(selective_dynamics, sizeof(char)*(jgn_supercell_xyz[0] * jgn_supercell_xyz[1] * jgn_supercell_xyz[2] * t * 3));
		isSelected = (bool*)realloc(isSelected, sizeof(bool)*t*sized[0] * sized[1] * sized[2]);
		for (int i = 0; i < t*sized[0] * sized[1] * sized[2]; i++)
		{
			isSelected[i] = false;
		}
		//isdeleted = (bool*)realloc(isdeleted, sizeof(bool)*t*sized[0] * sized[1] * sized[2]);
		isdeleted = (bool*)realloc(isdeleted, sizeof(bool)*t*jgn_supercell_xyz[0] * jgn_supercell_xyz[1] * jgn_supercell_xyz[2]);
		deletedHistory = (int*)realloc(deletedHistory, sizeof(int)*t*sized[0] * sized[1] * sized[2]);
		for (int i = 0; i < t*sized[0] * sized[1] * sized[2]; i++)
		{
			isdeleted[i] = false;
			deletedHistory[i] = 0;
		}
	}
#else
		;
#endif //JGN_SOURCE_CPP

	///////////////////////////////////////////////////////////////////////some extra string functionality
	class string : public std::string {

	public:
		string() {};
		string(char* c) : std::string(c) {};
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

	///////////////////////////////////////////////////////////////////////LPTSTR to string
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
	///////////////////////////////////////////////////////////////////////just a vec2
	class vec2
	{
	public:
		float x, y;
		vec2() {}
		vec2(float i, float j)
		{
			x = i;
			y = j;
		}
		vec2(const jgn::vec2& other)
		{
			x = other.x;
			y = other.y;
		}
	};
	///////////////////////////////////////////////////////////////////////just a vec3
	class vec3
	{
	public:
		float x, y, z;
		vec3() {}
		vec3(float i, float j, float k)
		{
			x = i;
			y = j;
			z = k;
		}
		vec3(const jgn::vec3& other)
		{
			x = other.x;
			y = other.y;
			z = other.z;
		}

		float abs()
#ifdef JGN_SOURCE_CPP
		{
			return sqrt(x *  x + y * y + z * z);
		}
#else
		;
#endif// JGN_SOURCE_CPP

		jgn::vec3 translate(jgn::vec3 v);


		jgn::vec3 rotate(jgn::vec3 v)
#ifdef JGN_SOURCE_CPP
		{
			jgn::vec3 p_bck1;
			jgn::vec3 p_bck2;
			jgn::vec3 out;
			//z rotation
			p_bck1.x = cos(v.z)*this->x - sin(v.z)*this->y;
			p_bck1.y = sin(v.z)*this->x + cos(v.z)*this->y;
			p_bck1.z = this->z;
			//x rotation
			p_bck2.x = p_bck1.x;
			p_bck2.y = cos(v.x)*p_bck1.y - sin(v.x)*p_bck1.z;
			p_bck2.z = sin(v.x)*p_bck1.y + cos(v.x)*p_bck1.z;
			//y rotation
			out.x = cos(v.y)*p_bck2.x + sin(v.y)*p_bck2.z;
			out.y = p_bck2.y;
			out.z = -sin(v.y)*p_bck2.x + cos(v.y)*p_bck2.z;
			return out;
		}
#else
			;
#endif// JGN_SOURCE_CPP
	};

	///////////////////////////////////////////////////////////////////////just a vec6
	class vec6d
	{
	public:
		vec3 start;
		vec3 fin;

		vec6d(float i, float j, float k, float ii, float jj, float kk)
		{
			this->start.x = i;
			this->start.y = j;
			this->start.z = k;

			this->fin.z = ii;
			this->fin.z = jj;
			this->fin.z = kk;

		}
		vec6d(const vec6d& other)
		{
			this->start = other.start;
			this->fin = other.fin;
		}
	};

	///////////////////////////////////////////////////////////////////////
#if NDEBUG
#else
	void debug(int num)
#ifdef JGN_SOURCE_CPP
	{
		std::cout << "debug: " << num << std::endl;
		getchar();
	}
#else
		;
#endif// JGN_SOURCE_CPP
#endif// NDEBUG
};




//////////////operators overload/////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////

std::ostream& operator<<(std::ostream& stream, const jgn::vec3& vect)
#ifdef JGN_SOURCE_CPP

{
	stream << vect.x << " , " << vect.y << " , " << vect.z;
	return stream;
}
#else
;
#endif// JGN_SOURCE_CPP

std::ostream& operator<<(std::ostream& stream, const jgn::vec6d& vect)
#ifdef JGN_SOURCE_CPP

{
	stream << vect.start << vect.fin;
	return stream;
}
#else
;
#endif// JGN_SOURCE_CPP

std::ostream& operator<<(std::ostream& stream, const std::vector<jgn::vec6d>& vect)
#ifdef JGN_SOURCE_CPP

{
	for (std::vector<jgn::vec6d>::const_iterator i = vect.begin(); i != vect.end(); i++)
	{
		stream << " , " << *i;
	}

	return stream;
}
#else
;
#endif// JGN_SOURCE_CPP

jgn::vec3 operator/(const jgn::vec3& v, const int& i)
#ifdef JGN_SOURCE_CPP

{
	jgn::vec3 out;
	out.x = v.x/i;
	out.y = v.y/i;
	out.z = v.z/i;
	return out;
}
#else
;
#endif// JGN_SOURCE_CPP

jgn::vec3 operator*(const jgn::vec3& v, const int& i)
#ifdef JGN_SOURCE_CPP

{
	jgn::vec3 out;
	out.x = v.x*i;
	out.y = v.y*i;
	out.z = v.z*i;
	return out;
}
#else
;
#endif// JGN_SOURCE_CPP

jgn::vec3 operator+(const jgn::vec3& v1, const jgn::vec3& v2)
#ifdef JGN_SOURCE_CPP

{
	jgn::vec3 out;
	out.x = v1.x + v2.x;
	out.y = v1.y + v2.y;
	out.z = v1.z + v2.z;
	return out;
}
#else
;
#endif// JGN_SOURCE_CPP

/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////functions body

#ifdef JGN_SOURCE_CPP
jgn::vec3 jgn::vec3::translate(jgn::vec3 v)
{
	return (*this) + v;
}
#endif// JGN_SOURCE_CPP

#define vec3ToGlfloat4(v) {v.x, v.y, v.z, 1.0}
#define glTranslatefvec3(v) glTranslatef(v.x/(Svmax + 5) , v.y/(Svmax + 5) , v.z/(Svmax + 5))
#define glVertex3dvec3(v) glVertex3d(v.x, v.y, v.z)
#define glVertex2dvec3(v) glVertex2d(v.x, v.y)


///////////////////////////////////////////////////////////////////////////////////////////
//TODO: a huge funtion that needs to be changes

void drawMoldsLines(float *p, float *p1)
#ifdef JGN_SOURCE_CPP
{
glBegin(GL_LINES);
if (jgn_supercell || nanotube)
{
}
else if (CustomSurfacesOn)
{
	if (DrawDistanceLine)
	{
		colr[0] = 0;
		colr[1] = 0;
		colr[2] = 0;
		GLfloat mat_ambient[] = { colr[0], colr[1], colr[2], 1.0 };
		GLfloat mat_deffuse[] = { colr[0], colr[1], colr[2], 1.0 };

		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_deffuse);
		ole3 = ClickedForDistance[0];
		p[0] = crystal[2 + 5 * ole3] / (Svmax + 5);
		p[1] = crystal[3 + 5 * ole3] / (Svmax + 5);
		p[2] = crystal[4 + 5 * ole3] / (Svmax + 5);
		//cout << ClickedForDistance[0] << " " << ClickedForDistance[1] << endl;
		//cout << "p = " << p[0] << " " << p[1] << " " << p[2] << endl;
		ole3 = ClickedForDistance[1];
		glVertex3fv(p1);
		glEnd();

	}
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
			S3v = S2v * 2;

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
					glVertex3f(i*float(S2v*0.866025404) / (Svmax + 5), j*asdf, k*0.88*float(S2v / 0.866025404 - 2 * S2v *0.866025404) / ((Svmax + 5)));
					glVertex3f(i*float(S2v *0.866025404) / (Svmax + 5), j*asdf, 0);

					glVertex3f(i*float(S2v *0.866025404) / (Svmax + 5), j*asdf, k*0.88*float(S2v / 0.866025404 - 2 * S2v *0.866025404) / ((Svmax + 5)));
					glVertex3f(i*float(S2v *0.866025404) / (Svmax + 5), 0, k*0.88*float(S2v / 0.866025404 - 2 * S2v *0.866025404) / ((Svmax + 5)));


					glVertex3f(0, j*asdf, k*float(S2v) / ((Svmax + 5)));
					glVertex3f(i*float(S2v *0.866025404) / (Svmax + 5), j*asdf, -k * 0.88*float(S2v / 0.866025404 - 2 * S2v *0.866025404) / ((Svmax + 5)));

					glVertex3f(0, j*asdf, k*float(S2v) / ((Svmax + 5)));
					glVertex3f(0, 0, k*float(S2v) / ((Svmax + 5)));
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
					glVertex3f(k*0.86*float(S1v / 0.866025404 - 2 * S1v *0.866025404) / ((Svmax + 5)), j*asdf, i*float(S1v *0.866025404) / (Svmax + 5));
					glVertex3f(0, j*asdf, i*float(S1v *0.866025404) / (Svmax + 5));

					glVertex3f(k*0.86*float(S1v / 0.866025404 - 2 * S1v *0.866025404) / ((Svmax + 5)), j*asdf, i*float(S1v *0.866025404) / (Svmax + 5));
					glVertex3f(k*0.86*float(S1v / 0.866025404 - 2 * S1v *0.866025404) / ((Svmax + 5)), 0, i*float(S1v *0.866025404) / (Svmax + 5));


					glVertex3f(k*float(S1v) / ((Svmax + 5)), j*asdf, 0);
					glVertex3f(-k * 0.86*float(S1v / 0.866025404 - 2 * S1v *0.866025404) / ((Svmax + 5)), j*asdf, i*float(S1v *0.866025404) / (Svmax + 5));

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
					glVertex3f(i*(float(S2v) *0.866025404) / (Svmax + 5), j*asdf, k*0.88*float(2 * S1v - 2 * (S2v)*0.866025404) / (Svmax + 5));




					glVertex3f(i*(float(S2v) *0.866025404) / (Svmax + 5), j*asdf, k*0.88*float(2 * S1v - 2 * (S2v)*0.866025404) / (Svmax + 5));
					glVertex3f(i*(float(S2v) *0.866025404) / (Svmax + 5), 0, k*0.88*float(2 * S1v - 2 * (S2v)*0.866025404) / (Svmax + 5));


					glVertex3f(i*0.88*(float(2 * S2v - 2 * S1v *0.866025404)) / (Svmax + 5), j*asdf, k*(float(S1v) *0.866025404) / (Svmax + 5));
					glVertex3f(0, j*asdf, k*(float(S1v) *0.866025404) / (Svmax + 5));


					glVertex3f(i*0.88*(float(2 * S2v - 2 * S1v *0.866025404)) / (Svmax + 5), j*asdf, k*(float(S1v) *0.866025404) / (Svmax + 5));
					glVertex3f(i*0.88*(float(2 * S2v - 2 * S1v *0.866025404)) / (Svmax + 5), 0, k*(float(S1v) *0.866025404) / (Svmax + 5));

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
}
#else
;
#endif// JGN_SOURCE_CPP


void LoadBMP(char* file, unsigned int* ID)
#ifdef JGN_SOURCE_CPP
{
	JGN_bmpLoad(file, JGN_RGBA);
	glGenTextures(1, ID);
	glBindTexture(GL_TEXTURE_2D, *ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, JGN_bmpWidth, JGN_bmpHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, JGN_bmpData);
}
#else
;
#endif// JGN_SOURCE_CPP