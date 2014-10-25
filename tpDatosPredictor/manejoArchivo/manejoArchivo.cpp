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

ManejoArchivo::ManejoArchivo(string pathEntrada, string modo){
	this->nombreArchivo = pathEntrada;
	fd_archivo = fopen(pathEntrada.c_str(), modo.c_str());
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

	int contexto = 0;
	for (int i = 0; i < aux.size(); i++){
		if (aux[i] == SEPARADOR_NGRAMA){
			contexto++;
		}
	}
	string unContexto = "";
	string termino = "";

	for (int j = 0; j < contexto -1; j++){
		int pos = aux.find_first_of(SEPARADOR_NGRAMA);
		for (int k = 0; k < pos; k++){
			unContexto += aux[k];
		}
		aux = aux.substr(pos+1);
		unContexto += " ";
	}
	unRegistro.setContexto(unContexto);

	int pos = aux.find_first_of(SEPARADOR_NGRAMA);
	for (int k = 0; k < pos; k++){
		termino += aux[k];
	}
	aux = aux.substr(pos+1);
	unRegistro.setTermino(termino);
	unRegistro.setFrecuencia(atoi(aux.c_str()));

	return unRegistro;
}

void merge(int cantArchivos){
	FILE* fp, fp_merged;

	// Creo un archivo destino <merged>
	fp_merged = fopen("file_merged.txt", "w");

	// Abro todos los archivos
	for (int i=0; i<cantArchivos; i++){
		char nombreArchivo[8] = "file";
		char num = (char) (i+1);
		strcat(nombreArchivo, &num);
		strcat(nombreArchivo, ".txt");
		(fp+i) = fopen(nombreArchivo, "r");
	}

	int cant_eof = 0;

	char str[], *str_menor;
	(*str_menor) = "zzzzzzzzzzzzzzzzzzzz";

	while ( cant_eof < cantArchivos ){
		// Leo una linea de todos los arhivos
		for (int i=0; i<cantArchivos; i++){
			if ( !feof(fp+i) ) fgets( (str+i), 256, (fp+i) );

			// ACA DEBERIA TRANSFORMAR LAS LINEAS OBTENIDAS A REGISTRO DE NGRAMAS
			// Y COMPARAR CON STR_MENOR

		}

		// ACA DEBERIA GUARDAR EN FP_MERGED AL MENOR REGISTRO

		// Leo proxima linea en archivo que ya se copio al merged
		for(int i=0; i<cantArchivos; i++){
			if ( *(str+i) == *(str_menor) ){
				if ( !feof(fp+i) ) fgets( (str+i), 256, (fp+i) );
			}
		}

		// Cuento cuantos archivos terminaron
		cant_eof = 0;
		for (int i=0; i<cantArchivos; i++){
			if ( feof(fp+i) ) cant_eof++;
		}
	}
}
