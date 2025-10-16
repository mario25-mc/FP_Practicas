/***************************************************************************/
// FUNDAMENTOS DE PROGRAMACION
//
// MARIO MARTINEZ CALLEJON
//
// SESION 04
/*
    Programa que evalúa y muestra el resultado de varias expresiones lógicas:
    - Si una letra es mayúscula
    - Si una edad está en el rango [18, 67)
    - Si un año es bisiesto
    - Si una distancia es menor que un límite
    - Comparación entre dos enteros
   
    NOTA: Se supone que los datos introducidos son correctos
   
    Entradas: letra, edad, año, distancia, dos enteros.
    Salidas:  resultados de las expresiones lógicas evaluadas.
*/
/***************************************************************************/

#include <iostream>
using namespace std;

/***************************************************************************/
/***************************************************************************/

int main() {
    //Comprobar si una letra es mayúscula
    char letra;
    cout << "Introduzca una letra: ";
    cin >> letra;
    bool es_mayuscula = (letra >= 'A' && letra <= 'Z'); //Expresion logica
    cout << "¿Es mayuscula?: " << es_mayuscula << endl;

    //Comprobar si edad está en [18, 67)
    const int EDAD_MIN = 18;
    const int EDAD_MAX = 67;
    int edad;
    cout << endl << "Introduzca la edad: ";
    cin >> edad;
    bool edad_valida = (edad >= EDAD_MIN && edad < EDAD_MAX); //Expresion logica
    cout << "¿Edad en rango [18,67)?: " << edad_valida << endl;

    //Comprobar si un año es bisiesto
    int anio;
    cout << endl << "Introduce un año: ";
    cin >> anio;
    bool es_bisiesto = ((anio % 4 == 0 && anio % 100 != 0) || 
                       (anio % 400 == 0));  //Expresion logica
    cout << "¿Es bisiesto?: " << es_bisiesto << endl;

    //Comprobar si distancia es menor que LIMITE
    const double LIMITE = 100.0;  
    double distancia;
    cout << endl << "Introduce la distancia: ";
    cin >> distancia;
    bool menor_que_limite = (distancia < LIMITE);   //Expresion logica
    cout << "¿Distancia menor que LIMITE?: " << menor_que_limite << endl;

    //Comparar dos enteros
    int a, b;
    cout << endl << "Introduce el primer entero (a): ";
    cin >> a;
    cout << endl << "Introduce el segundo entero (b): ";
    cin >> b;

    //Expresiones logicas
    bool menor = (a < b);   
    bool igual = (a == b);
    bool mayor = (a > b);

    cout << "a < b: " << menor << endl;
    cout << "a == b: " << igual << endl;
    cout << "a > b: " << mayor << endl;

    return 0;
}

/***************************************************************************/
/***************************************************************************/
