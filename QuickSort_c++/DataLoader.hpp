#ifndef DATALOADER_HPP
#define DATALOADER_HPP

#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>

// ─────────────────────────────────────────────────────────────────────────────
// Classe DataLoader
//
// Responsável por carregar os dados do arquivo de entrada.
// Em vez de ler o arquivo inteiro toda vez, lê apenas os primeiros N
// elementos — permitindo simular os diferentes tamanhos de entrada
// (10², 10³, 10⁴, 10⁵, 10⁶) a partir de um único arquivo.
// ─────────────────────────────────────────────────────────────────────────────
class DataLoader {
public:

    // Construtor: recebe o caminho do arquivo de entrada
    explicit DataLoader(const std::string& filePath) : filePath_(filePath) {}

    // ─────────────────────────────────────────────────────────────────────
    // load
    //
    // Lê os primeiros 'n' inteiros do arquivo e os retorna como vetor.
    //
    // O arquivo é reaberto do início a cada chamada, portanto chamadas
    // consecutivas com n=100, n=1000, etc. são independentes.
    //
    // Lança std::runtime_error se o arquivo não puder ser aberto ou se
    // não houver elementos suficientes.
    // ─────────────────────────────────────────────────────────────────────
    std::vector<int> load(size_t n) const {
        std::ifstream file(filePath_);
        if (!file.is_open())
            throw std::runtime_error("Nao foi possivel abrir o arquivo: " + filePath_);

        std::vector<int> data;
        data.reserve(n);   // aloca memória antecipadamente para evitar realocações

        int value;
        while (data.size() < n && file >> value) {
            data.push_back(value);
        }

        if (data.size() < n) {
            throw std::runtime_error(
                "Arquivo com elementos insuficientes. Pedido: " +
                std::to_string(n) + ", encontrado: " + std::to_string(data.size())
            );
        }

        return data;
    }

private:
    std::string filePath_;
};

#endif