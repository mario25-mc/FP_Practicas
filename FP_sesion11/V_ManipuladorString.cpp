/***************************************************************************
// FUNDAMENTOS DE PROGRAMACION
//
// MARIO MARTINEZ CALLEJON
//
// SESION 11
/*
    Este programa define la clase ManipuladorString, diseñada para extender
    la funcionalidad de la clase string estándar de C++. Proporciona métodos
    para realizar operaciones comunes de limpieza y transformación de cadenas,
    como eliminar espacios en blanco al principio y/o al final, y convertir
    toda la cadena a mayúsculas o minúsculas.

    La clase encapsula una cadena de caracteres y permite modificarla a través
    de sus métodos. El resultado de la manipulación se puede obtener
    posteriormente para ser utilizado en otras partes del programa.

    El programa principal (main) demuestra el uso de la clase con varios
    ejemplos prácticos, mostrando cómo instanciar la clase, manipular una
    cadena y recuperar el resultado.
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

    /***********************************************************************/
    // Convierte todos los caracteres de la cadena a mayúsculas.
    void ConvierteAMayusculas() {
        for (int i = 0; i < cadena.length(); i++) {
            cadena.at(i) = toupper(cadena.at(i));
        }
    }

    /***********************************************************************/
    // Convierte todos los caracteres de la cadena a minúsculas.
    void ConvierteAMinusculas() {
        for (int i = 0; i < cadena.length(); i++) {
            cadena.at(i) = tolower(cadena.at(i));
        }
    }
};

/***************************************************************************/
// Programa principal para probar la clase ManipuladorString
/***************************************************************************/
int main() {
    // Ejemplo 1: Eliminar espacios iniciales y finales
    cout << "--- Ejemplo 1: Eliminar espacios ---" << endl;
    string nombre = "   Frase de prueba   ";
    cout << "Original: \"" << nombre << "\"" << endl;

    // Usar el constructor con argumento
    ManipuladorString m1(nombre);
    m1.EliminaPrimerosYUltimosSeparadores();
    string nombre_limpio = m1.GetCadena();

    cout << "Limpio  : \"" << nombre_limpio << "\"" << endl << endl;

    // Ejemplo 2: Convertir a mayúsculas
    cout << "--- Ejemplo 2: Convertir a mayusculas ---" << endl;
    string frase = "Esta es una frase de prueba.";
    cout << "Original : " << frase << endl;

    // Usar el constructor por defecto y SetCadena
    ManipuladorString m2;
    m2.SetCadena(frase);
    m2.ConvierteAMayusculas();
    string frase_mayus = m2.GetCadena();

    cout << "Mayuscula: " << frase_mayus << endl << endl;

    // Ejemplo 3: Convertir a minúsculas
    cout << "--- Ejemplo 3: Convertir a minusculas ---" << endl;
    string texto_mezclado = "TeXtO CoN MaYuS Y mInUs";
    cout << "Original : " << texto_mezclado << endl;

    ManipuladorString m3(texto_mezclado);
    m3.ConvierteAMinusculas();
    string texto_minus = m3.GetCadena();

    cout << "Minuscula: " << texto_minus << endl << endl;

    // Ejemplo 4: Eliminar solo separadores iniciales
    cout << "--- Ejemplo 4: Eliminar solo separadores iniciales ---" << endl;
    string con_espacios_delante = "\t\n   Empieza con separadores";
    cout << "Original: \"" << con_espacios_delante << "\"" << endl;

    ManipuladorString m4(con_espacios_delante);
    m4.EliminaPrimerosSeparadores();
    string sin_espacios_delante = m4.GetCadena();

    cout << "Limpio  : \"" << sin_espacios_delante << "\"" << endl << endl;

    // Ejemplo 5: Eliminar solo separadores finales
    cout << "--- Ejemplo 5: Eliminar solo separadores finales ---" << endl;
    string con_espacios_detras = "Termina con separadores   \t\n";
    cout << "Original: \"" << con_espacios_detras << "\"" << endl;

    ManipuladorString m5(con_espacios_detras);
    m5.EliminaUltimosSeparadores();
    string sin_espacios_detras = m5.GetCadena();

    cout << "Limpio  : \"" << sin_espacios_detras << "\"" << endl << endl;

    return 0;
}

/***************************************************************************/
/***************************************************************************/