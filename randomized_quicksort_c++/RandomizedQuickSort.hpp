#ifndef RANDOMIZED_QUICKSORT_HPP
#define RANDOMIZED_QUICKSORT_HPP

#include "Sorter.hpp"
#include <vector>
#include <string>
#include <algorithm>   // std::swap
#include <random>      // std::mt19937, std::uniform_int_distribution

// ─────────────────────────────────────────────────────────────────────────────
// Classe RandomizedQuickSort
//
// Implementa o QuickSort com seleção de pivô ALEATÓRIA.
//
// Diferença em relação ao QuickSort clássico (mediana de três):
//   - Em vez de escolher o pivô com base nos valores de três posições fixas,
//     sorteia aleatoriamente UM índice dentro do subvetor atual e usa o valor
//     desse índice como pivô.
//
// Por que isso é útil?
//   - O QuickSort com pivô fixo (ex: sempre o último elemento) degrada para
//     O(n²) em arrays já ordenados ou quase ordenados.
//   - A aleatoriedade elimina qualquer padrão de entrada que possa causar
//     esse pior caso — na média, o desempenho se mantém O(n log n)
//     independentemente da disposição dos dados.
//
// O gerador de números aleatórios (mt19937) é inicializado UMA VEZ
// no construtor com uma semente baseada no relógio do sistema,
// garantindo sequências diferentes a cada execução.
// ─────────────────────────────────────────────────────────────────────────────
class RandomizedQuickSort : public Sorter {
public:

    // Inicializa o gerador de números aleatórios com semente do sistema.
    // random_device coleta entropia real do SO (não é pseudo-aleatório).
    RandomizedQuickSort() : rng_(std::random_device{}()) {}

    void sort(std::vector<int>& arr) override {
        if (arr.size() <= 1) return;
        quickSort(arr, 0, static_cast<int>(arr.size()) - 1);
    }

    std::string name() const override {
        return "RandomizedQuickSort";
    }

private:

    // Gerador Mersenne Twister — padrão da indústria para pseudo-aleatoriedade
    // rápida e de boa qualidade estatística.
    std::mt19937 rng_;

    // ─────────────────────────────────────────────────────────────────────
    // randomPivot
    //
    // Sorteia um índice aleatório entre low e high (inclusive),
    // move o elemento desse índice para a última posição (high)
    // e retorna o valor do pivô.
    //
    // Mover para high é uma convenção: o restante do partition
    // sempre espera o pivô em arr[high].
    // ─────────────────────────────────────────────────────────────────────
    int randomPivot(std::vector<int>& arr, int low, int high) {
        std::uniform_int_distribution<int> dist(low, high);
        int randomIndex = dist(rng_);
        std::swap(arr[randomIndex], arr[high]);
        return arr[high];
    }

    // ─────────────────────────────────────────────────────────────────────
    // partition
    //
    // Esquema de particionamento de Lomuto:
    //   - O pivô fica em arr[high] (posto ali por randomPivot).
    //   - 'i' rastreia a fronteira entre elementos menores e maiores.
    //   - Ao final, o pivô é colocado em sua posição definitiva.
    //
    // Retorna o índice final do pivô.
    // ─────────────────────────────────────────────────────────────────────
    int partition(std::vector<int>& arr, int low, int high) {
        int pivot = randomPivot(arr, low, high);

        int i = low - 1;

        for (int j = low; j < high; j++) {
            if (arr[j] <= pivot) {
                i++;
                std::swap(arr[i], arr[j]);
            }
        }

        // Coloca o pivô entre as duas partições
        std::swap(arr[i + 1], arr[high]);
        return i + 1;
    }

    // ─────────────────────────────────────────────────────────────────────
    // quickSort  (recursivo)
    // ─────────────────────────────────────────────────────────────────────
    void quickSort(std::vector<int>& arr, int low, int high) {
        if (low < high) {
            int pivotPos = partition(arr, low, high);
            quickSort(arr, low, pivotPos - 1);
            quickSort(arr, pivotPos + 1, high);
        }
    }
};

#endif