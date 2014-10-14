/*
 * NGrama.cpp
 *
 *  Created on: 11/10/2014
 *      Author: lucas
 */

#include "NGrama.h"
#include <iostream>
#include <sstream>
#include <stdio.h>

using namespace std;

NGrama::NGrama() {
	// TODO Auto-generated constructor stub
	this->cantGrama = 1;
}

NGrama::NGrama(int cantGrama, string separadorNgrama){
	this->cantGrama = cantGrama;
	this->separadorNgrama = separadorNgrama;
}

NGrama::NGrama(string oracion, int cantgrama,string separadorNgrama) {
	this->cantGrama = cantgrama;
	this->oracion = oracion;
	this->separadorNgrama = separadorNgrama;
}

NGrama::~NGrama() {

}
void NGrama:: stringANgrama(){

    istringstream iss(this->oracion);
    do
	{
		string sub;
		//split por espacios.
		iss >> sub;
		//porque en la ultima iteracion viene vacio y pincha, tengo que ver bien la condicion de while.
		if(sub.compare("")){
			string ultimoCaracter = sub.substr(sub.length()-1) ;
			//aca deberiamos salvar todos los caracter tipo ,.; etc

			//NOTA: los caracteres .,; etc estan siempre separados de la palabra anterior
			//por un espacio en el set de entrenamiento, es decir que nunca van a venir
			//seguidos de una palabra sino de un espacio.
			if(!ultimoCaracter.compare(".") || !ultimoCaracter.compare(",") || !ultimoCaracter.compare(";")){
				this->listaTerminos.push_back(sub.substr(0,sub.length()-1));
				this->listaTerminos.push_back(sub.substr(sub.length()-1));
			}else{
				this->listaTerminos.push_back(sub);
			}
		}
	}while(iss);
    //arma n-grama
 /*   for(std::size_t i=0;i<this->listaTerminos.size() -cantGrama+1; i++) {
       string aux;
       for(int k = 0; k < cantGrama; k++) {
    	   if (aux.compare("")){

    		   this->listaNgrama.push_back(aux);
    	   }
           if(k > 0) aux +=  " ";
           aux+= (this->listaTerminos[i+k]);
       }
       this->listaNgrama.push_back(aux);
    } */
    for(std::size_t i=0;i<this->listaTerminos.size() -cantGrama+1; i++) {
      	 pair<std::string,int> aux;
         for(int k = 0; k < cantGrama; k++) {
      	   if (aux.first.compare("")){
      		 this->armarYGuardarNgrama(aux);
      	   }
             if(k > 0) aux.first +=  this->separadorNgrama;
             aux.first+= (this->listaTerminos[i+k]);
         }
         this->armarYGuardarNgrama(aux);
      }
}

void NGrama::streamANgrama(FILE* fp){
	fpos_t position;
	fgetpos(fp, &position);
	fsetpos(fp, &position+cantGrama);
	while (! feof(fp) ){
		// Recuperamos la posicion normal dentro del archivo
		fsetpos(fp, &position-cantGrama);

		pair<std::string,int> aux;
		for(int k = 0; k < cantGrama; k++) {
			if (aux.first.compare("")){
				this->armarYGuardarNgrama(aux);
		    }
		    if(k > 0) aux.first +=  this->separadorNgrama;
		    char str [30];
		    aux.first+= ( fscanf(fp, "%s", str) );
		}

		this->armarYGuardarNgrama(aux);

		fsetpos(fp, &position+cantGrama);
	}
}

void NGrama::armarYGuardarNgrama(pair<string,int> aux){
	if(mapDePosiciones.count(aux.first)== 0){
		//no existe en el map entonces lo doy de alta y agrego a la lista
		aux.second = 1;
		this->listaNgrama.push_back(aux);
		mapDePosiciones.insert(std::pair<std::string,int>(aux.first,this->listaNgrama.size()-1));
	}else{
		//esta en el map, entonces saco la pos y sumo frecuencia.
		int pos =  mapDePosiciones.find(aux.first)->second;
		int frecuencia = this->listaNgrama[pos].second;
		frecuencia++;
		this->listaNgrama[pos].second = frecuencia;
	}
}

