#ifndef DATALOADER_HPP
#define DATALOADER_HPP

#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>

class DataLoader {
public:

    // Construtor: recebe o caminho do arquivo de entrada
    explicit DataLoader(const std::string& filePath) : filePath_(filePath) {}

    // load
    // Lê os primeiros 'n' inteiros do arquivo e os retorna como vetor.

    std::vector<int> load(size_t n) const {
        std::ifstream file(filePath_);
        if (!file.is_open())
            throw std::runtime_error("Nao foi possivel abrir o arquivo: " + filePath_);

        std::vector<int> data;
        data.reserve(n);  

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