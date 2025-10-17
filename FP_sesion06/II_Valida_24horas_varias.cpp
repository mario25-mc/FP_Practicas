/***************************************************************************
// FUNDAMENTOS DE PROGRAMACION
//
// Nombre del autor: MARIO MARTINEZ CALLEJON (EJEMPLO)
//
// SESION 06
/*
   Validador de Horas en Formato 24H

   Programa que lee una serie indeterminada de cadenas de texto y
   valida si cada una corresponde a un formato de hora válido (HH:MM).

   Para cada cadena leída, el programa elimina los espacios iniciales y
   finales, comprueba si el formato y el rango de la hora son correctos,
   y muestra un mensaje indicando el resultado. El proceso termina cuando
   el usuario introduce la palabra "FIN".

   Entradas:
       - Cadenas de texto introducidas por el usuario, una por línea.

   Salidas:
       - Mensaje de validación para cada hora.
       - Resumen final con el total de horas procesadas y el
         porcentaje de horas correctas e incorrectas.

   NOTA: Se utiliza getline para leer líneas completas y la validación
   del formato se realiza carácter a carácter.
*/
//**************************************************************************/

#include <iostream>
#include <string>      // Para el uso de string
#include <iomanip>     // Para formatear la salida con fixed y setprecision
#include <cctype>      // Para la función isdigit

using namespace std;

//**************************************************************************/
//**************************************************************************/

int main() {
    cout.setf(ios::fixed);      // Notación de punto fijo para los reales
    cout.setf(ios::showpoint);  // Mostrar siempre decimales

    // Variables de entrada y de control
    string linea_leida;

    // Variables para las estadísticas
    int total_leidas = 0;
    int correctas = 0;
    int incorrectas = 0;

    // Mensaje de bienvenida
    cout << endl;
    cout << "--- VALIDADOR DE HORAS EN FORMATO 24H ---" << endl;

    // Bucle principal de lectura y procesamiento
    bool seguir_leyendo = true;
    while (seguir_leyendo) {
        cout << endl;
        cout << "Introduzca una hora (HH:MM) o escriba FIN para terminar: ";
        getline(cin, linea_leida);

        // Eliminar espacios en blanco iniciales y finales
        string hora_procesar;
        int inicio = 0;
        int ultimo_no_espacio = -1;

        // Recorrer toda la cadena
        for (int i = 0; i < linea_leida.length(); i++) {
            if (linea_leida.at(i) != ' ') {
                // Si el caracter no es espacio, i obtiene el valor del primero
                if (inicio == 0 && ultimo_no_espacio == -1) {
                    inicio = i;
                }
                // Guardamos la posición del último carácter no espacio
                ultimo_no_espacio = i;
            }
        }

        //Extraer la subcadena si encontramos algún carácter no espacio
        if (ultimo_no_espacio >= 0) {
            hora_procesar = linea_leida.substr(inicio, ultimo_no_espacio 
                                                       - inicio + 1);
        } else {
            hora_procesar = ""; // La línea estaba vacía o solo tenía espacios
        }

        // Proceso de validación
        bool es_correcta = true;
        string motivo_error;

        // 1. Comprobar longitud
        if (hora_procesar.length() != 5) {
            es_correcta = false;
            motivo_error = "Longitud incorrecta. Formato: HH:MM (5 chars).";
        } else {
            // 2. Comprobar formato carácter a carácter
            for (int i = 0; i < 5 && es_correcta; i++) {
                char char_actual = hora_procesar.at(i);

                // Comprueba las posiciones que deben ser dígitos 
                if (i != 2) {
                    if (!isdigit(char_actual)) {
                        es_correcta = false;
                        motivo_error="Formato invalido. H/M deben ser digitos.";
                    }
                } else {    // Comprueba la posición del separador 
                    if (char_actual != ':') {
                        es_correcta = false;
                        motivo_error = "Separador incorrecto. Debe ser ':'.";
                    }
                }
            }
        }

        // 3. Si el formato es correcto, comprobar los rangos numéricos
        if (es_correcta) {
            // Extraer horas y minutos como cadenas
            string horas_str = hora_procesar.substr(0, 2);
            string minutos_str = hora_procesar.substr(3, 2);

            // Convertir a entero
            int horas = stoi(horas_str);
            int minutos = stoi(minutos_str);

            // Validar rango
            if (horas < 0 || horas > 23) {
                es_correcta = false;
                motivo_error = "Rango de hora invalido. Debe ser 00-23.";
            } else if (minutos < 0 || minutos > 59) {
                es_correcta = false;
                motivo_error = "Rango de minutos invalido. Debe ser 00-59.";
            }
        }
        
        // Condición de salida del bucle
        if (hora_procesar == "FIN") {
            seguir_leyendo = false;
        }
        else if (!hora_procesar.empty()) {
            total_leidas++; // Si la cadena no esta vacía sumar una hora leida
            
            // Mostrar resultado de la validación y actualizar contadores
            if (es_correcta) {
                cout << "'" << hora_procesar << "' -> HORA CORRECTA." << endl;
                correctas++;
            } else {
                cout << "'" << hora_procesar << "' -> HORA INCORRECTA. Motivo: " 
                    << motivo_error << endl;
                incorrectas++;
            }
        }
    }

    // Salida
    cout << endl;
    cout << "=============================================" << endl;
    cout << "               RESUMEN FINAL" << endl;
    cout << "=============================================" << endl;
    cout << "Total de horas procesadas: " << total_leidas << endl;
    cout << " -Correctas:   " << correctas << endl;
    cout << " -Incorrectas: " << incorrectas << endl;
    
    //Mostrar porcentajes
    if (total_leidas > 0) {
        double porc_correctas = (static_cast<double>(correctas) 
                                 / total_leidas) * 100.0;
        double porc_incorrectas = (static_cast<double>(incorrectas) 
                                   / total_leidas) * 100.0;
        cout << setprecision(2); // Formatear a 2 decimales
        cout << "Porcentaje de correctas:   " << porc_correctas << "%" << endl;
        cout << "Porcentaje de incorrectas: " << porc_incorrectas << "%";
        cout << endl;
    } else {
        cout << endl;
        cout << "No se ha procesado ninguna hora." << endl;
    }
     cout << "=============================================" << endl;

    return 0;
}

//**************************************************************************/
//**************************************************************************/