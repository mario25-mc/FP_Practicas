/***************************************************************************
// FUNDAMENTOS DE PROGRAMACION
//
// MARIO MARTINEZ CALLEJON
//
// SESION 10
/*
    Programa que genera "ASCII art" dibujando figuras geométricas simples
    (círculos y rectángulos) en un tablero bidimensional representado
    por una matriz de caracteres.

    El programa define varias figuras geométricas y luego itera sobre cada
    celda (píxel) del tablero para determinar si pertenece a una o más
    figuras. Las celdas se marcan con diferentes caracteres según si
    forman parte de una figura ('*') o de una intersección de varias ('x').

    Entradas:
        - Ninguna. Las figuras están predefinidas en el código.

    Salidas:
        - Una representación visual de las figuras en la consola.
*/
//**************************************************************************/
#include <iostream>
#include <string>
#include <cmath> // Para sqrt

using namespace std;

// Constantes del tablero
const int NUM_FILAS = 51; // y = 0..50, 0 abajo
const int NUM_COLS = 51;  // x = 0..50, 0 izquierda

// Tipos
struct Punto2D {
    double x, y;
};
struct Circunferencia {
    Punto2D c;
    double r;
};
struct Rectangulo {
    Punto2D esi; // (x_izq, y_sup)
    Punto2D eid; // (x_der, y_inf)
};

/***********************************************************************/
// Crea un Punto2D a partir de sus coordenadas.
// Parámetros:
//   x: Coordenada en el eje X.
//   y: Coordenada en el eje Y.
// Devuelve:
//   Un struct Punto2D con las coordenadas dadas.
/***********************************************************************/
Punto2D SetPunto2D (double x, double y) {
    Punto2D p;
    p.x = x; 
    p.y = y; 
    return p;
}

/***********************************************************************/
// Crea una Circunferencia a partir de su centro y radio.
// Parámetros:
//   c: El punto central de la circunferencia (Punto2D).
//   r: El radio de la circunferencia.
// Devuelve:
//   Un struct Circunferencia con los datos proporcionados.
/***********************************************************************/
Circunferencia SetCircunferencia (Punto2D c, double r) {
    Circunferencia circ;
    circ.c = c;
    circ.r = r;
    return circ;
}

/***********************************************************************/
// Crea un Rectangulo a partir de dos de sus esquinas opuestas.
// Parámetros:
//   esi: Esquina superior izquierda (Punto2D).
//   eid: Esquina inferior derecha (Punto2D).
// Devuelve:
//   Un struct Rectangulo definido por las esquinas dadas.
/***********************************************************************/
Rectangulo SetRectangulo (Punto2D esi, Punto2D eid) {
    Rectangulo rect;
    rect.esi = esi;
    rect.eid = eid;
    return rect;
}

/***********************************************************************/
// Obtiene la coordenada X (abscisa) de un punto.
// Parámetros:
//   p: El punto a consultar.
// Devuelve:
//   La coordenada X del punto.
/***********************************************************************/
double GetAbscisa (Punto2D p) {
    return p.x;
}

/***********************************************************************/
// Obtiene la coordenada Y (ordenada) de un punto.
// Parámetros:
//   p: El punto a consultar.
// Devuelve:
//   La coordenada Y del punto.
/***********************************************************************/
double GetOrdenada (Punto2D p) {
    return p.y;
}

/***********************************************************************/
// Obtiene el radio de una circunferencia.
// Parámetros:
//   c: La circunferencia a consultar.
// Devuelve:
//   El radio de la circunferencia.
/***********************************************************************/
double GetRadio (Circunferencia c) {
    return c.r;
}

/***********************************************************************/
// Obtiene el centro de una circunferencia.
// Parámetros:
//   c: La circunferencia a consultar.
// Devuelve:
//   El punto central (Punto2D) de la circunferencia.
/***********************************************************************/
Punto2D GetCentro (Circunferencia c) {
    return c.c;
}

/***********************************************************************/
// Obtiene la esquina superior izquierda de un rectángulo.
// Parámetros:
//   r: El rectángulo a consultar.
// Devuelve:
//   El punto (Punto2D) de la esquina superior izquierda.
/***********************************************************************/
Punto2D GetPuntoSuperiorIzquierdaRectangulo (Rectangulo r) {
    return r.esi;
}

/***********************************************************************/
// Obtiene la esquina superior derecha de un rectángulo.
// Parámetros:
//   r: El rectángulo a consultar.
// Devuelve:
//   El punto (Punto2D) de la esquina superior derecha.
/***********************************************************************/
Punto2D GetPuntoSuperiorDerechaRectangulo (Rectangulo r) {
    return SetPunto2D(GetAbscisa(r.eid), GetOrdenada(r.esi));
}

/***********************************************************************/
// Obtiene la esquina inferior izquierda de un rectángulo.
// Parámetros:
//   r: El rectángulo a consultar.
// Devuelve:
//   El punto (Punto2D) de la esquina inferior izquierda.
/***********************************************************************/
Punto2D GetPuntoInferiorIzquierdaRectangulo (Rectangulo r) {
    return SetPunto2D(GetAbscisa(r.esi), GetOrdenada(r.eid));
}

/***********************************************************************/
// Obtiene la esquina inferior derecha de un rectángulo.
// Parámetros:
//   r: El rectángulo a consultar.
// Devuelve:
//   El punto (Punto2D) de la esquina inferior derecha.
/***********************************************************************/
Punto2D GetPuntoInferiorDerechaRectangulo (Rectangulo r) {
    return r.eid;
}

/***********************************************************************/
// Convierte un Punto2D a una cadena de texto.
// Parámetros:
//   p: El punto a convertir.
// Devuelve:
//   Una cadena con el formato "(x, y)".
/***********************************************************************/
string ToString (Punto2D p) {
    return "(" + to_string(p.x) + ", " + to_string(p.y) + ")";
}

/***********************************************************************/
// Convierte una Circunferencia a una cadena de texto.
// Parámetros:
//   c: La circunferencia a convertir.
// Devuelve:
//   Una cadena con el formato "C((x, y), r)".
/***********************************************************************/
string ToString (Circunferencia c) {
    return "C(" + ToString(c.c) + ", " + to_string(c.r) + ")";
}

/***********************************************************************/
// Convierte un Rectangulo a una cadena de texto.
// Parámetros:
//   r: El rectángulo a convertir.
// Devuelve:
//   Una cadena con el formato "R((x1, y1), (x2, y2))".
/***********************************************************************/
string ToString (Rectangulo r) {
    return "R(" + ToString(r.esi) + ", " + ToString(r.eid) + ")";
}

/***********************************************************************/
// Calcula la distancia euclídea entre dos puntos.
// Parámetros:
//   uno: El primer punto.
//   otro: El segundo punto.
// Devuelve:
//   La distancia entre los dos puntos.
/***********************************************************************/
double DistanciaEuclidea (Punto2D uno, Punto2D otro) {
    double dx = GetAbscisa(uno) - GetAbscisa(otro);
    double dy = GetOrdenada(uno) - GetOrdenada(otro);
    return sqrt(dx*dx + dy*dy);
}

/***********************************************************************/
// Calcula el ancho de un rectángulo.
// Parámetros:
//   r: El rectángulo a medir.
// Devuelve:
//   El ancho del rectángulo.
/***********************************************************************/
double AnchoRectangulo (Rectangulo r) {
    return GetAbscisa(r.eid) - GetAbscisa(r.esi);
}

/***********************************************************************/
// Calcula el alto de un rectángulo.
// Parámetros:
//   r: El rectángulo a medir.
// Devuelve:
//   El alto del rectángulo.
/***********************************************************************/
double AltoRectangulo (Rectangulo r) {
    return GetOrdenada(r.esi) - GetOrdenada(r.eid);
}

/***********************************************************************/
// Comprueba si un punto está contenido dentro de una circunferencia.
// Un punto está contenido si su distancia al centro es menor o igual al radio.
// Parámetros:
//   p: El punto a comprobar.
//   c: La circunferencia.
// Devuelve:
//   true si el punto está contenido, false en caso contrario.
/***********************************************************************/
bool PuntoContenidoEnCircunferencia (Punto2D p, Circunferencia c) {
    return DistanciaEuclidea(p, GetCentro(c)) <= GetRadio(c);
}

/***********************************************************************/
// Comprueba si un punto está contenido dentro de un rectángulo.
// Un punto está contenido si sus coordenadas están entre las de las esquinas.
// Parámetros:
//   p: El punto a comprobar.
//   r: El rectángulo.
// Devuelve:
//   true si el punto está contenido, false en caso contrario.
/***********************************************************************/
bool PuntoContenidoEnRectangulo (Punto2D p, Rectangulo r) {
    bool dentro_x = (GetAbscisa(p) >= GetAbscisa(r.esi)) && (GetAbscisa(p) 
                    <= GetAbscisa(r.eid));
    bool dentro_y = (GetOrdenada(p) >= GetOrdenada(r.eid)) && (GetOrdenada(p) 
                    <= GetOrdenada(r.esi));
    return dentro_x && dentro_y;
}

/***************************************************************************/
/***************************************************************************/
int main() {

    Circunferencia circ = SetCircunferencia(SetPunto2D(5, 5), 10);
    Rectangulo r1 = SetRectangulo(SetPunto2D(8, 8), SetPunto2D(40, 0));
    Rectangulo r2 = SetRectangulo(SetPunto2D(20, 15), SetPunto2D(30, 5));
    
    //Declarar y rellenar el tablero con el carácter de fondo
    char tablero[NUM_FILAS][NUM_COLS];
    for (int i = 0; i < NUM_FILAS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            tablero[i][j] = '.';
        }
    }

    //Recorrer cada "punto" del sistema de coordenadas y dibujar en la matriz
    for (int y = 0; y < NUM_FILAS; y++) {
        for (int x = 0; x < NUM_COLS; x++) {
            Punto2D p = SetPunto2D(x, y);

            int count = 0;  // Contador de cuantas figuras incluyen el punto p
            if (PuntoContenidoEnCircunferencia(p, circ)) count++;
            if (PuntoContenidoEnRectangulo(p, r1)) count++;
            if (PuntoContenidoEnRectangulo(p, r2)) count++;

            // El origen es la esquina inferior izquierda, pero en la matriz
            // la fila 0 es la superior. Hay que invertir el eje Y.
            int fila_matriz = (NUM_FILAS - 1) - y;

            if (count > 1) {
                tablero[fila_matriz][x] = 'x'; // Intersección
            } else if (count == 1) {
                tablero[fila_matriz][x] = '*'; // Parte de una sola figura
            }
        }
    }

    // Imprimir el contenido de la matriz
    for (int i = 0; i < NUM_FILAS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            cout << tablero[i][j];
        }
        cout << endl;
    }

    return 0;
}