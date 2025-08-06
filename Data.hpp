#pragma once

typedef struct Data
{
    short dia;
    short mes;
    int ano;

    Data(short dia, short mes, int ano) : dia(dia), mes(mes), ano(ano){}
}Data;