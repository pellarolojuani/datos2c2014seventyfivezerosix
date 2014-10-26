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

namespace std {

class TestV2 {


private:
 	int id;
	string sentente; //contiene una sentencia incompleta.
	string sentencePredicha; //contiene la sentencia completa.
	vector<pair<string,int> > listaNgrama;

public:
	TestV2();
	TestV2(int id, string sentence,vector<pair<string,int> > listaNgrama);
	virtual ~TestV2();

	int getId() const {
		return id;
	}

	void setId(int id) {
		this->id = id;
	}

	const vector<pair<string, int> >& getListaNgrama() const {
		return listaNgrama;
	}

	void setListaNgrama(const vector<pair<string, int> >& listaNgrama) {
		this->listaNgrama = listaNgrama;
	}

	const string& getSentente() const {
		return sentente;
	}

	void setSentence(const string& sentente) {
		this->sentente = sentente;
	}

	const string& getSentencePredicha() const {
		return sentencePredicha;
	}

	void setSentencePredicha(const string& sentencePredicha) {
		this->sentencePredicha = sentencePredicha;
	}
};

} /* namespace std */

#endif /* TESTV2_H_ */
