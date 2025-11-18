/***************************************************************************
// FUNDAMENTOS DE PROGRAMACION
//
// MARIO MARTINEZ CALLEJON
//
// SESION 10
/*
    Programa que utiliza una clase para representar y operar con
    progresiones geométricas.

    La clase ProgresionGeometrica encapsula los datos esenciales de una
    progresión (primer término y razón) y ofrece métodos para calcular:
    - El término k-ésimo.
    - La suma de los n primeros términos.
    - El producto de los n primeros términos.
    - La suma de la serie infinita (si converge).

    Entradas:
        - Primer término de la progresión.
        - Razón de la progresión.
        - Posición 'k' para calcular un término.
        - Número de términos 'n' para sumar y multiplicar.

    Salidas:
        - Los resultados de las operaciones solicitadas.
*/
//**************************************************************************/

#include <iostream>
#include <cmath>   // Para la función pow()
#include <limits>  // Para std::numeric_limits

using namespace std;

/***************************************************************************/
// Definición de la clase ProgresionGeometrica
/***************************************************************************/
class ProgresionGeometrica {
private:
    double primer_termino; // a1
    double razon;          // r

public:
    /***********************************************************************/
    // Asigna el primer término de la progresión.
    // Parámetros:
    //   a1: El valor del primer término.
    /***********************************************************************/
    void SetTermino(double a1) {
        primer_termino = a1;
    }

    /***********************************************************************/
    // Asigna la razón de la progresión.
    // Parámetros:
    //   r: El valor de la razón.
    /***********************************************************************/
    void SetRazon(double r) {
        razon = r;
    }

    /***********************************************************************/
    // Devuelve la razón de la progresión.
    // Devuelve:
    //   El valor de la razón.
    /***********************************************************************/
    double GetRazon() const {
        return razon;
    }

    /***********************************************************************/
    // Devuelve el término k-ésimo de la progresión.
    // PRE: k >= 1
    // Parámetros:
    //   k: La posición del término a calcular.
    // Devuelve:
    //   El valor del término en la posición k.
    /***********************************************************************/
    double Termino(int k) const {
        // Fórmula: a_k = a_1 * r^(k-1)
        return primer_termino * pow(razon, k - 1);
    }

    /***********************************************************************/
    // Devuelve la suma de los n primeros términos.
    // PRE: n >= 1
    // Parámetros:
    //   n: El número de términos a sumar.
    // Devuelve:
    //   La suma de los primeros n términos.
    /***********************************************************************/
    double SumaHasta(int n) const {
        double suma;
        // Si la razón es 1, la suma es n * a_1
        if (razon == 1.0) {
            suma = n * primer_termino;
        } else {
            // Fórmula: S_n = a_1 * (1 - r^n) / (1 - r)
            suma = primer_termino * (1 - pow(razon, n)) / (1 - razon);
        }
        return suma;
    }

    /***********************************************************************/
    // Devuelve el producto de los n primeros términos.
    // PRE: n >= 1
    // Parámetros:
    //   n: El número de términos a multiplicar.
    // Devuelve:
    //   El producto de los primeros n términos.
    /***********************************************************************/
    double MultiplicaHasta(int n) {
        // Fórmula: P_n = (a_1^n) * r^((n-1)*n/2)
        double exponente_razon = (double)(n - 1) * n / 2.0;

        return pow(primer_termino, n) * pow(razon, exponente_razon);
    }

    /***********************************************************************/
    // Devuelve la suma de la progresión hasta el infinito.
    // Devuelve:
    //   La suma de la serie si converge (|r| < 1), o infinito si diverge.
    /***********************************************************************/
    double SumaHastaInfinito() const {
        return primer_termino / (1 - razon);
    }
};

/***************************************************************************/
// Programa Principal
/***************************************************************************/
int main() {
    // Pedir datos al usuario
    double a1, r;
    cout << "--- CALCULADORA DE PROGRESIONES GEOMETRICAS ---" << endl;
    cout << "Introduce el primer termino (a1): ";
    cin >> a1;
    cout << "Introduce la razon (r): ";
    cin >> r;

    // Crear el objeto de la progresión
    ProgresionGeometrica pg;
    pg.SetTermino(a1);
    pg.SetRazon(r);


    cout << "\n-------------------------------------------------" << endl;

    // Calcular el término k-ésimo
    int k;
    do {
        cout << "Introduce la posicion (k) del termino a calcular: ";
        cin >> k;
        if (k < 1) {
            cout << "ERROR: La posicion debe ser un entero positivo." << endl;
        }
    } while (k < 1);
    cout << "El termino en la posicion " << k << " es: " << pg.Termino(k) 
         << endl;

    cout << "\n-------------------------------------------------" << endl;

    // Calcular suma y producto hasta n
    int n;
    do {
        cout << "Introduce el numero de terminos (n) a sumar/multiplicar: ";
        cin >> n;
        if (n < 1) {
            cout << "ERROR: El numero de terminos debe ser un entero positivo." 
                 << endl;
        }
    } while (n < 1);
    cout << "La suma de los primeros " << n << " terminos es: " 
         << pg.SumaHasta(n) << endl;
    cout << "El producto de los primeros " << n << " terminos es: " 
         << pg.MultiplicaHasta(n) << endl;

    cout << "\n-------------------------------------------------" << endl;

    // Calcular la suma infinita
    // Comprobar si la serie converge antes de calcular la suma

    if (fabs(pg.GetRazon()) < 1.0) {
        double suma_infinita = pg.SumaHastaInfinito();
        cout << "La suma de la serie infinita es: " << suma_infinita << endl;
    } else {
        cout << "La serie no converge (la razon |r| no es menor que 1)." 
             << endl;
    }

    cout << "\n--- Fin del programa ---" << endl;

    return 0;
}

/***************************************************************************/
/***************************************************************************/