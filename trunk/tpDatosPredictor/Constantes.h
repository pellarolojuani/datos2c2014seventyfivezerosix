/*
 * Constantes.h
 *
 *  Created on: 14/10/2014
 *      Author: juanignacio
 */

#ifndef CONSTANTES_H_
#define CONSTANTES_H_

#ifndef LONG_MAX_LINEA
#define LONG_MAX_LINEA						2500
#endif

#ifndef N
#define N									5
#endif

#ifndef SEPARADOR_NGRAMA
#define SEPARADOR_NGRAMA					' '
#endif

#ifndef TOTAL_FRECUENCIAS
#define TOTAL_FRECUENCIAS					""
#endif

/*1073741824*/
#ifndef GIGA
#define GIGA								524288000//262144000 //250MB
#endif

#ifndef READ
#define READ								"r" //apertura para lectura. debe existir previamente
#endif

#ifndef	WRITE
#define WRITE								"w" //crea uno nuevo para escritura. si ya existe se borra
#endif

#ifndef	APPEND
#define APPEND								"a" //apertura para agregado al final del archivo. si no existe se crea
#endif

#ifndef	READ_WRITE
#define READ_WRITE							"rw" // combinacion de modos r y w
#endif

#ifndef	LECTURA_ESCRITURA_EXISTENTE
#define LECTURA_ESCRITURA_EXISTENTE			"r+" //apertura para lectura y escritura. con el archivo previamente existente
#endif

#ifndef	LECTURA_ESCRITURA_NO_EXISTENTE
#define LECTURA_ESCRITURA_NO_EXISTENTE		"w+" //apertura para lectura y escritura. si no existe se crea y si existe se borra lo anterior
#endif

#ifndef	LECTURA_Y_APPEND
#define LECTURA_Y_APPEND					"a+" //todo append se hace al final, protegiendo los datos previamente escritos. los read desde el seek. si no existe se crea
#endif

#ifndef	MODO_BINARIO
#define MODO_BINARIO						"b" //modo binario
#endif

#ifndef	LECTOESCRITURA_EXISTENTE_BINARIO
#define LECTOESCRITURA_EXISTENTE_BINARIO 	"r+b" //combinacion modos r+ y b
#endif

#ifndef LECTOESCRITURA_NO_EXISTENTE_BINARIO
#define LECTOESCRITURA_NO_EXISTENTE_BINARIO "w+b" //combinacion modos w+ y b
#endif

#ifndef	LECTURA_BINARIO
#define LECTURA_BINARIO						"rb"
#endif

#ifndef	ESCRITURA_BINARIO
#define ESCRITURA_BINARIO					"wb"
#endif

#ifndef		FIN_DE_LINEA
# define	FIN_DE_LINEA			'\n'
#endif

#endif /* CONSTANTES_H_ */
