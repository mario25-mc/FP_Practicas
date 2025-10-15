/***************************************************************************/
// FUNDAMENTOS DE PROGRAMACION
//
// MARIO MARTINEZ CALLEJON
//
// SESION 03
/*
    Programa que desplaza un número dentro de un intervalo dado, de forma 
    cíclica, según una cantidad de posiciones especificada por el usuario.
   
    NOTA: Se supone que los datos introducidos son correctos
   
    Entradas: valor mínimo y máximo del intervalo, cantidad de posiciones a 
              desplazar, número a desplazar.
    Salidas:  número desplazado dentro del intervalo.
*/
/***************************************************************************/

#include <iostream>

int main() {
    //Declaracion de variables
    int minimo, maximo;
    int desplazamiento;
    int a_desplazar;

    //Entrada
    std::cout << std::endl;
    std::cout << "Introduzca el valor minimo del intervalo: ";
    std::cin >> minimo;
    std::cout << "Introduzca el valor maximo del intervalo: ";
    std::cin >> maximo;
    std::cout << "Introduzca la cantidad de posiciones desplazadas: ";
    std::cin >> desplazamiento;
    std::cout << "Introduzca el numero a desplazar: ";
    std::cin >> a_desplazar;
    std::cout << std::endl;

    //Calculo
    int desplazado = ((a_desplazar - minimo + desplazamiento) %
                     (maximo - minimo +1)) + minimo;

    //Salida
    std::cout << "El numero desplazado es: " << desplazado;
    return 0;
}