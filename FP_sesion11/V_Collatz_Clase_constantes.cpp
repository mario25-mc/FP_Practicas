/***************************************************************************
// FUNDAMENTOS DE PROGRAMACION
//
// MARIO MARTINEZ CALLEJON
//
// SESION 10
/*
    Este programa calcula y analiza las secuencias de Collatz para un rango
    de números enteros positivos definidos por el usuario. Para cada número
    en el rango, se crea un objeto de la clase Collatz, imprime su
    secuencia y su longitud. Finalmente, informa cuál fue el número (base)
    que generó la secuencia más larga y cuál fue dicha longitud.

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

/***************************************************************************/
/*
    Devuelve el mayor de dos números enteros.
    Parámetros:
        a: Primer número entero.
        b: Segundo número entero.
    Devuelve:
        El valor más grande entre a y b.
*/
/***************************************************************************/
int Max(int a, int b);

/***************************************************************************/
/*
    Devuelve el menor de dos números enteros.
    Parámetros:
        a: Primer número entero.
        b: Segundo número entero.
    Devuelve:
        El valor más pequeño entre a y b.
*/
/***************************************************************************/
int Min(int a, int b);

/***************************************************************************/
// Definición de la clase Collatz
/***************************************************************************/
class Collatz {
private:
    const int base; // base de la sucesión
    // PRE: base >= 1

    //***********************************************************************/
    // Calcula el siguiente término en la secuencia de Collatz.
    // La regla es: si n es par, el siguiente es n/2; si es impar, es 3n+1.
    // Parámetros: n, El número actual en la secuencia.
    // Devuelve: El siguiente número en la secuencia de Collatz.
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

public:

    /***********************************************************************/
    // Constructor con parámetros.
    // PRE: b >= 1
    // Parámetros: b, la base de la secuencia de Collatz.
    Collatz(int b)
        : base(b)
    {}

    /***********************************************************************/
    // Consulta la base de la secuencia.
    // Devuelve: el valor de la base.
    int GetBase() {
        return base;
    }

    /***********************************************************************/
    // Calcula y devuelve la longitud de la secuencia.
    // Devuelve: el número de términos en la secuencia.
    int GetLongitud() {
        int longitud = 1;
        int actual = base;

        while (actual != 1) {
            actual = SiguienteCollatz(actual);
            longitud++;
        }
        return longitud;
    }

    /***********************************************************************/
    // Devuelve el término en la posición 'pos' de la secuencia.
    // PRE: pos >= 0
    // Parámetros:
    //   pos: la posición del término a obtener (0 es la base).
    // Devuelve: el valor del término en la posición dada.
    int GetTermino(int pos) {
        int termino = base;
        for (int i = 0; i < pos; ++i) {
            termino = SiguienteCollatz(termino);
        }
        return termino;
    }

    /***********************************************************************/
    // Imprime la secuencia completa de Collatz en la consola.
    void Imprimir() {
        cout << "\tCollatz(" << base << ") = {";

        int actual = base;
        while (actual != 1) {
            cout << actual << ", ";
            actual = SiguienteCollatz(actual);
        }

        cout << "1}. ";
    }
};

/***************************************************************************/
/***************************************************************************/

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
        // Crear un objeto Collatz para el número actual
        Collatz secuencia_actual(i);

        // Usar los métodos del objeto para imprimir y obtener la longitud
        secuencia_actual.Imprimir();
        int longitud_actual = secuencia_actual.GetLongitud();
        cout << "Longitud = " << longitud_actual << endl << endl;

        // Almacenar la longitud maxima y su base
        if (longitud_actual > longitud_max) {
            longitud_max = longitud_actual;
            base_longitud_max = i;
        }
    }

    // Muestra el resultado final de la búsqueda.
    cout << "Longitud maxima = " << longitud_max << endl;
    cout << "Base = " << base_longitud_max << endl;

    return 0;
}

/***************************************************************************/
/*
    Devuelve el mayor de dos números enteros.
    Parámetros:
        a: Primer número entero.
        b: Segundo número entero.
    Devuelve:
        El valor más grande entre a y b.
*/
/***************************************************************************/
int Max(int a, int b)
{
    return (a > b)? a : b;  //Devolver el mayor número
}

/***************************************************************************/
/*
    Devuelve el menor de dos números enteros.
    Parámetros:
        a: Primer número entero.
        b: Segundo número entero.
    Devuelve:
        El valor más pequeño entre a y b.
*/
/***************************************************************************/
int Min(int a, int b)
{
    return (a < b)? a : b;  //Devolver el menor número
}

//**************************************************************************/
//**************************************************************************/