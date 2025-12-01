/***************************************************************************/
// FUNDAMENTOS DE PROGRAMACION
//
// MARIO MARTINEZ CALLEJON
//
// SESION 12
/*
    Programa que busca el palíndromo más largo dentro de una secuencia
    de caracteres.

    Implementa una clase `SecuenciaCaracteres` que, además de las
    operaciones básicas, incluye un método `MayorPalindromoContenido`.
    Este método examina todas las posibles subsecuencias, de mayor a menor
    longitud, y devuelve la primera que resulta ser un palíndromo.

    Entradas: Ninguna. El programa contiene una batería de pruebas fija
              en la función `main`.

    Salidas: Muestra por pantalla los resultados de las pruebas, indicando
             la secuencia original y el palíndromo más largo encontrado en
             cada caso.
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
    // Extrae y devuelve una nueva secuencia que es una sección de la original.
    //
    // Parámetros:
    //   indice (int): el índice de inicio de la subsecuencia.
    //   longitud (int): el número de caracteres a extraer.
    //
    // Devuelve: Una nueva SecuenciaCaracteres que contiene la subsecuencia.
    //
    // PRE: indice >= 0, longitud >= 0, indice + longitud <= total_utilizados
    SecuenciaCaracteres SubSecuencia(int indice, int longitud)
    {
        SecuenciaCaracteres subsecuencia;

        // Recorre la sección del vector original y añade cada carácter
        // a la nueva subsecuencia.
        for (int i = 0; i < longitud; i++)
        {
            subsecuencia.Aniade(vector_privado[indice + i]);
        }

        return subsecuencia;
    }

    /*********************************************************/
    // Comprueba si una subsecuencia, definida por un índice y una longitud,
    // es un palíndromo.
    //
    // Parámetros:
    //   indice (int): el índice donde inicia la subsecuencia.
    //   longitud (int): la longitud de la subsecuencia.
    //
    // Devuelve: "true" si la subsecuencia es un palíndromo, "false" si no.
    //
    // PRE: indice + longitud <= total_utilizados
    bool EsPalindromo_Subsecuencia(int indice, int longitud) 
    {
        bool es_palindromo = true;
        SecuenciaCaracteres subsecuencia;
        
        // Utilizar el método SubSecuencia para obtener la subsecuencia.
        subsecuencia = SubSecuencia(indice, longitud);

        // Crea una versión invertida de la subsecuencia para comparar.
        SecuenciaCaracteres invertida = subsecuencia.Invierte();

        // Compara la subsecuencia con su inversa, carácter por carácter.
        for (int i = 0; (i < subsecuencia.TotalUtilizados()) 
                        && es_palindromo; i++)
        {
            if (subsecuencia.Elemento(i) != invertida.Elemento(i))
            {   
                // Si son diferentes no es palíndromo
                es_palindromo = false;
            } 
        }

        return es_palindromo;
    }

    /*********************************************************/
    // Busca y devuelve el palíndromo más largo contenido en la secuencia.
    // Itera desde la longitud máxima posible hacia abajo y devuelve el
    // primer palíndromo que encuentra, que por definición será el más largo.
    //
    // Devuelve: Una nueva SecuenciaCaracteres con el palíndromo más largo.
    // Si no hay palíndromos de longitud > 1, devuelve uno de longitud 1.
    SecuenciaCaracteres MayorPalindromoContenido ()
    {
        bool encontrado = false;
        SecuenciaCaracteres mayor_palindromo;
        
        // Itera por todas las longitudes posibles, de mayor a menor. Al 
        // encontrar el primer palíndromo, nos aseguramos de que es el más largo
        for(int len = total_utilizados; (len >=1) && (!encontrado); len--)
        {
            // Itera por todos los índices de inicio posibles para una longitud 
            // dada.
            for(int i = 0; (i + len <= total_utilizados) && (!encontrado) ; i++)
            {
                // Comprueba si la subsecuencia actual es un palíndromo.
                if(EsPalindromo_Subsecuencia(i, len))
                {
                    encontrado = true;
                    // Si lo es, la guarda y sale de los bucles.
                    mayor_palindromo = SubSecuencia(i, len);
                }
            }
        }

        return mayor_palindromo;
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

    private:

    /*********************************************************/
    // Intercambia dos componentes de la secuencia.
    //
    // Parámetros:
    //   indice_1 (int): índice del primer elemento.
    //   indice_2 (int): índice del segundo elemento.
    //
    // PRE: 0 <= indice_1, indice_2 < total_utilizados
    void IntercambiaComponentes(int indice_1, int indice_2)
    {
        // Guarda el primer valor en una variable temporal.
        char temp = vector_privado[indice_1];

        vector_privado[indice_1] = vector_privado[indice_2];
        // Asigna el valor guardado al segundo elemento.
        vector_privado[indice_2] = temp;
    }

    /*********************************************************/
    // Crea y devuelve una nueva secuencia que es la inversa de la
    // original. La secuencia original no se modifica.
    // Utiliza el método privado IntercambiaComponentes.
    //
    // Devuelve: Una nueva SecuenciaCaracteres que es la inversa de la original.
    SecuenciaCaracteres Invierte() 
    {
        SecuenciaCaracteres temporal;

        // Crea una copia exacta de la secuencia original.
        for (int i = 0; i < total_utilizados; i++)
        {
            temporal.Aniade(vector_privado[i]);
        }

        // Invierte la copia intercambiando los elementos simétricamente.
        for(int i = 0; i < (total_utilizados / 2); i++)
        {
            int j = total_utilizados - i - 1; // Índice simétrico desde el final
            temporal.IntercambiaComponentes(i, j);
        }
        
        //Devuelve la copia ya invertida.
        return temporal;
    }
};

//**************************************************************************/
// Función main
//**************************************************************************/

int main() {

    cout << "BATERIA DE PRUEBAS PARA MayorPalindromoContenido" << endl;
    cout << "===============================================" << endl << endl;

    SecuenciaCaracteres secuencia;
    string texto_prueba;

    // Prueba 1: Con un palíndromo complejo en su interior.
    // Esperado: "ABCCBA"
    texto_prueba = "gAAtySHHSvvABCCBAfh";
    secuencia.EliminaTodos();

    for (int i = 0; i < texto_prueba.length(); i++) 
    {
        secuencia.Aniade(texto_prueba.at(i));
    }

    cout << "Probando: \"" << secuencia.ToString() << "\"" << endl;
    SecuenciaCaracteres resultado1 = secuencia.MayorPalindromoContenido();

    cout << "Palindromo mas largo: \"" << resultado1.ToString() << "\"" << endl;
    cout << endl;

    // Prueba 2: Sin palíndromos de longitud > 1.
    // Esperado: "A" (o cualquier carácter individual)
    texto_prueba = "ABCDEF";
    secuencia.EliminaTodos();

    for (int i = 0; i < texto_prueba.length(); i++) 
    {
        secuencia.Aniade(texto_prueba.at(i));
    }

    cout << "Probando: \"" << secuencia.ToString() << "\"" << endl;
    SecuenciaCaracteres resultado2 = secuencia.MayorPalindromoContenido();

    cout << "Palindromo mas largo: \"" << resultado2.ToString() << "\"" << endl;
    cout << endl;

    // Prueba 3: La secuencia entera es un palíndromo.
    // Esperado: "AABBAABBAA"
    texto_prueba = "AABBAABBAA";
    secuencia.EliminaTodos();

    for (int i = 0; i < texto_prueba.length(); i++) 
    {
        secuencia.Aniade(texto_prueba.at(i));
    }

    cout << "Probando: \"" << secuencia.ToString() << "\"" << endl;
    SecuenciaCaracteres resultado3 = secuencia.MayorPalindromoContenido();

    cout << "Palindromo mas largo: \"" << resultado3.ToString() << "\"" << endl;
    cout << endl;

    // Prueba 4: Con varios palíndromos, encuentra el más largo.
    // Esperado: "RACECAR"
    texto_prueba = "ABARACECARDEF";
    secuencia.EliminaTodos();

    for (int i = 0; i < texto_prueba.length(); i++) 
    {
        secuencia.Aniade(texto_prueba.at(i));
    }

    cout << "Probando: \"" << secuencia.ToString() << "\"" << endl;
    SecuenciaCaracteres resultado4 = secuencia.MayorPalindromoContenido();

    cout << "Palindromo mas largo: \"" << resultado4.ToString() << "\"" << endl;
    cout << endl;

    return 0;
}

//**************************************************************************/
//**************************************************************************/