#include "multiSincronia.h"

//Escreve o horário e o nome do funcionário no arquivo.
void maquinaPontoSequencial(const vector<int> &filaFuncionarios, ofstream &Arquivo){
    string mensagem = "";                   //Armazena a string a ser colocada no arquivo

    for (int numero : filaFuncionarios) {   //Pega cada coiso do vetor e joga na var, que nem no python

        mensagem = getHorario() + " ID: " + to_string(numero) + "\tTID: " + to_string(std::hash<std::thread::id>{}(std::this_thread::get_id())); 
        cout << endl << mensagem;

        if (Arquivo.is_open()){
            Arquivo << mensagem << endl;
        } else {
            std::cerr << "Erro: Arquivo não está aberto!" << std::endl;
        }
    }
}