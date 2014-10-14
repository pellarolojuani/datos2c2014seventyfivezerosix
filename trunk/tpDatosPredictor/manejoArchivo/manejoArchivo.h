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
#include "../NGrama/NGrama.h"

using namespace std;




class ManejoArchivo {

private:
	FILE* fd_archivo;
	string nombreArchivo;
	long int cantidadBytes;
	bool eof;

public:
	ManejoArchivo();
	ManejoArchivo(string pathEntrada);
	virtual ~ManejoArchivo();
	void cerrarArchivo();
	long int contarBytes();
	NGrama darFormato(int tamanioNGrama);
	NGrama leerProxReg();

};
















#endif /*MANEJOARCHIVO_H_*/
