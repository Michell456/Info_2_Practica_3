#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string leerArchivo(const string &nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo: " << nombreArchivo << endl;
        return "";
    }

    string contenido = "";
    string linea;
    while (getline(archivo, linea)) {
        contenido += linea + "\n"; // Agregamos salto de línea si quieres mantener la estructura
    }

    archivo.close();
    return contenido;
}

void editarArchivo(const string &nombreArchivo, const string &contenido) {
    ofstream archivo(nombreArchivo, ios::app); // siempre agregar al final

    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo: " << nombreArchivo << endl;
        return;
    }

    archivo << contenido; // escribimos el contenido
    archivo.close();
}
