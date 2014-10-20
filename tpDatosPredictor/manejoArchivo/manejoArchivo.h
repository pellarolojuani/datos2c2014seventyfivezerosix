/*
 * manejoArchivo.h
 *
 *  Created on: 13/10/2014
 *      Author: nico
 */

#ifndef MANEJOARCHIVO_H_
#define MANEJOARCHIVO_H_
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>    // std::stable_sort
#include "../NGrama/NGrama.h"
#include "../parser/Nodo.h"
#include "../parser/ArbolB.h"

using namespace std;

class ManejoArchivo {

private:
	FILE* fd_archivo;
	string nombreArchivo;
	long int cantidadBytes;
	bool eof;

	//cada vez q se guarda un registro en el archivo se devuelve el offset
	long int guardarRegistro(pair<string,int> unRegistro, abb::ArbolB<Nodo,40> *lexico);

public:
	ManejoArchivo();
	ManejoArchivo(string pathEntrada);
	virtual ~ManejoArchivo();
	void cerrarArchivo();
	long int contarBytes();
	NGrama darFormato(int tamanioNGrama);
	NGrama leerProxReg();

	void armarArchivoNgramas(vector<pair<string,int> > listaNgrama, abb::ArbolB<Nodo,40> *lexico);


	FILE* getArchivo();

};

#endif /*MANEJOARCHIVO_H_*/
