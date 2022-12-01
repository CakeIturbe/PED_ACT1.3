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

void openFile(ifstream& inFile,string fname){
	inFile.open(fname);
	if (inFile.is_open()){
		// cout << "Successfully opened file"<<endl;
	}
	else{
		cout << "Failed to open file" << endl;
		exit(-1);
	}
}

vector<string> processFile(ifstream& inFile,int i, int limit){
	//read line by line
	vector<string> content;
	string line;
	int cont=0;
	
	while (!inFile.eof() && i < limit){
		i++;
		getline(inFile,line);
		// bool found = line.find('.');
		//found == 1 == No se encontro punto
		if(inFile.good()){
			content.push_back(line);
			
		}
		cont++;

	} 
	return content;
}

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
	ifstream inFile;
	openFile(inFile,"input2.txt");
	//obtener linea 1
	vector<string> linea1 = processFile(inFile,0,1);
	string linea, linea2;
	char delimiter= ' ';
	vector<string> linea1separada;
	for (int i = 0; i < linea1.size(); i++){
		stringstream x(linea1[i]);
		while (getline(x, linea, delimiter)) {
        linea1separada.push_back(linea);
		}
	}
	stringstream nP(linea1separada[0]);
	string prefix = linea1separada[1];
	nP >> argc;
	// obtener lineas registros
	vector<string> r1 = processFile(inFile,1,argc+1);
	vector<string> coincidencias;
	for (int i = 0; i < r1.size() ; i++){
		stringstream y(r1[i]);
		while (getline(y,linea2)){
			search(prefix, linea2, coincidencias);
		}
	}

	// BUSCAR COINCIDENCIAS
	sort(coincidencias);
	for (int i = 0; i < coincidencias.size(); i++)
	{
		cout << coincidencias[i]<< endl; 
	}
	return 0;
}
