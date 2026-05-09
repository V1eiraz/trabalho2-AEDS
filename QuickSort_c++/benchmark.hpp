#ifndef BENCHMARK_HPP
#define BENCHMARK_HPP

#include "Sorter.hpp"
#include <string>

// ─────────────────────────────────────────────────────────────────────────────
// Benchmark
//
// Agrupa as funções responsáveis por medir o desempenho de um algoritmo
// de ordenação: tempo médio sobre N repetições e memória teórica usada.
//
// A leitura do arquivo de entrada também é responsabilidade deste módulo —
// não há dependência de DataLoader.
//
// A implementação está em Benchmark.cpp.
// ─────────────────────────────────────────────────────────────────────────────

// Executa uma única ordenação e retorna o tempo em milissegundos.
double runSingleSort(Sorter* sorter, std::vector<int>& data);

// Lê os primeiros 'n' inteiros do arquivo e os retorna como vetor.
std::vector<int> loadData(const std::string& filePath, size_t n);

// Executa 'repetitions' rodadas para o tamanho 'n', imprime
// tempo médio e memória ao final.
void runExperiment(Sorter* sorter, const std::string& filePath, size_t n, int repetitions = 100);

#endif