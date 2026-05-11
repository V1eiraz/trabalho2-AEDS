#ifndef BENCHMARK_HPP
#define BENCHMARK_HPP

#include "Sorter.hpp"
#include "DataLoader.hpp"
#include <vector>
#include <string>


// Agrupa as funções responsáveis por medir o desempenho de um algoritmo
// de ordenação: tempo médio sobre N repetições.

// Executa uma única ordenação e retorna o tempo em milissegundos.
double runSingleSort(Sorter* sorter, std::vector<int>& data);

void runExperiment(Sorter* sorter, const DataLoader& loader, size_t n, int repetitions = 100);

#endif