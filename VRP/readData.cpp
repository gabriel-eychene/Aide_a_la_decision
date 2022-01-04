#include "readData.h"

/**
* Read the instance file
*
* This function will read the instance file, and will instantiate the data.
*
* @param data Object that will contain the instantiated data.
* @param instName Name of the instance.
*/
void readData(Data* data, string instName) {

	//Open instance file
	ifstream instance(instName, ios::in);

	if (!instance) {
		cout << "File not found\n";
		exit(1);
	}

	//Get instance name
	getInstanceName(instName, data);

	int inf = numeric_limits<int>::max();

	instance >> data->numberCustomers;	//Get number of customers
	instance >> data->vehicleCapacity;	//Get vehicle capacity

	//Assign memory for data
	int* auxDemand = new int[data->numberCustomers + 1];
	int* x = new int[data->numberCustomers + 1];
	int* y = new int[data->numberCustomers + 1];
	double** auxDistance = new double* [data->numberCustomers + 1];
	for (int i = 0; i <= data->numberCustomers; i++) {
		auxDistance[i] = new double[data->numberCustomers + 1];
		for (int j = 0; j <= data->numberCustomers; j++) {
			auxDistance[i][j] = inf;
		}
	}

	//Get depot data
	instance >> x[0];
	instance >> y[0];
	auxDemand[0] = 0;

	//Get customers data
	for (int i = 1; i <= data->numberCustomers; i++) {
		instance >> x[i];
		instance >> y[i];
		instance >> auxDemand[i];
	}
	data->demand = auxDemand;

	//Calculate Euclidean distance
	for (int i = 0; i <= data->numberCustomers; i++) {
		for (int j = 0; j <= data->numberCustomers; j++) {
			if (i != j) {
				auxDistance[i][j] = (double)(sqrt(pow(x[i] - x[j], 2) + pow(y[i] - y[j], 2)));
				auxDistance[j][i] = auxDistance[i][j];
			}
		}
	}
	data->distance = auxDistance;

	//Close instance file
	instance.close();

	//Print data
	/*
	cout << data->vehicleCapacity << endl;
	cout << data->numberCustomers << endl;
	for (int i = 1; i <= data->numberCustomers; i++) {
		cout << data->demand[i] << "\t";
	} cout << endl;

	for (int i = 0; i <= data->numberCustomers; i++) {
		for (int j = 0; j <= data->numberCustomers; j++) {
			if (i != j) {
				cout << data->distance[i][j] << "\t";
			}
		} cout << endl;
	} cout << endl;
	*/
}


/**
* Get the instance name
*
* This function will read the instance name, and set it in our data object.
*
* @param instancia Name of the instance
* @param data Object that contains the instantiated data.
*/
void getInstanceName(string instancia, Data* data)
{
	int length = instancia.size();
	int cont = 0;

	for (int i = length - 5; i >= 0; i--) {
		if (instancia[i] == '/') {
			break;
		}
		cont++;
	}

	for (int i = 0; i < cont; i++) {
		data->instanceName.push_back(instancia[length - 4 - cont + i]);
	}
}