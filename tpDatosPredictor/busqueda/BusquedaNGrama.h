/*
 * Busqueda.h
 *
 *  Created on: 25/10/2014
 *      Author: lucas
 */

#ifndef BUSQUEDA_H_
#define BUSQUEDA_H_
#include <string>

namespace std {

class BusquedaNGrama {
public:
	BusquedaNGrama();
	virtual ~BusquedaNGrama();

private:
	/*
	 * Busca la palabra faltante a traves de un ngrama candidato (el de menor probabilidad).
	 * retorno: devuelve el ngrama completo.
	 */
	string buscarPalabraFaltanteAPartirDeNgrama(string ngrama,string pathArchivo);

};

} /* namespace std */

#endif /* BUSQUEDA_H_ */
