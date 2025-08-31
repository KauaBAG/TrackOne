#include "Rastreador.hpp"
#include "Alerta.hpp"
#include "Data.hpp"
#include <memory>

std::string Rastreador::getString()
{
    return getTipoDeRastreador() + " \nid: " + std::to_string(id) + 
        ", \nmarca: " + marca + ", \nmodelo: " + modelo + 
        ", \n" + comunicacao->getString() + 
        ", \nestado: " + getEstadoString() +
        ", \ndata de ativacao: " + ativacao.getString();
}

std::string Rastreador::getStringJSON()
{
    return getTipoDeRastreador() +  ", " + std::to_string(id) +", " +
    marca +", "+ modelo + ", "+comunicacao->getString()+", " +
    getEstadoString() +", "+ ativacao.getString();
}

// PRINCIPAL MUDANÇA: Construtor modificado para usar shared_ptr
Rastreador::Rastreador(int id, int tipo, std::string marca, std::string modelo, TipoDeComunicacao* comunicacao,
    EstadoDoRastreador estado, Data ativacao)
{
    setId(id);
    setTipoDeRastreador(tipo);
    setMarca(marca);
    setModelo(modelo);
    this->comunicacao = std::shared_ptr<TipoDeComunicacao>(comunicacao);  // Wrap no shared_ptr
    setEstado(estado);
    this->ativacao = ativacao;
    resetAlertas();
}

// MUDANÇA: Destrutor - agora definido explicitamente
Rastreador::~Rastreador() {
    // shared_ptr limpa automaticamente quando necessário
    // Não precisamos mais do delete comunicacao
}

unsigned int Rastreador::getId() {return id;}

std::string Rastreador::getTipoDeRastreador() 
{
    if(tipoDeRastreador==0) return "Rastreador Veicular";
    if(tipoDeRastreador==1) return "Rastreador de Carga";
    if(tipoDeRastreador==2) return "Rastreador Pessoal";
    throw std::runtime_error("Tipo inválido de rastreador: " + std::to_string(tipoDeRastreador) + 
        " (Somente 0(Veicular), 1(Carga), 2(Pessoal) são aceitos)");
}

std::string Rastreador::getMarca() {return marca;}

std::string Rastreador::getModelo() {return modelo;}

EstadoDoRastreador Rastreador::getEstado() {return estado;}

std::string Rastreador::getEstadoString() {return (std::string[]){"ATIVO", "INATIVO", "MANUTENCAO", "BLOQUEADO"}[estado];}

// MUDANÇA: Retornar ponteiro raw do shared_ptr para compatibilidade
TipoDeComunicacao *Rastreador::getTipoDeComunicacaoPtr(){
    return comunicacao.get();  // .get() retorna o ponteiro raw
}

Data &Rastreador::getDataDeAtivacaoRef(){return ativacao;}

void Rastreador::setTipoDeRastreador(short tipoDeRastreador)
{
    if(tipoDeRastreador < 0 || tipoDeRastreador > 2) throw std::runtime_error("Tipo inválido de rastreador: " + std::to_string(tipoDeRastreador) + 
        " (Somente 0(Veicular), 1(Carga), 2(Pessoal) são aceitos)");
    this->tipoDeRastreador = tipoDeRastreador;
}

void Rastreador::setId(unsigned int id) {this->id = id;}

void Rastreador::setMarca(std::string marca) {this->marca = marca;}

void Rastreador::setModelo(std::string modelo) {this->modelo = modelo;}

void Rastreador::setEstado(EstadoDoRastreador estado) {this->estado = estado;}

void Rastreador::updateAlerta(Alerta &alerta)
{
    int i = searchAlerta(alerta.getSubid());
    if(i==-1) alertas.push_back(alerta);
    else alertas[i] = alerta;
}

int Rastreador::searchAlerta(int subid)
{
    for(int i = 0; i < alertas.size(); i++) 
        if(subid == alertas[i].getSubid()) return i;
    return -1;
}

void Rastreador::deleteAlerta(int subid)
{
    int i = searchAlerta(subid);
    if(i!=-1) alertas.erase(alertas.begin() + i);
}

std::string Rastreador::getAlertasList()
{
    std::string l = "";
    for(int i = 0; i < alertas.size(); i++) l += alertas[i].getString() + '\n';
    return l;
}

void Rastreador::resetAlertas()
{
    alertas.clear();
}

Alerta* Rastreador::getAlerta(int subid) 
{
    int alertaInd = searchAlerta(id);
    if(alertaInd == -1) return nullptr;
    return &alertas[alertaInd];
}
int Rastreador::getQtdAlertas() {return alertas.size();}