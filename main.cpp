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

int menu(const vector<string>& array, string nome) {
    while(true) {
        cout << "\nMenu " << nome << "\n";
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
    while(true) {
        vector<string> opcoesPrincipais = {"Gerenciar Rastreados", "Gerenciar Alertas", "Sair"};
        int escolhaPrincipal = menu(opcoesPrincipais, "principal");
        
        switch (escolhaPrincipal) {
        case 1: {
            cout << "Gerenciar Rastreados\n";
            vector<string> opcoesRastreados = {"Cadastrar Rastreador", "Listar Rastreadores", "Exibir Rastreador", 
                                             "Alterar Rastreador", "Remover Rastreador", "Exibir Relatório", "Voltar"};
            int escolhaRastreados = menu(opcoesRastreados, "dos Rastreados");
            
            switch (escolhaRastreados) {
            case 1: {
                cout << "Cadastrar Rastreador\n";

                unsigned int id;
                cout << "Digite o ID do rastreador: ";
                cin >> id;

                short tipoDeRastreador;
                vector<string> tipos = {"Veicular", "Carga", "Pessoal"};
                tipoDeRastreador = menu(tipos, "dos Tipos de Rastreador");
                
                string marca = "";
                cout << "Digite a marca do rastreador: ";
                cin.ignore(); // Limpar o buffer do cin
                getline(cin, marca);
                string modelo = "";
                cout << "Digite o modelo do rastreador: ";
                getline(cin, modelo);
                //TipoDeComunicacao *comunicacao = NULL;
                //EstadoDoRastreador estado = INATIVO;
                //Data ativacao = Data();
                //Rastreador rastreado(id, tipoDeRastreador, marca, modelo, comunicacao, estado, ativacao);
                break;
                }    
            case 2: {
                cout << "Listar Rastreadores\n";
                // Código para listar rastreadores
                break;
                }
            case 3: {
                cout << "Exibir Rastreador\n";
                // Código para exibir rastreador
                break;
                }
            case 4: {
                cout << "Alterar Rastreador\n";
                // Código para alterar rastreador
                break;
                }
            case 5: {
                cout << "Remover Rastreador\n";
                // Código para remover rastreador
                break;
                }
            case 6: {
                cout << "Exibir Relatório\n";
                // Código para exibir relatório
                break;
                }
            case 7:
                break; // Voltar ao menu principal
            default: {
                cout << "Opção inválida. Tente novamente.\n";
                break; 
                }
            } break;
        }

        case 2: {
            cout << "Gerenciar Alertas\n";
            vector<string> opcoesAlertas = {"Cadastrar Alerta", "Listar Alertas", "Exibir Alerta", 
                                          "Alterar Alerta", "Remover Alerta", "Exibir Relatório", "Voltar"};
            int escolhaAlertas = menu(opcoesAlertas, "Dos Alertas");
            switch (escolhaAlertas) {
                case 1: {
                    cout << "Cadastrar Alerta\n";

                    vector<string> tipos = {"Velocidade", "Bateria", "Zona"};
                    short int tipoDeAlerta = menu(tipos, "dos Tipos de Alerta");

                    unsigned int subid;
                    cout << "Digite o subid do alerta: ";
                    cin >> subid;

                    //Data dataDeEmissao;

                    string localizacao;
                    cout << "Digite a localização do alerta: ";
                    cin.ignore(); // Limpar o buffer do cin
                    getline(cin, localizacao);
                    break;
                }
                case 2: {
                    cout << "Listar Alertas\n";
                    // Código para listar alertas
                    break;
                }
                case 3: {
                    cout << "Exibir Alerta\n";
                    // Código para exibir alerta
                    break;
                }
                case 4: {
                    cout << "Alterar Alerta\n";
                    // Código para alterar alerta
                    break;
                }
                case 5: {
                    cout << "Remover Alerta\n";
                    // Código para remover alerta
                    break;
                }
                case 6: {
                    cout << "Exibir Relatório\n";
                    // Código para exibir relatório de alertas
                    break;
                }
                case 7:
                    break; // Voltar ao menu principal
                default:
                    cout << "Opção inválida. Tente novamente.\n";
                    break;
                }
            break;    
            }    
        case 3:
            return 0; // Sair do programa
        default:
            cout << "Opção inválida. Tente novamente.\n";
            break;
        }
    }
}
