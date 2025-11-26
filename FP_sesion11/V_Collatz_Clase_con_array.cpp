/***************************************************************************
// FUNDAMENTOS DE PROGRAMACION
//
// MARIO MARTINEZ CALLEJON
//
// SESION 10
/*
    Este programa calcula y analiza las secuencias de Collatz para un rango
    de números enteros positivos definidos por el usuario. Para cada número
    en el rango, se crea un objeto de la clase Collatz que almacena la
    secuencia en un vector privado, imprime su secuencia y su longitud. 
    Finalmente, informa cuál fue el número (base) que generó la secuencia más 
    larga y cuál fue dicha longitud.

    Entradas:
        - uno: Un número entero positivo.
        - otro: Otro número entero positivo.

    Salidas:
        - La secuencia de Collatz y su longitud para cada número en el rango.
        - La longitud máxima encontrada y el número base que la generó.
*/
//**************************************************************************/
#include <iostream>
#include <string>

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
    static const int TAMANIO = 200; // Número de casillas disponibles
    int vector_privado[TAMANIO];
    int total_utilizados;
    int base; // base de la sucesión, PRE: base >= 1

    /***********************************************************************/
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

    void Rellena() {
        int actual = base;
        int indice = 0;

        // Se deja un hueco al final por si la secuencia es muy larga
        // y hay que forzar la inclusión del 1.
        while ((actual != 1) && (indice < TAMANIO - 1)) {
            vector_privado[indice] = actual;
            indice++;
            actual = SiguienteCollatz(actual);
        }

        // Añadir el último término (siempre 1)
        vector_privado[indice] = 1;
        indice++;

        total_utilizados = indice;
    }

public:
    /***********************************************************************/
    // Constructor por defecto

    Collatz() {}

    /***********************************************************************/
    // Constructor con parámetros. 
    // PRE: n >= 1
    // Parámetros: n, el nuevo valor para la base.
    
    Collatz(int n)
        : base(n) 
    {
        Rellena();
    }

    /***********************************************************************/
    // Modifica el valor de la base y recalcula la secuencia
    // Parámetros: n, el nuevo valor de la base
    // PRE: n >= 1

    void SetBase(int n){
        base = n;
        Rellena();
    }

    /***********************************************************************/
    // Consulta la base de la secuencia.
    // Devuelve: el valor de la base.

    int GetBase() {
        return base;
    }

    /***********************************************************************/
    // Calcula y devuelve la longitud de la secuencia.
    // Devuelve: el número de términos en la secuencia.

    int Longitud() {
        return total_utilizados;
    }

    /***********************************************************************/
    // Devuelve el término en la posición 'pos' de la secuencia.
    // PRE: pos >= 0
    // Parámetros:
    //   pos: la posición del término a obtener (0 es la base).
    // Devuelve: el valor del término en la posición dada.

    int Valor(int pos) {
        // Obtener el valor en el índice indicado
        // NOTA: No se comprueba si pos es un índice válido.
        int termino = vector_privado[pos];
        return termino;
    }

    /***********************************************************************/
    // Pasa la secuencia de Collatz a un dato string.

    string ToString() {

        string collatz_s = "\tCollatz(" + to_string(base) + ") = {";

        for (int i = 0; i < total_utilizados; i++) {
            collatz_s += to_string(vector_privado[i]);
            if (i < total_utilizados - 1) {
                collatz_s += ", ";
            }
        }

        collatz_s += "}.";

        // Si la secuencia se cortó porque alcanzó el tamaño máximo
        // y el último término no es 1, se añade un mensaje de error.
        if (total_utilizados == TAMANIO && 
            vector_privado[total_utilizados - 1] != 1){
            collatz_s += " (secuencia demasiado larga)";
        }
        return collatz_s;
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
        string secuencia = secuencia_actual.ToString();
        int longitud_actual = secuencia_actual.Longitud();

        cout << secuencia << " Longitud = " << longitud_actual << endl << endl;

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