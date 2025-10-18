#include <iostream>
#include <bitset>
#include <cstring>
using namespace std;

int main() {
    char texto[150];
    string binario = "", textoCodificado = "";
    int n, contadorBinario = 0;

    cout << "Ingresa la cadena: ";
    cin.getline(texto, 150);

    // Validar n
    while (true) {
        cout << "Ingrese n: ";
        cin >> n;

        if (n > 1 && n <= 8)
            break;
        cout << "Numero no valido, intentalo nuevamente" << endl;
    }

    // Convertir el texto a binario
    for (int i = 0; i < strlen(texto); i++) {
        bitset<8> bits(texto[i]);
        binario += bits.to_string();
        contadorBinario += 8;
    }

    // Asegurar que la cadena sea múltiplo de n
    while (binario.length() % n != 0) {
        binario += '0';
        contadorBinario++;
    }

    // Procesar los bloques
    string anterior = "";
    for (int i = 0; i < contadorBinario; i += n) {
        string grupo = binario.substr(i, n);

        if (i == 0) {
            // Primer bloque → invertir todos los bits
            for (char &c : grupo) {
                if (c == '0') c = '1';
                else c = '0';
            }
        } else {

            // Contar 1s y 0s en el bloque anterior
            int unos = 0, ceros = 0;
            for (char c : anterior) {
                if (c == '1') unos++;
                else ceros++;
            }

            if (unos == ceros) {

                // Invertir todos los bits
                for (char &c : grupo) {
                    if (c == '0') {
                        c = '1';
                    }
                    else c = '0';
                }

            } else if (ceros > unos) {

                // Invertir cada 2 bits
                for (int j = 0; j + 1 < n; j += 2){
                    swap(grupo[j], grupo[j + 1]);
                }

            } else {

                // Invertir cada 3 bits
                for (int j = 0; j + 2 < n; j += 3){
                    swap(grupo[j], grupo[j + 2]);
                }
            }
        }

        textoCodificado += grupo;
        anterior = grupo;
    }

    // Mostrar resultado final
    cout << "\nBinario original:  " << binario << endl;
    cout << "Binario codificado: " << textoCodificado << endl;

    return 0;
}
