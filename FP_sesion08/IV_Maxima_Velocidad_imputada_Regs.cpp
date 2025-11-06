/***************************************************************************/
// FUNDAMENTOS DE PROGRAMACION
//
// MARIO MARTINEZ CALLEJON
//
// SESION 08
/*
	Programa que lee los datos de varios vehículos (matrícula, tipo de radar,
	velocidad) y calcula la velocidad imputada para cada uno. El programa
	determina y muestra la matrícula del vehículo con la máxima velocidad
	imputada. La lectura finaliza cuando se introduce "FIN" como matrícula.
   
	NOTA: Si la velocidad captada es inferior a 10 km/h, se considera error de 
    captación.
   
	Entradas: matrícula (string), tipo de radar (char), velocidad (double).
	Salidas:  Matrícula con máxima velocidad imputada, sanciones individuales
              y estadísticas finales (total sanciones, puntos, multas y 
              promedios).

    NOTA: Se supone que los datos introducidos son correctos
*/
/***************************************************************************/

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

/***************************************************************************/

// Struct para almacenar sanciones
struct Sancion {
    int puntos;
    int multa;
};

/***************************************************************************/
// Calcula la velocidad imputada y almacena la multa y puntos sancionados.
// Parámetros: velocidad_captada, la velocidad que ha captado el radar.
//             tipo_radar, indica si el radar es fijo o móvil.
//             sancion, struct para almacenar sanciones.
// Devuelve: la velocidad imputada.
/***************************************************************************/

double VelocidadImputada(double velocidad_captada, char tipo_radar, 
                         Sancion &sancion) 
{
    // Constantes para radares
    const double UMBRAL_MARGEN_LINEAL = 100.0;
    const double MARGEN_FIJO = 5.0;
    const double MARGEN_MOVIL = 7.0;
    const double PORCENTAJE_FIJO = 0.05;
    const double PORCENTAJE_MOVIL = 0.07;   
    // Constantes para la sanción
    const double U1 = 120.0, U2 = 150.0, U3 = 170.0, U4 = 180.0, U5 = 190.0;
    const int PTS_U1 = 0, PTS_U2 = 2, PTS_U3 = 4, PTS_U4 = 6, PTS_U5 = 6;
    const int MULTA_U1 = 100, MULTA_U2 = 350, MULTA_U3 = 475, MULTA_U4 = 600,
              MULTA_U5 = 750;

    // Inicializar con un valor base para manejar tipos de radar no válidos.
    double velocidad_imputada = velocidad_captada;
    tipo_radar = toupper(tipo_radar);

    // Calcular la velocidad imputada según el tipo de radar
    if (tipo_radar == 'F') {
        if (velocidad_captada <= UMBRAL_MARGEN_LINEAL)
            velocidad_imputada = velocidad_captada - MARGEN_FIJO;
        else
            velocidad_imputada = velocidad_captada * (1.0 - PORCENTAJE_FIJO);
    } else if (tipo_radar == 'M') { 
        if (velocidad_captada <= UMBRAL_MARGEN_LINEAL)
            velocidad_imputada = velocidad_captada - MARGEN_MOVIL;
        else
            velocidad_imputada = velocidad_captada * (1.0 - PORCENTAJE_MOVIL);
    }

    // Inicializar sanción a 0.
    sancion.puntos = 0;
    sancion.multa = 0;

    // Calcular la sanción solo si el tipo de radar era válido (F/M)
    if (tipo_radar == 'F' || tipo_radar == 'M') {
        // Calcular los puntos y la multa correspondiente
        if (velocidad_imputada > U5) {
            sancion.puntos = PTS_U5; 
            sancion.multa = MULTA_U5; 
        } else if (velocidad_imputada > U4) { 
            sancion.puntos = PTS_U4; 
            sancion.multa = MULTA_U4; 
        } else if (velocidad_imputada > U3) {
            sancion.puntos = PTS_U3; 
            sancion.multa = MULTA_U3; 
        } else if (velocidad_imputada > U2) {
            sancion.puntos = PTS_U2;
            sancion.multa = MULTA_U2; 
        } else if (velocidad_imputada > U1) { 
            sancion.puntos = PTS_U1; 
            sancion.multa = MULTA_U1; 
        }
    }
    
    return velocidad_imputada;
}

/***************************************************************************/
// Función main
/***************************************************************************/

int main() 
{
	// Constantes
	const double ERROR_CAPTACION = 10.0;
    const double LIMITE_VELOCIDAD = 120.0;

	// Variables de entrada para cada vehículo
	string matricula;
	double velocidad_captada;
	char tipo_radar;

	// Variables para registrar el máximo
	string matricula_max_velocidad;
	double max_velocidad_imputada = 0.0;

    // Variables para estadísticas
    int total_sanciones = 0;
    int total_puntos = 0;
    int total_multas = 0;

	cout << endl;
	cout << "Introduzca matricula, tipo de radar (F/M) y velocidad." << endl;
	cout << "Use FIN como matricula para terminar." << endl;

	// Lectura adelantada de la matrícula
	cin >> matricula;

	while (matricula != "FIN") {
        //Variables para almacenar sanciones
        Sancion sancion;

		cin >> tipo_radar;
        cin >> velocidad_captada;

		// Validación de error de captación
		if (velocidad_captada < ERROR_CAPTACION) {
			cout << "Error en la captacion de la velocidad para " << matricula 
                 << endl;
		} else {
			// Cálculo de velocidad imputada
			double velocidad_imputada = VelocidadImputada(velocidad_captada, 
                                        tipo_radar, sancion);

			cout << "-Vehiculo " << matricula << " -> Velocidad imputada: "
                 << fixed << setprecision(1) << velocidad_imputada << " km/h." 
                 << endl;

			// Comprobar si es la nueva velocidad máxima
			if (velocidad_imputada > max_velocidad_imputada) {
				max_velocidad_imputada = velocidad_imputada;
				matricula_max_velocidad = matricula;
			}
            
            // Comprobar si hay sanción y mostrarla
            if (velocidad_imputada > LIMITE_VELOCIDAD) {

                cout << "-Sancion para " << matricula << ":" << sancion.multa 
                     << " euros y " << sancion.puntos << " puntos." << endl;

                // Actualizar estadísticas
                total_sanciones++;
                total_puntos += sancion.puntos;
                total_multas += sancion.multa;
            }
            cout << "----------------------------------------" << endl;
		}
		// Siguiente lectura
		cin >> matricula;
	} // Fin del while

	// Salida final
	cout << endl << "Vehiculo con maxima velocidad imputada:" << endl;

    // Mostrar la velocidad máxima sólo si se ha procesado algún vehículo
    if (!matricula_max_velocidad.empty()) {
	    cout << matricula_max_velocidad << " " << fixed << setprecision(1)
             << max_velocidad_imputada << " km/h." << endl;
    } else {
        cout << "No se procesaron vehiculos." << endl;
    }

    // Mostrar estadísticas
    cout << "\n----------------------------------------" << endl;
    cout << "ESTADISTICAS FINALES DE SANCIONES" << endl;
    cout << "----------------------------------------" << endl;
    cout << "Total de sanciones tramitadas: " << total_sanciones << endl;
    if (total_sanciones > 0) {
        cout << "Total de puntos detraidos: " << total_puntos << endl;
        cout << "Total de multas (euros): " << total_multas << endl;
        cout << "Media de puntos por sancion: " << fixed << setprecision(2)
             << (double)total_puntos / total_sanciones << endl;
        cout << "Cuantia media por sancion (euros): " << fixed <<setprecision(2)
             << (double)total_multas / total_sanciones << " euros" << endl;
    }

	return 0;
}

/***************************************************************************/