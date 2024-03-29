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
#include "../Constantes.h"

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
	void agregarContexto(string masContexto); //contexto +=
	void setFrecuencia(int unaFrecuencia);
	string getContexto();
	string getTermino();
	int getFrecuencia();

	int getLongitud();
	void setLongitud(int longitud);

	void lineaNGramaARegistro(string str);
	void stringARegistro(string str);
	string registroAString();
	string registroAStringSinFrecuencia();
	void copiarRegistro(Registro unRegistro);
	void aumentarFrecuencia(int numero);

	size_t guardarRegistroEnDisco(FILE* fp);

	//con las siguientes operaciones vamos a definir los operadores
	//para comparar registros
	bool operator==(Registro&);//compara a igual
	bool operator<(Registro&);//compara a menor
	bool operator>(Registro&);//compara a mayor
	bool operator=(Registro);//asigna
};

#endif /* REGISTRO_H_ */
