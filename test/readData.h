#ifndef READDATA_H_INCLUDED
#define READDATA_H_INCLUDED

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

using std::cout;
using std::endl;
using std::ifstream;

struct Data {
	int nbObjet;
	int poidsMax;
	int* poids;
	int* valeurs;
};

void readData(Data* data);

#endif