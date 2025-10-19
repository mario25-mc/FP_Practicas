/***************************************************************************/
// FUNDAMENTOS DE PROGRAMACION
//
// MARIO MARTINEZ CALLEJON
//
// SESION 06
/*
    Programa que realiza una codificación básica de una secuencia de 
    caracteres. Lee una secuencia terminada en '*' y la procesa para 
    mostrar el número de veces que un carácter aparece de forma 
    consecutiva, seguido del propio carácter.

    Entradas: una secuencia de caracteres que debe terminar con '*'.
    Salidas:  la secuencia codificada.
*/
/***************************************************************************/

#include <iostream>
#include <string>

using namespace std;

/***************************************************************************/
/***************************************************************************/

int main() {

    //Entrada
    string secuencia_original;
    do {
        cout << "Introduzca una secuencia de caracteres que termine con *: ";
        getline(cin , secuencia_original);

        //Si no termina en '*' se pide otra secuencia
        if (secuencia_original.at(secuencia_original.length() - 1) != '*') {
                cout << "Introduzca una secuencia valida." << endl;
            }  
    } while (secuencia_original.at(secuencia_original.length() - 1) != '*');

    //Cálculos
    string secuencia_final; //Secuencia procesada
    char char_siguiente;
    char char_actual;
    int contador_char;  //Contador de caracteres iguales

    string secuencia_limpia = "";   //Se eliminan los espacios
    for (int i = 0; secuencia_original.at(i) != '*'; i++) {
        if (secuencia_original.at(i) != ' ') {
            secuencia_limpia += secuencia_original.at(i);
        }
    }
    secuencia_limpia += "*";

    contador_char = 1;
    for (int i = 0; secuencia_limpia.at(i) != '*'; i++) {  
        //Continuar hasta que se llegue al '*'
        char_actual = secuencia_limpia.at(i);
        char_siguiente = secuencia_limpia.at(i + 1);

        if (char_actual == char_siguiente) {
            //Si los char son iguales aumentar el contador
            contador_char++;    
        } else {
            //Si son distintos, se añade a la secuencia y el contador reinicia
            secuencia_final += to_string(contador_char) + char_actual + " ";
            contador_char = 1;  
        }
    }   

    //Salida
    cout << "La secuencia procesada es: " << secuencia_final << endl;

    return 0;
}

/***************************************************************************/
/***************************************************************************/