/***************************************************************************/
// FUNDAMENTOS DE PROGRAMACION
//
// MARIO MARTINEZ CALLEJON
//
// SESION 04
/*
    Programa que intercambia la primera y la última cifra de un número entero 
    positivo, construyendo un nuevo número y mostrando si la primera cifra del 
    original es igual, mayor o menor que la última.
   
    NOTA: Se supone que los datos introducidos son correctos
   
    Entradas: un número entero positivo.
    Salidas:  nuevo número, comparaciones entre la primera y la última cifra.
*/
/***************************************************************************/

#include <iostream>
#include <cmath>

using namespace std;

/***************************************************************************/
/***************************************************************************/

int main() {
    //Entrada
    string original;

    cout << "Introduce un número entero positivo: ";
    getline(cin, original);
    cout << endl;

    //Calculos
    //Extraer primera y ultima cifra del numero y almacenar el resto
    char primera_cifra = original.at(0);
    char ultima_cifra = original.at(original.length() - 1);
    string resto = original.substr(1, original.length() - 2);

    //Construir nuevo numero
    string nuevo = ultima_cifra + resto + primera_cifra;
    int nuevo_int = stoi(nuevo);

    //Convertir original a int para comparar
    int original_int = stoi(original);

    //Salida
    cout << "Nuevo número: " << nuevo << endl;
    cout << endl;

    cout << "¿Primera cifra igual a ultima cifra?: " 
         << (original_int == nuevo_int) << endl;

    cout << "¿Primera cifra mayor que ultima cifra?: " 
         << (original_int > nuevo_int) << endl;
         
    cout << "¿Primera cifra menor que ultima cifra?: " 
         << (original_int < nuevo_int) << endl;

    return 0;
}

/***************************************************************************/
/***************************************************************************/