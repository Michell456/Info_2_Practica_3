#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string leerArchivo(const string &nombreArchivo) {
    ifstream archivo(nombreArchivo, ios::binary);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo: " << nombreArchivo << endl;
        return "";
    }

    string contenido((istreambuf_iterator<char>(archivo)), istreambuf_iterator<char>());
    archivo.close();

    // Limpieza: eliminar caracteres no binarios
    string limpio;
    for (char c : contenido) {
        if (c == '0' || c == '1') limpio += c;
    }
    return limpio;
}

void guardarArchivo(const string &nombre, const string &contenido) {
    ofstream salida(nombre);
    salida << contenido;
    salida.close();
}
