/***************************************************************************/
// FUNDAMENTOS DE PROGRAMACION
//
// MARIO MARTINEZ CALLEJON
//
// SESION 04
/*
	Programa que convierte una letra mayúscula introducida por el usuario
	en su correspondiente letra minúscula.
   
	NOTA: Se supone que los datos introducidos son correctos
   
	Entradas: una letra mayúscula.
	Salidas:  la letra minúscula correspondiente.
*/
/***************************************************************************/

#include <iostream>

using namespace std;

/***************************************************************************/
/***************************************************************************/

int main() {
	// Diferencia entre mayúscula y minúscula en el código ASCII
	const int DIF_ASCII = 32;

	// Entrada
	char mayuscula;
	cout << endl << "Introduzca una letra mayuscula: ";
	cin >> mayuscula;

	// Cálculos
	char minuscula = mayuscula + DIF_ASCII;

	// Salida
	cout << endl << "La letra minuscula es: " << minuscula;

	return 0;
}

/***************************************************************************/
/***************************************************************************/