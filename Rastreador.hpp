#define RASTREADOR_HPP

#include <iostream>
#include <string> 

#include "TipoDeComunicaco.hpp"
#include "Data.hpp"
using namespace std;

class Rastreador 
{
protected:
    int id;
    int tipo;
    string marca;
    string modelo;
    TipoDeComunicacao *comunicacao;
    Data ativacao;
    vector<Alerta> alertas;

    Rastreador(int id, int tipo, string marca, string modelo, TipoDeComunicacao* comunicacao,
        EstadoDoRastreador estado, Data ativacao);
public:
    virtual string getString();
};

