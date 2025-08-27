//Programa.hpp
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

class programa{

    protected:

    vector <Rastreador> rastreadores;

    public:

	//Rastreador
	
    void InserirRastreador(Rastreador& rastreador){
    	int i = PesquisarRastreador(rastreador.getId());
    	if(i == -1) rastreadores.push_back(rastreador);
        else cout << "Ta errado boy" << endl;
    }
    
    string ListarRastreadores(){
        string ans = "";

    	for (int i = 0; i < rastreadores.size(); i++)
        {
            ans += rastreadores[i].getString() + "\n";
		}
        
        return ans;
	}
    
    void AlterarRastreador(Rastreador RastreadorAtualizado){
        int i = PesquisarRastreador(RastreadorAtualizado.getId());
    	if(i == -1) cout << "Ta errado boy" << endl;
        else 
        {
            //delete rastreadores[i];
            rastreadores[i] = RastreadorAtualizado; 
        }
    }
    
    bool RemoverRastreador(unsigned int id){
        int i = PesquisarRastreador(id);
        if(i==-1)return false;
        rastreadores.erase(rastreadores.begin() + i);
        return true;
    }

    void ResetRastreadores(){
        rastreadores.clear();
    }
    
    void Relatorio(){} //implementar depois
    
    int PesquisarRastreador(unsigned int id){
		for(int i = 0; i < rastreadores.size(); i++)
    		if(id == rastreadores[i].getId()) return i;
        return -1;
    }
    
    int PesquisarAlerta(unsigned int id, unsigned int subid){
        int idxr = PesquisarRastreador(id);
        if(idxr == -1){
            cout << "Rastreador não encontrado!" << endl;
            return -1;
                                                                                                                                                                                                                }
        Rastreador& rastreador = rastreadores.at(idxr);
        int idxa = rastreador.searchAlerta(subid);

        if (rastreador.getAlertas().empty()) {
            cout << "O rastreador não possui alertas!" << endl;
            return -1;
        }
            if(idxa == -1){
            cout << "Alerta não encontrado!" << endl;
            return -1;
            }
            return idxa;
        }       

    void Salvar(){
        fstream Arquivo("ArquivoSalvo.txt", ios::out);

        if(!Arquivo){
            cout << "O aquivo não foi criado!" << endl;
        }

        string ans = "";

    	for (int i = 0; i < rastreadores.size(); i++)
        {
            ans += rastreadores[i].getString() + "\n";
		}
        
        Arquivo << ans << endl;
        Arquivo.close();
        cout << "Arquivo Salvo em \"ArquivoSalvo.txt\"" << endl;
    }

    void JSON(){
        fstream json("Arquivo.json", ios::out);

        if(!json){
            cout << "O aquivo não foi criado!" << endl;
        }

        string ans = "";

    	for (int i = 0; i < rastreadores.size(); i++)
        {
            ans += rastreadores[i].getStringJSON() + "\n";
		}
        
        json << ans << endl;
        json.close();
        cout << "Arquivo Salvo em \"Arquivo.json\"" << endl;
        }
        
    Rastreador* getRastreadorByIndex(int index) { return &(rastreadores[index]); }
    
    Rastreador* getRastreadorId(int id) {
        int idxr = PesquisarRastreador(id);
        if(idxr == -1) {
            cout << "Rastreador não encontrado!" << endl;
            return nullptr;
        }
        return getRastreadorByIndex(idxr);
    }

};
