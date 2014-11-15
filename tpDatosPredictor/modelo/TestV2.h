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

namespace std {

class TestV2 {


private:
 	size_t id;
	string sentence; //contiene una sentencia incompleta.
	string sentencePredicha; //contiene la sentencia completa.
	Parser parser;
	string sentenceSinComillas;

	tr1::unordered_map<string, size_t> ngramas;//acá van los ngramas levantados de disco

	void armarHashDeRegistros();

public:
	TestV2();
	TestV2(size_t id, string sentence,vector<pair<string,int> > listaNgrama);
	virtual ~TestV2();

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
};

} /* namespace std */

#endif /* TESTV2_H_ */
