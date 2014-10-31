/*
 * NGrama.h
 *
 *  Created on: 11/10/2014
 *      Author: lucas
 */

#ifndef NGRAMAS_H_
#define NGRAMA_H_
#include <string>
#include <vector>
#include <iostream>
#include <map>
#include "../Constantes.h"
#include "../parser/ArbolB.h"
#include "../NGrama/Registro.h"

using namespace std;


class NGramas {

private:
	int cantGrama;
	string separadorNgrama;
	vector<string> listaTerminos;
	abb::ArbolB<Registro,40> *lexico;

	void armarYGuardarNgrama(pair<string,int> par);

public:
	NGramas();
	NGramas(int cantGrama, string separadorNgrama);
	//NGramas(string oracion,int cantGrama,string separadorNgrama);
	virtual ~NGramas();

	void stringANgrama();
	void stringA5Grama();
	void stringANGramaMax(); //solo arma los ngrama de long max indicada.

	void streamANgrama(FILE* fp);
	void aumentarFrecuenciaDeNgrama(int tamanioGrama);
	long getFrecuenciaDeNgrama(int tamanioGrama);

};


#endif /* NGRAMAS_H_ */
