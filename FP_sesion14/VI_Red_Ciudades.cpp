/***************************************************************************/
// FUNDAMENTOS DE PROGRAMACION
//
// MARIO MARTINEZ CALLEJON
//
// SESION 14
/*
    Programa que modela una red de ciudades mediante una matriz de distancias.

    Implementa las clases `SecuenciaReales`, `SecuenciaEnteros` y
    `MapaDistancias` para gestionar los datos. El programa permite al
    usuario definir el número de ciudades y las distancias entre ellas,
    asumiendo una red simétrica.

    Posteriormente, realiza varios análisis sobre la red, como:
    - Encontrar la ciudad con más conexiones directas.
    - Listar las ciudades conectadas a una ciudad específica.
    - Encontrar la mejor ruta indirecta entre dos ciudades no conectadas.
    - Comprobar si un conjunto de ciudades están todas conectadas entre sí.

    Entradas:
        - Número de ciudades.
        - Distancias entre cada par de ciudades.
        - Peticiones interactivas para realizar los análisis.

    Salidas:
        - La matriz de distancias completa.
        - Los resultados de los análisis solicitados por el usuario.
*/
//**************************************************************************/
#include <iostream>
#include <cmath>

using namespace std;

//**************************************************************************/
// Definición de la clase SecuenciaReales
//**************************************************************************/

class SecuenciaReales 
{
private:

    static const int TAMANIO = 50; // Núm.casillas disponibles
    double vector_privado[TAMANIO];

    // PRE: 0<=total_utilizados<=TAMANIO
    int total_utilizados; // Núm.casillas ocupadas

public:
    /*********************************************************/
    // Constructor sin argumentos
    SecuenciaReales (void) 
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
    void Aniade (double nuevo)
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
    double Elemento (int indice)
    {
        return (vector_privado[indice]);
    }
    
    /*********************************************************/
    // Cambia el contenido de la casilla "indice" por el valor
    // dado en "nuevo". El tamaño de la secuencia no cambia.
    // PRE: 0 <= indice < total_utilizados
    void Modifica (int indice, double nuevo)
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
    void Inserta (int indice, double valor_nuevo)
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
        {
            cadena = cadena + to_string(vector_privado[i]);
            
            if (i + 1 < total_utilizados)
                cadena = cadena + " ";
        }

        return (cadena);
    }
};

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
};

//**************************************************************************/
// Definición de la estructura PosicionEnMatriz
//**************************************************************************/
struct PosicionEnMatriz {
    int fila;
    int col;
};

/***************************************************************************/
// Definición de la clase MapaDistancias
/***************************************************************************/
class MapaDistancias {
private:
    static const int NUM_FILS = 50;
    static const int NUM_COLS = 50;

    SecuenciaReales vector_privado[NUM_FILS];

    int filas_utilizadas;
    int cols_utilizadas;

public:
    /*********************************************************/
    // Constructor sin argumentos.
    // Crea una tabla vacía de 0x0.
    MapaDistancias(void) : filas_utilizadas(0), cols_utilizadas(0) {}

    /*********************************************************/
    // Constructor que inicializa una tabla vacía con un número de columnas
    // predefinido.
    //
    // Parámetros:
    //   num_columnas: Número de columnas que tendrá la tabla.
    //
    // PRE: 0 <= num_columnas <= NUM_COLS
    MapaDistancias(int num_columnas) : filas_utilizadas(0) 
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
    //   primera_fila: Objeto SecuenciaReales que se usará como primera fila.
    // PRE: primera_fila.TotalUtilizados() <= CapacidadColumnas()
    //
    MapaDistancias(SecuenciaReales primera_fila) 
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
    double Elemento(int fila, int columna) 
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
    //   Un objeto SecuenciaReales que contiene la fila solicitada.
    //
    // PRE: 0 <= indice_fila < FilasUtilizadas()
    SecuenciaReales Fila(int indice_fila) 
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
    //   Un objeto SecuenciaReales que contiene la columna solicitada.
    //   Si el índice no es válido, devuelve una secuencia vacía.
    // PRE: 0 <= indice_columna < ColumnasUtilizadas()
    SecuenciaReales Columna(int indice_columna) 
    {
        SecuenciaReales columna;

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
    //   fila_nueva: La secuencia de reales a añadir como nueva fila.
    //
    // La operación solo se realiza si hay capacidad y el tamaño de la nueva 
    // fila coincide con el número de columnas de la tabla.
    // PRE: FilasUtilizadas() < CapacidadFilas()
    // PRE: fila_nueva.TotalUtilizados() == ColumnasUtilizadas() si la tabla
    //      no está vacía.
    void Aniade(SecuenciaReales fila_nueva) 
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
    //   fila_nueva: La secuencia de reales a insertar.
    //
    // La operación solo se realiza si hay capacidad, el índice es válido y el
    // tamaño de la nueva fila coincide con el número de columnas de la tabla.
    // PRE: FilasUtilizadas() < CapacidadFilas()
    // PRE: 0 <= num_fila <= FilasUtilizadas()
    // PRE: fila_nueva.TotalUtilizados() == ColumnasUtilizadas() si la tabla
    //      no está vacía.
    void Inserta(int num_fila, SecuenciaReales fila_nueva) 
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
    bool EsIgual(MapaDistancias otra_tabla) 
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
    // Devuelve: Un nuevo objeto MapaDistancias que es la traspuesta.
    MapaDistancias Traspuesta(void) 
    {
         // La nueva tabla tendrá "filas_utilizadas" columnas
        MapaDistancias traspuesta(filas_utilizadas);

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
    //   buscado: El valor real a buscar.
    // Devuelve:
    //   true si el valor se encuentra en la tabla, false en caso contrario.
    bool Contiene(double buscado) 
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
    //   buscado: El valor real a buscar.
    // Devuelve:
    //   Una estructura PosicionEnMatriz con la fila y columna de la primera
    //   ocurrencia. Si no se encuentra, devuelve {-1, -1}.
    PosicionEnMatriz PrimeraOcurrencia(double buscado) 
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
    //   referencia: La secuencia de reales con la que se compara cada fila.
    //   filas_a_comparar: Una secuencia de reales que contiene los índices de
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
    int FilaMasCercana(SecuenciaReales referencia, 
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
            SecuenciaReales fila_actual = Fila(indice_fila_actual);

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

    /*********************************************************/
    // Convierte la tabla a un formato de cadena para su visualización.
    //
    // Devuelve:
    //   Una cadena que representa la tabla completa.
    string ToString()
    {
        string resultado = "--- Matriz de distancias completa ---\n";

        for (int i = 0; i < filas_utilizadas; ++i) {
            resultado += "Ciudad " + to_string(i) + ":\t" + 
                         Fila(i).ToString() + "\n";
        }

        resultado += "-------------------------------------";

        return resultado;
    }

    /*********************************************************/
    // Obtiene la ciudad (su índice) con el mayor número de conexiones directas.
    // Una conexión directa existe si la distancia es > 0.
    //
    // Devuelve:
    //   El índice de la ciudad con más conexiones. Si el mapa está vacío
    //   o no hay conexiones, devuelve -1.
    // PRE: La matriz debe ser cuadrada (simétrica).
    int CiudadConMasConexiones()
    {
        int ciudad_max_conexiones = -1;
        int max_conexiones = -1;

        if (!EstaVacia()) 
        {
            for (int i = 0; i < filas_utilizadas; ++i) 
            {
                int conexiones_actuales = 0;

                for (int j = 0; j < cols_utilizadas; ++j) 
                {
                    // Una conexión existe si la distancia es positiva.
                    if (Elemento(i, j) > 0) {
                        conexiones_actuales++;
                    }
                }

                if (conexiones_actuales > max_conexiones) 
                {
                    max_conexiones = conexiones_actuales;
                    ciudad_max_conexiones = i;
                }
            }
        }
        
        return ciudad_max_conexiones;
    }

    /*********************************************************/
    // Dada una ciudad j, obtener las ciudades conectadas directamente con j.
    // Una conexión directa existe si la distancia es > 0.
    //
    // Parámetros:
    //   indice_ciudad: El índice de la ciudad a consultar.
    //
    // Devuelve:
    //   Una SecuenciaEnteros con los índices de las ciudades conectadas.
    //   Si el índice no es válido, devuelve una secuencia vacía.
    // PRE: 0 <= indice_ciudad < FilasUtilizadas()
    SecuenciaEnteros CiudadesConectadasA(int indice_ciudad)
    {
        SecuenciaEnteros conectadas;

        if (indice_ciudad >= 0 && indice_ciudad < filas_utilizadas)
        {
            for (int j = 0; j < cols_utilizadas; ++j)
            {
                if (Elemento(indice_ciudad, j) > 0) 
                {
                    conectadas.Aniade(j);
                }
            }
        }
        return conectadas;
    }

    /*********************************************************/
    // Encuentra la ciudad intermedia que minimiza la distancia entre dos
    // ciudades no conectadas directamente.
    //
    // Parámetros:
    //   ciudad_origen: El índice de la ciudad de partida.
    //   ciudad_destino: El índice de la ciudad de llegada.
    //
    // Devuelve:
    //   El índice de la ciudad intermedia 'z' que minimiza d(i,z) + d(z,j).
    //   Si no existe tal ciudad, devuelve -1.
    //
    // PRE: 0 <= ciudad_origen, ciudad_destino < FilasUtilizadas()
    int MejorCiudadIntermedia(int ciudad_origen, int ciudad_destino)
    {
        int mejor_ciudad_intermedia = -1;
        double min_distancia_total = -1.0;

        // Iterar por todas las posibles ciudades intermedias 'z'
        for (int z = 0; z < filas_utilizadas; ++z)
        {
            // La ciudad intermedia no puede ser ni el origen ni el destino
            if (z != ciudad_origen && z != ciudad_destino)
            {
                double dist_origen_z = Elemento(ciudad_origen, z);
                double dist_z_destino = Elemento(z, ciudad_destino);

                // Comprobar si hay conexión origen -> z y z -> destino
                if (dist_origen_z > 0 && dist_z_destino > 0)
                {
                    double distancia_actual = dist_origen_z + dist_z_destino;

                    // Si la distancia es menor que la anterior encontrada, 
                    // guardar la ciudad en mejor_ciudad_intermedia
                    if (min_distancia_total < 0 || 
                        distancia_actual < min_distancia_total) 
                    {
                        min_distancia_total = distancia_actual;
                        mejor_ciudad_intermedia = z;
                    }
                }
            }
        }
        return mejor_ciudad_intermedia;
    }

    /*********************************************************/
    // Comprueba si un conjunto de ciudades, dadas por sus índices, están
    // todas conectadas directamente entre sí.
    //
    // Parámetros:
    //   ciudades: Una SecuenciaEnteros con los índices de las ciudades a 
    //             comprobar.
    //
    // Devuelve:
    //   true si todas las ciudades en la secuencia tienen una conexión directa
    //   con todas las demás en la misma secuencia. false en caso contrario.
    //
    // PRE: Todos los elementos de "ciudades" deben ser índices de fila 
    //      válidos (0 <= indice < FilasUtilizadas()).
    bool EstanTodasConectadasDirectamente(SecuenciaEnteros ciudades)
    {
        bool conectadas = true;

        // Iterar sobre todos los pares de ciudades en la secuencia.
        for (int i = 0; i < ciudades.TotalUtilizados(); ++i) 
        {
            for (int j = i + 1; j < ciudades.TotalUtilizados(); ++j) 
            {
                // Si un par no está conectado, conectadas = false.
                if (Elemento(ciudades.Elemento(i), ciudades.Elemento(j)) <= 0)
                    conectadas = false; 
            }
        }

        return conectadas;
    }
};

/***************************************************************************/
// Definición de la clase Lector
/***************************************************************************/
class Lector {
private:

    string titulo; // Título a mostrar en las peticiones de lectura

    /***********************************************************************/    
    // Comprueba si una cadena representa un número entero válido.
    // Un entero válido puede tener un signo opcional (+ o -) al principio.
    // Devuelve: true si la cadena es un entero, false en caso contrario.
    /***********************************************************************/
    bool EsEntero(string entrada) {
        bool es_entero = true;

        if (entrada.empty()) 
        {
            es_entero = false; // Una cadena vacía no es un entero.
        }

        int inicio = 0;
        // Si hay un signo, la validación empieza desde el siguiente carácter.
        if (entrada.at(0) == '+' || entrada.at(0) == '-') 
        {
            inicio = 1;
            // Si la cadena solo tiene un signo, no es válido.
            if (entrada.length() == 1) 
            {
                es_entero = false;
            }
        }

        // Recorrer la cadena para asegurarse de que todos son dígitos
        for (int i = inicio; i < entrada.length(); i++) 
        {
            if (!isdigit(entrada.at(i))) 
            {
                es_entero = false; // Si encuentra un no-dígito, no es un entero
            }
        }

        return es_entero; // Si pasó todas las pruebas, es un entero.
    }

    /***********************************************************************/
    // Comprueba si una cadena representa un número real (double) válido.
    // Un real válido puede tener un signo opcional (+ o -) al principio,
    // seguido de dígitos y como máximo un punto decimal.
    // Devuelve: true si la cadena es un real, false en caso contrario.
    /***********************************************************************/
    bool EsReal(string entrada) {   
        bool es_real = true;

        if (entrada.empty()) {
            es_real = false;
        }

        int inicio = 0;
        if (entrada.at(0) == '+' || entrada.at(0) == '-') {
            inicio = 1;
            if (entrada.length() == 1) {
                es_real = false; // Solo un signo no es válido
            }
        }

        int puntos_decimales = 0;
        int num_digitos = 0;

        for (int i = inicio; i < entrada.length(); i++) {
            if (isdigit(entrada.at(i))) {
                num_digitos++;
            } else if (entrada.at(i) == '.') {
                puntos_decimales++;
            } else {
                es_real = false; // Carácter no válido
            }
        }

        // Debe tener al menos un dígito y como máximo un punto decimal.
        if (!(num_digitos > 0 && puntos_decimales <= 1))
            es_real = false;
        
        return es_real;
    }

public:
    /***********************************************************************/
    // Constructor por defecto
    Lector() 
        : titulo("") 
    {}

    /***********************************************************************/
    // Constructor con parámetros.
    // Parámetros: nuevo_titulo, el mensaje que se mostrará al leer.
    Lector(string nuevo_titulo) 
        : titulo(nuevo_titulo) 
    {}

    /***********************************************************************/
    // Establece el título que se mostrará en las lecturas.
    // Parámetros: nuevo_titulo, el nuevo mensaje a mostrar.
    void SetTitulo(string nuevo_titulo) {
        titulo = nuevo_titulo;
    }

    /***********************************************************************/
    // Lee y devuelve un dato entero. Si el valor leído no fuera un entero,
    // la función volvería a pedirlo hasta que se proporcione un valor correcto.
    // Devuelve: el número entero leído.
    /***********************************************************************/
    int LeeEntero ()
    {
        string entrada;

        if (!titulo.empty()) {
            cout << titulo;
        }

        // Lectura anticipada
        cin >> entrada;

        // Bucle de validación
        while (!EsEntero(entrada)) {
            // Informar del error
            cout << "\tERROR: Entrada no valida. Debe ser un numero entero." 
                 << endl;
            
            // Pedir de nuevo
            if (!titulo.empty()) {
                cout << titulo;
            }
            // Leer la nueva entrada
            cin >> entrada;
        }

        return stoi(entrada);
    }

    /***********************************************************************/
    // Lee un entero y verifica que esté en el rango [menor, mayor].
    // Vuelve a pedir el dato si no es un entero o si está fuera de rango.
    // Parámetros: menor (límite inferior), mayor (límite superior).
    // Devuelve: el número entero leído si está en el rango.
    // PRE: menor <= mayor
    /***********************************************************************/
    int LeeEnteroEnRango (int menor, int mayor)
    {
        string entrada;
        bool entrada_ok;

        if (!titulo.empty()) {
            cout << titulo;
        }

        // Lectura anticipada
        cin >> entrada;
        
        // Verificar la entrada.
        if (EsEntero(entrada))
        {
            int num = stoi(entrada);
            entrada_ok = (menor <= num && mayor >= num);
        } else {
            entrada_ok = false;
        }

        // Bucle de validación
        while (!entrada_ok) {
            // Informar del error
            cout << "\tERROR: Entrada no valida. Debe ser un numero entero "
                 << "entre " << menor << " y " << mayor << '.' << endl;
            
            // Pedir de nuevo
            if (!titulo.empty()) {
                cout << titulo;
            }
            // Leer la nueva entrada
            cin >> entrada;

            // Nueva verificación
            if (EsEntero(entrada))
            {
                int num = stoi(entrada);
                entrada_ok = (menor <= num && mayor >= num);
            } else {
                entrada_ok = false;
            }
        }

        return stoi(entrada);
    }

    /***********************************************************************/
    // Lee un entero y verifica que sea mayor o igual a un valor de referencia.
    // Vuelve a pedir el dato si no es un entero o si no cumple la condición.
    // Parámetros: referencia (valor mínimo permitido).
    // Devuelve: el número entero leído si es >= referencia.
    /***********************************************************************/
    int LeeEnteroMayorOIgual (int referencia) {
        string entrada;
        bool entrada_ok;

        if (!titulo.empty()) {
            cout << titulo;
        }

        // Lectura anticipada
        cin >> entrada;
        
        // Verificar la entrada.
        if (EsEntero(entrada))
        {
            int num = stoi(entrada);
            entrada_ok = (referencia <= num);
        } else {
            entrada_ok = false;
        }

        // Bucle de validación
        while (!entrada_ok) {
            // Informar del error
            cout << "\tERROR: Entrada no valida. Debe ser un numero entero "
                 << "mayor  o igual que " << referencia << '.' << endl;
            
            // Pedir de nuevo
            if (!titulo.empty()) {
                cout << titulo;
            }
            // Leer la nueva entrada
            cin >> entrada;

            // Nueva verificación
            if (EsEntero(entrada))
            {
                int num = stoi(entrada);
                entrada_ok = (referencia <= num);
            } else {
                entrada_ok = false;
            }
        }

        return stoi(entrada);
    }

    /***********************************************************************/
    // Lee y devuelve un dato double. Si el valor leido no fuera un double,
    // la función volvería a pedirlo hasta que se proporcione un valor correcto.
    // Devuelve: el número double leído.
    /***********************************************************************/
    double LeeReal ()
    {
        string entrada;

        if (!titulo.empty()) {
            cout << titulo;
        }

        // Lectura anticipada
        cin >> entrada;

        // Bucle de validación
        while (!EsReal(entrada)) {
            // Informar del error
            cout << "\tERROR: Entrada no valida. Debe ser un numero real." 
                 << endl;
            
            // Pedir de nuevo
            if (!titulo.empty()) {
                cout << titulo;
            }
            // Leer la nueva entrada
            cin >> entrada;
        }

        return stod(entrada);
    }

    /***********************************************************************/
    // Lee un double y verifica que esté en el rango [menor, mayor].
    // Parámetros: menor, mayor.
    // Devuelve: el número double leído si está en el rango.
    // PRE: menor <= mayor
    /***********************************************************************/
    double LeeRealEnRango (double menor, double mayor)
    {
        string entrada;
        bool entrada_ok = false;
        double num;

        if (!titulo.empty()) {
            cout << titulo;
        }
        cin >> entrada;

        if (EsReal(entrada)) {
            num = stod(entrada);
            entrada_ok = (num >= menor && num <= mayor);
        } else {
            entrada_ok = false;
        }

        while (!entrada_ok) {
            cout << "\tERROR: Entrada no valida. Debe ser un numero real en "
                 << " el rango [" << menor << "," << mayor << "]." << endl;

            if (!titulo.empty()) {
                cout << titulo;
            }
            cin >> entrada;

            if (EsReal(entrada)) {
                num = stod(entrada);
                entrada_ok = (num >= menor && num <= mayor);
            } else {
                entrada_ok = false;
            }
        }

        return stod(entrada);
    }

    /***********************************************************************/
    // Lee un double y verifica que sea mayor o igual a un valor de referencia.
    // Parámetros: referencia.
    // Devuelve: el número double leído si es >= referencia.
    /***********************************************************************/
    double LeeRealMayorOIgual (double referencia)
    {
        string entrada;
        bool entrada_ok = false;
        double num;

        if (!titulo.empty()) {
            cout << titulo;
        }
        cin >> entrada;

        if (EsReal(entrada)) {
            num = stod(entrada);
            entrada_ok = (num >= referencia);
        } else {
            entrada_ok = false;
        }

        while (!entrada_ok) {
            cout << "\tERROR: Entrada no valida. Debe ser un numero real mayor "
                 << " o igual que " << referencia << "." << endl;

            if (!titulo.empty()) {
                cout << titulo;
            }

            cin >> entrada;

            if (EsReal(entrada)) {
                num = stod(entrada);
                entrada_ok = (num >= referencia);
            } else {
                entrada_ok = false;
            }
        }

        return stod(entrada);
    }
};

//**************************************************************************/
//**************************************************************************/

int main() {
    // Crear un lector para la entrada del usuario
    Lector lector;

    // Pedir el número de ciudades
    lector.SetTitulo("Introduce el numero de ciudades (2-50): ");

    int num_ciudades = lector.LeeEnteroEnRango
                       (2, MapaDistancias().CapacidadFilas());

    // Crear el mapa de distancias con las dimensiones correctas
    MapaDistancias mapa(num_ciudades);

    cout << "\nIntroduce las distancias entre las ciudades." << endl;
    cout << "(0 si no hay camino directo)" << endl;
    cout << "---------------------------------------------" << endl;

    // Rellenar la matriz de distancias.
    // Como es simétrica, solo necesitamos leer la parte triangular superior.
    for (int i = 0; i < num_ciudades; ++i) 
    {
        SecuenciaReales fila_actual;
        for (int j = 0; j < num_ciudades; ++j) 
        {
            if (i == j) 
            {
                // La distancia de una ciudad a sí misma es 0
                fila_actual.Aniade(0);
            } else if (i < j) 
            {
                // Pedir al usuario la distancia para la mitad superior
                string mensaje = "Distancia de ciudad " + to_string(i) + 
                                 " a ciudad " + to_string(j) + ": ";

                lector.SetTitulo(mensaje);
                double distancia = lector.LeeRealMayorOIgual(0);
                fila_actual.Aniade(distancia);
            } else 
            {
                // Para la mitad inferior, usamos el valor simétrico ya leído
                // y almacenado en el mapa.
                double distancia_simetrica = mapa.Elemento(j, i);
                fila_actual.Aniade(distancia_simetrica);
            }
        }
        // Añadir la fila completada al mapa
        mapa.Aniade(fila_actual);
    }

    // Mostrar la matriz de distancias resultante
    cout << "\n" << mapa.ToString() << endl;

    // Encontrar y mostrar la ciudad con más conexiones
    int ciudad_mejor_conectada = mapa.CiudadConMasConexiones();
    if (ciudad_mejor_conectada != -1) 
    {
        cout << "\nLa ciudad con mas conexiones directas es la ciudad: " 
             << ciudad_mejor_conectada << endl;
    } else 
    {
        cout << "\nNo se pudo determinar la ciudad con mas conexiones." << endl;
    }

    // Preguntar por una ciudad y mostrar sus conexiones
    if (!mapa.EstaVacia()) 
    {
        lector.SetTitulo
              ("\nIntroduce el indice de una ciudad para ver sus conexiones: ");

        int ciudad_a_consultar = lector.LeeEnteroEnRango(0, num_ciudades - 1);

        SecuenciaEnteros conexiones = 
                        mapa.CiudadesConectadasA(ciudad_a_consultar);

        cout << "La ciudad " << ciudad_a_consultar << " esta conectada con: ";
        if (conexiones.TotalUtilizados() > 0) 
        {
            cout << conexiones.ToString() << endl;
        } else 
        {
            cout << "ninguna otra ciudad." << endl;
        }
    }

    // Preguntar por dos ciudades para encontrar la mejor ruta indirecta
    if (!mapa.EstaVacia())
    {
        cout << "\n--- BUSCAR MEJOR RUTA INDIRECTA ---" << endl;
        lector.SetTitulo("Introduce la ciudad de origen: ");
        int origen = lector.LeeEnteroEnRango(0, num_ciudades - 1);

        lector.SetTitulo("Introduce la ciudad de destino: ");
        int destino = lector.LeeEnteroEnRango(0, num_ciudades - 1);

        if (mapa.Elemento(origen, destino) > 0)
        {
            cout << "\nYa existe un camino directo entre la ciudad " << origen
                 << " y la " << destino << " con distancia "
                 << mapa.Elemento(origen, destino) << "." << endl;
        }
        else
        {
            int intermedia = mapa.MejorCiudadIntermedia(origen, destino);

            if (intermedia != -1)
            {
                double dist_total = mapa.Elemento(origen, intermedia) +
                                    mapa.Elemento(intermedia, destino);

                cout << "\nLa ruta mas corta sin conexion directa es a traves "
                        "de la ciudad " << intermedia << "." << endl;

                cout << "Ruta: " << origen << " -> " << intermedia << " -> " 
                     << destino << ". Distancia total: " << dist_total << endl;
            }
            else
            {
                cout << "\nNo se encontro ninguna ciudad intermedia para "
                        "conectar " << origen << " y " << destino << ".\n";
            }
        }
    }

    // Comprobar si un conjunto de ciudades están todas conectadas entre sí
    if (!mapa.EstaVacia())
    {
        cout << "\n--- COMPROBAR CONEXION TOTAL ENTRE CIUDADES ---" << endl;
        cout << "Introduce los indices de las ciudades a comprobar "
             << "(termina con -1):" << endl;

        SecuenciaEnteros ciudades_a_comprobar;
        int ciudad_leida;

        // Lectura anticipada
        lector.SetTitulo("Ciudad: ");
        ciudad_leida = lector.LeeEntero();

        while (ciudad_leida != -1) 
        {
            if (ciudad_leida >= 0 && ciudad_leida < num_ciudades) 
            {
                ciudades_a_comprobar.Aniade(ciudad_leida);
            } else 
            {
                cout << "\tERROR: El indice de ciudad debe estar entre 0 y "
                     << num_ciudades - 1 << "." << endl;
            }

            // Leer siguiente valor
            lector.SetTitulo("Ciudad: ");
            ciudad_leida = lector.LeeEntero();
        }

        if (ciudades_a_comprobar.TotalUtilizados() > 0) 
        {
            if (mapa.EstanTodasConectadasDirectamente(ciudades_a_comprobar)) 
            {
                cout << "\nTodas las ciudades introducidas ("
                     << ciudades_a_comprobar.ToString()
                     << ") estan conectadas directamente entre si." << endl;
            } else 
            {
                cout << "\nNo todas las ciudades introducidas ("
                     << ciudades_a_comprobar.ToString()
                     << ") estan conectadas directamente entre si." << endl;
            }
        }
    }
    return 0;
}
/***************************************************************************/
/***************************************************************************/