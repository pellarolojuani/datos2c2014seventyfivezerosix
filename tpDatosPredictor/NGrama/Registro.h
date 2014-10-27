/*
 * Registro.h
 *
 *  Created on: 19/10/2014
 *      Author: juanignacio
 */

#ifndef REGISTRO_H_
#define REGISTRO_H_

#include <string.h>
#include <fstream>
#include <sstream>

using namespace std;

class Registro {

	/*
	 * vamos a usar esta clase para almacenar los elementos que vamos a levantar
	 * de disco para calcular las probabilidades
	 * */

private:
	string contexto;
	string termino;
	int frecuencia;
	int longitud;

public:
	Registro();
	virtual ~Registro();

	void setContexto(string unContexto);
	void setTermino(string unTermino);
	void setFrecuencia(int unaFrecuencia);
	string getContexto();
	string getTermino();
	int getFrecuencia();

	int getLongitud();
	void setLongitud(int longitud);

	void stringARegistro(char* str);
	string registroAString();
	void copiarRegistro(Registro unRegistro);
	void aumentarFrecuencia(int numero);
};

#endif /* REGISTRO_H_ */
