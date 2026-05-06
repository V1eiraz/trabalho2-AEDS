#include <iostream>
#include <iomanip>
#include <vector>
#include <numeric>     // std::accumulate

#include "Sorter.hpp"
#include "RandomizedQuickSort.hpp"
#include "DataLoader.hpp"
#include "Timer.hpp"

// ─────────────────────────────────────────────────────────────────────────────
// runBenchmark
//
// Para um dado tamanho de entrada:
//   1. Repete o experimento 'runs' vezes
//   2. A cada rodada: carrega os dados frescos do arquivo, ordena, mede o tempo
//   3. Ao final, calcula e exibe a média dos tempos
//
// Os dados são recarregados a cada rodada para garantir que o algoritmo
// sempre ordena um array desordenado — se reutilizássemos o mesmo vetor,
// da segunda rodada em diante estaríamos medindo o tempo de ordenar um
// array já ordenado, o que distorceria os resultados.
// ─────────────────────────────────────────────────────────────────────────────
void runBenchmark(Sorter* sorter, const DataLoader& loader, size_t n, int runs) {

    std::vector<double> times;
    times.reserve(runs);

    for (int i = 0; i < runs; i++) {
        std::vector<int> data = loader.load(n);

        Timer timer;
        timer.start();
        sorter->sort(data);
        timer.stop();

        times.push_back(timer.elapsedMilliseconds());
    }

    double total = std::accumulate(times.begin(), times.end(), 0.0);
    double mean  = total / runs;

    std::cout << std::left
              << std::setw(24) << sorter->name()
              << " | n = " << std::setw(10) << n
              << " | Media (" << runs << " runs): "
              << std::fixed << std::setprecision(4)
              << mean << " ms"
              << std::endl;
}

int main() {

    std::string filePath = "input.dat";

    DataLoader loader(filePath);

    std::vector<size_t> inputSizes = {100, 1000, 10000, 100000, 1000000};

    RandomizedQuickSort rqs;

    std::cout << "========================================================" << std::endl;
    std::cout << "   Experimento: RandomizedQuickSort"                      << std::endl;
    std::cout << "   Arquivo de entrada: " << filePath                      << std::endl;
    std::cout << "========================================================" << std::endl;
    std::cout << std::endl;

    for (size_t n : inputSizes) {
        try {
            // Para n=1000000 reduz para 10 repetições (evita espera muito longa)
            int runs = (n == 1000000) ? 10 : 100;
            runBenchmark(&rqs, loader, n, runs);
        } catch (const std::exception& e) {
            std::cerr << "[ERRO] n=" << n << ": " << e.what() << std::endl;
        }
    }

    std::cout << std::endl;
    std::cout << "Experimento concluido." << std::endl;

    return 0;
}