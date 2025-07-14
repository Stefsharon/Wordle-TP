#include "lib.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <ostream>
using namespace std;

int main(){
    // Inicializo la semilla para generar números pseudo-aleatorios
    srand(time(0));

    // Cargo el listado completo de palabras del archivo "listado.txt":
    vector<string> listado = cargar_listado("listado.txt");

    /*
    El objetivo ahora es: 
    1) Elegir una palabra secreta al azar 
    2) ¿Como lo hago? Mediante la semilla y la cantidad total de palabras del archivo
    3) Comentario extra: En total tenemos --> 37 palabras dadas (cualquiera de ellas)
    */
  
     string palabra_secreta = listado[rand() % listado.size()]; 
     // Si la cuenta da 0, quiere decir que cargar_listado es vacío ya abarque el caso en dicha función.


    //  Antes de empezar el juego, necesito saber el número máximo de intentos permitidos:
    // Las posibilidades que me quedan se decrementan dentro del ciclo a medida de que no hayas adivinado:
    int intentos_restantes = 6; 
    
    // Bienvenida del Juego:
     cout << "Hola, soy Steffy! ¿Estás listo para jugar?" << endl;

    // Bucle principal del juego:
    // La guarda del ciclo se debe a que los intentos van hacer 6,5,4,3,2,1, si llegas a 0 perdiste!
    while (intentos_restantes > 0) {
        // Solicitar al usuario que haga un intento:
        string possibility;
        cout<< "Ingresa tu intento (" << intentos_restantes << " intentos restantes): ";
        cin >> possibility;

        // Checkeo si el intento es lo esperado:
        if (intento_valido(possibility, palabra_secreta, listado)) {
            // Si lo es evaluamos el intento:
            vector<EstadoLetra> resultado = evaluar_intento(possibility, palabra_secreta);

            // Muestro la respuesta mediante los simbolos (X+-) para que el usuario lo vea:
            cout << "Respuesta: " << respuesta_en_string(resultado) << endl;

            // Finalmente verifico si el usuario logro adivinar la palabra misteriosa:
            if (resultado == vector<EstadoLetra>(palabra_secreta.size(), EstadoLetra::LugarCorrecto)) {
                cout << "¡Felicidades :)! Adivinaste la palabra secreta: " << palabra_secreta << endl;
                break;  // Salir del bucle si el usuario adivinó la palabra
            }else{
                cout << "¡Casi lo logras! Intenta otra vez." << endl;
            }

            // Restarle una chance al usuario a medida de que no acierta:
            intentos_restantes--;
        } else {
            // Informar que el intento no es válido (que no está la palabra cargada en listado)
            // En este caso, no se le resta al usuario una posibilidad.
            cout << "Intento no válido. Por favor, ingresa un nuevo intento." << endl;
        }
    }

    // Caso extra: Verificar si se agotaron los intentos
    if (intentos_restantes == 0) {
        cout << "¡Oh lo siento! Se agotaron los intentos. La palabra secreta era: " << palabra_secreta << endl;
    }

    return 0;  
}