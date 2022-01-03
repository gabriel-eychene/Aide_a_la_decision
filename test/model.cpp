#include "model.h"
#include <ilcplex/ilocplex.h>


void createLP(Data* data, Solution* sol) {
	IloEnv env;

	// CREATE MODEL
	IloModel model(env);

	// CREATE VARIABLES
	// Create x_i for items
	IloBoolVarArray x(env, data->nbObjet+1);

	// Add x_i
	char var[100];
	for (int i = 1; i <= data->nbObjet; i++) {
		sprintf(var, "x(%d)", i);
		x[i].setName(var);
		model.add(x[i]);
	}

	// CREATE OBJECTIVE FUNCTION
	IloExpr prix(env);

	for (int i = 1; i <= data->nbObjet; i++) {
		prix += data->valeurs[i]*x[i];
	}

	// Add objective function
	model.add(IloMaximize(env, prix));
	
	// Capacity constraint
	IloExpr p(env);
	for (int i = 1; i <= data->nbObjet; i++) {
		p += data->poids[i] * x[i];
	}
	IloRange r = (p <= data->poidsMax);
	char c[100];
	sprintf(c, "const");
	r.setName(c);
	model.add(r);

	// WRITE LP
	IloCplex Knapsack(model);
	Knapsack.exportModel("model.lp");
	//Knapsack.setParam(IloCplex::MIPDisplay,4);
	//ofstream logfile("model.log");
	//Knapsack.setOut(logfile);
	////Batch.setParam(IloCplex::Threads,1);
	//Batch.setParam(IloCplex::TiLim, 3600);
	//Batch.setParam(IloCplex::TreLim, 10000);

	//--------------------------------------------------------------------
		// Get root cost
	//	MyBranchCallback * branchCbk = new MyBranchCallback(env);
	//	Batch.use(branchCbk);
	//	Batch.setParam(IloCplex::NodeLim, 3);
	//--------------------------------------------------------------------
	double before = Knapsack.getTime();
	Knapsack.solve();
	double after = Knapsack.getTime();

	int inf = numeric_limits<int>::max();
	sol->UB = inf;
	sol->LB = -1;
	sol->openNodes = 0;

	if (Knapsack.getStatus() != 0) {
		sol->UB = Knapsack.getObjValue();
	}
	sol->LB = Knapsack.getBestObjValue();
	sol->time = after - before;
	sol->openNodes = Knapsack.getNnodes();

	if (Knapsack.getObjValue() - Knapsack.getBestObjValue() < 0.01) {
		cout << "Optimal solution found!" << endl;
		cout << "Cost: " << sol->UB << "\n" << endl;
	}

	if (Knapsack.getStatus() != 0) {
		cout << "Solution: " << endl;
		for (int i = 1; i <= data->nbObjet; i++) {
			if (Knapsack.getValue(x[i]) > 0.999) {
				cout << "x(" << i << ") = 1" << endl;
			}
		}
	}

	env.end();
}