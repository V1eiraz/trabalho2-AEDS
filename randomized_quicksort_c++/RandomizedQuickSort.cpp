#include "RandomizedQuickSort.hpp"
#include <algorithm>  // std::swap

// ─────────────────────────────────────────────────────────────────────────────
// Construtor
//
// Inicializa o gerador Mersenne Twister com seed fixa 67.
// Isso garante que a sequência de pivôs aleatórios seja idêntica
// em toda execução, tornando o experimento reprodutível.
// ─────────────────────────────────────────────────────────────────────────────
RandomizedQuickSort::RandomizedQuickSort() : rng_(67) {}

// ─────────────────────────────────────────────────────────────────────────────
// name
// ─────────────────────────────────────────────────────────────────────────────
std::string RandomizedQuickSort::name() const {
    return "RandomizedQuickSort";
}

// ─────────────────────────────────────────────────────────────────────────────
// sort  (ponto de entrada público)
//
// Verifica o caso trivial e delega para a recursão interna.
// ─────────────────────────────────────────────────────────────────────────────
void RandomizedQuickSort::sort(std::vector<int>& arr) {
    if (arr.size() <= 1) return;
    quickSort(arr, 0, static_cast<int>(arr.size()) - 1);
}

// ─────────────────────────────────────────────────────────────────────────────
// randomPivot
//
// Sorteia um índice aleatório entre low e high (inclusive),
// move o elemento desse índice para a última posição (high)
// e retorna o valor do pivô.
//
// Mover para high é uma convenção: o partition sempre espera
// o pivô em arr[high].
// ─────────────────────────────────────────────────────────────────────────────
int RandomizedQuickSort::randomPivot(std::vector<int>& arr, int low, int high) {
    std::uniform_int_distribution<int> dist(low, high);
    int randomIndex = dist(rng_);
    std::swap(arr[randomIndex], arr[high]);
    return arr[high];
}

// ─────────────────────────────────────────────────────────────────────────────
// partition
//
// Esquema de particionamento de Lomuto:
//   - O pivô fica em arr[high] (posto ali por randomPivot).
//   - 'i' rastreia a fronteira entre elementos menores e maiores.
//   - Ao final, o pivô é colocado em sua posição definitiva.
//
// Retorna o índice final do pivô.
// ─────────────────────────────────────────────────────────────────────────────
int RandomizedQuickSort::partition(std::vector<int>& arr, int low, int high) {
    int pivot = randomPivot(arr, low, high);

    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }

    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

// ─────────────────────────────────────────────────────────────────────────────
// quickSort  (recursivo)
//
// Divide o subvetor em duas partes a partir do pivô e ordena cada
// parte recursivamente.
// ─────────────────────────────────────────────────────────────────────────────
void RandomizedQuickSort::quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pivotPos = partition(arr, low, high);
        quickSort(arr, low, pivotPos - 1);
        quickSort(arr, pivotPos + 1, high);
    }
}