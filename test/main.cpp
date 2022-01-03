#include "readData.h"
#include "model.h"

int main(int argc, char** argv) {
	Data data;
	Solution sol;

	readData(&data);
	createLP(&data, &sol);

	/*
	for (int i = 0; i < data.nbObjet; i++) {
		cout << data.poids[i] << " " << data.valeurs[i] << endl;
	}
	*/

	delete[] data.poids;
	delete[] data.valeurs;
}