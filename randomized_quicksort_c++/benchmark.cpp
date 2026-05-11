#include "benchmark.hpp"
#include "Timer.hpp"
#include <iostream>
#include <iomanip>

// Executa uma única ordenação e retorna o tempo em milissegundos.
double runSingleSort(Sorter* sorter, std::vector<int>& data) {
    Timer timer;
    timer.start();
    sorter->sort(data);
    timer.stop();
    return timer.elapsedMilliseconds();
}

// Executa 'repetitions' rodadas para o tamanho 'n':
//   1. A cada rodada: usa o DataLoader para carregar os primeiros 'n'
//      elementos do arquivo, executa a ordenação e acumula o tempo.
//   2. Imprime o tempo médio ao final.
void runExperiment(Sorter* sorter, const DataLoader& loader, size_t n, int repetitions) {
    double totalTime = 0.0;

    for (int i = 0; i < repetitions; ++i) {
        try {
            std::vector<int> data = loader.load(n);
            totalTime += runSingleSort(sorter, data);
        } catch (const std::exception& e) {
            std::cerr << "[ERRO] n=" << n << " (repeticao " << i+1 << "): " << e.what() << std::endl;
            return;
        }
    }

    double averageTime = totalTime / repetitions;

    std::cout << std::left
              << std::setw(24) << sorter->name()
              << " | n = "     << std::setw(10) << n
              << " | Tempo medio: "
              << std::fixed    << std::setprecision(4)
              << averageTime   << " ms"
              << "  ("         << averageTime / 1000.0 << " s)"
              << " ["          << repetitions << " runs]"
              << std::endl;
}