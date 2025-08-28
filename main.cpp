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
#include "Programa.hpp"

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <limits>

using namespace std;

Programa programa;

struct RastreadorBase {
    unsigned int id;
    string marca;
    string modelo;
    EstadoDoRastreador estado;
    Data dataDeAtivacao;
};

// Função para limpar o buffer de entrada
void limparBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Função para entrada segura de inteiros
int lerInteiro(const string& mensagem) {
    int valor;
    while (true) {
        cout << mensagem;
        if (cin >> valor) {
            limparBuffer();
            return valor;
        } else {
            cout << "Entrada inválida. Digite um número inteiro.\n";
            limparBuffer();
        }
    }
}

Data lerData(string mensagem) {
    short dia, mes;
    int ano;
    cout << mensagem << " (dia mes ano): ";
    
    cin >> dia >> mes >> ano;
      
    limparBuffer();
    
    return Data(dia, mes, ano);
}

int menu(const vector<string>& array, string nome) {
    while(true) {
        cout << "\n" << nome << "\n";
        string equals = "=";
        cout << setfill('=') << setw(nome.size()+2) << "\n";
        for (size_t i = 0; i < array.size(); ++i) {
            cout << setfill(' ') <<setw(2) << i + 1 << " - " << array[i] << endl;
        }
        
        int escolha = lerInteiro("Escolha uma opção: ");
        
        if (escolha > 0 && escolha <= static_cast<int>(array.size())) {
            return escolha;
        } else {
            cout << "Opção inválida. Tente novamente.\n";
        }
    }
}

TipoDeComunicacao* criarComunicacaoGsm() {
    cout << "\n=== Criando Comunicação GSM ===\n";
    int tipoDeBanda = menu({"2G", "4G", "5G"}, "Tipos de Banda") - 1;
    Banda banda;
    switch (tipoDeBanda) {
        case 0: banda = _2G; break;
        case 1: banda = _4G; break;
        case 2: banda = _5G; break;
        default: banda = _2G;
    }

    bool fallback;
    cout << "\nPossui fallback?  \n0. Nao \n1. Sim\n";
    int i = lerInteiro("Resposta: ");
    fallback = (i == 1);

    TipoDeComunicacao* gsm = new Gsm(banda, fallback);
    
    return gsm;
}

TipoDeComunicacao* criarComunicacaoRfid() {
    cout << "\n=== Criando Comunicação RFID ===\n";
    float freq;
    cout << "Digite a frequencia da comunicação: ";
    while (!(cin >> freq) || freq <= 0) {
        cout << "Frequência inválida. Digite novamente: ";
        limparBuffer();
    }
    limparBuffer();
    
    string type;
    cout << "Digite o tipo de frequencia: ";
    getline(cin, type);
    
    TipoDeComunicacao* rfid = new Rfid(freq, type);
    
    return rfid;
}

TipoDeComunicacao* criarComunicacaoSatelital() {
    cout << "\n=== Criando Comunicação Satelital ===\n";
    int satid = lerInteiro("Digite o Id da comunicação satelital: ");
    
    TipoDeComunicacao* satelital = new Satelital(satid);
    
    return satelital;
}

TipoDeComunicacao* criarComunicacao() {
    int tipoDeCom = menu({"Gsm","Rfid", "Satelital"}, "Tipos de comunicacao") - 1;
    
    switch (tipoDeCom) {
        case 0: return criarComunicacaoGsm();
        case 1: return criarComunicacaoRfid();
        case 2: return criarComunicacaoSatelital();
        default: return nullptr;
    }
}

RastreadorBase lerDadosBase() {
    cout << "\n=== Dados Base do Rastreador ===\n";
    
    unsigned int id = static_cast<unsigned int>(lerInteiro("Digite o ID do rastreador: "));

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

void criarRastreadorVeicular(const RastreadorBase& base, TipoDeComunicacao* comunicacao) {
    cout << "\n=== Criando Rastreador Veicular ===\n";
    
    string tipoDeCarro, marcaDoCarro, modeloDoCarro;
    cout << "Qual o tipo de carro: ";
    cin >> tipoDeCarro;
    cout << "Qual a marca do carro: ";
    cin >> marcaDoCarro;
    cout << "Qual o modelo do carro: ";
    cin >> modeloDoCarro;
    limparBuffer();
    
    bool temCamera;
    cout << "\nPossui Camera?  \n0. Nao \n1. Sim\n";
    int i = lerInteiro("Resposta: ");
    temCamera = (i == 1);
    
    string identificador, localDeEmissao;
    cout << "\nDigite os digitos da placa: ";
    cin >> identificador;
    limparBuffer();
    cout << "Digite o local de emissão da placa: ";
    getline(cin, localDeEmissao);
    
    TipoDePlaca tipo = (TipoDePlaca)(menu({"PARTICULAR", "ESPECIAL", "COLECAO", "DIPLOMATICO", "OFICIAIS", "COMERCIAIS"}, "Tipos de Placa")-1);
    
    Placa placa(identificador, localDeEmissao, tipo);

    RastreadorVeicular rastr(base.id, base.marca, base.modelo, comunicacao, 
                               base.estado, base.dataDeAtivacao, tipoDeCarro, 
                               marcaDoCarro, modeloDoCarro, placa, temCamera);
    cout << "\n" << rastr.getString() << "\n";
    
    programa.InserirRastreador(rastr);
}

void criarRastreadorCarga(const RastreadorBase& base, TipoDeComunicacao* comunicacao) {
    cout << "\n=== Criando Rastreador de Carga ===\n";
    
    string tipoCarga, remetente, destinatario;
    cout << "Qual o tipo de carga: ";
    getline(cin, tipoCarga);
    cout << "Qual o remetente da carga: ";
    getline(cin, remetente);
    cout << "Qual o destinatario da carga: ";
    getline(cin, destinatario);
    
    bool fragil;
    cout << "\nÉ fragil?  \n0. Nao \n1. Sim\n";
    int i = lerInteiro("Resposta: ");
    fragil = (i == 1);
    
    RastreadorCarga rastr = RastreadorCarga(base.id, base.marca, base.modelo, comunicacao, 
                        base.estado, base.dataDeAtivacao, tipoCarga, 
                        remetente, destinatario, fragil);
    cout << "\n" << rastr.getString() << "\n";
        
    programa.InserirRastreador(rastr);
    cout << "Rastreador inserido com sucesso!\n";
}

void criarRastreadorPessoal(const RastreadorBase& base, TipoDeComunicacao* comunicacao) {
    cout << "\n=== Criando Rastreador Pessoal ===\n";
    
    string nome, telefone, documento;
    cout << "Digite seu nome: ";
    getline(cin, nome);
    cout << "Digite seu telefone: ";
    getline(cin, telefone);
    cout << "Digite seu documento: ";
    getline(cin, documento);
    
    RastreadorPessoal rastr(base.id, base.marca, base.modelo, comunicacao, 
                              base.estado, base.dataDeAtivacao, nome, telefone, documento);
    cout << "\n" << rastr.getString() << "\n";
    
    programa.InserirRastreador(rastr);
}

int main() {
    cout << "=== Sistema de Rastreamento Iniciado ===\n";
    
    while(true) {
        int escolhaPrincipal = menu({"Gerenciar Rastreados", "Gerenciar Alertas", "Sair"}, "MENU PRINCIPAL");
        
        switch (escolhaPrincipal) {
        case 1: {
            bool voltarAoMenuPrincipal = false;
    
            while (!voltarAoMenuPrincipal) {
                int escolhaRastreados = menu({"Cadastrar Rastreador", "Listar Rastreadores", "Exibir Rastreador", 
                                            "Alterar Rastreador", "Remover Rastreador", "Exibir Relatório", "Voltar"}, "GERENCIAR RASTREADOS");
                
                switch (escolhaRastreados) {
                    case 1: {
                        cout << "\n=== CADASTRO DE RASTREADOR ===\n";
                        
                        RastreadorBase base = lerDadosBase();    
                        short tipoDeRastreador = menu({"Veicular", "Carga", "Pessoal"}, "Tipos de Rastreador") - 1;                        
                        
                        cout << "Criando comunicação...\n";
                        TipoDeComunicacao* comunicacao = criarComunicacao();
                        
                        switch (tipoDeRastreador) {
                            case 0: criarRastreadorVeicular(base, comunicacao); break;
                            case 1: criarRastreadorCarga(base, comunicacao); break;
                            case 2: criarRastreadorPessoal(base, comunicacao); break;
                            default:
                                cout << "Tipo de rastreador inválido.\n";
                                delete comunicacao; // Limpar memória se não foi usado
                                break;
                        }
                        
                        cout << "\nOperação de cadastro concluída.\n";
                        break;
                    }      
    
                    case 2: {
                        cout << "\n=== LISTAR RASTREADORES ===\n";
                        
                        cout << programa.ListarRastreadores();
                        cout << "\n# Pressione qualquer tecla para continuar";
                        getchar();
                        
                        break;
                    }
                    case 3: {
                        cout << "Exibir Rastreador\n";
                        unsigned int id;
                        cin >> id;
                        Rastreador* selected = programa.getRastreador(id);
                        if(selected==nullptr) break;
                        cout << "\n" << selected->getString() << "\n";
                        break;
                    }
                    case 4: {
                        unsigned int id;
                        cout << "Digite o Id do rastreador que deseja alterar: ";
                        cin >> id;
                        Rastreador* rastr = programa.getRastreador(id);
                        cout << rastr->getString();
                        
                        int ParamAlterar = menu({"Marca","Modelo","Estado","Tipo de Rastreador", "Tipo de comunicacao"}, "Parametros de Atualizaçao");
                        
                        switch(ParamAlterar) {
                            case 1: {string marca; cin >>marca ; rastr->setMarca(marca); break;}
                            case 2: {string modelo; cin >> modelo; rastr->setModelo(modelo); break;}
                            case 3: {int estado = menu({"ATIVO", "INATIVO", "MANUTENCAO", "BLOQUEADO"}, "Estados Do Rastreador"); 
                                    rastr->setEstado((EstadoDoRastreador)estado); break;}
                            //case 2: {cin >> string Marca; rastr->setModelo();}
                            //case 3: {cin >> string Marca; rastr->setEstado();}
                        };
                        break;
                    }
                    case 5: {
                        cout << "Remover Rastreador\n";
                        unsigned int id;
                        cout << "Digite o Id do rastreador que deseja excluir: ";
                        cin >> id;
                        
                        programa.RemoverRastreador(id);
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
                    } // default
                } // switch
            } //while
            break; // Sai do case 1 do menu externo
        }
    
        case 2: {
            cout << "Gerenciar Alertas\n";
            int escolhaAlertas = menu({"Cadastrar Alerta", "Listar Alertas", "Exibir Alerta", 
                                          "Alterar Alerta", "Remover Alerta", "Exibir Relatório", "Voltar"}, "GERENCIAR ALERTAS");
            switch (escolhaAlertas) {
                case 1: {
                    cout << "Cadastrar Alerta\n";
                    
                    unsigned int tipoDeAlerta = menu({"Velocidade", "Bateria", "Zona"}, "Tipos de Alerta");
                    
                    unsigned int subid = static_cast<unsigned int>(lerInteiro("Digite o subid do alerta: "));
                    
                    Data dataDeEmissao = lerData("Digite a data de emissão do alerta");
                    
                    string localizacao;
                    cout << "Digite a localização do alerta: ";
                    getline(cin, localizacao);
            
                    //Alerta alerta(tipoDeAlerta, subid, dataDeEmissao, localizacao);
                    //cout << alerta.getString();
                    
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
            programa.Salvar();
            programa.JSON();
            cout << "Encerrando programa...\n";
            return 0; // Sair do programa
        default:
            cout << "Opção inválida. Tente novamente.\n";
            break;
        }
    }
}