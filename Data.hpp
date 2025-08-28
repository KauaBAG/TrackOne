#pragma once

#include <iostream>
#include <string>
class Data
{
private:
    short dia = 1;
    short mes = 1;
    int ano = 2000;

public:
    Data() {}; 
    Data(short dia, short mes, int ano) : dia(dia), mes(mes), ano(ano){}

    short getDia() {return dia;}
    short getMes() {return mes;}
    int getAno() {return ano;}

    std::string getMesString()
    {
        static const std::string meses[] = {
            "Janeiro", "Fevereiro", "Marco", "Abril", "Maio", "Junho", "Julho",
            "Agosto", "Setembro", "Outubro", "Novembro", "Dezembro"
        };
        if (mes >= 1 && mes <= 12)
            return meses[mes - 1];
        else
            return "Mês Inválido";
    }

    void setDia(short dia) 
    {
        if(1<=dia||dia<=12) this->dia = dia;
        else 
        {
            std::cerr<<"Atribuição de valor invalido no dia bloqueada - valor: "<<mes<<std::endl;
        }
    };
    void setMes(short mes) 
    {
        if(1<=mes||mes<=12) this->mes = mes;
        else 
        {
            std::cerr<<"Atribuição de valor invalido no ano bloqueada - valor: "<<mes<<std::endl;
        }
    };
    void setAno(int ano) {this->ano = ano;};

    std::string getString()
    {
        return std::to_string(dia) + " de " + getMesString() + " de " + std::to_string(ano);
    }
};