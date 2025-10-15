/***************************************************************************/
// FUNDAMENTOS DE PROGRAMACION
//
// MARIO MARTINEZ CALLEJON
//
// SESION 04
/*
    Programa que lee una cadena de caracteres que indica una hora en formato
    horario de 24 horas e indica si es correcta o no usando condicionales para
    evitar hacer comprobaciones innecesarias.
   
    NOTA: Se supone que los datos introducidos son correctos
   
    Entradas: una cadena de 5 caracteres con el formato HH:MM.
    Salidas:  1 si la hora es correcta, 0 si no lo es.
*/
/***************************************************************************/

#include <iostream>
#include <string>

using namespace std;

/***************************************************************************/
/***************************************************************************/

int main() {
    // Entrada
    string hora_entrada;

    cout << endl;
    cout << "Introduzca la hora: ";
    getline(cin, hora_entrada);
    cout << endl;

    // Calculos y validación con condicionales
    bool es_correcta = false;
    if (hora_entrada.length() == 5 && hora_entrada.at(2) == ':') {
        // Solo si el formato es correcto, se convierte y valida
        int horas = stoi(hora_entrada.substr(0,2));
        int minutos = stoi(hora_entrada.substr(3,2));
        if (horas >= 0 && horas <= 23 && minutos >= 0 && minutos <= 59) {
            es_correcta = true;
        }
    }

    //Salida
    cout << "¿Formato correcto?: " << ((es_correcta) ? "Si" : "No") << endl;

    return 0;
}

/***************************************************************************/
/***************************************************************************/