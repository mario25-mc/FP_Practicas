/***************************************************************************/
// FUNDAMENTOS DE PROGRAMACION
//
// MARIO MARTINEZ CALLEJON
//
// SESION 04
/*
    Programa que analiza una cadena de 53 caracteres correspondiente a una 
    línea de índice y extrae sus componentes: sección, subsección, 
    subsubsección, título y página.
   
    NOTA: Se supone que los datos introducidos son correctos
   
    Entradas: una cadena de 53 caracteres.
    Salidas:  los componentes extraídos de la cadena.
*/
/***************************************************************************/

#include <iostream>
#include <string>

using namespace std;

/***************************************************************************/
/***************************************************************************/

int main() {
    //Entrada
    string cadena_entrada;

    cout << "Introduzca la cadena a procesar: ";
    getline(cin, cadena_entrada);
    cout << endl;

    // Calculos (dividir la cadena en subcadenas y almacenarlas)
    int seccion = stoi(cadena_entrada.substr(0,3));
    int subseccion = stoi(cadena_entrada.substr(3,3));
    int subsubseccion = stoi(cadena_entrada.substr(6,3));
    string titulo = cadena_entrada.substr(9, 40);
    int pagina = stoi(cadena_entrada.substr(49,4));

    // Salida
    cout << "Componentes: ";
    cout << "\tSeccion: " << seccion << endl;
    cout << "\tSubseccion: " << subseccion << endl;
    cout << "\tSubsubseccion: " << subsubseccion << endl;
    cout << "\tTitulo: " << titulo << endl;
    cout << "\tPagina: " << pagina << endl;

    return 0;
}

/***************************************************************************/
/***************************************************************************/