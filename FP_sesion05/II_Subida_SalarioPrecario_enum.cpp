/***************************************************************************/
// FUNDAMENTOS DE PROGRAMACION
//
// MARIO MARTINEZ CALLEJON
//
// SESION 05
/*
	Programa que lee la edad y el salario de una persona y aplica subidas al 
    salario según condiciones: 4% si la edad es mayor de 65 o menor de 35 años. 
    Si además el salario es inferior a 300 euros, se suma un 3% extra; si está 
    entre 300 y 900 euros (sin incluir 900), se suma un 1.5% extra. Se indica 
    por pantalla qué subidas se han aplicado.
   
	NOTA: Se supone que los datos introducidos son correctos.
   
	Entradas: edad (entero), salario (real).
	Salidas:  salario final (real), subidas aplicadas (texto).
*/
/***************************************************************************/

#include <iostream>
#include <iomanip>

using namespace std;

/***************************************************************************/
/***************************************************************************/

int main() {
    // Constantes
    const int EDAD_MAYOR = 65;
    const int EDAD_MENOR = 35;

    const double SUBIDA_PRINCIPAL = 4;

    const double LIMITE_SALARIO_MUY_BAJO = 300.0;
    const double SUBIDA_EXTRA_BAJA = 3;

    const double LIMITE_SALARIO_BAJO = 900.0;
    const double SUBIDA_EXTRA_MEDIA = 1.5;

    //Declaracion de valores para los tipos enumerados
    enum class Edad {
        joven,
        adulto,
        senior
    };

    enum class Salario {
        muy_bajo,
        bajo,
        normal
    };

    // Enum to report which subida was applied
    enum class Subida {
        ninguna,
        subida_edad,
        subida_maxima,
        subida_media
    };

    //Bool de comprobacion de entrada
    bool edad_ok = false;
    bool salario_ok = false;
    bool entrada_ok = false;

    // Entrada
    int edad;
    double salario;

    cout << endl;
    cout << "Introduzca la edad: ";
    cin >> edad;

    edad_ok = (edad >= 0);

    if (edad_ok) {
        cout << "Introduzca el salario: ";
        cin >> salario;

        salario_ok = (salario >= 0);
    }

    entrada_ok = (edad_ok && salario_ok);

    if (entrada_ok) {
        double salario_final = salario;
        Edad edad_usuario = Edad::adulto; // default
        Salario salario_usuario = Salario::normal; // default
        Subida subida_usuario = Subida::ninguna;

        // Determinar edad_usuario
        if (edad < EDAD_MENOR) {
            edad_usuario = Edad::joven;
        } else if (edad > EDAD_MAYOR) {
            edad_usuario = Edad::senior;
        } else {
            edad_usuario = Edad::adulto;
        }

        // Determinar salario_usuario 
        if (salario < LIMITE_SALARIO_MUY_BAJO) {
            salario_usuario = Salario::muy_bajo;
        } else if (salario < LIMITE_SALARIO_BAJO) {
            salario_usuario = Salario::bajo;
        } else {
            salario_usuario = Salario::normal;
        }

        //Aplicar subidas de salario
        if (edad_usuario == Edad::joven || edad_usuario == Edad::joven) {
            salario_final += salario * (SUBIDA_PRINCIPAL / 100);

            //Aplicar descuentos extras
            if (salario_usuario == Salario::muy_bajo) {
                salario_final += salario * (SUBIDA_EXTRA_BAJA / 100);
            } else if (salario_usuario == Salario::bajo) {
                salario_final += salario * (SUBIDA_EXTRA_MEDIA / 100);
            }
        }

        // Salida
        cout << fixed << setprecision(2);
        cout << endl;
        cout << "Salario final: " << salario_final << " euros." << endl;
        cout << endl;

        cout << fixed << setprecision(1);
        switch (edad_usuario) {
        case Edad::joven:
            cout << "Se ha aplicado una subida del " << SUBIDA_PRINCIPAL 
                << "% por ser menor de " << EDAD_MENOR << " años.";
            break;
        
        case Edad::senior:
            cout << "Se ha aplicado una subida del " << SUBIDA_PRINCIPAL 
                << "% por ser mayor de " << EDAD_MAYOR << " años.";
            break;

        default:
            cout << "No se aplica ninguna subida.";
            break;
        }

        cout << endl;

        if (edad_usuario == Edad::joven || edad_usuario == Edad::senior) {
            cout << endl;
            
            switch (salario_usuario) {
            case Salario::muy_bajo:
                cout << "Se ha aplicado una subida del " << SUBIDA_EXTRA_BAJA << 
                        "% por tener un salario menor que " << 
                        LIMITE_SALARIO_MUY_BAJO << " euros.";
                break;

            case Salario::bajo:
                cout << "Se ha aplicado una subida del " << SUBIDA_EXTRA_MEDIA << 
                        "% por tener un salario menor que " << LIMITE_SALARIO_BAJO
                    << " euros.";
                break;
            }
        }
        
    } else {
        cout << endl;
        if (!edad_ok) {
            cout << "La edad debe ser positiva" << endl;
        } else {
            cout << "El salario debe ser positivo" << endl;
        }
    }

    cout << endl;

    return 0;
}

/***************************************************************************/
/***************************************************************************/
