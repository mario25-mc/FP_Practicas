/***************************************************************************
// FUNDAMENTOS DE PROGRAMACION
//
// MARIO MARTINEZ CALLEJON
//
// SESION 11
/*
    Este programa define y demuestra el uso de dos clases: ManipuladorString
    y Lector.

    Clases utilizadas:
    - ManipuladorString: Proporciona métodos para la limpieza y manipulación
      de cadenas, como eliminar espacios en blanco al principio y al final.
    - Lector: Facilita la lectura y validación robusta de datos de entrada
      del usuario (números enteros y reales), manejando errores y rangos.
      Internamente, utiliza ManipuladorString para permitir entradas más
      flexibles (p.ej. con espacios extra).

    El programa principal (main) contiene varios ejemplos que ilustran cómo
    utilizar la clase Lector para leer diferentes tipos de datos enteros
    de forma segura, como una temperatura, una hora (con rangos) y una
    cantidad a ingresar (con un valor mínimo).
*/
//**************************************************************************/
#include <iostream>
#include <string>
#include <cctype> // Para toupper, tolower

using namespace std;

/***************************************************************************/
// Definición de la clase ManipuladorString
/***************************************************************************/
class ManipuladorString {
private:
    string cadena;

    /***********************************************************************/
    // Comprueba si un carácter es un separador (espacio, tabulador, etc.).
    // Parámetros: c, el carácter a comprobar.
    // Devuelve: true si es un separador, false en caso contrario.
    bool EsSeparador(char c) {
        bool es_separador = (c == ' ' || c == '\t' || c == '\n' || 
                             c == '\r' || c == '\f' || c == '\v');
        return es_separador;
    }

public:
    /***********************************************************************/
    // Constructor por defecto. Inicializa la cadena vacía.
    ManipuladorString() 
        : cadena("") 
    {}

    /***********************************************************************/
    // Constructor con parámetros. Inicializa la cadena con un valor dado.
    // Parámetros: la_cadena, el valor inicial para la cadena interna.
    ManipuladorString(string la_cadena) : cadena(la_cadena) {}

    /***********************************************************************/
    // Establece un nuevo valor para la cadena interna.
    // Parámetros: la_cadena, el nuevo valor.
    void SetCadena(string la_cadena) {
        cadena = la_cadena;
    }

    /***********************************************************************/
    // Devuelve el valor actual de la cadena interna.
    // Devuelve: una copia de la cadena manipulada.
    string GetCadena() {
        return cadena;
    }

    /***********************************************************************/
    // Elimina todos los caracteres separadores (espacios, tabuladores, etc.)
    // del principio de la cadena.
    void EliminaPrimerosSeparadores() {
        int pos = 0;
        while (pos < cadena.length() && EsSeparador(cadena.at(pos))) {
            pos++;
        }
        // Tomar la cadena a partir del índice pos
        cadena = cadena.substr(pos);
    }

    /***********************************************************************/
    // Elimina todos los caracteres separadores (espacios, tabuladores, etc.)
    // del final de la cadena.
    void EliminaUltimosSeparadores() {
        int ultimo_no_separador_pos = -1;

        // Bucle hacia adelante para encontrar el último carácter no separador
        for (int i = 0; i < cadena.length(); i++) {
            if (!EsSeparador(cadena.at(i))) {
                ultimo_no_separador_pos = i;
            }
        }

        // Si no se encontró ningún no-separador 
        if (ultimo_no_separador_pos == -1) {
            cadena = "";
        } else {
            // Recortar la cadena hasta el último no-separador encontrado
            cadena = cadena.substr(0, ultimo_no_separador_pos + 1);
        }
    }

    /***********************************************************************/
    // Elimina los caracteres separadores tanto del principio como del final
    // de la cadena, llamando a los métodos correspondientes.
    void EliminaPrimerosYUltimosSeparadores() {
        EliminaPrimerosSeparadores();
        EliminaUltimosSeparadores();
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
    bool EsEntero(string &entrada) {
        bool es_entero = true;

        LimpiarEspacios(entrada);

        if (entrada.empty()) 
        {
            es_entero = false; // Una cadena vacía no es un entero.
        }

        int inicio = 0;
        // Si hay un signo, la validación empieza desde el siguiente carácter.
        if (!entrada.empty() && (entrada.at(0) == '+' || entrada.at(0) == '-')) 
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
    bool EsReal(string &entrada) {   
        bool es_real = true;

        LimpiarEspacios(entrada);

        if (entrada.empty()) {
            es_real = false;
        }

        int inicio = 0;
        if (!entrada.empty() && (entrada.at(0) == '+' || entrada.at(0) == '-')) {
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

    /***********************************************************************/
    // Limpia los espacios en blanco al principio y al final de una cadena.
    // Modifica la cadena de entrada por referencia.
    /***********************************************************************/
    void LimpiarEspacios(string &cadena) {
        // Usamos un objeto ManipuladorString para limpiar la cadena
        ManipuladorString limpiador(cadena);
        limpiador.EliminaPrimerosYUltimosSeparadores();
        cadena = limpiador.GetCadena();
    }

public:
    /***********************************************************************/
    // Constructor sin argumentos
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
        getline(cin, entrada);

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
            getline(cin, entrada);
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
        getline(cin, entrada);
        
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
            getline(cin, entrada);

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
        getline(cin, entrada);
        
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
            getline(cin, entrada);

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
        getline(cin, entrada);

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
            getline(cin, entrada);
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

        // Lectura
        getline(cin, entrada);
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
            getline(cin, entrada);

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

        // Lectura
        getline(cin, entrada);
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

            getline(cin, entrada);

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
// Programa principal para resolver el Ejercicio 24
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