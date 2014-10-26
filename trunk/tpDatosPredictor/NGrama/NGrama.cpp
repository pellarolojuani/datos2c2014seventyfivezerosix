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
	frecuenciaDeNgramas = new long[cantGrama+1];
	for(int i=0; i<=cantGrama; i++){
		(frecuenciaDeNgramas[i])=0;
	}
}

NGrama::NGrama(string oracion, int cantgrama,string separadorNgrama) {
	this->cantGrama = cantgrama;
	this->oracion = oracion;
	this->separadorNgrama = separadorNgrama;
	frecuenciaDeNgramas = new long[cantGrama+1];
	for(int i=0; i<=cantGrama; i++){
		(frecuenciaDeNgramas[i])=0;
	}
}

NGrama::~NGrama() {
	delete[] frecuenciaDeNgramas;
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
    //for (int i = 0; i < this->listaTerminos.size(); i++) cout<<this->listaTerminos[i]<<endl;
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

    for(std::size_t i=0; i<this->listaTerminos.size() -cantGrama+1; i++) {
      	 pair<std::string,int> aux;
         for(int k = 0; k < cantGrama; k++) {
      	   if (aux.first.compare("")){
      		 this->armarYGuardarNgrama(aux);
      	   }
           if(k > 0) aux.first +=  " ";
           aux.first+= (this->listaTerminos[i+k]);
         }

         this->armarYGuardarNgrama(aux);
      }
}

void NGrama::stringA5Grama(){
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
				//this->listaTerminos.push_back(sub.substr(0,sub.length()-1));
				this->listaTerminos.push_back(sub.substr(sub.length()-1));
			}else{
				this->listaTerminos.push_back(sub);
			}
		}
	}while(iss);

	for (int i = 0; i < this->listaTerminos.size(); i++){
    	cout<<i<<": "<<this->listaTerminos.at(i)<<endl;
    }

    for (int i = 4; i < this->listaTerminos.size(); i++){

    	pair<std::string,int> primero; primero.first = "";
    	pair<std::string,int> segundo; segundo.first = "";
    	pair<std::string,int> tercero; tercero.first = "";
    	pair<std::string,int> cuarto; cuarto.first = "";
    	pair<std::string,int> quinto; quinto.first = "";


    	primero.first += this->listaTerminos.at(i-4);
    	this->armarYGuardarNgrama(primero);

    	segundo.first += this->listaTerminos.at(i-4);
    	segundo.first += this->separadorNgrama;
    	segundo.first += this->listaTerminos.at(i-3);
    	this->armarYGuardarNgrama(segundo);

    	tercero.first += this->listaTerminos.at(i-4);
    	tercero.first += " ";
    	tercero.first += this->listaTerminos.at(i-3);
    	tercero.first += this->separadorNgrama;
    	tercero.first += this->listaTerminos.at(i-2);
    	this->armarYGuardarNgrama(tercero);

    	cuarto.first += this->listaTerminos.at(i-4);
    	cuarto.first += " ";
    	cuarto.first += this->listaTerminos.at(i-3);
    	cuarto.first += " ";
    	cuarto.first += this->listaTerminos.at(i-2);
    	cuarto.first += this->separadorNgrama;
    	cuarto.first += this->listaTerminos.at(i-1);
    	this->armarYGuardarNgrama(cuarto);

    	quinto.first += this->listaTerminos.at(i-4);
    	quinto.first += " ";
    	quinto.first += this->listaTerminos.at(i-3);
    	quinto.first += " ";
    	quinto.first += this->listaTerminos.at(i-2);
    	quinto.first += " ";
    	quinto.first += this->listaTerminos.at(i-1);
    	quinto.first += this->separadorNgrama;
    	quinto.first += this->listaTerminos.at(i);
    	this->armarYGuardarNgrama(quinto);
    }
    pair<std::string,int> ultimo; ultimo.first = "";

    ultimo.first += this->listaTerminos.at(this->listaTerminos.size()-4);
    ultimo.first += " ";
    ultimo.first += this->listaTerminos.at(this->listaTerminos.size()-3);
    ultimo.first += " ";
    ultimo.first += this->listaTerminos.at(this->listaTerminos.size()-2);
    ultimo.first += this->separadorNgrama;
    ultimo.first += this->listaTerminos.at(this->listaTerminos.size()-1);
    this->armarYGuardarNgrama(ultimo);

    ultimo.first = "";
    ultimo.first += this->listaTerminos.at(this->listaTerminos.size()-3);
    ultimo.first += " ";
    ultimo.first += this->listaTerminos.at(this->listaTerminos.size()-2);
    ultimo.first += this->separadorNgrama;
    ultimo.first += this->listaTerminos.at(this->listaTerminos.size()-1);
    this->armarYGuardarNgrama(ultimo);

    ultimo.first = "";
    ultimo.first += this->listaTerminos.at(this->listaTerminos.size()-2);
    ultimo.first += this->separadorNgrama;
    ultimo.first += this->listaTerminos.at(this->listaTerminos.size()-1);
    this->armarYGuardarNgrama(ultimo);

    ultimo.first = "";
    ultimo.first += this->listaTerminos.at(this->listaTerminos.size()-1);
    this->armarYGuardarNgrama(ultimo);

}

void NGrama::streamANgrama(FILE* fp){
	fpos_t position;
	FILE* fp_flag;
	fp_flag = fp;
	while (!feof(fp_flag)){
		char* str = new char[100];
		fgetpos(fp, &position);
		pair<std::string,int> aux;
		aux.first = "";
		aux.second = -1;
		for(int k = 0; k < cantGrama; k++) {
			/* ESTO NO DEBERIA ESTAR. NICO
			if (aux.first == ""){
				this->armarYGuardarNgrama(aux);
		    }
			*/
		    if(k > 0) aux.first +=  this->separadorNgrama;
		    if (feof(fp)) break;
		    fscanf(fp, "%s", str);
		    aux.first+= str;
		    this->armarYGuardarNgrama(aux);
		    this->aumentarFrecuenciaDeNgrama(k+1); //Esto va calculando la frecuencia de Gramas de tamanio k+1
		}
		fp_flag = fp;
		fsetpos(fp, &position);
		fscanf(fp, "%s", str);
		delete []str;
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



void NGrama::aumentarFrecuenciaDeNgrama(int tamanioGrama){
	(frecuenciaDeNgramas[tamanioGrama])+=1;
}

long NGrama::getFrecuenciaDeNgrama(int tamanioGrama){
	return (frecuenciaDeNgramas[tamanioGrama]);
}

void NGrama:: stringANGramaMax(){

    istringstream iss(this->oracion);
    do
	{
		string sub;
		//split por espacios.
		iss >> sub;
		//porque en la ultima iteracion viene vacio y pincha, tengo que ver bien la condicion de while.
		if(sub.compare("")){
			string ultimoCaracter = sub.substr(sub.length()-1) ;
			if(!ultimoCaracter.compare(".") || !ultimoCaracter.compare(",") || !ultimoCaracter.compare(";")){
				//this->listaTerminos.push_back(sub.substr(0,sub.length()-1));
				this->listaTerminos.push_back(sub.substr(sub.length()-1));
			}else{
				//para no guardar los espacios.
				this->listaTerminos.push_back(sub);
			}
		}
	}while(iss);

    for(std::size_t i=0; i<this->listaTerminos.size() -cantGrama+1; i++) {
      	 pair<std::string,int> aux;
         for(int k = 0; k < cantGrama; k++) {
      	   if (aux.first.compare(" ") && k == cantGrama ){
      		 this->armarYGuardarNgrama(aux);
      	   }
           if(k > 0 && k != cantGrama -1 ){
        	   aux.first +=  " ";
           }
           if(k > 0 && k == cantGrama - 1){
        	   aux.first +=  ",";
           }
           aux.first+= (this->listaTerminos[i+k]);
         }

         this->armarYGuardarNgrama(aux);
      }
}




