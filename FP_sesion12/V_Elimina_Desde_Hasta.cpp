/***************************************************************************/
// FUNDAMENTOS DE PROGRAMACION
//
// MARIO MARTINEZ CALLEJON
//
// SESION 12
/*
    Programa de demostración para la clase SecuenciaCaracteres.

    Este programa implementa y prueba una clase que gestiona una secuencia
    de caracteres con un tamaño fijo. Se centra en la demostración de
    métodos que realizan subseccionado de la secuencia, como
    `EliminaDesde` y `EliminaHasta`, modificando la secuencia original.

    Entradas: Ninguna. El programa contiene una batería de pruebas fija.

    Salidas: Muestra por pantalla los resultados de las pruebas, mostrando
             el estado de la secuencia antes y después de cada operación.
*/
//**************************************************************************/

#include <iostream>

using namespace std;

//**************************************************************************/
// Definición de la clase SecuenciaCaracteres
//**************************************************************************/

class SecuenciaCaracteres {
private:

    static const int TAMANIO = 50; // Núm.casillas disponibles
    char vector_privado[TAMANIO];

    // PRE: 0<=total_utilizados<=TAMANIO
    int total_utilizados; // Núm.casillas ocupadas

public:
    /*********************************************************/
    // Constructor sin argumentos
    SecuenciaCaracteres (void) : total_utilizados (0) {}

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
    void Aniade (char nuevo)
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
    char Elemento (int indice)
    {
        return (vector_privado[indice]);
    }
    
    /*********************************************************/
    // Cambia el contenido de la casilla "indice" por el valor
    // dado en "nuevo". El tamaño de la secuencia no cambia.
    // PRE: 0 <= indice < total_utilizados
    void Modifica (int indice, char nuevo)
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

    void EliminaDesde (int indice)
    {
        if (indice >= 0 && indice <= total_utilizados) {
            total_utilizados = indice;
        }
    }

    void EliminaHasta (int indice)
    {
        if (indice >= 0 && indice < total_utilizados) 
        {
            int num_eliminados = indice + 1;
            int nuevos_total = total_utilizados - num_eliminados;

            for (int i = 0; i < nuevos_total; i++)
                vector_privado[i] = vector_privado[i + num_eliminados];

            total_utilizados = nuevos_total;
        }
    }

    /*********************************************************/
    // Inserta el carácter "nuevo" en la posición dada por "indice".
    // Desplaza todos los caracteres una posición a la derecha
    // antes de copiar en "indice" en valor "nuevo".
    // PRE: 0 <= indice < total_utilizados
    void Inserta (int indice, char valor_nuevo)
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

        for (int i=0; i<total_utilizados; i++)
            cadena = cadena + vector_privado[i];

        return (cadena);
    }
};

//**************************************************************************/
//**************************************************************************/

int main() {

    cout << "BATERIA DE PRUEBAS" << endl;
    cout << "==================" << endl << endl;

    SecuenciaCaracteres secuencia;

    // Preparar secuencia para las siguientes pruebas
    secuencia.EliminaTodos();
    secuencia.Aniade('A');
    secuencia.Aniade('B');
    secuencia.Aniade('C');
    secuencia.Aniade('D');
    secuencia.Aniade('E');

    // Prueba de EliminaDesde
    cout << "--- PRUEBA EliminaDesde ---" << endl;
    cout << "Secuencia original: \"" << secuencia.ToString() << "\"" << endl;
    cout << endl;

    secuencia.EliminaDesde(2); // Elimina desde el índice 2 hasta el final

    cout << "Secuencia tras EliminaDesde(2): " << secuencia.ToString() << endl; 
    cout << "Total utilizados (esperado 2): " << secuencia.TotalUtilizados() 
         << endl << endl;

    // Caso EliminaDesde(0)
    secuencia.EliminaDesde(0);
    cout << "Secuencia tras EliminaDesde(0) (vacia): " << secuencia.ToString() 
         << endl;
    cout << "Total utilizados (esperado 0): " << secuencia.TotalUtilizados() 
         << endl;

    // Restaurar
    secuencia.EliminaTodos();
    secuencia.Aniade('A'); 
    secuencia.Aniade('B'); 
    secuencia.Aniade('C'); 
    secuencia.Aniade('D'); 
    secuencia.Aniade('E');

    // Prueba de EliminaHasta
    cout << endl;
    cout << "--- PRUEBA EliminaHasta ---" << endl;
    cout << "Secuencia original: \"" << secuencia.ToString() << "\"" << endl;
    cout << endl;

    secuencia.EliminaHasta(2); // Elimina hasta el índice 2 incluido
    cout << "Secuencia tras EliminaHasta(2): " << secuencia.ToString() << endl;
    cout << "Total utilizados (esperado 2): " << secuencia.TotalUtilizados() 
         << endl << endl;

    // Restaurar
    secuencia.EliminaTodos();
    secuencia.Aniade('A');
    secuencia.Aniade('B');
    secuencia.Aniade('C');
    secuencia.Aniade('D');
    secuencia.Aniade('E');
    
    // Caso límite: EliminaHasta(4): toda la secuencia
    secuencia.EliminaHasta(4);
    cout << "Secuencia tras EliminaHasta(4) (vacia): " << secuencia.ToString() 
         << endl;
    cout << "Total utilizados (esperado 0): " << secuencia.TotalUtilizados() 
         << endl;
    cout << endl;

    cout << "============================" << endl;
    cout << "FIN DE LA BATERIA DE PRUEBAS" << endl;

    return 0;
}

//**************************************************************************/
//**************************************************************************/