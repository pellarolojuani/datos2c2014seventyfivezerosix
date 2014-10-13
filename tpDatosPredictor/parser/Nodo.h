#ifndef NODO_H_
#define NODO_H_

#ifndef ORDEN_NODO
#define ORDEN_NODO 40
#endif

#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

/*Aca se define como estará compuesto cada nodo del arbol de temrinos*/

class Nodo {

	private:

	string termino;
	long int offset;

	public:

	Nodo();
	string getTermino();
	long int getOffset();
	void setTermino(string unTermino);
	void setOffset(long int unOffset);

	//con las siguientes operaciones vamos a definir los operadores
	//para comparar nodos
	bool operator==(Nodo&);//compara a igual
	bool operator<(Nodo&);//compara a menor
	bool operator>(Nodo&);//compara a mayor
	bool operator=(Nodo);//asigna
};
#endif /* NODO_H_ */
