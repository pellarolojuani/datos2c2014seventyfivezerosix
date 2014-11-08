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
#include <algorithm>
#include <fstream>

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
		// cout<<"offset: "<<ftell(fp_flag)<<endl;
		if (ftell(fp_flag)>GIGA) break;
		char* str = new char[100];
		fgetpos(fp, &position);
		pair<std::string,int> aux;
		aux.first = "";
		aux.second = -1;
		for(int k = 0; k < cantGrama; k++) {
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

void NGrama::armarYGuardarNgramaSoloEnMap(pair<string,int> aux){
	if(mapDePosiciones.count(aux.first)== 0){
		//no existe en el map entonces lo doy de alta con frecuencia 1.
		mapDePosiciones.insert(std::pair<std::string,int>(aux.first,1));
	}else{
		//esta en el map, entonces saco la pos y sumo frecuencia.
		int frecuencia =  mapDePosiciones.find(aux.first)->second;
		frecuencia++;
		mapDePosiciones.find(aux.first)->second = frecuencia;
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

void NGrama::stringANGramaAlmacenadoEnMap(){
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
    	this->armarYGuardarNgramaSoloEnMap(primero);

    	segundo.first += this->listaTerminos.at(i-4);
    	segundo.first += this->separadorNgrama;
    	segundo.first += this->listaTerminos.at(i-3);
    	this->armarYGuardarNgramaSoloEnMap(segundo);

    	tercero.first += this->listaTerminos.at(i-4);
    	tercero.first += " ";
    	tercero.first += this->listaTerminos.at(i-3);
    	tercero.first += this->separadorNgrama;
    	tercero.first += this->listaTerminos.at(i-2);
    	this->armarYGuardarNgramaSoloEnMap(tercero);

    	cuarto.first += this->listaTerminos.at(i-4);
    	cuarto.first += " ";
    	cuarto.first += this->listaTerminos.at(i-3);
    	cuarto.first += " ";
    	cuarto.first += this->listaTerminos.at(i-2);
    	cuarto.first += this->separadorNgrama;
    	cuarto.first += this->listaTerminos.at(i-1);
    	this->armarYGuardarNgramaSoloEnMap(cuarto);

    	quinto.first += this->listaTerminos.at(i-4);
    	quinto.first += " ";
    	quinto.first += this->listaTerminos.at(i-3);
    	quinto.first += " ";
    	quinto.first += this->listaTerminos.at(i-2);
    	quinto.first += " ";
    	quinto.first += this->listaTerminos.at(i-1);
    	quinto.first += this->separadorNgrama;
    	quinto.first += this->listaTerminos.at(i);
    	this->armarYGuardarNgramaSoloEnMap(quinto);
    }
    pair<std::string,int> ultimo; ultimo.first = "";

    ultimo.first += this->listaTerminos.at(this->listaTerminos.size()-4);
    ultimo.first += " ";
    ultimo.first += this->listaTerminos.at(this->listaTerminos.size()-3);
    ultimo.first += " ";
    ultimo.first += this->listaTerminos.at(this->listaTerminos.size()-2);
    ultimo.first += this->separadorNgrama;
    ultimo.first += this->listaTerminos.at(this->listaTerminos.size()-1);
    this->armarYGuardarNgramaSoloEnMap(ultimo);

    ultimo.first = "";
    ultimo.first += this->listaTerminos.at(this->listaTerminos.size()-3);
    ultimo.first += " ";
    ultimo.first += this->listaTerminos.at(this->listaTerminos.size()-2);
    ultimo.first += this->separadorNgrama;
    ultimo.first += this->listaTerminos.at(this->listaTerminos.size()-1);
    this->armarYGuardarNgramaSoloEnMap(ultimo);

    ultimo.first = "";
    ultimo.first += this->listaTerminos.at(this->listaTerminos.size()-2);
    ultimo.first += this->separadorNgrama;
    ultimo.first += this->listaTerminos.at(this->listaTerminos.size()-1);
    this->armarYGuardarNgramaSoloEnMap(ultimo);

    ultimo.first = "";
    ultimo.first += this->listaTerminos.at(this->listaTerminos.size()-1);
    this->armarYGuardarNgramaSoloEnMap(ultimo);

}

string  NGrama::avanzarPalabra(string oracion){
	return oracion.substr(oracion.find(' ')+1,oracion.size());
}

void NGrama::stringANGramaAlmacenadoEnMapSinListaTerminos(){

	while (oracion.size()> 1){
		string oracionAux = oracion;
		string ngramaAux = "";
		int i = 0;
		while(i<4){
			std::size_t found = oracionAux.find(' ');
			if (found!=std::string::npos){
				ngramaAux = ngramaAux + oracionAux.substr(0,found);
				pair<string,int> par;
				par.first = ngramaAux;
				armarYGuardarNgramaSoloEnMap(par);
				//std::replace( ngramaAux.begin(), ngramaAux.end(), ',', ' ');
				ngramaAux = ngramaAux + ' ';
				oracionAux = avanzarPalabra(oracionAux);
				i++;
			}else{
				ngramaAux = ngramaAux + oracionAux.substr(0,oracionAux.size());
				pair<string,int> par;
				par.first = ngramaAux;
				armarYGuardarNgramaSoloEnMap(par);
				ngramaAux = ngramaAux + ' ';
				oracionAux = avanzarPalabra(oracionAux);
				oracion.clear();
				break;

			}
		}
		oracion = avanzarPalabra(oracion);
		oracionAux.clear();
		ngramaAux.clear();
	}
	//guardo la ultima palabra.
	pair<string,int> par;
	par.first = oracion;
	armarYGuardarNgramaSoloEnMap(par);
	//cout<< oracion << endl;
	oracion.clear();
}


void NGrama::stringANGramaMapTerminosYNGramas(){
	 istringstream iss(this->oracion);
	 this->oracion.clear();
	 int posicion = 0;
	 	cout<<"Comienzo a leer terminos"<<endl;
	    do
		{
			//try{
				string sub;
				iss >> sub;
				//cout<<sub<<endl;
				//porque en la ultima iteracion viene vacio y pincha, tengo que ver bien la condicion de while.
				if(sub.compare("")){
						//guardo los terminos como upper.
						std::transform(sub.begin(), sub.end(),sub.begin(), ::toupper);
						mapDePosicionesTerminos.insert(std::pair<int,string>(posicion,sub));
					}
				posicion++;
		//	}catch(bad_alloc & ba) {
			//	cout<<posicion<<endl;
		//	}
		}while(iss);
	    cout<<"Finalizo de leer terminos"<<endl;
	    iss.clear();
	    cout<<"Comienzo a armar"<<endl;
	    for(std::size_t i=0; i<this->mapDePosicionesTerminos.size() -cantGrama+1; i++) {
	      	 pair<std::string,int> aux;
	         for(int k = 0; k < cantGrama; k++) {
	      	   if (aux.first.compare("")){
	      		 this->armarYGuardarNgramaSoloEnMap(aux);
	      	   }
	           if(k > 0) aux.first +=  " ";
	           aux.first+= (mapDePosicionesTerminos.find(i+k)->second);
	         }
	         this->armarYGuardarNgramaSoloEnMap(aux);
	      }
	    cout<<"Finalizo  armar"<<endl;
	    mapDePosicionesTerminos.clear();
}

void NGrama::levantarNGramasDeArchivo(){
	ifstream ficheroNgrama("ngrama.txt");
	 string s;
	 while(getline(ficheroNgrama, s)) {
		string frecuencia = s.substr(s.find_last_of(",")+1);
		stringstream ss(s);
		int i;
		ss >> i;
		string ngrama =  s.substr(0,s.find_last_of(",")-1);

	    cout << ngrama <<"-"<<frecuencia << endl;
	    mapDeNGramas.insert(std::pair<std::string,int>(ngrama,i));
	}
	 ficheroNgrama.close();
}

