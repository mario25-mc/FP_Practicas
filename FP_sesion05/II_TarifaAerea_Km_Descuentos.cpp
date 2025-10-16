/***************************************************************************/
// FUNDAMENTOS DE PROGRAMACION
//
// MARIO MARTINEZ CALLEJON
//
// SESION 05
/*
Programa que calcula el precio final de un billete de avión en función de la 
distancia recorrida y los puntos de fidelización del cliente. Se aplican 
descuentos según la distancia y los puntos acumulados, usando condicionales.

NOTA: Se supone que los datos introducidos son correctos.

Entradas: distancia del vuelo en kilómetros (entero), puntos de fidelización 
          (entero).
Salidas:  precio final del billete (real, en euros).
*/
/***************************************************************************/

#include <iostream>
#include <cmath>

using namespace std;

/***************************************************************************/
/***************************************************************************/

int main() {
    const int TARIFA_BASE = 150;
    const int DISTANCIA_LIMITE = 300;
    const int DISTANCIA_DESCUENTO = 1000;
    const int DESCUENTO_DISTANCIA = 2;
    const int PUNTOS_DESCUENTO_MAX = 400;
    const int DESCUENTO_MAX = 4;
    const int PUNTOS_DESCUENTO_MIN = 200;
    const int DESCUENTO_MIN = 3;
    const double PRECIO_KM = 0.1;

    //Entrada
    int distancia, puntos;

    cout << endl;
    cout << "Introduzca la distancia del vuelo en kilometros: ";
    cin >> distancia;
    cout << "Indique cuántos puntos tiene en su tarjeta de fidelización: ";
    cin >> puntos;
    cout << endl;

    //Calculos 
    double precio_final;

    //calcular precio del billete
    if (distancia > DISTANCIA_LIMITE) {
        precio_final = TARIFA_BASE + PRECIO_KM*(distancia - DISTANCIA_LIMITE);
    } else {
        precio_final = TARIFA_BASE;
    }

    //calcular descuento
    double descuento = 0;

    if (distancia > DISTANCIA_DESCUENTO) {
        descuento += DESCUENTO_DISTANCIA;
    }

    if (puntos > PUNTOS_DESCUENTO_MAX){
        descuento += DESCUENTO_MAX;
    } else if (puntos > PUNTOS_DESCUENTO_MIN) {
        descuento += DESCUENTO_MIN;
    }

    //aplicar descuento
    precio_final -= precio_final*(descuento/100);

    //redondear a 2 decimales
    precio_final = (round(precio_final*100)) / 100;

    //Salida
    cout << "El precio de su billete es de " << precio_final << " euros.";

    return 0;
}

/***************************************************************************/
/***************************************************************************/