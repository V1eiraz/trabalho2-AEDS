#ifndef QUICKSORT_HPP
#define QUICKSORT_HPP

#include "Sorter.hpp"
#include <vector>
#include <string>
#include <random>   // std::mt19937


class QuickSort : public Sorter {
public:

    QuickSort();

    void sort(std::vector<int>& arr) override;

    std::string name() const override;

private:

    std::mt19937 rng_;

    int randomMedianOfThree(std::vector<int>& arr, int low, int high);

    int partition(std::vector<int>& arr, int low, int high);

    void quickSort(std::vector<int>& arr, int low, int high);
};

#endif