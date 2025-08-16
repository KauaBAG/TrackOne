#include "RastreadorVeicular.hpp"

std::string RastreadorVeicular::getString()
{
    return Rastreador::getString() + ", tipo: " + tipo + ", marca do carro: "+marcaDoCarro +", modelo do carro: "+modeloDoCarro+(temCamera?", com":", sem")+" camera";
}
RastreadorVeicular::RastreadorVeicular(unsigned int id, std::string marca, std::string modelo, TipoDeComunicacao* comunicacao,
    EstadoDoRastreador estado, Data ativacao, std::string tipo, std::string marcaDoCarro, std::string modeloDoCarro, Placa placa, bool temCamera)
    : Rastreador(id, 2, marca, modelo, comunicacao,
        estado, ativacao)
{
    setTipo(tipo);
    setMarcaDoCarro(marcaDoCarro);
    setModeloDoCarro(modeloDoCarro);
    this->placa = placa;
    setTemCamera(temCamera);
}

std::string RastreadorVeicular::getTipo(){return tipo;}
std::string RastreadorVeicular::getMarcaDoCarro(){return marcaDoCarro;}
std::string RastreadorVeicular::getModeloDoCarro(){return modeloDoCarro;}
Placa &RastreadorVeicular::getPlaca(){return placa;}
bool RastreadorVeicular::getTemCamera(){return temCamera;}

void RastreadorVeicular::setTipo(std::string tipo){this->tipo = tipo;}
void RastreadorVeicular::setMarcaDoCarro(std::string marcaDoCarro){this->marcaDoCarro = marcaDoCarro;}
void RastreadorVeicular::setModeloDoCarro(std::string modeloDoCarro){this->modeloDoCarro = modeloDoCarro;}
void RastreadorVeicular::setTemCamera(bool temCamera){this->temCamera = temCamera;}