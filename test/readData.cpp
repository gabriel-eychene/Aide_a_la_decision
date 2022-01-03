#include "readData.h"

void readData(Data* data) {
	ifstream instance("donnees.dat", ios::in);

	if (!instance) {
		cout << "File not found\n";
		exit(1);
	}

	instance >> data->nbObjet;
	instance >> data->poidsMax;

	int* auxPoids = new int[data->nbObjet];
	int* auxValeurs = new int[data->nbObjet];
	for (int i = 0; i < data->nbObjet; i++) {
		instance >> auxPoids[i];
	}
	for (int i = 0; i < data->nbObjet; i++) {
		instance >> auxValeurs[i];
	}

	data->poids = auxPoids;
	data->valeurs = auxValeurs;
}