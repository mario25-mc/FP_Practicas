/***************************************************************************/
// FUNDAMENTOS DE PROGRAMACION
//
// MARIO MARTINEZ CALLEJON
//
// SESION 14
/*
    Programa interactivo para el problema de las N reinas.

    Implementa una clase `Tablero` para representar un tablero de ajedrez
    de 8x8 y una clase `Lector` para gestionar la entrada del usuario.
    El programa permite al usuario especificar el número de reinas que
    desea colocar y luego introducirlas una por una en el tablero.

    El juego termina en victoria si el usuario logra colocar todas las
    reinas sin que se amenacen entre sí. Termina en derrota si se acaban
    las casillas libres antes de haber colocado todas las reinas.

    Entradas:
        - El número de reinas a colocar (entre 1 y 8).
        - Las coordenadas (fila y columna) para cada reina.

    Salidas:
        - El estado del tablero después de cada jugada.
        - Mensajes de estado (reinas colocadas, casillas libres).
        - Mensajes de victoria o derrota.
        - El estado final del tablero.
*/
//**************************************************************************/
#include <iostream>

using namespace std;

/***************************************************************************/
// Definición de la clase Tablero
/***************************************************************************/
class Tablero {
private:
    static const int TAM = 8;
    char matriz_privada[TAM][TAM];
    const int NUM_REINAS;

    static const char REINA = 'R';
    static const char LIBRE = ' ';
    static const char VIGILADO = 'x';

public:
    /***********************************************************************/
    // Constructor sin parámetros.
    // Inicializa el tablero con todas las casillas libres y el número
    // de reinas objetivo a TAM.
    Tablero(void) : NUM_REINAS(TAM) 
    {
        for (int i = 0; i < TAM; i++) 
        {
            for (int j = 0; j < TAM; j++) 
            {
                matriz_privada[i][j] = LIBRE;
            }
        }
    }

    /***********************************************************************/
    // Constructor con el parámetro n: el número máximo de reinas
    // Inicializa el tablero con todas las casillas libres y el número
    // de reinas objetivo a n.
    // PRE: 1 <= n <= TAM
    Tablero(int n) : NUM_REINAS(n) 
    {
        for (int i = 0; i < TAM; i++) 
        {
            for (int j = 0; j < TAM; j++) 
            {
                matriz_privada[i][j] = LIBRE;
            }
        }
    }

    /***********************************************************************/
    // Devuelve la dimensión del tablero (siempre 8).
    int Dimension(void) 
    {
        return TAM;
    }

    /***********************************************************************/
    // Devuelve el número de reinas que se deben colocar en el tablero.
    int NumReinasObjetivo(void) 
    {
        return NUM_REINAS;
    }

    /***********************************************************************/
    // Devuelve el contenido de una casilla.
    // PRE: 0 <= fil < Dimension(), 0 <= col < Dimension()
    char Contenido(int fil, int col) 
    {
        return matriz_privada[fil][col];
    }

    /***********************************************************************/
    // Devuelve el número de reinas colocadas en el tablero.
    int NumReinasColocadas(void) 
    {
        int contador = 0;
        for (int i = 0; i < TAM; i++) 
        {
            for (int j = 0; j < TAM; j++) 
            {
                if (matriz_privada[i][j] == REINA) 
                {
                    contador++;
                }
            }
        }
        return contador;
    }

    /***********************************************************************/
    // Devuelve el número de casillas libres en el tablero.
    int NumCasillasLibres(void) 
    {
        int contador = 0;
        for (int i = 0; i < TAM; i++) 
        {
            for (int j = 0; j < TAM; j++) 
            {
                if (matriz_privada[i][j] == LIBRE) 
                {
                    contador++;
                }
            }
        }
        return contador;
    }

    /***********************************************************************/
    // Coloca una reina en la casilla (fil, col) si está libre.
    // Si se coloca, marca las casillas vigiladas por ella.
    // Devuelve true si se pudo colocar, false en caso contrario.
    // PRE: 0 <= fil < Dimension(), 0 <= col < Dimension()
    bool ColocaReina(int fil, int col)
    {
        bool colocada = false;

        if(matriz_privada[fil][col] == LIBRE)
        {
            MarcarCasillasVigiladas(fil, col);

            // La reina se coloca después de marcar
            matriz_privada[fil][col] = REINA; 
            colocada = true;
        }
        return colocada;
    }

    /***********************************************************************/
    // Imprime el estado actual del tablero en la consola.
    void Imprimir(void)
    {
        cout << "  ";
        for (int j = 0; j < TAM; j++) {
            cout << " " << j;
        }
        cout << "\n  -";
        for (int j = 0; j < TAM; j++) {
            cout << "--";
        }
        cout << endl;

        for (int i = 0; i < TAM; i++) {
            cout << i << "|";
            for (int j = 0; j < TAM; j++) {
                cout << " " << matriz_privada[i][j];
            }
            cout << " |" << endl;
        }
        cout << "  -";
        for (int j = 0; j < TAM; j++) {
            cout << "--";
        }
        cout << endl;
    }
private:
    /***********************************************************************/
    // Marca como vigiladas la fila, columna y diagonales de una reina
    // colocada en (fil, col).
    // PRE: 0 <= fil < Dimension(), 0 <= col < Dimension()
    void MarcarCasillasVigiladas(int fil, int col)
    {
        // Marcar la fila como vigilada
        for (int j = 0; j < TAM; j++){
            if (matriz_privada[fil][j] == LIBRE)
                matriz_privada[fil][j] = VIGILADO;
        }
        // Marcar la columna como vigilada
        for (int i = 0; i < TAM; i++){
            if (matriz_privada[i][col] == LIBRE)
                matriz_privada[i][col] = VIGILADO;
        }

        // Marcar las diagonales
        // Para ello recorro todas las casillas e intento marcarlas si se
        // encuentran en una diagonal desde la reina
        for (int i = 0; i < TAM; i++) 
        {
            for (int j = 0; j < TAM; j++) 
            {
                // Si i - j = fil - col, entonces es la diagonal principal
                // Si i + j = fil + col, entonces es la diagonal secundaria
                if (i - j == fil - col || i + j == fil + col) 
                {
                    if (matriz_privada[i][j] == LIBRE) {
                        matriz_privada[i][j] = VIGILADO;
                    }
                }
            }
        }
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
};

/***************************************************************************/
/***************************************************************************/

int main()
{
    Lector lector;

    cout << "--- PROBLEMA DE LAS N REINAS ---" << endl;
    // El tamaño del tablero es fijo (8x8) según la clase Tablero.
    cout << "El tablero es de " << Tablero().Dimension() << "x" 
         << Tablero().Dimension() << "." << endl;

    lector.SetTitulo("Introduce el numero de reinas a colocar (1-8): ");
    int num_reinas = lector.LeeEnteroEnRango(1, Tablero().Dimension());

    Tablero tablero(num_reinas);

    bool juego_terminado = false;

    while (!juego_terminado) 
    {
        tablero.Imprimir();

        cout << "Reinas colocadas: " << tablero.NumReinasColocadas() 
             << "/" << tablero.NumReinasObjetivo() << endl;
        cout << "Casillas libres: " << tablero.NumCasillasLibres() << endl;

        // Comprobar si se ha ganado
        if (tablero.NumReinasColocadas() == tablero.NumReinasObjetivo()) 
        {
            cout << "\nHAS GANADO: Has colocado todas las reinas "
                 << "correctamente." << endl;
            juego_terminado = true;
        } 
        // Comprobar si se ha perdido
        else if (tablero.NumCasillasLibres() == 0) 
        {
            cout << "\nHAS PERDIDO: No quedan casillas libres para colocar mas " 
                 << "reinas." << endl;
            juego_terminado = true;
        } 
        // Si el juego no ha terminado, pedir la siguiente jugada
        else {
            cout << "\nColoca la siguiente reina:" << endl;
            
            lector.SetTitulo("Fila (0-7): ");
            int fila = lector.LeeEnteroEnRango(0, tablero.Dimension() - 1);

            lector.SetTitulo("Columna (0-7): ");
            int col = lector.LeeEnteroEnRango(0, tablero.Dimension() - 1);

            if (tablero.ColocaReina(fila, col)) 
            {
                cout << "Reina colocada en (" << fila << ", " << col << ")." 
                     << endl;
            } else 
            {
                cout << "¡Error! La casilla (" << fila << ", " << col 
                     << ") no esta libre. Intentalo de nuevo." << endl;
            }
            cout << "----------------------------------------" << endl;
        }
    }

    cout << "\n--- ESTADO FINAL DEL TABLERO ---" << endl;
    tablero.Imprimir();

    return 0;
}

/***************************************************************************/
/***************************************************************************/