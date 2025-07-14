#include "lib.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

vector<string> cargar_listado(const string & nombre_archivo){
    vector<string> juego;  // Vector para almacenar las palabras
    ifstream infile(nombre_archivo);  // Leeo con "ifstream"
   

    if (infile.is_open()) { 
        //Me aseguro de que se haya abierto correctamente el archivo correspondiente
          if (infile.good() == false) {
        cout << "No se pudo abrir el archivo de forma correcta" << nombre_archivo << endl;
        exit(1);
        }
        // Caso base: archivo complementamente vacío
        // Esto lo hago inmediatamente, después de abrir el archivo, para verificar si el listado no contiene ninguna palabra.
        // Uso peek() para "espiar" el siguiente carácter, sin avanzar en la lectura del archivo.
         else if(infile.peek() == ifstream::traits_type::eof()) {
            cout << "El archivo está vacío." << endl;
            }else{
                string palabra;
            while (!infile.eof()){ 
                // La idea de la guarda del while, es mover el cursor palabra a palabra hasta que el archivo haya llegado al final 
                getline(infile,palabra); // Tomo "palabra a palabra"
                /* Antes de ingresar la palabra, verifico si la línea específica leída del archivo no está vacía
                antes de agregar la palabra al vector.
                 Ingresa al if ---> Devuelve True si la palabra no está vacía. */
                 if(!palabra.empty()){
                    juego.push_back(palabra); // Lo agregamos atrás por una cuestión de comodidad del vector
                }
            }
        }
    }
    infile.close();  // Cierro el archivo, ya que dejo de utilizarlo!
    return juego;
}

bool intento_valido(const string & intento, const string & palabra_secreta, const vector<string> &listado){
    int tamaño_intento = intento.size();
    int tamaño_misteriosa = palabra_secreta.size();
    // Defino mis variable para checkear ¿si es cierto o no?
    bool incorrecto = false;
    bool correcto = true;
    //Para checkear si es legal o no, verifico que el intento tenga el mismo tamaño que la palabra misteriosa:
    if(tamaño_intento == tamaño_misteriosa){
        //Me fijo que el intento sea un palabra reconocida del listado.txt
        int iterador = 0;
        while(iterador<listado.size()){
            if(intento == listado[iterador]){ // Intento es una palabra fija, mientras que listado tiene un conjunto de palabras, por eso itero solo ahí
                return correcto; // Quiere decir que la palabra fue hallada!
            }
            iterador++;
        }
    }
// Si dentro de recorrer el archivo, no se encontro la palabra secreta, es lógico que no este por eso devuelvo False.
    return incorrecto;
}

vector<EstadoLetra> evaluar_intento(const string & intento, const string & palabra_secreta){
    vector <EstadoLetra> answer;
    // Esto iterará de 0 a 4 posiciones (ya que la palabra/intento siempre será de 5)
    for(int i=0; i<intento.size();++i){
        if(intento[i] == palabra_secreta[i]){
            answer.push_back(EstadoLetra::LugarCorrecto); // Coloco en el caso de que sea válido 
        }else{
            int j = 0;
            while(j<palabra_secreta.size()){
                // En el caso de que la letra se encuentre en la palabra, pero no en el lugar correspondiente.
                // Es decir la letra forma parte de la palabra_secreta pero posiciones distintas. 
                if(intento[i] == palabra_secreta[j]){
                    answer.push_back(EstadoLetra::LugarIncorrecto);
                    // Salida del ciclo:
                    break;
            // Caso cuando llegamos al final y no estuvo presente en ningun caso cierta letra.
            }else if(j==palabra_secreta.size()-1){
                answer.push_back(EstadoLetra::NoPresente);
                // Salida del ciclo:
                break;

            }
        j++;
        }
    }
    }
    return answer;
}

string respuesta_en_string(const vector<EstadoLetra> & respuesta){
    string res;
    // Hago un ciclo para recorrer toda la respuesta y como es un str para agregar utilizo append o + en cada caso:
    for(int i=0; i<respuesta.size();++i){
        if(respuesta[i]== EstadoLetra::LugarCorrecto){ // Estadoletra  = objeto
            res = res + "+";
        } else if(respuesta[i] == EstadoLetra::LugarIncorrecto){
            res.append("-");
        } else{
            res.append("X");
        }
    }
    return res;
}