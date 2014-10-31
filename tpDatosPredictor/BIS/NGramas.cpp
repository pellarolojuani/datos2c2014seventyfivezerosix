/*
 * NGramas.cpp
 *
 *  Created on: 30/10/2014
 *      Author: juanignacio
 */

#include "NGramas.h"

NGramas::NGramas() {
	this->lexico = new abb::ArbolB<Registro, 40>;
	this->cantGrama = 0;
	separadorNgrama = " ";
	listaTerminos = vector<string>();
}

NGramas::NGramas(int cantGrama, string separadorNgrama){
	this->lexico = new abb::ArbolB<Registro, 40>;
	this->cantGrama = cantGrama;
	this->separadorNgrama = separadorNgrama;
	this->listaTerminos = vector<string>();
}

NGramas::~NGramas() {
	// TODO Auto-generated destructor stub
}

void NGramas::streamANgrama(FILE* fp){
	fpos_t position;
	FILE* fp_flag;
	fp_flag = fp;
	while (!feof(fp_flag)){
		// cout<<"offset: "<<ftell(fp_flag)<<endl;
		if (ftell(fp_flag)>GIGA) break;
		char* str = new char[100];
		fgetpos(fp, &position);
		string aux = "";
		for(int k = 0; k < cantGrama; k++) {
			if(k > 0) aux += this->separadorNgrama;
			if (feof(fp)) break;
			fscanf(fp, "%s", str);
			aux+= str;
			Registro unRegistro = Registro();
			unRegistro.stringARegistro(aux);

			//agrego al arbol
			if (!this->lexico->buscar(unRegistro)){
				this->lexico->insertar(unRegistro);
			}else{
				this->lexico->aumentarFrecuencia(unRegistro);
			}
	}
}

