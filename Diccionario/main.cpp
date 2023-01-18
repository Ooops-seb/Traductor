#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Clase para un nodo del árbol binario de búsqueda
class NodoArbol {
public:

    NodoArbol *izquierda;
    NodoArbol *derecha;

    string espanol;
    string kichwa;
    string frances;
    string italiano;


    NodoArbol(string espanol, string kichwa, string frances, string italiano) {
        this->izquierda = this->derecha = NULL;
        this->espanol = espanol;
        this->kichwa = kichwa;
        this->frances = frances;
        this->italiano = italiano;
    }
};

// Clase para la tabla de dispersión
class Idiomas {
public:
    NodoArbol **tabla;
    int tablatam;

    Idiomas(int tablatam) {
        this->tablatam = tablatam;
        tabla = new NodoArbol*[tablatam];
        for(int i = 0; i < tablatam; i++)
            tabla[i] = NULL;
    }

    // Función de dispersión
    int dispercion(string palabra) {
        int suma = 0;
        for(int i = 0; i < palabra.length(); i++)
            suma += palabra[i];
        return suma % tablatam;
    }

    // Función para InsertarPalabra una palabra y su traducción en el árbol
    NodoArbol* InsertarPalabra(NodoArbol* raiz, string espanol, string kichwa, string frances, string italiano) {
        if(raiz == NULL)
            return new NodoArbol(espanol, kichwa, frances, italiano);
        if(espanol < raiz->espanol)
            raiz->izquierda = InsertarPalabra(raiz->izquierda, espanol, kichwa, frances, italiano);
        else if(espanol > raiz->espanol)
            raiz->derecha = InsertarPalabra(raiz->derecha, espanol, kichwa, frances, italiano);
        return raiz;
    }

    // Función para BuscarPalabraArbol una palabra en el árbol y devolver su traducción
    NodoArbol* BuscarPalabraArbol(NodoArbol* raiz, string espanol) {
            if(raiz == NULL)
                return NULL;
            if(raiz->espanol == espanol)
                return raiz;
            if(espanol < raiz->espanol)
                return BuscarPalabraArbol(raiz->izquierda, espanol);
            return BuscarPalabraArbol(raiz->derecha, espanol);
        }

    // Función para cargar el Idiomas desde el archivo "palabras.dat"
    void CargarPalabras() {
        ifstream archivo("C:\\Users\\seb_3\\OneDrive\\Documentos\\Universidad\\202251 - Oct22-Mar23\\ESTRUCTURA DE DATOS\\Diccionario\\api.dat");
        string espanol, kichwa, frances, italiano;
        while(archivo >> espanol >> kichwa >> frances >> italiano) {
            int indice = dispercion(espanol);
            tabla[indice] = InsertarPalabra(tabla[indice], espanol, kichwa, frances, italiano);
        }
        archivo.close();
    }

    // Función para traducir una frase ingresada
    void Traductor() {
        string frase;
        fflush(stdin);
        cout << "Ingrese la frase a traducir: ";
        getline(cin, frase);
        cout<<endl;
        string palabra = "";
        // Busqueda de palabras para traduccion en Kichwa 
        cout<<"-> Kichwa: ";
        for(int i = 0; i <= frase.length(); i++) {
            if(frase[i] == ' ' || frase[i] == '\0') {
                NodoArbol* traduccion = BuscarPalabraArbol(tabla[dispercion(palabra)], palabra);
                if(traduccion != NULL) {
                        cout << traduccion->kichwa << " ";
                }
                else
                    cout <<"*"<<palabra << "*"<<" ";
                palabra = "";
            }
            else
                palabra += frase[i];
        }
        cout<<endl;

        // Busqueda de palabras para traduccion en Frances 
        cout<<"-> Frances: ";
        for(int i = 0; i <= frase.length(); i++) {
            if(frase[i] == ' ' || frase[i] == '\0') {
                NodoArbol* traduccion = BuscarPalabraArbol(tabla[dispercion(palabra)], palabra);
                if(traduccion != NULL) {
                        cout << traduccion->frances << " ";
                }
                else
                    cout <<"*"<<palabra << "*"<<" ";
                palabra = "";
            }
            else
                palabra += frase[i];
        }
        cout<<endl;

        // Busqueda de palabras para traduccion en Italiano 
        cout<<"-> Italiano: ";
        for(int i = 0; i <= frase.length(); i++) {
            if(frase[i] == ' ' || frase[i] == '\0') {
                NodoArbol* traduccion = BuscarPalabraArbol(tabla[dispercion(palabra)], palabra);
                if(traduccion != NULL) {
                        cout << traduccion->italiano << " ";
                }
                else
                    cout <<"*"<<palabra << "*"<<" ";
                palabra = "";
            }
            else
                palabra += frase[i];
        }
        cout<<endl;
    }
};

int main() {
    string op;
    Idiomas dic(1000);
    dic.CargarPalabras();
    dic.Traductor();

    return 0;
}
