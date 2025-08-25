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

struct RastreadorBase {
    unsigned int id;
    string marca;
    string modelo;
    EstadoDoRastreador estado;
    Data dataDeAtivacao;
};

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
        cin.ignore();
        if (escolha > 0 && escolha <= static_cast<int>(array.size())) {
            return escolha;
        } else {
            cout << "Opção inválida. Tente novamente.\n";
        }
    }
}

TipoDeComunicacao* criarComunicacao() {
    int tipoDeCom = menu({"Gsm","Rfid", "Satelital"}, "dos Tipos de comunicacao") - 1;
    
    switch (tipoDeCom) {
        case 0: return criarComunicacaoGsm();
        case 1: return criarComunicacaoRfid();
        case 2: return criarComunicacaoSatelital();
        default: return nullptr;
    }
}

RastreadorBase lerDadosBase() {
    unsigned int id;
    cout << "Digite o ID do rastreador: ";
    cin >> id;
    cin.ignore();

    string marca = "";
    cout << "\nDigite a marca do rastreador: ";
    getline(cin, marca);
    
    string modelo = "";
    cout << "Digite o modelo do rastreador: ";
    getline(cin, modelo);
    
    EstadoDoRastreador estado = ATIVO;
    Data dataDeAtivacao = lerData("\nQual a data de ativação");
    
    return {id, marca, modelo, estado, dataDeAtivacao};
}

TipoDeComunicacao* criarComunicacaoGsm() {
    int tipoDeBanda = menu({"2G", "4G", "5G"}, "dos Tipos de Banda") - 1;
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

    return new Gsm(banda, fallback);
}

TipoDeComunicacao* criarComunicacaoRfid() {
    float freq;
    cout << "Digite a frequencia da comunicação: ";
    cin >> freq;
    string type;
    cout << "Digite o tipo de frequencia: ";
    cin >> type;
    return new Rfid(freq, type);
}

TipoDeComunicacao* criarComunicacaoSatelital() {
    int satid;
    cout << "Digite o Id da comunicação satelital: ";
    cin >> satid;
    return new Satelital(satid);
}

void criarRastreadorVeicular(const RastreadorBase& base, TipoDeComunicacao* comunicacao) {
    string tipoDeCarro, marcaDoCarro, modeloDoCarro;
    cout << "Qual o tipo de carro: ";
    cin >> tipoDeCarro;
    cout << "Qual a marca do carro: ";
    cin >> marcaDoCarro;
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
    getline(cin, localDeEmissao);
    
    TipoDePlaca tipo = (TipoDePlaca)(menu({"PARTICULAR", "ESPECIAL", "COLECAO", "DIPLOMATICO", "OFICIAIS", "COMERCIAIS"}, "dos Tipos de Placa")-1);
    
    Placa placa(identificador, localDeEmissao, tipo);
    
    RastreadorVeicular rastr(base.id, base.marca, base.modelo, comunicacao, 
                           base.estado, base.dataDeAtivacao, tipoDeCarro, 
                           marcaDoCarro, modeloDoCarro, placa, temCamera);
    cout << "\n" << rastr.getString() << "\n";
    //SUBSTITUIR POR FUNCAO QUE CADASTRA RASTREADOR NA LISTA
}

void criarRastreadorCarga(const RastreadorBase& base, TipoDeComunicacao* comunicacao) {
    string tipoCarga, remetente, destinatario;
    cin.ignore();
    cout << "Qual o tipo de carga: ";
    getline(cin, tipoCarga);
    cout << "Qual o remetente da carga: ";
    getline(cin, remetente);
    cout << "Qual o destinatario da carga: ";
    getline(cin, destinatario);
    
    bool fragil;
    cout << "\nÉ fragil?  \n0. Nao \n1. Sim\n Resposta: ";
    int i = 0;
    cin >> i;
    fragil = (i == 1);
    
    RastreadorCarga rastr(base.id, base.marca, base.modelo, comunicacao, 
                        base.estado, base.dataDeAtivacao, tipoCarga, 
                        remetente, destinatario, fragil);
    cout << "\n" << rastr.getString() << "\n";
    //SUBSTITUIR POR FUNCAO QUE CADASTRA RASTREADOR NA LISTA
}

void criarRastreadorPessoal(const RastreadorBase& base, TipoDeComunicacao* comunicacao) {
    string nome, telefone, documento;
    cin.ignore();
    cout << "Digite seu nome: ";
    getline(cin, nome);
    cout << "Digite seu telefone: ";
    getline(cin, telefone);
    cout << "Digite seu documento: ";
    getline(cin, documento);
    
    RastreadorPessoal rastr(base.id, base.marca, base.modelo, comunicacao, 
                          base.estado, base.dataDeAtivacao, nome, telefone, documento);
    cout << "\n" << rastr.getString() << "\n";
    //SUBSTITUIR POR FUNCAO QUE CADASTRA RASTREADOR NA LISTA
}

int main() {
    while(true) {
        int escolhaPrincipal = menu({"Gerenciar Rastreados", "Gerenciar Alertas", "Sair"}, "principal");
        
        switch (escolhaPrincipal) {
        case 1: {
            bool voltarAoMenuPrincipal = false;
    
            while (!voltarAoMenuPrincipal) {
            int escolhaRastreados = menu({"Cadastrar Rastreador", "Listar Rastreadores", "Exibir Rastreador", 
                                        "Alterar Rastreador", "Remover Rastreador", "Exibir Relatório", "Voltar"}, "dos Rastreados");
            
            switch (escolhaRastreados) {
                case 1: {
                    RastreadorBase base = lerDadosBase();    
                    short tipoDeRastreador = menu({"Veicular", "Carga", "Pessoal"}, "dos Tipos de Rastreador") - 1;                        
                    TipoDeComunicacao* comunicacao = criarComunicacao();
                    
                    switch (tipoDeRastreador) {
                        case 0: criarRastreadorVeicular(base, comunicacao); break;
                        case 1: criarRastreadorCarga(base, comunicacao); break;
                        case 2: criarRastreadorPessoal(base, comunicacao); break;
                    }
                
                    delete comunicacao;
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
                case 7: {
                    cout << "Voltando ao menu principal...\n";
                    voltarAoMenuPrincipal = true; // Sinaliza para sair do loop
                    break;
                }
                default: {
                    cout << "Opção inválida. Tente novamente.\n";
                    break; 
                }
            }
        }
        break; // Sai do case 1 do menu externo
    }
    
        case 2: {
            cout << "Gerenciar Alertas\n";
            int escolhaAlertas = menu({"Cadastrar Alerta", "Listar Alertas", "Exibir Alerta", 
                                          "Alterar Alerta", "Remover Alerta", "Exibir Relatório", "Voltar"}, "Dos Alertas");
            switch (escolhaAlertas) {
                case 1: {
                    cout << "Cadastrar Alerta\n";

                    
                    unsigned int tipoDeAlerta = menu({"Velocidade", "Bateria", "Zona"}, "dos Tipos de Alerta");

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
