/*
 * NGrama.h
 *
 *  Created on: 11/10/2014
 *      Author: lucas
 */

#ifndef NGRAMAS_H_
#define NGRAMAS_H_
#include <string>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <map>
#include <tr1/unordered_map>
#include "../Constantes.h"
#include "../parser/ArbolB.h"
#include "../NGrama/Registro.h"
#include "../manejoArchivo/manejoArchivo.h"

using namespace std;


class NGramas {

private:
	int cantGrama;
	string separadorNgrama;
	vector<string> listaTerminos;
	abb::ArbolB<Registro,60> *lexico;

	//aca guardamos como clave el registroAstring y como valor su frecuencia
	tr1::unordered_map<string, size_t> registros;

	string oracion;

	void armarYGuardarNgrama(pair<string,int> par);

public:

	/*------------------------------------------------------*/
		tr1::unordered_map<string, tr1::unordered_map<string, size_t> > contextos;
	/*------------------------------------------------------*/

	NGramas();
	NGramas(int cantGrama, string separadorNgrama);
	NGramas(int cantGrama, string separadorNgrama,string oracion);
	//NGramas(string oracion,int cantGrama,string separadorNgrama);
	virtual ~NGramas();

	void stringANgrama();
	void stringA5Grama();
	void stringANGramaMax(); //solo arma los ngrama de long max indicada.
	void stringANGramaHashTable(char* buffer);

	void streamANgrama(FILE* fp);
	void aumentarFrecuenciaDeNgrama(int tamanioGrama);
	long getFrecuenciaDeNgrama(int tamanioGrama);

	abb::ArbolB<Registro,60>* getLexico();
	void agregarRegistroEnArbol(Registro unRegistro);
	void levantarNgramas();

	tr1::unordered_map<string, tr1::unordered_map<string, size_t> > getContextos();
	void guardarNgramasAAchivo(char* nombreArchivo); //levanta en memoria x bytes del set y armar ngramas.
	void fusionarArchivosNgramas(string unArchivoNgrama,string otroArchivoNgrama); //abre 2 archivos de ngramas y los fusiona en uno.


	const string& getOracion() const {
		return oracion;
	}

	void setOracion(const string& oracion) {
		this->oracion = oracion;
	}
};


#endif /* NGRAMAS_H_ */
