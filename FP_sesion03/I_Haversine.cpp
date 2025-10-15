/***************************************************************************/
// FUNDAMENTOS DE PROGRAMACION
//
// MARIO MARTINEZ CALLEJON
//
// SESION 03
/*
    Programa que calcula la distancia entre dos puntos geográficos dados por
    su latitud, longitud y altura sobre el nivel del mar, utilizando la fórmula
    de Haversine para la distancia sobre el plano y considerando la diferencia
    de alturas para la distancia real.
   
    NOTA: Se supone que los datos introducidos son correctos

    Entradas: latitud, longitud y altura del primer y segundo punto.
    Salidas:  distancia sobre el plano y distancia real entre los dos puntos 
              dados.
*/
/***************************************************************************/

#include <iostream>
#include <cmath>
#include <algorithm>

const double R = 6372797.560856; // Radio medio de la Tierra en metros
const double PI = 3.141592653589793;

int main() {
    //Declaracion de variables de entrada
    double lat1, lon1, h1;
    double lat2, lon2, h2;

    //Entrada de datos
    std::cout << "Introduce la latitud del primer punto:   ";
    std::cin >> lat1;
    std::cout << "Introduce la longitud del primer punto:  ";
    std::cin >> lon1;
    std::cout << "Introduce la altura del primer punto:    ";
    std::cin >> h1;
    std::cout << "Introduce la latitud del segundo punto:  ";
    std::cin >> lat2;
    std::cout << "Introduce la longitud del segundo punto: ";
    std::cin >> lon2;
    std::cout << "Introduce la altura del segundo punto:   ";
    std::cin >> h2;

    // Convertir a radianes
    lat1 = lat1 * PI / 180.0;
    lon1 = lon1 * PI / 180.0;
    lat2 = lat2 * PI / 180.0;
    lon2 = lon2 * PI / 180.0;

    // Formula de Haversine

    double a = pow(sin((lat2 - lat1) / 2.0), 2) + 
    cos(lat1) * cos(lat2) * pow(sin((lon2 - lon1) / 2.0), 2);

    double c = 2 * asin(std::min(1.0, sqrt(a)));

    double distancia_plano = R * c; // distancia sobre plano

    // Distancia real considerando alturas
    double diferencia_alturas = h2 - h1;
    double distancia_real = sqrt(pow(distancia_plano, 2) + 
                            pow(diferencia_alturas, 2));

    //Mostrar resultados
    std::cout.setf(std::ios::fixed);
    
    std::cout << std::endl << "Distancia sobre plano (dp): " << distancia_plano 
    << " metros" << std::endl;

    std::cout << "Distancia real (dr):        " << distancia_real << " metros";

    return 0;
}
