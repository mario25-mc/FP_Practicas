/***************************************************************************/
// FUNDAMENTOS DE PROGRAMACION
//
// MARIO MARTINEZ CALLEJON
//
// SESION 03
/*
    Programa que ajusta una cantidad de horas, minutos y segundos a su forma 
    normalizada, mostrando el resultado en días, horas, minutos y segundos.
   
    NOTA: Se supone que los datos introducidos son correctos
   
    Entradas: horas, minutos y segundos.
    Salidas:  tiempo ajustado en días, horas, minutos y segundos.
*/
/***************************************************************************/

#include <iostream>

int main() {
    // Declaracion de variables 
    int dias;
    int horas;
    int minutos;
    int segundos;

    // Solicitar al usuario los valores de días, horas, minutos y segundos

    std::cout << "Introduzca las horas: ";
    std::cin >> horas;
    std::cout << "Introduzca los minutos: ";
    std::cin >> minutos;
    std::cout << "Introduzca los segundos: ";
    std::cin >> segundos;
    std::cout << std::endl;

    // Convertir todo a segundos 
    int total_segundos = horas * 3600 + minutos * 60 + segundos;

    //Calcular dias, horas, minutos y segundos
    int resto;

    dias = total_segundos / 86400;
    resto = total_segundos % 86400;
    horas = resto / 3600;
    resto = resto % 3600;
    minutos = resto / 60;
    segundos= resto % 60;

    //Salida
    std::cout << "Tiempo ajustado: " << dias << " días, " << horas 
    << " horas, " << minutos << " minutos, " << segundos 
    << " segundos." << std::endl;

    return 0;
}