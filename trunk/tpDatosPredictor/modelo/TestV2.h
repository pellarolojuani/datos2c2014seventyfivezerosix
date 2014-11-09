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
#include "../parser/Parser.h"

namespace std {

class TestV2 {


private:
 	size_t id;
	string sentence; //contiene una sentencia incompleta.
	string sentencePredicha; //contiene la sentencia completa.
	vector<pair<string,int> > listaNgrama;
	Parser parser;
	string sentenceSinComillas;

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

	const vector<pair<string, int> >& getListaNgrama() const {
		return listaNgrama;
	}

	void setListaNgrama(const vector<pair<string, int> >& listaNgrama) {
		this->listaNgrama = listaNgrama;
	}

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
