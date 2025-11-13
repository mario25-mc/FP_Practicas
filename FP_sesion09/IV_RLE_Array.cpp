/***************************************************************************/
// FUNDAMENTOS DE PROGRAMACION
//
// MARIO MARTINEZ CALLEJON
//
// SESION 09
/*
    Programa que realiza la codificación y decodificación RLE de una secuencia 
    de datos almacenada en un array.

    El programa realiza los siguientes pasos:
    1. Parte de una secuencia original predefinida.
    2. Codifica la secuencia en un array de parejas (valor, repeticiones).
    3. Decodifica el array de parejas para reconstruir la secuencia.
    4. Compara la secuencia original con la reconstruida para verificar.

    El tipo de dato de la secuencia se puede cambiar mediante un typedef.
*/
/***************************************************************************/

#include <iostream>

using namespace std;

// Definir el tipo de valor para la secuencia.
typedef char TipoValor;

// Constantes para el tamaño máximo de los arrays
const int NUM_MAX_VALORES = 100;
const int NUM_MAX_PAREJAS = 100;

// Estructura para almacenar una pareja en RLE.
struct Pareja {
    TipoValor valor; 
    int veces;       
};

/***************************************************************************/
/*
    Codifica una secuencia usando RLE.

    Parámetros:
        original:      Array con la secuencia original.
        utiles_orig:   Número de elementos en la secuencia original.
        codificada:    Array donde se guardará el resultado codificado.
        utiles_codif:  Referencia al número de parejas en el array codificado.
*/
/***************************************************************************/
void CodificarRLE(const TipoValor original[], int utiles_orig,
                  Pareja codificada[], int &utiles_codif) 
{
    // Se inicializa el numero de posiciones del array codificado a cero.
    utiles_codif = 0;
    // Si la secuencia original está vacía, no hay nada que codificar.
    if (utiles_orig != 0) 
    {
        // Se toma el primer valor como el valor actual y se inicia el contador.
        TipoValor valor_actual = original[0];
        int contador = 1;

        // Se recorre la secuencia original desde el segundo elemento.
        for (int i = 1; i < utiles_orig; ++i) {
            TipoValor valor_siguiente = original[i];

            if (valor_siguiente == valor_actual) {
                // Si el valor se repite se incrementa el contador.
                contador++;
            } else {
                // Si el valor cambia, se guarda la pareja de la serie anterior.
                codificada[utiles_codif].valor = valor_actual;
                codificada[utiles_codif].veces = contador;
                utiles_codif++;

                // Se empieza una nueva serie con el nuevo valor.
                valor_actual = valor_siguiente;
                contador = 1;
            }
        }

        // Se añade la última pareja al array codificado.
        codificada[utiles_codif].valor = valor_actual;
        codificada[utiles_codif].veces = contador;
        utiles_codif++;
    }
}

/***************************************************************************/
/*
    Descodifica una secuencia RLE.

    Parámetros:
        codificada:       Array con las parejas codificadas.
        utiles_codif:     Número de parejas en el array codificado.
        reconstruida:     Array donde se guardará la secuencia reconstruida.
        utiles_reconst:   Referencia al número de elementos reconstruidos.
*/
/***************************************************************************/
void DescodificarRLE(const Pareja codificada[], int utiles_codif,
                     TipoValor reconstruida[], int &utiles_reconst) 
{
    // Se inicializa el número de posiciones usadas del array nuevo a 0
    utiles_reconst = 0;

    // Se recorre cada pareja del array codificado.
    for (int i = 0; i < utiles_codif; ++i) {

        // Para cada pareja, se añade el 'valor' a la secuencia reconstruida
        // tantas 'veces' como indique la pareja.
        for (int j = 0; j < codificada[i].veces; ++j) {

            if (utiles_reconst < NUM_MAX_VALORES) { // Control de desbordamiento
                reconstruida[utiles_reconst] = codificada[i].valor;
                utiles_reconst++;
            }

        }
    }
}

/***************************************************************************/
/*
    Compara dos secuencias para ver si son idénticas.

    Parámetros:
        sec1:      Primer array a comparar.
        utiles1:   Tamaño del primer array.
        sec2:      Segundo array a comparar.
        utiles2:   Tamaño del segundo array.

    Devuelve:
        true si las secuencias son idénticas, false en caso contrario.
*/
/***************************************************************************/
bool SecuenciasIguales(const TipoValor sec1[], int utiles1,
                        const TipoValor sec2[], int utiles2) 
{
    bool iguales = true;
    // Si las secuencias tienen diferente longitud no pueden ser iguales.
    if (utiles1 != utiles2) {
        iguales = false;
    }
    // Se recorren las secuencias elemento por elemento.
    for (int i = 0; i < utiles1 && iguales; ++i) {
        if (sec1[i] != sec2[i]) {
            // Si se encuentra un elemento diferente se devuelve false.
            iguales = false;
        }
    }
    return iguales;
}

/***************************************************************************/
/*
    Muestra una secuencia de valores en la consola.

    Parámetros:
        sec:    Array con la secuencia a mostrar.
        utiles: Número de elementos a mostrar del array.
*/
/***************************************************************************/
void MostrarSecuencia(const TipoValor sec[], int utiles) 
{
    cout << "{ " << sec[0];

    //Imprimir valor a valor
    for (int i = 1; i < utiles; i++) {
        cout << ", " << sec[i];
    }
    cout << " }";
}

/***************************************************************************/
/*
    Muestra una secuencia de parejas (RLE) en la consola.

    Parámetros:
        sec:    Array con las parejas a mostrar.
        utiles: Número de parejas a mostrar del array.
*/
/***************************************************************************/
void MostrarParejas(const Pareja sec[], int utiles) 
{
    //Recorrer el array e imprimir pareja a pareja
    for (int i = 0; i < utiles; ++i) {
        cout << "[" << sec[i].veces << ","
             << sec[i].valor << "] ";
    }
}

/***************************************************************************/
/***************************************************************************/

int main() {
    // Datos de entrada
    TipoValor s_original[NUM_MAX_VALORES] = 
        {'a', 'a', 'a', 'b', 'd', 'd', 'e', 'e', 'e', 'e',
         'e', 'e', 'd', 'd', 's', 's', 's', 's', 's', 'a'};
    int tamanio_s_original = 20;

    // Arrays para los resultados
    Pareja s_codificada[NUM_MAX_PAREJAS];
    int num_parejas = 0;

    TipoValor s_reconstruida[NUM_MAX_VALORES];
    int tamanio_s_reconstruida = 0;

    // Mostrar secuencia original
    cout << "Secuencia original: " << endl;
    MostrarSecuencia(s_original, tamanio_s_original);
    cout << endl << endl;

    // a) Codificar
    CodificarRLE(s_original, tamanio_s_original, s_codificada, num_parejas);

    cout << "a) Secuencia codificada (RLE):" << endl;
    MostrarParejas(s_codificada, num_parejas);  
    cout << endl << endl;

    // b) Descodificar
    
    DescodificarRLE(s_codificada, num_parejas, s_reconstruida, 
                    tamanio_s_reconstruida);

    cout << "b) Secuencia reconstruida:" << endl;
    MostrarSecuencia(s_reconstruida, tamanio_s_reconstruida);
    cout << endl << endl;

    // c) Comparar
    cout << "c) Verificacion: ";
    if (SecuenciasIguales(s_original, tamanio_s_original, s_reconstruida, 
                         tamanio_s_reconstruida)) {
        cout << "EXITO: Las secuencias original y reconstruida son iguales." 
             << endl;
    } else {
        cout << "FALLO: Las secuencias son diferentes." << endl;
    }

    return 0;
}

/***************************************************************************/
/***************************************************************************/