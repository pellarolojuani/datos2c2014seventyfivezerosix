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
	this->offset = unOffset;
}


//OPERADORES DE COMPARACION
bool Nodo::operator==(Nodo& nuevoNodo)
{
	int sonIguales = (nuevoNodo.getTermino().compare(this->getTermino()) == 0);
	if (sonIguales == 0) return true;
	return false;
}

bool Nodo::operator<(Nodo& nuevoTermino)
{
	int soyMenor = (this->getTermino().compare(nuevoTermino.getTermino()) < 0);
	if (soyMenor < 0) return true;
	return false;
}
bool Nodo::operator>(Nodo& nuevoTermino)
{
	int soyMayor = (this->getTermino().compare(nuevoTermino.getTermino()) > 0);
	if (soyMayor > 0) return true;
	return false;
}


bool Nodo::operator=(Nodo nuevoTermino)
{
	this->termino = nuevoTermino.getTermino();
	this->offset = nuevoTermino.getOffset();

	return true;
}
