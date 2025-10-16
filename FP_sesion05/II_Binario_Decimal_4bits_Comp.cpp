/***************************************************************************/
// FUNDAMENTOS DE PROGRAMACION
//
// MARIO MARTINEZ CALLEJON
//
// SESION 05
/*
    Programa que convierte un número binario de 4 cifras a su valor decimal. El
    programa comprueba que el número introducido es de 4 cifras.
   
    NOTA: Se supone que los datos introducidos son correctos
   
    Entradas: las 4 cifras del número binario (de izquierda a derecha).
    Salidas:  valor decimal correspondiente.
*/
/***************************************************************************/

#include <iostream>
#include <string>

using namespace std;

int main() {
    // Declaracion de variables
    string numero;
    int b0, b1, b2, b3;

    // Entrada
    cout << endl;
    cout << "Introduce un número binario de 4 cifras: ";
    cin >> numero;
    cout << endl;

    if (numero.length() == 4) {
        int numero_int = stoi(numero);
        // Separar las cifras
        b0 = numero_int % 10;
        b1 = (numero_int / 10) % 10;
        b2 = (numero_int / 100) % 10;
        b3 = (numero_int / 1000) % 10;

        // Calcular numero decimal
        int decimal = b3 * 8 + b2 * 4 + b1 * 2 + b0 * 1;

        // Salida
        cout << "El valor decimal es: " << decimal << endl;
    } else {
        cout << "Error: el número no tine 4 cifras" << endl;
    }

    return 0;
}