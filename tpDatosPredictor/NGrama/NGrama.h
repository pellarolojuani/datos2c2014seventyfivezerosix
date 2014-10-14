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
	void armarYGuardarNgrama(pair<string,int> par);

public:
	NGrama();
	NGrama(int cantGrama, string separadorNgrama);
	NGrama(string oracion,int cantGrama,string separadorNgrama);
	virtual ~NGrama();
	void stringANgrama();

	void streamANgrama(FILE* fp);

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
};


#endif /* NGRAMA_H_ */
