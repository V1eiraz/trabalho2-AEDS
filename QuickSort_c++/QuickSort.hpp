#ifndef QUICKSORT_HPP
#define QUICKSORT_HPP

#include "Sorter.hpp"
#include <vector>
#include <string>
#include <random>   // std::mt19937

// ─────────────────────────────────────────────────────────────────────────────
// Classe QuickSort
//
// Implementa o algoritmo QuickSort com seleção de pivô pela
// Mediana de Três Aleatória (Random Median-of-Three).
//
// Herda de Sorter (interface abstrata), respeitando o princípio
// de polimorfismo — o benchmark em main.cpp trabalha com Sorter*
// sem precisar conhecer os detalhes desta classe.
//
// A implementação dos métodos está em QuickSort.cpp.
// ─────────────────────────────────────────────────────────────────────────────
class QuickSort : public Sorter {
public:

    // Inicializa o gerador Mersenne Twister com seed fixa 67
    // para garantir reprodutibilidade entre execuções.
    QuickSort();

    // Ponto de entrada público: ordena o vetor completo.
    void sort(std::vector<int>& arr) override;

    // Retorna o nome do algoritmo para identificação na saída.
    std::string name() const override;

private:

    // Gerador de números pseudoaleatórios (Mersenne Twister).
    // Usado por randomMedianOfThree para sortear os candidatos ao pivô.
    std::mt19937 rng_;

    // Sorteia três índices distintos em [low..high] e retorna
    // o índice cujo valor é a mediana dos três.
    int randomMedianOfThree(std::vector<int>& arr, int low, int high);

    // Particiona arr[low..high] em torno do pivô escolhido pela
    // mediana aleatória e retorna o índice final do pivô.
    int partition(std::vector<int>& arr, int low, int high);

    // Chamada recursiva principal do QuickSort.
    void quickSort(std::vector<int>& arr, int low, int high);
};

#endif