/*
 * Busqueda.cpp
 *
 *  Created on: 25/10/2014
 *      Author: lucas
 */

#include "BusquedaNGrama.h"
#include "../NGrama/NGrama.h"
#include <iostream>
#include <fstream>
#include "../modelo/TestV2.h"
#include <map>

using namespace std;


BusquedaNGrama::BusquedaNGrama() {
	// TODO Auto-generated constructor stub

}

BusquedaNGrama::~BusquedaNGrama() {
	// TODO Auto-generated destructor stub
}

string BusquedaNGrama::buscarPalabraFaltanteAPartirDeNgrama(string frase,map<string,int> mapDeNGramasSet){

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
	//guardo la frasee original
	string fraseOriginal = frase;
	NGrama ngrama3 = NGrama(frase, 3,",");
	ngrama3.stringANGramaMax();
	frase.clear();
	frase = calculoProbabilidadYElijoNgrama(mapDeNGramasSet,ngrama3.getMapDeNGramas());
	ngrama3.~NGrama();
	//con el ngrama de 3 seleccionado, armo los de 2.
	NGrama ngrama2 = NGrama(frase, 2,",");
	ngrama2.stringANGramaMax();
	frase = calculoProbabilidadYElijoNgrama(mapDeNGramasSet,ngrama2.getMapDeNGramas());
	string palabra = buscarPalabra(frase,ngrama2.getMapDeNGramas());

	return armarSentenceCompleta(fraseOriginal,palabra);
}

void BusquedaNGrama::resolverConsultas(map<string,int> mapNGrama){

		ifstream leer_fich ("test_v2.txt");
		ofstream fichero("test_v2_completo.txt");

		TestV2 testV2 = TestV2();
		char* linea = new char[2800];
		//descarto la sentencia 1;
		leer_fich.getline(linea,2800,'\n');
		fichero << linea << endl;

		for (int i = 0; i < 8; i ++){

			leer_fich.getline(linea,2800,'\n');
			std::string oracionAux = std::string(linea);

			string oracion = oracionAux.erase(oracionAux.find_last_not_of(" \n\r\t")+1);
			//cout<<oracion<<endl;
			std::size_t pos = oracion.find(",");
			string id = oracion.substr(0,pos);
			string sentence = oracion.substr(pos+1);
			//cout<<sentence.find('"')<<endl;
			string sentenceSinComilla = sentence.substr(1,sentence.rfind('"')-1);
			testV2.setSentenceSinComillas(sentenceSinComilla);
			testV2.setId(std::atoi(id.c_str()));
			testV2.setSentence(sentence);

			cout<<"---"<<endl;
			cout<<"ID: "<<testV2.getId()<<endl;
			cout<<"SENTENCE: "<<testV2.getSentence()<<endl;
			cout<<"SENTENCE SIN COM: "<<testV2.getSentenceSinComillas()<<endl;
			cout<<"---"<<endl;
			//aca guardo la sentencia completo en el archivo de salida.
			fichero << testV2.getId() << ","<<'"'<<testV2.getSentenceSinComillas()<<'"'<<endl;

		}

		for(std::size_t i=0; i < testV2.getListaNgrama().size();++i){
			cout << testV2.getListaNgrama()[i].first  << "," << testV2.getListaNgrama()[i].second << endl;
		}
		leer_fich.close();
		fichero.close();
}

string BusquedaNGrama::calculoProbabilidadYElijoNgrama(map<string,int> mapDeNGramasSet,map<string,int> mapDeNGramasSentence){
	return "";
}
string BusquedaNGrama::buscarPalabra(string ngrama,map<string,int> mapDeNGramasSet){
	return "";
}

string BusquedaNGrama::armarSentenceCompleta(string fraseOriginal,string palabra){
	return "";
}



