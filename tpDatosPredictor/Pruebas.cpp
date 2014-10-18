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
	string oracion ="This is a very beautiful day . This is a very big house . The elephant is very big . The house is small . The dog is black . The car is very big and red .";
	//string oracion = "This is a very beautiful day .";

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
		//cout << ngrama5.getListaNgrama()[i] << endl;
	}
}

void pruebaStreamANgrama(){
	FILE* fp;
	fp = fopen("file.txt", "w+");

	const char* oracion = "This is a very beautiful day. This is a very big house. The elephant is very big. The house is small. The dog is black. The car is very big and red.";
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
	}
	cout<<endl;

	cout<<"FIN DE PRUEBAS."<<endl;
	cout<<endl;
	return 0;


}
