/***************************************************************************/
// FUNDAMENTOS DE PROGRAMACION
//
// MARIO MARTINEZ CALLEJON
//
// SESION 09
/*
    Programa que implementa la Ley D'Hondt para la asignación de escaños
    en una elección.

    El programa lee el número total de escaños, el número de partidos y los
    votos de cada uno. Luego, asigna los escaños en varias rondas
    basándose en la Ley D'Hont. Finalmente, muestra los resultados
    ordenados de mayor a menor por número de escaños obtenidos.

    Entradas:
        - Número total de escaños a repartir.
        - Número de partidos políticos.
        - Nombre y votos obtenidos por cada partido.

    Salidas:
        - Lista de partidos con los escaños asignados, ordenados
          decrecientemente por escaños y, en caso de empate, por votos.
*/
/***************************************************************************/

#include <iostream>
#include <string>


using namespace std;

struct Partido {
    string nombre;
    long votos;
    int escagnos;
};

const int MAX_PARTIDOS = 50; // Definimos un máximo de partidos

/***************************************************************************/
/*
    Ordena un vector de partidos. El criterio de ordenación es:
    1. Descendente por número de escaños.
    2. En caso de empate en escaños, descendente por número de votos.

    Parámetros:
        partidos: Array de structs Partido a ordenar (se modifica).
        num_partidos: Número de elementos en el array.
*/
/***************************************************************************/
void OrdenarPartidos(Partido partidos[], int num_partidos) {
    // Algoritmo de ordenación por selección
    for (int i = 0; i < num_partidos - 1; ++i) {
        int indice_max = i;
        
        for (int j = i + 1; j < num_partidos; ++j) {
            // El que tiene más escaños aparece antes
            if (partidos[j].escagnos > partidos[indice_max].escagnos) {
                indice_max = j;
            } 
            // Si hay empate en escaños aparece antes el que tiene más votos
            else if (partidos[j].escagnos == partidos[indice_max].escagnos) {
                if (partidos[j].votos > partidos[indice_max].votos) {
                    indice_max = j;
                }
            }
        }
        // Intercambiar el elemento actual con el máximo encontrado
        if (indice_max != i) {
            Partido temp = partidos[i];
            partidos[i] = partidos[indice_max];
            partidos[indice_max] = temp;
        }
    }
}

/***************************************************************************/
/*
    Asigna los escaños a los partidos según la Ley D'Hondt.
    El proceso es iterativo: en cada iteración se asigna un escaño al partido
    con el cociente más alto (votos / (escaños_actuales + 1)).

    Parámetros:
        partidos:       Array de structs Partido.
        num_partidos:   Número de elementos en el array de partidos.
        total_escagnos:  Número total de escaños a repartir.
*/
/***************************************************************************/
void AsignarEscagnos(Partido partidos[], int num_partidos, int total_escagnos) {
    for (int i = 0; i < total_escagnos; ++i) {
        double max_cociente = -1.0;
        int indice_ganador = -1;

        // Encontrar el partido con el cociente máximo en esta iteración
        for (int j = 0; j < num_partidos; ++j) {
            // cociente = Votos / (Escaños_actuales + 1)
            double cociente_actual = static_cast<double>(partidos[j].votos) 
                                     / (partidos[j].escagnos + 1);

            if (cociente_actual > max_cociente) {
                max_cociente = cociente_actual;
                indice_ganador = j;
            } 
            // Si los cocientes son iguales, gana el que tiene más votos.
            else if (cociente_actual == max_cociente) {
                if (partidos[j].votos > partidos[indice_ganador].votos) {
                    indice_ganador = j;
                }
            }
        }

        // Asignar el escaño al partido ganador de esta ronda
        if (indice_ganador != -1) {
            partidos[indice_ganador].escagnos++;
        }
    }
}

/***************************************************************************/
/***************************************************************************/

int main() {
    int total_escagnos;
    int num_partidos;

    // Lectura de datos iniciales
    cout << "Introduce el numero total de escagnos a repartir: ";
    cin >> total_escagnos;

    do {
        cout << "Introduce el numero de partidos que han participado (maximo " 
             << MAX_PARTIDOS << "): ";
        cin >> num_partidos;
    } while (num_partidos <= 0 || num_partidos > MAX_PARTIDOS);

    Partido partidos[MAX_PARTIDOS];

    // Lectura de los datos de cada partido
    for (int i = 0; i < num_partidos; ++i) {
        cout << "\n--- Partido " << i + 1 << " ---" << endl;
        cout << "Nombre: ";
        cin >> partidos[i].nombre;
        cout << "Votos: ";
        cin >> partidos[i].votos;
        partidos[i].escagnos = 0; // Inicializar escaños a 0
    }

    // Proceso de asignación de escaños (Ley D'Hondt)
    AsignarEscagnos(partidos, num_partidos, total_escagnos);

    // Ordenar los resultados para la presentación
    OrdenarPartidos(partidos, num_partidos);

    // Mostrar los resultados finales
    cout << "\n--- RESULTADOS FINALES ---" << endl;
    cout << "--------------------------" << endl;
    cout << "Partido\t\tEscagnos" << endl;
    cout << "--------------------------" << endl;

    for (int i = 0; i < num_partidos; ++i) {
        cout << partidos[i].nombre << "\t\t" << partidos[i].escagnos << endl;
    }
    cout << "--------------------------" << endl;

    return 0;
}

/***************************************************************************/
/***************************************************************************/