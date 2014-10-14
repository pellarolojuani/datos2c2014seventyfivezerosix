/*
 * manejoArchivo.cpp
 *
 *  Created on: 13/10/2014
 *      Author: nico
 */

#include "manejoArchivo.h"
#include <string>
#include <fstream>
#include <stdio.h>
#include <iostream>

using namespace std;

ManejoArchivo::ManejoArchivo() {
	fd_archivo = 0;
	nombreArchivo = "";
	this->cantidadBytes = 0;
	eof = false;
}

ManejoArchivo::ManejoArchivo(string pathEntrada) {
	this->nombreArchivo = pathEntrada;
	fd_archivo = fopen(pathEntrada.c_str(), "r");
	if (fd_archivo == 0)
		cout << "No se puede abrir el archivo" << "\n";
	this->cantidadBytes = this->contarBytes();
	eof = false;
}

ManejoArchivo::~ManejoArchivo() {
	// TODO Auto-generated destructor stub

}

void ManejoArchivo::cerrarArchivo() {
	fclose(fd_archivo);
}

long int ManejoArchivo::contarBytes(){
	long int cantidad;
	fseek(this->fd_archivo, 0, ios::end);
	cantidad = ftell(this->fd_archivo);
	this->cantidadBytes = cantidad;
	rewind(fd_archivo);
	return cantidad;
}

NGrama ManejoArchivo::darFormato(int tamanioNGrama){
	/*PRE: El archivo ya tiene que estar abierto*/
	NGrama ngrama(tamanioNGrama, ",");
	ngrama.streamANgrama(this->fd_archivo);
	return ngrama;
}

NGrama ManejoArchivo::leerProxReg(){
	char str [80];
	NGrama ngrama;
	if ( fgets(str, 80, fd_archivo) != 0 ){
		// DARLE FORMATO AL STRING
	}
	else {
		// ERROR DE LECTURA.
	}
	return ngrama;
}
