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
	fd_archivo = fopen(pathEntrada.c_str(), "w+");
	if (fd_archivo == 0)
		cout << "No se puede abrir el archivo" << "\n";
	this->cantidadBytes = this->contarBytes();
	eof = false;
}

ManejoArchivo::~ManejoArchivo() {
	// TODO Auto-generated destructor stub

}

FILE* ManejoArchivo::getArchivo(){
	return this->fd_archivo;
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

long int ManejoArchivo::guardarRegistro(pair<string,int> unRegistro, abb::ArbolB<Nodo,40> *lexico){
	/*Ya tiene que estar abierto el archivo para almacenar los registros*/

	long int offset;
	string texto = unRegistro.first;

	int cant = 0;
	for (int i = 0; i < texto.size(); i++){
		if (texto[i] == SEPARADOR_NGRAMA) cant++;
	}
	offset = ftell(this->fd_archivo);
	if (cant == 0){ //si es un termino sin contexto lo guardamos en el arbol de offsets
		Nodo termino ;
		termino.setTermino(unRegistro.first);
		termino.setOffset(offset);
		lexico->insertar(termino); //agrega el elemento y su offset al arbol
	}
	string registro = "";
	stringstream frecuencia;
	frecuencia << unRegistro.second;
	registro += unRegistro.first;
	registro += SEPARADOR_NGRAMA;
	registro += frecuencia.str();
	fputs(registro.c_str(), this->fd_archivo);

	registro = "";
	registro += '\n';
	fputs(registro.c_str(), this->fd_archivo);

	return offset;
}

void ManejoArchivo::armarArchivoNgramas(vector<pair<string,int> > listaNgrama, abb::ArbolB<Nodo,40> *lexico){

	std::stable_sort(listaNgrama.begin(), listaNgrama.end());
	for (int i = 0; i < listaNgrama.size(); i++){
		this->guardarRegistro(listaNgrama.at(i), lexico);
	}
}

Registro ManejoArchivo::getRegistro(long int offset){
	//*devuelve el registro ubicado en la posicion indicada por el offset*/

	fseek(this->fd_archivo, offset, 0);
	return this->getSiguienteRegistro();

}

Registro ManejoArchivo::getSiguienteRegistro(){
	//*sirve para la busqueda secuencial de elementos dentro del archivo*/

	Registro unRegistro = Registro();
	char linea[LONG_MAX_LINEA];
	fgets(linea, LONG_MAX_LINEA, this->fd_archivo);
	string aux = string(linea);
	istringstream iss(aux);
	int contexto = 0;
	for (int i = 0; i < aux.size(); i++){
		if (aux[i] == SEPARADOR_NGRAMA){
			contexto++;
		}
	}
	string unContexto = "";
	string termino;
	for (int j = 0; j < contexto-1; j++ ){
		iss >> termino;
		unContexto += termino;
		unContexto += SEPARADOR_NGRAMA;
	}
	unRegistro.setContexto(unContexto);
	iss >> termino;
	unRegistro.setTermino(termino);
	iss >> termino;
	unRegistro.setFrecuencia(atoi(termino.c_str()));
	return unRegistro;
}
