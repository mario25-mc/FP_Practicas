/***************************************************************************
// FUNDAMENTOS DE PROGRAMACION
//
// MARIO MARTINEZ CALLEJON
//
// SESION 13
/*
    Este programa define y utiliza una jerarquía de clases para trabajar con
    matrices de enteros. Su objetivo es encontrar, dentro de un subconjunto
    de filas de una matriz, aquella que es más "cercana" a una secuencia de
    enteros de referencia. La cercanía se mide mediante la distancia euclídea.

    Clases implementadas:
    - SecuenciaEnteros: Una clase para almacenar y gestionar una secuencia
      de números enteros.
    - TablaRectangularEnteros: Representa una matriz 2D de enteros, construida
      a partir de objetos SecuenciaEnteros. Proporciona métodos para la
      manipulación y análisis de la matriz.

    Entradas:
        - matriz: Una tabla de enteros (7x4) definida en el código.
        - referencia: Un vector de enteros (tamaño 4) usado como patrón.
        - filas_a_comparar: Un vector que especifica los índices de las
          filas de la matriz que participarán en la búsqueda.

    Salidas:
        - El índice de la fila de la matriz que tiene la menor distancia
          euclídea a la secuencia de referencia, considerando solo el
          subconjunto de filas especificado.
*/
//**************************************************************************/

#include <iostream>
#include <cmath>

using namespace std;

//**************************************************************************/
// Definición de la clase SecuenciaEnteros
//**************************************************************************/

class SecuenciaEnteros 
{
private:

    static const int TAMANIO = 200; // Núm.casillas disponibles
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
};

//**************************************************************************/
// Definición de la estructura PosicionEnMatriz
//**************************************************************************/
struct PosicionEnMatriz {
    int fila;
    int col;
};

/***************************************************************************/
// Definición de la clase TablaRectangularEnteros
/***************************************************************************/
class TablaRectangularEnteros {
private:
    static const int NUM_FILS = 50;
    static const int NUM_COLS = 50;

    SecuenciaEnteros vector_privado[NUM_FILS];

    int filas_utilizadas;
    int cols_utilizadas;

public:
    /*********************************************************/
    // Constructor sin argumentos.
    // Crea una tabla vacía de 0x0.
    TablaRectangularEnteros(void) : filas_utilizadas(0), cols_utilizadas(0) {}

    /*********************************************************/
    // Constructor que inicializa una tabla vacía con un número de columnas
    // predefinido.
    //
    // Parámetros:
    //   num_columnas: Número de columnas que tendrá la tabla.
    //
    // PRE: 0 <= num_columnas <= NUM_COLS
    TablaRectangularEnteros(int num_columnas) : filas_utilizadas(0) 
    {
        if (num_columnas >= 0 && num_columnas <= NUM_COLS) {
            cols_utilizadas = num_columnas;
        } else {
            cols_utilizadas = 0;
        }
    }

    /*********************************************************/
    // Constructor que crea una tabla a partir de una primera fila.
    // El número de columnas de la tabla se establece según el tamaño de esta
    // primera fila.
    //
    // Parámetros:
    //   primera_fila: Objeto SecuenciaEnteros que se usará como primera fila.
    //
    TablaRectangularEnteros(SecuenciaEnteros primera_fila) 
    {
        filas_utilizadas = 0;
        cols_utilizadas = primera_fila.TotalUtilizados();

        if (cols_utilizadas > 0 && cols_utilizadas <= NUM_COLS) {
            Aniade(primera_fila);
        } else {
            cols_utilizadas = 0;
        }
    }

    /*********************************************************/
    // Devuelve la capacidad máxima de filas de la tabla.
    int CapacidadFilas(void) 
    {
        return NUM_FILS;
    }

    /*********************************************************/
    // Devuelve la capacidad máxima de columnas de la tabla.
    int CapacidadColumnas(void) 
    {
        return NUM_COLS;
    }

    /*********************************************************/
    // Devuelve el número de filas actualmente en uso.
    int FilasUtilizadas(void) 
    {
        return filas_utilizadas;
    }

    /*********************************************************/
    // Devuelve el número de columnas actualmente en uso.
    int ColumnasUtilizadas(void) 
    {
        return cols_utilizadas;
    }

    /*********************************************************/
    // Obtiene el valor de una celda específica.
    //
    // Parámetros:
    //   fila: Índice de la fila.
    //   columna: Índice de la columna.
    //
    // Devuelve:
    //   El valor entero en la posición (fila, columna).
    //
    // PRE: 0 <= fila < FilasUtilizadas()
    // PRE: 0 <= columna < ColumnasUtilizadas()
    int Elemento(int fila, int columna) 
    {
        return vector_privado[fila].Elemento(columna);
    }

    /*********************************************************/
    // Devuelve una copia de una fila completa de la tabla.
    //
    // Parámetros:
    //   indice_fila: El índice de la fila a obtener.
    //
    // Devuelve:
    //   Un objeto SecuenciaEnteros que contiene la fila solicitada.
    //
    // PRE: 0 <= indice_fila < FilasUtilizadas()
    SecuenciaEnteros Fila(int indice_fila) 
    {
        return vector_privado[indice_fila];
    }

    /*********************************************************/
    // Construye y devuelve una columna de la tabla.
    //
    // Parámetros:
    //   indice_columna: El índice de la columna a obtener.
    //
    // Devuelve:
    //   Un objeto SecuenciaEnteros que contiene la columna solicitada.
    //   Si el índice no es válido, devuelve una secuencia vacía.
    SecuenciaEnteros Columna(int indice_columna) 
    {
        SecuenciaEnteros columna;

        if (indice_columna >= 0 && indice_columna < cols_utilizadas) 
        {
            for (int i = 0; i < filas_utilizadas; ++i) 
            {
                columna.Aniade(vector_privado[i].Elemento(indice_columna));
            }
        }
        return columna;
    }

    /*********************************************************/
    // Añade una nueva fila al final de la tabla.
    //
    // Parámetros:
    //   fila_nueva: La secuencia de enteros a añadir como nueva fila.
    //
    // La operación solo se realiza si hay capacidad y el tamaño de la nueva 
    // fila coincide con el número de columnas de la tabla.
    void Aniade(SecuenciaEnteros fila_nueva) 
    {
        // Si la tabla está vacía ajustar el número de columnas
        if (filas_utilizadas == 0)
        {
            cols_utilizadas = fila_nueva.TotalUtilizados();
        }

        // Solo añade si no está llena y la nueva fila tiene el número 
        // correcto de columnas

        if (filas_utilizadas < NUM_FILS && 
            fila_nueva.TotalUtilizados() == cols_utilizadas) 
        {
            vector_privado[filas_utilizadas] = fila_nueva;
            filas_utilizadas++;
        }
    }

    /*********************************************************/
    // Inserta una nueva fila en una posición específica de la tabla.
    //
    // Parámetros:
    //   num_fila: Índice donde se insertará la nueva fila.
    //   fila_nueva: La secuencia de enteros a insertar.
    //
    // La operación solo se realiza si hay capacidad, el índice es válido y el
    // tamaño de la nueva fila coincide con el número de columnas de la tabla.
    void Inserta(int num_fila, SecuenciaEnteros fila_nueva) 
    {
        if (filas_utilizadas < NUM_FILS && 
            num_fila >= 0 && num_fila <= filas_utilizadas && 
            fila_nueva.TotalUtilizados() == cols_utilizadas) 
        {
            for (int i = filas_utilizadas; i > num_fila; --i) {
                vector_privado[i] = vector_privado[i - 1];
            }
            vector_privado[num_fila] = fila_nueva;
            filas_utilizadas++;
        }
    }

    /*********************************************************/
    // Elimina una fila de la tabla. Las filas posteriores se desplazan hacia 
    // arriba.
    //
    // Parámetros:
    //   num_fila: El índice de la fila a eliminar.
    // PRE: 0 <= num_fila < FilasUtilizadas()
    void Elimina(int num_fila) {
        if (num_fila >= 0 && num_fila < filas_utilizadas) 
        {
            for (int i = num_fila; i < filas_utilizadas - 1; ++i) 
            {
                vector_privado[i] = vector_privado[i + 1];
            }
            filas_utilizadas--;
        }
    }

    /*********************************************************/
    // Elimina todas las filas de la tabla, dejándola vacía (0x0).
    void EliminaTodos(void) {
        filas_utilizadas = 0;
        cols_utilizadas = 0;
    }

    /*********************************************************/
    // Comprueba si la tabla está vacía (no tiene filas).
    //
    // Devuelve:
    //   true si la tabla no tiene filas, false en caso contrario.
    bool EstaVacia(void) {
        return filas_utilizadas == 0;
    }

    /*********************************************************/
    // Compara si la tabla actual es idéntica a otra.
    //
    // Parámetros:
    //   otra_tabla: La tabla con la que se va a comparar.
    //
    // Devuelve:
    //   true si ambas tablas tienen las mismas dimensiones y elementos, 
    //   false en caso contrario.
    bool EsIgual(TablaRectangularEnteros otra_tabla) 
    {
        bool igual = true;

        if (filas_utilizadas != otra_tabla.FilasUtilizadas() || 
            cols_utilizadas != otra_tabla.ColumnasUtilizadas()) 
        {
            igual = false;
        } else
        {
            for (int i = 0; (i < filas_utilizadas) && igual; ++i) 
            {
                for (int j = 0; (j < cols_utilizadas) && igual; ++j) 
                {
                    if (Elemento(i, j) != otra_tabla.Elemento(i, j)) 
                    {
                        igual = false;
                    }
                }
            }
        }
        return igual;
    }

    /*********************************************************/
    // Calcula y devuelve la matriz traspuesta.
    //
    // Devuelve: Un nuevo objeto TablaRectangularEnteros que es la traspuesta.
    TablaRectangularEnteros Traspuesta(void) 
    {
         // La nueva tabla tendrá "filas_utilizadas" columnas
        TablaRectangularEnteros traspuesta(filas_utilizadas);

        for (int j = 0; j < cols_utilizadas; ++j) 
        {
            traspuesta.Aniade(Columna(j));
        }

        return traspuesta;
    }

    /*********************************************************/
    // Comprueba si la tabla es una matriz simétrica.
    //
    // Devuelve:
    //   true si la tabla es cuadrada y simétrica (A[i][j] == A[j][i]), 
    //   false en caso contrario.
    bool EsSimetrica(void) 
    {
        bool simetrica = true;

        if (filas_utilizadas != cols_utilizadas || EstaVacia()) 
        {
            simetrica = false; 
        }

        for (int i = 0; (i < filas_utilizadas) && simetrica; ++i) 
        {
            for (int j = i + 1; j < cols_utilizadas; ++j) 
            {
                if (Elemento(i, j) != Elemento(j, i)) 
                {
                    simetrica = false;
                }
            }
        }
        return simetrica;
    }

    /*********************************************************/
    // Busca un valor en la tabla.
    //
    // Parámetros:
    //   buscado: El valor entero a buscar.
    // Devuelve:
    //   true si el valor se encuentra en la tabla, false en caso contrario.
    bool Contiene(int buscado) 
    {
        bool encontrado = false;

        for (int i = 0; (i < filas_utilizadas) && !encontrado; ++i) 
        {
            for (int j = 0; (j < cols_utilizadas) && !encontrado; ++j) 
            {
                if (Elemento(i, j) == buscado) 
                {
                    encontrado = true;
                }
            }
        }

        return encontrado;
    }

    /*********************************************************/
    // Encuentra la primera aparición de un valor en la tabla.
    //
    // Parámetros:
    //   buscado: El valor entero a buscar.
    // Devuelve:
    //   Una estructura PosicionEnMatriz con la fila y columna de la primera
    //   ocurrencia. Si no se encuentra, devuelve {-1, -1}.
    PosicionEnMatriz PrimeraOcurrencia(int buscado) 
    {
        PosicionEnMatriz pos = {-1, -1}; // Valor por defecto si no se encuentra

        bool encontrado = false;

        for (int i = 0; (i < filas_utilizadas) && !encontrado; ++i) 
        {
            for (int j = 0; (j < cols_utilizadas) && !encontrado; ++j)
            {
                if (Elemento(i, j) == buscado) {
                    pos.fila = i;
                    pos.col = j;
                    encontrado = true; // Para la búsqueda al encontrar el primero
                }
            }
        }
        return pos;
    }
    
    /*********************************************************/
    // Busca, entre un conjunto seleccionado de filas, cuál es la más cercana a
    // una secuencia de referencia según la distancia euclídea.
    //
    // Parámetros:
    //   referencia: La secuencia de enteros con la que se compara cada fila.
    //   filas_a_comparar: Una secuencia de enteros que contiene los índices de
    //                     las filas de la matriz que se deben considerar en la
    //                     búsqueda.
    //
    // PRE: referencia.TotalUtilizados() == ColumnasUtilizadas()
    // PRE: filas_a_comparar no está vacía y contiene índices de fila válidos.
    //
    // Devuelve:
    //   El índice de la fila más cercana. Si hay varias filas con la misma
    //   distancia mínima, devuelve la primera que se encontró.
    //   Devuelve -1 si filas_a_comparar está vacía.
    int FilaMasCercana(SecuenciaEnteros referencia, 
                         SecuenciaEnteros filas_a_comparar)
    {
        // Variables para guardar el resultado de la búsqueda.
        int indice_fila_mas_cercana = -1;
        double min_distancia = -1.0; // Almacena la distancia euclídea mínima.

        // Recorrer la lista de índices de filas que se deben comparar.
        for (int i = 0; i < filas_a_comparar.TotalUtilizados(); ++i) 
        {
            // Obtener el índice de la fila actual y la fila completa.
            int indice_fila_actual = filas_a_comparar.Elemento(i);
            SecuenciaEnteros fila_actual = Fila(indice_fila_actual);

            // Calcular la suma de los cuadrados de las diferencias.
            double suma_cuadrados = 0.0;

            for (int j = 0; j < ColumnasUtilizadas(); ++j) 
            {
                // Calcular la diferencia entre los elementos de la fila actual 
                // y la de referencia.
                double diff = fila_actual.Elemento(j) - referencia.Elemento(j);
                suma_cuadrados += diff * diff;
            }

            // Calcular la distancia euclídea (raíz cuadrada de la suma de 
            // cuadrados).
            double distancia = sqrt(suma_cuadrados);

            // Comprobar si es la primera fila que se evalúa o si su distancia 
            // es menor que la mínima encontrada hasta ahora.
            if (min_distancia < 0 || distancia < min_distancia) 
            {
                // Actualizar la distancia min y el índice más cercano.
                min_distancia = distancia;
                indice_fila_mas_cercana = indice_fila_actual;
            }
        }
        return indice_fila_mas_cercana;
    }
};

//**************************************************************************/
//**************************************************************************/

int main()
{
    // Crear una matriz de ejemplo
    SecuenciaEnteros fila1;
    fila1.Aniade(3); 
    fila1.Aniade(1); 
    fila1.Aniade(0); 
    fila1.Aniade(8);
    
    SecuenciaEnteros fila2;
    fila2.Aniade(4); 
    fila2.Aniade(5); 
    fila2.Aniade(1); 
    fila2.Aniade(5);

    SecuenciaEnteros fila3;
    fila3.Aniade(5); 
    fila3.Aniade(7); 
    fila3.Aniade(1); 
    fila3.Aniade(7);

    SecuenciaEnteros fila4;
    fila4.Aniade(7); 
    fila4.Aniade(9); 
    fila4.Aniade(6); 
    fila4.Aniade(1);

    SecuenciaEnteros fila5;
    fila5.Aniade(4); 
    fila5.Aniade(9); 
    fila5.Aniade(5); 
    fila5.Aniade(5);

    SecuenciaEnteros fila6;
    fila6.Aniade(2); 
    fila6.Aniade(8); 
    fila6.Aniade(2); 
    fila6.Aniade(2);

    SecuenciaEnteros fila7;
    fila7.Aniade(7); 
    fila7.Aniade(3); 
    fila7.Aniade(2); 
    fila7.Aniade(5);

    TablaRectangularEnteros matriz(fila1);
    matriz.Aniade(fila2);
    matriz.Aniade(fila3);
    matriz.Aniade(fila4);
    matriz.Aniade(fila5);
    matriz.Aniade(fila6);
    matriz.Aniade(fila7);

    // Secuencia de referencia para la búsqueda
    SecuenciaEnteros referencia;
    referencia.Aniade(2); referencia.Aniade(8); 
    referencia.Aniade(1); referencia.Aniade(1);

    // Secuencia con los índices de las filas a comparar
    SecuenciaEnteros filas_a_comparar;
    filas_a_comparar.Aniade(0);
    filas_a_comparar.Aniade(2);
    filas_a_comparar.Aniade(4);
    filas_a_comparar.Aniade(5);

    cout << "Matriz de trabajo (" << matriz.FilasUtilizadas() << "x" 
         << matriz.ColumnasUtilizadas() << "):" << endl;

    for (int i=0; i < matriz.FilasUtilizadas(); i++)
        cout << "Fila " << i << ": " << matriz.Fila(i).ToString() << endl;

    cout << endl;

    cout << "Buscando la fila mas cercana a la secuencia de referencia: " 
         << referencia.ToString() << endl;

    cout << "Comparando solo con las filas con indice: " 
         << filas_a_comparar.ToString() << endl;

    if (matriz.EstaVacia() || 
        matriz.ColumnasUtilizadas() != referencia.TotalUtilizados()) 
    {
        cout << "La matriz esta vacia o las dimensiones no coinciden." << endl;
    } else 
    {
        // Llamada al nuevo método
        int indice_fila_mas_cercana = 
            matriz.FilaMasCercana(referencia, filas_a_comparar);

        // Mostrar el resultado
        cout << "------------------------------------------" << endl;
        if (indice_fila_mas_cercana != -1) 
        {
            cout << "Resultado: La fila mas cercana es la " 
                << indice_fila_mas_cercana << "." << endl;

            cout << "Fila " << indice_fila_mas_cercana << ": " 
                << matriz.Fila(indice_fila_mas_cercana).ToString() << endl;
        } else 
        {
            cout << "No se pudo encontrar la fila mas cercana";
            cout << "(la lista de filas a comparar estaba vacia)." << endl;
        }
    }
    return 0;
}

//**************************************************************************/
//**************************************************************************/