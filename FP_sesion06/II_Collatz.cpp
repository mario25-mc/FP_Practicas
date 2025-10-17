/***************************************************************************
// FUNDAMENTOS DE PROGRAMACION
//
// MARIO MARTINEZ CALLEJON
//
// SESION 06
/*
    Generador de la Secuencia de Collatz.

    Este programa calcula y muestra la secuencia de Collatz (tambi�n conocida
    como conjetura 3n+1) para un n�mero natural introducido por el usuario.
    La secuencia se genera aplicando repetidamente las siguientes reglas
    hasta que el n�mero resultante es 1:
    - Si el n�mero es par, se divide por 2.
    - Si el n�mero es impar, se multiplica por 3 y se le suma 1.

    Entradas:
        - base: n�mero natural (entero positivo) para iniciar la secuencia.

    Salidas:
        - La secuencia de Collatz completa, desde 'base' hasta 1,

    NOTA: Se supone que la entrada es un n�mero natural. El programa
    intenta validar que el n�mero introducido es un entero positivo en
    tiempo de ejecuci�n.
*/
//**************************************************************************/

#include <iostream>
#include <string>

using namespace std;

int main (){
    // Entrada
    string base_str;
    long long base;
    bool es_int;

    do{
        es_int = true;
        cout << "Introduzca la base (numero natural): ";
        cin >> base_str;
        
        // Comprobar si es un numero natural
        for (int i = 0; i < base_str.length(); i++) {
            if (!isdigit(base_str.at(i))) { 
                es_int = false;     //Comprobar que es un numero
            }
        }
        if (es_int) {   //Si es un numero ver si es positivo
            base = stoi(base_str);  //Pasar a int
            if (base <= 0) {
                es_int = false;     //Si no es natural se pide otro numero
            }
        }

    } while (!es_int);

    // C�lculos
    string secuencia = "{"; //Comenzar secuencia
    long long num_actual = base;  //Variable para realizar los calculos

    while (num_actual != 1) {
        secuencia += to_string(num_actual); //A�adir numero a la secuencia
        secuencia += ", ";

        if (num_actual % 2 == 0) {  //Si es par se divide entre 2
            num_actual /= 2;
        } else {    
            num_actual *= 3;    //Si es impar se multiplica por 3 y se suma 1   
            num_actual += 1;
        }
    }
    secuencia += "1}";   //Cerrar secuencia

    //Salida
    cout << endl;
    cout << "Collatz(" << base << ") = " << secuencia << endl;

    return 0;
}