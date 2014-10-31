//Clase Arbol B
/*
Axiomas: 1 - Todas sus hojas estan en el mismo nivel.
         2 - Todos los nodos, a excepcion de la raiz tienen
            a lo sumo m hijos no vacios y, al menos, m/2 hijos no vacios.
         3 - El numero de claves de cada nodo es uno menos que el nÃºmero de
            sus hijos no vacios, y esas claves particionan las claves en los hijos de
            la misma forma que es un arbol de busqueda.
            Es decir que cada rama izquierda de un dato es menor estricto que el dato
            y la rama derecha es mayor estricta que el dato.
         4 - La raiz tiene a lo sumo, m hijos, pero puede tener tan solo 2 si no es hoja
			o ninguno si el arbol consiste en la raiz sola.

*/

#ifndef _ARBOLB_H_
#define _ARBOLB_H_

#ifndef NULL
#define NULL 0
#endif //NULL


#include <iostream>
#include <string.h>
#include <stdio.h>

using namespace std;

namespace abb {
enum codigosDeError
{
    overflow,
    nodoDuplicado,
    sinDato,
    exitoso,
};

template <class T, int orden>
struct B_nodo
{
    int entradasOcupadas; //Cuan ocupado esta el nodo.
    T *data; //Array que posee los datos del nodo.
    B_nodo< T, orden > *ramas[orden];//punteros hacia las ramas.
    // constructor:
    B_nodo( )
    {
        entradasOcupadas = 0;
        data = new T[orden];
    }
};

//Estos miembros del template dan la posibilidad
//al usuario de elegir el tipo de dato del arbol
// y ademas el orden del arbol B (cantidad de ramas por nodo)


//			ARBOL B:
//TODO LO QUE HAY QUE SABER DE ESTE CODIGO:
//	abb::ArbolB<Nodo,40> *lexico = new abb::ArbolB<Nodo, 40>; --> para crear el arbol
//	unArbol.insertar(unNodo); --> para insertar un nodo al arbol
//	unArbol.buscar(unNodo); --> chequea que ese nodo este en el arbol
//	unArbol.buscarYdevolver(unNodo); --> si existe el nodo en el arbol, lo devuelve

//Cada nodo tiene el termino y el offset.
//estan redefinidos los operadores de = > < para que compare solo el termino cuando se comparan
//nodos.
//Para ver si un termino esta en el arbol hay que redefinir un nodo aux, asignarle un valor a
//termino y ese aux es el que se mete en el metodo del arbol para comparar. Si esta ese nodo en el
//arbol, la funcion te devuelve un nodo con el termino y su offset.

template <class T, int orden>
class ArbolB{
	public:

    ArbolB()
    {
        raiz = NULL;
    }

    codigosDeError insertar(T &nuevaEntrada)
    /*
    Post: Si la clave de la nueva entrada ya esta en el arbol B, la funcion devuelve
    nodoDuplicado. Si no, la funcion devuelve exitoso y la nueva entrada es insertada en
    el arbol de manera que Ã©ste no pierda sus propiedades de arbol B.
    */
    {
        T datoMedio;
        B_nodo< T, orden > *ramaDerecha, *nuevaRaiz;
        codigosDeError resultado = push_down(raiz, nuevaEntrada, datoMedio, ramaDerecha);

        if (resultado == overflow) {     // Cuando ocurre esto, el arbol crece en altura.
										 // Hay que asignar una nueva raiz.
            nuevaRaiz = new B_nodo< T, orden >;
            nuevaRaiz->entradasOcupadas = 1;
            nuevaRaiz->data[0] = datoMedio;
            nuevaRaiz->ramas[0] = raiz;
            nuevaRaiz->ramas[1] = ramaDerecha;
            raiz = nuevaRaiz;
            resultado = exitoso;
        }
        return resultado;
    }

    bool buscar(T target)
    /*
    post: si hay una entrada en el arbol cuya clave coincide con la
    de target, se devuelve True, en otro caso devuelve False.
    */
    {
        return buscarRecursivamente(raiz, target);
    }

    bool aumentarFrecuencia(T target){
    	/*Solo para el caso en el que se guarden Registros en el arbol*/
    	return aumentarFrecuenciaRecursivo(raiz, target);
    }

   bool modify(T target)

	{
    	return buscarRecursivamenteParaModify(raiz, target);
	}

    T buscarYdevolver(T target)

	{
		T* dato = new T;
    	buscarRecursivamenteParaDevolver(raiz, target, dato);
    	return *dato;
	}

    void emitir()
    {
        emitirRecursivo(raiz);
    };

    void emitirRegistros(){
    	emitirRegistrosRecursivo(raiz);
    }

    void borrar()
	{
		borrarRec(raiz);
	};


    private:



        B_nodo<T,orden> *raiz;

        void emitirRecursivo(B_nodo<T,orden>* actual)
        {
            int i;
            if (actual){
                for (i=0; i<actual->entradasOcupadas; i++)
                {
                    emitirRecursivo(actual->ramas[i]);
                    cout <<actual->data[i].getTermino()<<", "<<actual->data[i].getOffset();
                    cout << endl;

                }
                emitirRecursivo(actual->ramas[actual->entradasOcupadas]);
            }
        }
        void emitirRegistrosRecursivo(B_nodo<T,orden>* actual)
        {
            int i;
            if (actual){
                for (i=0; i<actual->entradasOcupadas; i++)
                {
                    emitirRegistrosRecursivo(actual->ramas[i]);
                    cout <<actual->data[i].getTermino()<<", "<<actual->data[i].getContexto()<<actual->data[i].getFrecuencia();
                    cout << endl;

                }
                emitirRegistrosRecursivo(actual->ramas[actual->entradasOcupadas]);
            }
        }

        void borrarRec(B_nodo<T,orden>* actual)
		{
        	int i;
			if (actual){
				for (i=0; i<actual->entradasOcupadas; i++)
				{
					borrarRec(actual->ramas[i]);
				}
				borrarRec(actual->ramas[actual->entradasOcupadas]);
			}
//			delete actual;
		}

        codigosDeError push_down(B_nodo<T,orden> *actual, T &nueva_entrada, T &datoMedio,
                          B_nodo<T,orden> * &ramaDerecha)
        /* Pre: actual es o nulo o apunta a un B_nodo.
        Post: Si la entrada esta duplicada se devuelve error por nodoDuplicado. Si no,
        la nueva entrada es insertada en el subarbol: Si causa que la altura del
        arbol crezca, devuelve OVERFLOW ya que no puede ser insertada sin modificar
        la raiz del arbol B, y el registro medio es devuelto para ser reinsertado
        arriba en el arbol B, junto con el subarbol rama derecha en su derecha.
        Si la altura no crece, la funcion devuelve exitoso.
        */
        {
            codigosDeError resultado;

            int posicion;

            if (actual == NULL)
            {
                //Dado que no podemos insertar el dato en un arbol vacio, la recursion termina.
                datoMedio = nueva_entrada;
                ramaDerecha = NULL;
                resultado = overflow;
            }
            else { // Busco en el nodo actual.
                if (buscarEnNodo(actual, nueva_entrada, posicion) == true)
                    resultado = nodoDuplicado;
                else {
                    T entradaAuxiliar;
                    B_nodo<T, orden> *extraRama;
                    resultado = push_down(actual->ramas[posicion], nueva_entrada,
                                            entradaAuxiliar, extraRama);
                    if (resultado == overflow) {
                        //El registro auxiliar debe ser aÃ±adido al nodo actual.
                        if ( actual->entradasOcupadas < (int(orden)-1)) {
                            resultado = exitoso;
                            push_in(actual, entradaAuxiliar, extraRama, posicion);
                        }
                        else
                            partir_nodo( actual, entradaAuxiliar, extraRama, posicion,
                                        ramaDerecha, datoMedio);
                    //El registro medio junto con su rama derecha pasaran a un nodo mas alto.
                    }
                }
            }
            return resultado;
        }

        void push_in(B_nodo<T,orden> *actual, const T &entrada, B_nodo<T,orden> *rama_derecha, int posicion)
        /*Pre: actual apunta a un nodo de un arbol B, dicho nodo no esta lleno.
           Post: Se inserta entrada junto con su rama derecha en actual en la posicion indicada.
        */
        {
            int i;
            for (i = actual->entradasOcupadas; i > posicion; i-- ) {
                                // manda todos los posteriores hacia la derecha.
                actual->data[i] = actual->data[i - 1];
                actual->ramas[i + 1] = actual->ramas[i];
            }
            actual->data[posicion]=entrada;
            actual->ramas[posicion + 1]=rama_derecha;
            actual->entradasOcupadas++ ;
        }



        void partir_nodo(B_nodo<T,orden> *actual, const T &entradaAuxiliar,B_nodo<T,orden> *extraRama, int posicion,
                B_nodo<T, orden> * &mitad_derecha, T &datoMedio)
        /*
        actual: nodo a ser partido.
        entradaAuxiliar: entrada nueva a insertar.
        extraRama: subarbol a la derecha de entradaAuxiliar.
        posicion: index en el nodo donde va la entrada auxiliar.
        mitad_derecha: nuevo nodo para la mitad derecha de las entradas.
        datoMedio: entrada medio que se utiliza para dividir el nodo.

        Pre: Actual apunta a un nodo del arbol B. El nodo actual esta lleno.
        Post: El nodo actual que posee a entradaAuxiliar y su rama derecha es extraRama en la posicion /posicion/
			es dividido en los nodos actual y mitad derecha, separados por el registro medio, que es mayor a todos
			sus hijos izquierdos y menor a todos sus hijos derechos.
        */
        {
			mitad_derecha = new B_nodo<T,orden>;
			int mid = orden/2;             // Los datos que estan despues del medio iran a la mitad derecha.
			if (posicion <= mid) {         // Primer caso: entradaAuxiliar pertenece a la parte izquierda.
				for (int i = mid; i < orden - 1; i ++ ) { // se mueven las entradas a la parte derecha
					mitad_derecha->data[i - mid] = actual->data[i];
					mitad_derecha->ramas[i + 1 - mid] = actual->ramas[i + 1];
				}
				actual->entradasOcupadas = mid;
				mitad_derecha->entradasOcupadas = orden - 1 - mid;
				push_in(actual,entradaAuxiliar,extraRama,posicion);
			}
			else {                         // Segundo caso: entradaAuxiliar pertenece a la mitad izquierda.
				mid ++ ;                    // Por el momento se deja el dato medio en la parte izquierda.
				for (int i = mid; i < orden - 1; i ++ ) { // se mueven las entradas a la parte derecha
					mitad_derecha->data[i - mid] = actual->data[i];
					mitad_derecha->ramas[i + 1 - mid] = actual->ramas[i + 1];
				}
				actual->entradasOcupadas = mid;
				mitad_derecha->entradasOcupadas = orden - 1 - mid;
				push_in(mitad_derecha, entradaAuxiliar, extraRama, posicion - mid);
			}
			datoMedio = actual->data[actual->entradasOcupadas - 1];
                                    // Quito a medio de la mitad izquierda.
			mitad_derecha->ramas[0] = actual->ramas[actual->entradasOcupadas];
			actual->entradasOcupadas-- ;
		}





        bool buscarRecursivamente(B_nodo<T,orden>* actual, T& target)
        {
            //se almacenara si el target es encontrado en algun nodo.
            bool resultado = false;
            //se almacena si se encuentra el target, la posicion en el nodo en la que esta
            //o si no se encuentra el target, la rama que hay que tomar para continuar la busqueda.
            int posicion;

            if ( actual != NULL )
            {
                resultado = buscarEnNodo(actual, target, posicion);
                if ( resultado == false )
                    resultado = buscarRecursivamente(actual->ramas[posicion], target);
                else
                    target = actual->data[posicion];//PARTE QUE NO ENTIENDO.
            }
            return resultado;
        }

        bool buscarEnNodo(B_nodo<T,orden>* actual, T& target, int &posicion)
        {
            /*
            pre: actual apunta a un B_nodo.
            post: Si la clave de target es encontrada en el nodo actual, la funcion
            devuelve true y el parametro de posicion se seatea de forma que concuerde con
            la posicion en la que esta el target. Si no, se devuelve false y la posicion
            es seteada de forma que coincida con la rama por la que hay que continuar la
            busqueda.
            */
            posicion = 0;

            //Aumenta posicion hasta que target sea menor que la siguiente entrada.
            //Y, ademas, mientras la posicion no exceda la cantidad de nodos ocupados.
            while (( posicion < actual->entradasOcupadas )&&( target > actual->data[posicion]))
            {
                posicion++;
            }

            if (( posicion < actual->entradasOcupadas )&&( target == actual->data[posicion] ))
                return true;

            else
                return false;
        }

        bool aumentarFrecuenciaRecursivo(B_nodo<T,orden>* actual, T& target){

            bool resultado = false;
            int posicion;

            if ( actual != NULL )
            {
                resultado = buscarEnNodoParaAumentarFrecuencia(actual, target, posicion);
                if ( resultado == false )
                    resultado = aumentarFrecuenciaRecursivo(actual->ramas[posicion], target);
                else
                    target = actual->data[posicion];//PARTE QUE NO ENTIENDO.
            }
            return resultado;

        }

        bool buscarEnNodoParaAumentarFrecuencia(B_nodo<T,orden>* actual, T& target, int &posicion){
        	posicion = 0;

        	//Aumenta posicion hasta que target sea menor que la siguiente entrada.
        	//Y, ademas, mientras la posicion no exceda la cantidad de nodos ocupados.
        	while (( posicion < actual->entradasOcupadas )&&( target > actual->data[posicion]))
        	{
        	    posicion++;
        	}

        	if (( posicion < actual->entradasOcupadas )&&( target == actual->data[posicion] )){
        		actual->data[posicion].aumentarFrecuencia(1);
        		return true;
        	}

        	else
        	    return false;
        }


        bool buscarRecursivamenteParaModify(B_nodo<T,orden>* actual, T& target)
		{
			//se almacenara si el target es encontrado en algun nodo.
        	bool resultado = false;
			//se almacena si se encuentra el target, la posicion en el nodo en la que esta
			//o si no se encuentra el target, la rama que hay que tomar para continuar la busqueda.
			int posicion;

			if ( actual != NULL )
			{
				resultado = buscarEnNodoParaModify(actual, target, posicion);
				if ( resultado == false )
					resultado = buscarRecursivamenteParaModify(actual->ramas[posicion], target);
				else
					actual->data[posicion] = target;//PARTE QUE NO ENTIENDO.
			}
			return resultado;
		}



        bool buscarEnNodoParaModify(B_nodo<T,orden>* actual, T& target, int &posicion)
		{
			/*
			pre: actual apunta a un B_nodo.
			post: Si la clave de target es encontrada en el nodo actual, la funcion
			devuelve true y el parametro de posicion se seatea de forma que concuerde con
			la posicion en la que esta el target. Si no, se devuelve false y la posicion
			es seteada de forma que coincida con la rama por la que hay que continuar la
			busqueda.
			*/
			posicion = 0;

			//Aumenta posicion hasta que target sea menor que la siguiente entrada.
			//Y, ademas, mientras la posicion no exceda la cantidad de nodos ocupados.
			while (( posicion < actual->entradasOcupadas )&&( target > actual->data[posicion]))
			{
				posicion++;
			}

			if (( posicion < actual->entradasOcupadas )&&( target == actual->data[posicion] )){
				actual->data[posicion] = target;
				return true;
			}

			else
				return false;
		}

        bool buscarRecursivamenteParaDevolver(B_nodo<T,orden>* actual, T& target, T* devuelto)
		{
			//se almacenara si el target es encontrado en algun nodo.
			bool resultado = false;
			//se almacena si se encuentra el target, la posicion en el nodo en la que esta
			//o si no se encuentra el target, la rama que hay que tomar para continuar la busqueda.
			int posicion;

			if ( actual != NULL )
			{
				resultado = buscarEnNodoParaDevolver(actual, target, posicion, devuelto);
				if ( resultado == false )
					resultado = buscarRecursivamenteParaDevolver(actual->ramas[posicion], target, devuelto);
				else
					target = actual->data[posicion];//PARTE QUE NO ENTIENDO.
			}
			return resultado;
		}



		bool buscarEnNodoParaDevolver(B_nodo<T,orden>* actual, T& target, int &posicion, T* devuelto)
		{
			posicion = 0;

			//Aumenta posicion hasta que target sea menor que la siguiente entrada.
			//Y, ademas, mientras la posicion no exceda la cantidad de nodos ocupados.
			while (( posicion < actual->entradasOcupadas )&&( target > actual->data[posicion]))
			{
				posicion++;
			}

			if (( posicion < actual->entradasOcupadas )&&( target == actual->data[posicion] )){
				*devuelto = actual->data[posicion];
				return true;
			}

			else
				return false;
		}

	};

};



#endif /*_ARBOLB_H_*/
