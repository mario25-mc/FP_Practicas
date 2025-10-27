/***************************************************************************
// FUNDAMENTOS DE PROGRAMACION
//
// MARIO MARTINEZ CALLEJON
//
// SESION 07
/*
    Programa que presenta un menú para que el usuario pueda elegir entre
    calcular un factorial, una potencia o salir del programa.

    El programa se ejecuta en un bucle, mostrando el menú repetidamente
    después de cada operación, hasta que el usuario decide salir.

    Opciones del menú:
    a) Calcular factorial: Pide un entero no negativo n y calcula n!.
    b) Calcular potencia: Pide una base real x y un exponente entero n,
       y calcula x^n.
    c) Salir: Termina la ejecución del programa.

    Entradas:
        - opcion: La elección del usuario en el menú (1, 2, o 3).
        - n (factorial): Un entero no negativo.
        - x (potencia): Un número real que será la base.
        - n (potencia): Un entero que será el exponente.

    Salidas:
        - El resultado del factorial o la potencia, mostrado en pantalla.
*/
//**************************************************************************/
/***************************************************************************/

#include <iostream>
#include <iomanip>
#include <cctype> // Necesario para tolower

using namespace std;

/***************************************************************************/
/***************************************************************************/

// Calcula el factorial de un número entero no negativo n.
long double Factorial(int n) 
{
    long double resultado = 1.0;
    for (int i = 2; i <= n; i++) {
        resultado *= i;
    }
    return resultado;
}

/***************************************************************************/
/***************************************************************************/

// Calcula la potencia de una base elevada a un exponente.
double Potencia(double base, int exponente) 
{
    double resultado = 1.0;
    if (exponente > 0) {
        for (int i = 0; i < exponente; i++) {
            resultado *= base;
        }
    } else if (exponente < 0) {
        for (int i = 0; i < -exponente; i++) {
            resultado *= base;
        }
        resultado = 1.0 / resultado;
    }
    // Si exponente es 0, el resultado es 1.
    return resultado;
}

/***************************************************************************/
/***************************************************************************/

// Muestra el menú principal de opciones.
void MostrarMenu() 
{
    cout << "\n--- MENU PRINCIPAL ---" << endl;
    cout << "1. Calcular factorial" << endl;
    cout << "2. Calcular potencia" << endl;
    cout << "3. Salir" << endl;
    cout << "----------------------" << endl;
}

/***************************************************************************/
/***************************************************************************/

// Pide los datos para el factorial, lo calcula y muestra el resultado.
void ProcesarFactorial() 
{
    int n;
    cout << "Introduce un numero entero no negativo para calcular el "
            "factorial: ";
    cin >> n;

    // Validar si la entrada fue un número y si es no negativo
    if (n < 0) {
        cout << "Error: El factorial solo esta definido para numeros no "
                "negativos." << endl;
    } else {
        cout << n << "! = " << Factorial(n) << endl;
    }
}

/***************************************************************************/
/***************************************************************************/

// Pide los datos para la potencia, la calcula y muestra el resultado.
void ProcesarPotencia() 
{
    double base;
    int exponente;
    cout << "Introduce la base (numero real): ";
    cin >> base;
    cout << "Introduce el exponente (numero entero): ";
    cin >> exponente;

    cout << base << " elevado a " << exponente << " = " << 
            Potencia(base, exponente) << endl;
}

/***************************************************************************/
/***************************************************************************/

// Lee una opción del usuario, asegurándose de que sea una de las dos
// alternativas válidas 
char LeeOpcion2Alternativas(string mensaje, char op1, char op2) 
{
    char opcion_leida;
    op1 = tolower(op1);
    op2 = tolower(op2);

    do {
        cout << mensaje << " (" << op1 << "/" << op2 << "): ";
        cin >> opcion_leida;
        opcion_leida = tolower(opcion_leida);

        if (opcion_leida != op1 && opcion_leida != op2) {
            cout << "Opcion no valida. Intentalo de nuevo." << endl;
        }

    } while (opcion_leida != op1 && opcion_leida != op2);

    return opcion_leida;
}

/***************************************************************************/
/***************************************************************************/

int main() 
{
    cout.setf(ios::fixed);

    int opcion;
    bool salir = false;

    do {
        MostrarMenu();
        cout << setprecision(5);
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                ProcesarFactorial();
                break;
            case 2:
                ProcesarPotencia();
                break;
            case 3:
                if (LeeOpcion2Alternativas("Estas seguro de que quieres salir?",
                    's', 'n') == 's') {
                    cout << "Programa finalizado" << endl;
                    salir = true;
                }
                break;
            default:
                cout << "Opcion no valida. Por favor, intentalo de nuevo." 
                << endl;
        }
    } while (!salir);

    return 0;
}

/***************************************************************************/
/***************************************************************************/