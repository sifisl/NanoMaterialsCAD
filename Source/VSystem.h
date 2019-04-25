#pragma once

#include "stdafx.h"

////////////////////////////////
//helping classes
class Group
{
public:
	Group() {};
	void _Group(int N_a, int N_t) { N_atoms = N_a; _N_types = N_t; _reserve(N_a); };/*(number_of_atoms, number_of_types)*/
	~Group() {};

	unsigned int N_atoms;//number of atoms
	jgn::vec3 primitiveVec[3];//the simumation box
	std::vector<jgn::vec3> position;
	std::vector<jgn::string> type;
	int _N_types;
	std::vector<jgn::string> _alltype;
	std::vector<jgn::string> selective_dynamics;
	std::vector<jgn::vec3> color;
	std::vector<float> number;//atomic number
	std::vector<float> weight;//atomic weight
	std::vector<float> radius;
	std::vector<bool> isSelected;
	std::vector<bool> isdeleted;
	std::vector<bool> iscut;//if the atoms is cut by a surface

	void _reserve(const unsigned int N_a);
	void N_types(const unsigned int N_t);
};


class VSystem
{
public:

	VSystem();
	~VSystem();

	int N_groups = 0;//#N of groups
	int N_types = 0;//#N of different elements
	std::vector<jgn::string> types;//#N of different elements
	int N_atoms = 0;// total #N of the system


	std::vector<Group> group;
	std::vector<int> deletedHistory;

	void draw();

}EXT vsystem;




