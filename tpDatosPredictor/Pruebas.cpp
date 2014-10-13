/*
 * Pruebas.cpp
 *
 *  Created on: 13/10/2014
 *      Author: juanignacio
 */

#include "parser/ArbolB.h"
#include "parser/Nodo.h"
#include "NGrama.h"

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <utility>
#include <algorithm>    // std::stable_sort

using namespace std;

void PruebaArbol() {

	abb::ArbolB<Nodo,40> *lexico = new abb::ArbolB<Nodo, 40>;
	Nodo aux;
	aux.setTermino("prueba");

	if (!lexico->buscar(aux)) cout<<"OK"<<endl;
	lexico->insertar(aux);
	if (lexico->buscar(aux)) cout<<"OK"<<endl;

	cout<<"Fin de pruebas Arbol."<<endl;
}

void pruebaNgrama(){
	string oracion ="This is a very beautiful day. This is a very big house. The elephant is very big. The house is small. The dog is black. The car is very big and red.";

	//oracion.max long ngrama y separador.
	NGrama ngrama5 =  NGrama(oracion, 5,",");
	ngrama5.stringANgrama();



	vector<pair<string,int> > listaNgrama;
	listaNgrama = ngrama5.getListaNgrama();
    std::stable_sort(listaNgrama.begin(), listaNgrama.end());//,compare_first_only());
    std::cout << std::endl << "Sorted:" << std::endl;

	for(std::size_t i=0;ngrama5.getListaNgrama().size();++i){
		cout << listaNgrama[i].first  << "," << listaNgrama[i].second << endl;
		//cout << ngrama5.getListaNgrama()[i] << endl;

	}
}

int main(int argc, char *argv[]){
	//aca voy llamando a las diferentes pruebas

	//PruebaArbol();
	pruebaNgrama();

}
