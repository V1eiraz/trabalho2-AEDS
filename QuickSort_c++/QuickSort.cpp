#include "QuickSort.hpp"
#include <algorithm>  // std::swap


QuickSort::QuickSort() : rng_(67) {}

std::string QuickSort::name() const {
    return "QuickSort (Median-of-Three)";
}

void QuickSort::sort(std::vector<int>& arr) {
    if (arr.size() <= 1) return;
    quickSort(arr, 0, static_cast<int>(arr.size()) - 1);
}

// randomMedianOfThree
// Sorteia três índices DISTINTOS aleatoriamente dentro do subvetor
// [low..high] e retorna o índice cujo valor é a mediana dos três.

int QuickSort::randomMedianOfThree(std::vector<int>& arr, int low, int high) {
    std::uniform_int_distribution<int> dist(low, high);

    int ia = dist(rng_);

    int ib;
    do { ib = dist(rng_); } while (ib == ia);

    int ic;
    do { ic = dist(rng_); } while (ic == ia || ic == ib);

    int va = arr[ia], vb = arr[ib], vc = arr[ic];

    if ((va <= vb && vb <= vc) || (vc <= vb && vb <= va)) return ib;
    if ((vb <= va && va <= vc) || (vc <= va && va <= vb)) return ia;
    return ic;
}

// partition
// Rearranja os elementos de arr[low..high] em torno do pivô:
//   - elementos menores ou iguais ao pivô ficam à esquerda
//   - elementos maiores ficam à direita
//   - o pivô é colocado em sua posição final
int QuickSort::partition(std::vector<int>& arr, int low, int high) {
    if (high - low < 2) {
        if (arr[low] > arr[high])
            std::swap(arr[low], arr[high]);
        return low;
    }

    int pivotIndex = randomMedianOfThree(arr, low, high);
    int pivotValue = arr[pivotIndex];

    std::swap(arr[pivotIndex], arr[high]);

    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivotValue) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }

    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

// quickSort  (recursivo)
// Divide o subvetor em duas partes a partir do pivô e ordena cada
// parte recursivamente.
void QuickSort::quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pivotPos = partition(arr, low, high);
        quickSort(arr, low, pivotPos - 1);
        quickSort(arr, pivotPos + 1, high);
    }
}