/*
 * Parser.h
 *
 *  Created on: 13/10/2014
 *      Author: juanignacio
 */

#ifndef PARSER_H_
#define PARSER_H_

#include <string>
#include <fstream>
#include <iostream>
#include "ArbolB.h"
#include "../Constantes.h"
#include "Nodo.h"

class Parser {

private:
	abb::ArbolB<Nodo,40> *lexico;
	FILE* archivo;

public:
	Parser();
	virtual ~Parser();

	bool abrirArchivo(string nombreArchivo);
	string getSiguienteTermino();

};
