/***************************************************************************/
// FUNDAMENTOS DE PROGRAMACION
//
// MARIO MARTINEZ CALLEJON
//
// SESION 09
/*
    Programa que lee dos secuencias de enteros ordenadas ascendentemente,
    las mezcla en un único array también ordenado y muestra el resultado.

    La entrada de datos para cada secuencia termina cuando el usuario
    introduce la palabra "FIN". El programa se asegura de que las secuencias
    introducidas estén ordenadas antes de proceder a la mezcla.

    Entradas:
        - Dos secuencias de enteros ordenados ascendentemente.
    Salidas:
        - La secuencia mezclada, también ordenada.
*/
/***************************************************************************/

#include <iostream>
#include <string>

using namespace std;

/***************************************************************************/
/*
    Comprueba si un array de enteros está ordenado de forma ascendente.
    Parámetros:
        arr:    Array de enteros a comprobar.
        utiles: Número de elementos útiles en el array.
    Devuelve:
        true si el array está ordenado, false en caso contrario.
*/
/***************************************************************************/

bool Ordenado(int arr[], int utiles)
{
    bool ordenado = true;

    // El bucle se detiene si llega al final o si encuentra un par de
    // elementos que no están en orden.
    for (int i = 0; (i < utiles - 1) && ordenado; i++) 
    {
        // Si un elemento es mayor que el siguiente, no está ordenado.
        if (arr[i] > arr[i+1]) {
            ordenado = false;
        }
    }

    if (!ordenado) {
        cout << "El array no esta ordenado." << endl;
    }

    return ordenado;
}

/***************************************************************************/
/*
    Mezcla dos arrays ordenados en un tercer array, manteniendo el orden.
    Parámetros:
        arr1:       Primer array ordenado.
        utiles1:    Número de elementos en arr1.
        arr2:       Segundo array ordenado.
        utiles2:    Número de elementos en arr2.
        mezcla:     Array de destino para la mezcla. Se modifica.
*/
/***************************************************************************/

void Mezclar(int arr1[], int utiles1, int arr2[], int utiles2, int mezcla[])
{   
    // Índices para recorrer cada uno de los tres arrays.
    int actual_1 = 0;     
    int actual_2 = 0;
    int actual_mezcla = 0;

    mezcla[0] = 0;  // Si los arrays están vacíos la mezcla será {0}
    
    // Bucle principal: se ejecuta mientras queden elementos en ambos arrays.
    while ((actual_1 < utiles1) && (actual_2 < utiles2))
    {
        // Compara los elementos actuales de cada array y copia el menor.
        if (arr1[actual_1] < arr2[actual_2])
        {
            mezcla[actual_mezcla] = arr1[actual_1];
            actual_1++;
        } else 
        {
            mezcla[actual_mezcla] = arr2[actual_2];
            actual_2++;
        }
        // Avanza al siguiente hueco en el array de mezcla.
        actual_mezcla++;
    }

    // Copiar los elementos restantes de arr1, si los hay.
    while (actual_1 < utiles1) 
    {
        mezcla[actual_mezcla] = arr1[actual_1];
        actual_1++;
        actual_mezcla++;
    }
    // Copiar los elementos restantes de arr2, si los hay.
    while (actual_2 < utiles2) 
    {
        mezcla[actual_mezcla] = arr2[actual_2];
        actual_2++;
        actual_mezcla++;
    }
}

/***************************************************************************/
/*
    Muestra una secuencia de enteros en la consola.
    Parámetros:
        arr:    Array de enteros a mostrar.
        utiles: Número de elementos a mostrar.
*/
/***************************************************************************/
void MostrarSecuencia(int arr[], int utiles) 
{
    cout << "{";
    if (utiles > 0) {
        cout << " " << arr[0];

        //Imprimir valor a valor
        for (int i = 1; i < utiles; i++) {
            cout << ", " << arr[i];
        }
        cout << " ";
    }

    cout << " }";
}

/***************************************************************************/
/***************************************************************************/

int main(){
    // Constantes para la capacidad máxima de los arrays.
    const int CAPACIDAD1 = 50;
    const int CAPACIDAD2 = 50;

    // Declaración de los arrays y sus variables de útiles.
    int v1[CAPACIDAD1], v2[CAPACIDAD2], mezcla[CAPACIDAD1 + CAPACIDAD2];
    int utiles1, utiles2, utiles_mezcla;

    // Bucle para leer la primera secuencia. Se repite si no está ordenada.
    do {
        cout << endl;
        cout << "Introduzca la primera secuencia (FIN para terminar):" << endl;

        utiles1 = 0;

        // Lectura anticipada
        string entrada;
        cin >> entrada;

        // Rellena el array hasta que se introduce "FIN" o se llena.
        while (entrada != "FIN" && utiles1 < CAPACIDAD1){
            v1[utiles1] = stoi(entrada);
            utiles1++;
            cin >> entrada;
        }
    } while (!Ordenado(v1, utiles1));

    // Bucle para leer la segunda secuencia. Se repite si no está ordenada.
    do {
        cout << endl;
        cout << "Introduzca la segunda secuencia (FIN para terminar):" << endl;

        utiles2 = 0;

        // Lectura anticipada
        string entrada;
        cin >> entrada;

        // Rellena el array hasta que se introduce "FIN" o se llena.
        while (entrada != "FIN" && utiles2 < CAPACIDAD2){
            v2[utiles2] = stoi(entrada);
            utiles2++;
            cin >> entrada;
        }
    } while (!Ordenado(v2, utiles2));

    // Calcula el tamaño final del array mezclado.
    utiles_mezcla = utiles1 + utiles2;

    // Llama a la función para mezclar los dos arrays.
    Mezclar(v1, utiles1, v2, utiles2, mezcla);

    // Muestra el resultado final.
    cout << "-------------------------------------------------" << endl;
    cout << "Secuencia mezclada: " << endl;
    MostrarSecuencia(mezcla, utiles_mezcla);
    
    return 0;
}

/***************************************************************************/
/***************************************************************************/