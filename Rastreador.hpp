#pragma once

#include <string> 
#include <vector>

#include "Data.hpp"
#include "Alerta.hpp"
#include "TipoDeComunicacao.hpp"

enum EstadoDoRastreador {ATIVO, INATIVO, MANUTENCAO, BLOQUEADO};

class Rastreador 
{
private:
    void setTipoDeRastreador(short tipoDeRastreador);
protected:
    unsigned int id;
    short tipoDeRastreador = -1;
    std::string marca = "";
    std::string modelo = "";
    TipoDeComunicacao *comunicacao = NULL;
    EstadoDoRastreador estado = INATIVO;
    Data ativacao = Data();
    std::vector<Alerta> alertas = {};

    Rastreador(int id, int tipoDeRastreador, std::string marca, std::string modelo, TipoDeComunicacao* comunicacao,
        EstadoDoRastreador estado, Data ativacao);
public:
    virtual std::string getString();
    virtual std::string getStringJSON();

    virtual ~Rastreador();

    unsigned int getId();
    std::string getTipoDeRastreador();
    std::string getMarca();
    std::string getModelo();
    EstadoDoRastreador getEstado();

    TipoDeComunicacao *getTipoDeComunicacaoPtr();
    Data &getDataDeAtivacaoRef();

    void setId(unsigned int id);
    void setMarca(std::string marca);
    void setModelo(std::string modelo);
    void setEstado(EstadoDoRastreador estado);
    std::string getEstadoString();

    void updateAlerta(Alerta &alerta);
    int searchAlerta(int subid);
    void deleteAlerta(int subid);
    std::string getAlertasList();
    void resetAlertas();
    std::vector<Alerta> getAlertas();
    
};
