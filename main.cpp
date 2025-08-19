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

Data lerData(string mensagem) {
    short dia, mes;
    int ano;
    cout << mensagem << " (dia mes ano): ";
    cin >> dia >> mes >> ano;
    return Data(dia, mes, ano);
}

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
            vector<string> opcoesRastreados = {"Cadastrar Rastreador", "Listar Rastreadores", "Exibir Rastreador", 
                                             "Alterar Rastreador", "Remover Rastreador", "Exibir Relatório", "Voltar"};
            int escolhaRastreados = menu(opcoesRastreados, "dos Rastreados");
            
            switch (escolhaRastreados) {
            case 1: {
                cout << "\nCadastrar Rastreador\n";

                unsigned int id;
                cout << "Digite o ID do rastreador: ";
                cin >> id;

                short tipoDeRastreador;
                vector<string> tipos = {"Veicular", "Carga", "Pessoal"};
                tipoDeRastreador = menu(tipos, "dos Tipos de Rastreador")-1;
                
                string marca = "";
                cout << "\nDigite a marca do rastreador: ";
                cin.ignore(); // Limpar o buffer do cin
                getline(cin, marca);
                
                string modelo = "";
                cout << "Digite o modelo do rastreador: ";
                getline(cin, modelo);
                
                vector<string> tiposa = {"Gsm", "Rfid", "Satelital"};
                TipoDeComunicacao* comunicacao = nullptr;

                int tipoDeCom = menu(tiposa, "dos Tipos de comunicacao") - 1;
                
            
                switch (tipoDeCom) {
                case 0: {
                    vector<string> bandas = {"2G", "4G", "5G"};
                    int tipoDeBanda = menu(bandas, "dos Tipos de Banda") - 1;

                    Banda banda;
                    switch (tipoDeBanda) {
                        case 0: banda = _2G; break;
                        case 1: banda = _4G; break;
                        case 2: banda = _5G; break;
                        default: banda = _2G;
                    }

                    bool fallback;
                    cout << "\nPossui fallback?  \n0. Nao \n1. Sim\n Resposta: ";
                    int i = 0;
                    cin >> i;
                    fallback = (i == 1);

                    comunicacao = new Gsm(banda, fallback);
                    break;
                }
                case 1: {
                    float freq;
                    cout << "Digite a frequencia da comunicação: ";
                    cin >> freq;
                    string type;
                    cout << "Digite o tipo de frequencia: ";
                    cin >> type;
                    comunicacao = new Rfid(freq, type);
                    break;
                }
                case 2: {
                    int satid;
                    cout << "Digite o Id da comunicação satelital: ";
                    cin >> satid;
                    comunicacao = new Satelital(satid);
                    break;
                }
        }

                EstadoDoRastreador estado = ATIVO;
                
                Data dataDeAtivacao = lerData("\nQual a data de ativação");
                
                switch (tipoDeRastreador) {
                    case 0: {
                        string tipoDeCarro;
                        cout << "Qual o tipo de carro: ";
                        cin >> tipoDeCarro;
                        
                        string marcaDoCarro;
                        cout << "Qual a marca do carro: ";
                        cin >> marcaDoCarro;
                        
                        string modeloDoCarro;
                        cout << "Qual o modelo do carro: ";
                        cin >> modeloDoCarro;
                        
                        bool temCamera;
                        cout << "\nPossui Camera?  \n0. Nao \n1. Sim\n Resposta: ";
                        int i = 0;
                        cin >> i;
                        temCamera = (i == 1);
                        
                        string identificador, localDeEmissao;
                        cout << "\nDigite os digitos da placa: ";
                        cin >> identificador;
                        cin.ignore();
                        cout << "Digite o local de emissão da placa: ";
                        getline(cin,localDeEmissao);
                        vector<string> TiposPlaca = {"PARTICULAR", "ESPECIAL", "COLECAO", "DIPLOMATICO", "OFICIAIS", "COMERCIAIS"};
                        TipoDePlaca tipo = (TipoDePlaca)(menu(TiposPlaca, "dos Tipos de Placa")-1);
                        
                        Placa placa(identificador, localDeEmissao, tipo);
                        
                        
                        RastreadorVeicular rastr(id, marca, modelo, comunicacao, estado, dataDeAtivacao, tipoDeCarro, marcaDoCarro, modeloDoCarro, placa, temCamera);
                        cout << "\n" << rastr.getString() << "\n";
                        break;
                    }
                    case 1: {
                        string tipoCarga, remetente, destinatario;
                        cin.ignore();
                        cout << "Qual o tipo de carga: ";
                        getline(cin,tipoCarga);
                        cout << "Qual o remetente da carga: ";
                        getline(cin,remetente);
                        cout << "Qual o destinatario da carga: ";
                        getline(cin,destinatario);
                        
                        bool fragil;
                        cout << "\nÉ fragil?  \n0. Nao \n1. Sim\n Resposta: ";
                        int i = 0;
                        cin >> i;
                        fragil = (i == 1);
                        
                        RastreadorCarga rastr(id, marca, modelo, comunicacao, estado, dataDeAtivacao, tipoCarga, remetente, destinatario, fragil);
                        cout << "\n" << rastr.getString() << "\n";
                        
                        break;
                    }
                    case 2: {
                        cin.ignore();
                        string nome, telefone, documento;
                        cout << "Digite seu nome: ";
                        getline(cin, nome);
                        cout << "Digite seu telefone: ";
                        getline(cin, telefone);
                        cout << "Digite seu documento: ";
                        getline(cin, documento);
                        RastreadorPessoal rastr(id, marca, modelo, comunicacao, estado, dataDeAtivacao, nome, telefone, documento);
                        cout << "\n" << rastr.getString() << "\n";
                        break;
                    }
                }
                //Rastreador rastreado(id, tipoDeRastreador, marca, modelo, comunicacao, estado, dataDeAtivacao);
                
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
                    unsigned int tipoDeAlerta = menu(tipos, "dos Tipos de Alerta");

                    unsigned int subid;
                    cout << "Digite o subid do alerta: ";
                    cin >> subid;
                    
                    short dia, mes;
                    int ano;
                    cout << "Digite a data de emissão do alerta (dia mes ano): ";
                    cin >> dia >> mes >> ano;
                    Data dataDeEmissao(dia, mes, ano);

                    string localizacao;
                    cout << "Digite a localização do alerta: ";
                    cin.ignore(); // Limpar o buffer do cin
                    getline(cin, localizacao);

                    Alerta alerta(tipoDeAlerta, subid, dataDeEmissao, localizacao);
                    cout << alerta.getString();
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
