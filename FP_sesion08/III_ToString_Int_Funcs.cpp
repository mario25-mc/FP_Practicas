/***************************************************************************
// FUNDAMENTOS DE PROGRAMACION
//
// MARIO MARTINEZ CALLEJON
//
// SESION 08
/*
    Este programa define y prueba una función de utilidad llamada ToStringInt,
    diseñada para convertir un número entero en una cadena de caracteres
    (string) con un formato específico.

    La función principal (main) sirve como un banco de pruebas que demuestra
    el comportamiento de ToStringInt con diferentes valores, anchos de campo
    y caracteres de relleno, mostrando los resultados por consola.

    Entradas: Ninguna (los valores de prueba están definidos en el código).
    Salidas:  Muestra en la consola los resultados de las pruebas de la
              función ToStringInt.
*/
//**************************************************************************/

#include <iostream>
#include <string>

using namespace std;

/***************************************************************************/
/*
    Convierte un número entero a su representación textual en un string con
    un ancho y relleno específicos.

    Parámetros:
        entero:       El número entero a convertir.
        num_casillas: El ancho mínimo deseado para el string resultante.
        relleno:      El carácter usado para rellenar los espacios vacíos.

    Devuelve:
        Un string con el número formateado. Si la longitud del número es
        menor que num_casillas, se rellena por la izquierda. Si es mayor,
        se devuelve el número completo sin truncar.
*/
/***************************************************************************/
string ToStringInt (int entero, int num_casillas, char relleno)
{
    // Convertir el entero a un string base.
    string cad_entero = to_string(entero);
    int longitud_entero = cad_entero.length();

    // Comprobar si se necesita relleno.
    if (num_casillas > longitud_entero) {
        // Calcular cuántos caracteres de relleno se necesitan.
        int longitud_relleno = num_casillas - longitud_entero;

        // Crear la cadena de relleno.
        string cad_relleno;
        cad_relleno.assign(longitud_relleno, relleno);

        // Devolver la cadena de relleno seguida del número.
        return cad_relleno + cad_entero;
    } else {
        // Si no se necesita relleno, devolver el número tal cual.
        return cad_entero;
    }
}

/***************************************************************************/
// Función main para probar ToStringInt.
/***************************************************************************/
int main() {
    cout << "--- Pruebas de la funcion ToStringInt ---" << endl;

    // Ejemplo 1: Relleno con espacios
    cout << "ToStringInt(15, 6, ' ')   -> " << ToStringInt(15, 6, ' ') 
         << endl;

    // Ejemplo 2: Relleno con '#'
    cout << "ToStringInt(15, 6, '#')   -> " << ToStringInt(15, 6, '#') 
         << endl;

    // Ejemplo 3: num_casillas menor que la longitud del número
    cout << "ToStringInt(155, 2, ' ')  -> " << ToStringInt(155, 2, '*') 
         << endl;

    // Ejemplo 4: Número negativo
    cout << "ToStringInt(-99, 8, '_')  -> " << ToStringInt(-99, 8, '_') 
         << endl;

    // Ejemplo 5: Número cero
    cout << "ToStringInt(0, 5, '0')    -> " << ToStringInt(0, 5, '0') 
         << endl;

    return 0;
}

/***************************************************************************/
/***************************************************************************/