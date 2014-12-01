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

string TestV2::getTerminoMasProbable(string unContexto, string unContextoPosterior){
	//este metodo devuelve el termino con mayor frecuencia dentro de el contexto indicado como parametro

	size_t maxFrec = 0;
	string maxElemento = "";
	tr1::unordered_map<string, tr1::unordered_map<string, size_t> >::iterator it_buscadorContexto;
	tr1::unordered_map<string, size_t>::iterator it_buscador2;
	size_t frecRegresivaProgresiva = 0;
	bool contextoPunto = false;

	it_buscadorContexto = this->ngramas.contextos.find(unContexto);
	if ( it_buscadorContexto == this->ngramas.contextos.end() ){
		// no encontro el contexto, buscamos si podemos reducir el contexto de 2 a 1 palabra
		size_t pos = unContexto.find(" ");
		if (pos != string::npos){
			unContexto = unContexto.substr(unContexto.find(" ")+1);
		}
	}

	for (tr1::unordered_map<string, size_t>::iterator it = this->ngramas.contextos[unContexto].begin(); it != this->ngramas.contextos[unContexto].end(); it++){
		frecRegresivaProgresiva = (*it).second;
		if (unContextoPosterior != ""){
			it_buscador2 = this->ngramas.contextos[(*it).first].find(unContextoPosterior);
			if (it_buscador2 != this->ngramas.contextos[(*it).first].end()){
				frecRegresivaProgresiva += (*it_buscador2).second;
			}
		}

		string contextoAnterior = unContexto;
		size_t pos = unContexto.find(" ");
		if (pos != string::npos){
			contextoAnterior = unContexto.substr(unContexto.find(" ")+1);
		}
		if (contextoAnterior==".") contextoPunto = true;
		char c = (*it).first[0];
		if (contextoPunto && !isupper(c)){
			frecRegresivaProgresiva = 0;
		}

		if (frecRegresivaProgresiva > maxFrec) {
			if ((*it).first.size() != 0){
				maxFrec = frecRegresivaProgresiva;
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
	if (oracionAux.size() == LONG_MAX_LINEA) oracionAux += this->parser.getLinea();
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

	tr1::unordered_map<string, tr1::unordered_map<string, size_t> >::iterator it_buscadorContexto;
	tr1::unordered_map<string, size_t>::iterator it_buscadorTermino;
	double num = 0;
	double den = 0;

	it_buscadorContexto = this->ngramas.contextos.find(unContexto);
	if ( it_buscadorContexto != this->ngramas.contextos.end() ){
		// encontro el contexto
		it_buscadorTermino = this->ngramas.contextos[unContexto].find(unTermino);
		if ( it_buscadorTermino != this->ngramas.contextos[unContexto].end() ){
			// encontro el termino con dicho contexto
			num = (*it_buscadorTermino).second;
			den = this->ngramas.contextos[unContexto][TOTAL_FRECUENCIAS];
		}
	}
	if ( it_buscadorContexto == this->ngramas.contextos.end() || it_buscadorTermino == this->ngramas.contextos[unContexto].end() ){
			// no encontro el contexto o encontro el contexto, pero no existe el termino con dicho contexto
			size_t pos = unContexto.find(" ");
			if (pos != string::npos){
				string contextoAnterior = unContexto.substr(unContexto.find(" ")+1);
				it_buscadorTermino = this->ngramas.contextos[contextoAnterior].find(unTermino);
				// el contextoAnterior existe, porque existe contexto
				if ( it_buscadorTermino == this->ngramas.contextos[contextoAnterior].end() ){
					// no encontro el termino con contextoAnterior
					if (pos == string::npos){ //en este caso calculamos la probabilidad del termino sin contexto
					num = 0.4*0.4*this->ngramas.contextos[""][unTermino];
					den = this->ngramas.contextos[""][TOTAL_FRECUENCIAS];
					}
				} else{
					// encontro el termino con contextoAnterior
					num = 0.4*(*it_buscadorTermino).second;
					den = this->ngramas.contextos[contextoAnterior][TOTAL_FRECUENCIAS];
					}
			}
		}

	if (den == 0) return 0; 	//en esta caso no existe el termino en nuestro diccionario: CAGAMOS!

	return num/den;

}

double TestV2::calcularProbabilidad_bigrama(string termino1, string termino2){
	double uni = this->calcularProbabilidad("", termino1);
	double bi = this->calcularProbabilidad(termino1, termino2);
	return uni*bi;	//Regla de la cadena. Probabilidad!
}

double TestV2::calcularProbabilidad_trigrama(string termino1, string termino2, string termino3){
	double bi = this->calcularProbabilidad_bigrama(termino1, termino2);
	double tri = this->calcularProbabilidad(termino1 + " " + termino2, termino3);
	return bi*tri;	//Regla de la cadena. Probabilidad!
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

	if (cantidadDePalabras<3){
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
		triProb.push_back(this->calcularProbabilidad_trigrama(unigramas.at(i), unigramas.at(i+1), unigramas.at(i+2)));
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
			biProb[i] = this->calcularProbabilidad_bigrama(unigramas[i], unigramas[i+1]);
			biProb[i+1] = this->calcularProbabilidad_bigrama(unigramas[i+1], unigramas[i+2]);

			double menor1;
			if (biProb[i] <= biProb[i+1]) menor1 = biProb[i];
			else menor1 = biProb[i+1];

			double menor2;
			biProb[tri_minProb_pos] = this->calcularProbabilidad_bigrama(unigramas[tri_minProb_pos], unigramas[tri_minProb_pos+1]);
			biProb[tri_minProb_pos+1] = this->calcularProbabilidad_bigrama(unigramas[tri_minProb_pos+1], unigramas[tri_minProb_pos+2]);
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
		biProb[tri_minProb_pos] = this->calcularProbabilidad_bigrama(unigramas[tri_minProb_pos], unigramas[tri_minProb_pos+1]);;
		if (cantidadDePalabras>2){
			biProb[tri_minProb_pos+1] = this->calcularProbabilidad_bigrama(unigramas[tri_minProb_pos+1], unigramas[tri_minProb_pos+2]);;
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
	if (bi_minProb_pos>0){
		// quiere decir que no estamos al comienzo de la frase, hay palabras antes que bi_minProb_pos
		palabraPropuesta = this->getTerminoMasProbable(bigramas.at(bi_minProb_pos-1), unigramas.at(bi_minProb_pos+1));
	} else{
	palabraPropuesta = this->getTerminoMasProbable(unigramas.at(bi_minProb_pos), unigramas.at(bi_minProb_pos+1));
	}

	// Evaluo si el trigrama con la palabra propuesta es mas probable que el trigrama sin insercion
	double uni = this->calcularProbabilidad("", unigramas.at(tri_minProb_pos));
	double bi;
	double tri;
	double prob_trigramaPropuesto;
	if ( bi_minProb_pos == tri_minProb_pos ){
		prob_trigramaPropuesto = this->calcularProbabilidad_trigrama(unigramas[tri_minProb_pos], palabraPropuesta, unigramas[tri_minProb_pos+1]);
	} else{
		prob_trigramaPropuesto = this->calcularProbabilidad_trigrama(unigramas[tri_minProb_pos], unigramas[tri_minProb_pos+1], palabraPropuesta);
	}

	// Si el trigramaPropuesto no es mas probable, no inserto nada y devuelvo misma frase
	if (prob_trigramaPropuesto - tri_minProb < 0.1){
		this->sentencePredicha = this->sentenceSinComillas;
		return 0;
	}

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
