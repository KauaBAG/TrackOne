#include "Programa.hpp"
#include "Alerta.hpp"
#include "Data.hpp"
#include "Gsm.hpp"
#include "Rastreador.hpp"
#include "RastreadorPessoal.hpp"
#include "RastreadorVeicular.hpp"
#include <cstdio>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>
#include "Rfid.hpp"
#include "Satelital.hpp"
#include "TipoDeComunicacao.hpp"
#include "utils.hpp"
using namespace std;

int Programa::InserirRastreador(Rastreador* rastreador)
{
    int i = PesquisarRastreador(rastreador->getId());
    if(i == -1) rastreadores.push_back(rastreador);
    else cout << "Já existe rastreador com esse id!" << endl;
    return i;
}

string Programa::ListarRastreadores()
{
    string ans = "";

    for (int i = 0; i < rastreadores.size(); i++)
    {
        ans += rastreadores[i]->getString() + "\n";
    }
    
    return ans;
}

string Programa::ListarAlertas()
{
    string ans = "";

    for (int i = 0; i < rastreadores.size(); i++)
    {
        ans += "Id: " + to_string(rastreadores[i]->getId()) + "\n";
        ans += rastreadores[i]->getAlertasList() + "\n";
    }
    
    return ans;
}
void Programa::AlterarRastreador(Rastreador* RastreadorAtualizado)
{
    int i = PesquisarRastreador(RastreadorAtualizado->getId());
    if(i == -1) cout << "Não existe rastreador com esse id" << endl;
    else 
    {
        delete rastreadores[i];
        rastreadores[i] = RastreadorAtualizado; 
    }
}

bool Programa::RemoverRastreador(unsigned int id)
{
    int i = PesquisarRastreador(id);
    if(i == -1) return false;
    delete rastreadores[i];
    rastreadores.erase(rastreadores.begin() + i);
    return true;
}

void Programa::ResetRastreadores() 
{
    for(Rastreador* rast : rastreadores) delete rast;
    rastreadores.clear();
}

int Programa::PesquisarRastreador(unsigned int id)
{
    for(int i = 0; i < rastreadores.size(); i++)
        if(id == rastreadores[i]->getId()) return i;
    return -1;
}
vector<Rastreador*> Programa::getRastreadoresComInicio(unsigned int id)
{
    vector<Rastreador*> found;
    string sbegin = to_string(id);
    for(int i = 0; i < rastreadores.size(); i++)
        if(ABeginsWithB(to_string(rastreadores[i]->getId()), sbegin))
            found.push_back(rastreadores[i]);
    return found;
}

void Programa::contadorTipo(){
        qtda = 0; qtdc = 0; qtdp = 0; qtdv = 0;
        for(auto &rastreador : rastreadores){
            if(rastreador->getTipoDeRastreador() == "Rastreador de Carga"){
                qtdc++;
            }else if(rastreador->getTipoDeRastreador() == "Rastreador Veicular"){
                qtdv++;
            }else if(rastreador->getTipoDeRastreador() == "Rastreador Pessoal"){
                qtdp++;
            }
            qtda = rastreador->getQtdAlertas();
        }
    }

int Programa::getQuantidadeDeAlertas(){ 
        contadorTipo();
        return qtda;
    }
    
    void Programa::Relatorio(){

        contadorTipo();

        cout << "Rastreadores cadastrados: " << rastreadores.size() << endl;
        cout << "Rastreadores de carga: " << qtdc << endl;
        cout << "Rastreadores pessoais: " << qtdp << endl;
        cout << "Rastreadores veiculares: " << qtdv << endl;
        cout << "Rastreadores com alerta: " << qtda << endl;

        cout << "\n1 - Consultar rastreadores: " << endl;
        cout << "2 - Consultar rastreadores por tipo: " << endl;
        cout << "3 - Consultar rastreadores com alertas" << endl;

        cout << "Escolha uma opção: " << endl;
        int escolha;
        cin >> escolha;
        cin.ignore();

        switch(escolha){

            case 1:
                cout << ListarRastreadores();
                break;
            case 2:
                cout << "1 - Rastreador de carga " << endl;
                cout << "2 - Rastreador pessoal " << endl;
                cout << "3 - Rastreador veicular " << endl;

                cout << "Escolha o tipo de rastreador: " << endl;
                int escolha2;
                cin >> escolha2;
                cin.ignore();
                
                for (auto &rastreador : rastreadores){
                    switch(escolha2){
                        
                        case 1:
                            if (rastreador->getTipoDeRastreador() == "Rastreador de Carga"){
                                cout << rastreador->getString();
                            }
                            break;
                        case 2:
                            if (rastreador->getTipoDeRastreador() == "Rastreador Pessoal"){
                                cout << rastreador->getString();
                            }
                            break;
                        case 3:
                            if (rastreador->getTipoDeRastreador() == "Rastreador Veicular"){
                                cout << rastreador->getString();
                            }    
                            break;  
                    }
                }
                        break;
            case 3:
                for (int i = 0; i < rastreadores.size(); i++){
                    if(rastreadores.at(i)->getQtdAlertas() != 0){
                        cout << rastreadores.at(i)->getString() << endl;
                    }
                }
                break;
        }
        
    }

void Programa::Salvar()
{
    fstream Arquivo("ArquivoSalvo.txt", ios::out);

    if(!Arquivo){
        cout << "O aquivo não foi criado!" << endl;
    }

    string ans = "";

    for (int i = 0; i < rastreadores.size(); i++)
    {
        ans += rastreadores[i]->getStringSalvar() + "\n";
    }
    
    Arquivo << ans << endl;
    Arquivo.close();
    cout << "Arquivo Salvo em \"ArquivoSalvo.txt\"" << endl;
}

Rastreador* CarregarRastreador(vector<std::string> desc)
{
    int c = 0;
    cout<<desc[c]<<endl;
    int tipo = stoi(desc[c]); c++;
    cout<<desc[c]<<endl;
    int id = stoi(desc[c]); c++;
    string marca = desc[c]; c++;
    string modelo = desc[c]; c++;
    TipoDeComunicacao* tp = nullptr;
    cout<<desc[c]<<endl;
    int TipoDeComunicacao = stoi(desc[c]);c++;
    if(TipoDeComunicacao == 0)//GSM
    {
        Banda b;
        if(desc[c]=="2G")b=_2G;
        else if(desc[c]=="4G")b=_4G;
        else if(desc[c]=="5G")b=_5G;
        c++;
        bool fallback = desc[c][0]-'0'; c++;
        tp = new Gsm(b,fallback);
    }
    else if(TipoDeComunicacao == 1)//RFID
    {
        cout<<desc[c]<<endl;
        float frequencia = stof(desc[c]); c++;
        string tipoRfid = desc[c]; c++;
        tp = new Rfid(frequencia,tipoRfid);
    }
    else if(TipoDeComunicacao == 2)//Satelital
    {
        cout<<desc[c]<<endl;
        int id = stoi(desc[c]); c++;
        tp = new Satelital(id);
    }
    EstadoDoRastreador estado;
    if(desc[c]=="ATIVO")estado=EstadoDoRastreador::ATIVO;
    else if(desc[c]=="INATIVO")estado=EstadoDoRastreador::INATIVO;
    else if(desc[c]=="BLOQUEADO")estado=EstadoDoRastreador::BLOQUEADO;
    else if(desc[c]=="MANUTENCAO")estado=EstadoDoRastreador::MANUTENCAO;
    c++;

    int dia = stoi(desc[c]); c++;
    int mes = stoi(desc[c]); c++;
    int ano = stoi(desc[c]); c++;

    Data dt(dia,mes,ano);

    if(tipo == 0)//veicular
    {
        string tipoVeiculo = desc[c]; c++;
        string marcaDoCarro = desc[c]; c++;
        string modeloDoCarro = desc[c]; c++;
        
        string identificador = desc[c]; c++;
        string localDeEmissao = desc[c]; c++;
        TipoDePlaca tipoPlaca = (TipoDePlaca)stoi(desc[c]);c++;

        bool temCamera = desc[c][0]-'0'; c++;

        return new RastreadorVeicular(id,marca,modelo,tp,estado,dt,tipoVeiculo,marcaDoCarro,modeloDoCarro,
            Placa(identificador,localDeEmissao,tipoPlaca),temCamera);
    }

    return nullptr;
}
Alerta* CriarAlerta(std::string desc)
{
    return nullptr;
}
void Programa::Carregar()
{
    fstream arquivo("ArquivoSalvo.txt", ios::in);
    if(!arquivo)
        return;
    std::string linha; 
    vector<std::string> rastCompleto; 
    getline(arquivo,linha);

    while(getline(arquivo,linha))
    {
        if(linha == "INICIO")
        {
            InserirRastreador(CarregarRastreador(rastCompleto));
            rastCompleto.clear();
        }
        else rastCompleto.push_back(linha);
    }
    InserirRastreador(CarregarRastreador(rastCompleto));
}
    
Rastreador* Programa::getRastreador(int id) 
{
    int rastInd = PesquisarRastreador(id);
    if(rastInd == -1) return nullptr;
    return rastreadores[rastInd];
}
Alerta* Programa::getAlerta(int id, int subid) 
{
    Rastreador* rast = getRastreador(id);
    if(rast == nullptr) return nullptr;
    return rast->getAlerta(subid);
} 
Programa::~Programa()
{
    for(Rastreador* rast : rastreadores) delete rast;
}

int Programa::getQuantidadeDeRastreadores() { return rastreadores.size(); }

