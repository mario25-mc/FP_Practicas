/***************************************************************************
// FUNDAMENTOS DE PROGRAMACION
//
// MARIO MARTINEZ CALLEJON
//
// SESION 10
/*
    Programa que valida una contraseña introducida por el usuario utilizando
    la clase ValidadorContrasenias. El usuario tiene un número limitado
    de intentos para introducir una contraseña que cumpla un conjunto de
    reglas de seguridad.

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

/***************************************************************************/
// Definición de la clase ValidadorContrasenias
/***************************************************************************/
class ValidadorContrasenias {
private:
    string passwd;  // Contraseña que se valida
    string mensaje; // Mensaje de error

    /***********************************************************************/
    // Comprueba si la contraseña tiene la longitud mínima requerida (12).
    // Si no la cumple, añade un mensaje de error.
    // Devuelve: true si la longitud es correcta, false en caso contrario.
    /***********************************************************************/
    bool Longitud_ok() {
        bool longitud_ok = true; 

        if (passwd.length() < 12) {
            // Si la longitud es menor a 12, la validación falla.
            longitud_ok = false;
            
            // Añadir el error al mensaje de la clase.
            mensaje += "\tERROR: Debe tener al menos 12 caracteres\n";
        }
        return longitud_ok;
    }

    /***********************************************************************/
    // Comprueba si la contraseña contiene al menos 2 letras mayúsculas.
    // Si no las cumple, añade un mensaje de error.
    // Devuelve: true si tiene suficientes mayúsculas, false en caso contrario.
    /***********************************************************************/
    bool Mayusculas_ok() {
        bool mayusculas_ok = true;
        int num_mayusculas = 0;
        char c_actual;

        for (int i = 0; i < passwd.length(); i++) {
            c_actual = passwd.at(i);

            // Si el carácter está en el rango, se incrementa el contador.
            if (c_actual >= 'A' && c_actual <= 'Z') {
                num_mayusculas++;
            }
        }
        if (num_mayusculas < 2) {
            // Si no se alcanzan las 2 mayúsculas, la validación falla.
            mayusculas_ok = false;
            mensaje += "\tERROR: Debe tener al menos 2 letras mayusculas\n";
        }

        return mayusculas_ok;
    }

    /***********************************************************************/
    // Comprueba si la contraseña contiene al menos un carácter especial.
    // Si no lo cumple, añade un mensaje de error.
    // Devuelve: true si tiene un carácter especial, false en caso contrario.
    /***********************************************************************/
    bool Char_especiales_ok() {
        const string ESPECIALES = "@-*!";

        bool especiales_ok = true;
        int num_especiales = 0;
        char c_actual, c_especial;

        // Bucle anidado para comparar cada carácter con los especiales.
        for (int i = 0; i < passwd.length(); i++) 
        {
            c_actual = passwd.at(i);
            
            for (int j = 0; j < ESPECIALES.length(); j++) 
            {
                c_especial = ESPECIALES.at(j);
                if (c_actual == c_especial) 
                {
                    // Se ha encontrado un carácter especial admitido
                    num_especiales++;   
                }
            }
        }

        // Si no hay ningún carácter especia, añadir el error correspondiente
        if (num_especiales == 0) {
            especiales_ok = false;
            mensaje += "\tERROR: Debe contener alguno de los siguientes "
                       "caracteres: @ - * !\n";
        }
        return especiales_ok;
    }

    /***********************************************************************/
    // Comprueba si la contraseña tiene caracteres consecutivos repetidos.
    // Si los tiene, añade un mensaje de error.
    // Devuelve: true si no hay repeticiones, false en caso contrario.
    /***********************************************************************/
    bool Repeticion_ok() {
        bool repeticion_ok = true;
        char c_actual;
        char c_siguiente;

        // Recorre la contraseña hasta el penúltimo carácter.
        for (int i = 0; i < passwd.length() - 1 && repeticion_ok; i++) {
            c_actual = passwd.at(i);
            c_siguiente = passwd.at(i + 1);

            if (c_actual == c_siguiente) {
                // Si un carácter es igual al siguiente, la validación falla.
                repeticion_ok = false;
                mensaje += "\tERROR: No puede haber dos caracteres iguales "
                           "consecutivos\n";
            }
        }
        return repeticion_ok;
    }

public:

    /***********************************************************************/
    // Asigna una contraseña al objeto para su posterior validación.
    // Parámetros:
    //   p: la contraseña a validar.
    /***********************************************************************/
    void SetContrasenia(string p) {
        passwd = p;
        mensaje = "";
    }

    /***********************************************************************/
    // Devuelve el mensaje de error acumulado tras la validación.
    // Devuelve: un string con todos los errores encontrados.
    /***********************************************************************/
    string GetMensajeError() {
        return mensaje;
    }

    /***********************************************************************/
    // Realiza todas las validaciones sobre la contraseña.
    // Acumula los mensajes de error en el miembro "mensaje".
    // Devuelve: true si la contraseña cumple todas las reglas, false si no.
    /***********************************************************************/
    bool EsValida() {
        mensaje = ""; // Limpiar mensaje antes de cada validación completa

        bool lon_ok = Longitud_ok();
        bool mayus_ok = Mayusculas_ok();
        bool esp_ok = Char_especiales_ok();
        bool rep_ok = Repeticion_ok();

        if (passwd.empty()) {
            mensaje = "\tERROR: Contrasenia vacia\n";
        } else 
        {
            // Se llama a cada función para acumular todos los mensajes de error.
            lon_ok = Longitud_ok();
            mayus_ok = Mayusculas_ok();
            esp_ok = Char_especiales_ok();
            rep_ok = Repeticion_ok();
        }

        return lon_ok && mayus_ok && esp_ok && rep_ok;
    }
};

//**************************************************************************/
//**************************************************************************/

int main(){
    // Constante que define el número máximo de intentos permitidos.
    const int MAX_INTENTOS = 3; 
    
    int intentos = 0; // Contador para los intentos realizados.
    string contrasenia;
    bool contrasenia_valida = false;

    do {
        intentos++;

        // Pedir la contraseña al usuario
        cout << "Intento " << intentos << "/" << MAX_INTENTOS << 
                ". Introduzca su nueva contrasenia: ";
        getline(cin, contrasenia);
        
        // Usar la clase para validar la contraseña
        ValidadorContrasenias validador;
        validador.SetContrasenia(contrasenia);

        // Comprobar el resultado y mostrar errores si es necesario
        contrasenia_valida = validador.EsValida();
        if (!contrasenia_valida) {
            cout << validador.GetMensajeError();
        }
        cout << endl;

    // El bucle se repite mientras queden intentos y la contraseña no sea válida
    } while (intentos < MAX_INTENTOS && !contrasenia_valida);

    // Mostrar el resultado final del proceso
    cout << "====================================================" << endl;
    if (contrasenia_valida) {
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