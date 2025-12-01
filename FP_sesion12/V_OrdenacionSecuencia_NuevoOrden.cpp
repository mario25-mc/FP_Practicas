//***************************************************************************/
// FUNDAMENTOS DE PROGRAMACION
//
// MARIO MARTÍNEZ CALLEJÓN
//
// SESION 12
/*
    Programa que gestiona una secuencia de enteros y aplica sobre ella
    diferentes algoritmos de ordenación (Selección, Inserción, Burbuja)
    basados en un criterio de comparación no tradicional.

    El programa permite elegir entre dos criterios de ordenación alternativos
    modificando una constante en el código:
    1) Frecuencia de dígitos: Un número es mayor que otro si tiene más
       dígitos '9'. En caso de empate, se compara por el número de '8',
       y así sucesivamente hasta el '0'.
    2) Valor reflejado: Un número es mayor que otro si su reflejo es mayor.

    Entradas:
        - num_elementos: El número de enteros a generar y ordenar,
                         introducido por el usuario.
        - opcion_criterio: Seleccionador del criterio de ordenación.

    Salidas:
        - La secuencia de números aleatorios original.
        - La secuencia ordenada según el criterio seleccionado.
*/
//**************************************************************************/

#include <iostream>
#include <random>  // para la generación de números pseudoaleatorios
#include <chrono>  // para la semilla

using namespace std;

//**************************************************************************/
// Enumeración para definir los criterios de ordenación disponibles.
//**************************************************************************/

enum CriterioOrden {
    FRECUENCIA, // Criterio basado en la frecuencia de dígitos (9, 8, 7...)
    REFLEJO     // Criterio basado en el valor reflejado del número
};

//**************************************************************************/
// Definición de la clase GeneradorAleatorioEnteros
//**************************************************************************/

class GeneradorAleatorioEnteros
{  
private:
	
	mt19937 generador_mersenne;    // Mersenne twister
	uniform_int_distribution<int>  distribucion_uniforme;
	
	/************************************************************************/ 
	
public:

	/************************************************************************/
	// Constructor para generar valores aleatorios [0,1]

	GeneradorAleatorioEnteros(void) : GeneradorAleatorioEnteros(0, 1) 
	{ }
	
	/************************************************************************/
	// Constructor para generar valores aleatorios [min,max]

	GeneradorAleatorioEnteros(int min, int max) 
	{	
		const int A_DESCARTAR = 70000;
		// ACM TOMS Volume 32 Issue 1, March 2006
		
		auto semilla = Nanosec();
		generador_mersenne.seed(semilla);
		generador_mersenne.discard(A_DESCARTAR);
		distribucion_uniforme = uniform_int_distribution<int> (min, max);
	}
	
	/************************************************************************/
	// Devuelve un número aleatorio de acuerdo a los valores indicados en 
	// la inicialización. 
	
	int Siguiente(){
	  return (distribucion_uniforme(generador_mersenne));
	}
	
	/************************************************************************/
	
private: 

	/************************************************************************/
	// Brevemente: obtiene el número de nanosegundos que ha transcurrido 
	// desde la "Unix epoch" (01/01/1970). Un buen valor para ser "semilla" 
	// de un generador de números aleatorios. 
	
	long long Nanosec(){
		
		return (chrono::high_resolution_clock::
				now().time_since_epoch().count());
	}
	
	/************************************************************************/
};

//**************************************************************************/
// Definición de la clase SecuenciaEnteros
//**************************************************************************/

class SecuenciaEnteros {
private:

    static const int TAMANIO = 50; // Núm.casillas disponibles
    int vector_privado[TAMANIO];

    // PRE: 0<=total_utilizados<=TAMANIO
    int total_utilizados; // Núm.casillas ocupadas

    // Almacena el criterio de ordenación que se usará en los métodos.
    CriterioOrden criterio_activo;

public:
    /*********************************************************/
    // Constructor sin argumentos
    // Por defecto, el criterio es por frecuencia.
    SecuenciaEnteros (void) 
        : total_utilizados (0), criterio_activo(FRECUENCIA) 
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
    // Establece el criterio de ordenación a utilizar.
    void SetCriterioOrden(CriterioOrden nuevo_criterio)
    {
        criterio_activo = nuevo_criterio;
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

    /*********************************************************/
    // Ordena la secuencia usando el método de Selección,
    // basado en el nuevo criterio de orden.
    void OrdenaSeleccion_NuevoOrden()
    {
        int pos_min;

        // El bucle externo recorre el vector para colocar el elemento 
        // correcto en cada posición.
        for (int izda=0; izda<total_utilizados-1; izda++) {
            
            // Suponemos que el mínimo está al principio de la zona no ordenada.
            pos_min = izda; 

            // Buscamos la posición del elemento "menor" en la zona no ordenada.
            for (int j=izda+1; j<total_utilizados; j++)

                if (EsMayor_NuevoOrden(vector_privado[pos_min], 
                                      vector_privado[j])) 
                    pos_min = j;

            // Intercambiamos el mínimo encontrado con el elemento de la
            // posición "izda".
            int aux = vector_privado[izda];
            vector_privado[izda] = vector_privado[pos_min];
            vector_privado[pos_min] = aux;
        }
    }

    /*********************************************************/
    // Ordena la secuencia usando el método de Inserción,
    // basado en el nuevo criterio de orden.
    void OrdenaInsercion_NuevoOrden()
    {
        // El bucle externo empieza en 1, considerando que un vector 
        // de 1 elemento ya está ordenado.
        for (int izda = 1; izda < total_utilizados; izda++){

            // "a_insertar" es el valor que tomamos de la zona no ordenada 
            // para colocarlo en la zona ordenada.
            int a_insertar = vector_privado[izda];

            // Buscamos la posición correcta para "a_insertar" en la zona 
            // ordenada (0 hasta izda-1). Mientras buscamos, desplazamos los 
            // elementos mayores hacia la derecha.
            int i = izda;
            while (( i > 0 ) && 
                  (EsMayor_NuevoOrden(vector_privado[i-1], a_insertar))) 
            {
                // Desplazar a la derecha
                vector_privado[i] = vector_privado[i-1]; 
                i--;
            }

            // Colocamos el elemento en el "hueco" creado.
            vector_privado[i] = a_insertar; 
        }
    }

    /*********************************************************/
    // Ordena la secuencia usando el método de Intercambio (Burbuja),
    // basado en el nuevo criterio de orden.
    void OrdenaIntercambio_NuevoOrden()
    {
        int aux;

        for (int i=0; i<total_utilizados-1; i++)
            for (int j=total_utilizados-1; j>i; j--)
                if (EsMayor_NuevoOrden(vector_privado[j-1], vector_privado[j])) 
                {
                    aux = vector_privado[j];
                    vector_privado[j] = vector_privado[j-1];
                    vector_privado[j-1] = aux;
                }
    }

    /*********************************************************/
    // Ordena la secuencia usando el método de Intercambio (Burbuja) Mejorado,
    // basado en el nuevo criterio de orden.
    void OrdenaIntercambioMejorado_NuevoOrden()
    {
        int aux;
        bool cambio = true;

        for (int i=0; i<total_utilizados-1 && cambio; i++) {
            cambio = false;
            for (int j=total_utilizados-1; j>i; j--)
                if (EsMayor_NuevoOrden(vector_privado[j-1], vector_privado[j])) 
                {
                    aux = vector_privado[j];
                    vector_privado[j] = vector_privado[j-1];
                    vector_privado[j-1] = aux;
                    cambio = true;
                }
        }
    }

private:

    /*********************************************************/
    // Función auxiliar que encapsula el criterio de comparación.
    // Devuelve "true" si a > b según el nuevo orden.
    // Para cambiar el criterio, solo hay que modificar esta función.
    bool EsMayor_NuevoOrden(int a, int b)
    {
        bool resultado = false;   // valor por defecto: no es mayor
        bool decidido = false;    // indica si ya se ha decidido el resultado

        if (criterio_activo == FRECUENCIA) {
            // Criterio 1: Frecuencia de dígitos (de 9 a 0)
            for (int digito = 9; digito >= 0 && !decidido; digito--) 
            {
                int frec_a = ContarDigitos(a, digito);
                int frec_b = ContarDigitos(b, digito);

                if (frec_a > frec_b) 
                {
                    resultado = true;
                    decidido = true;
                } else if (frec_a < frec_b) 
                {
                    resultado = false;
                    decidido = true;
                }
                // Si son iguales, seguimos al siguiente dígito
            }
            // Si nunca se decidió, resultado sigue en false 
            // (iguales según este criterio)

        } else { // criterio_activo == REFLEJO
            // Criterio 2: Reflejo de los números
            resultado = (Reflejo(a) > Reflejo(b));
        }

        return resultado;
    }

    /*********************************************************/
    // Función auxiliar para el criterio de frecuencia.
    // Cuenta cuántas veces aparece un dígito en un número.
    int ContarDigitos(int n, int digito_a_buscar)
    {
        int contador = 0;

        if (n == 0 && digito_a_buscar == 0) {
            contador = 1;
        } else {
            int n_abs = abs(n);
            while (n_abs > 0) {
                if (n_abs % 10 == digito_a_buscar) 
                {
                    contador++;
                }
                n_abs /= 10;
            }
        }
        return contador;
    }



    /*********************************************************/
    // Función auxiliar para el criterio del reflejo.
    // Devuelve el valor reflejado de un número.
    int Reflejo(int n) {
        int reflejado = 0;
        int n_abs = abs(n);

        while (n_abs > 0) {
            reflejado = reflejado * 10 + (n_abs % 10);
            n_abs /= 10;
        }

        return (n < 0) ? -reflejado : reflejado;
    }
};

//**************************************************************************/
//**************************************************************************/

int main()
{
    const int MIN_VAL = 0;
    const int MAX_VAL = 999;
    int num_elementos, opcion_criterio;

    cout << "Cuantos elementos quiere generar (0-";
    cout << SecuenciaEnteros().Capacidad() << ")? ";
    cin >> num_elementos;

    cout << "\nSeleccione el criterio de ordenacion:" << endl;
    cout << "1. Frecuencia de digitos (9, 8, 7...)" << endl;
    cout << "2. Valor reflejado" << endl;
    cout << "Opcion: ";
    cin >> opcion_criterio;

    while (opcion_criterio != 1 && opcion_criterio != 2) 
    {
        cout << "Opcion no valida. Introduzca 1 o 2: ";
        cin >> opcion_criterio;
    }

    SecuenciaEnteros secuencia_original;
    GeneradorAleatorioEnteros generador(MIN_VAL, MAX_VAL);

    if (num_elementos > 0 && num_elementos <= secuencia_original.Capacidad()) {
        for (int i = 0; i < num_elementos; i++) {
            secuencia_original.Aniade(generador.Siguiente());
        }

        // Establecer el criterio elegido por el usuario
        if (opcion_criterio == 2) {
            secuencia_original.SetCriterioOrden(REFLEJO);
        } // Si es 1, se queda el de por defecto (FRECUENCIA)

        cout << "\nSecuencia original:" << endl;
        cout << secuencia_original.ToString() << endl;

        // Se crea una copia para cada método de ordenación para no
        // modificar la secuencia original.

        // Prueba con OrdenaSeleccion_NuevoOrden
        SecuenciaEnteros secuencia_a_ordenar = secuencia_original;
        secuencia_a_ordenar.OrdenaSeleccion_NuevoOrden();
        cout << "\nOrdenada con Seleccion:" << endl;
        cout << secuencia_a_ordenar.ToString() << endl;

        // Prueba con OrdenaInsercion_NuevoOrden
        secuencia_a_ordenar = secuencia_original; // Restaurar
        secuencia_a_ordenar.OrdenaInsercion_NuevoOrden();
        cout << "\nOrdenada con Insercion:" << endl;
        cout << secuencia_a_ordenar.ToString() << endl;

        // Prueba con OrdenaIntercambio_NuevoOrden
        secuencia_a_ordenar = secuencia_original; // Restaurar
        secuencia_a_ordenar.OrdenaIntercambio_NuevoOrden();
        cout << "\nOrdenada con Burbuja:" << endl;
        cout << secuencia_a_ordenar.ToString() << endl;

        // Prueba con OrdenaIntercambioMejorado_NuevoOrden
        secuencia_a_ordenar = secuencia_original; // Restaurar
        secuencia_a_ordenar.OrdenaIntercambioMejorado_NuevoOrden();
        cout << "\nOrdenada con Burbuja Mejorada:" << endl;
        cout << secuencia_a_ordenar.ToString() << endl;

    } else {
        cout << "Numero de elementos invalido." << endl;
    }

    return 0;
}

//**************************************************************************/
//**************************************************************************/