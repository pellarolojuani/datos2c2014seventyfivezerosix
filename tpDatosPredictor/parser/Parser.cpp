/*
 * Parser.cpp
 *
 *  Created on: 13/10/2014
 *      Author: juanignacio
 */

#include <string>
#include <fstream>
#include <iostream>
#include "ArbolB.h"
#include "../Constantes.h"
#include "Nodo.h"
#include "Parser.h"

using namespace std;

Parser::Parser() {
	this->lexico = new abb::ArbolB<Nodo,40>();
	this->archivo = NULL;
}

Parser::~Parser() {
}

bool Parser::abrirArchivo(string nombreArchivo){

	this->archivo = fopen(nombreArchivo.c_str(), READ);
	if (this->archivo == 0) return false;

	return true;
}

void Parser::cerrarArchivo(){
	fclose(this->archivo);
}

string Parser::getSiguienteTermino(){
	string termino = "";
	char c = fgetc(this->archivo);
	while (c > 32){ //a partir del ascii 33 comienzan los caracteres que necesitamos
		termino += c;
		c = fgetc(this->archivo);
	}
	return termino;
}

string Parser::getLinea(){
	char linea[LONG_MAX_LINEA];
	if (feof(this->archivo)) return "";
	fgets(linea, LONG_MAX_LINEA, this->archivo);

	return linea;
}
long Parser::getPosicionActualArchivo() {
	return ftell(this->archivo);
}

void Parser::setPosicionArchivo(long posicion){
	fseek(this->archivo,posicion,SEEK_SET);
}

long int Parser::setDeEntrenamiento(){
	long int offset;

	NGrama ngrama5 =  NGrama(5," ");

	cout<<"Comienza la lectura del set de entrenamiento.."<<endl;
	ngrama5.streamANgrama(this->archivo);
	cout<<"FIN de la lectura del set de entrenamiento.."<<endl;
	fclose(this->archivo);

	vector<pair<string,int> > listaNgrama;
	listaNgrama = ngrama5.getListaNgrama();
	cout<<"Ordenando lista de NGramas.."<<endl;
	//std::stable_sort(listaNgrama.begin(), listaNgrama.end());

	ManejoArchivo manejoArchivo = ManejoArchivo("1erSet.txt");
	cout<<"Guardando Ngramas en disco.."<<endl;
	manejoArchivo.armarArchivoNgramas(listaNgrama, this->lexico);
	manejoArchivo.cerrarArchivo();

	//cout<<"<termino, offset>"<<endl;
	//lexico->emitir();

	cout<<"FIN."<<endl;

	return offset;
}
