#ifndef SORTER_HPP
#define SORTER_HPP

#include <vector>
#include <string>

// Classe base abstrata para algoritmos de ordenação.
// Define a interface comum que qualquer algoritmo deverá implementar.
class Sorter {
public:
    virtual void sort(std::vector<int>& arr) = 0;
    virtual std::string name() const = 0;
    virtual ~Sorter() = default;
};

#endif