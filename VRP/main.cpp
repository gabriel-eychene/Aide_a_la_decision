#include "readData.h"
#include "functions.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
	//Get start time
	clock_t before = clock();

	Data data;
	Solution sol;
	string instName = "Instances/vrpSmall.txt";
	
	//Read instance file
	readData(&data, instName);
	cout << "Instance: " << data.instanceName << endl;
	


	//Get initial solution
	construction(&data, &sol);

	// //Improve initial solution
	// //...

	// //Get end time
	// sol.time = (double) (clock() - before)/CLOCKS_PER_SEC;
	
	// //Print solution in file
	// printSolutionInFile(&data, &sol);

	delete[] data.demand;
	for (int i = 0; i <= data.numberCustomers; i++) {
		delete[] data.distance[i];
	}
	delete[] data.distance;

	return 0;
}