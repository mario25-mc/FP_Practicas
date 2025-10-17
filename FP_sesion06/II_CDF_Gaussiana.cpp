/***************************************************************************
// FUNDAMENTOS DE PROGRAMACION
//
// MARIO MARTINEZ CALLEJON
//
// SESION 06
/*
    Calculadora de la Funcion de Distribucion Acumulada (CDF) de una
    distribución Gaussiana (normal).

    Programa que aproxima la CDF integrando la función de densidad normal
    mediante una suma de Riemann (rectángulos) desde media - 3*desviacion
    hasta el valor x proporcionado por el usuario.

    Entradas:
        - media: media (mu) de la distribución normal (double)
        - desviacion: desviacion estandar (sigma) > 0 (double)
        - x: abscisa hasta la cual se calcula la CDF (double)

    Salidas:
        - Valor aproximado de la CDF en x (double), impreso por pantalla.

    NOTA: Se supone que las entradas son numéricas y la desviacion es
    un valor positivo (se comprueba antes de calcular).
*/
//**************************************************************************/

#include <iostream>
#include <cmath>   
#include <iomanip> // Para formatear la salida con fixed y setprecision

using namespace std;

//**************************************************************************/
//**************************************************************************/

int main() {
    cout.setf(ios::fixed);		// Notación de punto fijo para los reales
	cout.setf(ios::showpoint);	// Mostrar siempre decimales 

    //Constantes
    const double SALTO = 0.00001;
    const double PI = 3.1415927;
    //Variables de entrada 
    double media, desviacion, x_final;
    string media_str, desviacion_str, x_final_str;

    //Entrada
    cout << "Calculadora de la Funcion de Distribucion Acumulada (CDF)" << endl;
    cout << "---------------------------------------------------------" << endl;
    cout << "Gaussiana" << endl;
    cout << "Introduzca los siguientes parametros:" << endl;
    cout << endl;

    //Media
    bool media_ok;
    int numero_pts;
    do{  
        media_ok = true;
        numero_pts = 0;
        cout << "Introduzca el valor de la media: ";
        cin >> media_str;

        for(int i = 0; i < media_str.length() && media_ok; i++){
            char char_actual = media_str.at(i);
        
            if(char_actual == '.'){
                numero_pts++;
                if(numero_pts > 1) media_ok = false; //Solo un punto
            }
            else if(char_actual == '-' && i != 0){ 
                media_ok = false; //Signo '-' al inicio
            } 
            else if(!isdigit(char_actual) && char_actual != '-'){
                media_ok = false; //Tiene que ser un digito
            }
        }
        if(!media_ok){
            cout << "Error: La media debe ser un numero" << endl;
            cout << endl;
        }
    } while(!media_ok);
    media = stod(media_str); //Pasar la media a valor numérico

    //Desviacion
    bool desviacion_ok;
    do{  
        desviacion_ok = true;
        numero_pts = 0;
        cout << "Introduzca el valor de la desviacion tipica: ";
        cin >> desviacion_str;

        for(int i = 0; i < desviacion_str.length() && desviacion_ok; i++){
            char char_actual = desviacion_str.at(i);
        
            if(char_actual == '.'){
                numero_pts++;
                if(numero_pts > 1) desviacion_ok = false; //Solo un punto
            }
            else if(char_actual == '-' && i != 0){ 
                desviacion_ok = false; //Signo '-' al inicio
            } 
            else if(!isdigit(char_actual) && char_actual != '-'){
                desviacion_ok = false; //Tiene que ser un digito
            }
        }
        desviacion = stod(desviacion_str);  //Pasar a valor numerico
        if(desviacion < 0) {
            desviacion_ok = false;  //Tiene que ser positiva
        }
        if(!desviacion_ok){
            cout << "Error: La desviacion debe ser un numero positivo" << endl;
            cout << endl;
        }
    } while(!desviacion_ok);
    

    //x_final
    bool x_final_ok;
    do{  
        x_final_ok = true;
        numero_pts = 0;
        cout << "Valor de la abscisa (x) para calcular CDF: ";
        cin >> x_final_str;

        for(int i = 0; i < x_final_str.length() && x_final_ok; i++){
            char char_actual = x_final_str.at(i);
        
            if(char_actual == '.'){
                numero_pts++;
                if(numero_pts > 1) x_final_ok = false; //Solo un punto
            }
            else if(char_actual == '-' && i != 0){ 
                x_final_ok = false; //Signo '-' al inicio
            } 
            else if(!isdigit(char_actual) && char_actual != '-'){
                x_final_ok = false; //Tiene que ser un digito
            }
        }
        if(!x_final_ok){
            cout << "Error: La abscisa debe ser un numero" << endl;
            cout << endl;
        }
    } while(!x_final_ok);
    x_final = stod(x_final_str); //Pasar la x_final a valor numérico
    

    //Cálculos

    //El valor inicial para la suma
    double x_inicial = media - 3 * desviacion;
    
    // Variable para acumular la suma de las áreas
    double cdf_aproximada = 0.0;

    //Suma de Riemann desde el punto inicial hasta x_final
    for (double x_iter = x_inicial; x_iter <= x_final; x_iter += SALTO) {
        //Calcular la densidad gaussiana
        double coeficiente = 1.0 / (desviacion * sqrt(2.0 * PI));
        double exponente = -0.5 * pow((x_iter - media) / desviacion, 2.0);
        double altura = coeficiente * exp(exponente);

        //Area del rectángulo = b * h
        double area_rectangulo = altura * SALTO;

        //Sumar al acumulador
        cdf_aproximada += area_rectangulo;
    }

    //Salida
    cout << endl;
    cout << "El valor aproximado de CDF (" << x_final << ") es: " <<
            cdf_aproximada << endl;
    cout << endl;

    return 0; 
}

//**************************************************************************/
//**************************************************************************/