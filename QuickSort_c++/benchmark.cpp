#include "benchmark.hpp"
#include "Timer.hpp"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdexcept>

// ─────────────────────────────────────────────────────────────────────────────
// loadData
//
// Lê os primeiros 'n' inteiros do arquivo e os retorna como vetor.
// O arquivo é reaberto do início a cada chamada, portanto chamadas
// consecutivas com n=100, n=1000, etc. são independentes.
//
// Lança std::runtime_error se o arquivo não puder ser aberto ou se
// não houver elementos suficientes.
// ─────────────────────────────────────────────────────────────────────────────
std::vector<int> loadData(const std::string& filePath, size_t n) {
    std::ifstream file(filePath);
    if (!file.is_open())
        throw std::runtime_error("Nao foi possivel abrir o arquivo: " + filePath);

    std::vector<int> data;
    data.reserve(n);

    int value;
    while (data.size() < n && file >> value)
        data.push_back(value);

    if (data.size() < n)
        throw std::runtime_error(
            "Arquivo com elementos insuficientes. Pedido: " +
            std::to_string(n) + ", encontrado: " + std::to_string(data.size())
        );

    return data;
}

// ─────────────────────────────────────────────────────────────────────────────
// runSingleSort
//
// Executa uma única ordenação e retorna o tempo em milissegundos.
// ─────────────────────────────────────────────────────────────────────────────
double runSingleSort(Sorter* sorter, std::vector<int>& data) {
    Timer timer;
    timer.start();
    sorter->sort(data);
    timer.stop();
    return timer.elapsedMilliseconds();
}

// ─────────────────────────────────────────────────────────────────────────────
// runExperiment
//
// Executa 'repetitions' rodadas para o tamanho 'n':
//   1. A cada rodada: carrega os primeiros 'n' elementos do arquivo,
//      executa a ordenação e acumula o tempo.
//   2. Imprime o tempo médio ao final.
//
// A memória é medida externamente pelo GNU Time no executar.sh,
// que roda um processo separado por (arquivo x tamanho) para que
// o pico seja individual e não acumulado.
// ─────────────────────────────────────────────────────────────────────────────
void runExperiment(Sorter* sorter, const std::string& filePath, size_t n, int repetitions) {
    double totalTime = 0.0;

    for (int i = 0; i < repetitions; ++i) {
        try {
            std::vector<int> data = loadData(filePath, n);
            totalTime += runSingleSort(sorter, data);
        } catch (const std::exception& e) {
            std::cerr << "[ERRO] n=" << n << " (repeticao " << i+1 << "): " << e.what() << std::endl;
            return;
        }
    }

    double averageTime = totalTime / repetitions;

    std::cout << std::left
              << std::setw(32) << sorter->name()
              << " | n = "     << std::setw(10) << n
              << " | Tempo medio: "
              << std::fixed    << std::setprecision(4)
              << averageTime   << " ms"
              << "  ("         << averageTime / 1000.0 << " s)"
              << " ["          << repetitions << " runs]"
              << std::endl;
}