/*
 * TestV2.h
 *
 *  Created on: 19/10/2014
 *      Author: lucas
 */

#ifndef TESTV2_H_
#define TESTV2_H_
#include <string>
#include <vector>
#include <tr1/unordered_map>
#include "../parser/Parser.h"
#include "../BIS/NGramas.h"

namespace std {

class TestV2 {


private:
 	size_t id;
	string sentence; //contiene una sentencia incompleta.
	string sentencePredicha; //contiene la sentencia completa.
	Parser parser;	//Para todas las operaciones de lectura/escritura del archivo
	string sentenceSinComillas;
	bool eof;

	NGramas ngramas;

	FILE *resultados;


public:
	TestV2();
	TestV2(size_t id, string sentence,vector<pair<string,int> > listaNgrama);
	TestV2(string archivoPruebas);
	virtual ~TestV2();

	string getTerminoMasProbable(string unContexto, string unContextoPosterior = "");
	void armarHashDeRegistros();
	void cerrarArchivoResultados();
	void guardarSentencePredicha();
	double calcularProbabilidad(string unContexto, string unTermino);
	double calcularProbabilidad_bigrama(string termino1, string termino2);
	double calcularProbabilidad_trigrama(string termino1, string termino2, string termino3);

	size_t getId() const {
		return id;
	}

	void setId(size_t id) {
		this->id = id;
	}

	Parser getParser(){
		return this->parser;
	}

	void readNextSentence();
	void correrPruebas();


	const string& getSentence() const {
		return sentence;
	}

	void setSentence(const string& sentente) {
		this->sentence = sentente;
	}

	const string& getSentencePredicha() const {
		return sentencePredicha;
	}

	void setSentencePredicha(const string& sentencePredicha) {
		this->sentencePredicha = sentencePredicha;
	}

	void cerrarArchivo();

	const string& getSentenceSinComillas() const {
		return sentenceSinComillas;
	}

	void setSentenceSinComillas(const string& sentenceSinComillas) {
		this->sentenceSinComillas = sentenceSinComillas;
	}

	int calcularPrediccion(); // CALCULA LA PALABRA FALTANTE Y MODIFICA SENTECEPREDICHA. DEVUELVE 1 SI INSERTA ALGO, 0 CASO QUE NO
};

} /* namespace std */

#endif /* TESTV2_H_ */
