/*
 * Quick Sort - Pivo pela Mediana de Tres Aleatorios
 * Seminario: Ordenacoes por Divisao Recursiva
 *
 * Compilar: make
 * Executar: ./executar.sh
 */

#include "QuickSort.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Uso: %s <arquivo> <tamanho>\n", argv[0]);
        fprintf(stderr, "Exemplo: %s input.dat 1000\n", argv[0]);
        return 1;
    }

    const char *nome_arquivo      = argv[1];
    int         quantidade_elementos = atoi(argv[2]);

    printf("n = %7d  |  arquivo = %s\n", quantidade_elementos, nome_arquivo);

    executar_benchmark(nome_arquivo, quantidade_elementos, 100);

    /* Gera output apenas para a entrada completa (1000000) com input.dat */
    if (quantidade_elementos == 1000000) {
        gerar_output_ordenado(nome_arquivo);
    }

    return 0;
}