/*
 * Pruebas.cpp
 *
 *  Created on: 13/10/2014
 *      Author: juanignacio
 */

#include "parser/ArbolB.h"
#include "parser/Nodo.h"
#include "NGrama/NGrama.h"
#include "parser/Parser.h"
#include "manejoArchivo/manejoArchivo.h"
#include "modelo/TestV2.h"

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <utility>
#include <algorithm>    // std::stable_sort

using namespace std;

void pruebaArbol() {

	abb::ArbolB<Nodo,40> *lexico = new abb::ArbolB<Nodo, 40>;
	Nodo aux;
	aux.setTermino("prueba");

	if (!lexico->buscar(aux)) cout<<"OK"<<endl;
	lexico->insertar(aux);
	if (lexico->buscar(aux)) cout<<"OK"<<endl;

	cout<<"Fin de pruebas Arbol."<<endl;
}

void pruebaNgrama(){
	//string oracion ="This is a very beautiful day . This is a very big house . The elephant is very big . The house is small . The dog is black . The car is very big and red .";
	string oracion = "This is a very beautiful day .";

	//oracion.max long ngrama y separador.
	NGrama ngrama5 =  NGrama(oracion, 5,",");
	ngrama5.stringA5Grama();

	vector<pair<string,int> > listaNgrama;
	listaNgrama = ngrama5.getListaNgrama();
    //std::stable_sort(listaNgrama.begin(), listaNgrama.end());//,compare_first_only());
    std::cout << std::endl << "Sorted:" << std::endl;

    cout <<"Cantidad elementos: "<< listaNgrama.size()<< endl;
	for(int i=0; i < listaNgrama.size(); ++i){
		cout << listaNgrama.at(i).first<< "," <<listaNgrama.at(i).second << endl;
	}
}

void pruebaStreamANgrama(){
	FILE* fp;
	fp = fopen("file.txt", "w+");

	const char* oracion = "This is a very beautiful day . This is a very big house . The elephant is very big . The house is small . The dog is black . The car is very big and red .";

	fputs(oracion, fp);
	rewind(fp);

	long int length;
	fseek(fp, 0, SEEK_END);
	length = ftell(fp);
	rewind(fp);

	void* str = calloc(length + 1, 1);
	fread(str, 1, length, fp);
	rewind(fp);
	printf("%s", str);

	cout<<endl<<"ARCHIVO LISTO"<<endl;

	NGrama ngrama5 =  NGrama(5,",");
	ngrama5.streamANgrama(fp);

	for(int i=1; i<=5; i++){
	cout<<"La frecuencia total de Gramas de tamanio "<<i<<" es: "<<ngrama5.getFrecuenciaDeNgrama(i)<<endl;
	}

	vector<pair<string,int> > listaNgrama;
	listaNgrama = ngrama5.getListaNgrama();
    std::stable_sort(listaNgrama.begin(), listaNgrama.end());
    std::cout << std::endl << "Sorted:" << std::endl;

	for(std::size_t i=0; i < ngrama5.getListaNgrama().size();++i){
		cout << listaNgrama[i].first  << "," << listaNgrama[i].second << endl;
	}

	fclose(fp);
	remove("file.txt");
	cout<<"FIN"<<endl;
}

void pruebaParser(){
	Parser unParser;
	unParser.abrirArchivo("train_v2.txt");

	for (int i = 0; i < 100; i ++){
		cout<<unParser.getSiguienteTermino()<<endl;
	}
	unParser.cerrarArchivo();
}

void pruebaParser2(){

	/*
	 * esta prueba devuelve los primeros 10 renglones del set de entrenamiento.
	 * Para tener una idea de como esta formado el archivo de 4gb!!
	 */

	Parser unParser;
	unParser.abrirArchivo("train_v2.txt");

	for (int i = 0; i < 10; i++){
		cout<<unParser.getLinea()<<endl;
	}
	unParser.cerrarArchivo();
}

void pruebaParser3(){

	/*
	 en esta prueba vamos a chequear el tamaño maximo que puede llegar a tener
	 un string.
	 */

	Parser unParser;
	unParser.abrirArchivo("train_v2.txt");
	string texto = "";

	for (int i = 0; i < 999999; i++){
		texto += unParser.getLinea();
	}

	cout<<texto<<endl;

	unParser.cerrarArchivo();
}

void pruebaGuardarNgramasEnArchivo(){

	const char* oracion = "This is a very beautiful day . This is a very big house . The elephant is very big . The house is small . The dog is black . The car is very big and red .";
	abb::ArbolB<Nodo,40> *lexico = new abb::ArbolB<Nodo, 40>;

	FILE* fp;
	fp = fopen("file.txt", "w+");
	fputs(oracion, fp);
	rewind(fp);

	long int length;
	fseek(fp, 0, SEEK_END);
	length = ftell(fp);
	rewind(fp);

	void* str = calloc(length + 1, 1);
	fread(str, 1, length, fp);
	rewind(fp);
	printf("%s", str);
	cout<<endl;

	NGrama ngrama5 =  NGrama(5," ");
	ngrama5.streamANgrama(fp);

	vector<pair<string,int> > listaNgrama;
	listaNgrama = ngrama5.getListaNgrama();
    std::stable_sort(listaNgrama.begin(), listaNgrama.end());

	for(std::size_t i=0; i < ngrama5.getListaNgrama().size();++i){
		//cout << listaNgrama[i].first  << "," << listaNgrama[i].second << endl;
	}

	fclose(fp);
	remove("file.txt");

	ManejoArchivo manejoArchivo = ManejoArchivo("ngramas.txt");
	manejoArchivo.armarArchivoNgramas(listaNgrama, lexico);
	manejoArchivo.cerrarArchivo();

	cout<<"<termino, offset>"<<endl;
	lexico->emitir();

	delete []lexico;
	cout<<endl;
	cout<<endl;
	cout<<">>Se ha creado un archivo con todos los ngramas correspondientes."<<endl;
}

void pruebaGetRegistroDeArchivo(){

		const char* oracion = "This is a very beautiful day . This is a very big house . The elephant is very big . The house is small . The dog is black . The car is very big and red .";
		abb::ArbolB<Nodo,40> *lexico = new abb::ArbolB<Nodo, 40>;

		FILE* fp;
		fp = fopen("file.txt", "w+");
		fputs(oracion, fp);
		rewind(fp);

		long int length;
		fseek(fp, 0, SEEK_END);
		length = ftell(fp);
		rewind(fp);

		void* str = calloc(length + 1, 1);
		fread(str, 1, length, fp);
		rewind(fp);
		printf("%s", str);
		cout<<endl;

		NGrama ngrama5 =  NGrama(5," ");
		ngrama5.streamANgrama(fp);

		vector<pair<string,int> > listaNgrama;
		listaNgrama = ngrama5.getListaNgrama();
	    std::stable_sort(listaNgrama.begin(), listaNgrama.end());

	    fclose(fp);
	    remove("file.txt");

	    ManejoArchivo manejoArchivo = ManejoArchivo("ngramas.txt");
	    manejoArchivo.armarArchivoNgramas(listaNgrama, lexico);
	    manejoArchivo.cerrarArchivo();

	    cout<<"<termino, offset>"<<endl;
	    lexico->emitir();

	   manejoArchivo = ManejoArchivo("ngramas.txt", "r");

	    Registro unRegistro;
	    unRegistro = manejoArchivo.getRegistro(657);

	    cout<<endl;
	    cout<<"Contexto: "<<unRegistro.getContexto()<<endl;
	    cout<<"Termino: "<<unRegistro.getTermino()<<endl;
	    cout<<"Frecuencia: "<<unRegistro.getFrecuencia()<<endl;

	    unRegistro = manejoArchivo.getSiguienteRegistro();

	    cout<<endl;
	    cout<<"Contexto: "<<unRegistro.getContexto()<<endl;
	    cout<<"Termino: "<<unRegistro.getTermino()<<endl;
	    cout<<"Frecuencia: "<<unRegistro.getFrecuencia()<<endl;

	    unRegistro = manejoArchivo.getSiguienteRegistro();

	    cout<<endl;
	    cout<<"Contexto: "<<unRegistro.getContexto()<<endl;
	    cout<<"Termino: "<<unRegistro.getTermino()<<endl;
	    cout<<"Frecuencia: "<<unRegistro.getFrecuencia()<<endl;

	    manejoArchivo.cerrarArchivo();

}


void pruebaObtenerSentenceTestV2(){
	Parser unParser;
	unParser.abrirArchivo("test_v2.txt");
	//vector<TestV2 > listaTestV2;
	TestV2 testV2 = TestV2();

	for (int i = 0; i < 2; i ++){

		string oracionAux =  unParser.getLinea();
		//para que no procese "id","sentence" (son los nombres de las columnas).
		if(oracionAux.find("sentence") == std::string::npos){
			string oracion = oracionAux.erase(oracionAux.find_last_not_of(" \n\r\t")+1);
			//cout<<oracion<<endl;
			std::size_t pos = oracion.find(",");
			string id = oracion.substr(0,pos);
			string sentence = oracion.substr(pos+1);
			//cout<<sentence.find('"')<<endl;
			string sentenceSinComilla = sentence.substr(1,sentence.rfind('"')-1);
			testV2.setId(std::atoi(id.c_str()));
			testV2.setSentente(sentence);

			//oracion.max long ngrama y separador.
			NGrama ngrama5 =  NGrama(sentenceSinComilla, 5,",");
			ngrama5.stringA5Grama();
			testV2.setListaNgrama(ngrama5.getListaNgrama());
			//cout<<sentenceSinComilla<<endl;
			//cout<<testV2.getId()<<"-"<<testV2.getSentente()<<endl;
		}

	}
	unParser.cerrarArchivo();
	for(std::size_t i=0; i < testV2.getListaNgrama().size();++i){
		cout << testV2.getListaNgrama()[i].first  << "," << testV2.getListaNgrama()[i].second << endl;
	}
}

int main(int argc, char *argv[]){

//Aca voy habilitando las pruebas que quiera correr
	int i=0;
	char j;
	cout<<"ELEGIR NUMERO DE PRUEBA: "<<endl;
	cout<<"1- testPruebaArbol"<<endl;
	cout<<"2- testPruebaNgrama"<<endl;
	cout<<"3- testPruebaParser"<<endl;
	cout<<"4- testPruebaParser2"<<endl;
	cout<<"5- testPrueba stream"<<endl;
	cout<<"6- testPruebaParser3"<<endl;
	cout<<"7- testPruebaObtenerSentence"<<endl;
	cout<<"8- testArmarArchivoNgramas"<<endl;
	cout<<"9- testGetRegistroDeArchivo"<<endl;
	cin>>i;
	switch (i){
		case 1: pruebaArbol();
				break;
		case 2: pruebaNgrama();
				break;
		case 3: pruebaParser();
				break;
		case 4: pruebaParser2();
				break;
		case 5: pruebaStreamANgrama();
				break;
		case 6: cout<<"ADVERTENCIA: Esta prueba puede tardar varios minutos."<<endl;
				cout<<"Continuar de todas formas? [Y/N]"<<endl;
				cin>>j;
				switch(j){
					case 'Y': 	pruebaParser3();
								break;
					case 'y': 	pruebaParser3();
								break;
					case 'N': 	break;
					case 'n': 	break;
				}
				break;
		case 7: pruebaObtenerSentenceTestV2();
		break;
		case 8: pruebaGuardarNgramasEnArchivo();
		break;
		case 9: pruebaGetRegistroDeArchivo();
		break;

	}

	cout<<endl;

	cout<<"FIN DE PRUEBAS."<<endl;
	cout<<endl;
	return 0;


}
