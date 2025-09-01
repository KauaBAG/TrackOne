#include "Programa.hpp"
#include "Alerta.hpp"
#include "Rastreador.hpp"
#include "RastreadorPessoal.hpp"
#include "RastreadorVeicular.hpp"
#include <fstream>
#include <iterator>
#include <string>
#include <vector>
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
        ans += rastreadores[i]->getString() + "\n";
    }
    Arquivo << ans << endl;
    Arquivo.close();
    cout << "Arquivo Salvo em \"ArquivoSalvo.txt\"" << endl;

    fstream arquivo3("AlertaSalvo.txt", ios::out);
    if(!arquivo3){
        cout << "O aquivo não foi criado!" << endl;
    }
    string ans2 = "";
    for (int i = 0; i < rastreadores.size(); i++)
    {
        ans2 += rastreadores[i]->getStringCarregar() + "\n ";
    }  
    arquivo3 << ans2 << endl;
    arquivo3.close();
    cout << "Arquivo Salvo em \"AlertaSalvo.txt\"" << endl;
}

void Programa::JSON()
{
    fstream json("Arquivo.json", ios::out);

    if(!json){
        cout << "O aquivo não foi criado!" << endl;
    }

    string ans = "";

    for (int i = 0; i < rastreadores.size(); i++)
    {
        ans += rastreadores[i]->getStringJSON() + "\n";
    }
    
    json << ans << endl;
    json.close();
}
Rastreador* CarregarRastreador(vector<std::string> desc)
{
    return nullptr;
}
Alerta* CarregarAlerta(vector<std::string> desc)
{
    return nullptr;
}
void Programa::Carregar()
{
    fstream arquivo("ArquivoSalvo.txt", ios::in);
    if(!arquivo)
        return;
    std::string linha; 
    vector<std::string> rastCompleto(1); 
    getline(arquivo,rastCompleto[0]);

    while(getline(arquivo,linha))
    {
        if(linha == "Rastreador Veicular" || 
            linha == "Rastreador de Carga" || 
            linha == "Rastreador Pessoal")
        {
            CarregarRastreador(rastCompleto);
            rastCompleto.clear();
        }
        rastCompleto.push_back(linha);
    }
    CarregarRastreador(rastCompleto);
    arquivo.close();
    fstream arquivo2("AlertaSalvo.txt", ios::in);
    if(!arquivo2)
        return;
        linha = "";
    vector<std::string> alertaCompleto(1); 
    getline(arquivo2,alertaCompleto[0]);

    while(getline(arquivo2,linha))
    {
        if(linha == "Rastreador Veicular" || 
            linha == "Rastreador de Carga" || 
            linha == "Rastreador Pessoal")
        {
            CarregarAlerta(alertaCompleto);
            alertaCompleto.clear();
        }
        alertaCompleto.push_back(linha);
    }
    CarregarAlerta(alertaCompleto);
    arquivo2.close();
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

