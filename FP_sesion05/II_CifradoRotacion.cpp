/***************************************************************************/
// FUNDAMENTOS DE PROGRAMACION
//
// MARIO MARTINEZ CALLEJON
//
// SESION 05
/*
    Programa que cifra una letra mayúscula mediante un desplazamiento 
    (cifrado de rotación). Se hace uso de condicionales para realizar los 
    cálculos.
   
    NOTA: Se supone que los datos introducidos son correctos
   
    Entradas: una letra mayúscula y el número de posiciones a desplazar.
    Salidas:  la letra codificada resultante.
*/
/***************************************************************************/

#include <iostream>

using namespace std;

/***************************************************************************/
/***************************************************************************/

int main() {
    const int MINIMO = 65;
    const int MAXIMO = 90;

    //Entrada
    int clave;
    char letra;

    cout << endl;
    cout << endl << "Introduzca una letra mayúscula: ";
    cin >> letra;
    cout << "Introduzca el numero de posiciones a desplazar (0-51): ";
    cin >> clave;
    cout << endl;

    //Calculos
    char desplazado;
    int desplazamiento = (letra - MINIMO) + clave;

    if (clave < 52) {
        if (desplazamiento > (MAXIMO - MINIMO)) {
            /*si el desplazamiento se pasa del intervalo  se ajusta restando el 
            tamaño del alfabeto*/
            desplazado = MINIMO + (desplazamiento - (MAXIMO - MINIMO + 1));
        } else {
            desplazado = MINIMO + desplazamiento;
        }
        //Salida
        cout << "La el caracter codificado es: " << desplazado << endl;
    } else {
        cout << "Introduzca una clave menor o igual que 51" << endl;
    }
    

    
}

/***************************************************************************/
/***************************************************************************/