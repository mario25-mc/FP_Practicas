/***************************************************************************/
/***************************************************************************/
// FUNDAMENTOS DE PROGRAMACIÓN
//
// (C) FRANCISCO JOSÉ CORTIJO BON
// DEPARTAMENTO DE CIENCIAS DE LA COMPUTACIÓN E INTELIGENCIA ARTIFICIAL
//
// RELACIÓN DE PROBLEMAS 2
//
/*
	El método RLE (Run Length Encoding) codifica una secuencia de datos
	formada por series de valores idénticos consecutivos como una secuencia de
	parejas de números(valor de la secuencia y número de veces que se repite).

	Este programa lee una secuencia de números naturales (terminada con -1) y
	la codifica mediante el método RLE.

	La lectura no está etiquetada, por lo que es aconsejable realizarla con
	redirección de entrada, tomando los datos de un fichero de texto.

	ALGORITMO:

		Leer actual
		anterior = actual

		Mientras que actual no sea TERMINADOR

			Leer actual

			Si son iguales anterior y actual
				incrementar la longitud de la secuencia actual
			si no
				"Imprimir" el anterior junto con la longitud actual
					y resetear el contador de la longitud actual

				anterior = actual

*/
/***************************************************************************/
/***************************************************************************/

#include <iostream>
using namespace std;

int main()
{
	const char TERMINADOR = '*';

	char actual;   	// número leido, en proceso
	char anterior; 	// número inmediantamente anterior al leido
	int iguales_hasta_ahora;  // número de valores iguales

	bool continuar; // Determina si debe realizarse una nueva iteración
					// (solo si el dato leido no es es TERMINADOR)

	string resultado; // Cadena con el resultado de la codificación

 
	cin >> actual;	// Lectura anticipada

	anterior = actual;
	iguales_hasta_ahora = 0; // Podría ser TERMINADOR

	continuar = (actual != TERMINADOR);

	while (continuar) {

		if (actual == anterior) iguales_hasta_ahora++; // Continua la serie
		else {

            // Montar pareja: num.veces - valor
			resultado += "("+to_string(iguales_hasta_ahora) + "," + 
			              anterior + ") ";

			iguales_hasta_ahora = 1; // Empezar una nueva serie
		}

        anterior = actual; // Preparar siguiente paso


		// Nueva lectura

    	cin >> actual; // Lectura anticipada
		continuar = (actual != TERMINADOR);
	}

	// Considerar la última pareja: num.veces - valor

    if (iguales_hasta_ahora != 0)
     	resultado += "("+to_string(iguales_hasta_ahora) + "," + 
			           anterior + ") ";


	// Salida
    cout << resultado << endl;

	return 0;
}