#pragma once

#include "Rastreador.hpp"
#include <string>

enum TipoDePlaca{PATICULAR, ESPECIAL, COLECAO, DIPLOMATICO, OFICIAIS, COMERCIAIS};
typedef struct Placa
{
    std::string identificador = "";
    std::string localDeEmissao = "";
    TipoDePlaca tipo = PATICULAR;

    Placa(){}
    Placa(std::string identificador, std::string localDeEmissao, TipoDePlaca tipo) 
     : identificador(identificador), localDeEmissao(localDeEmissao), tipo(tipo){}
} Placa;

class RastreadorVeicular : public Rastreador
{
private:
    std::string tipo = "";
    std::string marcaDoCarro = "";
    std::string modeloDoCarro = "";
    Placa placa;
    bool temCamera = false;
public:
    RastreadorVeicular(unsigned int id, std::string marca, std::string modelo, TipoDeComunicacao* comunicacao,
        EstadoDoRastreador estado, Data ativacao, std::string tipo, std::string marcaDoCarro, std::string modeloDoCarro, Placa placa, bool temCamera);
    std::string getString();
    std::string getStringJSON();

    std::string getTipo();
    std::string getMarcaDoCarro();
    std::string getModeloDoCarro();
    Placa &getPlaca();
    bool getTemCamera();

    void setTipo(std::string tipo);
    void setMarcaDoCarro(std::string marcaDoCarro);
    void setModeloDoCarro(std::string modeloDoCarro);
    void setPlaca(Placa placa);
    void setTemCamera(bool temCamera);
};

