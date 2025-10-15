/***************************************************************************/
// FUNDAMENTOS DE PROGRAMACION
//
// MARIO MARTINEZ CALLEJON
//
// SESION 03
/*
    Programa que calcula el valor de la función gaussiana para un valor x,
    dados la media y la desviación típica.
   
    NOTA: Se supone que los datos introducidos son correctos
   
    Entradas: media, desviación típica y valor de x.
    Salidas:  valor de la función gaussiana para x.
*/
/***************************************************************************/

#include <iostream>
#include <cmath>

int main() {
    // Declaracion de variables
    double media;
    double desviacion_tipica;
    double x;   // Valor de abcisa x

    // Pedir datos al usuario
    std::cout << "Introduce la media: ";
    std::cin >> media;
    std::cout << "Introduce la desviacion tipica: ";
    std::cin >> desviacion_tipica;
    std::cout << "Introduce el valor de x: ";
    std::cin >> x;

    double resultado;   // Variable para almacenar el resultado
    double pi = 3.141592653589793;  // Almacenar el valor de pi

    //Calcular resultado con la formula
    resultado = ((1.0/(desviacion_tipica*sqrt(2*pi)))*  
    exp(-0.5*pow((x-media)/desviacion_tipica,2)));  

    // Mostrar el resultado
    std::cout << "El valor de la función gaussiana es: " << resultado;

    return 0;
}