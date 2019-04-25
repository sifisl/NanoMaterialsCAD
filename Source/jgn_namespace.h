#pragma once

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

	///////////////////////////////////////////////////////////////////////just a vec3
	class vec3
	{
	public:
		float x, y, z;
		vec3() {};
		vec3(float i, float j, float k)
		{
			x = i;
			y = j;
			z = k;
		}
		vec3(const vec3& other)
		{
			x = other.x;
			y = other.y;
			z = other.z;
		}
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

#define vec3ToGlfloat(v) {v.x, v.y, v.z, 1.0}

#define glTranslatefvec3(v) glTranslatef(v.x/(Svmax + 5) , v.y/(Svmax + 5) , v.z/(Svmax + 5))