/*
 * NGramas.cpp
 *
 *  Created on: 30/10/2014
 *      Author: juanignacio
 */

#include "NGramas.h"

NGramas::NGramas() {
	this->lexico = new abb::ArbolB<Registro, 60>;
	this->cantGrama = 0;
	separadorNgrama = " ";
	listaTerminos = vector<string>();
	this->registros = tr1::unordered_map<string, size_t>();
	this->terminos_x_contexto = tr1::unordered_map<string, size_t>();
	this->oracion = "";
}

NGramas::NGramas(int cantGrama, string separadorNgrama){
	this->lexico = new abb::ArbolB<Registro, 60>;
	this->cantGrama = cantGrama;
	this->separadorNgrama = separadorNgrama;
	this->listaTerminos = vector<string>();
	this->registros = tr1::unordered_map<string, size_t>();
	this->terminos_x_contexto = tr1::unordered_map<string, size_t>();
	this->oracion = "";
}

NGramas::NGramas(int cantGrama, string separadorNgrama,string oracion){
	this->lexico = new abb::ArbolB<Registro, 60>;
	this->cantGrama = cantGrama;
	this->separadorNgrama = separadorNgrama;
	this->listaTerminos = vector<string>();
	this->registros = tr1::unordered_map<string, size_t>();
	this->terminos_x_contexto = tr1::unordered_map<string, size_t>();
	this->oracion = oracion;
}

NGramas::~NGramas() {
	// TODO Auto-generated destructor stub
}

abb::ArbolB<Registro,60>* NGramas::getLexico(){
	return this->lexico;
}

//--------------------------------------------------------//
//---------Comienzo de funciones auxiliares --------------//
string getSiguienteTermino(FILE* fp){
	string termino = "";
	char c = fgetc(fp);
	if (c == EOF) return "";
	if (c == ' ') c = fgetc(fp);
	while (c > 32 && c != ' '){ //a partir del ascii 33 comienzan los caracteres que necesitamos
		termino += c;
		c = fgetc(fp);
	}
	if (termino == " ") return "";
	return termino;
}

string sacarPrimerTermino(string texto){
	//saca la primera palabra de una frase y devuelve la frase nueva
	int espacio = texto.find_first_of(" ");
	string nuevoTexto = texto.substr(espacio+1);
	return nuevoTexto;
}

void NGramas::agregarRegistroEnArbol(Registro unRegistro){
	if (!this->lexico->buscar(unRegistro)){
		this->lexico->insertar(unRegistro);
	}else{
		this->lexico->aumentarFrecuencia(unRegistro, 1);
	}
}
//--------------------------------------------------------//
//--------------Fin de funciones auxiliares --------------//

void NGramas::streamANgrama(FILE* fp){

	char *c = new char[2884354560];	//reservamos mas de 2.5gb de memoria!
	fpos_t position;
	FILE* fp_flag;
	size_t offset = 0;
	delete[] c;	//libero la memoria reservada

	while (!feof(fp) && offset < GIGA){ //Faltaria corregir la creacion de ngramas pero no es tan urgente..

		offset = ftell(fp);
		cout<<offset<<endl;
		string ngrama = "";

		ngrama += getSiguienteTermino(fp);
		//if (ngrama == "") break;
		size_t nuevoOffset = ftell(fp);
		Registro unRegistro = Registro();
		unRegistro.stringARegistro(ngrama);
		if (unRegistro.getTermino() != "" && unRegistro.getTermino() != " ")
			this->agregarRegistroEnArbol(unRegistro);

		for (int k = 0; k < cantGrama-1; k++){
			ngrama += " ";
			ngrama += getSiguienteTermino(fp);
			unRegistro.stringARegistro(ngrama);
			this->agregarRegistroEnArbol(unRegistro);

		}
		fseek(fp, nuevoOffset, SEEK_SET);

	}
}


void NGramas::levantarNgramas(string unArchivoNgramas){

	ManejoArchivo manejoArchivo = ManejoArchivo();
	manejoArchivo.abrirArchivo(unArchivoNgramas, "r");
	Registro unRegistro = Registro();
	this->registros.rehash(40000000);
	this->terminos_x_contexto.rehash(25000000);
	cout<<"Procesando archivo.."<<endl;

	size_t cantRegistros = 0;

	while(feof(manejoArchivo.getArchivo()) == 0){
		//cout<<ftell(manejoArchivo.getArchivo())<<endl;
		unRegistro = manejoArchivo.getSiguienteRegistro();
		cantRegistros ++;
		cout<< "ngrama:" << unRegistro.registroAString()<< endl;
		cout<< "contexto:" <<unRegistro.getContexto()<< endl;
		this->registros[unRegistro.registroAString()] += unRegistro.getFrecuencia();
		this->terminos_x_contexto[unRegistro.getContexto()] += unRegistro.getFrecuencia();
	}
	manejoArchivo.cerrarArchivo();

	cout<<"Cantidad Registros leidos: "<<cantRegistros<<endl;
	cout<<"the: "<<this->terminos_x_contexto["the"]<<endl;
	cout<<"The: "<<this->terminos_x_contexto["The"]<<endl;
	cout<<"Final del procesamiento del archivo."<<endl;
}

void NGramas::stringANGramaHashTable(){
	istringstream iss(this->oracion);
	this->registros.rehash(40000000);
	long posicionPuntero = 0;
	    do
		{
			string sub = "";
			string subAux;
			  for(std::size_t i=0; i<3; i++) {
				iss >> sub;
				if(i==0){
					posicionPuntero = iss.tellg();
				}
				if(sub.compare("")){
					subAux = subAux + sub;
					//aca guardamos en los hash.
					//this->registros[subAux] += 1;
					cout << subAux << endl;
					subAux += " ";
				}
			}
			  iss.seekg(posicionPuntero);
			  subAux.clear();
		}while(iss);

}
