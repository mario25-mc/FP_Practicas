/***************************************************************************/
// FUNDAMENTOS DE PROGRAMACION
//
// MARIO MARTINEZ CALLEJON
//
// SESION 04
/*
	Programa que calcula la velocidad imputada según el tipo de radar (fijo o 
    móvil) y determina la sanción correspondiente en una autovía con límite de 
    120 km/h. Se aplican los márgenes de error especificados por la normativa y 
    se consulta la tabla de sanciones para exceso de velocidad.
   
	NOTA: Si la velocidad captada es inferior a 10 km/h, se considera error de 
    captación.
   
	Entradas: velocidad captada (real), tipo de radar (carácter: 'F' o 'M').
	Salidas:  velocidad imputada (real), puntos a detraer (entero), multa 
              (entero).
*/
/***************************************************************************/

#include <iostream>
#include <iomanip>

using namespace std;

/***************************************************************************/
/***************************************************************************/

int main() {
	// Constantes (umbrales, márgenes y sanciones)
	const double LIMITE_AUTOVIA = 120.0;         
	const double ERROR_CAPTACION = 10.0;         
	const double UMBRAL_MARGEN_LINEAL = 100.0;   
	const double MARGEN_FIJO = 5.0;         
	const double MARGEN_MOVIL = 7.0;        
	const double PORCENTAJE_FIJO = 0.05;         
	const double PORCENTAJE_MOVIL = 0.07;         

	// Tabla sanciones (umbrales, puntos y multas)
	const double U1 = 120.0;
	const double U2 = 150.0;
	const double U3 = 170.0;
	const double U4 = 180.0;
	const double U5 = 190.0;

	const int PTS_U1 = 0;    
	const int PTS_U2 = 2;    
	const int PTS_U3 = 4;    
	const int PTS_U4 = 6;    
	const int PTS_U5 = 6; 

	const int MULTA_U1 = 100;
	const int MULTA_U2 = 350;
	const int MULTA_U3 = 475;
	const int MULTA_U4 = 600;
	const int MULTA_U5 = 750;

	// Entrada
	double velocidad_captada;
	char tipo_radar;

	cout << endl;
	cout << "Introduzca la velocidad captada (km/h): ";
	cin >> velocidad_captada;
	cout << "Introduzca el tipo de radar (F=fijo, M=móvil): ";
	cin >> tipo_radar;
	cout << endl;

	// Validación de error de captación
	if (velocidad_captada < ERROR_CAPTACION) {
		cout << "Error en la captación de la velocidad." << endl;
	}

	// Cálculo de velocidad imputada
	double velocidad_imputada = velocidad_captada;

	// Normalizar el tipo de radar a mayúscula
	tipo_radar = (toupper(tipo_radar));

	if (tipo_radar == 'F') {
		if (velocidad_captada <= UMBRAL_MARGEN_LINEAL)
			velocidad_imputada = velocidad_captada - MARGEN_FIJO;
		else
			velocidad_imputada = velocidad_captada - 
							     (PORCENTAJE_FIJO * velocidad_captada);
	} else if (tipo_radar == 'M') {
		if (velocidad_captada <= UMBRAL_MARGEN_LINEAL)
			velocidad_imputada = velocidad_captada - MARGEN_MOVIL;
		else
			velocidad_imputada = velocidad_captada - 
			                     (PORCENTAJE_MOVIL * velocidad_captada);
	} else {
		cout << "Tipo de radar no válido." << endl;
		return 0;
	}

	// Mostrar velocidad imputada
	cout << "Velocidad imputada: " << velocidad_imputada << " km/h" << endl;

	// Tabla de sanciones
	int puntos = 0;
	int multa = 0;
	
	if (velocidad_imputada > U5) {
		puntos = PTS_U5; 
		multa = MULTA_U5;
	} else if (velocidad_imputada > U4) {
		puntos = PTS_U4; 
		multa = MULTA_U4;
	} else if (velocidad_imputada > U3) {
		puntos = PTS_U3; 
		multa = MULTA_U3;
	} else if (velocidad_imputada > U2) {
		puntos = PTS_U2; 
		multa = MULTA_U2;
	} else if (velocidad_imputada > U1) {
		puntos = PTS_U1; 
		multa = MULTA_U1;
	}

	// Mostrar sanción si corresponde
	if (velocidad_imputada > 120) {
		cout << "Sanción: " << multa << " euros, " << puntos << " puntos." 
             << endl;
	} else {
		cout << "No hay sanción." << endl;
	}

	return 0;
}
/***************************************************************************/
/***************************************************************************/
