// =================================================================
//
// File: main.cpp
// Author: DIEGO ITURBE BRAVO
// Date: 23/NOV/2022
//
// =================================================================
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;


void search(string prefix, string linea, vector<string> &coincidencias){
	string busqueda = linea.substr( 17, 3 );
	if (prefix == busqueda){
		coincidencias.push_back(linea); 
	}

}


void swap(vector<string> &coincidencias, int i, int j) {
	string aux = coincidencias[i];
	coincidencias[i] = coincidencias[j];
	coincidencias[j] = aux;
}

void sort( vector<string> &coincidencias){
	int pos;
	for(int i = coincidencias.size() - 1; i > 0; i--){
		pos = 0;
		for(int j = 1; j <= i; j++){
			int anio1,anio2,mes1,mes2,dia1,dia2,hora1,hora2,minuto1,minuto2;
			stringstream y1(coincidencias[j].substr(6,2));
			stringstream y2(coincidencias[pos].substr(6,2));
			y1>> anio1;
			y2>> anio2; 
			stringstream m1(coincidencias[j].substr(3,2));
			stringstream m2(coincidencias[pos].substr(3,2));
			m1>> mes1;
			m2>> mes2;
			stringstream d1(coincidencias[j].substr(0,2));
			stringstream d2(coincidencias[pos].substr(0,2));
			d1>> dia1;
			d2>> dia2;
			stringstream h1(coincidencias[j].substr(9,2));
			stringstream h2(coincidencias[pos].substr(9,2));
			h1>> hora1;
			h2>> hora2;
			stringstream min1(coincidencias[j].substr(12,2));
			stringstream min2(coincidencias[pos].substr(12,2));
			min1>> minuto1;
			min2>> minuto2;

			if (anio2 < anio1)
            pos = j;
        	else if (anio2 == anio1)
        	{
				if (mes2 < mes1)
					pos = j;
				else if (mes2 == mes1)
				{
					if (dia2 < dia1)
						pos = j;
					else if (dia2 == dia1)
					{
						if (hora2 < hora1)
						pos = j;
						else if (hora2 == hora1)
						{
							if (minuto2 < minuto1)
							pos = j;
						}
					}
				}
       		}
			if (pos != i){
				swap(coincidencias, i, pos);
			}
		}
	}
}

int main(int argc, char* argv[]) {
	argc= 805;
	string prefix= "1FR";
	string input = "input.txt";
	ifstream archivo(input.c_str());
	string linea;
	vector<string> coincidencias;
	cout << "comienza lista:" << endl;
	while (getline(archivo,linea)){
		search(prefix, linea, coincidencias);
	}
	sort(coincidencias);
	for (int i = 0; i < coincidencias.size(); i++)
	{
		cout << i << " " << coincidencias[i]<< endl; 
	}
	return 0;
}
