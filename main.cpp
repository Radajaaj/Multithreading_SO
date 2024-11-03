#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <fstream>
#include <string>
#include <atomic>

// Mutex para controle de acesso ao arquivo
std::mutex fileMutex;

// Variável para indicar se o sistema está em uso
std::atomic<bool> emUso(false);

// Função para simular o registro de ponto
void registrarPonto(int id, char tecla) {
    while (true) {
        std::cout << "Pressione '" << tecla << "' para o Funcionário " << id << " registrar seu ponto ou 'S' para sair:\n";
        std::string comando;
        std::getline(std::cin, comando);

        if (comando == "S" || comando == "s") {
            std::cout << "Funcionário " << id << " saiu.\n";
            break; // Encerra o loop se o funcionário escolher sair
        }

        if (comando == std::string(1, tecla)) { // Verifica se a tecla correta foi pressionada
            if (emUso.exchange(true)) { // Tenta entrar em uso
                std::cout << "Arquivo já está em uso. Funcionário " << id << ", tente novamente mais tarde.\n";
                continue; // Retorna ao início do loop se o arquivo estiver em uso
            }

            std::this_thread::sleep_for(std::chrono::seconds(1)); // Espera 1 segundo antes de gravar

            // Lock do mutex para garantir acesso exclusivo ao arquivo
            {
                std::lock_guard<std::mutex> lock(fileMutex); // O mutex será liberado ao sair do escopo

                // Abre o arquivo de registro
                std::ofstream registro("registros.txt", std::ios::app);
                if (registro.is_open()) {
                    // Simula a gravação do ponto
                    std::string ponto = "Funcionário " + std::to_string(id) + " registrou ponto em " +
                                        std::to_string(std::time(nullptr)) + "\n";
                    registro << ponto;
                    std::cout << ponto;
                    registro.close();
                } else {
                    std::cerr << "Erro ao abrir o arquivo.\n";
                }
            }

            emUso = false; // Libera o uso após a gravação
        } else {
            std::cout << "Comando inválido. Tente novamente.\n";
        }
    }
}

int main() {
    // Cria uma thread para cada funcionário, passando a tecla correspondente
    std::thread funcionario1(registrarPonto, 1, '1');
    std::thread funcionario2(registrarPonto, 2, '2');
    std::thread funcionario3(registrarPonto, 3, '3');

    // Espera que todas as threads terminem
    funcionario1.join();
    funcionario2.join();
    funcionario3.join();

    std::cout << "Programa finalizado.\n";
    return 0;
}
