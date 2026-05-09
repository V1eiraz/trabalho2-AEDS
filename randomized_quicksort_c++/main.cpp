#include <iostream>
#include <string>
#include <cstdlib>
#include "RandomizedQuickSort.hpp"
#include "DataLoader.hpp"
#include "benchmark.hpp"

// ─────────────────────────────────────────────────────────────────────────────
// main
//
// Recebe dois argumentos pela linha de comando:
//   argv[1] — caminho do arquivo de entrada  (ex: input.dat)
//   argv[2] — quantidade de elementos a ordenar (ex: 1000)
//
// Isso permite que o script executar.sh invoque o programa uma vez
// por combinação (arquivo x tamanho), de modo que o GNU Time meça
// o pico de memória de cada execução individualmente.
// ─────────────────────────────────────────────────────────────────────────────
int main(int argc, char* argv[]) {

    if (argc != 3) {
        std::cerr << "Uso: " << argv[0] << " <arquivo> <tamanho>" << std::endl;
        std::cerr << "Exemplo: " << argv[0] << " input.dat 1000" << std::endl;
        return 1;
    }

    std::string filePath = argv[1];
    size_t n = static_cast<size_t>(std::atoi(argv[2]));

    if (n == 0) {
        std::cerr << "[ERRO] Tamanho invalido: " << argv[2] << std::endl;
        return 1;
    }

    RandomizedQuickSort rqs;
    DataLoader loader(filePath);

    try {
        runExperiment(&rqs, loader, n);
    } catch (const std::exception& e) {
        std::cerr << "[ERRO] " << e.what() << std::endl;
        return 1;
    }

    return 0;
}