#include "RastreadorCarga.hpp"

std::string RastreadorCarga::getString()
{
    return Rastreador::getString() + ", tipo de carga: " + tipoDeCarga + 
        ", remetente: " + remetente + ", destinatario: " + destinatario +
        (eFragil?", e Fragil":", nao e fragil"); 
}
std::string RastreadorCarga::getStringJSON()
{
    return Rastreador::getStringJSON() + ", " + tipoDeCarga + 
        ", " + remetente + ", " + destinatario +
        (eFragil?", e Fragil":", nao e fragil"); 
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
