/***************************************************************************
// FUNDAMENTOS DE PROGRAMACION
//
// MARIO MARTINEZ CALLEJON
//
// SESION 07
/*
    Programa que ofrece un menú para redondear o truncar un número real
    a un número de decimales especificado por el usuario.

    El programa implementa funciones para calcular potencias, redondear
    (alejándose de cero en el caso de .5) y truncar números. El menú
    principal permite al usuario elegir la operación, introducir los
    datos y ver el resultado.

    Entradas:
        - opcion: Opción del menú (1: redondear, 2: truncar, 0: salir).
        - numero: Número real (double) que se va a procesar.
        - decimales: Número de decimales (entero >= 0) para la operación.

    Salidas:
        - El resultado de la operación (redondeo o truncamiento) impreso
          en la consola.
*/
//**************************************************************************/

#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

//**************************************************************************/
//**************************************************************************/

double Potencia(double base, int exponente) {
    double resultado = 1.0;
    if (exponente > 0) {
        for (int i = 0; i < exponente; i++) {
            resultado *= base;
        }
    } else if (exponente < 0) {
        for (int i = 0; i < -exponente; i++) {
            resultado *= base;
        }
        resultado = 1.0 / resultado;
    }
    // Si exponente es 0, el resultado es 1.
    return resultado;
}

//**************************************************************************/
//**************************************************************************/

double Redondea(double num, int num_decimales) 
{
    //Desplazar la coma num_decimales + 1 posiciones a la derecha y truncar
    int truncado = num * Potencia(10, num_decimales + 1);
    truncado = fabs(truncado);  //Pasar a valor absoluto para evitar fallos 
    double redondeado;

    if ((truncado % 10) >= 5) {
        //Si la ultima cifra >= 5, aumentar uno a la penultima cifra
        truncado /= 10;
        truncado += 1;
        //Llevar la coma a la posicion original
        redondeado = truncado / Potencia(10, num_decimales);
    } else {
        //Si la ultima cifra < 5, llevar la coma a la posicion original
        truncado /= 10;
        redondeado = truncado / Potencia(10, num_decimales);
    }

    if (num < 0) redondeado *= -1;  //Si num era negativo, volver a ponerle el -

    return redondeado;  //Devolver el numero redondeado
}

//**************************************************************************/
//**************************************************************************/

double Trunca(double num, int num_decimales) 
{
    //Desplazar la coma num_decimales posiciones a la derecha y truncar
    int truncado_sin_coma = num * Potencia(10, num_decimales); 
    double redondeado;

    //LLevar la coma a la posicion original
    double truncado = truncado_sin_coma / Potencia(10, num_decimales);

    return truncado;
}

//**************************************************************************/
//**************************************************************************/

int main() {
    int opcion;
    double numero;
    int decimales;

    cout.setf(ios::fixed);
    cout.setf(ios::showpoint); 

    do {
        //Menu para seleccionar la funcion a usar
        cout << "\n--- MENU DE OPERACIONES ---" << endl;
        cout << "1. Redondear un numero" << endl;
        cout << "2. Truncar un numero" << endl;
        cout << "0. Salir" << endl;
        cout << "---------------------------" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        if (opcion == 1 || opcion == 2) {
            
            //Pedir el numero
            cout << "Introduzca el numero: ";
            cin >> numero;

            //Pedir el numero de decimales >= 0
            do {    
                cout << "Introduzca el numero de decimales (>= 0): ";
                cin >> decimales;
            } while (decimales < 0);

            cout << "===========================================" << endl;

            if (opcion == 1) {  //Redondear e imprimir el resultado
                
                double resultado_redondeado = Redondea(numero, decimales);
                cout << "Numero redondeado a " << decimales << " decimales: " 
                     << setprecision(decimales) << resultado_redondeado << endl;

            } else {    //Truncar e imprimir el resultado
                
                double resultado_truncado = Trunca(numero, decimales);
                cout << "Numero truncado a " << decimales << " decimales: " << 
                     setprecision(decimales) << resultado_truncado << endl;
            }
        } else if (opcion == 0) {   //Mensaje de finalización
            cout << "===========================================" << endl;
            cout << "Programa finalizado." << endl;
        } else {    //Error si se introduce un numero fuera de (0, 2, 3)
            cout << "===========================================" << endl;
            cout << "ERROR: Opcion no valida." << endl;
        }
        cout << "===========================================" << endl;
    } while (opcion != 0);

    return 0;
}

//**************************************************************************/
//**************************************************************************/