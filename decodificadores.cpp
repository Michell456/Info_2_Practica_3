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

    int sobrantes = textoDecodificado.size() % 8;
    if (sobrantes != 0) {
        string limpio = "";
        for (int i = 0; i < textoDecodificado.size() - sobrantes; i++) {
            limpio += textoDecodificado[i];
        }
        textoDecodificado = limpio;
    }

    // lo convierte a ASCII
    string textoASCII = "";
    for (int i = 0; i < textoDecodificado.size(); i += 8) {
        bitset<8> bits(textoDecodificado.substr(i, 8));
        textoASCII += char(bits.to_ulong());
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

        //Desplazar a la derecha
        char ultimo = grupo[semilla - 1];
        for (int j = semilla - 1; j > 0; j--) {
            grupo[j] = grupo[j - 1];
        }
        grupo[0] = ultimo;

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
