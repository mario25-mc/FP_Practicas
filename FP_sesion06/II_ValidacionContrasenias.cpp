/***************************************************************************
// FUNDAMENTOS DE PROGRAMACION
//
// MARIO MARTINEZ CALLEJON
//
// SESION 06
/*
    Validador de Contraseñas.

    Este programa solicita al usuario que introduzca una contraseña y la
    verifica según un conjunto de reglas de seguridad. Si la contraseña
    no cumple los requisitos, muestra un mensaje de error y vuelve a
    pedirla hasta que se introduzca una válida.

    Las reglas de validación son las siguientes:
    1.  Debe tener una longitud mínima de 12 caracteres.
    2.  Debe contener al menos 2 letras mayúsculas (A-Z).
    3.  Debe incluir al menos uno de los siguientes caracteres: @ - * !
    4.  No puede tener dos caracteres idénticos consecutivos.

    Entradas:
        - contrasenia: La cadena de texto (string) que el usuario introduce
          para ser validada.

    Salidas:
        - Mensaje de error si la contraseña no es válida, indicando el
          fallo encontrado.
        - Mensaje de éxito cuando la contraseña es aceptada.

    NOTA: La comprobación de las letras mayúsculas se realiza utilizando
    los valores del código ASCII para 'A' y 'Z'.
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

    //Variables
    string contrasenia;
    string error;
    bool contrasenia_ok;

    do {
        //Entrada
        cout << "Introduzca su nueva contrasenia: ";
        getline(cin, contrasenia);

        //Comprobación de la contraseña
        contrasenia_ok = true;
        error = "";  //Eliminar errores de la anterior contraseña
        if (contrasenia.length() < 12) {
            //Comprobar longitud de la contraseña
            contrasenia_ok = false;
            error += "ERROR: Debe tener al menos 12 caracteres\n";
        } 

        //Comprobacion de tipos de caracteres
        int num_mayusculas = 0;     //Contadores para validar
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
            error += "ERROR: Debe tener al menos 2 letras mayusculas.\n";
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
                //Si los char son iguales invalidar contraseña
                contrasenia_ok = false;
                error += "ERROR: No puede haber mas de dos caracteres iguales "
                         "consecutivos\n";
            }
        
        }
        //Mostrar error si la contraseña no es válida
        if (!contrasenia_ok) {
            cout << error;
        }
        cout << endl;
    } while (!contrasenia_ok);

    //Salida
    cout << "====================================================" << endl;
    cout << "EXITO: Su contrasenia se ha registrado correctamente" << endl;
    cout << "====================================================" << endl;
}

//**************************************************************************/
//**************************************************************************/