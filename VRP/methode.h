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

void cplex(Data* data, Solution* sol);
void construction(Data* data, Solution* sol);
void amelioration(Data* data, Solution* sol, clock_t before);
void getCost(Data *data, Solution *sol);
int currentCapacity(Data* data, vector<int> route);
void printSolutionInFileCplex(Data* data, Solution* sol);
void printSolutionInFileHeur(Data* data, Solution* sol);


#endif