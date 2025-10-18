#include <iostream>
#include <bitset>
#include <cstring>
using namespace std;

int metCodificador1() {
    char texto[150], grupo[9], anterior[9];
    string binario = "", textoCodificado = "";
    int n, a = 0, contadorBinario = 0;

    cout << "Ingresa la cadena: ";
    cin.getline(texto, 150);

    while (true) {
        cout << "Ingrese n: ";
        cin >> n;
        if (n > 1 && n <= 8)
            break;
        cout << "Numero no valido, intentalo nuevamente" << endl;
    }

    // Convertir texto a binario
    for (int i = 0; i < strlen(texto); i++) {
        bitset<8> bits(texto[i]);
        binario += bits.to_string();
        contadorBinario += 8;
    }

    // Asegurar múltiplo de n
    while (binario.length() % n != 0) {
        binario += '0';
        contadorBinario++;
    }

    // Procesar bloques
    for (int i = 0; i < contadorBinario; i += n) {
        for (int j = 0; j < n; j++) {
            grupo[j] = binario[a];
            a++;
        }
        grupo[n] = '\0';

        if (i == 0) {
            //invertir todos los bits
            for (int j = 0; j < n; j++) {
                if (grupo[j] == '0') grupo[j] = '1';
                else grupo[j] = '0';
            }
        } else {
            //Contar 1s y 0s en el bloque anterior
            int unos = 0, ceros = 0;
            for (int j = 0; j < n; j++) {
                if (anterior[j] == '1') unos++;
                else ceros++;
            }

            if (unos == ceros) {
                // Invertir todos los bits
                for (int j = 0; j < n; j++) {
                    if (grupo[j] == '0') grupo[j] = '1';
                    else grupo[j] = '0';
                }
            } else if (ceros > unos) {
                // Invertir cada 2 bits
                for (int j = 0; j + 1 < n; j += 2) {
                    char temp = grupo[j];
                    grupo[j] = grupo[j + 1];
                    grupo[j + 1] = temp;
                }
            } else {
                // Invertir cada 3 bits
                for (int j = 0; j + 2 < n; j += 3) {
                    char temp = grupo[j];
                    grupo[j] = grupo[j + 2];
                    grupo[j + 2] = temp;
                }
            }
        }

        textoCodificado += grupo;

        for (int j = 0; j < n; j++) {
            anterior[j] = grupo[j];
        }
    }

    cout << "\nBinario original:   " << binario << endl;
    cout << "Binario codificado: " << textoCodificado << endl;

    return 0;
}

int metCodificador2() {
    char texto[150], grupo[9];
    string binario = "", textoCodificado = "";
    int n, a = 0, contadorBinario = 0;

    cout << "Ingresa la cadena: ";
    cin.getline(texto, 150);

    while (true) {
        cout << "Ingrese n: ";
        cin >> n;
        if (n > 1 && n <= 8)
            break;
        cout << "Numero no valido, intentalo nuevamente" << endl;
    }

    // Convertir texto a binario
    for (int i = 0; i < strlen(texto); i++) {
        bitset<8> bits(texto[i]);
        binario += bits.to_string();
        contadorBinario += 8;
    }

    // Asegurar múltiplo de n
    while (binario.length() % n != 0) {
        binario += '0';
        contadorBinario++;
    }

    // Procesar cada bloque de n bits
    for (int i = 0; i < contadorBinario; i += n) {
        for (int j = 0; j < n; j++) {
            grupo[j] = binario[a];
            a++;
        }
        grupo[n] = '\0';

        // Desplazar a la izquierda
        char primerCaracter = grupo[0];
        for (int j = 0; j < n - 1; j++) {
            grupo[j] = grupo[j + 1];
        }
        grupo[n - 1] = primerCaracter;

        textoCodificado += grupo;
    }

    cout << "\nBinario original:   " << binario << endl;
    cout << "Binario codificado: " << textoCodificado << endl;

    return 0;
}
