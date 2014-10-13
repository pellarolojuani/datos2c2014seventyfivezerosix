/*
 * Pruebas.cpp
 *
 *  Created on: 13/10/2014
 *      Author: juanignacio
 */

#include "parser/ArbolB.h"
#include "parser/Nodo.h"

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>

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


int main(int argc, char *argv[]){
	//aca voy llamando a las diferentes pruebas

	PruebaArbol();

}
