/*
 * NGrama.h
 *
 *  Created on: 11/10/2014
 *      Author: lucas
 */

#ifndef NGRAMA_H_
#define NGRAMA_H_
#include <string>
#include <vector>
#include <iostream>
#include <map>
#include "../Constantes.h"

using namespace std;


class NGrama {

private:
	string oracion;
	int cantGrama;
	string separadorNgrama;
	vector<string> listaTerminos;
	//vector<string> listaNgrama;
	vector<pair<string,int> > listaNgrama;
	map<string,int> mapDePosiciones;
	map<int,string> mapDePosicionesTerminos;
	map<string,int> mapDeNGramas;
	void armarYGuardarNgrama(pair<string,int> par);
	void armarYGuardarNgramaSoloEnMap(pair<string,int> par);
	long* frecuenciaDeNgramas;
	string avanzarPalabra(string oracion);

public:
	NGrama();
	NGrama(int cantGrama, string separadorNgrama);
	NGrama(string oracion,int cantGrama,string separadorNgrama);
	virtual ~NGrama();
	void stringANgrama();
	void stringANGramaMax(); //solo arma los ngrama de long max indicada.
	void stringANGramaAlmacenadoEnMap();
	void stringANGramaAlmacenadoEnMapSinListaTerminos();
	void stringANGramaMapTerminosYNGramas();
	void levantarNGramasDeArchivo();
	void stringA5Grama();

	void streamANgrama(FILE* fp);
	void aumentarFrecuenciaDeNgrama(int tamanioGrama);
	long getFrecuenciaDeNgrama(int tamanioGrama);

	const std::vector<std::string>& getListaTerminos() const {
		return listaTerminos;
	}

	void setListaTerminos(const std::vector<std::string>& listaTerminos) {
		this->listaTerminos = listaTerminos;
	}

	int getCantGrama() const {
		return cantGrama;
	}

	void setCantGrama(int cantGrama) {
		this->cantGrama = cantGrama;
	}

	const string& getOracion() const {
		return oracion;
	}

	void setOracion(const string& oracion) {
		this->oracion = oracion;
	}

	const std::vector<std::pair<std::string, int> >& getListaNgrama() const {
		return listaNgrama;
	}

	void setListaNgrama(
			const std::vector<std::pair<std::string, int> >& listaNgrama) {
		this->listaNgrama = listaNgrama;
	}

	const map<string, int>& getMapDePosiciones() const {
		return mapDePosiciones;
	}

	void setMapDePosiciones(const map<string, int>& mapDePosiciones) {
		this->mapDePosiciones = mapDePosiciones;
	}

	const map<string, int>& getMapDeNGramas() const {
		return mapDeNGramas;
	}

	void setMapDeNGramas(const map<string, int>& mapDeNGramas) {
		this->mapDeNGramas = mapDeNGramas;
	}

	const map<int, string>& getMapDePosicionesTerminos() const {
		return mapDePosicionesTerminos;
	}

	void setMapDePosicionesTerminos(
			const map<int, string>& mapDePosicionesTerminos) {
		this->mapDePosicionesTerminos = mapDePosicionesTerminos;
	}
};


#endif /* NGRAMA_H_ */
