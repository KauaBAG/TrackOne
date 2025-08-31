#pragma once
#include <string> 
#include <vector>
#include <memory>
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
    std::shared_ptr<TipoDeComunicacao> comunicacao = nullptr;  // Usando shared_ptr
    EstadoDoRastreador estado = INATIVO;
    Data ativacao = Data();
    std::vector<Alerta*> alertas = {};
    
    // Construtor protegido
    Rastreador(int id, int tipoDeRastreador, std::string marca, std::string modelo, 
               TipoDeComunicacao* comunicacao, EstadoDoRastreador estado, Data ativacao);

public:
    // Construtor de cópia (será implementado automaticamente pelo shared_ptr)
    Rastreador(const Rastreador& other) = default;
    
    // Operador de atribuição (será implementado automaticamente pelo shared_ptr)
    Rastreador& operator=(const Rastreador& other) = default;
    
    // Destrutor virtual
    virtual ~Rastreador();
    
    // Métodos virtuais
    virtual std::string getString();
    virtual std::string getStringJSON();
    
    // Getters
    unsigned int getId();
    unsigned int getQtdAlertas();
    std::string getTipoDeRastreador();
    std::string getMarca();
    std::string getModelo();
    EstadoDoRastreador getEstado();
    TipoDeComunicacao* getTipoDeComunicacaoPtr();
    Data& getDataDeAtivacaoRef();
    std::string getEstadoString();
    
    // Setters
    void setId(unsigned int id);
    void setMarca(std::string marca);
    void setModelo(std::string modelo);
    void setEstado(EstadoDoRastreador estado);
    
    // Métodos para alertas
    void updateAlerta(Alerta *alerta);
    int searchAlerta(int subid);
    void deleteAlerta(int subid);
    std::string getAlertasList();
    void resetAlertas();
    Alerta* getAlerta(int subid);
};