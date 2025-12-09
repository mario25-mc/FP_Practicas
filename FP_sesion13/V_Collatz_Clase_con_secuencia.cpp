/***************************************************************************
// FUNDAMENTOS DE PROGRAMACION
//
// MARIO MARTINEZ CALLEJON
//
// SESION 13
/*
    Este programa calcula y analiza las secuencias de Collatz para un rango
    de números enteros positivos definidos por el usuario. Para cada número
    en el rango, se crea un objeto de la clase Collatz que almacena la
    secuencia en un objeto de la clase SecuenciaEnteros, imprime la secuencia y 
    su longitud. Finalmente, informa cuál fue el número (base) que generó la 
    secuencia más larga y cuál fue dicha longitud.

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

//**************************************************************************/
// Definición de la clase SecuenciaEnteros
//**************************************************************************/

class SecuenciaEnteros {
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

/***************************************************************************/
// Definición de la clase Collatz
/***************************************************************************/
class Collatz {
private:

    int base; // base de la sucesión, PRE: base >= 1

    SecuenciaEnteros sec; // SecuenciaEnteros donde se almacenan los valores

public:
    /***********************************************************************/
    // Constructor por defecto

    Collatz(void) {}

    /***********************************************************************/
    // Constructor con parámetros. 
    // PRE: n >= 1
    // Parámetros: n, el nuevo valor para la base.
    
    Collatz(int la_base)
        : base(la_base) 
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
        return sec.TotalUtilizados();
    }

    /***********************************************************************/
    // Devuelve el término en la posición 'pos' de la secuencia.
    // PRE: pos >= 0
    // Parámetros:
    //   pos, la posición del término a obtener (0 es la base).
    // Devuelve: el valor del término en la posición dada.

    int Valor(int pos) {
        int termino = sec.Elemento(pos);
        return termino;
    }

    /***********************************************************************/
    // Pasa la secuencia de Collatz a un dato string.

    string ToString() {

        string collatz_s = "\tCollatz(" + to_string(base) + ") = {";

        for (int i = 0; i < sec.TotalUtilizados(); i++) {
            collatz_s += to_string(sec.Elemento(i));
            if (i < sec.TotalUtilizados() - 1) {
                collatz_s += ", ";
            }
        }

        collatz_s += "}.";

        // Si la secuencia se cortó porque alcanzó el tamaño máximo
        // y el último término no es 1, se añade un mensaje de error.
        if (sec.TotalUtilizados() == sec.Capacidad() && 
            sec.Elemento(sec.TotalUtilizados() - 1) != 1){
            collatz_s += " (secuencia demasiado larga)";
        }
        return collatz_s;
    }

private:

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

        // Se deja un hueco al final por si la secuencia es muy larga
        // y hay que forzar la inclusión del 1.
        while ((actual != 1)) 
        {
            sec.Aniade(actual);
            actual = SiguienteCollatz(actual);
        }

        // Añadir el último término (siempre 1)
        sec.Aniade(1);
    }
};

/***************************************************************************/
// Definición de la clase Lector
/***************************************************************************/
class Lector {
private:

    string titulo; // Título a mostrar en las peticiones de lectura

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

private:
    
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

};

/***************************************************************************/
// Función main
/***************************************************************************/

int main()
{   
    int uno, otro;
    Lector lector_entrada("Introduzca un entero mayor que cero: ");
    
    // Entrada
    uno = lector_entrada.LeeEnteroMayorOIgual(1);

    lector_entrada.SetTitulo("Introduzca otro entero mayor que cero: ");
    otro = lector_entrada.LeeEnteroMayorOIgual(1);
    
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