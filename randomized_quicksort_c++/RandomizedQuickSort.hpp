#ifndef RANDOMIZED_QUICKSORT_HPP
#define RANDOMIZED_QUICKSORT_HPP

#include "Sorter.hpp"
#include <vector>
#include <string>
#include <random>   // std::mt19937

// ─────────────────────────────────────────────────────────────────────────────
// Classe RandomizedQuickSort
//
// Implementa o QuickSort com seleção de pivô ALEATÓRIA pura.
//
// Diferença em relação ao QuickSort (mediana de três):
//   - Sorteia aleatoriamente UM índice dentro do subvetor e usa o valor
//     desse índice como pivô, sem considerar os valores dos vizinhos.
//
// Por que isso é útil?
//   - Elimina qualquer padrão de entrada que possa causar o pior caso
//     O(n²), mantendo O(n log n) esperado independentemente dos dados.
//
// Herda de Sorter (interface abstrata).
// A implementação dos métodos está em RandomizedQuickSort.cpp.
// ─────────────────────────────────────────────────────────────────────────────
class RandomizedQuickSort : public Sorter {
public:

    // Inicializa o gerador Mersenne Twister com seed fixa 67
    // para garantir reprodutibilidade entre execuções.
    RandomizedQuickSort();

    // Ponto de entrada público: ordena o vetor completo.
    void sort(std::vector<int>& arr) override;

    // Retorna o nome do algoritmo para identificação na saída.
    std::string name() const override;

private:

    // Gerador de números pseudoaleatórios (Mersenne Twister).
    std::mt19937 rng_;

    // Sorteia um índice aleatório em [low..high], move o elemento
    // para arr[high] e retorna o valor do pivô.
    int randomPivot(std::vector<int>& arr, int low, int high);

    // Particiona arr[low..high] em torno do pivô (esquema de Lomuto)
    // e retorna o índice final do pivô.
    int partition(std::vector<int>& arr, int low, int high);

    // Chamada recursiva principal do QuickSort.
    void quickSort(std::vector<int>& arr, int low, int high);
};

#endif