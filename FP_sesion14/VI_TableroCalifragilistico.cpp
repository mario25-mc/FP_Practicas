/***************************************************************************/
// FUNDAMENTOS DE PROGRAMACION
//
// MARIO MARTINEZ CALLEJON
//
// SESION 14
/*
    Programa que comprueba si un tablero cuadrado es "califragilístico" o
    "supercalifragilístico".

    Implementa una clase `TableroCuadrado` que incluye métodos para
    verificar estas propiedades. Un tablero es califragilístico si todas
    las sumas de sus filas, columnas y diagonales son diferentes. Es
    supercalifragilístico si, además, estas sumas forman una secuencia
    de enteros consecutivos.

    Entradas: Ninguna. El programa contiene una batería de pruebas fija
              en la función `main`.

    Salidas: Muestra por pantalla los resultados de las pruebas.
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
    // antes de copiar en "indice" el valor "nuevo".
    // PRE: total_utilizados < TAMANIO
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

    /*********************************************************/
    // Ordena la secuencia de menor a mayor usando el
    // método de Selección.
    void Ordena() 
    {
        // Buscar el menor entre las casillas "izda" y "total_utilizados"-1
        // e intercambiar ese valor por el de la posición "izda"
        for (int izda = 0 ; izda < total_utilizados ; izda++)
        {
            int pos_min = PosicionMinimoEntre (izda, total_utilizados-1);
            IntercambiaComponentes (izda, pos_min);
        }
    }

private:
    /*********************************************************/
    // Intercambia los elementos de las posiciones dadas.
    // PRE: 0 <= pos_izda < total_utilizados
    // PRE: 0 <= pos_dcha < total_utilizados
    void IntercambiaComponentes (int pos_izda, int pos_dcha) 
    {
        int intercambia = vector_privado[pos_izda];

        vector_privado[pos_izda] = vector_privado[pos_dcha];
        vector_privado[pos_dcha] = intercambia;
    }

    /*********************************************************/
    // Devuelve la posición del mínimo en el subvector que va 
    // desde "pos_izda" hasta "pos_dcha"
    // PRE: 0 <= pos_izda <= pos_dcha < total_utilizados
    int PosicionMinimoEntre (int pos_izda, int pos_dcha)
    {
        int pos_min = pos_izda;

        for (int i = pos_izda + 1; i <= pos_dcha; i++)
            if (vector_privado[i] < vector_privado[pos_min])
                pos_min = i;

        return pos_min;
    }
};

//**************************************************************************/
// Definición de la clase TableroCuadrado
//**************************************************************************/

class TableroCuadrado
{
private:
    static const int MAX = 15;
    int matriz_privada[MAX][MAX];
    int dimension;

    int filas_aniadidas;    // Almacena la cantidad de filas ocupadas

    // Almacena las sumas de cada fila, columna y diagonales
    SecuenciaEnteros sumas_privadas;    

public:
    /****************************************************************/
    // Constructor sin argumentos.
    // Inicializa un tablero de dimensión 0.
    TableroCuadrado(void)
        : dimension(0), filas_aniadidas(0)
    {}

    /****************************************************************/
    // Constructor con argumentos.
    // Inicializa un tablero de dimensión "dim".
    // Si "dim" está fuera del rango [0, MAX], se ajusta al límite
    // más cercano.
    TableroCuadrado(int dim)
    {
        if (dim < 0) dim = 0;
        if (dim > MAX) dim = MAX;

        dimension = dim;
        filas_aniadidas = 0;

        for (int i = 0; i < dim; i++)
            for (int j = 0; j < dim; j++)
                matriz_privada[i][j] = 0;
    }

    /****************************************************************/
    // Devuelve la dimensión del tablero.
    int GetDimension(void)
    {
        return dimension;
    }

    /****************************************************************/
    // Devuelve el elemento en la posición (fil, col).
    // Si la posición está fuera de los límites del tablero,
    // devuelve 0.
    // PRE: 0 <= fil < dimension, 0 <= col < dimension
    int Elemento(int fil, int col)
    {
        int elemento = 0; // valor por defecto si índices fuera de rango

        if ((fil >= 0) && (fil < dimension) && (col >= 0) && (col < dimension))
            elemento = matriz_privada[fil][col];

        return elemento;
    }

    /****************************************************************/
    // Modifica el elemento en la posición (fil, col).
    // No hace nada si la posición está fuera de los límites.
    // PRE: 0 <= fil < dimension, 0 <= col < dimension
    void Modifica(int fil, int col, int valor)
    {
        if ((fil >= 0) && (fil < dimension) && (col >= 0) && (col < dimension))
        {
            matriz_privada[fil][col] = valor;
        }
    }

    /****************************************************************/
    // Añade una fila al tablero.
    // La fila se añade en la primera posición de fila disponible.
    // PRE: fila.TotalUtilizados() == dimension
    // PRE: El número de filas añadidas es menor que la dimensión.
    void AniadeFila(SecuenciaEnteros fila)
    {
        if (filas_aniadidas < dimension && fila.TotalUtilizados() == dimension)
        {
            for (int j = 0; j < dimension; j++)
            {
                matriz_privada[filas_aniadidas][j] = fila.Elemento(j);
            }
            filas_aniadidas++;
        }
    }

    /****************************************************************/
    // "Vacía" el contenido del tablero, poniendo todos sus
    // elementos a 0 y reiniciando el contador de filas añadidas.
    // No cambia la dimensión.
    void EliminaContenido(void)
    {
        for (int i = 0; i < dimension; i++)
            for (int j = 0; j < dimension; j++)
                matriz_privada[i][j] = 0;
        
        filas_aniadidas = 0;
    }

    /****************************************************************/
    // Devuelve una secuencia de enteros con los elementos de la
    // fila "fil".
    // Si "fil" está fuera de rango, devuelve una secuencia vacía.
    // PRE: 0 <= fil < dimension
    SecuenciaEnteros Fila(int fil)
    {
        SecuenciaEnteros seq;

        if ((fil >= 0) && (fil < dimension))
        {
            for (int col = 0; col < dimension; col++)
                seq.Aniade(matriz_privada[fil][col]);
        }
        return seq;
    }

    /****************************************************************/
    // Devuelve una secuencia de enteros con los elementos de la
    // columna "col".
    // Si "col" está fuera de rango, devuelve una secuencia vacía.
    // PRE: 0 <= col < dimension
    SecuenciaEnteros Columna(int col)
    {
        SecuenciaEnteros seq;

        if ((col >= 0) && (col < dimension))
        {
            for (int fil = 0; fil < dimension; fil++)
                seq.Aniade(matriz_privada[fil][col]);
        }
        return seq;
    }

    /****************************************************************/
    // Comprueba si el tablero es "califragilístico".
    // Un tablero es califragilístico si todas las sumas de sus
    // filas, columnas y diagonales son diferentes entre sí.
    // Un tablero de dimensión 0 o negativa no es califragilístico.
    //
    // Necesidad y ámbito: Este método público es esencial para que un
    // usuario de la clase pueda consultar una propiedad fundamental del
    // tablero.
    bool EsCalifragilistico(void)
    {
        bool es = true;

        // Un tablero sin dimensiones no puede ser califragilístico.
        if (dimension <= 0) 
        {
            es = false;
        } else 
        {
            // Se calculan y almacenan internamente todas las sumas.
            SecuenciaSumas();
            
            int total_sumas = sumas_privadas.TotalUtilizados();

            // Se comprueba que no haya valores repetidos. Para ello, se
            // compara cada suma con las demás.
            for (int i = 0; i < total_sumas && es; ++i) 
            {
                for (int j = i + 1; j < total_sumas && es; ++j) 
                {
                    // Si se encuentra una suma repetida, el tablero no es
                    // califragilístico.
                    if (sumas_privadas.Elemento(i) == 
                        sumas_privadas.Elemento(j)) 
                    {
                        es = false;
                    }
                }
            }
        }

        return es;
    }

    /****************************************************************/
    // Comprueba si el tablero es "supercalifragilístico".
    //
    // Un tablero es supercalifragilístico si es califragilístico y,
    // además, el conjunto de todas las sumas (filas, columnas y
    // diagonales) forma una secuencia de números enteros
    // consecutivos.
    //
    // Necesidad y ámbito: Este método público permite consultar una
    // propiedad más específica del tablero, que depende de que sea
    // califragilístico.
    bool EsSuperCalifragilistico(void)
    {
        bool es = true;

        // Si no es califragilistico no puede ser supercalifragilístico
        if (!EsCalifragilistico()) 
        {
            es = false;
        } else 
        {
            // Las sumas ya han sido calculadas por EsCalifragilistico().
            // Solo se necesita obtener el total.
            int total_sumas = sumas_privadas.TotalUtilizados();

            // Si no hay sumas no es supercalifragilistico
            if (total_sumas == 0) 
            {
                es = false;
            } else // Se comprueban si estan ordenados y son consecutivos
            {   
                // Ordenar la secuencia de sumas
                sumas_privadas.Ordena();

                // Comprobar que sean consecutivos con diferencia 1
                for (int i = 1; (i < total_sumas) && es; ++i) 
                {
                    if (sumas_privadas.Elemento(i) != 
                       sumas_privadas.Elemento(i - 1) + 1) 
                    {
                        es = false;
                    }
                }
            }
        }

        return es;
    }

private:

    /****************************************************************/
    // Añade una suma a la secuencia interna de sumas.
    // Necesidad y ámbito: Este método privado es una utilidad interna.
    void AniadeSuma(int suma)
    {
        sumas_privadas.Aniade(suma);
    }

    /****************************************************************/
    // Vacía la secuencia interna de sumas.
    // Necesidad y ámbito: Este método privado es una utilidad interna.
    void EliminaTodasLasSumas()
    {
        sumas_privadas.EliminaTodos();
    }


    /****************************************************************/
    // Calcula las sumas de todas las filas, columnas y las dos
    // diagonales del tablero.
    //
    // Necesidad y ámbito: Este método privado es una utilidad interna.
    // Se usa para obtener los datos que los métodos públicos
    // EsCalifragilistico y EsSuperCalifragilistico necesitan para operar.
    void SecuenciaSumas(void)
    {
        // Se vacía la secuencia antes de volver a calcular.
        EliminaTodasLasSumas();

        // 1. Calcular las sumas de todas las filas.
        for (int r = 0; r < dimension; ++r) 
        {
            int s = 0;
            
            for (int c = 0; c < dimension; ++c)
                s += matriz_privada[r][c];

            AniadeSuma(s);
        }

        // 2. Calcular las sumas de todas las columnas.
        for (int c = 0; c < dimension; ++c) 
        {
            int s = 0;

            for (int r = 0; r < dimension; ++r)
                s += matriz_privada[r][c];

            AniadeSuma(s);
        }

        // Solo se calculan las diagonales si el tablero tiene dimensión.
        if (dimension > 0) {
            // 3. Calcular la suma de la diagonal principal.
            int sd1 = 0;

            for (int i = 0; i < dimension; ++i)
                sd1 += matriz_privada[i][i];
                
            AniadeSuma(sd1);

            // 4. Calcular la suma de la diagonal secundaria.
            int sd2 = 0;

            for (int i = 0; i < dimension; ++i)
                sd2 += matriz_privada[i][dimension - 1 - i];

            AniadeSuma(sd2);
        }
    }
};

/****************************************************************/
// Programa principal para probar la clase TableroCuadrado
/****************************************************************/
int main()
{

    // Caso 1: Tablero 2x2 que es califragilístico pero no supercalifragilístico
    cout << "****** CASO 1: Tablero 2x2 Califragilistico (no Super) ******" 
         << endl;

    TableroCuadrado tablero1(2);
    SecuenciaEnteros fila;

    fila.Aniade(1); fila.Aniade(8);
    tablero1.AniadeFila(fila);
    fila.EliminaTodos();
    fila.Aniade(6); fila.Aniade(4);
    tablero1.AniadeFila(fila);

    // Sumas: filas(9, 10), columnas(7, 12), diagonales(5, 14). Todas diferentes
    cout << "Tablero de prueba (califragilistico, no super):" << endl;
    cout << " " << tablero1.Elemento(0,0) << " " << tablero1.Elemento(0,1) 
         << endl;
    cout << " " << tablero1.Elemento(1,0) << " " << tablero1.Elemento(1,1) 
         << endl;
    cout << "Es califragilistico? ";
    cout << (tablero1.EsCalifragilistico() ? "si" : "no") << endl;
    cout << "Es supercalifragilistico? " ;
    cout << (tablero1.EsSuperCalifragilistico() ? "si" : "no") << endl;
    cout << endl;

    // Caso 2: tablero 4x4 que sí es supercalifragilístico.
    cout << "****** CASO 2: Tablero 4x4 Supercalifragilistico ******" << endl;

    TableroCuadrado tablero_super_4x4(4);
    fila.EliminaTodos();
    fila.Aniade(15); fila.Aniade(2); fila.Aniade(12); fila.Aniade(4);
    tablero_super_4x4.AniadeFila(fila);
    fila.EliminaTodos();
    fila.Aniade(1); fila.Aniade(14); fila.Aniade(10); fila.Aniade(5);
    tablero_super_4x4.AniadeFila(fila);
    fila.EliminaTodos();
    fila.Aniade(8); fila.Aniade(9); fila.Aniade(3); fila.Aniade(16);
    tablero_super_4x4.AniadeFila(fila);
    fila.EliminaTodos();
    fila.Aniade(11); fila.Aniade(13); fila.Aniade(6); fila.Aniade(7);
    tablero_super_4x4.AniadeFila(fila);

    cout << "Tablero de prueba (supercalifragilistico):" << endl;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cout << " " << tablero_super_4x4.Elemento(i, j);
        }
        cout << endl;
    }
    cout << "Es califragilistico? ";
    cout << (tablero_super_4x4.EsCalifragilistico() ? "si" : "no") << endl;
    cout << "Es supercalifragilistico? ";
    cout << (tablero_super_4x4.EsSuperCalifragilistico() ? "si" : "no") << endl;
    cout << endl;

    // Caso 3: Tablero 3x3 con una suma repetida
    cout << "****** CASO 3: Tablero 3x3 con suma repetida ******" << endl;

    TableroCuadrado tablero3(3);
    fila.EliminaTodos();
    fila.Aniade(1); fila.Aniade(2); fila.Aniade(3); // Suma fila = 6
    tablero3.AniadeFila(fila);
    fila.EliminaTodos();
    fila.Aniade(4); fila.Aniade(5); fila.Aniade(6);
    tablero3.AniadeFila(fila);
    fila.EliminaTodos();
    fila.Aniade(3); fila.Aniade(2); fila.Aniade(1); // Suma fila = 6
    tablero3.AniadeFila(fila);

    // La suma de la fila 0 y la fila 2 son iguales (6), no es califragilístico.
    cout << "Tablero de prueba (sumas de filas repetidas):" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << " " << tablero3.Elemento(i, j);
        }
        cout << endl;
    }
    cout << "Es califragilistico? ";
    cout << (tablero3.EsCalifragilistico() ? "si" : "no") << endl;
    cout << "Es supercalifragilistico? ";
    cout << (tablero3.EsSuperCalifragilistico() ? "si" : "no") << endl;
    cout << endl;

    // Caso 4: Tablero vacío
    cout << "****** CASO 4: Tablero vacio ******" << endl;
    TableroCuadrado tablero4(0);
    cout << "Tablero de dimension 0:" << endl;
    cout << "Es califragilistico? ";
    cout << (tablero4.EsCalifragilistico() ? "si" : "no") << endl;
    cout << "Es supercalifragilistico? ";
    cout << (tablero4.EsSuperCalifragilistico() ? "si" : "no") << endl;
    cout << endl;

    return 0;
}

//**************************************************************************/
//**************************************************************************/