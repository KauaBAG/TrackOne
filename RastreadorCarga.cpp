#include "RastreadorCarga.hpp"
#include <string>

std::string RastreadorCarga::getString()
{
    return Rastreador::getString() + ",\n    Tipo de carga: " + tipoDeCarga + 
        ",\n    Remetente: " + remetente + ",\n    Destinatario: " + destinatario +
        (eFragil?",\n    É fragil":",\n    Não é fragil"); 
}
std::string RastreadorCarga::getStringSalvar()
{
    return Rastreador::getStringSalvar()+"\n"
     + tipoDeCarga+"\n"
     + remetente+"\n"
     + destinatario+"\n"
     + std::to_string(eFragil);
}
RastreadorCarga::RastreadorCarga(unsigned int id, std::string marca, std::string modelo, TipoDeComunicacao* comunicacao,
    EstadoDoRastreador estado, Data ativacao, std::string tipo, std::string remetente, std::string destinatario, bool eFragil)
    : Rastreador(id, 1, marca, modelo, comunicacao,
        estado, ativacao)
    {
        setTipoDeCarga(tipoDeCarga);
        setRemetente(remetente);
        setDestinatario(destinatario);
        setEFragil(eFragil);
    }

std::string RastreadorCarga::getTipoDeCarga(){return tipoDeCarga;}
std::string RastreadorCarga::getRemetente(){return remetente;}
std::string RastreadorCarga::getDestinatario(){return destinatario;}
bool RastreadorCarga::getEFragil(){return eFragil;}

void RastreadorCarga::setTipoDeCarga(std::string tipoDeCarga){this->tipoDeCarga = tipoDeCarga;}
void RastreadorCarga::setRemetente(std::string remetente){this->remetente = remetente;}
void RastreadorCarga::setDestinatario(std::string destinatario){this->destinatario = destinatario;}
void RastreadorCarga::setEFragil(bool eFragil) {this->eFragil = eFragil;}
