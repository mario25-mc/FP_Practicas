/***************************************************************************
// FUNDAMENTOS DE PROGRAMACION
//
// MARIO MARTINEZ CALLEJON
//
// SESION 07
/*
    Analizador de la Conjetura de Collatz.

    Este programa calcula y analiza las secuencias de Collatz para un rango
    de n�meros enteros positivos definidos por el usuario. Para cada n�mero
    en el rango, imprime su secuencia completa y la longitud de la misma.
    Finalmente, informa cu�l fue el n�mero (base) que gener� la secuencia
    m�s larga dentro de ese rango y cu�l fue dicha longitud.

    Entradas:
        - uno: Un n�mero entero positivo.
        - otro: Otro n�mero entero positivo.

    Salidas:
        - La secuencia de Collatz y su longitud para cada n�mero en el rango.
        - La longitud m�xima encontrada y el n�mero base que la gener�.
*/
//**************************************************************************/
#include <iostream>

using namespace std;

//Declaraci�n de funciones
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

    // Determinar el rango de n�meros a procesar.
    int minimo = Min(uno, otro);
    int maximo = Max(uno, otro);

    // Variables para almacenar el resultado de la b�squeda
    int longitud_max = 0;
    int base_longitud_max = 0;

    // Iterar a trav�s de cada n�mero en el rango especificado.
    for (int i = minimo; i <= maximo; i++) {
        // Procesar la secuencia para el n�mero actual y obtener su longitud.
        int longitud_actual = ProcesarCollatz(i);

        //Guardar la longitud m�xima hasta ahora y su base
        if (longitud_actual > longitud_max){
            longitud_max = longitud_actual;
            base_longitud_max = i;
        }
    }

    // Muestra el resultado final de la b�squeda.
    cout << "Longitud maxima = " << longitud_max << endl;
    cout << "Base = " << base_longitud_max << endl;

    return 0;
}

//**************************************************************************/
//**************************************************************************/

int Max(int a, int b)
{
    return (a > b)? a : b;  //Devolver el mayor n�mero
}

//**************************************************************************/
//**************************************************************************/

int Min(int a, int b)
{
    return (a < b)? a : b;  //Devolver el menor n�mero
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

    // Sumar uno a la longitud por cada t�rmino de la secuencia
    while (n != 1) {
        longitud++;
        n = SiguienteCollatz(n);
    }
    longitud++; // Contar el �ltimo n�mero de la secuencia (el '1').

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