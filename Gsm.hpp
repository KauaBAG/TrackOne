#pragma once

#include "TipoDeComunicacao.hpp"
#include <string>

enum Banda{_2G, _4G, _5G};

class Gsm : public TipoDeComunicacao
{
private:
    Banda banda = _2G;
    bool fallback = false;
public:
    Gsm(Banda banda, bool fallback) : TipoDeComunicacao(0)
    {
        setBanda(banda);
        setFallback(fallback);
    }
    std::string toString(Banda b)
    {
        switch (banda) 
        {
            case (_2G):
                return "2G";
            case (_4G):
                return "4G";
            case (_5G):
                return "5G";
            default:
                return "Desconhecido";
        }
    }
    std::string getString()
    {
        return "    Comunicação GSM de banda " + toString(banda) + (fallback?" com fallback":" sem fallback");
    }
    std::string getStringSalvar()
    {
        return std::to_string(TipoDeComunicacao::tipo)+"\n" 
        + toString(banda)+"\n"
        + std::to_string(fallback);
    }

    Banda getBanda() {return banda;}
    bool getFallback() {return fallback;}

    void setBanda(Banda banda) {this->banda = banda;}
    void setFallback(bool fallback) {this->fallback = fallback;}
};

