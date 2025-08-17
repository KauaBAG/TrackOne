#include "Rastreador.hpp"
#include "RastreadorVeicular.hpp"
#include "RastreadorCarga.hpp"
#include "RastreadorPessoal.hpp"
#include "Alerta.hpp"
#include "AlertaVelocidade.hpp"
#include "AlertaBateria.hpp"
#include "AlertaZona.hpp"
#include "TipoDeComunicacao.hpp"
#include "Satelital.hpp"
#include "Gsm.hpp"
#include "Rfid.hpp"

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;

int menu(const vector<string>& array) {
    while(true) {
        cout << "\nMenu Principal\n";
        cout << "=============\n";
        for (size_t i = 0; i < array.size(); ++i) {
            cout << setw(2) << i + 1 << " - " << array[i] << endl;
        }
        cout << "Escolha uma opção: ";
        int escolha;
        cin >> escolha;
        if (escolha > 0 && escolha <= static_cast<int>(array.size())) {
            return escolha;
        } else {
            cout << "Opção inválida. Tente novamente.\n";
        }
    }
}

int main() {
    return 0; 
}