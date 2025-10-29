#include <iostream>
#include <string>
#include <fstream>

using namespace std;

string metCodificador1(const string &texto,int semilla);
string MetDecodificador1(const string &textoBinario,int semilla);
string metCodificador2(const string &texto,int semilla);
string metDecodificador2(const string &textoBinario,int semilla);
string leerArchivo(const string &nombreArchivo);
void guardarArchivo(const string &nombre, const string &contenido);

string verificacionUsuario() {
    while (true) {
        string usuario, contrasena;
        cout << "Ingresa tu usuario: ";
        cin >> usuario;
        cout << "Ingresa tu contrasena: ";
        cin >> contrasena;

        // Verificación de admin
        string adminCod = leerArchivo("sudo.txt");
        if (adminCod.empty()) {
            cout << "Error: Archivo sudo.txt no encontrado o vacio\n";
            continue;
        }

        string adminDeco = metDecodificador2(adminCod, 4);
        if (adminDeco == usuario + " " + contrasena) {
            cout << "\nInicio de sesión como ADMIN.\n";
            return "admin";
        }

        // Verificación de usuarios normales
        string usuariosCod = leerArchivo("usuarios.txt");
        string usuariosDeco = metDecodificador2(usuariosCod, 4);

        string linea = "";
        for (int i = 0; i <= usuariosDeco.size(); i++) {
            char c = (i < usuariosDeco.size()) ? usuariosDeco[i] : '\n';

            if (c == '\n') {
                if (!linea.empty()) {
                    // Separar campos manualmente
                    string cedula = "", usu = "", contra = "", saldo = "";
                    int campo = 0;
                    for (int j = 0; j < linea.size(); j++) {
                        if (linea[j] == ' ') {
                            campo++;
                        } else {
                            if (campo == 0) cedula += linea[j];
                            else if (campo == 1) usu += linea[j];
                            else if (campo == 2) contra += linea[j];
                            else if (campo == 3) saldo += linea[j];
                        }
                    }

                    if (usu == usuario && contra == contrasena) {
                        cout << "\nInicio de sesión exitoso.\n";
                        return cedula;
                    }
                }
                linea = "";
            } else {
                linea += c;
            }
        }

        cout << "\nUsuario o contrasena incorrectos. Intenta de nuevo.\n\n";
    }
}



void agregarUsuario() {
    string usuarios, usuario, contrasena, codificado, decodificado, cedula;
    double saldo;

    usuarios = leerArchivo("usuarios.txt");
    if (!usuarios.empty())
        decodificado = metDecodificador2(usuarios, 4); // <-- semilla 4

    cout << "Ingresa la cedula: ";
    cin >> cedula;
    cout << "Ingresa el nuevo usuario: ";
    cin >> usuario;
    cout << "Ingresa la contrasena: ";
    cin >> contrasena;
    cout << "Ingresa el saldo inicial: ";
    cin >> saldo;

    decodificado += cedula + " " + usuario + " " + contrasena + " " + to_string(saldo) + "\n";

    codificado = metCodificador2(decodificado, 4);

    guardarArchivo("usuarios.txt", codificado);

    cout << "Usuario agregado correctamente.\n";
}

void leerSaldoYDescontar(const string &cedula) {
    string usuariosCod = leerArchivo("usuarios.txt");
    string usuariosDeco = metDecodificador2(usuariosCod, 4);

    string linea = "";
    string nuevoContenido = "";
    bool encontrado = false;

    for (int i = 0; i < usuariosDeco.size(); i++) {
        char c = usuariosDeco[i];

        if (c == '\n' || i == usuariosDeco.size() - 1) {
            if (i == usuariosDeco.size() - 1 && c != '\n') linea += c;

            if (!linea.empty()) {
                string cedulaL = "", usuario = "", contrasena = "", saldo = "";
                int campo = 0;

                for (int j = 0; j < linea.size(); j++) {
                    if (linea[j] == ' ') campo++;
                    else {
                        if (campo == 0) cedulaL += linea[j];
                        else if (campo == 1) usuario += linea[j];
                        else if (campo == 2) contrasena += linea[j];
                        else if (campo == 3) saldo += linea[j];
                    }
                }

                if (cedulaL == cedula) {
                    encontrado = true;

                    // convertir saldo a número
                    int saldoNum = 0;
                    for (int k = 0; k < saldo.size(); k++) {
                        saldoNum = saldoNum * 10 + (saldo[k] - '0');
                    }

                    if (saldoNum < 1000) {
                        cout << "\n Saldo insuficiente para cubrir el costo de la consulta.\n";
                        return;
                    }

                    saldoNum -= 1000;

                    // convertir saldoNum a string
                    string nuevoSaldoStr = "";
                    if (saldoNum == 0) nuevoSaldoStr = "0";
                    else {
                        string temp = "";
                        int aux = saldoNum;
                        while (aux > 0) {
                            temp += char((aux % 10) + '0');
                            aux /= 10;
                        }
                        for (int k = temp.size() - 1; k >= 0; k--)
                            nuevoSaldoStr += temp[k];
                    }

                    linea = cedulaL + " " + usuario + " " + contrasena + " " + nuevoSaldoStr;

                    cout << "\n Se descontaron 1000 COP por la lectura del saldo.\n";
                    cout << " Saldo actual: " << saldoNum << " COP\n";
                }

                nuevoContenido += linea + "\n";
            }
            linea = "";
        } else {
            linea += c;
        }
    }

    string codificado = metCodificador2(nuevoContenido, 4);
    guardarArchivo("usuarios.txt", codificado);
}

void retirarSaldo(const string &cedula) {
    string usuariosCod = leerArchivo("usuarios.txt");
    string usuariosDeco = metDecodificador2(usuariosCod, 4);

    string linea = "";
    string nuevoContenido = "";
    bool encontrado = false;

    for (int i = 0; i < usuariosDeco.size(); i++) {
        char c = usuariosDeco[i];

        if (c == '\n' || i == usuariosDeco.size() - 1) {
            if (i == usuariosDeco.size() - 1 && c != '\n') linea += c;

            if (!linea.empty()) {
                string cedulaL = "", usuario = "", contrasena = "", saldo = "";
                int campo = 0;

                for (int j = 0; j < linea.size(); j++) {
                    if (linea[j] == ' ') campo++;
                    else {
                        if (campo == 0) cedulaL += linea[j];
                        else if (campo == 1) usuario += linea[j];
                        else if (campo == 2) contrasena += linea[j];
                        else if (campo == 3) saldo += linea[j];
                    }
                }

                if (cedulaL == cedula) {
                    encontrado = true;

                    // convertir saldo a número
                    int saldoNum = 0;
                    for (int k = 0; k < saldo.size(); k++) {
                        saldoNum = saldoNum * 10 + (saldo[k] - '0');
                    }

                    if (saldoNum < 1000) {
                        cout << "\n Saldo insuficiente para ingresar al sistema.\n";
                        return;
                    }

                    saldoNum -= 1000;
                    cout << "\n Se descontaron 1000 COP por el costo de la transacion.\n";
                    cout << " Saldo actual antes del retiro: " << saldoNum << " COP\n";

                    int retiro;
                    cout << "¿Cuánto deseas retirar?: ";
                    cin >> retiro;

                    if (retiro > saldoNum) {
                        cout << "\n Saldo insuficiente para retirar esa cantidad.\n";
                        return;
                    }

                    saldoNum -= retiro;

                    // convertir nuevo saldo a string
                    string nuevoSaldoStr = "";
                    if (saldoNum == 0) nuevoSaldoStr = "0";
                    else {
                        string temp = "";
                        int aux = saldoNum;
                        while (aux > 0) {
                            temp += char((aux % 10) + '0');
                            aux /= 10;
                        }
                        for (int k = temp.size() - 1; k >= 0; k--)
                            nuevoSaldoStr += temp[k];
                    }

                    linea = cedulaL + " " + usuario + " " + contrasena + " " + nuevoSaldoStr;

                    cout << "\n Retiro exitoso.\n";
                    cout << " Nuevo saldo: " << saldoNum << " COP\n";
                }

                nuevoContenido += linea + "\n";
            }
            linea = "";
        } else {
            linea += c;
        }

    }

    string codificado = metCodificador2(nuevoContenido, 4);
    guardarArchivo("usuarios.txt", codificado);
}


