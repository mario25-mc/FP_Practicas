/***************************************************************************/
// FUNDAMENTOS DE PROGRAMACION
//
// MARIO MARTINEZ CALLEJON
//
// SESION 12
/*
    Programa que comprueba si una secuencia de caracteres es un palíndromo.

    Implementa una clase `SecuenciaCaracteres` que incluye un método
    `EsPalindromo_Alternativo`. Este método determina si la secuencia es
    un palíndromo creando una versión invertida de sí misma y comparándola
    con la original, carácter por carácter.

    Entradas: Ninguna. El programa contiene una batería de pruebas fija
              en la función `main`.

    Salidas: Muestra por pantalla los resultados de las pruebas, indicando
             si cada secuencia es un palíndromo y si el resultado es correcto.
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
    // Comprueba si la secuencia es un palíndromo.
    // Un palíndromo se lee igual de izquierda a derecha que de
    // derecha a izquierda.
    // Crea una copia invertida de la secuencia y la compara con
    // la original.
    bool EsPalindromo_Alternativo() 
    {
        bool es_palindromo = true;

        // Se ejecuta el constructor de copia con la secuencia invertida
        SecuenciaCaracteres invertida = Invierte();

        // Se comparan la secuencia original y la invertida elemento a elemento.
        for (int i = 0; (i < total_utilizados) && es_palindromo; i++)
        {
            if (vector_privado[i] != invertida.Elemento(i))
            {   
                // Si son diferentes no es palíndromo
                es_palindromo = false;
            } 
        }

        return es_palindromo;
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
    // Utiliza el método privado IntercambiaComponentes
    SecuenciaCaracteres Invierte() 
    {
        SecuenciaCaracteres invertida;

        // Crea una copia exacta de la secuencia original.
        for (int i = 0; i < total_utilizados; i++)
        {
            invertida.Aniade(vector_privado[i]);
        }

        // Invierte la copia intercambiando los elementos simétricamente.
        for(int i = 0; i < (total_utilizados / 2); i++)
        {
            int j = total_utilizados - i - 1; // Índice simétrico desde el final
            invertida.IntercambiaComponentes(i, j);
        }
        
        //Devuelve la copia ya invertida.
        return invertida;
    }
};

//**************************************************************************/
// Función main
//**************************************************************************/

int main() {

    cout << "BATERIA DE PRUEBAS PARA EsPalindromo_Alternativo()" << endl;
    cout << "================================================" << endl << endl;

    SecuenciaCaracteres secuencia;

    // Prueba 1: Palíndromo simple de longitud impar
    secuencia.EliminaTodos();
    secuencia.Aniade('A');
    secuencia.Aniade('N');
    secuencia.Aniade('A');
    cout << "Probando \"" << secuencia.ToString() << "\"         ";
    if (secuencia.EsPalindromo_Alternativo()) {
        cout << "Resultado: Es un palindromo. (Correcto)" << endl;
    } else {
        cout << "Resultado: NO es un palindromo. (Incorrecto)" << endl;
    }

    // Prueba 2: Palíndromo de longitud par
    secuencia.EliminaTodos();
    secuencia.Aniade('S');
    secuencia.Aniade('O');
    secuencia.Aniade('M');
    secuencia.Aniade('O');
    secuencia.Aniade('S');
    cout << "Probando \"" << secuencia.ToString() << "\"       ";
    if (secuencia.EsPalindromo_Alternativo()) {
        cout << "Resultado: Es un palindromo. (Correcto)" << endl;
    } else {
        cout << "Resultado: NO es un palindromo. (Incorrecto)" << endl;
    }

    // Prueba 3: Secuencia que no es un palíndromo
    secuencia.EliminaTodos();
    secuencia.Aniade('H');
    secuencia.Aniade('O');
    secuencia.Aniade('L');
    secuencia.Aniade('A');
    cout << "Probando \"" << secuencia.ToString() << "\"        ";
    if (!secuencia.EsPalindromo_Alternativo()) {
        cout << "Resultado: NO es un palindromo. (Correcto)" << endl;
    } else {
        cout << "Resultado: Es un palindromo. (Incorrecto)" << endl;
    }

    // Prueba 4: Secuencia vacía (considerada palíndromo)
    secuencia.EliminaTodos();
    cout << "Probando \"" << secuencia.ToString() << "\"            ";
    if (secuencia.EsPalindromo_Alternativo()) {
        cout << "Resultado: Es un palindromo. (Correcto)" << endl;
    } else {
        cout << "Resultado: NO es un palindromo. (Incorrecto)" << endl;
    }

    // Prueba 5: Secuencia con un solo carácter (considerada palíndromo)
    secuencia.Aniade('Z');
    cout << "Probando \"" << secuencia.ToString() << "\"           ";
    if (secuencia.EsPalindromo_Alternativo()) {
        cout << "Resultado: Es un palindromo. (Correcto)" << endl;
    } else {
        cout << "Resultado: NO es un palindromo. (Incorrecto)" << endl;
    }

    cout << "\n============================" << endl;
    cout << "FIN DE LA BATERIA DE PRUEBAS" << endl;

    return 0;
}

//**************************************************************************/
//**************************************************************************/