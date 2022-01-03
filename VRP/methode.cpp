#include "methode.h"
#include <ilcplex/ilocplex.h>

void construction(Data* data, Solution* sol) {
	IloEnv env;

	// CREATE MODEL
	IloModel model(env);

	// CREATE VARIABLES
	// Create x_{ij} 
	IloArray <IloBoolVarArray> x(env, data->numberCustomers+1);
	for (int i = 0; i < data->numberCustomers+1; i++) {
		IloBoolVarArray array(env, data->numberCustomers+1);
		x[i] = array;
	}

	// Add x_i
	char varName[100];
	for (int i = 0; i < data->numberCustomers+1; i++) {
		for (int j = 0; j < data->numberCustomers+1; j++) {
			sprintf(varName, "x(%d,%d)", i, j);
			x[i][j].setName(varName);
			model.add(x[i][j]);
		}
	}

	// Create a_i
	IloIntVarArray a(env, data->numberCustomers+1, 0, data->vehicleCapacity);
	// Add a_i
	for(int i = 0 ; i < data->numberCustomers + 1 ; i++) {
		sprintf(varName, "a(%d)", i);
		a[i].setName(varName);
		model.add(a[i]);
	}
	// CREATE OBJECTIVE FUNCTION
	IloExpr objfonc(env);

	for (int i = 0; i < data->numberCustomers+1; i++) {
		for (int j = 0; j < data->numberCustomers+1; j++) {
			if(i != j) {
				objfonc += data->distance[i][j] * x[i][j];
			}
		}
	}

	model.add(IloMinimize(env, objfonc));
	// CONSTRAINTS
	// Constraints 1
	IloRangeArray c1(env);
	for (int j = 1; j < data->numberCustomers+1; j++) {
		IloExpr p(env);
		for (int i = 0; i < data->numberCustomers+1; i++) {
			p += x[i][j];
		}
		c1.add( p == 1 );
		sprintf(varName, "c1(%d)", j);
		c1[j-1].setName(varName);
	}
	model.add(c1);
	// Constraints 2
	IloRangeArray c2(env);
	for (int i = 1; i < data->numberCustomers+1; i++) {
		IloExpr p(env);
		for (int j = 0; j < data->numberCustomers+1; j++) {
			p += x[i][j];
		}
		c2.add( p == 1 );
		sprintf(varName, "c2(%d)", i);
		c2[i-1].setName(varName);
	}
	model.add(c2);

	// Constraints 3
	// i goes from 1 to n but in c3 it goes from 0 to n-1
	IloArray <IloConstraintArray> c3(env, data->numberCustomers);
	for(int i = 1 ; i < data->numberCustomers + 1 ; i++) {
		IloConstraintArray array(env);
		
		for(int j = 0 ; j < data->numberCustomers + 1 ; j++ ) {
			if(i != j) {
				array.add(a[j] - a[i] + data->demand[i] <= data->vehicleCapacity * ( 1 - x[i][j]) );
			}
		}
		sprintf(varName, "c3(%d)", i);
		array.setNames(varName);
		c3[i-1] = array;
		model.add(c3[i-1]);
	}
	// Constraints 4
	IloRangeArray c4(env);
	for(int i = 1 ; i < data->numberCustomers + 1 ; i++ ) {
		c4.add( data->demand[i] <= a[i] <= data->vehicleCapacity);
		sprintf(varName, "c4(%d)", i);
		c4[i-1].setName(varName);
	}
	model.add(c4);

	IloCplex vrp(model);
	vrp.exportModel("modelVRP.lp");

	double before = vrp.getTime();
	vrp.solve();
	double after = vrp.getTime();



	// vector <vector<int>> rotas;
	// if (vrp.getStatus() != 0) {

	// 	// Get solution
	// 	int a = 0;
	// 	list<int> customers;
	// 	list<int>::iterator it;

	// 	customers.clear();
	// 	for (int i = 1; i <= data->numberCustomers; i++) {
	// 		customers.push_back(i);
	// 	}
	// 	it = customers.begin();

	// 	vector<int> vec;
	// 	vec.push_back(0);

	// 	while (customers.size() > 0) {
	// 		if (vrp.getValue(x[a][*it]) > 0.001) {
	// 			a = *it;
	// 			vec.push_back(a);
	// 			customers.remove(*it);
	// 			it = customers.begin();
	// 		}
	// 		else {
	// 			++it;
	// 		}
	// 		if (a > 0) {
	// 			if (vrp.getValue(x[a][0]) > 0.001) {
	// 				vec.push_back(0);
	// 				rotas.push_back(vec);
	// 				vec.clear();
	// 				vec.push_back(0);
	// 				a = 0;
	// 				it = customers.begin();
	// 			}
	// 		}
	// 	}
	// }
	// sol->routes = rotas;

	env.end();

}

void printSolutionInFile(Data *data, Solution *sol) {

	char tempString[100];
	sprintf(tempString, "Solutions/%s_sol.txt", data->instanceName.c_str());
	ofstream solution(tempString, ios::out);
	
	solution << "Cost: " << setw(10) << fixed << setprecision(2) << sol->cost;
	//...

	solution.close();
}
