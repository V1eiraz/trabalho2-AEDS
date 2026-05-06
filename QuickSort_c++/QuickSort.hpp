#ifndef QUICKSORT_HPP
#define QUICKSORT_HPP

#include "Sorter.hpp"
#include <vector>
#include <string>
#include <algorithm>  // std::swap

// ─────────────────────────────────────────────────────────────────────────────
// Classe QuickSort
//
// Implementa o algoritmo QuickSort clássico com seleção de pivô
// pelo método da Mediana de Três (Median-of-Three).
//
// Herda da classe base Sorter, respeitando o princípio de polimorfismo.
// ─────────────────────────────────────────────────────────────────────────────
class QuickSort : public Sorter {
public:

    // Ponto de entrada público: ordena o vetor completo.
    void sort(std::vector<int>& arr) override {
        if (arr.size() <= 1) return;
        quickSort(arr, 0, static_cast<int>(arr.size()) - 1);
    }

    std::string name() const override {
        return "QuickSort (Median-of-Three)";
    }

private:

    // ─────────────────────────────────────────────────────────────────────
    // medianOfThree
    //
    // Recebe os índices esquerdo (low), central (mid) e direito (high).
    // Compara os três valores correspondentes no array e retorna o ÍNDICE
    // do elemento cujo VALOR é a mediana (o do meio quando ordenados).
    //
    // Exemplo:
    //   arr[low]=10, arr[mid]=3, arr[high]=15
    //   Valores ordenados conceitualmente: 3, 10, 15
    //   Mediana = 10  →  retorna o índice low (pois arr[low]=10 é o valor do meio)
    //
    // Além de identificar a mediana, esta função já REPOSICIONA os três
    // elementos de forma que:
    //   arr[low]  <= arr[mid]   (menor ou igual ao meio)
    //   arr[mid]  <= arr[high]  (meio menor ou igual ao maior)
    // Isso serve como uma mini-ordenação dos três candidatos.
    // ─────────────────────────────────────────────────────────────────────
    int medianOfThree(std::vector<int>& arr, int low, int mid, int high) {

        // Passo 1: garantir que arr[low] <= arr[mid]
        if (arr[low] > arr[mid])
            std::swap(arr[low], arr[mid]);

        // Passo 2: garantir que arr[low] <= arr[high]
        if (arr[low] > arr[high])
            std::swap(arr[low], arr[high]);

        // Passo 3: garantir que arr[mid] <= arr[high]
        if (arr[mid] > arr[high])
            std::swap(arr[mid], arr[high]);

        // Após os 3 passos: arr[low] <= arr[mid] <= arr[high]
        // O valor mediano está em arr[mid].
        return mid;
    }

    // ─────────────────────────────────────────────────────────────────────
    // partition
    //
    // Rearranja os elementos do subarray arr[low..high] em torno do pivô:
    //   - todos os elementos menores que o pivô ficam à esquerda;
    //   - todos os maiores ficam à direita;
    //   - o pivô é colocado em sua posição final.
    //
    // Retorna o índice final do pivô após o particionamento.
    //
    // Estratégia: o pivô é escolhido pela mediana de três e movido para
    // a posição arr[high-1] antes do loop principal (técnica clássica).
    // ─────────────────────────────────────────────────────────────────────
    int partition(std::vector<int>& arr, int low, int high) {

        // Para subvetores muito pequenos (2 ou 3 elementos), a mediana
        // de três já faz o trabalho de ordenar — tratamos como caso especial.
        if (high - low < 2) {
            if (arr[low] > arr[high])
                std::swap(arr[low], arr[high]);
            return low;  // pivô já está em posição correta
        }

        int mid = low + (high - low) / 2;

        // Escolhe o pivô pela mediana dos três candidatos e já os ordena
        // minimamente: arr[low] <= arr[mid] <= arr[high]
        int pivotIndex = medianOfThree(arr, low, mid, high);

        // Move o pivô para a posição high-1 para ficar fora do loop
        // de comparação (arr[low] e arr[high] já estão nos lugares certos)
        int pivotValue = arr[pivotIndex];
        std::swap(arr[pivotIndex], arr[high - 1]);

        // Índices que caminham de fora para dentro do subvetor
        int i = low;        // começa após arr[low] (que já é o menor dos 3)
        int j = high - 1;   // começa antes do pivô (que está em high-1)

        // Loop de particionamento: i avança até achar elemento >= pivô,
        // j recua até achar elemento <= pivô; quando i < j, troca-os.
        while (true) {
            while (arr[++i] < pivotValue) {}   // avança i
            while (arr[--j] > pivotValue) {}   // recua j

            if (i < j)
                std::swap(arr[i], arr[j]);
            else
                break;
        }

        // Restaura o pivô para sua posição final (entre as duas partições)
        std::swap(arr[i], arr[high - 1]);

        return i;  // índice final do pivô
    }

    // ─────────────────────────────────────────────────────────────────────
    // quickSort  (recursivo)
    //
    // Divide o subarray em duas partes a partir do pivô e ordena cada
    // parte recursivamente. É a "espinha dorsal" do algoritmo.
    // ─────────────────────────────────────────────────────────────────────
    void quickSort(std::vector<int>& arr, int low, int high) {
        if (low < high) {
            int pivotPos = partition(arr, low, high);
            quickSort(arr, low, pivotPos - 1);   // ordena parte esquerda
            quickSort(arr, pivotPos + 1, high);  // ordena parte direita
        }
    }
};

#endif