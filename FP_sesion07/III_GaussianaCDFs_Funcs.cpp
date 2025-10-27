/***************************************************************************
// FUNDAMENTOS DE PROGRAMACION
//
// MARIO MARTINEZ CALLEJON
//
// SESION 07
/*
    Programa que calcula el valor de la funci�n gaussiana (PDF) y su
    funci�n de distribuci�n acumulada (CDF) para un valor x, dados una
    media y una desviaci�n t�pica.

    El programa utiliza tres funciones separadas:
    1. Gaussiana: Calcula la funci�n de densidad de probabilidad (PDF).
    2. CDF_Gaussiana: Aproxima la CDF mediante una suma de Riemann.
    3. CDF_Gaussiana_Aprox: Aproxima la CDF usando la f�rmula de
       Abramowitz y Stegun, que es m�s eficiente.

    Entradas:
        - media: La media de la distribuci�n.
        - desviacion_tipica: La desviaci�n t�pica.
        - x: El punto en el que se eval�an las funciones.

    Salidas:
        - El valor de la PDF g(x).
        - El valor de la CDF aproximado por suma de Riemann.
        - El valor de la CDF aproximado por la f�rmula de Abramowitz y Stegun.
*/
//**************************************************************************/

#include <iostream>
#include <cmath>

using namespace std;

const double PI = 3.141592653589793;

/***************************************************************************/
/***************************************************************************/

double Gaussiana(double x, double media, double desviacion)
{
    
    // Pre-c�lculo de los componentes de la f�rmula
    double coeficiente = 1.0 / (desviacion * sqrt(2.0 * PI));
    double exponente = -0.5 * pow((x - media) / desviacion, 2.0);

    return (coeficiente * exp(exponente));
}

/***************************************************************************/
/***************************************************************************/

double CDF_Gaussiana(double x_final, double media, double desviacion)
{
    const double SALTO = 0.00001; // Precisi�n de la integraci�n

    // El valor inicial para la suma
    double x_inicial = media - 3 * desviacion;

    // Variable para acumular la suma de las �reas
    double cdf_aproximada = 0.0;

    // Suma desde el punto inicial hasta x_final
    for (double x_iter = x_inicial; x_iter <= x_final; x_iter += SALTO) {
        // Reutilizar la funci�n Gaussiana para obtener la altura
        double altura = Gaussiana(x_iter, media, desviacion);
        // Sumar el �rea del rect�ngulo al acumulador
        cdf_aproximada += altura * SALTO;
    }

    return cdf_aproximada;
}

/***************************************************************************/
/***************************************************************************/

double CDF_Gaussiana_Aprox(double x, double media, double desviacion)
{
    // Constantes de la f�rmula de aproximaci�n
    const double b0 = 0.2316419;
    const double b1 = 0.319381530;
    const double b2 = -0.356563782;
    const double b3 = 1.781477937;
    const double b4 = -1.821255978;
    const double b5 = 1.330274429;

    // La f�rmula funciona para la distribuci�n normal est�ndar(media=0, desv=1)
    // Primero estandarizamos el valor de x a su puntuaci�n z.
    double z = (x - media) / desviacion;
    double t = 1.0 / (1.0 + b0 * fabs(z));

    // Usar funci�n Gaussiana con media 0 y desviaci�n 1.
    double gaussiana_z = Gaussiana(fabs(z), 0.0, 1.0);

    // Polinomio de la f�rmula
    double polinomio = b1 * t + b2 * pow(t, 2) + b3 * pow(t, 3) +
                       b4 * pow(t, 4) + b5 * pow(t, 5);

    double w = 1.0 - gaussiana_z * polinomio;

    // Ajustar el resultado final seg�n el signo de z
    if (z >= 0) {
        return w;
    } else {
        return 1.0 - w;
    }
}

/***************************************************************************/
/***************************************************************************/

int main() {
    // Declaracion de variables
    double media, desviacion, x;

    // Pedir datos al usuario
    cout << "Introduce la media: ";
    cin >> media;
    cout << "Introduce la desviacion tipica: ";
    cin >> desviacion;
    cout << "Introduce el valor de x: ";
    cin >> x;

    // Calcular y mostrar el valor de la funci�n Gaussiana (PDF)
    double resultado_pdf = Gaussiana(x, media, desviacion);
    cout << "El valor de la funcion gaussiana (PDF) g(" << x << ") es: " << 
         resultado_pdf << endl;

    // Calcular y mostrar el valor de la CDF con ambos m�todos
    double resultado_cdf_riemann = CDF_Gaussiana(x, media, desviacion);
    cout << "El valor de la CDF (Suma de Riemann) en (" << x << ") es: " << 
         resultado_cdf_riemann << endl;

    double resultado_cdf_aprox = CDF_Gaussiana_Aprox(x, media, desviacion);
    cout << "El valor de la CDF (Aproximacion) en (" << x << ") es:   " << 
         resultado_cdf_aprox << endl;

    return 0;
}

//**************************************************************************/
//**************************************************************************/