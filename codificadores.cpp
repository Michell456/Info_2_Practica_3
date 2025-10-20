#include <iostream>
#include <bitset>
#include <cstring>
using namespace std;

string metCodificador1(const string &texto,int semilla) {
    char grupo[9], anterior[9];
    string binario = "", textoCodificado = "";
    int a = 0, contadorBinario = 0;

    // Convertir texto a binario
    for (int i = 0; i < texto.size(); i++) {
        bitset<8> bits(texto[i]);
        binario += bits.to_string();
        contadorBinario += 8;
    }

    // Asegurar múltiplo de semilla
    while (binario.length() % semilla != 0) {
        binario += '0';
        contadorBinario++;
    }

    // Procesar bloques
    for (int i = 0; i < contadorBinario; i += semilla) {
        for (int j = 0; j < semilla; j++) {
            grupo[j] = binario[a];
            a++;
        }
        grupo[semilla] = '\0';

        if (i == 0) {
            //invertir todos los bits
            for (int j = 0; j < semilla; j++) {
                if (grupo[j] == '0') grupo[j] = '1';
                else grupo[j] = '0';
            }
        } else {
            //Contar 1s y 0s en el bloque anterior
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
                // Invertir cada 2 bits
                for (int j = 0; j + 1 < semilla; j += 2) {
                    char temp = grupo[j];
                    grupo[j] = grupo[j + 1];
                    grupo[j + 1] = temp;
                }
            } else {
                // Invertir cada 3 bits
                for (int j = 0; j + 2 < semilla; j += 3) {
                    char temp = grupo[j];
                    grupo[j] = grupo[j + 2];
                    grupo[j + 2] = temp;
                }
            }
        }

        textoCodificado += grupo;

        for (int j = 0; j < semilla; j++) {
            anterior[j] = grupo[j];
        }
    }

    return textoCodificado;
}

string metCodificador2(const string &texto,int semilla) {
    char grupo[9];
    string binario = "", textoCodificado = "";
    int a = 0, contadorBinario = 0;

    // Convertir texto a binario
    for (int i = 0; i < texto.size(); i++) {
        bitset<8> bits(texto[i]);
        binario += bits.to_string();
        contadorBinario += 8;
    }

    // Asegurar múltiplo de semilla
    while (binario.length() % semilla != 0) {
        binario += '0';
        contadorBinario++;
    }

    // Procesar cada bloque de n(semilla) bits
    for (int i = 0; i < contadorBinario; i += semilla) {
        for (int j = 0; j < semilla; j++) {
            grupo[j] = binario[a];
            a++;
        }
        grupo[semilla] = '\0';

        // Desplazar a la izquierda
        char primerCaracter = grupo[0];
        for (int j = 0; j < semilla - 1; j++) {
            grupo[j] = grupo[j + 1];
        }
        grupo[semilla - 1] = primerCaracter;

        textoCodificado += grupo;
    }

    return textoCodificado;
}
