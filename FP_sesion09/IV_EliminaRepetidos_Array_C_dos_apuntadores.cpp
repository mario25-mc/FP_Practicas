/***************************************************************************/
// FUNDAMENTOS DE PROGRAMACION
//
// MARIO MARTINEZ CALLEJON
//
// SESION 09
/*
    Programa que lee una serie de números positivos (hasta 50) y los
    almacena en un array. La lectura termina al introducir un número negativo.

    A continuación, elimina los valores repetidos del array utilizando el 
    método de dos apuntadores y lo imprime en la consola.

    Entradas:
        - Serie de números enteros positivos.

    Salidas:
        - El array original y el array sin repetidos.
*/
/***************************************************************************/

#include <iostream>

using namespace std;

/***************************************************************************/
/*
    Busca un valor en las primeras posiciones indicadas de un array.

    Parámetros:
        array:  El array donde buscar.
        utiles: El número de elementos a considerar en la búsqueda.
        valor:  El valor que se busca.

    Devuelve:
        true si el valor se encuentra, false en caso contrario.
*/
/***************************************************************************/

bool Contiene(const int array[], int utiles, int valor) {
    bool contiene = false;

    for (int i = 0; (!contiene) && ( i < utiles); ++i) {
        if (array[i] == valor) {
            contiene = true;
        }
    }

    return contiene;
}

/***************************************************************************/
/*
    Muestra los primeros "utiles" elementos de un array.

    Parámetros:
        mensaje: Mensaje a mostrar antes de imprimir el array.
        array:   El array a imprimir.
        utiles:  El número de elementos a mostrar.
*/
/***************************************************************************/
void MostrarArray(const char* mensaje, const int array[], int utiles) {
    cout << mensaje;
    for (int i = 0; i < utiles; ++i) {
        cout << array[i] << " ";
    }
    cout << endl;
}

/***************************************************************************/
/*
    Elimina los elementos duplicados de un array en el sitio, usando el
    método de dos apuntadores. Recorre el array con un apuntador de lectura y 
    escribe los elementos sin repetir en una posición marcada por el apuntador 
    pos_escritura.

    Parámetros:
        datos:  El array que será modificado.
        utiles: Referencia al número de elementos útiles, que se actualizará.
*/
/***************************************************************************/
void EliminaRepetidos(int datos[], int &utiles) {
    if (utiles != 0){

        int pos_escritura = 1;

        // Agrupar todos los números sin repetir al inicio del string
        for (int pos_lectura = 1; pos_lectura < utiles; pos_lectura++) {
            
            if (!Contiene(datos, pos_escritura, datos[pos_lectura])) {
                // Si el elemento no había aparecido antes, se copia en la 
                // posición de escritura
                datos[pos_escritura] = datos[pos_lectura];
                
                pos_escritura++;    //Desplazar el apuntador de escritura
            }
        }
        // Actualizar el número de elementos útiles
        utiles = pos_escritura;
    }   
}

/***************************************************************************/
/***************************************************************************/

int main() {
    const int TOPE = 50;    // Tamaño máximo del array
    int datos[TOPE];        // Array que almacena los números
    int utiles = 0;         // Variable que cuenta las posiciones usadas

    // Lectura de datos
    cout << "Introduzca numeros positivos (negativo para terminar):" << endl;
    int numero;

    // Lectura anticipada
    cin >> numero;

    // Rellenar el array
    while (numero >= 0 && utiles < TOPE) {
        datos[utiles] = numero;
        utiles++;
        cin >> numero;
    }

    if (utiles == 0) {
        cout << "No se introdujeron datos." << endl;
    } else {
        //Mostrar array original
        cout << "\n-------------------------------------------------" << endl;
        MostrarArray("Array Original: ", datos, utiles);
        cout << "-------------------------------------------------" << endl;

        // Mostrar los resultados
        EliminaRepetidos(datos, utiles);
        MostrarArray("Array sin repeticiones: ", datos, utiles);

        cout << "-------------------------------------------------" << endl;
    }

    return 0;
}

/***************************************************************************/
/***************************************************************************/