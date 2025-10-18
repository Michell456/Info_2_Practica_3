#include <iostream>
#include <bitset>
#include <cstring>
using namespace std;

int MetDecodificador1() {

    char textoBinario[150], grupo[9], anterior[9];
    string textoDecodificado = "";
    int semilla, a = 0;

    cout << "Ingresa el texto binario a desencriptar: ";
    cin.getline(textoBinario, 150);

    // Pedir semilla válida
    while (true) {
        cout << "Ingrese la semilla: ";
        cin >> semilla;
        if (semilla > 1 && semilla <= 8)
            break;
        cout << "Semilla no válida, intentalo nuevamente" << endl;
    }

    int longitud = strlen(textoBinario);

    // Procesar bloques
    for (int i = 0; i < longitud; i += semilla) {
        for (int j = 0; j < semilla; j++) {
            grupo[j] = textoBinario[a];
            a++;
        }
        grupo[semilla] = '\0';

        if (i == 0) {
            // Primer grupo → invertir todos los bits
            for (int j = 0; j < semilla; j++) {
                if (grupo[j] == '0') grupo[j] = '1';
                else grupo[j] = '0';
            }
        } else {
            // Contar 1s y 0s en el bloque anterior (YA DECODIFICADO)
            int unos = 0, ceros = 0;
            for (int j = 0; j < semilla; j++) {
                if (anterior[j] == '1') unos++;
                else ceros++;
            }

            if (unos == ceros) {
                // Invertir todos los bits
                for (int j = 0; j < semilla; j++) {
                    if (grupo[j] == '0') grupo[j] = '1';
                    else grupo[j] = '0';
                }
            } else if (ceros > unos) {
                // Intercambiar cada 2 bits
                for (int j = 0; j + 1 < semilla; j += 2) {
                    char temp = grupo[j];
                    grupo[j] = grupo[j + 1];
                    grupo[j + 1] = temp;
                }
            } else {
                // Intercambiar cada 3 bits
                for (int j = 0; j + 2 < semilla; j += 3) {
                    char temp = grupo[j];
                    grupo[j] = grupo[j + 2];
                    grupo[j + 2] = temp;
                }
            }
        }

        // Agregar grupo decodificado al resultado
        textoDecodificado += grupo;

        // Guardar bloque para el siguiente ciclo
        for (int j = 0; j < semilla; j++) {
            anterior[j] = grupo[j];
        }
    }

    cout << "\nBinario decodificado: " << textoDecodificado << endl;

    int sobrantes = textoDecodificado.size() % 8;
    if (sobrantes != 0) {
        string limpio = "";
        for (int i = 0; i < textoDecodificado.size() - sobrantes; i++) {
            limpio += textoDecodificado[i];
        }
        textoDecodificado = limpio;
    }

    // Convertir a texto ASCII (cada 8 bits)
    cout << "Texto original: ";
    for (int i = 0; i < textoDecodificado.size(); i += 8) {
        bitset<8> bits(textoDecodificado.substr(i, 8));
        cout << char(bits.to_ulong());
    }
    cout << endl;

    return 0;
}

int metDecodificador2() {
    char textoBinario[150], grupo[9];
    string textoDecodificado = "";
    int semilla, a = 0;

    cout << "Ingresa el texto binario a desencriptar: ";
    cin.getline(textoBinario, 150);

    // Pedir semilla válida
    while (true) {
        cout << "Ingrese la semilla: ";
        cin >> semilla;
        if (semilla > 1 && semilla <= 8)
            break;
        cout << "Semilla no válida, intentalo nuevamente" << endl;
    }

    int longitud = strlen(textoBinario);

    // Procesar bloques de n bits
    for (int i = 0; i < longitud; i += semilla) {
        for (int j = 0; j < semilla; j++) {
            grupo[j] = textoBinario[a];
            a++;
        }
        grupo[semilla] = '\0';

        //Desplazar a la derecha
        char ultimo = grupo[semilla - 1];
        for (int j = semilla - 1; j > 0; j--) {
            grupo[j] = grupo[j - 1];
        }
        grupo[0] = ultimo;

        textoDecodificado += grupo;
    }

    cout << "\nBinario decodificado: " << textoDecodificado << endl;

    // Convertir de binario a texto ASCII
    cout << "Texto original: ";
    for (int i = 0; i < textoDecodificado.size(); i += 8) {
        string byte = textoDecodificado.substr(i, 8);
        bitset<8> bits(byte);
        cout << char(bits.to_ulong());
    }
    cout << endl;

    return 0;
}
