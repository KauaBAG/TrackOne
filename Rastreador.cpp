#include "Rastreador.hpp"
#include "Alerta.hpp"

Rastreador::Rastreador(int id, int tipo, std::string marca, std::string modelo, TipoDeComunicacao* comunicacao,
    EstadoDoRastreador estado, Data ativacao) 
    : id(id), tipo(tipo), marca(marca), modelo(modelo), comunicacao(comunicacao),
    estado(estado), ativacao(ativacao) {}

Rastreador::~Rastreador() {delete comunicacao;}

unsigned int Rastreador::getId() {return id;}
std::string Rastreador::getTipo() 
{
    if(tipo==0) return "Rastreador Veicular";
    if(tipo==1) return "Rastreador de Carga";
    if(tipo==2) return "Rastreador Pessoal";
    throw std::runtime_error("Tipo inválido de rastreador: " + std::to_string(tipo) + 
        " (Somente 0(Veicular), 1(Carga), 2(Pessoal) são aceitos)");
}
std::string Rastreador::getMarca() {return marca;}
std::string Rastreador::getModelo() {return modelo;}

TipoDeComunicacao *Rastreador::getTipoDeComunicacao(){return comunicacao;}
Data &Rastreador::getDataDeAtivacao(){return ativacao;};

void Rastreador::setId(unsigned int id) {this->id = id;}
void Rastreador::setMarca(std::string marca) {this->marca = marca;};
void Rastreador::setModelo(std::string modelo) {this->modelo = modelo;};

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