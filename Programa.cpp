#include "Programa.hpp"
#include "Rastreador.hpp"
#include "RastreadorVeicular.hpp"
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
