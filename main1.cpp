#include "sequencial.h"


int main(){
    //float t_inicio, t_fim;
    srand(time(NULL));

    ofstream Arquivo("pontosBatidos.txt");
    if (!Arquivo){
        std::cerr << " Erro ao abrir o arquivo! " << endl;
        return 1;
    }

    int numThreads = 0;
    int sincrono = -1;
    int tamanhoFila = 300;

    while(numThreads < 1){  //Selecionamos o numero de threads
        cout << "--_-''- Boas Vindas ao Sistema! -''-_--" << endl;

        cout << "-_- Inicialmente, insira o numero de threads\nR: ";
        cin >> numThreads;
        numThreads = static_cast<int>(numThreads);

        if(numThreads < 1){
            cout << "\n-_- Nao podemos ter menos de uma thread!\n\n";
        }
    }

    if (numThreads > 1){    //Escolhemos se vai ser síncrono ou não
        while(sincrono != 0 && sincrono != 1){
            cout << "\n-_- Com ou sem sincronizacao?\n[1] Com\n[0] Sem\nR: ";
            cin >> sincrono;

            if(sincrono != 0 && sincrono != 1){
                cout << "\n-_- Escolha 0 ou 1!\n\n";
            }
        }
    }

    //cout << endl << endl;

    //Agora, devemos popular cada vetor. Cada vetor vai ser uma "fila de funcionários" que vai ficar em cada
    //  máquina de ponto, batendo o ponto em intervalos de tempo aleatórios.
    
    //Armazenamos tudo em uma matriz (vector de vectors). Daí cada linha é passada para cada máquina de ponto

    //Definição da matriz:
    // Cada fila vem com tamanhoFila pessoas, cada um com sua ID gerada randomicamente.
    vector<vector<int>> matriz(numThreads, vector<int>(tamanhoFila, 0));

    for (int i = 0; i < numThreads; i++){
        for (int j = 0; j < tamanhoFila; j++){
            matriz[i][j] = rand();
        }
    }

    //for (int i = 0; i < numThreads; i++){
    //    for (int j = 0; j < tamanhoFila; j++){
    //        cout << matriz[i][j] << " ";
    //    }
    //    cout << endl;
    //}
    //cout << endl << endl;
    auto t_inicio = std::chrono::high_resolution_clock::now();

    //Aqui iniciamos e executamos cada thread, de acordo com a escolha do usuário:
    if (numThreads == 1){   //Sequencial
        t_inicio = std::chrono::high_resolution_clock::now();
        for(int i = 0; i < numThreads; i++){
            maquinaPontoSequencial(matriz[i], Arquivo);
        }
    }else{

        vector<std::thread> threads;    //Vetor para aramzenar as threads criadas dinamicamente


        if(sincrono == 1){  //Multithread com sincronização
            t_inicio = std::chrono::high_resolution_clock::now();
            for(int i = 0; i < numThreads; i++){    //Thredas dinâmicas
                threads.emplace_back(maquinaPontoSincrona, std::cref(matriz[i]), std::ref(Arquivo));
            }
        }else{              //Nultithread sem sincronização
            t_inicio = std::chrono::high_resolution_clock::now();
            for(int i = 0; i < numThreads; i++){
                threads.emplace_back(maquinaPontoSequencial, std::cref(matriz[i]), std::ref(Arquivo));
            }
        }
    
        for (auto &thread : threads){   //Join nas threads dinâmicas
            thread.join();
        }
    
    }

    auto t_fim = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duracao = t_fim - t_inicio;

    Arquivo << "Duracao: ";
    Arquivo << to_string(duracao.count());
    Arquivo << " Milissegundos";

    Arquivo.close();

    return 0;
}