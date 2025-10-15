/***************************************************************************/
// FUNDAMENTOS DE PROGRAMACION
//
// MARIO MARTINEZ CALLEJON
//
// SESION 03
/*
    Programa que calcula el cambio a devolver al cliente en monedas de euro 
    y céntimos, dados el importe a pagar y la cantidad pagada.
   
    NOTA: Se supone que los datos introducidos son correctos
   
    Entradas: cantidad a pagar y cantidad pagada (en euros).
    Salidas:  número de monedas de cada tipo a devolver.
*/
/***************************************************************************/

#include <iostream>
#include <cmath>

int main()
{
    //Declaración de variables
    double cantidad_a_pagar;
    double cantidad_pagada;
    int monedas_2e = 0, monedas_1e = 0, monedas_50c = 0, monedas_20c = 0,
        monedas_10c = 0, monedas_5c = 0, monedas_2c = 0, monedas_1c = 0;

    //Entradas
    std::cout << std::endl << "Introduzca la cantidad a pagar (en euros): ";
    std::cin >> cantidad_a_pagar;
    std::cout << "Introduzca la cantidad con la que se ha pagado (en euros): ";
    std::cin >> cantidad_pagada;
    std::cout << std::endl;

    int int_a_pagar_cts = round(cantidad_a_pagar * 100);
    int int_pagado_cts = round(cantidad_pagada * 100);

    // Se calcula la cantidad a devolver en céntimos
    int cantidad_a_devolver = int_pagado_cts - int_a_pagar_cts;

    monedas_2e = cantidad_a_devolver / 200;
    cantidad_a_devolver %= 200;

    monedas_1e = cantidad_a_devolver / 100;
    cantidad_a_devolver %= 100;

    monedas_50c = cantidad_a_devolver / 50;
    cantidad_a_devolver %= 50;

    monedas_20c = cantidad_a_devolver / 20;
    cantidad_a_devolver %= 20;

    monedas_10c = cantidad_a_devolver / 10;
    cantidad_a_devolver %= 10;

    monedas_5c = cantidad_a_devolver / 5;
    cantidad_a_devolver %= 5;

    monedas_2c = cantidad_a_devolver / 2;
    cantidad_a_devolver %= 2;

    monedas_1c = cantidad_a_devolver;

    //Salidas
    std::cout << "Cantidad a devolver: " << cantidad_a_devolver << std::endl;

    std::cout << std::endl <<"Monedas a devolver: " << std::endl;

    std::cout << "\t" << monedas_2e << " moneda(s) de 2 euros." << std::endl;

    std::cout << "\t" << monedas_1e << " moneda(s) de 1 euro." << std::endl;

    std::cout << "\t" << monedas_50c << " moneda(s) de 50 centimos." 
              << std::endl;

    std::cout << "\t" << monedas_20c << " moneda(s) de 20 centimos." 
              << std::endl;

    std::cout << "\t" << monedas_10c << " moneda(s) de 10 centimos." 
              << std::endl;

    std::cout << "\t" << monedas_5c << " moneda(s) de 5 centimos." << std::endl;

    std::cout << "\t" << monedas_2c << " moneda(s) de 2 centimos." << std::endl;

    std::cout << "\t" << monedas_1c << " moneda(s) de 1 centimo." << std::endl;

    return 0;
}

