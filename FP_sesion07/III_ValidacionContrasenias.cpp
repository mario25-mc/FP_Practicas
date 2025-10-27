/***************************************************************************
// FUNDAMENTOS DE PROGRAMACION
//
// MARIO MARTINEZ CALLEJON
//
// SESION 07
/*
    Programa que valida una contrase�a introducida por el usuario bas�ndose
    en un conjunto de reglas de seguridad. El usuario tiene un n�mero limitado
    de intentos para introducir una contrase�a v�lida.

    Reglas de validaci�n:
    - Longitud m�nima de 12 caracteres.
    - Al menos 2 letras may�sculas.
    - Al menos un car�cter especial de la lista: @, -, *, !
    - No puede haber dos caracteres iguales consecutivos.

    Entradas:
        - contrasenia: La contrase�a introducida por el usuario (string).

    Salidas:
        - Mensajes de �xito o fracaso.
        - Lista de errores de validaci�n si la contrase�a es incorrecta.
*/
//**************************************************************************/
#include <iostream>

using namespace std;

//Declaraci�n de funciones
void MostrarError(string);
bool Contrasenia_ok(string);
bool Longitud_ok(string);
bool Mayusculas_ok(string);
bool Char_especiales_ok(string);
bool Repeticion_ok(string);

// Variable global para almacenar los mensajes de error de la contrase�a.
string error = "";

//**************************************************************************/
//**************************************************************************/

int main(){
    // Constante que define el n�mero m�ximo de intentos permitidos.
    const int MAX_INTENTOS = 3; 
    
    int intentos = 0; // Contador para los intentos realizados.
    string contrasenia;

    do {
        intentos++; // Se incrementa el contador en cada intento
        error = ""; // Reiniciar la cadena de errores en cada nuevo intento.

        //Entrada
        cout << "Intento " << intentos << "/" << MAX_INTENTOS << 
                ". Introduzca su nueva contrasenia: ";
        getline(cin, contrasenia);
        
        //Mostrar error si la contrase�a no es v�lida
        MostrarError(contrasenia);

    } while (intentos < MAX_INTENTOS && !Contrasenia_ok(contrasenia));

    //Salida
    cout << "====================================================" << endl;
    if (Contrasenia_ok(contrasenia)) {
        cout << "EXITO: Su contrasenia se ha registrado correctamente." << endl;
        cout << "Contrasenia registrada: " << contrasenia << endl;
    } else {
        cout << "FRACASO: No se ha introducido una contrasenia valida." << endl;
        cout << "Registro finalizado sin exito." << endl;
    }
    cout << "Numero de intentos realizados: " << intentos << endl;
    cout << "====================================================" << endl;

    return 0;
}

//**************************************************************************/
//**************************************************************************/

bool Longitud_ok(string contrasenia)
{   
    bool longitud_ok = true; //Asumir que la longitud es correcta inicialmente.

    if (contrasenia.length() < 12) {
            // Si la longitud es menor a 12, la validaci�n falla.
            longitud_ok = false;
            
            // A�adir el error a la cadena global.
            error += "\tERROR: Debe tener al menos 12 caracteres\n"; 
    }
    return longitud_ok;
}

//**************************************************************************/
//**************************************************************************/

bool Mayusculas_ok(string contrasenia)
{   
    // Rango de caracteres ASCII para las letras may�sculas.
    const char MINIMO = 'A';
    const char MAXIMO = 'Z';

    bool mayusculas_ok = true;
    int num_mayusculas = 0; // Contador para las may�sculas encontradas.
    char c_actual;

    for (int i = 0; i < contrasenia.length(); i++) {
            c_actual = contrasenia.at(i);

            // Si el car�cter est� en el rango, se incrementa el contador.
            if (c_actual >= MINIMO && c_actual <= MAXIMO) {
                num_mayusculas++;
            }
    }   

    if (num_mayusculas < 2) {
        // Si no se alcanzan las 2 may�sculas, la validaci�n falla.
        mayusculas_ok = false;
        error += "\tERROR: Debe tener al menos 2 letras mayusculas\n";
    }

    return mayusculas_ok;
}

//**************************************************************************/
//**************************************************************************/

bool Char_especiales_ok(string contrasenia)
{
    const string ESPECIALES = "@-*!";   //Caracteres especiales admitidos

    bool especiales_ok = true;
    int num_especiales = 0; // Contador de caracteres especiales.
    char c_actual, c_especial;

    // Bucle anidado para comparar cada car�cter con los especiales.
    for (int i = 0; i < contrasenia.length(); i++) {
        c_actual = contrasenia.at(i);

        //Comprobar si es un caracter especial admitido
        for (int j = 0; j < ESPECIALES.length(); j++) {
            c_especial = ESPECIALES.at(j);
            if (c_actual == c_especial){
                //Se ha encontrado un caracter especial admitido
                num_especiales++;
            }
        }
    }

    // Si no se encuentra ning�n car�cter especial, la validaci�n falla.
    if (num_especiales == 0) {
            especiales_ok = false;
            error += "\tERROR: Debe contener alguno de los siguientes "
                     "caracteres: @ - * !\n";
    }
    return especiales_ok;
}

//**************************************************************************/
//**************************************************************************/

bool Repeticion_ok(string contrasenia)
{
    bool repeticion_ok = true;
    char c_actual;
    char c_siguiente; // Variable para almacenar el car�cter siguiente al actual

    // Recorre la contrase�a hasta el pen�ltimo car�cter.
    for (int i = 0; i < contrasenia.length() - 1 && repeticion_ok; i++) {  
        c_actual = contrasenia.at(i);
        c_siguiente = contrasenia.at(i + 1);
        
        if (c_actual == c_siguiente) {
            // Si un car�cter es igual al siguiente, la validaci�n falla.
            repeticion_ok = false;
            error += "\tERROR: No puede haber dos caracteres iguales "
                     "consecutivos\n";
        }
    }
    return repeticion_ok;
}

//**************************************************************************/
//**************************************************************************/

bool Contrasenia_ok(string contrasenia) 
{   
    bool todo_ok;

    // Casos especiales para contrase�as vac�as o muy cortas.
    if (contrasenia.empty()){
        todo_ok = false;
        error = "\tERROR: Contrasenia vacia\n";
    } else if (contrasenia.length() < 3){
        todo_ok = false;
        error = "\tERROR: Contrasenia demasiado corta para evaluar\n";
    } else {
        // Se llama a cada funci�n de validaci�n para que se ejecuten todos
        // los filtros y se muestren todos los errores
        bool rep_ok = Repeticion_ok(contrasenia);
        bool mayus_ok = Mayusculas_ok(contrasenia);
        bool esp_ok = Char_especiales_ok(contrasenia);
        bool lon_ok = Longitud_ok(contrasenia);
        
        // El resultado final es true solo si todas las validaciones 
        // individuales son true
        todo_ok = rep_ok && mayus_ok && esp_ok && lon_ok;
    }
    return todo_ok;
}

//**************************************************************************/
//**************************************************************************/

void MostrarError(string contrasenia)
{   
    // Si la contrasenia no pasa alg�n filtro, imprimirlo en pantalla
    if (!Contrasenia_ok(contrasenia) ) {
        cout << error;
    }
    cout << endl;
}

//**************************************************************************/
//**************************************************************************/