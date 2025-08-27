#include "Programa.hpp"
using namespace std;

int Programa::InserirRastreador(Rastreador& rastreador)
{
    int i = PesquisarRastreador(rastreador.getId());
    if(i == -1) rastreadores.push_back(rastreador);
    else cout << "Já existe rastreador com esse id!" << endl;
    return i;
}

string Programa::ListarRastreadores()
{
    string ans = "";

    for (int i = 0; i < rastreadores.size(); i++)
    {
        ans += rastreadores[i].getString() + "\n";
    }
    
    return ans;
}

void Programa::AlterarRastreador(Rastreador RastreadorAtualizado)
{
    int i = PesquisarRastreador(RastreadorAtualizado.getId());
    if(i == -1) cout << "Não existe rastreador com esse id" << endl;
    else 
    {
        delete rastreadores[i].getTipoDeComunicacaoPtr();
        rastreadores[i] = RastreadorAtualizado; 
    }
}

bool Programa::RemoverRastreador(unsigned int id)
{
    int i = PesquisarRastreador(id);
    if(i == -1) return false;
    rastreadores.erase(rastreadores.begin() + i);
    return true;
}

void Programa::ResetRastreadores() {rastreadores.clear();}

void Programa::Relatorio(){} //implementar depois

int Programa::PesquisarRastreador(unsigned int id)
{
    for(int i = 0; i < rastreadores.size(); i++)
        if(id == rastreadores[i].getId()) return i;
    return -1;
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
        ans += rastreadores[i].getString() + "\n";
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
        ans += rastreadores[i].getStringJSON() + "\n";
    }
    
    json << ans << endl;
    json.close();
}
    
Rastreador* Programa::getRastreador(int id) 
{
    int rastInd = PesquisarRastreador(id);
    if(rastInd == -1) return nullptr;
    return &rastreadores[rastInd];
}
Alerta* Programa::getAlerta(int id, int subid) 
{
    Rastreador* rast = getRastreador(id);
    if(rast == nullptr) return nullptr;
    return rast->getAlerta(subid);
}