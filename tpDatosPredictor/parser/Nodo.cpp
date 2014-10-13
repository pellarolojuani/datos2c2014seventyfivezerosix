/*
 * Nodo.cpp
 *
 *  Created on: 10/10/2014
 *      Author: juanignacio
 */

#include "Nodo.h"

using namespace std;

Nodo::Nodo(){
	this->termino = "";
	this->offset = -1;
}

string Nodo::getTermino(){
	return this->termino;
}

long int Nodo::getOffset(){
	return this->offset;
}

void Nodo::setTermino(string unTermino){
	this->termino = unTermino;
}

void Nodo::setOffset(long int unOffset){
	this->offset = offset;
}


//OPERADORES DE COMPARACION
bool Nodo::operator==(Nodo& nuevoNodo)
{
	bool sonIguales = (nuevoNodo.getTermino() == this->getTermino());
	return sonIguales;
}

bool Nodo::operator<(Nodo& nuevoTermino)
{
	bool soyMenor = (this->getTermino() < nuevoTermino.getTermino());
	return soyMenor;
}
bool Nodo::operator>(Nodo& nuevoTermino)
{
	bool soyMayor = (this->getTermino() > nuevoTermino.getTermino());
	return soyMayor;
}


bool Nodo::operator=(Nodo nuevoTermino)
{
	this->termino = nuevoTermino.getTermino();
	this->offset = nuevoTermino.getOffset();

	return true;
}
