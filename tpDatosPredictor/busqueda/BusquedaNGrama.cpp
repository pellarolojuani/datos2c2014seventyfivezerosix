/*
 * Busqueda.cpp
 *
 *  Created on: 25/10/2014
 *      Author: lucas
 */

#include "BusquedaNGrama.h"

using namespace std;


BusquedaNGrama::BusquedaNGrama() {
	// TODO Auto-generated constructor stub

}

BusquedaNGrama::~BusquedaNGrama() {
	// TODO Auto-generated destructor stub
}

string BusquedaNGrama::buscarPalabraFaltanteAPartirDeNgrama(string ngrama, string pathArchivo){

	/*
	 * -armo los 4grama con long = 4
	 * -con 4grama resultados, busco su offset en el arbol, con el offset los busco en los archivos
	 *  y me me quedo con el de menor frecuencia/probabilidad. NOTA: deberiamos definir que pasa si hay mas de
	 *  uno con igual menor frecuencia.
	 *  - repito este proceso con long = log - 1 hasta que long = 1.
	 *  -Para seleccionar el término candidato a colocar en esa posición volvemos al mayor contexto posible,
	 *  en este caso es un contexto de 4 términos y dentro de ese contexto elegimos el término con
	 *  mayor probabilidad, es decir, el que mayor frecuencia tiene como candidato para completar nuestra frase.
	 *  - armo la frase completa con el ngrama de M y luego la devuelvo.
	 *
	*/

	return "";
}

