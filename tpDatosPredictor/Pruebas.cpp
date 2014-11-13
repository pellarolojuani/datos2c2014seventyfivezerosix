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
#include "BIS/NGramas.h"

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <string>
#include <map>
//#include <tr1/unordered_map.h>
#include <vector>
#include <utility>
#include <algorithm>    // std::stable_sort
#include "util/Timer.h"
#include <time.h>
#include <fstream>

using namespace std;

void pruebaArbol() {

	abb::ArbolB<Nodo,40> *lexico = new abb::ArbolB<Nodo, 40>;
	Nodo aux;
	aux.setTermino("prueba");

	if (!lexico->buscar(aux)) cout<<"OK"<<endl;
	lexico->insertar(aux);
	if (lexico->buscar(aux)) cout<<"OK"<<endl;
	cout<<"Fin de pruebas Arbol."<<endl;

	delete []lexico;

	abb::ArbolB<Registro,40> *otroArbol = new abb::ArbolB<Registro,40>;
	Registro unRegistro = Registro();
	Registro otroRegistro = Registro();
	Registro resultado;
	Registro auxiliar = Registro();

	auxiliar.setTermino("Datos");

	unRegistro.setTermino("Datos");
	unRegistro.setFrecuencia(2);

	otroRegistro.setTermino("Prueba");
	otroRegistro.setFrecuencia(5);

	otroArbol->insertar(unRegistro);
	otroArbol->insertar(otroRegistro);
	otroArbol->aumentarFrecuencia(unRegistro, 1);
	otroArbol->emitirRegistros();

	delete []otroArbol;
}

void pruebaNgrama(){
	//string oracion ="This is a very beautiful day . This is a very big house . The elephant is very big . The house is small . The dog is black . The car is very big and red .";
	string oracion = "This is a very beautiful day .";

	//oracion.max long ngrama y separador.
	NGrama ngrama5 =  NGrama(oracion, 5,",");
	//ngrama5.stringA5Grama();

	vector<pair<string,int> > listaNgrama;
	listaNgrama = ngrama5.getListaNgrama();
    //std::stable_sort(listaNgrama.begin(), listaNgrama.end());//,compare_first_only());
    std::cout << std::endl << "Sorted:" << std::endl;

    cout <<"Cantidad elementos: "<< listaNgrama.size()<< endl;
	for(int i=0; i < listaNgrama.size(); ++i){
		cout << listaNgrama.at(i).first<< "," <<listaNgrama.at(i).second << endl;
	}
}

void pruebaNgramaMax(){
	//string oracion ="This is a very beautiful day . This is a very big house . The elephant is very big . The house is small . The dog is black . The car is very big and red .";
	string oracion = "This is a very beautiful day . ";

	//oracion.max long ngrama y separador.
	NGrama ngrama5 =  NGrama(oracion, 5,",");
	ngrama5.stringANGramaMax();

	vector<pair<string,int> > listaNgrama;
	listaNgrama = ngrama5.getListaNgrama();
    //std::stable_sort(listaNgrama.begin(), listaNgrama.end());//,compare_first_only());
    std::cout << std::endl << "Sorted:" << std::endl;

	for(std::size_t i=0; i < listaNgrama.size(); ++i){
		cout << listaNgrama.at(i).first<< "," <<listaNgrama.at(i).second << endl;
    cout <<"Cantidad elementos: "<< listaNgrama.size()<< endl;
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

	for (int i = 0; i < 100000; i++){
		texto += unParser.getLinea();
	}

	cout<<texto<<endl;

	unParser.cerrarArchivo();
}

void pruebaTextoARegistro(){
	Registro unRegistro = Registro();
	string unTexto = "Hola como te va";
	unRegistro.stringARegistro(unTexto);

	cout<<"Contexto: "<<unRegistro.getContexto()<<endl;
	cout<<"Termino: "<<unRegistro.getTermino()<<endl;
	cout<<"Frecuencia: "<<unRegistro.getFrecuencia()<<endl;
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
	long posicion = 0;

	for (int i = 0; i < 3; i ++){

		posicion = unParser.getPosicionActualArchivo();
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
			testV2.setSentence(sentence);

			cout<<"---"<<endl;
			cout<<"ID: "<<testV2.getId()<<endl;
			cout<<"SENTENCE: "<<testV2.getSentence()<<endl;
			cout<<"---"<<endl<<endl;

			//oracion.max long ngrama y separador.
			//NGrama ngrama5 =  NGrama(sentenceSinComilla, 5,",");
			//ngrama5.stringA5Grama();
			//testV2.setListaNgrama(ngrama5.getListaNgrama());
			//cout<<sentenceSinComilla<<endl;
			//cout<<testV2.getId()<<"-"<<testV2.getSentente()<<endl;
		}

	}

	for(std::size_t i=0; i < testV2.getListaNgrama().size();++i){
		cout << testV2.getListaNgrama()[i].first  << "," << testV2.getListaNgrama()[i].second << endl;
	}
	//si siguiera leyendo, esta es la linea que sigue.
	cout << "antes de posicionamineto estoy en = " << unParser.getLinea() << endl;
	//aca me posiciono en la ultima linea que lei en el for.
	unParser.setPosicionArchivo(posicion);
	cout << "se posiciona en la ultima pos leida del archivo posicionamiento = " << unParser.getLinea() << endl;
	unParser.cerrarArchivo();
}

void pruebaNgramaGenerico(){
	//string oracion ="This is a very beautiful day . This is a very big house . The elephant is very big . The house is small . The dog is black . The car is very big and red .";
	string oracion = "This is a very beautiful day .";

	//oracion.max long ngrama y separador.
	NGrama ngrama5 =  NGrama(oracion, 5,",");
	ngrama5.stringANgrama();

	vector<pair<string,int> > listaNgrama;
	listaNgrama = ngrama5.getListaNgrama();
    //std::stable_sort(listaNgrama.begin(), listaNgrama.end());//,compare_first_only());
    std::cout << std::endl << "Sorted:" << std::endl;

    cout <<"Cantidad elementos: "<< listaNgrama.size()<< endl;
	for(int i=0; i < listaNgrama.size(); ++i){
		cout << listaNgrama.at(i).first<< "," <<listaNgrama.at(i).second << endl;
	}
}

void pruebaCorrerSetDeEntrenamiento(){
	Parser unParser = Parser();
	unParser.abrirArchivo("train_v2.txt");
	long int offset;
	
	offset = unParser.setDeEntrenamiento();
}

void pruebaMerge(){

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

	ManejoArchivo manejoArchivo = ManejoArchivo("file1.txt");
	manejoArchivo.armarArchivoNgramas(listaNgrama, lexico);
	manejoArchivo.cerrarArchivo();

	cout<<"<termino, offset>"<<endl;
	lexico->emitir();

	delete []lexico;
	cout<<endl;
	cout<<endl;
	cout<<">>Se ha creado UN archivo con todos los ngramas correspondientes."<<endl;

	FILE *fp1, *fp2;

	fp1 = fopen("file1.txt", "r");
	fp2 = fopen("file2.txt", "w+");
	char ch;
	while ( ( ch = fgetc(fp1) ) != EOF ){
		fputc(ch, fp2);
	}
    fclose(fp1);
    fclose(fp2);
    cout<<">>Se ha creado OTRO archivo con todos los ngramas correspondientes."<<endl;

    merge(2);
    cout<<"Termino el proceso de MERGE"<<endl;
}



void pruebaNgramaSoloConMap(){

	string oracion ="This is a very beautiful day . This is a very big house . The elephant is very big . The house is small . The dog is black . The car is very big and red .";

	map<string, int>::const_iterator itr;
	NGrama ngrama5 =  NGrama(oracion, 5,",");
	ngrama5.stringANGramaAlmacenadoEnMap();

	map<string,int> mapNgrama;
	mapNgrama = ngrama5.getMapDePosiciones();

	for(itr = mapNgrama.begin(); itr != mapNgrama.end(); ++itr){
			cout << (*itr).first << "," << (*itr).second <<endl;

		}
}

void pruebaSetEntrenamientoConMap(){

	 char cadena[128];
	 char * buffer = new char [GIGA];
	 ofstream fichero("ngrama.txt");
	map<string, int>::const_iterator itr;

	 ifstream leer_fich ("train_v2.txt");
	// leer_fich.getline(cadena,128);
	 leer_fich.read(buffer,GIGA);
	 leer_fich.close();
	cout<< "Termino de leer el archivo" <<endl;
	NGrama ngrama5 =  NGrama(buffer, 5,",");
	cout<< "Comienza Armado Ngrama" <<endl;
	 ngrama5.stringANGramaAlmacenadoEnMapSinListaTerminos();

	 map<string,int> mapNgrama;
	 mapNgrama = ngrama5.getMapDePosiciones();
	 cout<< "Finaliza Armado Ngrama" <<endl;
	 cout<< "Comienza copiado de mensaje" <<endl;
	 for(itr = mapNgrama.begin(); itr != mapNgrama.end(); ++itr){
		 string ngrama = (*itr).first.c_str();
		 ngrama = ngrama + ",";
		 stringstream ss;
		 ss << (*itr).second;
		 ngrama = ngrama + ss.str();

		 //cout<< ngrama << endl;
		 fichero << ngrama << endl;
		// cout << (*itr).first << "," << (*itr).second <<endl;
	 }
	 cout<< "finaliza copiado de mensaje" <<endl;
	 fichero.close();
	 delete[] buffer;
}


void nuevaPruebaStreamANgrama(){
	NGramas nGramas = NGramas(3, " ");
	FILE *pruebas = fopen("train_v2.txt", "r");
	FILE *fp_ngramas = fopen("ngramas.txt", "w+");
	Timer t = Timer();
	t.start();
	cout<<"Comenzó a leer - "<< t.getTime()<<endl;
	fseek(pruebas, 262144002, SEEK_SET);
	cout<<"Terminó de leer - "<< t.getTime()<<endl;
	cout<<"Comenzó a armar ngrama - "<< t.getTime()<<endl;
	nGramas.streamANgrama(pruebas);
	cout<<"Terminó de armar ngrama - "<< t.getTime()<<endl;
	cout<<"Guardando en disco.."<< t.getTime() << endl;
	nGramas.getLexico()->guardarEnArchivo(fp_ngramas);
	cout<<"Fin guardar en disco.."<< t.getTime() << endl;
	//nGramas.getLexico()->emitirRegistros();
	t.stop();

	fclose(pruebas);
}

void pruebaLeerLoteDePruebas(){

	TestV2 pruebas = TestV2();

	for (int i = 0; i < 10; i++){
		pruebas.readNextSentence();
		cout<<pruebas.getId()<<": "<<pruebas.getSentence()<<endl<<endl;
	}

	pruebas.cerrarArchivo();
}

void pruebaLevantarRegistros(){
	//esta prueba levanta el archivo de registros y guarda los ngramas en un hash

	char *c = new char[2884354560];	//reservamos mas de 2.5gb de memoria!
	delete[] c;

	NGramas nGramas = NGramas(3, " ");
	nGramas.levantarNgramas("file1.txt");
}

void pruebaArmarNgramaEnHash(){

	char * buffer = new char [GIGA];
	int * reserva = new int [6442450944];
	delete[] reserva;

	ifstream leer_fich ("train_v2.txt");
	ofstream fichero("textoLeido.txt");
	 Timer t = Timer();
		 t.start();
	leer_fich.read(buffer,GIGA);
	fichero << buffer ;
	leer_fich.close();

	NGramas nGramas = NGramas(3, " ",buffer);
	nGramas.stringANGramaHashTable();
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
	cout<<"10- testPruebaNgramaMax"<<endl;
	cout<<"11- testSetDeEntrenamiento"<<endl;
	cout<<"12- testPruebaTextoARegistro"<<endl;
	cout<<"13- test MERGE"<<endl;
	cout<<"14- test armar ngramas con map"<<endl;
	cout<<"15- test procesar set entrenamiento con map "<<endl;	
	cout<<"16- nuevaPruebaStreamANgrama"<<endl;
	cout<<"17- Leer lote de pruebas"<<endl;
	cout<<"18- test LevantarRegistros"<<endl;
	cout<<"19- test pruebaArmarNgramaEnHash"<<endl;
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
		case 10: pruebaNgramaMax();
		break;
		case 11: pruebaCorrerSetDeEntrenamiento();
		break;
		case 12: pruebaTextoARegistro();
		break;
		case 13: pruebaMerge();
		break;
		case 14: pruebaNgramaSoloConMap();
		break;
		case 15:pruebaSetEntrenamientoConMap();
		break;
		case 16: nuevaPruebaStreamANgrama();
		break;
		case 17: pruebaLeerLoteDePruebas();
		break;
		case 18: pruebaLevantarRegistros();
		break;
		case 19: pruebaArmarNgramaEnHash();
		break;
	}

	cout<<endl;

	cout<<"FIN DE PRUEBAS."<<endl;
	cout<<endl;
	return 0;


}
