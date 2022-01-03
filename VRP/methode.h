#ifndef METHODE_H_INCLUDED
#define METHODE_H_INCLUDED

#include "readData.h"
#include <time.h>
#include <iostream>     // std::cout, std::fixed
#include <iomanip>      // std::setprecision
#include <cstdio>

struct Solution {
	double cost;		//Solution cost
	double time;		//Running time
	vector <vector <int>> routes;	//Solution
	double UB;
	double LB;
};

void construction(Data* data, Solution* sol);
void getCost(Data *data, Solution *sol);
void printSolutionInFile(Data* data, Solution* sol);


#endif