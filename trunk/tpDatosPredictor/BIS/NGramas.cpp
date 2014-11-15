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
	//this->terminos_x_contexto = tr1::unordered_map<string, size_t>();
	this->oracion = "";
}

NGramas::NGramas(int cantGrama, string separadorNgrama){
	this->lexico = new abb::ArbolB<Registro, 60>;
	this->cantGrama = cantGrama;
	this->separadorNgrama = separadorNgrama;
	this->listaTerminos = vector<string>();
	this->registros = tr1::unordered_map<string, size_t>();
    //this->terminos_x_contexto = tr1::unordered_map<string, size_t>();
	this->oracion = "";
}

NGramas::NGramas(int cantGrama, string separadorNgrama,string oracion){
	this->lexico = new abb::ArbolB<Registro, 60>;
	this->cantGrama = cantGrama;
	this->separadorNgrama = separadorNgrama;
	this->listaTerminos = vector<string>();
	this->registros = tr1::unordered_map<string, size_t>();
	//this->terminos_x_contexto = tr1::unordered_map<string, size_t>();
	this->oracion = oracion;
}

NGramas::~NGramas() {
	// TODO Auto-generated destructor stub
}

abb::ArbolB<Registro,60>* NGramas::getLexico(){
	return this->lexico;
}

tr1::unordered_map<string, size_t> NGramas::getRegistros(){
	return this->registros;
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


void NGramas::levantarNgramas(){

	ManejoArchivo manejoArchivo = ManejoArchivo();
	manejoArchivo.abrirArchivo("file1.txt", "r");
	Registro unRegistro = Registro();
	this->registros.rehash(80000000);
	//this->terminos_x_contexto.rehash(25000000);
	cout<<"Procesando archivo.."<<endl;

	size_t cantRegistros = 0;

	while(feof(manejoArchivo.getArchivo()) == 0){
		cout<<ftell(manejoArchivo.getArchivo())<<endl;
		unRegistro = manejoArchivo.getSiguienteRegistro();
		cantRegistros ++;
		this->registros[unRegistro.registroAString()] += unRegistro.getFrecuencia();
		//this->terminos_x_contexto[unRegistro.getContexto()] += unRegistro.getFrecuencia();
	}
	manejoArchivo.cerrarArchivo();

	cout<<"Cantidad Registros leidos: "<<cantRegistros<<endl;
	//cout<<"the: "<<this->terminos_x_contexto["the"]<<endl;
	//cout<<"The: "<<this->terminos_x_contexto["The"]<<endl;
	cout<<"Final del procesamiento del archivo."<<endl;
}

void NGramas::stringANGramaHashTable(char* buffer){
	istringstream iss(buffer);
	strcpy(buffer,"");
	this->registros.rehash(40000000);
	unsigned long int posicionPuntero = 0;
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
					this->registros[subAux] += 1;
					//cout << subAux << endl;
					subAux += " ";
				}
			}
			  iss.seekg(posicionPuntero);
			  subAux.clear();
		}while(iss);
	    iss.str(std::string());
}

void NGramas:: guardarNgramasAAchivo(char* nombreArchivo){

	tr1::unordered_map<string, size_t>::iterator itr;
	 ofstream fichero(nombreArchivo);

	 for(itr = this->registros.begin(); itr != registros.end(); ++itr){
			 string ngrama = (*itr).first.c_str();
			 ngrama = ngrama + " ";
			 stringstream ss;
			 ss << (*itr).second;
			 ngrama = ngrama + ss.str();

			 fichero << ngrama << endl;
		 }
	 fichero.close();
}

void NGramas::fusionarArchivosNgramas(string unArchivoNgrama,string otroArchivoNgrama){
	ManejoArchivo manejoArchivo = ManejoArchivo();
	ManejoArchivo otroArchivo = ManejoArchivo();
	manejoArchivo.abrirArchivo(unArchivoNgrama, "r");
	otroArchivo.abrirArchivo(otroArchivoNgrama, "r");
	Registro unRegistro = Registro();
	this->registros.rehash(200000000);
	//this->terminos_x_contexto.rehash(25000000);
	cout<<"Procesando  1er archivo.."<<endl;

	while(feof(manejoArchivo.getArchivo()) == 0){
		unRegistro = manejoArchivo.getSiguienteRegistro();
		this->registros[unRegistro.registroAString()] += unRegistro.getFrecuencia();
	}
	manejoArchivo.cerrarArchivo();
	cout<<"Termino Procesar  1er archivo.."<<endl;
	cout<<"Procesando  2do archivo.."<<endl;
	while(feof(otroArchivo.getArchivo()) == 0){
			unRegistro = otroArchivo.getSiguienteRegistro();
			this->registros[unRegistro.registroAString()] += unRegistro.getFrecuencia();
	}
	cout<<"Termino Procesar  2do archivo.."<<endl;
	otroArchivo.cerrarArchivo();
	unRegistro.~Registro();

}
