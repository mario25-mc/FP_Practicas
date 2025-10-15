/***************************************************************************/
// FUNDAMENTOS DE PROGRAMACION
//
// MARIO MARTINEZ CALLEJON
//
// SESION 03
/*
    Programa que calcula la velocidad media de un vehículo en un tramo
    controlado por radar, dados el tiempo de entrada y salida y la distancia 
    recorrida.
   
    Entradas: distancia del tramo, tiempo de entrada y tiempo de salida.
    Salidas:  velocidad media del vehículo en el tramo.
*/
/***************************************************************************/

#include <iostream>

int main() {
    //Declaración de variables
    double longitud_1 = 5.3, velocidad_1 = 80;
    double longitud_2 = 8.1, velocidad_2 = 100;
    double longitud_3 = 6.4, velocidad_3 = 80;
    int tiempo_total_segundos = 0;

    //Cálculos
    //calcular segundos minimos por tramo
    tiempo_total_segundos += (longitud_1 / velocidad_1)*3600;
    tiempo_total_segundos += (longitud_2 / velocidad_2)*3600;
    tiempo_total_segundos += (longitud_3 / velocidad_3)*3600;

    //pasar segundos a minutos y segundos
    double minutos;
    double segundos;
    minutos = tiempo_total_segundos / 60;
    segundos = tiempo_total_segundos % 60;

    //Salida
    std::cout << "Tiempo en segundos: " << tiempo_total_segundos << " segundos" 
              << std::endl;
    std::cout << "Tiempo en minutos y segundos: " << minutos << " minutos y " 
              << segundos << " segundos";

    return 0;
}