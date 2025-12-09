/***************************************************************************
// FUNDAMENTOS DE PROGRAMACION
//
// MARIO MARTINEZ CALLEJON
//
// SESION 13
/*
    Programa que utiliza varias clases para leer, procesar y mostrar
    puntos en un plano 2D. El programa principal solicita al usuario
    que introduzca coordenadas de puntos y, para cada uno, determina
    en qué cuadrante o sobre qué eje se encuentra. El programa finaliza
    cuando el usuario introduce el punto de origen (0,0).

    Clases implementadas:
    - LectorDouble: Para leer y validar números de tipo double.
    - Punto2D: Representa un punto con coordenadas (x, y).
    - LectorPunto2D: Utiliza LectorDouble para leer un Punto2D.
    - FormateadorPunto: Formatea un Punto2D para su visualización.

    Entradas:
        - Coordenadas x e y (double) para cada punto.

    Salidas:
        - Para cada punto, se muestra su representación formateada y su
          ubicación (cuadrante o eje) en la consola.
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
// Definición de la clase FormateadorPunto
/***************************************************************************/
class FormateadorPunto
{
private:
    static const int  ANCHO_TOTAL_DEF = 7;
    static const int  ANCHO_PARTE_DECIMAL_DEF  = 3;
    static const char RELLENO_DEF = ' ';
    static const char INICIO_DEF = '(';
    static const char FIN_DEF = ')';
    static const char SEPARADOR_DEF = ',';

    Punto2D p;                // El punto que se va a formatear
    int ancho_total;          // Ancho total
    int ancho_parte_decimal; // Ancho de la parte decimal
    char relleno;             // Carácter usado para rellenar los "huecos"
    char inicio;              // Carácter de apertura
    char fin;                 // Carácter de cierre
    char separador;           // Carácter separador

public:
    /***********************************************************************/
    // Constructor por defecto.
    FormateadorPunto (void)
        : p(0,0), ancho_total(ANCHO_TOTAL_DEF),
          ancho_parte_decimal(ANCHO_PARTE_DECIMAL_DEF),
          relleno(RELLENO_DEF), inicio(INICIO_DEF), fin(FIN_DEF),
          separador(SEPARADOR_DEF)
    {}

    /***********************************************************************/
    // Constructor con un punto. Usa valores por defecto para el formato.
    // Parámetros: 
    //   el_punto: El objeto Punto2D a formatear.
    FormateadorPunto (Punto2D el_punto)
        : p(el_punto), ancho_total(ANCHO_TOTAL_DEF),
          ancho_parte_decimal(ANCHO_PARTE_DECIMAL_DEF),
          relleno(RELLENO_DEF), inicio(INICIO_DEF), fin(FIN_DEF),
          separador(SEPARADOR_DEF)
    {}

    /***********************************************************************/
    // Constructor con punto y parámetros de formato (ancho y precisión).
    // Parámetros:
    //   el_punto: El objeto Punto2D a formatear.
    //   el_ancho_total: Ancho total para cada coordenada.
    //   el_ancho_parte_decimal: Número de decimales para cada coordenada.
    // PRE: el_ancho_total > 0, el_ancho_parte_decimal >= 0.
    FormateadorPunto (Punto2D el_punto, int el_ancho_total,
                      int el_ancho_parte_decimal)
        : p(el_punto), ancho_total(el_ancho_total),
          ancho_parte_decimal(el_ancho_parte_decimal),
          relleno(RELLENO_DEF), inicio(INICIO_DEF), fin(FIN_DEF),
          separador(SEPARADOR_DEF)
    {}

    /***********************************************************************/
    // Constructor con parámetros de formato. El punto se inicializa en (0,0).
    // Parámetros:
    //   el_ancho_total: Ancho total para cada coordenada.
    //   el_ancho_parte_decimal: Número de decimales para cada coordenada.
    // PRE: el_ancho_total > 0, el_ancho_parte_decimal >= 0.
    FormateadorPunto (int el_ancho_total, int el_ancho_parte_decimal)
        : p(0,0), ancho_total(el_ancho_total),
          ancho_parte_decimal(el_ancho_parte_decimal),
          relleno(RELLENO_DEF), inicio(INICIO_DEF), fin(FIN_DEF),
          separador(SEPARADOR_DEF)
    {}

    /***********************************************************************/
    // Establece los caracteres especiales para el formato.
    // Parámetros:
    //   el_relleno: Carácter para rellenar los huecos.
    //   el_inicio: Carácter de apertura.
    //   el_fin: Carácter de cierre.
    //   el_separador: Carácter para separar las coordenadas
    void SetParametros (char el_relleno, char el_inicio,
                        char el_fin, char el_separador) {
        relleno = el_relleno;
        inicio = el_inicio;
        fin = el_fin;
        separador = el_separador;
    }

    /***********************************************************************/
    // Establece o cambia el punto a formatear.
    // Parámetros:
    //   el_punto: El nuevo objeto Punto2D a formatear.
    void SetPunto (Punto2D el_punto) {
        p = el_punto;
    }

    /***********************************************************************/
    // Compone y devuelve una cadena con el punto formateado según los
    // parámetros de la clase.
    // Devuelve: una cadena con el punto formateado.
    string ToString (void) {
        string sx = FormateaCoordenada(p.GetX());
        string sy = FormateaCoordenada(p.GetY());

        return inicio + sx + separador + " " + sy + fin;
    }

private:
    /***********************************************************************/
    // Función de ayuda para formatear una coordenada (un número double) a
    // una cadena, aplicando el ancho y la precisión definidos en la clase.
    // Parámetros:
    //   valor: El número double a formatear.
    // Devuelve:
    //   Una cadena que representa el número formateado.
    string FormateaCoordenada(double valor) {
        // Manejar el signo
        string signo = "";
        if (valor < 0) {
            signo = "-";
            valor = -valor;
        }

        // Separar parte entera y decimal
        int parte_entera = static_cast<int>(valor);
        double parte_decimal_double = valor - parte_entera;

        // Convertir parte entera a cadena
        string str_entera = to_string(parte_entera);

        // Convertir parte decimal a cadena con la precisión deseada
        string str_decimal = "";

        if (ancho_parte_decimal > 0) 
        {
            str_decimal += ".";
            // Multiplicar para mover los decimales a la parte entera
            int decimal_como_entero = static_cast<int>
                   (round(parte_decimal_double * pow(10, ancho_parte_decimal)));

            string temp_decimal = to_string(decimal_como_entero);
            
            // Añadir ceros a la izquierda si es necesario para la precisión
            int ceros_faltantes = ancho_parte_decimal - temp_decimal.length();
            if (ceros_faltantes > 0) {
                for(int i = 0; i < ceros_faltantes; i++)
                {
                    str_decimal += '0';
                }
            }
            str_decimal += temp_decimal;
        }

        string numero_completo = signo + str_entera + str_decimal;

        // Añadir relleno a la izquierda para el ancho total
        string resultado;
        int relleno_necesario = ancho_total - numero_completo.length();

        if (relleno_necesario > 0) 
        {
            string str_relleno = "";

            for (int i = 0; i < relleno_necesario; i++) 
            {
                str_relleno += relleno;
            }
            resultado = str_relleno + numero_completo;
        } else 
        {
            resultado = numero_completo;
        }

        return resultado;
    }

};

/***************************************************************************/
// Programa principal
/***************************************************************************/
int main()
{
    LectorPunto2D lector_punto;
    FormateadorPunto formateador;
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
            
            // Usar el formateador para mostrar el punto
            formateador.SetPunto(punto_leido);

            cout << "El punto " << formateador.ToString();

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

    // Mensaje de fin del programa
    cout << "\nSe ha introducido el origen. Programa finalizado." << endl;
    return 0;
}

/***************************************************************************/
/***************************************************************************/
