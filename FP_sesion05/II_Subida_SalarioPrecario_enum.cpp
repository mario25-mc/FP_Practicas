/***************************************************************************/
// FUNDAMENTOS DE PROGRAMACION
//
// MARIO MARTINEZ CALLEJON
//
// SESION 04
/*
	Programa que lee la edad y el salario de una persona y aplica subidas al 
    salario según condiciones: 4% si la edad es mayor de 65 o menor de 35 años. 
    Si además el salario es inferior a 300 euros, se suma un 3% extra; si está 
    entre 300 y 900 euros (sin incluir 900), se suma un 1.5% extra. Se indica 
    por pantalla qué subidas se han aplicado.
   
	NOTA: Se supone que los datos introducidos son correctos.
   
	Entradas: edad (entero), salario (real).
	Salidas:  salario final (real), subidas aplicadas (texto).
*/
/***************************************************************************/


#include <iostream>
#include <iomanip>

using namespace std;

/***************************************************************************/
/***************************************************************************/

int main() {
    // Constantes
    const int EDAD_MAYOR = 65;
    const int EDAD_MENOR = 35;
    const double SUBIDA_PRINCIPAL = 0.04;
    const double SALARIO_LIMITE_BAJO = 300.0;
    const double SUBIDA_EXTRA_BAJA = 0.03;
    const double SALARIO_LIMITE_ALTO = 900.0;
    const double SUBIDA_EXTRA_MEDIA = 0.015;

    // Entrada
    int edad;
    double salario;

    cout << endl;
    cout << "Introduzca la edad: ";
    cin >> edad;
    cout << "Introduzca el salario: ";
    cin >> salario;
    cout << endl;

    //Declaracion de valores para el tipo enumerado Subida
    enum class Subida {
        ninguna,
        subida_edad,
        subida_media,
        subida_maxima
    };

    double salario_final = salario;
    Subida subida_usuario = Subida::ninguna;

    // Subida del 4%
    if (edad > EDAD_MAYOR || edad < EDAD_MENOR) {
        salario_final += salario * SUBIDA_PRINCIPAL;
        subida_usuario = Subida::subida_edad;

        // Subidas adicionales
        if (salario < SALARIO_LIMITE_BAJO) {
            salario_final += salario * SUBIDA_EXTRA_BAJA;
            subida_usuario = Subida::subida_maxima;

        } else if (salario >= SALARIO_LIMITE_BAJO && 
                   salario < SALARIO_LIMITE_ALTO) {
            salario_final += salario * SUBIDA_EXTRA_MEDIA;
            subida_usuario = Subida::subida_media;
        }
    }

    // Salida
    cout << "Salario final: " << salario_final << " euros." << endl;
    cout << "Subidas aplicadas: ";
    switch (subida_usuario) {
        case Subida::ninguna:
            cout << "Ninguna.";
            break;
        case Subida::subida_edad:
            cout << "4%.";
            break;
        case Subida::subida_maxima:
            cout << "4% y 3%.";
            break;
        case Subida::subida_media:
            cout << "4% y 1.5%.";
            break;
    }
    cout << endl;

    return 0;
}
/***************************************************************************/
/***************************************************************************/
