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
	this->id = -1;
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

TestV2::TestV2(string archivoPruebas) {
	this->id = -1;
	this->sentence = "";
	this->sentencePredicha = "";
	this->eof = false;
	this->parser = Parser();
	this->parser.abrirArchivo(archivoPruebas);

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
	int cambiadas = 0;
	int sinCambiar = 0;
	ofstream cambios;
	cambios.open("frasesCambiadas.txt");

	this->readNextSentence();
	while (!this->eof){
		if  (this->eof == true) break;
		int valor;
		valor = this->calcularPrediccion();
		if (valor==1){
			cambiadas++;
			cambios << this->id << ": " << this->sentencePredicha << endl;
		} else{
			sinCambiar++;
		}
		this->guardarSentencePredicha();
		this->readNextSentence();
	}
	cambios.close();
	this->cerrarArchivoResultados();
	this->cerrarArchivo();
	cout << "Frases sin cambiar: "<< sinCambiar << endl;
	cout << "Cambiadas: " << cambiadas << endl;
	cout << "Total: " << cambiadas+sinCambiar << endl;

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
			} else{
				size_t pos = unContextoPosterior.find(" ");
				if (pos != string::npos){
					unContextoPosterior.substr(0, pos);
					if (unContextoPosterior != ""){
								it_buscador2 = this->ngramas.contextos[(*it).first].find(unContextoPosterior);
								if (it_buscador2 != this->ngramas.contextos[(*it).first].end()){
									frecRegresivaProgresiva += 0.4*(*it_buscador2).second;
								}
					}
				}
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
	if (std::atoi(id.c_str()) == this->id){
		this->eof = true;
		return;
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
	bool flag_buscarEnContextoAnterior = false;
	bool flag_buscarSinContexto = false;

	it_buscadorContexto = this->ngramas.contextos.find(unContexto);
	if ( it_buscadorContexto != this->ngramas.contextos.end() ){
		// encontro el contexto
		it_buscadorTermino = this->ngramas.contextos[unContexto].find(unTermino);
		if ( it_buscadorTermino != this->ngramas.contextos[unContexto].end() ){
			// encontro contexto y el termino
			num = (*it_buscadorTermino).second;
			den = this->ngramas.contextos[unContexto][TOTAL_FRECUENCIAS];
		} else{
			//encontro contexto pero no el termino
			flag_buscarEnContextoAnterior = true;
		}
	} else{
		// no encontro el contexto
		flag_buscarEnContextoAnterior = true;
	}

	if ( flag_buscarEnContextoAnterior ){
			// no encontro el contexto o encontro contexto pero no termino
			size_t pos = unContexto.find(" ");
			if (pos != string::npos){
				string contextoAnterior = unContexto.substr(unContexto.find(" ")+1);
				it_buscadorContexto = this->ngramas.contextos.find(contextoAnterior);
				if (it_buscadorContexto != this->ngramas.contextos.end()){
					// encontro contextoAnterior
					it_buscadorTermino = this->ngramas.contextos[contextoAnterior].find(unTermino);
					if ( it_buscadorTermino != this->ngramas.contextos[contextoAnterior].end() ){
						// encontro contextoAnterior y termino
						num = 0.4*(*it_buscadorTermino).second;
						den = this->ngramas.contextos[contextoAnterior][TOTAL_FRECUENCIAS];
					} else{
						// encontro contextoAnterior pero no el termino
						flag_buscarSinContexto = true;
					}
				} else{
					// no encontro contextoAnterior
					flag_buscarSinContexto = true;
				}
			} else{
				// no hay mas palabras para achicar el contexto
				flag_buscarSinContexto = true;
			}
	}

	if ( flag_buscarSinContexto ){
		// o no encontro contextoAnterior
		// o encontro contextoAnterior pero no termino
		// o no hay mas palabras para achicar el contexto
		it_buscadorTermino = this->ngramas.contextos[""].find(unTermino);
		if ( it_buscadorTermino != this->ngramas.contextos[""].end() ){
			// encontro el termino sin contexto
			num = this->ngramas.contextos[""][unTermino];
			den = this->ngramas.contextos[""][TOTAL_FRECUENCIAS];
		} else{
			// no encontro el termino
			return 0; //en esta caso no existe el termino en nuestro diccionario: CAGAMOS!
		}
	}

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

	vector<double> triProb = vector<double>();     // sobrarian 2 posiciones que se ocupan pero contienen basura
	vector<double> biProb = vector<double>(cantidadDePalabras-1);      // sobraria 1 posicion que se ocupa pero contienen basura
//	cout << "Creados los vectores"<< endl;

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
//	cout << "Llenados los vectores"<< endl;
	for(int i=0; i<cantidadDePalabras-2; i++){
		triProb.push_back(this->calcularProbabilidad_trigrama(unigramas.at(i), unigramas.at(i+1), unigramas.at(i+2)));
	}
//	cout << "Calculadas las probabilidades de tri"<< endl;

	double tri_minProb = std::numeric_limits<double>::max();
	// BUSCO CUAL ES EL TRIGRAMA DE MENOR PROBABILIDAD --------------------------------------------

	// busco cual es la menor probabilidad
	for(int i=0; i<cantidadDePalabras-2; i++){
		if ( (triProb.at(i) < tri_minProb) && (triProb.at(i)!=0) ){
			tri_minProb = triProb.at(i);
		}
	}

	if (tri_minProb == std::numeric_limits<double>::max()){
	        this->sentencePredicha = this->sentenceSinComillas;
	        return 0;
	    }
	// agrego en un vector la posicion de todos los trigramas de probabilidad tri_minProb
	vector<int> tri_minProb_pos = vector<int>();
	for(int i=0; i<cantidadDePalabras-2; i++){
		if (triProb.at(i) == tri_minProb){
			tri_minProb_pos.push_back(i);
		}
	}
/*	// los trigramas de peor probab son:
	for (vector<int>::iterator it = tri_minProb_pos.begin() ; it != tri_minProb_pos.end(); ++it){
		cout << "<" << trigramas.at((*it)) << ">" << " con probab " << triProb.at((*it));
	}
*/
	// a los trigramas selectos, les agrego una palabra y guardo la probabilidad de dicho trigramaConInsercion en un vector
	vector<double> probab_trigramasPropuestos = vector<double>();
	vector<string> palabrasPropuestas = vector<string>();
	int numeroDeIteracion = 0;
	for (vector<int>::iterator it = tri_minProb_pos.begin() ; it != tri_minProb_pos.end(); ++it){
		int bi_minProb_pos = 0;

		// BUSCO CUAL ES EL BIGRAMA DE MENOR PROBABILIDAD
		if (biProb[(*it)] == 0){
			biProb[(*it)] = this->calcularProbabilidad_bigrama(unigramas[(*it)], unigramas[(*it)+1]);;
			if (cantidadDePalabras>2){
				biProb[(*it)+1] = this->calcularProbabilidad_bigrama(unigramas[(*it)+1], unigramas[(*it)+2]);;
			}
		}
		if ( cantidadDePalabras>2 && biProb[(*it)] >= biProb[(*it)+1] ){
			bi_minProb_pos = (*it)+1;
		} else{
			bi_minProb_pos = (*it);
		}
		// peor bigrama encontrado

		// BUSCO CUAL ES BIGRAMA CON MAYOR PROBABILIDAD COMPUESTO POR:
		// 1ERA PALABRA DEL BIGRAMAS[bi_minProb_pos] + ALGUNA OTRA

		if (bi_minProb_pos>0){
			// quiere decir que no estamos al comienzo de la frase, hay palabras antes que bi_minProb_pos
			if (bi_minProb_pos<cantidadDePalabras-2){
				// podemos tomar 2 palabras posteriores
				palabrasPropuestas.push_back( this->getTerminoMasProbable(bigramas.at(bi_minProb_pos-1), bigramas.at(bi_minProb_pos+1)) );
			} else{
				// solo podemos tomar 1 palabra posterior
				palabrasPropuestas.push_back( this->getTerminoMasProbable(bigramas.at(bi_minProb_pos-1), unigramas.at(bi_minProb_pos+1)) );
			}
		} else{
			if (bi_minProb_pos<cantidadDePalabras-2){
				// podemos tomar 2 palabras posteriores
				palabrasPropuestas.push_back( this->getTerminoMasProbable(unigramas.at(bi_minProb_pos), bigramas.at(bi_minProb_pos+1)) );
			} else{
				// solo podemos tomar 1 palabra posterior
				palabrasPropuestas.push_back( this->getTerminoMasProbable(unigramas.at(bi_minProb_pos), unigramas.at(bi_minProb_pos+1)) );
			}
		}
		// calculo probabilidad de tri
		if ( bi_minProb_pos == (*it) ){
			probab_trigramasPropuestos.push_back( this->calcularProbabilidad_trigrama(unigramas[(*it)], palabrasPropuestas.at(numeroDeIteracion), unigramas[(*it)+1]) );
		} else{
			probab_trigramasPropuestos.push_back( this->calcularProbabilidad_trigrama(unigramas[(*it)], unigramas[(*it)+1], palabrasPropuestas.at(numeroDeIteracion)) );
		}
		numeroDeIteracion++;
	} // ya calculadas las probab de los trigramas propuestos

	int tri_minProbUnica_pos = 0;
	int palabraPropuesta_pos = 0;
	// me quedo con la probabilidad mas baja de los trigramas propuestos
	numeroDeIteracion = 0;
	double triPropuesto_minProb = std::numeric_limits<double>::max();
	for(vector<int>::iterator it = tri_minProb_pos.begin() ; it != tri_minProb_pos.end(); ++it){
		if (probab_trigramasPropuestos.at(numeroDeIteracion) < triPropuesto_minProb){
			triPropuesto_minProb = probab_trigramasPropuestos.at(numeroDeIteracion);
			tri_minProbUnica_pos = (*it);
			palabraPropuesta_pos = numeroDeIteracion;
		}
		numeroDeIteracion++;
	}

	// YA DEFINIDO EL DESEMPATE DE PEOR TRIGRAMA -------------------------------------------------------




//	cout <<endl<<"El trigrama de menor probabilidad es <"<< trigramas.at(tri_minProbUnica_pos)<<"> con probab "<<triProb.at(tri_minProbUnica_pos)<<endl;

	int bi_minProb_pos = 0;

	// BUSCO CUAL ES EL BIGRAMA DE MENOR PROBABILIDAD
	if (biProb[tri_minProbUnica_pos] == 0){
		biProb[tri_minProbUnica_pos] = this->calcularProbabilidad_bigrama(unigramas[tri_minProbUnica_pos], unigramas[tri_minProbUnica_pos+1]);;
		if (cantidadDePalabras>2){
			biProb[tri_minProbUnica_pos+1] = this->calcularProbabilidad_bigrama(unigramas[tri_minProbUnica_pos+1], unigramas[tri_minProbUnica_pos+2]);;
		}
	}
	if ( cantidadDePalabras>2 && biProb[tri_minProbUnica_pos] >= biProb[tri_minProbUnica_pos+1] ){
		bi_minProb_pos = tri_minProbUnica_pos+1;
	} else{
		bi_minProb_pos = tri_minProbUnica_pos;
	}
	//cout << "El bigrama de menor probab es: "<< bigramas.at(bi_minProb_pos)<<endl;

	string palabraPropuesta;
	palabraPropuesta = palabrasPropuestas.at(palabraPropuesta_pos);

	// Evaluo si el trigrama con la palabra propuesta es mas probable que el trigrama sin insercion
	double prob_trigramaPropuesto;
	if ( bi_minProb_pos == tri_minProbUnica_pos ){
		prob_trigramaPropuesto = this->calcularProbabilidad_trigrama(unigramas[tri_minProbUnica_pos], palabraPropuesta, unigramas[tri_minProbUnica_pos+1]);
//		cout << "Propongo <"<<unigramas[tri_minProbUnica_pos]<<" "<<palabraPropuesta<<" "<<unigramas[tri_minProbUnica_pos+1]<<"> con probab "<<prob_trigramaPropuesto<<endl;
	} else{
		prob_trigramaPropuesto = this->calcularProbabilidad_trigrama(unigramas[tri_minProbUnica_pos], unigramas[tri_minProbUnica_pos+1], palabraPropuesta);
//		cout << "Propongo <"<<unigramas[tri_minProbUnica_pos]<<" "<<unigramas[tri_minProbUnica_pos+1]<<" "<<palabraPropuesta<<"> con probab "<<prob_trigramaPropuesto<<endl;
	}

	// Si el trigramaPropuesto no es mas probable, no inserto nada y devuelvo misma frase

	if (prob_trigramaPropuesto - tri_minProb < UMBRAL){
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
