/***************************************************************************/
/***************************************************************************/
// FUNDAMENTOS DE PROGRAMACI�N
//
// (C) FRANCISCO JOS� CORTIJO BON
// DEPARTAMENTO DE CIENCIAS DE LA COMPUTACI�N E INTELIGENCIA ARTIFICIAL
//
// RELACI�N DE PROBLEMAS 2
//
/*
	El m�todo RLE (Run Length Encoding) codifica una secuencia de datos
	formada por series de valores id�nticos consecutivos como una secuencia de
	parejas de n�meros(valor de la secuencia y n�mero de veces que se repite).

	Este programa lee una secuencia de n�meros naturales (terminada con -1) y
	la codifica mediante el m�todo RLE.

	La lectura no est� etiquetada, por lo que es aconsejable realizarla con
	redirecci�n de entrada, tomando los datos de un fichero de texto.

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

	char actual;   	// n�mero leido, en proceso
	char anterior; 	// n�mero inmediantamente anterior al leido
	int iguales_hasta_ahora;  // n�mero de valores iguales

	bool continuar; // Determina si debe realizarse una nueva iteraci�n
					// (solo si el dato leido no es es TERMINADOR)

	string resultado; // Cadena con el resultado de la codificaci�n

 
	cin >> actual;	// Lectura anticipada

	anterior = actual;
	iguales_hasta_ahora = 0; // Podr�a ser TERMINADOR

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

	// Considerar la �ltima pareja: num.veces - valor

    if (iguales_hasta_ahora != 0)
     	resultado += "("+to_string(iguales_hasta_ahora) + "," + 
			           anterior + ") ";


	// Salida
    cout << resultado << endl;

	return 0;
}