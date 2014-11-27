/*
 * TestV2.cpp
 *
 *  Created on: 19/10/2014
 *      Author: lucas
 */

#include "TestV2.h"
#include <limits>


namespace std {

TestV2::TestV2() {
	this->id = 0;
	this->sentence = "";
	this->sentencePredicha = "";
	this->eof = false;
	this->parser = Parser();
	this->parser.abrirArchivo("test_v2.txt");

	this->resultados = fopen("test_results.txt", "w+");

	//descarto la primera linea del archivo de test y se la pongo
	//al archivo de test_results
	fputs(this->parser.getLinea().c_str(), this->resultados);
	//fputc('\n', this->resultados);

}

TestV2::TestV2(size_t id, string sentence,vector<pair<string,int> > listaNgrama) {
	this->id = id;
	this->sentence = sentence;
	this->sentencePredicha = "";
	this->eof = false;
	this->parser = Parser();
	this->parser.abrirArchivo("test_v2.txt");

	this->resultados = fopen("test_results.txt", "w+");

	//descarto la primera linea del archivo de test y se la pongo
	//al archivo de test_results
	fputs(this->parser.getLinea().c_str(), this->resultados);
	fputc('\n', this->resultados);

}

void TestV2::cerrarArchivoResultados(){
	fclose(this->resultados);
}

void TestV2::correrPruebas(){

	this->readNextSentence();
	while (!this->eof){
		this->calcularPrediccion();
		this->guardarSentencePredicha();
		this->readNextSentence();
	}
	this->cerrarArchivoResultados();
	this->cerrarArchivo();
}

void TestV2::guardarSentencePredicha(){
	string comillas = "\"";
	string linea = "";
	ostringstream num;
	num << (this->id);
	string ID = num.str();
	string sentence = "";
	for (size_t a = 0; a < this->sentencePredicha.length(); a++){
		sentence += this->sentencePredicha[a];
		if (this->sentencePredicha[a] == '"'){
			sentence += '"';
		}
	}
	linea += ID;
	linea += ",";
	linea += comillas;
	linea += sentence;
	linea += comillas;
	linea += '\n';
	fputs(linea.c_str(), this->resultados);
	cout<<ID<<endl;
}

TestV2::~TestV2() {
}

void TestV2::cerrarArchivo(){
	this->parser.cerrarArchivo();
}

void TestV2::armarHashDeRegistros(){
	this->ngramas = NGramas(3, " ");
	ngramas.levantarNgramas();
}

string TestV2::getTerminoMasProbable(string unContexto){
	//este metodo devuelve el termino con mayor frecuencia dentro de el contexto indicado como parametro

	size_t maxFrec = 0;
	string maxElemento = "";
	for (tr1::unordered_map<string, size_t>::iterator it = this->ngramas.contextos[unContexto].begin(); it != this->ngramas.contextos[unContexto].end(); it++){
		if ((*it).second > maxFrec) {
			if ((*it).first.size() != 0){
				maxFrec = (*it).second;
				maxElemento = (*it).first;
			}
		}
	}
	return maxElemento;
}

void TestV2::readNextSentence(){
	//Lee la siguiente frase en el lote de pruebas y actualiza
	//los valores de id y sentence.


	string comillaDoble = "\"\"";
	string comillaSimple = "\"";

	size_t posicion = this->parser.getPosicionActualArchivo();
	string oracionAux =  this->parser.getLinea();
	if (oracionAux == LONG_MAX_LINEA) oracionAux += this->parser.getLinea();
	if (oracionAux.size() == 0 || oracionAux.size() == 1){
		this->eof = true;
		return;
	}

	string oracion = oracionAux.erase(oracionAux.find_last_not_of(" \n\r\t")+1);
	std::size_t pos = oracion.find(",");
	string id = oracion.substr(0,pos);
	string sentence = oracion.substr(pos+1);

	string sentenceSinComillaDoble;
	if (sentence.size()==2){
		sentenceSinComillaDoble = "";
	} else{
		string sentenceSinComilla = sentence.substr(1,sentence.size()-2);

		for (size_t a = 0; a < sentenceSinComilla.length()-1; a++){
			if (sentenceSinComilla[a] == '"' && sentenceSinComilla[a+1] == '"'){
				sentenceSinComilla.replace(a, 1, "");
			}
		}
		sentenceSinComillaDoble = sentenceSinComilla;
	}
	this->setId(std::atoi(id.c_str()));
	this->setSentenceSinComillas(sentenceSinComillaDoble);
	this->sentencePredicha = "";

}

double TestV2::calcularProbabilidad(string unContexto, string unTermino){

	double num = this->ngramas.contextos[unContexto][unTermino];
	double den = this->ngramas.contextos[unContexto][TOTAL_FRECUENCIAS];

	if (den == 0) return 0; 	//en esta caso no existe el termino en nuestro diccionario: CAGAMOS!
	if (num == 0 && unContexto.size() != 0){	//Bajamos al contexto anterior para calcular su probabilidad
		size_t pos = unContexto.find(" ");
		if (pos != string::npos){
			string contextoAnterior = unContexto.substr(unContexto.find(" ")+1);
			num = 0.4*this->ngramas.contextos[contextoAnterior][unTermino];
		}
		if (num == 0 || pos == string::npos){ //en este caso calculamos la probabilidad del termino sin contexto
			num = 0.4*0.4*this->ngramas.contextos[""][unTermino];
		}
	}
	return num/den;

}

int TestV2::calcularPrediccion(){
	istringstream unaFrase (this->sentenceSinComillas);
	if (this->sentenceSinComillas==""){
		this->sentencePredicha = this->getTerminoMasProbable("");
		return 1;
	}

	int cantidadDePalabras = 0;
	string word;
	while (unaFrase >> word){
		cantidadDePalabras++;
	}

	if (cantidadDePalabras==1){
		this->sentencePredicha = this->sentenceSinComillas;
		return 0;
	}

	vector<string> trigramas = vector<string>();
	vector<string> bigramas = vector<string>();
	vector<string> unigramas = vector<string>();

	vector<double> triFrec = vector<double>();
	vector<double> biFrec = vector<double>();

	vector<double> triProb = vector<double>();     // sobrarian 2 posiciones que se ocupan pero luego se eliminan
	vector<double> biProb = vector<double>(cantidadDePalabras-1);      // sobraria 1 posicion que se ocupa pero luego se elimina
	//cout << "Creados los vectores"<< endl;

	string tri_aux = "";
	string bi_aux = "";

	int tri_flag = 0; // cantidad de palabras guardadas en tri_aux
	int bi_flag = 0; // cantidad de palabras guardadas en bi_aux

	word = ""; // limpio contenido de word
	istringstream frase (this->sentenceSinComillas); // vuelvo a llenar el istringstream

	for(int i=0; i<cantidadDePalabras; i++){
		frase >> word;
		unigramas.push_back(word);
		if (tri_flag < 3){
			tri_aux += word;
			tri_aux += " ";
			tri_flag++;
		} else{
			if (tri_flag == 3){
				tri_aux = tri_aux.substr(0, tri_aux.size()-1); //saco el espacio al final del string
				trigramas.push_back(tri_aux);
			}
			tri_aux = tri_aux.substr(tri_aux.find_first_of(" ")+1);
			tri_aux += " ";
			tri_aux += word;
			tri_aux += " ";
		}

		if (bi_flag < 2){
			bi_aux += word;
			bi_aux += " ";
			bi_flag++;
		} else{
			if (bi_flag == 2){
				bi_aux = bi_aux.substr(0, bi_aux.size()-1); //saco el espacio al final del string
				bigramas.push_back(bi_aux);
			}
			bi_aux = bi_aux.substr(bi_aux.find_first_of(" ")+1);
			bi_aux += " ";
			bi_aux += word;
			bi_aux += " ";
		}

		if (i == cantidadDePalabras -1){
			tri_aux = tri_aux.substr(0, tri_aux.size()-1); //saco el espacio al final del string
			trigramas.push_back(tri_aux);
			bi_aux = bi_aux.substr(0, bi_aux.size()-1); //saco el espacio al final del string
			bigramas.push_back(bi_aux);
		}
	}
	//cout << "Llenados los vectores"<< endl;
	for(int i=0; i<cantidadDePalabras-2; i++){
		double uni = this->calcularProbabilidad("", unigramas.at(i));
		double bi = this->calcularProbabilidad(unigramas.at(i), unigramas.at(i+1));
		double tri = this->calcularProbabilidad(bigramas.at(i), unigramas.at(i+2));
		triProb.push_back(uni*bi*tri);	//Regla de la cadena. Probabilidad!
	}
	//cout << "Calculadas las probabilidades de tri"<< endl;
	size_t tri_minProb = std::numeric_limits<double>::max();
	size_t tri_minProb_pos = 0;

	// BUSCO CUAL ES EL TRIGRAMA DE MENOR PROBABILIDAD
	for(int i=0; i<cantidadDePalabras-2; i++){
		if (triProb.at(i) < tri_minProb){
			tri_minProb_pos = i;
			tri_minProb = triProb.at(i);
		} else if (triProb.at(i) == tri_minProb){
			double bi = this->calcularProbabilidad(unigramas[i], unigramas[i+1]);
			double uni = this->calcularProbabilidad("", unigramas[i]);
			biProb[i] = bi*uni;
			bi = this->calcularProbabilidad(unigramas[i+1], unigramas[i+2]);
			uni = this->calcularProbabilidad("", unigramas[i+1]);
			biProb[i+1] = bi+uni; //Regla de la cadena. Probabilidad!

			double menor1;
			if (biProb[i] <= biProb[i+1]) menor1 = biProb[i];
			else menor1 = biProb[i+1];

			double menor2;
			bi = this->calcularProbabilidad(unigramas[tri_minProb_pos], unigramas[tri_minProb_pos+1]);
			uni = this->calcularProbabilidad("", unigramas[tri_minProb_pos]);
			biProb[tri_minProb_pos] = bi+uni; //Regla de la cadena. Probabilidad!
			bi = this->calcularProbabilidad(unigramas[tri_minProb_pos+1], unigramas[tri_minProb_pos+2]);
			uni = this->calcularProbabilidad("", unigramas[tri_minProb_pos+1]);
			biProb[tri_minProb_pos+1] = bi+uni; //Regla de la cadena. Probabilidad!
			if (biProb[tri_minProb_pos] <= biProb[tri_minProb_pos+1]) menor2 = biProb[tri_minProb_pos];
			else menor2 = biProb[tri_minProb_pos+1];

			if (menor1 < menor2){
				tri_minProb_pos = i;
				tri_minProb = triProb.at(i);
			}

		}
	}
	//cout << "El trigrama de menor probabilidad es: "<< trigramas.at(tri_minProb_pos)<<endl;

	double bi_minProb = std::numeric_limits<double>::max();
	int bi_minProb_pos = 0;

	// BUSCO CUAL ES EL BIGRAMA DE MENOR PROBABILIDAD
	if (biProb[tri_minProb_pos] == 0){
		double bi = this->calcularProbabilidad(unigramas[tri_minProb_pos], unigramas[tri_minProb_pos+1]);
		double uni = this->calcularProbabilidad("", unigramas[tri_minProb_pos]);
		biProb[tri_minProb_pos] = bi*uni;
		if (cantidadDePalabras>2){
			bi = this->calcularProbabilidad(unigramas[tri_minProb_pos+1], unigramas[tri_minProb_pos+2]);
			uni = this->calcularProbabilidad("", unigramas[tri_minProb_pos+1]);
			biProb[tri_minProb_pos+1] = bi*uni;
		}
	}
	if ( cantidadDePalabras>2 && biProb[tri_minProb_pos] >= biProb[tri_minProb_pos+1] ){
		bi_minProb = biProb[tri_minProb_pos+1];
		bi_minProb_pos = tri_minProb_pos+1;
	} else{
		bi_minProb = biProb[tri_minProb_pos];
		bi_minProb_pos = tri_minProb_pos;
	}
	//cout << "El bigrama de menor probab es: "<< bigramas.at(bi_minProb_pos)<<endl;

	// BUSCO CUAL ES BIGRAMA CON MAYOR PROBABILIDAD COMPUESTO POR:
	// 1ERA PALABRA DEL BIGRAMAS[bi_minFrec_pos] + ALGUNA OTRA

	string palabraPropuesta;
	palabraPropuesta = this->getTerminoMasProbable(unigramas.at(bi_minProb_pos));

	// ARMO LA SENTENCE PREDICHA
	word = ""; // limpio contenido de word
	istringstream sentence (this->sentenceSinComillas); // vuelvo a llenar el istringstream
	string frasePropuesta = "";

	for(int i=0; i<bi_minProb_pos+1; i++){
		sentence >> word;
		frasePropuesta += word;
		frasePropuesta += " ";
	}
	frasePropuesta += palabraPropuesta;
	if (palabraPropuesta.size() != 0) frasePropuesta += " ";

	for(int i=bi_minProb_pos+1; i<cantidadDePalabras; i++){
		sentence >> word;
		frasePropuesta += word;
		if (i != cantidadDePalabras-1) frasePropuesta += " ";
	}

	this->sentencePredicha = frasePropuesta;

	return 1;
}


}	/* namespace std */
