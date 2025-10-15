/***************************************************************************/
// FUNDAMENTOS DE PROGRAMACION
//
// MARIO MARTINEZ CALLEJON
//
// SESION 04
/*
    Programa que lee una cadena de caracteres que indica una hora en formato
    horario de 24 horas e indica si es correcta o no.
   
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
    cout << "Introduzca la hora: ";
    getline(cin, hora_entrada);
    cout << endl;

    //Calculos
    //Comprobar longitud y dos puntos
    bool longitud_ok = (hora_entrada.length() == 5);
    bool dos_puntos_ok = (hora_entrada.at(2) == ':');

    // Convertir a enteros
    int horas = stoi(hora_entrada.substr(0,2));
    int minutos = stoi(hora_entrada.substr(3,2));

    // Validar rango
    int horas_ok = (horas >= 0) && (horas <= 23);
    int minutos_ok = (minutos >= 0) && (minutos <= 59);

    // Es correcta si todas las condiciones se cumplen
    int es_correcta = longitud_ok && dos_puntos_ok && horas_ok && minutos_ok;

    //Salida
    cout << "¿Hora correcta? (1=si, 0=no): " << es_correcta << endl;

    return 0;
}

/***************************************************************************/
/***************************************************************************/