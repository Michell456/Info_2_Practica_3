#include <iostream>
#include <bitset>
#include <fstream>
#include <string>
using namespace std;

string metCodificador1(const string &texto, int semilla);
string MetDecodificador1(const string &textoBinario, int semilla);
string metCodificador2(const string &texto, int semilla);
string metDecodificador2(const string &textoBinario, int semilla);
string leerArchivo(const string &nombreArchivo);
void guardarArchivo(const string &nombre, const string &contenido);
string verificacionUsuario();
void agregarUsuario();
void leerSaldoYDescontar(const string &cedula);
void retirarSaldo(const string &cedula);

int main() {
    while (true) {
        int opcion;

        cout << "\n=== MENU PRINCIPAL ===\n";
        cout << "1. Codificadores y decodificadores\n";
        cout << "2. Aplicacion del banco\n";
        cout << "3. Salir\n";
        cout << "Elija una opcion: ";
        cin >> opcion;
        cin.ignore();

        if (opcion == 1) {
            int semilla, metodo, operacion;

            // Seleccionar operación
            while (true) {
                cout << "¿Deseas codificar o decodificar? (1=codificar, 2=decodificar): ";
                cin >> operacion;
                if (operacion == 1 || operacion == 2) break;
                cout << "Opción inválida.\n";
            }

            while (true) {
                cout << "¿Qué metodo deseas usar (1 o 2)?: ";
                cin >> metodo;
                if (metodo == 1 || metodo == 2) break;
                cout << "Opción inválida.\n";
            }

            while (true) {
                cout << "¿Cual es la semilla? (2 a 8): ";
                cin >> semilla;
                if (semilla >= 2 && semilla <= 8) break;
                cout << "Semilla invalida.\n";
            }

            cin.ignore();
            string texto, nombreArchivo, contenido, resultado;

            if (operacion == 1) {
                cout << "Ingresa el texto que deseas codificar: ";
                getline(cin, texto);

                if (metodo == 1) {
                    resultado = metCodificador1(texto, semilla);
                } else {
                    resultado = metCodificador2(texto, semilla);
                }

                cout << "Texto codificado: " << resultado << endl;

                cout << "¿Deseas guardar en archivo? (s/n): ";
                char guardar;
                cin >> guardar;
                cin.ignore();

                if (guardar == 's' || guardar == 'S') {
                    cout << "Nombre del archivo: ";
                    string nombreArchivo;
                    getline(cin, nombreArchivo);
                    guardarArchivo(nombreArchivo, resultado);
                    cout << "Archivo guardado correctamente.\n";
                }
            }
            else {
                cout << "Ingresa el nombre del archivo a decodificar: ";
                getline(cin, nombreArchivo);
                contenido = leerArchivo(nombreArchivo);

                if (contenido.empty()) {
                    cout << "Error: No se pudo leer el archivo o está vacío.\n";
                    continue;
                }

                if (metodo == 1) {
                    resultado = MetDecodificador1(contenido, semilla);
                } else {
                    resultado = metDecodificador2(contenido, semilla);
                }

                cout << "Texto decodificado: " << resultado << endl;
            }
        }

        else if (opcion == 2) {
            // Sistema bancario
            cout << "\n=== SISTEMA DEL BANCO ===\n";
            string tipo = verificacionUsuario();

            if (tipo == "admin") {

                while (true) {
                    cout << "\n--- MODO ADMIN ---\n";
                    cout << "1. Agregar usuario\n";
                    cout << "2. Volver al menu principal\n";
                    cout << "Elige una opcion: ";
                    int opAdmin;
                    cin >> opAdmin;
                    cin.ignore();

                    if (opAdmin == 1) {
                        agregarUsuario();
                    }
                    else if (opAdmin == 2) {
                        break;
                    }
                    else {
                        cout << "Opcion invalida.\n";
                    }
                }
            }
            else if (tipo != "") {

                while (true) {
                    cout << "\n--- MODO CLIENTE ---\n";
                    cout << "1. Consultar saldo (costo 1000 COP)\n";
                    cout << "2. Retirar dinero (costo 1000 COP)\n";
                    cout << "3. Volver al menu principal\n";
                    cout << "Elige una opcion: ";
                    int opCliente;
                    cin >> opCliente;
                    cin.ignore();

                    if (opCliente == 1) {
                        leerSaldoYDescontar(tipo);
                    }
                    else if (opCliente == 2) {
                        retirarSaldo(tipo);
                    }
                    else if (opCliente == 3) {
                        break;
                    }
                    else {
                        cout << "Opcion invalida.\n";
                    }
                }
            }
        }

        else if (opcion == 3) {
            cout << "Saliendo del programa...\n";
            break;
        }
        else {
            cout << "Opcion invalida.\n";
        }
    }

    return 0;
}



