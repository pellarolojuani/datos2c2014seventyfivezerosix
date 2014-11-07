/*
 * NGramas.cpp
 *
 *  Created on: 30/10/2014
 *      Author: juanignacio
 */

#include "NGramas.h"

NGramas::NGramas() {
	this->lexico = new abb::ArbolB<Registro, 60>;
	this->cantGrama = 0;
	separadorNgrama = " ";
	listaTerminos = vector<string>();
}

NGramas::NGramas(int cantGrama, string separadorNgrama){
	this->lexico = new abb::ArbolB<Registro, 60>;
	this->cantGrama = cantGrama;
	this->separadorNgrama = separadorNgrama;
	this->listaTerminos = vector<string>();
}

NGramas::~NGramas() {
	// TODO Auto-generated destructor stub
}

abb::ArbolB<Registro,60>* NGramas::getLexico(){
	return this->lexico;
}

//--------------------------------------------------------//
//---------Comienzo de funciones auxiliares --------------//
string getSiguienteTermino(FILE* fp){
	string termino = "";
	char c = fgetc(fp);
	if (c == EOF) return "";
	if (c == ' ') c = fgetc(fp);
	while (c > 32 && c != ' '){ //a partir del ascii 33 comienzan los caracteres que necesitamos
		termino += c;
		c = fgetc(fp);
	}
	if (termino == " ") return "";
	return termino;
}

string sacarPrimerTermino(string texto){
	//saca la primera palabra de una frase y devuelve la frase nueva
	int espacio = texto.find_first_of(" ");
	string nuevoTexto = texto.substr(espacio+1);
	return nuevoTexto;
}

void NGramas::agregarRegistroEnArbol(Registro unRegistro){
	if (!this->lexico->buscar(unRegistro)){
		this->lexico->insertar(unRegistro);
	}else{
		this->lexico->aumentarFrecuencia(unRegistro);
	}
}
//--------------------------------------------------------//
//--------------Fin de funciones auxiliares --------------//

void NGramas::streamANgrama(FILE* fp){

	char *c = new char[2884354560];	//reservamos mas de 2.5gb de memoria!
	fpos_t position;
	FILE* fp_flag;
	size_t offset = 0;
	delete[] c;	//libero la memoria reservada

	while (!feof(fp) && offset < GIGA){ //Faltaria corregir la creacion de ngramas pero no es tan urgente..

		offset = ftell(fp);
		cout<<offset<<endl;
		string ngrama = "";

		ngrama += getSiguienteTermino(fp);
		if (ngrama == "") break;
		size_t nuevoOffset = ftell(fp);
		Registro unRegistro = Registro();
		unRegistro.stringARegistro(ngrama);
		if (unRegistro.getTermino() != "" && unRegistro.getTermino() != " ")
			this->agregarRegistroEnArbol(unRegistro);
		for (int k = 0; k < cantGrama-1; k++){
			ngrama += " ";
			ngrama += getSiguienteTermino(fp);
			unRegistro.stringARegistro(ngrama);
			this->agregarRegistroEnArbol(unRegistro);

		}
		fseek(fp, nuevoOffset, SEEK_SET);

	}

}
