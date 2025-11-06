/***************************************************************************
// FUNDAMENTOS DE PROGRAMACION
//
// MARIO MARTINEZ CALLEJON
//
// SESION 08
/*
    Programa que calcula el valor de la funcin gaussiana (PDF) y su
    función de distribución acumulada (CDF) para un valor x, dados una
    media y una desviación típica. 

    El programa utiliza tres funciones separadas:
    1. Gaussiana: Calcula la función de densidad de probabilidad (PDF).
    2. CDF_Gaussiana: Aproxima la CDF mediante una suma de Riemann.
    3. CDF_Gaussiana_Aprox: Aproxima la CDF usando la fórmula de
       Abramowitz y Stegun, que es más eficiente.

    Entradas:
        - media: La media de la distribucion.
        - desviacion_tipica: La desviacin tpica.
        - x: El punto en el que se evalan las funciones.

    Salidas:
        - El valor de la PDF g(x).
        - El valor de la CDF aproximado por suma de Riemann.
        - El valor de la CDF aproximado por la frmula de Abramowitz y Stegun.

    NOTA: El programa utiliza un struct para almacenar los datos de la 
          distribución.
*/
//**************************************************************************/

#include <iostream>
#include <cmath>

using namespace std;

const double PI = 3.141592653589793;

//**************************************************************************/

struct Gaussiana {
    double media;
    double desviacion;
};

/***************************************************************************/
// Calcula la Función de Densidad de Probabilidad (PDF) de una Gaussiana.
// Parámetros: x, el punto donde se evalúa la función.
//             Gauss, struct con la media y desviación de la distribución.
// Devuelve: el valor de la PDF en el punto x.
// PRE: Gauss.desviacion > 0
/***************************************************************************/

double PDF_Gaussiana(double x, Gaussiana Gauss)
{
    
    // Pre-cálculo de los componentes de la fórmula
    double coeficiente = 1.0 / (Gauss.desviacion * sqrt(2.0 * PI));
    double exponente = -0.5 * pow((x - Gauss.media) / Gauss.desviacion, 2.0);

    return (coeficiente * exp(exponente));
}

/***************************************************************************/
// Aproxima la Función de Distribución Acumulada (CDF) mediante suma de Riemann.
// Parámetros: x_final, el punto hasta el que se calcula la CDF.
//             Gauss, struct con la media y desviación de la distribución.
// Devuelve: el valor aproximado de la CDF en x_final.
// PRE: Gauss.desviacion > 0
/***************************************************************************/

double CDF_Gaussiana(double x_final, Gaussiana Gauss)
{
    const double SALTO = 0.0001; // Precisión de la integracin

    // El valor inicial para la suma
    double x_inicial = Gauss.media - 3 * Gauss.desviacion;

    // Variable para acumular la suma de las áreas
    double cdf_aproximada = 0.0;

    // Suma desde el punto inicial hasta x_final
    for (double x_iter = x_inicial; x_iter <= x_final; x_iter += SALTO) {
        // Reutilizar la función Gaussiana para obtener la altura
        double altura = PDF_Gaussiana(x_iter, Gauss);
        // Sumar el rea del rectngulo al acumulador
        cdf_aproximada += altura * SALTO;
    }

    return cdf_aproximada;
}

/***************************************************************************/
// Aproxima la CDF usando la fórmula de Abramowitz y Stegun.
// Parámetros: x, el punto donde se evalúa la función.
//             Gauss, struct con la media y desviación de la distribución.
// Devuelve: el valor aproximado de la CDF en el punto x.
// PRE: Gauss.desviacion > 0
/***************************************************************************/

double CDF_Gaussiana_Aprox(double x, Gaussiana Gauss)
{
    // Constantes de la fórmula de aproximación
    const double b0 = 0.2316419;
    const double b1 = 0.319381530;
    const double b2 = -0.356563782;
    const double b3 = 1.781477937;
    const double b4 = -1.821255978;
    const double b5 = 1.330274429;

    // La fórmula funciona para la distribución normal estándar(media=0, desv=1)
    // Primero estandarizamos el valor de x a su puntuación z.
    double z = (x - Gauss.media) / Gauss.desviacion;
    double t = 1.0 / (1.0 + b0 * fabs(z));

    // Usar función Gaussiana con media 0 y desviación 1.
    Gaussiana gaussiana_estandar = {0.0, 1.0};
    double gaussiana_z = PDF_Gaussiana(fabs(z), gaussiana_estandar);

    // Polinomio de la fórmula
    double polinomio = b1 * t + b2 * pow(t, 2) + b3 * pow(t, 3) +
                       b4 * pow(t, 4) + b5 * pow(t, 5);

    double w = 1.0 - gaussiana_z * polinomio;

    // Ajustar el resultado final según el signo de z
    if (z >= 0) {
        return w;
    } else {
        return 1.0 - w;
    }
}

/***************************************************************************/
// Valida si una cadena de caracteres representa un número positivo.
// Parámetros: num, la cadena a validar.
// Devuelve: true si es un número positivo, false en caso contrario.
// PRE: ninguna.
/***************************************************************************/

bool EsNumeroPositivo(string num){
    int numero_pts = 0;
    bool num_ok = true;

    for(int i = 0; i < num.length() && num_ok; i++){
        char char_actual = num.at(i);
    
        if (char_actual == '+' || char_actual == '-') {
            if (i != 0) {
                num_ok = false; // El signo solo es válido al principio
            }
        }
        else if(char_actual == '.'){
            numero_pts++;
            if(numero_pts > 1) {
                num_ok = false;  //Solo un punto
            } 
        }
        else if(!isdigit(char_actual)){
            num_ok = false; //Tiene que ser un digito
        }
    }
    if (num_ok) {
        double valor_numerico = stod(num);  //Pasar a valor numerico
        if(valor_numerico <= 0) { // La desviación no puede ser 0 tampoco
            num_ok = false;  //Tiene que ser positiva
        }
    } 

    if (!num_ok) cout <<"Error: Introduzca un numero positivo." << endl << endl;

    return num_ok;
}

/***************************************************************************/
// Valida si una cadena de caracteres representa un número.
// Parámetros: num, la cadena a validar.
// Devuelve: true si es un número, false en caso contrario.
// PRE: ninguna.
/***************************************************************************/

bool EsNumero(string num){
    int numero_pts = 0;
    bool num_ok = true;

    for(int i = 0; i < num.length() && num_ok; i++){
        char char_actual = num.at(i);
    
        if (char_actual == '+' || char_actual == '-') {
            if (i != 0) {
                num_ok = false; // El signo solo es válido al principio
            }
        }
        else if(char_actual == '.'){
            numero_pts++;
            if(numero_pts > 1) {
                num_ok = false;  //Solo un punto
            } 
        }
        else if(!isdigit(char_actual)){
            num_ok = false; //Tiene que ser un digito
        }
    }

    if (!num_ok) cout << "Error: Introduzca un numero." << endl << endl;

    return num_ok;
}

/***************************************************************************/
// Lee y valida una opción de dos alternativas (caracteres).
// Parámetros: mensaje, el texto a mostrar al usuario.
//             op1, el carácter de la primera opción.
//             op2, el carácter de la segunda opción.
// Devuelve: el carácter de la opción elegida por el usuario.
// PRE: ninguna.
/***************************************************************************/

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

    return opcion_leida == op1;
}

/***************************************************************************/
// Función principal del programa.
/***************************************************************************/
int main()
{   
    bool sigue;
    do{
        // Variables
        string x_str;  
        string media_str;
        string desviacion_str;
        Gaussiana Gauss;

        // Pedir datos al usuario
        do{
            cout << "Introduce la media: ";
            cin >> media_str;
        } while (!EsNumero(media_str));

        do {
            cout << "Introduce la desviacion tipica: ";
            cin >> desviacion_str;
        } while (!EsNumeroPositivo(desviacion_str));

        do{ 
            cout << "Introduce el valor de x: ";
            cin >> x_str;
        } while (!EsNumero(x_str));

        cout << endl;
        
        // Pasar los datos introducidos a double y almacenarlos en las 
        // variables correspondientes
        Gauss.media = stod(media_str);
        Gauss.desviacion = stod(desviacion_str);
        double x = stod(x_str);

        // Calcular y mostrar el valor de la función Gaussiana (PDF)
        double resultado_pdf = PDF_Gaussiana(x, Gauss);
        cout << "El valor de la funcion gaussiana (PDF) g(" << x << ") es: " << 
            resultado_pdf << endl;

        // Calcular y mostrar el valor de la CDF con ambos métodos
        double resultado_cdf_riemann = CDF_Gaussiana(x, Gauss);
        cout << "El valor de la CDF (Suma de Riemann) en (" << x << ") es: " << 
            resultado_cdf_riemann << endl;

        double resultado_cdf_aprox = CDF_Gaussiana_Aprox(x, Gauss);
        cout << "El valor de la CDF (Aproximacion) en (" << x << ") es:   " << 
            resultado_cdf_aprox << endl << endl;
        
        sigue = LeeOpcion2Alternativas("Desea continuar?", 's', 'n');

    } while (sigue);

    cout << "Programa finalizado";
    
    return 0;
}

//**************************************************************************/
//**************************************************************************/