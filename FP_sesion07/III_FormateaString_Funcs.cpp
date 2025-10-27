/***************************************************************************
// FUNDAMENTOS DE PROGRAMACION
//
// MARIO MARTINEZ CALLEJON
//
// SESION 07
/*
    Programa que formatea una cadena de texto (string) aplicando un relleno
    específico y un tipo de ajuste (izquierda, centro, derecha) a un número
    determinado de casillas.

    El programa permite al usuario introducir la cadena, el número de casillas
    deseado, el carácter de relleno y el tipo de ajuste.

    Entradas:
        - cad: La cadena de texto original (string).
        - num_casillas: El ancho total deseado para la cadena formateada (int).
        - ajuste: El tipo de alineación (izquierda, centro, derecha) 
                  (TipoAjuste enum).
        - relleno: El carácter a usar para rellenar los espacios (char).

    Salidas:
        - La cadena formateada con el relleno y ajuste aplicados (string).
          Impresa por pantalla en la función main.

    NOTA: Si la cadena original es más larga que 'num_casillas', se devuelve
    la cadena original sin modificar.
*/
//**************************************************************************/

#include <iostream>
#include <string>

using namespace std;

enum class TipoAjuste {izquierda, centro, derecha}; //Declarar el tipo enum

//**************************************************************************/
//**************************************************************************/

string FormateaString (string cad, int num_casillas, 
                       TipoAjuste ajuste, char relleno)
{   
    string cad_final;

    // Si la cadena ya es igual o más larga que el espacio, devolverla tal cual.
    if (num_casillas <= cad.length()) {
        cad_final = cad;;
    } else {

        int longitud_relleno = num_casillas - cad.length();

        // Crear una cadena distinta segun el tipo de ajuste
        switch (ajuste){
            case TipoAjuste::izquierda: {

                string cad_relleno;     //Cadena para el relleno
                cad_relleno.assign(longitud_relleno, relleno);

                cad_final = cad + cad_relleno;
                break;
            }
            case TipoAjuste::derecha: {

                string cad_relleno; //Cadena para el relleno
                cad_relleno.assign(longitud_relleno, relleno);

                cad_final = cad_relleno + cad;
                break;
            }
            case TipoAjuste::centro: {
                int relleno_izq = longitud_relleno / 2;
                int relleno_der = longitud_relleno - relleno_izq; //long impar

                string cad_relleno_izq;     //Cadena para la izquierda
                cad_relleno_izq.assign(relleno_izq, relleno);

                string cad_relleno_der;     //Cadena para la derecha
                cad_relleno_der.assign(relleno_der, relleno);
                
                cad_final = cad_relleno_izq + cad + cad_relleno_der;
                break;
            }
        }
    }

    return cad_final;
}

//**************************************************************************/
//**************************************************************************/

int main() {
    string texto;
    int casillas;
    int opcion_ajuste;
    char caracter_relleno;
    
    cout << "\n--- FORMATEADOR DE CADENAS ---" << endl;
    cout << "Introduce la cadena de texto: ";
    getline(cin, texto);

    cout << "Introduce el numero total de casillas: ";
    cin >> casillas;

    cout << "Introduce el caracter de relleno: ";
    cin >> caracter_relleno;

    cout << "Selecciona el tipo de ajuste (1: Izquierda, 2: Centro, "
            "3: Derecha): ";
    cin >> opcion_ajuste;

    TipoAjuste ajuste = TipoAjuste::izquierda; // Valor por defecto
    if (opcion_ajuste == 2) ajuste = TipoAjuste::centro;
    if (opcion_ajuste == 3) ajuste = TipoAjuste::derecha;

    string resultado = FormateaString(texto, casillas, ajuste, 
                                     caracter_relleno);

    cout << "\nResultado: " << resultado << endl;

    return 0;
}

//**************************************************************************/
//**************************************************************************/