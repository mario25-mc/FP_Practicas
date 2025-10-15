/***************************************************************************/
// FUNDAMENTOS DE PROGRAMACION
//
// MARIO MARTINEZ CALLEJON
//
// SESION 04
/*
    Programa que convierte una letra minúscula introducida por el usuario
    en su correspondiente letra mayúscula.
   
    NOTA: Se supone que los datos introducidos son correctos
   
    Entradas: una letra minúscula.
    Salidas:  la letra mayúscula correspondiente.
*/
/***************************************************************************/

#include <iostream>

using namespace std;

/***************************************************************************/
/***************************************************************************/

int main() {
    //Diferencia entre minuscula y mayuscula en el codigo ASCII
    const int DIF_ASCII = -32;

    //Entrada
    char minuscula;
    cout << endl << "Intruduzca una letra minuscula: ";
    cin >> minuscula;

    //Calculos
    char mayuscula = minuscula + DIF_ASCII;

    //Salida
    cout << endl << "La letra mayuscula es: " << mayuscula;

    return 0;
}

/***************************************************************************/
/***************************************************************************/