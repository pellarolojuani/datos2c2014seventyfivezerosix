/*
 * TestV2.cpp
 *
 *  Created on: 19/10/2014
 *      Author: lucas
 */

#include "TestV2.h"


namespace std {

TestV2::TestV2() {
	this->id = 0;
	this->sentence = "";
	this->sentencePredicha = "";
	this->parser = Parser();
	this->parser.abrirArchivo("test_v2.txt");
	this->parser.getLinea(); //para descartar la primera linea
}

TestV2::TestV2(size_t id, string sentence,vector<pair<string,int> > listaNgrama) {
	this->id = id;
	this->sentence = sentence;
	this->sentencePredicha = "";
	this->parser = Parser();
	this->parser.abrirArchivo("test_v2.txt");
	this->parser.getLinea(); //para descartar la primera linea

}

TestV2::~TestV2() {
}

void TestV2::cerrarArchivo(){
	this->parser.cerrarArchivo();
}

void TestV2::readNextSentence(){
	//Lee la siguiente frase en el lote de pruebas y actualiza
	//los valores de id y sentence.

	string comillaDoble = "\"\"";
	string comillaSimple = "\"";

	size_t posicion = this->parser.getPosicionActualArchivo();
	string oracionAux =  this->parser.getLinea();

	//para que no procese "id","sentence" (son los nombres de las columnas).
	if(oracionAux.find("sentence") == std::string::npos){
		string oracion = oracionAux.erase(oracionAux.find_last_not_of(" \n\r\t")+1);
		std::size_t pos = oracion.find(",");
		string id = oracion.substr(0,pos);
		string sentence = oracion.substr(pos+1);
		string sentenceSinComilla = sentence.substr(1,sentence.rfind('"')-1);

		string sentenceSinComillaDoble = sentenceSinComilla;
		for (int i = 0; i < sentenceSinComilla.length()-1; i++){
			if (sentenceSinComilla[i] == '"' && sentenceSinComilla[i+1] == '"'){
				sentenceSinComillaDoble.replace(i, 1, "");
			}
		}

		this->setId(std::atoi(id.c_str()));
		this->setSentence(sentenceSinComillaDoble);
	}
}

}	/* namespace std */
