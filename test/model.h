#ifndef MODEL_H_INCLUDED
#define MODEL_H_INCLUDED

#include "readData.h"

struct Solution {
	double UB;
	double LB;
	double time;
	double openNodes;
	vector <int> items;
};

void createLP(Data* data, Solution* sol);

#endif