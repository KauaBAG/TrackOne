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

#include <cstddef>
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <limits>
#include <typeinfo>

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
    cout << mensagem << " (dia mes ano)\n";
    
    dia = lerInteiro("Dia: ");
    mes = lerInteiro("Mês: ");
    ano = lerInteiro("Ano: ");
      
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

bool promptSimNao(std::string pergunta)
{
    while(true)
    {
        cout << "\n" << pergunta <<"\n1. Sim \n0. Nao\n";
        int i = lerInteiro("Resposta: ");
        if(i == 1) return true;
        if(i == 0) return false;
        cout << "Opção inválida. Tente novamente.\n";
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

    bool fallback = promptSimNao("Possui fallback?");

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

RastreadorVeicular* criarRastreadorVeicular(const RastreadorBase& base, TipoDeComunicacao* comunicacao) {
    cout << "\n=== Criando Rastreador Veicular ===\n";
    
    string tipoDeCarro, marcaDoCarro, modeloDoCarro;
    cout << "Qual o tipo de carro: ";
    cin >> tipoDeCarro;
    cout << "Qual a marca do carro: ";
    cin >> marcaDoCarro;
    cout << "Qual o modelo do carro: ";
    cin >> modeloDoCarro;
    limparBuffer();
    
    bool temCamera = promptSimNao("Possui Camera?");
    
    string identificador, localDeEmissao;
    cout << "\nDigite os digitos da placa: ";
    cin >> identificador;
    limparBuffer();
    cout << "Digite o local de emissão da placa: ";
    getline(cin, localDeEmissao);
    
    TipoDePlaca tipo = (TipoDePlaca)(menu({"PARTICULAR", "ESPECIAL", "COLECAO", "DIPLOMATICO", "OFICIAIS", "COMERCIAIS"}, "Tipos de Placa")-1);
    
    Placa placa(identificador, localDeEmissao, tipo);

    return new RastreadorVeicular(base.id, base.marca, base.modelo, comunicacao, 
                               base.estado, base.dataDeAtivacao, tipoDeCarro, 
                               marcaDoCarro, modeloDoCarro, placa, temCamera);
}

RastreadorCarga* criarRastreadorCarga(const RastreadorBase& base, TipoDeComunicacao* comunicacao) {
    cout << "\n=== Criando Rastreador de Carga ===\n";

    string tipoCarga, remetente, destinatario;
    cout << "Qual o tipo de carga: ";
    getline(cin, tipoCarga);
    cout << "Qual o remetente da carga: ";
    getline(cin, remetente);
    cout << "Qual o destinatario da carga: ";
    getline(cin, destinatario);
    
    bool fragil = promptSimNao("É fragil?");
    
    return new RastreadorCarga(base.id, base.marca, base.modelo, comunicacao, 
                        base.estado, base.dataDeAtivacao, tipoCarga, 
                        remetente, destinatario, fragil);
}

RastreadorPessoal* criarRastreadorPessoal(const RastreadorBase& base, TipoDeComunicacao* comunicacao) {
    cout << "\n=== Criando Rastreador Pessoal ===\n";
    
    string nome, telefone, documento;
    cout << "Digite seu nome: ";
    getline(cin, nome);
    cout << "Digite seu telefone: ";
    getline(cin, telefone);
    cout << "Digite seu documento: ";
    getline(cin, documento);
    
    return new RastreadorPessoal(base.id, base.marca, base.modelo, comunicacao, 
                              base.estado, base.dataDeAtivacao, nome, telefone, documento);
}

void promptCadastroRastreador()
{
    cout << "\n=== CADASTRO DE RASTREADOR ===\n";
                        
    RastreadorBase base = lerDadosBase();    
    short tipoDeRastreador = menu({"Veicular", "Carga", "Pessoal"}, "Tipos de Rastreador") - 1;                        
    
    cout << "Criando comunicação...\n";
    
    TipoDeComunicacao* comunicacao = criarComunicacao();
    Rastreador* toInsert;
    switch (tipoDeRastreador) 
    {
        case 0: toInsert = criarRastreadorVeicular(base, comunicacao); break;
        case 1: toInsert = criarRastreadorCarga(base, comunicacao); break;
        case 2: toInsert = criarRastreadorPessoal(base, comunicacao); break;
        default:
            cout << "Tipo de rastreador inválido.\n";
            delete comunicacao; // Limpar memória se não foi usado
            return;
    }
    while(true)
    {
        if(programa.InserirRastreador(toInsert) == -1) 
        {
            cout << "\nOperação de cadastro concluída.\n";
            return;
        }
        else 
        {
            int conflictingId = toInsert->getId();
            cout<<"\nRastreador Cadastrado\n"<<endl;
            cout<<toInsert->getString()<<endl<<endl;
            Rastreador* existing = programa.getRastreador(conflictingId);
            if(existing!=nullptr) 
            {
                cout<<"Rastreador Existente"<<endl;
                cout << "\n" << existing->getString() << "\n";
            }
            switch(menu({"Inserir Cadastrado e apagar Existente", "Apagar Cadastrado e manter Existente", "Alterar Id do Cadastrado", }, "Como prosseguir?")-1)
            {
                case 0:
                    programa.AlterarRastreador(toInsert); return;
                case 1:
                    delete toInsert; return;
                case 2:
                    toInsert->setId(lerInteiro("Insira o novo id: ")); break;
            }
        }
    }
    
    
}
Rastreador* promptEscolherRastreador(string prompt)
{
    Rastreador* selected = nullptr;
    while(selected==nullptr)
    {
        unsigned int id = lerInteiro(prompt);
        vector<Rastreador*> encontrados = programa.getRastreadoresComInicio(id);
        
        if(encontrados.size()==1)
        {
            selected=encontrados.front();
            break;
        }
        vector<string> escolhas;
        for (Rastreador* r : encontrados) 
            escolhas.push_back(to_string(r->getId()));
        escolhas.push_back("Digitar novamente");
        escolhas.push_back("Voltar");
        
        string mPrompt = encontrados.size()==0? "Não há rastreadores com esse Id!": "Há vários rastreadores com Id similar a esse! Escolher qual?";
        int escolha = menu(escolhas, mPrompt)-1;

        if(escolha == escolhas.size()-1) break;
        if(escolha == escolhas.size()-2) continue;

        selected = encontrados[escolha];
    }
    return selected;
}
void promptExibirRastreador()
{
    cout << "\n=== EXIBIR RASTREADORES ===\n";
    if (programa.getQuantidadeDeRastreadores() == 0) {
        cout << "Nenhum rastreador cadastrado\n";
        return;
    }
    
    Rastreador* selected = promptEscolherRastreador("Digite o Id do rastreador que deseja exibir: ");
    if(selected == nullptr) return;

    cout << "\n" << selected->getString() << "\n";
    cout << "\n# Pressione qualquer tecla para continuar";
    getchar();
}
void promptAlterarRastreador()
{
    cout << "\n=== ALTERAR RASTREADOR ===\n";
    if (programa.getQuantidadeDeRastreadores() == 0) 
    {
        cout << "Nenhum rastreador cadastrado\n";
        return;;
    }
    unsigned int id;
    Rastreador* rastr = promptEscolherRastreador("Digite o Id do rastreador que deseja alterar: ");
    if(rastr == nullptr) return;

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
}
void promptRemoverRastreador()
{
    cout << "\n=== REMOVER RASTREADOR ===\n";
    if (programa.getQuantidadeDeRastreadores() == 0) {
        cout << "Nenhum rastreador cadastrado\n";
        return;
    }

    Rastreador* selected = promptEscolherRastreador("Digite o Id do rastreador que deseja excluir: ");
    if(selected == nullptr) return;

    cout << "\n" << selected->getString() << "\n";
    if(!promptSimNao("Tem certeza que quer excluir esse rastreador?")) return;
    
    programa.RemoverRastreador(selected->getId());
    cout << "Rastreador removido com sucesso!\n";   
}
void promptCadastrarAlerta()
{
    cout << "\n=== Cadastrar Alerta ===\n";
    if (programa.getQuantidadeDeRastreadores() == 0) {
        cout << "Nenhum rastreador cadastrado, portanto, não há como cadastrar alertas!\n";
        return;
    }
    Rastreador* rastreador = promptEscolherRastreador("Digite o ID do rastreador para associar o alerta: ");
    if(rastreador == nullptr) return;
    
    
    unsigned int subid = static_cast<unsigned int>(lerInteiro("Digite o subid do alerta: "));
    
    Data dataDeEmissao = lerData("Digite a data de emissão do alerta");
    unsigned int tipoDeAlerta = menu({"Velocidade", "Bateria", "Zona"}, "Tipos de Alerta");

    string localizacao;
    cout << "Digite a localização do alerta: ";
    getline(cin, localizacao);
    
    Alerta* alerta;
    switch (tipoDeAlerta)
    {
    case 1: {
        float velocidadeExercida = 0, velocidadeLimite = 0;
        while(true)
        {
            cout << "Digite a velocidade exercida: ";
            cin >> velocidadeExercida;
            cout << "Digite a velocidade limite: ";
            cin >> velocidadeLimite;
            if (velocidadeExercida >= velocidadeLimite) break;
            cout << "Velocidade exercida não pode ser menor que a velocidade limite. Tente novamente.\n";
        }
        limparBuffer();
        
        alerta = new AlertaVelocidade(subid, dataDeEmissao, localizacao, velocidadeExercida, velocidadeLimite);
        break;
    }
    case 2:{
        bool foiViolada = promptSimNao("Foi violada?");
        bool foiDescarregada = promptSimNao("Foi descarregada?");

        alerta = new AlertaBateria(subid, dataDeEmissao, localizacao, foiViolada, foiDescarregada);
        break;
    }
        
    case 3:{
        bool entrouZona = promptSimNao("Entrou na zona?");
        string zona;
        cout << "Digite o nome da zona: ";
        getline(cin, zona);

        alerta = new AlertaZona(subid, dataDeEmissao, localizacao, entrouZona, zona);
        break;
    }
    
    default:
        cout << "Ta errado boy\n";
        break;
    }
    rastreador->updateAlerta(alerta);
}
Alerta* promptEscolherAlerta(string prompt, Rastreador* rastreador)
{
    Alerta* selected = nullptr;
    while(selected==nullptr)
    {
        unsigned int subid = lerInteiro(prompt);
        vector<Alerta*> encontrados = rastreador->getAlertasComInicio(subid);
        
        if(encontrados.size()==1)
        {
            selected=encontrados.front();
            break;
        }
        vector<string> escolhas;
        for (Alerta* a : encontrados) 
            escolhas.push_back(to_string(a->getSubid()));
        escolhas.push_back("Digitar novamente");
        escolhas.push_back("Voltar");
        
        string mPrompt = encontrados.size()==0? "Não há alertas com esse subid!": "Há várias alertas com subid similar a esse! Escolher qual?";
        int escolha = menu(escolhas, mPrompt)-1;

        if(escolha == escolhas.size()-1) break;
        if(escolha == escolhas.size()-2) continue;

        selected = encontrados[escolha];
    }
    return selected;
}
Alerta* promptEscolherAlerta(Rastreador* & rastreadorRef, string prompt)
{
    Alerta* aSelected; 
    while (true) 
    {
        rastreadorRef = promptEscolherRastreador("Digite o Id do rastreador que se encontra a alerta: ");
        if(rastreadorRef==nullptr) return nullptr;

        aSelected = promptEscolherAlerta(prompt, rastreadorRef);
        if(aSelected==nullptr) continue;
        break;
    }
    return aSelected;
}
Alerta* promptEscolherAlerta(string prompt)
{
    Rastreador* rastreadorRef;   
    return promptEscolherAlerta(rastreadorRef, prompt);
}
void promptExibirAlerta()
{
    cout << "\n=== Exibir Alerta ===\n";
    if (programa.getQuantidadeDeRastreadores() == 0) {
        cout << "Nenhum rastreador cadastrado, portanto, não há como exibir alertas!\n";
        return;
    }

    Alerta* selected = promptEscolherAlerta("Digite o subId do Alerta que deseja exibir: ");
    if(selected==nullptr) return;

    cout << "\n" << selected->getString() << "\n";

    cout << "\n# Pressione qualquer tecla para continuar";
}
void promptAlterarAlerta()
{
    cout << "\n=== Alterar Alerta ===\n";
    if (programa.getQuantidadeDeRastreadores() == 0) {
        cout << "Nenhum rastreador cadastrado, portanto, não há como alterar alertas!\n";
        return;
    }

    Alerta* alerta = promptEscolherAlerta("Digite o subId do Alerta que deseja alterar: ");
    if(alerta == nullptr) return;

    cout << alerta->getString();
    
    int ParamAlterar = menu({"Tipo","Data de Emissao","Localização"}, "Parametros de Atualizaçao");
    
    switch(ParamAlterar) {
        case 1: { break;}
        case 2: {Data data; data = lerData("Qual a nova data de emissão"); alerta->setDataDeEmissao(data); break;}
        case 3: {string localizacao = ""; cout << "Digite a nova localização: "; 
            getline(cin, localizacao); alerta->setLocalizacao(localizacao); break;}
    };
}
void promptRemoverAlerta()
{
    cout << "\n=== Remover Alerta ===\n";
    if (programa.getQuantidadeDeRastreadores() == 0) {
        cout << "Nenhum rastreador cadastrado, portanto, não há como remover alertas!\n";
        return;
    }
    Rastreador* rastreador = nullptr;   
    Alerta* alerta = promptEscolherAlerta(rastreador, "Digite o subId do Alerta que deseja excluir: ");
    if(rastreador==nullptr||alerta==nullptr) return;

    cout << "\n" << alerta->getString() << "\n";
    if(!promptSimNao("Tem certeza que quer excluir essa alerta?")) return;

    rastreador->deleteAlerta(alerta->getSubid());
    cout << "Alerta removida com sucesso!\n";   
}
int main() {
    cout << "=== Sistema de Rastreamento Iniciado ===\n";
    
    while(true) {
        int escolhaPrincipal = menu({"Gerenciar Rastreados", "Gerenciar Alertas", "Mostrar Relatório", "Sair"}, "MENU PRINCIPAL");
        
        switch (escolhaPrincipal) {
        case 1: {
            bool voltarAoMenuPrincipal = false;
    
            while (!voltarAoMenuPrincipal) {
                int escolhaRastreados = menu({"Cadastrar Rastreador", "Listar Rastreadores", "Exibir Rastreador", 
                                            "Alterar Rastreador", "Remover Rastreador", "Voltar"}, "GERENCIAR RASTREADOS");
                
                switch (escolhaRastreados) {
                    case 1: {
                        promptCadastroRastreador();
                        break;
                    }      
    
                    case 2: {
                        cout << "\n=== LISTAR RASTREADORES ===\n";
                        if (programa.getQuantidadeDeRastreadores() == 0) {
                            cout << "Nenhum rastreador cadastrado\n";
                            break;
                        }
                        cout << programa.ListarRastreadores();
                        cout << "\n# Pressione qualquer tecla para continuar";
                        getchar();
                        
                        break;
                    }
                    case 3: {
                        promptExibirRastreador();
                        break;
                    }
                    case 4: {
                        promptAlterarRastreador();
                        break;
                    }
                    case 5: {
                        promptRemoverRastreador();
                        break;
                    }
                    case 6: {
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
            bool voltarAoMenuPrincipal = false;
    
            while (!voltarAoMenuPrincipal) {
                int escolhaAlertas = menu({"Cadastrar Alerta", "Listar Alertas", "Exibir Alerta", 
                                            "Alterar Alerta", "Remover Alerta", "Voltar"}, "GERENCIAR ALERTAS");
                switch (escolhaAlertas) {
                    case 1: {
                        promptCadastrarAlerta();
                        break;
                    }
                    case 2: {
                        if (programa.getQuantidadeDeRastreadores() == 0) {
                            cout << "Nenhum rastreador cadastrado, portanto, não há alertas\n";
                            break;
                        }
                        if (programa.getQuantidadeDeAlertas() == 0) {
                            cout << "Nenhum alerta cadastrado\n";
                            break;
                        }
                        cout << "Listar Alertas\n";
                        cout << programa.ListarAlertas();
                        cout << "\n# Pressione qualquer tecla para continuar";
                        getchar();
                        break;
                    }
                    case 3: {
                        promptExibirAlerta();
                        break;
                    }
                    case 4: {
                        promptAlterarAlerta();
                        break;
                    }
                    case 5: {
                        promptRemoverAlerta();
                        break;
                    }
                    case 6:
                        cout << "Voltando ao menu principal...\n";
                        voltarAoMenuPrincipal = true; // Sinaliza para sair do loop
                        break; // Voltar ao menu principal
                    default:
                        cout << "Opção inválida. Tente novamente.\n";
                        break;
                    }
                }    
                break;    
            }   
        case 3:
            cout << "\n--- RELATóRIO GERAL ---\n";
            programa.Relatorio();
            cout << "\n# Pressione qualquer tecla para continuar";
            getchar();
            break;
        case 4:
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