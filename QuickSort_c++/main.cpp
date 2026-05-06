#include <iostream>
#include <iomanip>
#include <vector>

#include "Sorter.hpp"
#include "QuickSort.hpp"
#include "DataLoader.hpp"
#include "Timer.hpp"

// ─────────────────────────────────────────────────────────────────────────────
// runSingleSort
//
// Executa uma única ordenação e retorna o tempo em milissegundos
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
// Executa um experimento múltiplas vezes (repetições) para um dado algoritmo 
// e tamanho de entrada, calculando a média dos tempos:
//   1. Para cada repetição:
//      - Carrega os primeiros 'n' elementos do arquivo via DataLoader
//      - Executa o algoritmo de ordenação
//      - Acumula o tempo
//   2. Calcula a média e imprime o resultado
//
// Parâmetros:
//   sorter      — ponteiro para qualquer objeto que implemente Sorter
//   loader      — objeto que lê o arquivo de entrada
//   n           — quantidade de elementos a ordenar
//   repetitions — número de vezes a executar (padrão: 100)
// ─────────────────────────────────────────────────────────────────────────────
void runExperiment(Sorter* sorter, const DataLoader& loader, size_t n, int repetitions = 100) {
    double totalTime = 0.0;
    
    for (int i = 0; i < repetitions; ++i) {
        try {
            // Carrega uma CÓPIA dos dados
            std::vector<int> data = loader.load(n);
            totalTime += runSingleSort(sorter, data);
        } catch (const std::exception& e) {
            std::cerr << "[ERRO] n=" << n << " (repetição " << i+1 << "): " << e.what() << std::endl;
            return;
        }
    }
    
    double averageTime = totalTime / repetitions;
    
    // Formatação da saída: nome do algoritmo, tamanho, tempo médio
    std::cout << std::left
              << std::setw(32) << sorter->name()
              << " | n = " << std::setw(10) << n
              << " | Tempo médio: "
              << std::fixed << std::setprecision(4)
              << averageTime << " ms"
              << "  (" << averageTime / 1000.0 << " s)"
              << " [" << repetitions << " runs]"
              << std::endl;
}

// ─────────────────────────────────────────────────────────────────────────────
// main
// ─────────────────────────────────────────────────────────────────────────────
int main() {

    std::string filePath = "input.dat";

    DataLoader loader(filePath);

    // Tamanhos de entrada exigidos pelo trabalho
    std::vector<size_t> inputSizes = {100, 1000, 10000, 100000, 1000000};

    // Instância do algoritmo (pode adicionar outros aqui futuramente)
    QuickSort qs;

    std::cout << "========================================================" << std::endl;
    std::cout << "   Experimento: Algoritmos de Ordenacao" << std::endl;
    std::cout << "   Arquivo de entrada: " << filePath << std::endl;
    std::cout << "========================================================" << std::endl;
    std::cout << std::endl;

    for (size_t n : inputSizes) {
        try {
            runExperiment(&qs, loader, n);
        } catch (const std::exception& e) {
            std::cerr << "[ERRO] n=" << n << ": " << e.what() << std::endl;
        }
    }

    std::cout << std::endl;
    std::cout << "Experimento concluido." << std::endl;

    return 0;
}