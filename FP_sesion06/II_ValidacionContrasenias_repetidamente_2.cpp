/***************************************************************************
// FUNDAMENTOS DE PROGRAMACION
//
// MARIO MARTINEZ CALLEJON
//
// SESION 06
/*
    Validador de Contrase�as con L�mite de Intentos.

    Este programa solicita al usuario que introduzca una contrase�a y la
    verifica seg�n un conjunto de reglas de seguridad. Si la contrase�a
    no cumple los requisitos, muestra un mensaje de error y vuelve a
    pedirla hasta que se llegue al m�ximo de 3 intentos.

    Las reglas de validaci�n son las siguientes:
    1.  Debe tener una longitud m�nima de 12 caracteres.
    2.  Debe contener al menos 2 letras may�sculas (A-Z).
    3.  Debe incluir al menos uno de los siguientes caracteres: @ - * !
    4.  No puede tener dos caracteres id�nticos consecutivos.

    Entradas:
        - contrasenia: La cadena de texto (string) que el usuario introduce
          para ser validada.

    Salidas:
        - Mensaje de error si la contrase�a no es v�lida en un intento.
        - Mensaje de �xito si la contrase�a es aceptada en uno de los intentos.
        - Mensaje de fracaso si no se logra en los tres intentos.
        - N�mero total de intentos realizados.

    NOTA: La comprobaci�n de las letras may�sculas se realiza utilizando
    los valores del c�digo ASCII para 'A' y 'Z'.
*/
//**************************************************************************/

#include <iostream>
#include <string>

using namespace std;

//**************************************************************************/
//**************************************************************************/

int main() {
    //Constantes
    const string ESPECIALES = "@-*!";
    const int MINIMO = 65;  //Valor Ascii de 'A'
    const int MAXIMO = 90;  //Valor Ascii de 'Z'
    const int MAX_INTENTOS = 3; // L�mite de intentos

    //Variables
    string contrasenia;
    string error;
    bool contrasenia_ok = false; 
    int intentos = 0; // Contador de intentos

    do {
        intentos++; // Se incrementa el contador en cada intento

        //Entrada
        cout << "Intento " << intentos << "/" << MAX_INTENTOS << 
                ". Introduzca su nueva contrasenia: ";
        getline(cin, contrasenia);

        //Comprobaci�n de la contrase�a
        contrasenia_ok = true;
        error = "";  //Eliminar errores de la anterior contrase�a
        if (contrasenia.length() < 12) {
            //Comprobar longitud de la contrase�a
            contrasenia_ok = false;
            error += "ERROR: Debe tener al menos 12 caracteres\n";
        }

        //Comprobacion de tipos de caracteres
        int num_mayusculas = 0;      //Contadores para validar
        int num_especiales = 0;
        char c_actual, c_especial;  //Variables para recorrer las cadenas

        for (int i = 0; i < contrasenia.length(); i++) {
            c_actual = contrasenia.at(i);
            if (c_actual >= MINIMO && c_actual <= MAXIMO) {
                //Comprobar si es mayuscula
                num_mayusculas++;
            } else {
                //Comprobar si es un caracter especial admitido
                for (int j = 0; j < ESPECIALES.length(); j++) {
                    c_especial = ESPECIALES.at(j);
                    if (c_actual == c_especial){
                        //Se ha encontrado un caracter especial admitido
                        num_especiales++;
                    }
                }
            }
        }
        //Mostrar errores
        if (num_mayusculas < 2) {
            contrasenia_ok = false;
            error += "ERROR: Debe tener al menos 2 letras mayusculas\n";
        }
        if (num_especiales == 0) {
            contrasenia_ok = false;
            error += "ERROR: Debe contener alguno de los siguientes "
                     "caracteres: @ - * !\n";
        }

        char c_siguiente; //Variable para almacenar el char siguiente a c_actual
        for (int i = 0; i < contrasenia.length() - 1; i++) {
            c_actual = contrasenia.at(i);
            c_siguiente = contrasenia.at(i + 1);

            if (c_actual == c_siguiente) {
                //Si los char son iguales invalidar contrase�a
                contrasenia_ok = false;
                error += "ERROR: No puede haber dos caracteres iguales "
                         "consecutivos\n";
                break; // Salimos del bucle para no repetir el mismo error
            }

        }
        //Mostrar error si la contrase�a no es v�lida
        if (!contrasenia_ok) {
            cout << error;
        }
        cout << endl;
    } while (!contrasenia_ok && intentos < MAX_INTENTOS);

    //Salida
    cout << "====================================================" << endl;
    if (contrasenia_ok) {
        cout << "EXITO: Su contrasenia se ha registrado correctamente." << endl;
        cout << "Contrasenia registrada: " << contrasenia << endl;
    } else {
        cout << "FRACASO: No se ha introducido una contrasenia valida." << endl;
        cout << "Registro finalizado sin exito." << endl;
    }
    cout << "Numero de intentos realizados: " << intentos << endl;
    cout << "====================================================" << endl;
}

//**************************************************************************/
//**************************************************************************/