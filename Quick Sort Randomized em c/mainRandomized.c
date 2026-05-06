/*
 * Randomized Quick Sort - Pivo Aleatorio (seed 67)
 * Seminario: Ordenacoes por Divisao Recursiva
 *
 * Compilar: make
 * Executar: make run
 */

#include "RandomizedQuickSort.h"

int main() {
    printf("==============================================\n");
    printf("  Randomized Quick Sort - Pivo Aleatorio (C)\n");
    printf("  Seed: 67\n");
    printf("==============================================\n");

    int tamanhos_entrada[]       = {100,  1000, 10000, 100000, 1000000};
    int repeticoes_por_tamanho[] = {1000,  500,   250,    100,      50};
    int numero_tamanhos = sizeof(tamanhos_entrada) / sizeof(tamanhos_entrada[0]);

    for (int i = 0; i < numero_tamanhos; i++) {
        executar_benchmark(tamanhos_entrada[i], repeticoes_por_tamanho[i]);
    }

    printf("==============================================\n");

    gerar_output_ordenado();

    return 0;
}