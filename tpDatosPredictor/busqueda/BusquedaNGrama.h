/*
 * Busqueda.h
 *
 *  Created on: 25/10/2014
 *      Author: lucas
 */

#ifndef BUSQUEDA_H_
#define BUSQUEDA_H_
#include <string>
#include <map>

namespace std {

class BusquedaNGrama {
public:
	BusquedaNGrama();
	virtual ~BusquedaNGrama();
	void resolverConsultas(map<string,int> mapDeNGramasSet);


private:
	/*
	 * Busca la palabra faltante a traves de un ngrama candidato (el de menor probabilidad).
	 * retorno: devuelve el ngrama completo.
	 */
	string buscarPalabraFaltanteAPartirDeNgrama(string ngrama,map<string,int> mapDeNGramas);
	string calculoProbabilidadYElijoNgrama(map<string,int> mapDeNGramasSet,map<string,int> mapDeNGramasSentence);
	string buscarPalabra(string ngrama,map<string,int> mapDeNGramasSet);
	string armarSentenceCompleta(string fraseOriginal,string palabra);

};

} /* namespace std */

#endif /* BUSQUEDA_H_ */
