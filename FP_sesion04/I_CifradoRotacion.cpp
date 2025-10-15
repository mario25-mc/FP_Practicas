/***************************************************************************/
// FUNDAMENTOS DE PROGRAMACION
//
// MARIO MARTINEZ CALLEJON
//
// SESION 04
/*
    Programa que cifra una letra mayúscula mediante un desplazamiento (cifrado de rotación).
   
    NOTA: Se supone que los datos introducidos son correctos
   
    Entradas: una letra mayúscula y el número de posiciones a desplazar.
    Salidas:  la letra codificada resultante.
*/
/***************************************************************************/

#include <iostream>

using namespace std;

/***************************************************************************/
/***************************************************************************/

int main() {
    const int MINIMO = 65;
    const int MAXIMO = 90;

    //Entrada
    int clave;
    char letra;

    cout << endl << "Introduzca una letra mayúscula: ";
    cin >> letra;
    cout << "Introduzca el numero de posiciones a desplazar: ";
    cin >> clave;
    cout << endl;

    //Calculos
    char desplazado = ((letra - MINIMO + clave) % (MAXIMO - MINIMO + 1)) 
                      + MINIMO;

    //Salida
    cout << "La el caracter codificado es: " << desplazado;
}

/***************************************************************************/
/***************************************************************************/