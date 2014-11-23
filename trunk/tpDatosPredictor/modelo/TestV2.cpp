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
	this->parser = Parser();
	this->parser.abrirArchivo("test_v2.txt");

	this->resultados = fopen("test_results.txt", "w+");

	//descarto la primera linea del archivo de test y se la pongo
	//al archivo de test_results
	fputs(this->parser.getLinea().c_str(), this->resultados);
	fputc('\n', this->resultados);

}

TestV2::TestV2(size_t id, string sentence,vector<pair<string,int> > listaNgrama) {
	this->id = id;
	this->sentence = sentence;
	this->sentencePredicha = "";
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
	size_t i = 0;
	while (i != 306682){
		this->readNextSentence();
		this->calcularPrediccion();
		this->guardarSentencePredicha();
		i++;
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
	linea += ID;
	linea += ",";
	linea += comillas;
	linea += this->sentencePredicha;
	linea += comillas;
	linea += '\n';
	fputs(linea.c_str(), this->resultados);
	cout<<"Generada sentence "<<ID<<endl;
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
			maxFrec = (*it).second;
			maxElemento = (*it).first;
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

	string oracion = oracionAux.erase(oracionAux.find_last_not_of(" \n\r\t")+1);
	std::size_t pos = oracion.find(",");
	string id = oracion.substr(0,pos);
	string sentence = oracion.substr(pos+1);
	string sentenceSinComilla = sentence.substr(1,sentence.size()-2);

	string sentenceSinComillaDoble;
	for (size_t a = 0; a < sentenceSinComilla.length()-1; a++){
		if (sentenceSinComilla[a] == '"' && sentenceSinComilla[a+1] == '"'){
			sentenceSinComilla.replace(a, 1, "");
		}
	}
	sentenceSinComillaDoble = sentenceSinComilla;
	cout<<sentenceSinComillaDoble<<endl;

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

void TestV2::calcularPrediccion(){

	istringstream frase (this->sentenceSinComillas);
	int cantidadDePalabras = 0;

	string word;
	while (frase >> word){
		cantidadDePalabras++;
	}

	string trigramas[cantidadDePalabras-2];
	string bigramas[cantidadDePalabras-1];
	string unigramas[cantidadDePalabras];

	double triProb[cantidadDePalabras-2];
	double biProb[cantidadDePalabras-1];

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
		unigramas[i] = word;
		if (tri_flag < 3){
			tri_aux += word;
			if (tri_flag < 2) tri_aux += " ";
			tri_flag++;
		} else{
			trigramas[tri_pos] = tri_aux;
			tri_pos++;
			tri_flag = 1;
			tri_aux = word;
			tri_aux += " ";
		}
		if (bi_flag < 2){
			bi_aux += word;
			if (bi_flag < 2) tri_aux += " ";
			bi_flag++;
		} else{
			bigramas[bi_pos] = bi_aux;
			bi_pos++;
			bi_flag = 1;
			bi_aux = word;
			bi_aux += " ";
		}
	}


	for(int i=0; i<cantidadDePalabras-2; i++){
		triProb[i] = this->calcularProbabilidad(bigramas[i], unigramas[i+2]);
	}

	size_t tri_minProb = std::numeric_limits<double>::max();
	size_t tri_minProb_pos = 0;


	// BUSCO CUAL ES EL TRIGRAMA DE MENOR PROBABILIDAD
	for(int i=0; i<cantidadDePalabras-2; i++){
		if (triProb[i] < tri_minProb){
			tri_minProb_pos = i;
			tri_minProb = triProb[i];
		} else if (triProb[i] == tri_minProb){
			biProb[i] = this->calcularProbabilidad(unigramas[i], unigramas[i+1]);
			biProb[i+1] = this->calcularProbabilidad(unigramas[i+1], unigramas[i+2]);

			double menor;
			if (biProb[i] <= biProb[i+1]) menor = biProb[i];
			else menor = biProb[i+1];
		}
	}

	double bi_minProb = std::numeric_limits<double>::max();
	int bi_minProb_pos = 0;

	// BUSCO CUAL ES EL BIGRAMA DE MENOR FRECUENCIA
	if (biProb[tri_minProb_pos] == 0){
		biProb[tri_minProb_pos] = this->calcularProbabilidad(unigramas[tri_minProb_pos], unigramas[tri_minProb_pos+1]);
		biProb[tri_minProb_pos+1] = this->calcularProbabilidad(unigramas[tri_minProb_pos+1], unigramas[tri_minProb_pos+2]);
	}
	if (biProb[tri_minProb_pos] <= biProb[tri_minProb_pos+1]){
		bi_minProb = biProb[tri_minProb_pos];
		bi_minProb_pos = tri_minProb_pos;
	} else{
		bi_minProb = biProb[tri_minProb_pos+1];
		bi_minProb_pos = tri_minProb_pos+1;
	}


	// BUSCO CUAL ES BIGRAMA CON MAYOR PROBABILIDAD COMPUESTO POR:
	// 1ERA PALABRA DEL BIGRAMAS[bi_minFrec_pos] + ALGUNA OTRA

	string palabraPropuesta;
	palabraPropuesta = this->getTerminoMasProbable(bigramas[bi_minProb_pos]);

	//
	//FALTA EL CASO EN QUE NO ENCUENTRE EL TERMINO CON ESE CONTEXTO!!
	//

	// ARMO LA SENTENCE PREDICHA
	word = ""; // limpio contenido de word
	frase.str(this->sentenceSinComillas); // vuelvo a llenar el istringstream
	string frasePropuesta = "";

	for(int i=0; i<bi_minProb_pos+1; i++){
		frase >> word;
		frasePropuesta += word;
		frasePropuesta += " ";
	}
	frasePropuesta += palabraPropuesta;

	for(int i=bi_minProb_pos+1; i<cantidadDePalabras; i++){
		frasePropuesta += " ";
		frase >> word;
		frasePropuesta += word;
	}

	this->sentencePredicha = frasePropuesta;

}


}	/* namespace std */
