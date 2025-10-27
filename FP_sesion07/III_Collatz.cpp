/***************************************************************************
// FUNDAMENTOS DE PROGRAMACION
//
// MARIO MARTINEZ CALLEJON
//
// SESION 07
/*
    Analizador de la Conjetura de Collatz.

    Este programa calcula y analiza las secuencias de Collatz para un rango
    de números enteros positivos definidos por el usuario. Para cada número
    en el rango, imprime su secuencia completa y la longitud de la misma.
    Finalmente, informa cuál fue el número (base) que generó la secuencia
    más larga dentro de ese rango y cuál fue dicha longitud.

    Entradas:
        - uno: Un número entero positivo.
        - otro: Otro número entero positivo.

    Salidas:
        - La secuencia de Collatz y su longitud para cada número en el rango.
        - La longitud máxima encontrada y el número base que la generó.
*/
//**************************************************************************/
#include <iostream>

using namespace std;

//Declaración de funciones
int Max(int, int);
int Min(int, int);
int ProcesarCollatz(int);
int SiguienteCollatz(int);
int LongitudCollatz(int);
void ImprimirCollatz(int);

//**************************************************************************/
//**************************************************************************/

int main()
{   
    int uno, otro;
    
    // Entrada
    do {
        cout << "Introduzca un entero mayor que cero: ";
        cin >> uno;
    } while (uno <= 0);

    do {
        cout << "Introduzca otro entero mayor que cero: ";
        cin >> otro;
    } while (otro <= 0);
    
    cout << endl;

    // Determinar el rango de números a procesar.
    int minimo = Min(uno, otro);
    int maximo = Max(uno, otro);

    // Variables para almacenar el resultado de la búsqueda
    int longitud_max = 0;
    int base_longitud_max = 0;

    // Iterar a través de cada número en el rango especificado.
    for (int i = minimo; i <= maximo; i++) {
        // Procesar la secuencia para el número actual y obtener su longitud.
        int longitud_actual = ProcesarCollatz(i);

        //Guardar la longitud máxima hasta ahora y su base
        if (longitud_actual > longitud_max){
            longitud_max = longitud_actual;
            base_longitud_max = i;
        }
    }

    // Muestra el resultado final de la búsqueda.
    cout << "Longitud maxima = " << longitud_max << endl;
    cout << "Base = " << base_longitud_max << endl;

    return 0;
}

//**************************************************************************/
//**************************************************************************/

int Max(int a, int b)
{
    return (a > b)? a : b;  //Devolver el mayor número
}

//**************************************************************************/
//**************************************************************************/

int Min(int a, int b)
{
    return (a < b)? a : b;  //Devolver el menor número
}

//**************************************************************************/
//**************************************************************************/

int SiguienteCollatz(int n)
{
    // Aplicar la regla de Collatz: si n es par, n/2; si es impar, 3n+1.
    if (n % 2 == 0) {
        n /= 2;
    } else {
        n = n * 3 + 1;
    }

    return n;
}

//**************************************************************************/
//**************************************************************************/

int LongitudCollatz(int n) 
{
    int longitud = 0;

    // Sumar uno a la longitud por cada término de la secuencia
    while (n != 1) {
        longitud++;
        n = SiguienteCollatz(n);
    }
    longitud++; // Contar el último número de la secuencia (el '1').

    return longitud;
}

//**************************************************************************/
//**************************************************************************/

void ImprimirCollatz(int base) //Tomamos la base como n
{
    cout << "\tCollatz(" << base << ") = {";
    
    int actual = base;
    while (actual != 1) {
        cout << actual << ", ";     // Imprimir cada numero de la secuencia
        actual = SiguienteCollatz(actual);
    }

    cout << "1}. "; // Cerrar la secuencia
}

//**************************************************************************/
//**************************************************************************/

int ProcesarCollatz(int base) 
{   
    // Imprimir la secuencia y su longitud
    ImprimirCollatz(base);
    int longitud = LongitudCollatz(base);

    cout << "Longitud = " << longitud << endl << endl;

    return longitud;    // Devolver la longitud de la secuencia
}

//**************************************************************************/
//**************************************************************************/