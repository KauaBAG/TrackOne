#include "RastreadorPessoal.hpp"

std::string RastreadorPessoal::getString()
{
    return Rastreador::getString() + ",\n    Nome: " + nome + ",\n    Telefone: " + telefone + ",\n    Documento " + documento;
}
std::string RastreadorPessoal::getStringJSON()
{
    return Rastreador::getStringJSON() + ", " + nome + ", " + telefone + ", " + documento;
}
RastreadorPessoal::RastreadorPessoal(unsigned int id, std::string marca, std::string modelo, TipoDeComunicacao* comunicacao,
    EstadoDoRastreador estado, Data ativacao, std::string nome, std::string telefone, std::string documento)
: Rastreador(id, 2, marca, modelo, comunicacao,
        estado, ativacao)
{
    setNome(nome);
    setTelefone(telefone);
    setDocumento(documento);
}

std::string RastreadorPessoal::getNome(){return nome;};
std::string RastreadorPessoal::getTelefone(){return telefone;};
std::string RastreadorPessoal::getDocumento(){return documento;};

void RastreadorPessoal::setNome(std::string nome){this->nome = nome;}
void RastreadorPessoal::setTelefone(std::string telefone){this->telefone = telefone;}
void RastreadorPessoal::setDocumento(std::string documento){this->documento = documento;}
