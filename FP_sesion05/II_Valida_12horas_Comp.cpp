/***************************************************************************/
// FUNDAMENTOS DE PROGRAMACION
//
// MARIO MARTINEZ CALLEJON
//
// SESION 04
/*
    Programa que lee una cadena de caracteres que indica una hora en formato
    horario de 12 horas e indica si es correcta o no usando condicionales para
    evitar hacer comprobaciones innecesarias.
   
    NOTA: Se supone que los datos introducidos son correctos
   
    Entradas: una cadena de 7 caracteres con el formato HH:MMAM o HH:MMPM.
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

    //Comprobar formato de la cadena
    if (hora_entrada.length() == 7 && hora_entrada.at(2) == ':') {

        string sufijo = hora_entrada.substr(5,2);

        //Comprobar AM/PM
        if (sufijo == "AM" || sufijo == "PM" || sufijo == "am" || 
            sufijo == "pm") {

            // Solo si el formato es correcto, se convierte y valida
            int horas = stoi(hora_entrada.substr(0,2));
            int minutos = stoi(hora_entrada.substr(3,2));

            if (horas >= 1 && horas <= 12 && minutos >= 0 && minutos <= 59) {
                es_correcta = true;
            }
        }    
    }

    //Salida
    cout << "¿Formato correcto?: " << ((es_correcta) ? "Si" : "No") << endl;

    return 0;
}

/***************************************************************************/
/***************************************************************************/