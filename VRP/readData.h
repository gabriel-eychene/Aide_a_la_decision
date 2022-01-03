#ifndef READDATA_H_INCLUDED
#define READDATA_H_INCLUDED

#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <list>
#include <cmath>
#include <limits>
#include <cstdio>

using namespace std;

using std::cout;
using std::endl;
using std::ifstream;

struct Data {
	int numberCustomers;	//Number of custumers 
	int vehicleCapacity;	//Vehicle capacity
	int* demand;			//Demands of customers
	double** distance;		//Distance matrix
	string instanceName;	//Instance name
};

void readData(Data* data, string instName);
void getInstanceName(string instName, Data *data);

#endif