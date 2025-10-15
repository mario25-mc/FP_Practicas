/***************************************************************************/
// FUNDAMENTOS DE PROGRAMACION
//
// MARIO MARTINEZ CALLEJON
//
// SESION 03
/*
    Programa que trunca un número real a un número de decimales especificado
    por el usuario.
   
    NOTA: Se supone que los datos introducidos son correctos
   
    Entradas: número real y número de decimales a truncar.
    Salidas:  número truncado con el número de decimales indicado.
*/
/***************************************************************************/

#include <iostream>
#include <cmath>

int main() {
    // Declaracion de variables del numero real y el numero 
    double numero_real;
    int numero_de_decimales;

    // Pedir datos al usuario
    std::cout << "Introduzca un numero real: ";
    std::cin >> numero_real;
    std::cout << "Introduzca el numero de decimales: ";
    std::cin >> numero_de_decimales;

    // Elevar 10 al numero de decimales
    double factor = pow(10, numero_de_decimales);   

    //Calculos
    int entero = numero_real * factor;  
    double resultado = entero / factor; 

    //Salida
    std::cout << "Resultado truncado: " << resultado;   
    return 0;
}