/***************************************************************************
// FUNDAMENTOS DE PROGRAMACION
//
// MARIO MARTINEZ CALLEJON
//
// SESION 08
/*
    Este programa proporciona un conjunto de funciones reutilizables para
    leer datos de tipo entero desde la entrada estándar, asegurando que
    cumplen con ciertos criterios de validación. Incluye:

        1. LeeEntero: Lee cualquier número entero.

        2. LeeEnteroEnRango: Lee un entero que debe estar dentro de un rango
        específico [menor, mayor].

        3. LeeEnteroMayorOIgual: Lee un entero que debe ser mayor o igual a un
        valor de referencia.

    El programa principal (main) actúa como un menú de prueba para demostrar
    el funcionamiento de cada una de estas funciones.

    Entradas:
        - Opciones del menú y valores numéricos introducidos por el usuario.
    Salidas:
        - Mensajes de error en caso de entrada no válida y el número validado.
*/
//**************************************************************************/

#include <iostream>
#include <string>

using namespace std;

/***************************************************************************/
// Lee y valida un número entero introducido por el usuario.
// Parámetros: titulo, el mensaje que se muestra al usuario para pedir el dato.
// Devuelve: el número entero validado.
// PRE: ninguna.
/***************************************************************************/

int LeeEntero (string titulo){
    string num;
    bool num_ok = false;

    do {
        // Imprimir en pantalla el mensaje
        cout << titulo;
        
        //Pedir un valor del num
        cin >> num;

        // Comprobar que num es un entero
        num_ok = true;

        // Recorrer cada carácter del string
        for(int i = 0; i < num.length() && num_ok; i++){
            char char_actual = num.at(i);
        
            if (char_actual == '+' || char_actual == '-') {
                // El signo solo es válido al principio
                if (i != 0) {
                    num_ok = false; 
                }
            } else if(!isdigit(char_actual)){
                // Tiene que ser un digito
                num_ok = false; 
            }
        }

        //Imprimir el mensaje de error
        if (!num_ok) cout << "Error: Introduzca un entero." << endl << endl;

    } while (!num_ok);

    return stoi(num);
}

/***************************************************************************/
// Lee y valida un entero en un rango específico [menor, mayor].
// Parámetros: titulo, el mensaje que se muestra al usuario.
//             menor, el límite inferior del rango (incluido).
//             mayor, el límite superior del rango (incluido).
// Devuelve: el número entero validado dentro del rango.
// PRE: menor <= mayor.
/***************************************************************************/

int LeeEnteroEnRango (string titulo, int menor, int mayor) {
    string num_str;
    int num;
    bool num_ok = false;

    do {
        // Imprimir en pantalla el mensaje
        cout << titulo;
        
        //Pedir un valor del num
        cin >> num_str;

        // Comprobar que num es un entero dentro del rango
        num_ok = true;

        // Recorrer cada carácter del string
        for(int i = 0; i < num_str.length() && num_ok; i++){
            char char_actual = num_str.at(i);
        
            if (char_actual == '+' || char_actual == '-') {
                // El signo solo es válido al principio
                if (i != 0) {
                    num_ok = false; 
                }
            } else if(!isdigit(char_actual)){
                // Tiene que ser un digito
                num_ok = false; 
            }
        }
        // Convertit a entero una vez comprobado que no dará error
        num = stoi(num_str);
        if (num < menor || num > mayor) {
            num_ok = false;
        }

        //Imprimir el mensaje de error
        if (!num_ok) cout << "Error: Introduzca un entero dentro del rango "
                          "[" << menor << ", " << mayor << "]." << endl << endl;

    } while (!num_ok);

    return num;
}

/***************************************************************************/
// Lee y valida un entero que debe ser mayor o igual a un valor de referencia.
// Parámetros: titulo, el mensaje que se muestra al usuario.
//             referencia, el valor mínimo que puede tomar el entero (incluido).
// Devuelve: el número entero validado.
// PRE: ninguna.
/***************************************************************************/

int LeeEnteroMayorOIgual (string titulo, int referencia) {
    string num_str;
    int num;
    bool num_ok = false;

    do {
        // Imprimir en pantalla el mensaje
        cout << titulo;
        
        //Pedir un valor del num
        cin >> num_str;

        // Comprobar que num es un entero dentro del rango
        num_ok = true;

        // Recorrer cada carácter del string
        for(int i = 0; i < num_str.length() && num_ok; i++){
            char char_actual = num_str.at(i);
        
            if (char_actual == '+' || char_actual == '-') {
                // El signo solo es válido al principio
                if (i != 0) {
                    num_ok = false; 
                }
            } else if(!isdigit(char_actual)){
                // Tiene que ser un digito
                num_ok = false; 
            }
        }
        // Convertit a entero una vez comprobado que no dará error
        num = stoi(num_str);
        if (num < referencia) {
            num_ok = false;
        }

        //Imprimir el mensaje de error
        if (!num_ok) cout << "Error: Introduzca un entero mayor o igual que "
                          << referencia << "." << endl << endl;

    } while (!num_ok);

    return num;
}

/***************************************************************************/
// Función main que muestra un menú para probar las funciones de lectura
// de enteros.
/***************************************************************************/

int main() {
    // Variable para almacenar la opción del menú seleccionada por el usuario.
    int opcion;

    // Bucle principal que se ejecuta hasta que el usuario elija la opción 0.
    do {
        // Mostrar el menú de opciones en la consola.
        cout << "\n--- MENU DE FUNCIONES ---" << endl;
        cout << "1. Probar LeeEntero" << endl;
        cout << "2. Probar LeeEnteroEnRango" << endl;
        cout << "3. Probar LeeEnteroMayorOIgual" << endl;
        cout << "0. Salir" << endl;
        cout << "------------------------" << endl;
        
        // Leer la opción del menú, validando que esté entre 0 y 3.
        opcion = LeeEnteroEnRango("Seleccione una opcion: ", 0, 3);
        cout << endl;

        // Ejecutar el bloque de código correspondiente a la opción elegida.
        switch (opcion) {
            case 1: {
                int numero = LeeEntero("Introduzca un entero cualquiera: ");
                cout << "\nNumero leido correctamente: " << numero << endl;
                break;
            }
            case 2: {
                int menor = LeeEntero("Introduzca el limite inferior del "
                                      "rango: ");
                int mayor = LeeEntero("Introduzca el limite superior del "
                                      "rango: ");
                // Validar que el rango sea coherente.
                if (menor > mayor) {
                    cout << "Error: el limite inferior no puede ser mayor que "
                            "el superior." << endl;
                } else {
                    int numero = LeeEnteroEnRango("Introduzca un entero en el "
                                                  "rango: ", menor, mayor);
                    cout << "\nNumero leido correctamente: " << numero << endl;
                }
                break;
            }
            case 3: {
                int referencia = LeeEntero("Introduzca el valor de referencia "
                                           "(el numero debe ser >=): ");
                int numero = LeeEnteroMayorOIgual("Introduzca un entero: ", 
                                                  referencia);
                cout << "\nNumero leido correctamente: " << numero << endl;
                break;
            }
            case 0: {
                // Mensaje de despedida al salir del programa.
                cout << "\nPrograma finalizado" << endl;
                break;
            }
        }

    } while (opcion != 0);

    return 0;
}