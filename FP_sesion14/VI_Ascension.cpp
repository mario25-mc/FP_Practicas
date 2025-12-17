/***************************************************************************/
// FUNDAMENTOS DE PROGRAMACION
//
// MARIO MARTINEZ CALLEJON
//
// SESION 14
/*
    Programa que simula la búsqueda de un camino de ascensión en un mapa
    topográfico.

    Implementa una clase `Mapa` que almacena las alturas de un terreno en
    una matriz. El programa incluye un método `Ascender` que, a partir de
    una coordenada de inicio, busca un camino moviéndose a casillas vecinas
    cuya altura sea exactamente una unidad mayor que la actual. La ascensión
    termina cuando se alcanza la altura 9 o cuando no es posible encontrar
    un siguiente paso válido.

    Entradas: Ninguna. El programa utiliza un mapa de prueba fijo definido
              en la función `main`.

    Salidas: Muestra por pantalla el mapa de prueba y los caminos de
             ascensión encontrados para diferentes puntos de inicio.
*/
//**************************************************************************/
#include <iostream>

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
};

/***************************************************************************/
// Definición de la clase Coordenada
/***************************************************************************/
class Coordenada {
private:
    int fila;
    int columna;

public:
    /***********************************************************************/
    // Constructor por defecto. Inicializa las coordenadas a (0,0).
    Coordenada(void) : 
        fila(0), 
        columna(0) 
    {}

    /***********************************************************************/
    // Establece el valor de la fila.
    void SetFila(int fil) {
        fila = fil;
    }

    /***********************************************************************/
    // Establece el valor de la columna.
    void SetColumna(int col) {
        columna = col;
    }

    /***********************************************************************/
    // Establece ambos valores de la coordenada.
    void SetCoordenadas(int fil, int col) {
        fila = fil;
        columna = col;
    }

    /***********************************************************************/
    // Devuelve el valor de la fila.
    int GetFila(void) {
        return fila;
    }

    /***********************************************************************/
    // Devuelve el valor de la columna.
    int GetColumna(void) {
        return columna;
    }
};

/***************************************************************************/
// Definición de la clase SecuenciaCoordenadas
/***************************************************************************/
class SecuenciaCoordenadas {
private:
    static const int MAX_COORDENADAS = 100;
    Coordenada v[MAX_COORDENADAS];
    int num_coordenadas;

public:
    /***********************************************************************/
    // Constructor por defecto. Crea una secuencia vacía.
    SecuenciaCoordenadas(void) : 
        num_coordenadas(0) 
    {}

    /***********************************************************************/
    // Añade una coordenada al final de la secuencia si hay capacidad.
    //
    // Parámetros:
    //   posicion: La coordenada a añadir.
    //
    // La operación solo se realiza si hay espacio disponible en la secuencia.
    // PRE: TotalUtilizados() < Capacidad()
    void Aniade(Coordenada posicion) 
    {
        if (num_coordenadas < MAX_COORDENADAS) 
        {
            v[num_coordenadas] = posicion;
            num_coordenadas++;
        }
    }

    /***********************************************************************/
    // Devuelve la coordenada en la posición i.
    // PRE: 0 <= i < TotalUtilizados()
    Coordenada Elemento(int i) {
        return v[i];
    }

    /***********************************************************************/
    // Devuelve la capacidad máxima de la secuencia.
    int Capacidad(void) {
        return MAX_COORDENADAS;
    }

    /***********************************************************************/
    // Devuelve el número de coordenadas actualmente almacenadas.
    int TotalUtilizados(void) {
        return num_coordenadas;
    }
};

/***************************************************************************/
// Definición de la clase Mapa
/***************************************************************************/
class Mapa {
private:
    // Dimensiones máximas de la matriz
    static const int NUM_FILAS = 50;
    static const int NUM_COLUMNAS = 100;

    // Matriz para almacenar las alturas del mapa
    int matriz_privada[NUM_FILAS][NUM_COLUMNAS];

    // Dimensiones actualmente en uso
    int filas_utilizadas;
    int columnas_utilizadas;

public:
    /***********************************************************************/
    // Constructor por defecto.
    // Inicializa un mapa vacío (0x0).
    Mapa() : 
        filas_utilizadas(0), 
        columnas_utilizadas(0) 
    {}

    /***********************************************************************/
    // Devuelve el número de filas actualmente en uso en el mapa.
    int NumeroFilas() 
    {
        return filas_utilizadas;
    }

    /***********************************************************************/
    // Devuelve el número de columnas actualmente en uso en el mapa.
    int NumeroColumnas() 
    {
        return columnas_utilizadas;
    }

    /***********************************************************************/
    // Añade una fila de datos al mapa.
    // Este es un método auxiliar para facilitar la carga de datos de prueba.
    //
    // Parámetros:
    //   fila_datos: SecuenciaEnteros con los datos de altura de la nueva fila.
    //
    // La operación solo se realiza si hay capacidad de filas y las columnas
    // no exceden la capacidad máxima.
    void AniadeFila(SecuenciaEnteros fila_datos) 
    {
        int num_cols = fila_datos.TotalUtilizados();

        if (filas_utilizadas < NUM_FILAS && num_cols <= NUM_COLUMNAS) {
            for (int j = 0; j < num_cols; j++)
                matriz_privada[filas_utilizadas][j] = fila_datos.Elemento(j);
            filas_utilizadas++;
            columnas_utilizadas = num_cols;
        }
    }

    /***********************************************************************/
    // Devuelve la altura (valor) en una posición específica del mapa.
    //
    // Parámetros:
    //   fila: El índice de la fila.
    //   col: El índice de la columna.
    //
    // Devuelve:
    //   La altura en la posición (fila, col) si los índices son válidos.
    //   Devuelve -1 si los índices están fuera de los límites del mapa.
    //
    // PRE: 0 <= fila < NumeroFilas()
    // PRE: 0 <= col < NumeroColumnas()
    int Altura(int fila, int col) 
    {
        int altura = -1;    // Valor de error si la posición es inválida

        if (fila >= 0 && fila < filas_utilizadas && col >= 0 && col < 
            columnas_utilizadas) 
        {
            altura = matriz_privada[fila][col];
        }

        return altura; 
    }

    /***********************************************************************/
    // Imprime el contenido del mapa en la consola.
    // Itera sobre las filas y columnas utilizadas y muestra cada altura.
    void Imprimir()
    {
        for (int i = 0; i < filas_utilizadas; i++)
        {
            for (int j = 0; j < columnas_utilizadas; j++)
            {
                cout << matriz_privada[i][j] << "\t";
            }
            cout << endl;
        }
    }

    /***********************************************************************/
    // Busca un camino de ascensión desde una coordenada de inicio.
    // El camino se construye saltando a una casilla vecina cuya altura sea
    // exactamente 1 unidad mayor que la actual. La búsqueda de vecinos se
    // realiza por filas (arriba->abajo) y columnas (izda->dcha).
    // El proceso termina si se alcanza la altura 9 o si no hay un
    // siguiente paso válido.
    //
    // Parámetros:
    //   inicio: La coordenada desde la que comienza la ascensión.
    //
    // Devuelve:
    //   Una SecuenciaCoordenadas con el camino encontrado.
    SecuenciaCoordenadas Ascender(Coordenada inicio) {
        SecuenciaCoordenadas camino;
        Coordenada pos_actual = inicio;

        camino.Aniade(pos_actual);

        bool fin_camino = false;

        while (!fin_camino) 
        {
            int fila_actual = pos_actual.GetFila();
            int col_actual = pos_actual.GetColumna();
            int altura_actual = Altura(fila_actual, col_actual);

            // Condición de parada: altura 9 o fuera del mapa
            if (altura_actual == 9 || altura_actual == -1) {
                fin_camino = true;
            } else {
                bool encontrado_siguiente_paso = false;

                // Búsqueda de la siguiente casilla en el orden especificado
                for (int f_vecina = fila_actual - 1; f_vecina <= fila_actual + 1
                     && !encontrado_siguiente_paso; f_vecina++) 
                {
                    for (int c_vecina = col_actual - 1; 
                         c_vecina <= col_actual + 1 && 
                         !encontrado_siguiente_paso; c_vecina++) 
                    {
                        // No comprobar la casilla actual
                        if (f_vecina != fila_actual || c_vecina != col_actual) 
                        {
                            if (Altura(f_vecina, c_vecina) == altura_actual + 1) 
                            {
                                pos_actual.SetCoordenadas(f_vecina, c_vecina);
                                camino.Aniade(pos_actual);
                                encontrado_siguiente_paso = true;
                            }
                        }
                    }
                }

                // Si no se encontró un siguiente paso, el camino termina
                if (!encontrado_siguiente_paso) {
                    fin_camino = true;
                }
            }
        }

        return camino;
    }
};

/***************************************************************************/
/***************************************************************************/

int main()
{
    // Crear y cargar un mapa de ejemplo para las pruebas
    Mapa mapa_prueba;
    SecuenciaEnteros fila;

    // Rellenar el mapa
    fila.Aniade(1); fila.Aniade(2); fila.Aniade(3); 
    fila.Aniade(4); fila.Aniade(5);
    mapa_prueba.AniadeFila(fila);
    fila.EliminaTodos();

    fila.Aniade(2); fila.Aniade(3); fila.Aniade(8); 
    fila.Aniade(9); fila.Aniade(6);
    mapa_prueba.AniadeFila(fila);
    fila.EliminaTodos();

    fila.Aniade(3); fila.Aniade(4); fila.Aniade(5); 
    fila.Aniade(6); fila.Aniade(7);
    mapa_prueba.AniadeFila(fila);
    fila.EliminaTodos();

    fila.Aniade(4); fila.Aniade(5); fila.Aniade(6); 
    fila.Aniade(7); fila.Aniade(8);
    mapa_prueba.AniadeFila(fila);
    fila.EliminaTodos();

    fila.Aniade(5); fila.Aniade(6); fila.Aniade(7); 
    fila.Aniade(8); fila.Aniade(1);
    mapa_prueba.AniadeFila(fila);

    cout << "****** MAPA DE PRUEBA ******" << endl;
    mapa_prueba.Imprimir();
    cout << "****************************" << endl;

    cout << "****** PRUEBA DE ASCENSION ******" << endl;

    // Caso A: Ascensión desde (0,0) que llega a altura 9
    cout << "\n--- Caso A: Ascension desde (0,0) ---" << endl;
    Coordenada inicio_A;
    inicio_A.SetCoordenadas(0, 0);
    SecuenciaCoordenadas camino_A = mapa_prueba.Ascender(inicio_A);

    cout << "Camino encontrado: ";
    for (int i = 0; i < camino_A.TotalUtilizados(); i++) {
        Coordenada paso = camino_A.Elemento(i);
        cout << "(" << paso.GetFila() << "," << paso.GetColumna() << ") ";
    }
    cout << endl;

    // Caso B: Ascensión desde (0,1) que se detiene
    cout << "\n--- Caso B: Ascension desde (0,1) ---" << endl;
    Coordenada inicio_B;
    inicio_B.SetCoordenadas(0, 1);
    SecuenciaCoordenadas camino_B = mapa_prueba.Ascender(inicio_B);

    cout << "Camino encontrado: ";
    for (int i = 0; i < camino_B.TotalUtilizados(); i++) {
        Coordenada paso = camino_B.Elemento(i);
        cout << "(" << paso.GetFila() << "," << paso.GetColumna() << ") ";
    }
    cout << endl;

    return 0;
}

/***************************************************************************/
/***************************************************************************/