#include <iostream>
#include <bitset>
#include <cstring>
using namespace std;


string MetDecodificador1(const string &textoBinario,int semilla) {

    char grupo[9], anterior[9];
    string textoDecodificado = "";
    int a = 0;

    int longitud = textoBinario.size();

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
                else if (anterior[j] == '0') ceros++;  // ← Solo contar '0' explícitamente
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

    // Convertir de binario a texto ASCII
    string textoASCII = "";
    for (int i = 0; i < textoDecodificado.size(); i += 8) {

        if (i + 8 <= textoDecodificado.size()) {
            bitset<8> bits(textoDecodificado.substr(i, 8));
            textoASCII += char(bits.to_ulong());
        }
    }
    return textoASCII;

}

string metDecodificador2(const string &textoBinario, int semilla) {
    char grupo[9];
    string textoDecodificado = "";
    int a = 0;

    int longitud = textoBinario.size();

    // Procesar bloques de n bits
    for (int i = 0; i < longitud; i += semilla) {
        for (int j = 0; j < semilla; j++) {
            grupo[j] = textoBinario[a];
            a++;
        }
        grupo[semilla] = '\0';

        //Desplazar a la derecha 1 posición (revertir la rotacion izquierda de codificador)
        char temp[9];
        for (int j = 0; j < semilla; j++) {
            temp[(j + 1) % semilla] = grupo[j];
        }
        for (int j = 0; j < semilla; j++) {
            grupo[j] = temp[j];
        }

        textoDecodificado += grupo;
    }

    // Convertir de binario a texto ASCII
    string textoASCII = "";
    for (int i = 0; i < textoDecodificado.size(); i += 8) {
        bitset<8> bits(textoDecodificado.substr(i, 8));
        textoASCII += char(bits.to_ulong());
    }

    return textoASCII;
}
