/***************************************************************************/
// FUNDAMENTOS DE PROGRAMACION
//
// MARIO MARTINEZ CALLEJON
//
// SESION 09
/*
    Programa que pide rellenar dos arrays con números enteros positivos. 
    La entrada de datos para cada array termina cuando se introduce un cero.

    Para cada array, calcula y muestra la media de sus valores.
    Finalmente, compara si los dos arrays son idénticos (mismos
    valores en el mismo orden) y muestra el resultado.

    Entradas:
        - Series de enteros positivos para cada uno de los dos arrays.

    Salidas:
        - Valor medio de los elementos de cada array.
        - Mensaje indicando si los dos arrays son iguales.
*/
/***************************************************************************/

#include <iostream>

using namespace std;

/***************************************************************************/
/*
    Rellena un array con enteros positivos introducidos por el usuario.
    La entrada de datos se detiene cuando se introduce un cero o se alcanza
    el tamaño máximo del array.
    Parámetros:
        array:  El array a rellenar.
        utiles: Variable que almacena el número de posicoines útiles.
        TOPE:   El tamaño máximo del array.

    Devuelve:
        Nada. El array y los útiles se modifican directamente.
*/
/***************************************************************************/
void RellenarArray(int array[], int &utiles, const int TOPE) {
    int numero;
    utiles = 0; // Iniciar el contador de elementos útiles a 0

    //Lectura anticipada
    cin >> numero;

    //Rellenar el array mientra el numero sea distinto de 0
    while (numero != 0 && utiles < TOPE) {
        //Procesar el numero y guardar el numero de posiciones utilizadas
        if (numero > 0) {
            array[utiles] = numero;
            utiles++;
        } else {
            cout << "Por favor, introduzca solo números positivos." << endl;
        }

        //Nueva lectura
        cin >> numero;
    }
}

/***************************************************************************/
/*
    Calcula el valor medio de los elementos de un array de enteros.
    Parámetros:
        array:  El array de enteros.
        utiles: El número de elementos útiles en el array.

    Devuelve:
        Un double con el valor medio. Si el array está vacío, devuelve 0.
*/
/***************************************************************************/
double CalcularMedia(int array[], int utiles) {
    double suma = 0;   //Almacena la suma de todos los numeros
    double media;

    if (utiles != 0) {
        //Si el array no está vacío, suma los numeros 
        for (int i = 0; i < utiles; i++){
            suma += array[i];
        }
        media = suma / utiles;  //Calcular la media

    } else {
        media = 0;  //Si no hay numeros la media es 0
    }

    return media;   //Devolver la media
}
/***************************************************************************/
/*
    Compara dos arrays para determinar si son idénticos en contenido y orden.
    Parámetros:
        array1:  El primer array a comparar.
        utiles1: El número de elementos útiles en el primer array.
        array2:  El segundo array a comparar.
        utiles2: El número de elementos útiles en el segundo array.

    Devuelve:
        Un bool: true si los arrays son idénticos, false en caso contrario.
*/
/***************************************************************************/
bool ArraysIguales(int array1[], int utiles1, int array2[], int utiles2) {
    bool iguales = true;

    if (utiles1 != utiles2) {
        iguales = false;
    } else {
        //Comprobar número a número si son iguales
        for (int i = 0; (i < utiles1) && (iguales == true); i++) {

            //Si son distintos, iguales = false
            if (array1[i] != array2[i]) iguales = false;
        }
    }
    return iguales; //Devolver si son iguales
}

/***************************************************************************/
/***************************************************************************/

int main() {
    const int TOPE = 100; // Tamaño máximo para los arrays
    int array1[TOPE], array2[TOPE];
    int utiles1 = 0, utiles2 = 0;

    cout << "Todos los valores deben ser enteros positivos (0 para finalizar)"
         << endl << endl;

    // Rellenar y procesar el primer array
    cout << "--- Introduzca los valores del primer array ---" << endl;
    RellenarArray(array1, utiles1, TOPE);

    // Rellenar y procesar el segundo array
    cout << "\n--- Introduzca los valores del segundo array ---" << endl;
    RellenarArray(array2, utiles2, TOPE);

    // Calcular y mostrar las medias
    cout << "-------------------------------" << endl;
    cout << "Media del primer array: " << CalcularMedia(array1, utiles1)
         << endl;

    cout << "Media del segundo array: " << CalcularMedia(array2, utiles2)
         << endl;
    cout << "-------------------------------" << endl;

    // Comparar los dos arrays
    
    if (ArraysIguales(array1, utiles1, array2, utiles2)){
        cout << "Los dos arrays son iguales." << endl;
    } else {
        cout << "Los dos arrays NO son iguales." << endl;
    }
    cout << "-------------------------------" << endl;

    return 0;
}

/***************************************************************************/
/***************************************************************************/