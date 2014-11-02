/*
 * Registro.cpp
 *
 *  Created on: 19/10/2014
 *      Author: juanignacio
 */

#include "Registro.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

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
void Registro::agregarContexto(string masContexto){
	this->contexto += masContexto;
}

void Registro::setTermino(string unTermino){
	this->termino = unTermino;
}
void Registro::setFrecuencia(int unaFrecuencia){
	this->frecuencia = unaFrecuencia;
}
void Registro::setLongitud(int unaLongitud){
	this->longitud = unaLongitud;
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

int Registro::getLongitud(){
	return this->longitud;
}

void Registro::lineaNGramaARegistro(string str){

		int contexto = 0;
		for (int i = 0; i < str.size(); i++){
			if (str[i] == SEPARADOR_NGRAMA){
				contexto++;
			}
		}
		string unContexto = "";
		string termino = "";

		for (int j = 0; j < contexto -1; j++){
			int pos = str.find_first_of(SEPARADOR_NGRAMA);
			for (int k = 0; k < pos; k++){
				unContexto += str[k];
			}
			str = str.substr(pos+1);
			if (j < contexto-2 ) unContexto += " ";
		}
		this->setContexto(unContexto);

		int pos = str.find_first_of(SEPARADOR_NGRAMA);
		for (int k = 0; k < pos; k++){
			termino += str[k];
		}
		str = str.substr(pos+1);
		this->setTermino(termino);
		this->setFrecuencia(atoi(str.c_str()));

}

void Registro::stringARegistro(string unTexto){

	int contexto = 0;
	for (int i = 0; i < unTexto.size(); i++){
		if (unTexto[i] == SEPARADOR_NGRAMA){
			contexto++;
		}
	}
	string unContexto = "";
	string termino = "";

	for (int j = 0; j < contexto; j++){
		int pos = unTexto.find_first_of(SEPARADOR_NGRAMA);
		for (int k = 0; k < pos; k++){
			unContexto += unTexto[k];
		}
		unTexto = unTexto.substr(pos+1);
		unContexto += " "; //OJO: Al final del contexto queda un espacio!!
	}
	this->setContexto(unContexto);

	for (int k = 0; k < unTexto.size(); k++){
		termino += unTexto[k];
	}
	this->setTermino(termino);
	this->setFrecuencia(1);

}
string Registro::registroAString(){
	string resultado = "";

	resultado += (this->contexto);
	resultado += " ";
	resultado += (this->termino);
	resultado += " ";

	ostringstream num;
	num << (this->frecuencia);
	string frec = num.str();
	resultado += frec;

	return resultado;
}

void Registro::copiarRegistro(Registro unRegistro){
	this->contexto = unRegistro.getContexto();
	this->frecuencia = unRegistro.getFrecuencia();
	this->termino = unRegistro.getTermino();
	this->longitud = unRegistro.getLongitud();
}

void Registro::aumentarFrecuencia(int numero){
	this->frecuencia = this->frecuencia+numero;
}

//OPERADORES DE COMPARACION. TERMINAR DE DEFINIR CRITERIO!!!
bool Registro::operator==(Registro& nuevoRegistro)
{
	string unTermino = "";
	string otroTermino = "";
	unTermino += this->getTermino();
	unTermino += " ";
	unTermino += this->getContexto();
	otroTermino += nuevoRegistro.getTermino();
	otroTermino += " ";
	otroTermino += nuevoRegistro.getContexto();
	bool igualTermino = (unTermino == otroTermino);
	if (igualTermino) return true;
	return false;
}

bool Registro::operator<(Registro& nuevoRegistro)
{
	string unTermino = "";
	string otroTermino = "";
	unTermino += this->getTermino();
	unTermino += " ";
	unTermino += this->getContexto();
	otroTermino += nuevoRegistro.getTermino();
	otroTermino += " ";
	otroTermino += nuevoRegistro.getContexto();
	if (unTermino < otroTermino) return true;
	return false;
}
bool Registro::operator>(Registro& nuevoRegistro)
{
	string unTermino = "";
	string otroTermino = "";
	unTermino += this->getTermino();
	unTermino += " ";
	unTermino += this->getContexto();
	otroTermino += nuevoRegistro.getTermino();
	otroTermino += " ";
	otroTermino += nuevoRegistro.getContexto();
	if (unTermino > otroTermino) return true;
	return false;
}


bool Registro::operator=(Registro nuevoRegistro)
{
	this->contexto = nuevoRegistro.getContexto();
	this->termino = nuevoRegistro.getTermino();
	this->frecuencia = nuevoRegistro.getFrecuencia();

	return true;
}
