/***************************************************************************/
// FUNDAMENTOS DE PROGRAMACION
//
// MARIO MARTINEZ CALLEJON
//
// SESION 12
/*
    Programa que demuestra la mezcla de dos secuencias de enteros ordenadas,
    creando una nueva secuencia que contiene los elementos de ambas sin
    valores repetidos.

    Implementa una clase `SecuenciaEnteros` con un método `Mezcla_NoRepetidos`.
    Este método verifica que ambas secuencias estén ordenadas crecientemente
    antes de proceder. Si no lo están, devuelve una secuencia vacía.
    La mezcla se realiza de forma eficiente, recorriendo ambas secuencias
    simultáneamente.

    Salidas: Muestra por pantalla los resultados de las pruebas, incluyendo
             las secuencias originales y la secuencia resultante de la mezcla.
*/
//**************************************************************************/

#include <iostream>
#include <string>

using namespace std;

//**************************************************************************/
// Definición de la clase SecuenciaEnteros
//**************************************************************************/

class SecuenciaEnteros 
{
private:

    static const int TAMANIO = 50; // Núm.casillas disponibles
    int vector_privado[TAMANIO];

    // PRE: 0<=total_utilizados<=TAMANIO
    int total_utilizados; // Núm.casillas ocupadas

public:
    /*********************************************************/
    // Constructor sin argumentos
    // Por defecto, el criterio es por frecuencia.
    SecuenciaEnteros (void) 
        : total_utilizados (0)
    {}

    /*********************************************************/
    // Devuelve el número de casillas ocupadas
    int TotalUtilizados (void)
    {
        return (total_utilizados);
    }

    /*********************************************************/
    // Devuelve el número de casillas disponibles
    int Capacidad (void)
    {
        return (TAMANIO);
    }

    /*********************************************************/
    // "Vacía" completamente la secuencia
    void EliminaTodos (void)
    {
        total_utilizados = 0;
    }

    /*********************************************************/
    // Añade un elemento ("nuevo") al vector.
    // PRE: total_utilizados < TAMANIO
    // La adición se realiza si hay alguna casilla disponible.
    // El nuevo elemento se coloca al final del vector.
    // Si no hay espacio, no se hace nada.
    void Aniade (int nuevo)
    {
        if (total_utilizados < TAMANIO)
        {
            vector_privado[total_utilizados] = nuevo;
            total_utilizados++;
        }
    }

    /*********************************************************/
    // Devuelve el elemento de la casilla "indice"
    // PRE: 0 <= indice < total_utilizados
    int Elemento (int indice)
    {
        return (vector_privado[indice]);
    }
    
    /*********************************************************/
    // Cambia el contenido de la casilla "indice" por el valor
    // dado en "nuevo". El tamaño de la secuencia no cambia.
    // PRE: 0 <= indice < total_utilizados
    void Modifica (int indice, int nuevo)
    {
        if ((indice >= 0) && (indice < total_utilizados)) 
        {
            vector_privado[indice] = nuevo;
        }
    }

    /*********************************************************/    
    // Eliminar el carácter de la posición dada por "indice".
    // Realiza un borrado físico (desplazamiento y sustitución).
    // PRE: 0 <= indice < total_utilizados
    void Elimina (int indice)
    {
        if ((indice >= 0) && (indice < total_utilizados)) {

            int tope = total_utilizados-1; // posic. del último

            for (int i = indice ; i < tope ; i++)
                vector_privado[i] = vector_privado[i+1];

            total_utilizados--;
        }
    }

    /*********************************************************/
    // Inserta el carácter "nuevo" en la posición dada por "indice".
    // Desplaza todos los caracteres una posición a la derecha
    // antes de copiar en "indice" en valor "nuevo".
    // PRE: 0 <= indice < total_utilizados
    void Inserta (int indice, int valor_nuevo)
    {
        if ((total_utilizados < TAMANIO) && (indice >= 0)
        && (indice < total_utilizados)) 
        {
            for (int i = total_utilizados ; i > indice ; i--)
                vector_privado[i] = vector_privado[i-1];

            vector_privado[indice] = valor_nuevo;
            total_utilizados++;
        }
    }

    /*********************************************************/
    // Compone un string con todos los caracteres que están
    // almacenados en la secuencia y lo devuelve.
    string ToString()
    {
        string cadena;

        for (int i=0; i<total_utilizados; i++) {
            cadena = cadena + to_string(vector_privado[i]);
            if (i+1 < total_utilizados)
                cadena = cadena + " ";
        }

        return (cadena);
    }

    /************************************************************************/
    // Este método toma otra secuencia de enteros y produce una nueva que
    // contiene la unión ordenada de los elementos de ambas, sin duplicados.
    //
    // Parámetros:
    //   SecuenciaEnteros otra: La secuencia con la que se realizará la mezcla
    //
    // Devuelve:
    //   Una nueva SecuenciaEnteros con el resultado. Si alguna de las
    //   secuencias no está ordenada, devuelve una secuencia vacía.
    SecuenciaEnteros Mezcla_NoRepetidos (SecuenciaEnteros otra)
    {
        SecuenciaEnteros mezcla;

        // Comprobar precondición: ambas secuencias deben estar ordenadas.
        if (EstaOrdenadaCreciente() && otra.EstaOrdenadaCreciente()) {
            int i = 0; // Índice para la secuencia implícita
            int j = 0; // Índice para la secuencia 'otra'

            // Recorrer ambas secuencias mientras haya elementos en las dos.
            while (i < total_utilizados && j < otra.TotalUtilizados()) {
                if (vector_privado[i] < otra.Elemento(j)) 
                {
                    mezcla.AniadeSinRepetir(vector_privado[i]);
                    i++;
                } else if (vector_privado[i] > otra.Elemento(j)) 
                {
                    mezcla.AniadeSinRepetir(otra.Elemento(j));
                    j++;
                } else // Son iguales
                { 
                    mezcla.AniadeSinRepetir(vector_privado[i]);
                    i++;
                    j++;
                }
            }

            // Añadir los elementos restantes de la primera secuencia.
            while (i < total_utilizados) {
                mezcla.AniadeSinRepetir(vector_privado[i]);
                i++;
            }

            // Añadir los elementos restantes de la segunda secuencia.
            while (j < otra.TotalUtilizados()) {
                mezcla.AniadeSinRepetir(otra.Elemento(j));
                j++;
            }
        }

        return mezcla;  //Si no están ordenadas se devuelve una secuencia vacía
    }

private:

    /***********************************************************************/
    // Añade un valor al final de la secuencia solo si no es un duplicado del
    // último elemento existente.
    //
    // Parámetros:
    //   valor (int): El entero a añadir.
    //
    // PRE: total_utilizados < TAMANIO
    void AniadeSinRepetir(int valor) {
        if (total_utilizados == 0 || 
            vector_privado[total_utilizados - 1] != valor) 
        {
            Aniade(valor);
        }
    }

    /***********************************************************************/
    // Comprueba si la secuencia está ordenada en sentido creciente.
    //
    // Devuelve:
    //   `true` si los elementos están en orden no decreciente, y `false` en
    //   caso contrario.
    bool EstaOrdenadaCreciente(void) {

        bool ordenada = true;

        for (int i = 0; (i < total_utilizados - 1) && ordenada; i++) 
        {
            if (vector_privado[i] > vector_privado[i + 1]) 
            {
                ordenada = false;
            }
        }

        return ordenada;
    }
};

/**************************************************************************/
// Batería de pruebas para la clase SecuenciaEnteros, para el método
// Mezcla_NoRepetidos.
/**************************************************************************/
int main() {
    cout << "BATERIA DE PRUEBAS PARA Mezcla_NoRepetidos" << endl;
    cout << "==========================================" << endl << endl;

    SecuenciaEnteros s1, s2, mezcla;

    // Prueba 1: Ambas secuencias ordenadas y con elementos comunes.
    cout << "--- PRUEBA 1: Mezcla estandar ---" << endl;
    s1.EliminaTodos();
    s2.EliminaTodos();
    s1.Aniade(1); s1.Aniade(3); s1.Aniade(5); s1.Aniade(7);
    s2.Aniade(2); s2.Aniade(3); s2.Aniade(6); s2.Aniade(7); s2.Aniade(9);

    cout << "Secuencia 1: " << s1.ToString() << endl;
    cout << "Secuencia 2: " << s2.ToString() << endl;
    
    mezcla = s1.Mezcla_NoRepetidos(s2);
    cout << "Mezcla: " << mezcla.ToString() << endl;
    cout << "----------------------------------------" << endl << endl;

    // Prueba 2: Una de las secuencias no está ordenada.
    cout << "--- PRUEBA 2: Una secuencia desordenada ---" << endl;
    s1.EliminaTodos();
    s2.EliminaTodos();
    s1.Aniade(1); s1.Aniade(5); s1.Aniade(3); // Desordenada
    s2.Aniade(2); s2.Aniade(4); s2.Aniade(6);

    cout << "Secuencia 1: " << s1.ToString() << " (desordenada)" << endl;
    cout << "Secuencia 2: " << s2.ToString() << endl;

    mezcla = s1.Mezcla_NoRepetidos(s2);
    cout << "Mezcla: " << mezcla.ToString() << endl;
    cout << "----------------------------------------" << endl << endl;

    // Prueba 3: Mezcla con una secuencia vacía.
    cout << "--- PRUEBA 3: Mezcla con secuencia vacia ---" << endl;
    s1.EliminaTodos();
    s2.EliminaTodos();
    s1.Aniade(10); s1.Aniade(20); s1.Aniade(30);

    cout << "Secuencia 1: " << s1.ToString() << endl;
    cout << "Secuencia 2: " << s2.ToString() << " (vacia)" << endl;

    mezcla = s1.Mezcla_NoRepetidos(s2);
    cout << "Mezcla: " << mezcla.ToString() << endl;
    cout << "----------------------------------------" << endl << endl;

    // Prueba 4: Secuencias sin elementos en común.
    cout << "--- PRUEBA 4: Secuencias disjuntas ---" << endl;
    s1.EliminaTodos();
    s2.EliminaTodos();
    s1.Aniade(1); s1.Aniade(2); s1.Aniade(3);
    s2.Aniade(4); s2.Aniade(5); s2.Aniade(6);

    cout << "Secuencia 1: " << s1.ToString() << endl;
    cout << "Secuencia 2: " << s2.ToString() << endl;

    mezcla = s1.Mezcla_NoRepetidos(s2);
    cout << "Mezcla: " << mezcla.ToString() << endl;
    cout << "----------------------------------------" << endl << endl;

    // Prueba 5: Ambas secuencias vacías.
    cout << "--- PRUEBA 5: Ambas secuencias vacias ---" << endl;
    s1.EliminaTodos();
    s2.EliminaTodos();

    cout << "Secuencia 1: (vacia)" << endl;
    cout << "Secuencia 2: (vacia)" << endl;

    mezcla = s1.Mezcla_NoRepetidos(s2);
    cout << "Mezcla: " << mezcla.ToString() << endl;
    cout << "==========================================" << endl;

    return 0;
}

/**************************************************************************/
/**************************************************************************/