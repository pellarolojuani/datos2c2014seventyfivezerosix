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
	this->ngramas = tr1::unordered_map<string, size_t>();
}

TestV2::TestV2(size_t id, string sentence,vector<pair<string,int> > listaNgrama) {
	this->id = id;
	this->sentence = sentence;
	this->sentencePredicha = "";
	this->parser = Parser();
	this->parser.abrirArchivo("test_v2.txt");
	this->parser.getLinea(); //para descartar la primera linea
	this->ngramas = tr1::unordered_map<string, size_t>();
}

TestV2::~TestV2() {
}

void TestV2::cerrarArchivo(){
	this->parser.cerrarArchivo();
}

void TestV2::armarHashDeRegistros(){
	NGramas ngramas = NGramas();
	ngramas.levantarNgramas();
	this->ngramas = ngramas.getRegistros();
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

void TestV2::calcularPrediccion(){
	tr1::unordered_map<string, size_t>::const_iterator iterator = this->ngramas;
	istringstream frase (this->sentenceSinComillas);
	int cantidadDePalabras = 0;

	string word;
	while (frase >> word){
		cantidadDePalabras++;
	}

	string trigramas[cantidadDePalabras-2];
	string bigramas[cantidadDePalabras-1];

	double triFrec[cantidadDePalabras-2];
	double biFrec[cantidadDePalabras-1];

	string tri_aux = "";
	string bi_aux = "";

	int tri_flag = 0; // cantidad de palabras guardadas en tri_aux
	int bi_flag = 0; // cantidad de palabras guardadas en bi_aux
	int tri_pos = 0; // guarda posicion dentro de trigramas[]
	int bi_pos = 0; // guarda posicion dentro de bigramas[]

	word = ""; // limpio contenido de word
	frase.str(this->sentenceSinComillas); // vuelvo a llenar el istringstream

	for(int i=0; i<cantidadDePalabras; i++){
		frase >> word;
		if (tri_flag < 3){
			tri_aux += word;
			tri_flag++;
		} else{
			trigramas[tri_pos] = tri_aux;
			tri_pos++;
			tri_flag = 1;
			tri_aux = word;
		}
		if (bi_flag < 2){
			bi_aux += word;
			bi_flag++;
		} else{
			bigramas[bi_pos] = bi_aux;
			bi_pos++;
			bi_flag = 1;
			bi_aux = word;
		}
	}

	for(int i=0; i<cantidadDePalabras-2; i++){
		iterator = ngramas.find(trigramas[i]);
		triFrec[i] = iterator->second;
	}

	double tri_minFrec = 9999999999999999999999999999999999999999999999;
	int tri_minFrec_pos = 0;

	// BUSCO CUAL ES EL TRIGRAMA DE MENOR FRECUENCIA
	for(int i=0; i<cantidadDePalabras-2; i++){
		if (triFrec[i] < tri_minFrec){
			tri_minFrec_pos = i;
			tri_minFrec = triFrec[i];
		} else if (triFrec[i] == tri_minFrec){
			iterator = ngramas.find(bigramas[i]);
			biFrec[i] = iterator->second;
			iterator = ngramas.find(bigramas[i+1]);
			biFrec[i+1] = iterator->second;

			double menor = 0;
			if (biFrec[i] <= biFrec[i+1]) menor = biFrec[i];
			else menor = biFrec[i+1];
		}
	}

	double bi_minFrec = 9999999999999999999999999999999999999999999999;
	int bi_minFrec_pos = 0;

	// BUSCO CUAL ES EL BIGRAMA DE MENOR FRECUENCIA
	if (biFrec[tri_minFrec_pos] == 0){
		iterator = ngramas.find(bigramas[tri_minFrec_pos]);
		biFrec[tri_minFrec_pos] = iterator->second;
		iterator = ngramas.find(bigramas[tri_minFrec_pos+1]);
		biFrec[tri_minFrec_pos+1] = iterator->second;
	}
	if (biFrec[tri_minFrec_pos] <= biFrec[tri_minFrec_pos+1]){
		bi_minFrec = biFrec[tri_minFrec_pos];
		bi_minFrec_pos = tri_minFrec_pos;
	} else{
		bi_minFrec = biFrec[tri_minFrec_pos+1];
		bi_minFrec_pos = tri_minFrec_pos+1;
	}

	// DEBERIA BUSCAR CUAL ES BIGRAMA CON MAYOR FRECUENCIA COMPUESTO POR:
	// 1ERA PALABRA DEL BIGRAMAS[bi_minFrec_pos] + ALGUNA OTRA
	//
	// UNA VEZ ENCONTRADO, "ALGUNA OTRA" ES LA PALABRA A AGREGAR!

}



}	/* namespace std */
