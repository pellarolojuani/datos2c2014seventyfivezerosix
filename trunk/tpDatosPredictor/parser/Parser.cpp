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
	delete []this->lexico;
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
	fgets(linea, LONG_MAX_LINEA, this->archivo);


	return linea;
}
long Parser::getPosicionActualArchivo() {
	return ftell(this->archivo);
}

void Parser::setPosicionArchivo(long posicion){
	fseek(this->archivo,posicion,SEEK_SET);
}

