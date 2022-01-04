#include "methode.h"
#include <ilcplex/ilocplex.h>


/**
* CPLEX
*
* This method will perform all the treatment concerning the cplex.
*
* @param data Object that contains the instantiated data.
* @param sol Objetc that will contain the solution.
*/
void cplex(Data* data, Solution* sol) {
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
			if(i != j){
				p += x[i][j];
			}
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
			if(i != j){
				p += x[i][j];
			}
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

	vrp.setParam(IloCplex::Param::TimeLimit, 300);

	double before = vrp.getTime();
	vrp.solve();
	double after = vrp.getTime();



	vector <vector<int>> rotas;
	if (vrp.getStatus() != 0) {

		// for (int i = 0; i < data->numberCustomers+1; i++) {
		// 	for (int j = 0; j < data->numberCustomers+1; j++) {
		// 		printf("x %d %d = %f\n", i, j, vrp.getValue(x[i][j]));
		// 	}
		// }

		//Get solution
		int currentCustomer = 0;
		list<int> customers;
		list<int>::iterator it;

		customers.clear();
		for (int i = 1; i <= data->numberCustomers; i++) {
			customers.push_back(i);
		}
		it = customers.begin();

		vector<int> vec;
		vec.push_back(0);

		while (customers.size() > 0 && it != customers.end()) {
			if (vrp.getValue(x[currentCustomer][*it]) > 0.001) {
				currentCustomer = *it;
				vec.push_back(currentCustomer);
				customers.remove(*it);
				it = customers.begin();
			}
			else {
				++it;
			}
			if (currentCustomer > 0) {
				if (vrp.getValue(x[currentCustomer][0]) > 0.001) {
					vec.push_back(0);
					rotas.push_back(vec);
					vec.clear();
					vec.push_back(0);
					currentCustomer = 0;
					it = customers.begin();
				}
			}
		}
	}
	sol->routes = rotas;

	sol->time = after - before;
	sol->cost = vrp.getBestObjValue();
	int inf = numeric_limits<int>::max();
	sol->UB = inf;
	if (vrp.getStatus() != 0) {
		sol->UB = vrp.getObjValue();
	}
	sol->LB = vrp.getBestObjValue();
	env.end();

}


/**
* CONSTRUCTIVE HEURISTIC METHOD
*
* This method will perform all the treatment concerning our constructive heuristic.
*
* @param data Object that contains the instantiated data.
* @param sol Objetc that will contain the solution.
*/
void construction(Data* data, Solution* sol) {
	printf("dist 01 %f\n", data->distance[0][1]);
	sol->routes = {{0,1,0}};
	Solution tested;
	tested.routes = {{0,1,0}};
	double bestCost;

	for(int customer = 2; customer < data->numberCustomers + 1 ; customer++) {
		tested.routes.push_back({0, customer, 0});
		printRoute(&tested);
		getCost(data, &tested);
		sol->routes = tested.routes;
		sol->cost = tested.cost;
		bestCost = tested.cost;
		tested.routes.pop_back();
		for(vector <vector <int>>::iterator route = tested.routes.begin() ; route !=tested.routes.end() ; route++) {
			if(currentCapacity(data, *route) + data->demand[customer] <= data->vehicleCapacity){
				for(vector <int>::iterator i = (*route).begin() + 1 ; i != (*route).end() ; i++) {
					i = (*route).insert(i, customer);
					printRoute(&tested);
					getCost(data, &tested);
					if(tested.cost < bestCost) {
						sol->routes = tested.routes;
						sol->cost = tested.cost;
						bestCost = tested.cost;
					}
					i = (*route).erase(i);
				}
			}
		}

		tested.routes = sol->routes;
		tested.cost = sol->cost;

	}
}


/**
* ROUTE DISPLAY METHOD
*
* This method will display the route of the solution.
*
* @param sol Object that contains the solution.
*/
void printRoute(Solution *sol) {
	printf("--print--\n");
	for(vector <int> route : sol->routes) {
		for(int cust : route) {
			printf("%d ", cust);
		}
		printf("\n");
	}
	printf("--fin print--\n");
}


/**
* GET COST METHOD
*
* This method will set the cost of the solution passed in parameter.
*
* @param data Object that contains the instantiated data.
* @param sol Object that contains the solution.
*/
void getCost(Data *data, Solution *sol) {
	
	double cost = 0.0;
	for(vector <int> route : sol->routes) {
		int prec = 0;
		for(int customer : route) {
			if(prec != customer){
				cost += data->distance[prec][customer];
				prec = customer;
			}
		}
	}
	printf("get %f\n", cost);
	sol->cost = cost;
}


/**
* CURRENT CAPACITY METHOD
*
* This method returns the capacity currently used by the route indicated in parameter.
*
* @param data Object that contains the instantiated data.
* @param route route for which we want to know the used capacity.
* @return capacity currently used by the route.
*/
int currentCapacity(Data* data, vector<int> route) {
	int capacity = 0;
	for(int customer : route) {
		if(customer != 0) {
			capacity += data->demand[customer];
		}
	}
	return capacity;
}


/**
* PRINT CPLEX SOLUTION IN FILE METHOD
*
* This method will print our CPLEX solution in a file.
*
* @param data Object that contains the instantiated data.
* @param sol Object that contains the solution.
*/
void printSolutionInFileCplex(Data *data, Solution *sol) {
	int inf = numeric_limits<int>::max();

	char tempString[100];
	sprintf(tempString, "Solutions/%s_sol.txt", data->instanceName.c_str());
	ofstream solution(tempString, ios::out);
	
	solution << "Upper Bound: ";
	if (sol->UB > inf - 1000) {
		solution << setw(10) << "--";
	}
	else {
		solution << setw(10) << fixed << setprecision(2) << sol->UB;
	}

	solution << "\nLower Bound: ";
	if (sol->LB > -1) {
		solution << setw(10) << fixed << setprecision(2) << sol->LB;
	}
	else {
		solution << setw(10) << "--";
	}

	solution << "\nRunning time: ";
	solution << setw(10) << sol->time << "\n\n";

	if (sol->UB < inf-1000) {
		solution << "Solution: " << endl;
		for (int r = 0; r < sol->routes.size(); r++) {
			for (int i = 0; i < sol->routes[r].size(); i++) {
				solution << sol->routes[r][i] << setw(7);
			}
			solution << "\n";
		} 
	}
	solution.close();
}


/**
* PRINT HEURISTIC SOLUTION IN FILE METHOD
*
* This method will print our heuristic solution in a file.
*
* @param data Object that contains the instantiated data.
* @param sol Object that contains the solution.
*/
void printSolutionInFileHeur(Data *data, Solution *sol) {
	int inf = numeric_limits<int>::max();

	char tempString[100];
	sprintf(tempString, "Solutions/%s_sol.txt", data->instanceName.c_str());
	ofstream solution(tempString, ios::out);
	
	solution << "Cost: ";
	solution << setw(10) << fixed << setprecision(2) << sol->cost;

	solution << "\nRunning time: ";
	solution << setw(10) << sol->time << "\n\n";

	solution << "Solution: " << endl;
	for (int r = 0; r < sol->routes.size(); r++) {
		for (int i = 0; i < sol->routes[r].size(); i++) {
			solution << sol->routes[r][i] << setw(7);
		}
		solution << "\n";
	}
	solution.close();
}
