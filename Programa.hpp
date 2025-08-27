#pragma once

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <fstream>

#include "Rastreador.hpp"
#include "Alerta.hpp"
#include "RastreadorCarga.hpp"
#include "RastreadorPessoal.hpp"
#include "RastreadorVeicular.hpp"

using namespace std;

class Programa
{

protected:
    vector <Rastreador> rastreadores;
    Rastreador* getRastreadorByIndex(int index);

public:
    int InserirRastreador(Rastreador& rastreador);
    Rastreador* getRastreador(int id);
    string ListarRastreadores();
    void AlterarRastreador(Rastreador RastreadorAtualizado);
    bool RemoverRastreador(unsigned int id);
    void Relatorio();

    void ResetRastreadores();
    
    int PesquisarRastreador(unsigned int id);
    int PesquisarAlerta(unsigned int id, unsigned int subid);

    void Salvar();
    void JSON();      

    Alerta* getAlerta(int id, int subid);
};