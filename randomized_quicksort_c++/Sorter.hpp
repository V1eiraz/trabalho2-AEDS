#ifndef SORTER_HPP
#define SORTER_HPP

#include <vector>
#include <string>

class Sorter {
public:
    virtual void sort(std::vector<int>& arr) = 0;
    virtual std::string name() const = 0;
    virtual ~Sorter() = default;
};

#endif