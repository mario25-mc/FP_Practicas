/***************************************************************************
// FUNDAMENTOS DE PROGRAMACION
//
// MARIO MARTINEZ CALLEJON
//
// SESION 11
/*
    Este programa define la clase Lector, diseñada para facilitar la lectura
    y validación de datos de entrada del usuario. La clase proporciona
    métodos robustos para leer números enteros y reales, asegurando que
    los datos introducidos sean del tipo correcto y, opcionalmente, que
    cumplan con ciertas restricciones de rango.

    La clase encapsula la lógica de validación, como comprobar si una
    cadena es un número válido (entero o real) y gestionar bucles de
    lectura hasta que el usuario proporcione una entrada correcta.

    El programa principal ejecuta varios ejemplos para ver el funcionamiento
    de la clase Lector.
*/
//**************************************************************************/
#include <iostream>

using namespace std;

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
};

/***************************************************************************/
// Programa principal 
/***************************************************************************/
int main()
{
    // Lectura de un entero
    Lector lector_temp("Temperatura: ");

    int temp = lector_temp.LeeEntero();

    cout << "Temperatura leida = " << temp << endl << endl;

    // Lectura de enteros acotados superior e inferiormente
    Lector lector_hora;

    lector_hora.SetTitulo("Introduzca hora: ");
    int h = lector_hora.LeeEnteroEnRango (0, 23);

    lector_hora.SetTitulo("Introduzca minuto: ");
    int m = lector_hora.LeeEnteroEnRango (0, 59);

    lector_hora.SetTitulo("Introduzca segundo: ");
    int s = lector_hora.LeeEnteroEnRango (0, 59);

    cout << "Hora: " << h << ":" << m << ":" << s << endl << endl;

    // Lectura de un entero acotado inferiormente
    Lector lector_ingreso("Cantidad a ingresar: ");
    int ingreso = lector_ingreso.LeeEnteroMayorOIgual (0);

    cout << "Valor del ingreso = " << ingreso << endl;

    return 0;
}

/***************************************************************************/
/***************************************************************************/