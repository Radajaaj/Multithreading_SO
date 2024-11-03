#include "multiSincronia.h"

void maquinaPontoSequencial(const vector<int> &filaFuncionarios, ofstream &Arquivo){
    //O que que vai fazer: vai abrir o arquivo, escrever o nome do funcionário e o horário nele, e fechar.
    string mensagem = "";
    string numeroString = "";

    // "Range-Based loop" para iterar por elementos de um vetor
    // Vi no reddit, parece elegante
    for (int numero : filaFuncionarios) {   //Basicamente ele pega cada coiso do vetor e joga nessa variavel
        //cout << numero << " ";                // Que nem no python

        mensagem = getHorario() + " ID: " + to_string(numero);
        cout << endl << mensagem;

        Arquivo << mensagem << endl;
    }


}