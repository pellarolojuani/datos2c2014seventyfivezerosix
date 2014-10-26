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

}

TestV2::TestV2(int id, string sentence,vector<pair<string,int> > listaNgrama) {
	this->id = id;
	this->sentence = sentence;
	this->listaNgrama = listaNgrama;
	this->sentencePredicha = "";

}

TestV2::~TestV2() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
