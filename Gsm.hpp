#pragma once

#include "TipoComunicacao.hpp"

enum Banda{_2G, _4G, _5G};

class Gsm : TipoDeComunicacao
{
private:
    Banda banda;
    bool fallback;
public:
    Gsm(Banda banda, bool fallback) : banda(banda), fallback(fallback), TipoDeComunicacao(0){}
};

