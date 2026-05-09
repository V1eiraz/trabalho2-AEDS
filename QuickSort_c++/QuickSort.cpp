#include "QuickSort.hpp"
#include <algorithm>  // std::swap

// ─────────────────────────────────────────────────────────────────────────────
// Construtor
//
// Inicializa o gerador Mersenne Twister com seed fixa 67.
// Isso garante que a sequência de pivôs aleatórios seja idêntica
// em toda execução, tornando o experimento reprodutível.
// ─────────────────────────────────────────────────────────────────────────────
QuickSort::QuickSort() : rng_(67) {}

// ─────────────────────────────────────────────────────────────────────────────
// name
// ─────────────────────────────────────────────────────────────────────────────
std::string QuickSort::name() const {
    return "QuickSort (Median-of-Three)";
}

// ─────────────────────────────────────────────────────────────────────────────
// sort  (ponto de entrada público)
//
// Verifica o caso trivial e delega para a recursão interna.
// ─────────────────────────────────────────────────────────────────────────────
void QuickSort::sort(std::vector<int>& arr) {
    if (arr.size() <= 1) return;
    quickSort(arr, 0, static_cast<int>(arr.size()) - 1);
}

// ─────────────────────────────────────────────────────────────────────────────
// randomMedianOfThree
//
// Sorteia três índices DISTINTOS aleatoriamente dentro do subvetor
// [low..high] e retorna o índice cujo valor é a mediana dos três.
//
// Por que aleatório?
//   Com posições fixas (left, mid, right), entradas já ordenadas ou
//   inversamente ordenadas podem degradar o particionamento.
//   Sorteando os candidatos, eliminamos qualquer padrão de entrada
//   que explore essa fragilidade, mantendo O(n log n) esperado.
//
// Por que seed 67?
//   Garante a mesma sequência de sorteios em toda execução,
//   tornando o experimento reprodutível.
// ─────────────────────────────────────────────────────────────────────────────
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

// ─────────────────────────────────────────────────────────────────────────────
// partition
//
// Rearranja os elementos de arr[low..high] em torno do pivô:
//   - elementos menores ou iguais ao pivô ficam à esquerda
//   - elementos maiores ficam à direita
//   - o pivô é colocado em sua posição final
//
// Retorna o índice final do pivô após o particionamento.
// ─────────────────────────────────────────────────────────────────────────────
int QuickSort::partition(std::vector<int>& arr, int low, int high) {
    // Caso especial: subvetor com apenas 2 elementos
    if (high - low < 2) {
        if (arr[low] > arr[high])
            std::swap(arr[low], arr[high]);
        return low;
    }

    // Escolhe o pivô pela mediana de três índices aleatórios
    int pivotIndex = randomMedianOfThree(arr, low, high);
    int pivotValue = arr[pivotIndex];

    // Move o pivô para o final para ficar fora do loop de comparação
    std::swap(arr[pivotIndex], arr[high]);

    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivotValue) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }

    // Restaura o pivô para sua posição final
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

// ─────────────────────────────────────────────────────────────────────────────
// quickSort  (recursivo)
//
// Divide o subvetor em duas partes a partir do pivô e ordena cada
// parte recursivamente.
// ─────────────────────────────────────────────────────────────────────────────
void QuickSort::quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pivotPos = partition(arr, low, high);
        quickSort(arr, low, pivotPos - 1);
        quickSort(arr, pivotPos + 1, high);
    }
}