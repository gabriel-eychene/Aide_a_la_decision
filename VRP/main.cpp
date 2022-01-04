#include "readData.h"
#include "methode.h"
#include <iostream>
#include <string>

using namespace std;


/**
* Main of our program
*
* @return integer which indicates if everything went well or not.
*/
int main() {
	//Get start time
	clock_t before = clock();

	Data data;
	Solution sol;

	//Name of instance file
	string instName = "Instances/vrpnc11.txt";
	
	//Read instance file
	readData(&data, instName);
	cout << "Instance: " << data.instanceName << endl;
	
	// CPLEX EXECUTION
	// cplex(&data, &sol);


	// HEURISTIC EXECUTION
	// Get initial solution
	construction(&data, &sol);

	// Improve initial solution
	// amelioration(&data, &sol, before);

	// Get end time
	sol.time = (double) (clock() - before)/CLOCKS_PER_SEC;
	
	// Print solution in file
	printSolutionInFileHeur(&data, &sol);

	delete[] data.demand;
	for (int i = 0; i <= data.numberCustomers; i++) {
		delete[] data.distance[i];
	}
	delete[] data.distance;
	return 0;
}