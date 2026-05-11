#ifndef RANDOMIZED_QUICKSORT_HPP
#define RANDOMIZED_QUICKSORT_HPP

#include "Sorter.hpp"
#include <vector>
#include <string>
#include <random>   


class RandomizedQuickSort : public Sorter {
public:

    RandomizedQuickSort();

    void sort(std::vector<int>& arr) override;

    std::string name() const override;

private:

    std::mt19937 rng_;

    int randomPivot(std::vector<int>& arr, int low, int high);

    // Particiona arr[low..high] em torno do pivô (esquema de Lomuto)
    // e retorna o índice final do pivô.
    int partition(std::vector<int>& arr, int low, int high);

    // Chamada recursiva principal do QuickSort.
    void quickSort(std::vector<int>& arr, int low, int high);
};

#endif