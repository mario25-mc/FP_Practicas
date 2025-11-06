/***************************************************************************
// FUNDAMENTOS DE PROGRAMACION
//
// MARIO MARTINEZ CALLEJON
//
// SESION 08
/*
    Programa que valida una contraseña introducida por el usuario basándose
    en un conjunto de reglas de seguridad. El usuario tiene un número limitado
    de intentos para introducir una contraseña válida.

    Reglas de validación:
    - Longitud mínima de 12 caracteres.
    - Al menos 2 letras mayúsculas.
    - Al menos un carácter especial de la lista: @, -, *, !
    - No puede haber dos caracteres iguales consecutivos.

    Entradas:
        - contrasenia: La contraseña introducida por el usuario (string).

    Salidas:
        - Mensajes de éxito o fracaso.
        - Lista de errores de validación si la contraseña es incorrecta.
*/
//**************************************************************************/
#include <iostream>

using namespace std;
//Declaración de funciones
bool Contrasenia_ok(string contrasenia, string &error);
bool Longitud_ok(string contrasenia, string &error);
bool Mayusculas_ok(string contrasenia, string &error);
bool Char_especiales_ok(string contrasenia, string &error);
bool Repeticion_ok(string contrasenia, string &error);

//**************************************************************************/
//**************************************************************************/

int main(){
    // Constante que define el número máximo de intentos permitidos.
    const int MAX_INTENTOS = 3; 
    
    int intentos = 0; // Contador para los intentos realizados.
    string contrasenia;
    string mensaje_error;
    bool es_valida;

    do {
        intentos++; // Se incrementa el contador en cada intento

        //Entrada
        cout << "Intento " << intentos << "/" << MAX_INTENTOS << 
                ". Introduzca su nueva contrasenia: ";
        getline(cin, contrasenia);
        
        es_valida = Contrasenia_ok(contrasenia, mensaje_error);

        //Mostrar error si la contraseña no es válida
        if (!es_valida) {
            cout << mensaje_error;
        }
        cout << endl;
    } while (intentos < MAX_INTENTOS && !es_valida);

    //Salida
    cout << "====================================================" << endl;
    if (es_valida) {
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

bool Longitud_ok(string contrasenia, string &error)
{   
    bool longitud_ok = true; //Asumir que la longitud es correcta inicialmente.

    if (contrasenia.length() < 12) {
            // Si la longitud es menor a 12, la validación falla.
            longitud_ok = false;
            
            // Añadir el error a la cadena global.
            error += "\tERROR: Debe tener al menos 12 caracteres\n"; 
    }
    return longitud_ok;
}

//**************************************************************************/
//**************************************************************************/

bool Mayusculas_ok(string contrasenia, string &error)
{   
    // Rango de caracteres ASCII para las letras mayúsculas.
    const char MINIMO = 'A';
    const char MAXIMO = 'Z';

    bool mayusculas_ok = true;
    int num_mayusculas = 0; // Contador para las mayúsculas encontradas.
    char c_actual;

    for (int i = 0; i < contrasenia.length(); i++) {
            c_actual = contrasenia.at(i);

            // Si el carácter está en el rango, se incrementa el contador.
            if (c_actual >= MINIMO && c_actual <= MAXIMO) {
                num_mayusculas++;
            }
    }   

    if (num_mayusculas < 2) {
        // Si no se alcanzan las 2 mayúsculas, la validación falla.
        mayusculas_ok = false;
        error += "\tERROR: Debe tener al menos 2 letras mayusculas\n";
    }

    return mayusculas_ok;
}

//**************************************************************************/
//**************************************************************************/

bool Char_especiales_ok(string contrasenia, string &error)
{
    const string ESPECIALES = "@-*!";   //Caracteres especiales admitidos

    bool especiales_ok = true;
    int num_especiales = 0; // Contador de caracteres especiales.
    char c_actual, c_especial;

    // Bucle anidado para comparar cada carácter con los especiales.
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

    // Si no se encuentra ningún carácter especial, la validación falla.
    if (num_especiales == 0) {
            especiales_ok = false;
            error += "\tERROR: Debe contener alguno de los siguientes "
                     "caracteres: @ - * !\n";
    }
    return especiales_ok;
}

//**************************************************************************/
//**************************************************************************/

bool Repeticion_ok(string contrasenia, string &error)
{
    bool repeticion_ok = true;
    char c_actual;
    char c_siguiente; // Variable para almacenar el carácter siguiente al actual

    // Recorre la contraseña hasta el penúltimo carácter.
    for (int i = 0; i < contrasenia.length() - 1 && repeticion_ok; i++) {  
        c_actual = contrasenia.at(i);
        c_siguiente = contrasenia.at(i + 1);
        
        if (c_actual == c_siguiente) {
            // Si un carácter es igual al siguiente, la validación falla.
            repeticion_ok = false;
            error += "\tERROR: No puede haber dos caracteres iguales "
                     "consecutivos\n";
        }
    }
    return repeticion_ok;
}

//**************************************************************************/
//**************************************************************************/

bool Contrasenia_ok(string contrasenia, string &error) 
{   
    bool todo_ok;
    error = ""; // Reiniciar la cadena de errores en cada nuevo intento.

    // Casos especiales para contraseñas vacías o muy cortas.
    if (contrasenia.empty()){
        todo_ok = false;
        error += "\tERROR: Contrasenia vacia\n";
    } else if (contrasenia.length() < 3){
        todo_ok = false;
        error += "\tERROR: Contrasenia demasiado corta para evaluar\n";
    } else {
        // Se llama a cada función de validación para que se ejecuten todos
        // los filtros y se muestren todos los errores
        bool rep_ok = Repeticion_ok(contrasenia, error);
        bool mayus_ok = Mayusculas_ok(contrasenia, error);
        bool esp_ok = Char_especiales_ok(contrasenia, error);
        bool lon_ok = Longitud_ok(contrasenia, error);
        
        // El resultado final es true solo si todas las validaciones 
        // individuales son true
        todo_ok = rep_ok && mayus_ok && esp_ok && lon_ok;
    }
    return todo_ok;
}

//**************************************************************************/
//**************************************************************************/