/***************************************************************************
// FUNDAMENTOS DE PROGRAMACION
//
// MARIO MARTINEZ CALLEJON
//
// SESION 13
/*
    Este programa define clases para representar puntos 2D, una colección
    de puntos (NubePuntos) y un rectángulo. El objetivo principal es
    calcular el rectángulo envolvente mínimo que contiene todos los
    puntos de una nube de puntos.

    Clases implementadas:
    - Punto2D: Representa un punto con coordenadas (x, y).
    - NubePuntos: Almacena una colección de objetos Punto2D.
    - Rectangulo: Representa un rectángulo definido por dos esquinas opuestas.

    Salidas:
        - Coordenadas del rectángulo envolvente calculado.
*/
//**************************************************************************/
#include <iostream>

using namespace std;

/***************************************************************************/
// Definición de la clase Punto2D
/***************************************************************************/
class Punto2D
{
private:

    double x, y;    // Valores x e y del punto

public:

    /***********************************************************************/
    // Constructor por defecto
    Punto2D(void) {};

    /***********************************************************************/
    // Constructor con parámetros.
    // Parámetros: absc, el valor de la abscisa
    //             ord, el valor de la ordenada
    Punto2D(double absc, double ord) 
        : x(absc), y(ord)
    {}

    /***********************************************************************/
    // Modifica la coordenada x del punto.
    // Parámetros: valor_x, el nuevo valor para la coordenada x.
    void SetCoordenadas(double absc, double ord)
    {
        x = absc;
        y = ord;
    }

    /***********************************************************************/
    // Devuelve la coordenada x del punto.
    double Abscisa(void)
    {
        return x;
    }

    /***********************************************************************/
    // Devuelve la coordenada y del punto.
    double Ordenada(void)
    {
        return y;
    }
};

/***************************************************************************/
// Definición de la clase Rectangulo
/***************************************************************************/
class Rectangulo
{
private:
    Punto2D esq_sup_izda;
    Punto2D esq_inf_dcha;

public:
    /***********************************************************************/
    // Constructor con parámetros.
    // Parámetros: la_esq_sup_izda, el punto de la esquina superior izquierda.
    //             la_esq_inf_dcha, el punto de la esquina inferior derecha.
    Rectangulo(Punto2D la_esq_sup_izda, Punto2D la_esq_inf_dcha)
        : esq_sup_izda(la_esq_sup_izda), esq_inf_dcha(la_esq_inf_dcha)
    {}

    /***********************************************************************/
    // Devuelve el punto de la esquina superior izquierda.
    Punto2D EsqSupIzda()
    {
        return esq_sup_izda;
    }

    /***********************************************************************/
    // Devuelve el punto de la esquina inferior derecha.
    Punto2D EsqInfDcha()
    {
        return esq_inf_dcha;
    }

    /***********************************************************************/
    // Modifica el punto de la esquina superior izquierda.
    void SetEsqSupIzda(Punto2D la_esq_sup_izda) {
        esq_sup_izda = la_esq_sup_izda;
    }

    /***********************************************************************/
    // Modifica el punto de la esquina inferior derecha.
    void SetEsqInfDcha(Punto2D la_esq_inf_dcha) {
        esq_inf_dcha = la_esq_inf_dcha;
    }
};

/***************************************************************************/
// Definición de la clase NubePuntos
/***************************************************************************/
class NubePuntos
{
private:
    static const int MAX = 100;
    Punto2D v[MAX];
    int util;

public:
    /***********************************************************************/
    // Constructor por defecto
    NubePuntos()
        : util(0)
    {}

    /***********************************************************************/
    // Devuelve la capacidad máxima de la nube de puntos.
    int Capacidad()
    {
        return MAX;
    }

    /***********************************************************************/
    // Devuelve el número de puntos actualmente en la nube.
    int Utilizados()
    {
        return util;
    }

    /***********************************************************************/
    // Añade un punto a la nube si hay capacidad.
    // Parámetros: pto, el punto a añadir.
    void Aniade(Punto2D pto)
    {
        if (util < MAX) {
            v[util] = pto;
            util++;
        }
    }

    /***********************************************************************/
    // Devuelve el punto en la posición especificada.
    // Parámetros: indice, la posición del punto a devolver.
    // PRE: 0 <= indice < Utilizados()
    Punto2D Elemento(int indice)
    {
        return v[indice];
    }

    /***********************************************************************/
    // Calcula y devuelve el rectángulo envolvente de la nube de puntos.
    // PRE: La nube debe contener al menos un punto.
    Rectangulo RectanguloEnvolvente()
    {
        // Asumimos que hay al menos un punto.
        // Inicializamos los mínimos y máximos con el primer punto.
        double min_x = v[0].Abscisa();
        double max_x = v[0].Abscisa();
        double min_y = v[0].Ordenada();
        double max_y = v[0].Ordenada();

        // Recorremos el resto de puntos para encontrar los extremos.
        for (int i = 1; i < util; i++) {
            double current_x = v[i].Abscisa();
            double current_y = v[i].Ordenada();

            if (current_x < min_x) {
                min_x = current_x;
            }
            if (current_x > max_x) {
                max_x = current_x;
            }
            if (current_y < min_y) {
                min_y = current_y;
            }
            if (current_y > max_y) {
                max_y = current_y;
            }
        }

        // Creamos los puntos de las esquinas del rectángulo envolvente.
        Punto2D esq_sup_izda(min_x, max_y);
        Punto2D esq_inf_dcha(max_x, min_y);

        return Rectangulo(esq_sup_izda, esq_inf_dcha);
    }
};

/***************************************************************************/
// Función main
/***************************************************************************/

int main()
{
    NubePuntos nube;
    double x, y;

    cout << "Introduzca puntos (x y).";
    cout << "Para terminar, introduzca el origen (0 0)." << endl;

    // Lectura adelantada
    cout << "Nuevo punto: " << endl;
    cout << "x: ";
    cin >> x;
    cout << "y: ";
    cin >> y;
    cout << endl;

    Punto2D punto_leido(x, y);

    // Bucle mientras no se introduzca el origen y haya espacio en la nube
    while ((punto_leido.Abscisa() != 0 || punto_leido.Ordenada() != 0) 
           && nube.Utilizados() < nube.Capacidad())
    {
        nube.Aniade(punto_leido);

        // Leer el siguiente punto
        cout << "Nuevo punto: " << endl;
        cout << "x: ";
        cin >> x;
        cout << "y: ";
        cin >> y;
        cout << endl;

        punto_leido.SetCoordenadas(x, y);
    }

    cout << "\n------------------------------------------" << endl;
    cout << "Se han introducido " << nube.Utilizados() << " puntos.";
    cout << endl << endl;

    // Calcular y mostrar el rectángulo envolvente si hay puntos
    if (nube.Utilizados() > 0)
    {
        Rectangulo rect_env = nube.RectanguloEnvolvente();
        Punto2D sup_izda = rect_env.EsqSupIzda();
        Punto2D inf_dcha = rect_env.EsqInfDcha();

        cout << "El rectangulo envolvente es:" << endl;
        cout << "  Esquina Superior Izquierda: (" << sup_izda.Abscisa() << ", " 
             << sup_izda.Ordenada() << ")" << endl;
        cout << "  Esquina Inferior Derecha:   (" << inf_dcha.Abscisa() << ", " 
             << inf_dcha.Ordenada() << ")" << endl;
    }

    return 0;
}

/***************************************************************************/
/***************************************************************************/