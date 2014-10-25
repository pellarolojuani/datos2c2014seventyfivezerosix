/*
 * Registro.cpp
 *
 *  Created on: 19/10/2014
 *      Author: juanignacio
 */

#include "Registro.h"

Registro::Registro() {
	this->contexto = "";
	this->termino = "";
	this->frecuencia = 0;
	this->longitud = 0;
}

Registro::~Registro() {
	// TODO Auto-generated destructor stub
}

void Registro::setContexto(string unContexto){
	this->contexto = unContexto;
}
void Registro::setTermino(string unTermino){
	this->termino = unTermino;
}
void Registro::setFrecuencia(int unaFrecuencia){
	this->frecuencia = unaFrecuencia;
}
string Registro::getContexto(){
	return this->contexto;
}
string Registro::getTermino(){
	return this->termino;
}
int Registro::getFrecuencia(){
	return this->frecuencia;
}

void Registro::stringARegistro(char* str){
	char* token;
	char* separador = " ";

	token = strtok(str, separador);

	int i = 0;
	while (token != NULL){
		i++;
		(token+i) = strtok(str, separador);
	}
	// str tenia i+1 de palabras separadas

	string contexto = "";
	for (int j=0; j<i; j++){
		contexto = contexto.append( (token+j) );
	}

	string termino = "";
	termino = termino.append( (token+i) );

	int frecuencia;
	frecuencia = *(token+i+1);

	this->setContexto(contexto);
	this->setTermino(termino);
	this->setFrecuencia(frecuencia);
}

string Registro::registroAString(){
	string resultado = "";

	resultado = resultado.append(this->contexto);
	resultado = resultado.append(" ");
	resultado = resultado.append(this->termino);
	resultado = resultado.append(" ");

	stringstream ss2;
	ss2 << frecuencia;
	string frec = ss2.str();
	resultado = resultado.append(frec);

	return resultado;
}