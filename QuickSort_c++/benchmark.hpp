#ifndef BENCHMARK_HPP
#define BENCHMARK_HPP

#include "Sorter.hpp"
#include "DataLoader.hpp"
#include <vector>
#include <string>

// Executa uma única ordenação e retorna o tempo em milissegundos.
double runSingleSort(Sorter* sorter, std::vector<int>& data);

// Executa 'repetitions' rodadas para o tamanho 'n', imprime
// tempo médio ao final.
void runExperiment(Sorter* sorter, const DataLoader& loader, size_t n, int repetitions = 100);

#endif