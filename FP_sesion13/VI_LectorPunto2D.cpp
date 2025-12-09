/***************************************************************************
// FUNDAMENTOS DE PROGRAMACION
//
// MARIO MARTINEZ CALLEJON
//
// SESION 13
/*
    Este programa define y utiliza un conjunto de clases para leer puntos
    en un plano 2D y determinar su posición (cuadrante o eje).

    Clases implementadas:

    - LectorDouble: Clase de utilidad para leer números reales
    (double) desde la entrada del usuario, validando el formato.

    - Punto2D: Representa un punto en un plano cartesiano con coordenadas (x, y)
      Proporciona métodos para manipular el punto y calcular distancias.

    - LectorPunto2D: Utiliza LectorDouble para leer las coordenadas y crear
      un objeto Punto2D.

    El programa principal pide al usuario que introduzca puntos 2D de forma
    repetida. Para cada punto, indica en qué cuadrante se encuentra o si
    está sobre uno de los ejes. El programa finaliza cuando el usuario
    introduce el punto de origen (0,0).

    Entradas: Coordenadas x e y (reales) para cada punto.
    Salidas: Mensajes indicando la posición de cada punto y un mensaje de
             finalización.
*/
//**************************************************************************/
#include <iostream>
#include <cmath>

using namespace std;

/***************************************************************************/
// Definición de la clase LectorDouble
/***************************************************************************/
class LectorDouble {
private:

    string titulo; // Título a mostrar en las peticiones de lectura

public:
    /***********************************************************************/
    // Constructor por defecto
    LectorDouble() 
        : titulo("") 
    {}

    /***********************************************************************/
    // Constructor con parámetros.
    // Parámetros: nuevo_titulo, el mensaje que se mostrará al leer.
    LectorDouble(string nuevo_titulo) 
        : titulo(nuevo_titulo) 
    {}

    /***********************************************************************/
    // Establece el título que se mostrará en las lecturas.
    // Parámetros: nuevo_titulo, el nuevo mensaje a mostrar.
    void SetTitulo(string nuevo_titulo) {
        titulo = nuevo_titulo;
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

private:

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
};

/***************************************************************************/
// Definición de la clase Punto2D
/***************************************************************************/
class Punto2D
{
private:

    double x, y;    // Valores x e y del punto

public:

    /***********************************************************************/
    // Constructor por defecto
    Punto2D(void) {};

    /***********************************************************************/
    // Constructor con parámetros.
    // Parámetros: valor_x, el valor de la abscisa
    //             valor_y, el valor de la ordenada
    Punto2D(double valor_x, double valor_y) 
        : x(valor_x), y(valor_y)
    {}

    /***********************************************************************/
    // Modifica la coordenada x del punto.
    // Parámetros: valor_x, el nuevo valor para la coordenada x.
    void SetX(double valor_x)
    {
        x = valor_x;
    }

    /***********************************************************************/
    // Modifica la coordenada y del punto.
    // Parámetros: valor_y, el nuevo valor para la coordenada y.
    void SetY(double valor_y)
    {
        y = valor_y;
    }

    /***********************************************************************/
    // Devuelve la coordenada x del punto.
    double GetX(void)
    {
        return x;
    }

    /***********************************************************************/
    // Devuelve la coordenada y del punto.
    double GetY(void)
    {
        return y;
    }

    /***********************************************************************/
    // Calcula la distancia euclidiana entre este punto y otro.
    // Parámetros: p, el otro punto para calcular la distancia.
    // Devuelve: la distancia entre los dos puntos.
    double Distancia(Punto2D p)
    {
        double diff_x = x - p.GetX();
        double diff_y = y - p.GetY();
        return sqrt(pow(diff_x, 2) + pow(diff_y, 2));
    }

    /***********************************************************************/
    // Comprueba si este punto es igual a otro (mismas coordenadas).
    // Parámetros: p, el punto con el que se compara.
    // Devuelve: true si los puntos son iguales, false en caso contrario.
    bool EsIgual(Punto2D p)
    {
        bool igual = false;

        // Compara las coordenadas x e y de ambos puntos.
        if (x == p.GetX() && y == p.GetY()) 
            igual = true;
        
        return igual;
    }

    /***********************************************************************/
    // Convierte las coordenadas del punto a un formato de cadena "(x, y)".
    // Devuelve: una cadena que representa el punto.
    string ToString(void)
    {
        string punto_str = "(";

        punto_str += to_string(x);
        punto_str += ", ";
        punto_str += to_string(y);
        punto_str += ")";

        return punto_str;
    }
};

/***************************************************************************/
// Definición de la clase LectorPunto2D
/***************************************************************************/
class LectorPunto2D
{
private:
    string mensaje = ""; // Mensaje a mostrar antes de la lectura.

public:
    /***********************************************************************/
    // Constructor por defecto.
    LectorPunto2D (void) {}

    /***********************************************************************/
    // Constructor con parámetros.
    // Parámetros: el_mensaje, el mensaje a mostrar al leer un punto.
    LectorPunto2D (string el_mensaje)
        : mensaje(el_mensaje)
    {}

    /***********************************************************************/
    // Establece el mensaje que se mostrará en las lecturas.
    // Parámetros: nuevo_mensaje, el nuevo mensaje a mostrar.
    void SetMensaje (string nuevo_mensaje)
    {
        mensaje = nuevo_mensaje;
    }

    /***********************************************************************/
    // Devuelve el mensaje de lectura actual.
    string GetMensaje (void)
    {
        return mensaje;
    }

    /***********************************************************************/
    // Lee un punto 2D del usuario, mostrando el mensaje de la clase.
    // Devuelve: un objeto Punto2D con las coordenadas leídas.
    Punto2D Lee (void)
    {
        double x,y;

        cout << mensaje << endl;

        // Usa LectorDouble para leer la coordenada x.
        LectorDouble lector_double("Introduzca el valor de x: ");
        x = lector_double.LeeReal();

        // Reutiliza el lector para la coordenada y.
        lector_double.SetTitulo("Introduzca el valor de y: ");
        y = lector_double.LeeReal();

        return Punto2D(x, y);
    }

    /***********************************************************************/
    // Lee un punto 2D del usuario, mostrando un mensaje específico.
    // Parámetros: el_mensaje, el mensaje a mostrar para esta lectura.
    // Devuelve: un objeto Punto2D con las coordenadas leídas.
    Punto2D Lee (string el_mensaje)
    {
        double x,y;

        cout << el_mensaje << endl;

        LectorDouble lector_double("Introduzca el valor de x: ");
        x = lector_double.LeeReal();

        lector_double.SetTitulo("Introduzca el valor de y: ");
        y = lector_double.LeeReal();

        return Punto2D(x, y);
    }
};

/***************************************************************************/
// Programa principal
/***************************************************************************/
int main()
{
    LectorPunto2D lector_punto;
    Punto2D punto_leido;
    Punto2D origen(0, 0);

    cout << "Introduzca puntos para saber su cuadrante." << endl;
    cout << "La lectura finalizara cuando introduzca el origen (0,0)." << endl;
    cout << "--------------------------------------------------------" << endl;

    // Bucle principal: se ejecuta hasta que el usuario introduce el origen.
    do {
        // Leer un nuevo punto
        punto_leido = lector_punto.Lee("Nuevo punto:");

        // Comprobar si el punto es el origen para terminar
        if (!punto_leido.EsIgual(origen)) {
            
            cout << "El punto " << punto_leido.ToString();

            double x = punto_leido.GetX();
            double y = punto_leido.GetY();

            // Determinar el cuadrante o eje donde se encuentra el punto.
            if (x > 0 && y > 0) {
                cout << " se encuentra en el Cuadrante I." << endl;
            } else if (x < 0 && y > 0) {
                cout << " se encuentra en el Cuadrante II." << endl;
            } else if (x < 0 && y < 0) {
                cout << " se encuentra en el Cuadrante III." << endl;
            } else if (x > 0 && y < 0) {
                cout << " se encuentra en el Cuadrante IV." << endl;
            } else if (x == 0 && y != 0) {
                // Si x es 0 pero y no, está en el eje Y.
                cout << " se encuentra sobre el eje Y." << endl;
            } else if (x != 0 && y == 0) {
                cout << " se encuentra sobre el eje X." << endl;
            }
            cout << endl;
        }
    } while (!punto_leido.EsIgual(origen));

    cout << "\nSe ha introducido el origen. Programa finalizado." << endl;
    return 0;
}

/***************************************************************************/
/***************************************************************************/