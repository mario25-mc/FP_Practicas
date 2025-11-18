/***************************************************************************/
// FUNDAMENTOS DE PROGRAMACION
//
// MARIO MARTINEZ CALLEJON
//
// SESION 10
/*
    Programa para asignar asientos de pasajeros en un avión.

    El programa muestra un mapa de asientos de un avión (10 filas, 4 columnas).
    Los asientos disponibles se marcan con '.' y los ocupados con 'X'.

    El programa pide al usuario que introduzca un asiento.
    Si el asiento es válido y está libre, lo marca como ocupado. Si está ocupado
    o la entrada no es válida, muestra un mensaje de error.

    El proceso se repite hasta que todos los asientos están asignados o hasta
    que el usuario introduce "-1" para terminar.

    Entradas:
        - Asiento deseado en formato "filaLetra" (p. ej., "3B").
        - "-1" para finalizar el programa.

    Salidas:
        - Mapa de asientos actualizado tras cada reserva.
        - Mensajes de estado (confirmación, error).
*/
/***************************************************************************/

#include <iostream>
#include <string>

using namespace std;

const int MAX_FILAS = 10;
const int MAX_COLUMNAS = 4;

/***************************************************************************/
/*
    Convierte la entrada del usuario a indices de la matriz.
    Valida que el formato sea correcto y que el asiento este dentro de los
    limites del avion.

    Parámetros:
        entrada: La cadena introducida por el usuario (string).
        fila:    Referencia a un entero donde se guarda el indice de la fila
        columna: Referencia a un entero donde se guarda el indice de la columna

    Devuelve:
        true si la entrada es valida y se pudo procesar, false en caso contrario
*/
/***************************************************************************/
bool ProcesarAsiento(string entrada, int &fila, int &columna) {
    // Extraer número de fila y letra de columna
    int num_fila;
    char letra_col;
    
    num_fila = stoi(entrada.substr(0, entrada.length() - 1));
    letra_col = entrada.at(entrada.length() - 1);

    // Convertir a índices de la matriz
    fila = num_fila - 1;
    columna = toupper(letra_col) - 'A';

    // Validar que los índices estén en el rango correcto
    return (fila >= 0 && fila < MAX_FILAS && columna >= 0 && 
            columna < MAX_COLUMNAS);
}

/***************************************************************************/

int main() {
    const int NUM_ASIENTOS = MAX_FILAS * MAX_COLUMNAS;
    char mapa_asientos[MAX_FILAS][MAX_COLUMNAS];
    int ocupados = 0;

    // Inicializar todos los asientos como disponibles ('.')
    for (int i = 0; i < MAX_FILAS; i++) {
        for (int j = 0; j < MAX_COLUMNAS; j++) {
            mapa_asientos[i][j] = '.';
        }
    }

    string asiento_str;
    do {
        // Mostrar el mapa de asientos (lógica integrada en main)
        cout << "\n   A B C D" << endl;
        cout << "  ---------" << endl;
        for (int i = 0; i < MAX_FILAS; i++) {
            // Imprimir número de fila (con formato para alinear)
            if (i + 1 < 10) {
                cout << " " << i + 1 << "|";
            } else {
                cout << i + 1 << "|";
            }
            // Imprimir estado de los asientos
            for (int j = 0; j < MAX_COLUMNAS; j++) {
                cout << mapa_asientos[i][j] << " ";
            }
            cout << endl;
        }
        cout << "  ---------" << endl;
        cout << "   A B C D" << endl << endl;

        cout << "Introduzca asiento o -1 para salir: ";
        cin >> asiento_str;

        if (asiento_str != "-1") {
            int fila, col;
            if (ProcesarAsiento(asiento_str, fila, col)) {
                if (mapa_asientos[fila][col] == '.') {
                    mapa_asientos[fila][col] = 'X';
                    ocupados++;
                    cout << "--> Asiento " << asiento_str << " reservado." 
                         << endl;
                } else {
                    cout << "--> ERROR: El asiento " << asiento_str 
                         << " ya esta ocupado." << endl;
                }
            } else {
                cout << "--> ERROR: Asiento no valido."<< endl;
            }
        }

    } while (asiento_str != "-1" && ocupados < NUM_ASIENTOS);

    cout << "\n--- Fin del programa de reservas ---" << endl;
    // Mostrar el mapa de asientos final 
    cout << "\n   A B C D" << endl;
    cout << "  ---------" << endl;
    for (int i = 0; i < MAX_FILAS; i++) {
        if (i + 1 < 10) {
            cout << " " << i + 1 << "|";
        } else {
            cout << i + 1 << "|";
        }
        for (int j = 0; j < MAX_COLUMNAS; j++) {
            cout << mapa_asientos[i][j] << " ";
        }
        cout << endl;
    }
    cout << "  ---------" << endl;
    cout << "   A B C D" << endl << endl;

    return 0;
}

/***************************************************************************/