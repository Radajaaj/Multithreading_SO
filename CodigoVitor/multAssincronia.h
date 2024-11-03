#include "header.h"

//Escreve o horário e o nome do funcionário no arquivo.
void maquinaPontoAssincrona(const vector<int> &filaFuncionarios, ofstream &Arquivo){
    string mensagem = "";                   //Armazena a string a ser colocada no arquivo

    for (int numero : filaFuncionarios) {   //Pega cada coiso do vetor e joga na var, que nem no python

        mensagem = getHorario() + " ID: " + to_string(numero);
        cout << endl << mensagem;

        Arquivo << mensagem << endl;
    }
}