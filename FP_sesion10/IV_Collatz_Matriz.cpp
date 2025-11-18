/***************************************************************************
// FUNDAMENTOS DE PROGRAMACION
//
// MARIO MARTINEZ CALLEJON
//
// SESION 10
/*
    Analizador de la Conjetura de Collatz con almacenamiento en matriz.

    Este programa lee dos enteros positivos que definen un rango. Calcula
    y almacena todas las secuencias de Collatz para los números en ese
    rango dentro de una matriz bidimensional.

    Cada fila de la matriz guarda una secuencia. La ocupación de cada fila
    es variable, por lo que se gestiona como una matriz "a jirones".

    Después de generar y almacenar las secuencias, el programa las muestra
    todas, y finalmente informa cuál fue el número (base) que generó la
    secuencia más larga y cuál fue dicha longitud.

    Se realizan comprobaciones para no exceder la capacidad de la matriz.

    Entradas:
        - uno: Un número entero positivo.
        - otro: Otro número entero positivo.

    Salidas:
        - Mensajes sobre el cálculo de cada secuencia.
        - Mensajes de error si se excede la capacidad.
        - Listado de todas las secuencias calculadas.
        - La longitud máxima encontrada y el número base que la generó.
*/
//**************************************************************************/
#include <iostream>

using namespace std;

// Constantes para la matriz de secuencias
const int MAX_NUM_SECUENCIAS = 40;
const int MAX_LONG_SECUENCIA = 20;

//Declaración de funciones
int Max(int, int);
int Min(int, int);
int SiguienteCollatz(int);

//**************************************************************************/
//**************************************************************************/


int main()
{   
    int uno, otro;
    
    // Entrada

    bool entrada_ok;
    int minimo, maximo;

    do{
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
        minimo = Min(uno, otro);
        maximo = Max(uno, otro);
        int num_secuencias_pedidas = maximo - minimo + 1;

        cout << "Ha pedido " << num_secuencias_pedidas << " secuencias." 
             << endl;

        // Comprobar si caben las secuencias pedidas
        if (num_secuencias_pedidas > MAX_NUM_SECUENCIAS) {
            cout << "ERROR: No es posible generarlas. Maximo valor = " 
                << MAX_NUM_SECUENCIAS << endl;
            entrada_ok = false;
        } else {
            entrada_ok = true;
        }
    }while (!entrada_ok);


    cout << "-----------------------------------------------" << endl;

    // Declaración de la matriz y arrays de control
    int SecuenciasCollatz[MAX_NUM_SECUENCIAS][MAX_LONG_SECUENCIA];
    int long_secuencias[MAX_NUM_SECUENCIAS] = {0};
    int num_filas_usadas = 0; // Número de filas realmente usadas
    bool todo_ok = true; // Flag para detener el proceso si ocurre un error

    // Generar y almacenar todas las secuencias
    for (int base = minimo; base <= maximo && todo_ok; base++) 
    {
        int fila_actual = num_filas_usadas; // Fila donde se guardará la sec.

        // Guardar la base de la secuencia en la primera columna
        SecuenciasCollatz[fila_actual][0] = base;
        long_secuencias[fila_actual] = 1; // La longitud inicial es 1

        int actual = base;
        int pos_col = 1;

        while (actual != 1 && todo_ok) 
        {
            if (pos_col >= MAX_LONG_SECUENCIA) 
            {
                cout << "ERROR: Secuencia de base " << base 
                     << " demasiado larga. Maxima longitud = "
                     << MAX_LONG_SECUENCIA << endl;
                todo_ok = false;
            } else 
            {
                actual = SiguienteCollatz(actual);
                SecuenciasCollatz[fila_actual][pos_col] = actual;
                long_secuencias[fila_actual]++;
                pos_col++;
            }
        }

        // Si la secuencia se generó sin errores, se incrementa el contador
        if (todo_ok) 
        {
            cout << "Calculada secuencia de base " << base << ". Longitud = " 
                 << long_secuencias[fila_actual] << endl;
            num_filas_usadas++;
        }
    }

    // Mostrar las secuencias almacenadas
    cout << "-----------------------------------------------" << endl;

    for (int i = 0; i < num_filas_usadas; i++) 
    {
        int base = SecuenciasCollatz[i][0];
        int longitud = long_secuencias[i];

        cout << "Collatz (" << base << ") = { ";
        for (int j = 0; j < longitud; j++) 
        {
            // Imprimir el término y una coma, excepto para el último elemento
            cout << SecuenciasCollatz[i][j] << (j < longitud - 1 ? ", " : "");
        }
        cout << "}. Longitud = " << longitud << endl;
    }

    // Buscar y mostrar la secuencia más larga entre las almacenadas
    int base_max = 0;
    int long_max = 0;

    // Recorrer el vector de longitudes para encontrar el valor máximo
    for (int i = 0; i < num_filas_usadas; i++) 
    {
        if (long_secuencias[i] > long_max) 
        {
            // Si se encuentra una longitud mayor, se actualiza el máximo
            long_max = long_secuencias[i];
            base_max = SecuenciasCollatz[i][0];
        }
    }

    cout << "-----------------------------------------------" << endl;
    if (num_filas_usadas > 0) 
    {
        cout << "Secuencia max = Collatz (" << base_max << "). Longitud = " 
             << long_max << endl;
    }

    return 0;
}

/***************************************************************************/
/*
    c el mayor de dos números enteros.
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
    Comprueba cual es el menor de dos números enteros.
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


/***************************************************************************/
/*
    Calcula el siguiente término en la secuencia de Collatz.
    La regla es: si n es par, el siguiente es n/2; si es impar, es 3n+1.
    Parámetros:
        n: El número actual en la secuencia.
    Devuelve:
        El siguiente número en la secuencia de Collatz.
*/
/***************************************************************************/
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