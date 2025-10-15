/***************************************************************************/
// FUNDAMENTOS DE PROGRAMACION
//
// MARIO MARTINEZ CALLEJON
//
// SESION 03
/*
    Programa que convierte un número binario de 4 cifras a su valor decimal.
   
    NOTA: Se supone que los datos introducidos son correctos
   
    Entradas: las 4 cifras del número binario (de izquierda a derecha).
    Salidas:  valor decimal correspondiente.
*/
/***************************************************************************/

#include <iostream>

int main() {
    // Declaracion de variables
    int numero;
    int b0, b1, b2, b3;

    // Entrada
    std::cout << std::endl;
    std::cout << "Introduce un número binario de 4 cifras: ";
    std::cin >> numero;
    std::cout << std::endl;

    // Separar las cifras
    b0 = numero % 10;
    b1 = (numero / 10) % 10;
    b2 = (numero / 100) % 10;
    b3 = (numero / 1000) % 10;

    // Calcular numero decimal
    int decimal = b3 * 8 + b2 * 4 + b1 * 2 + b0 * 1;

    // Salida
    std::cout << "El valor decimal es: " << decimal << std::endl;
    return 0;
}