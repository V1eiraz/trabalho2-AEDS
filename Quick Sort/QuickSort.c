/*
 * Quick Sort - Pivo pela Mediana de Tres
 * Seminario: Ordenacoes por Divisao Recursiva
 *
 * Compilar: gcc -O0 -o QuickSort QuickSort.c
 * Executar: ./QuickSort input.dat
 */

#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* ─────────────────────────────────────────────
 * CALCULO DO TEMPO DECORRIDO
 *
 * Recebe dois instantes capturados com
 * clock_gettime e retorna a diferenca em
 * milissegundos com precisao de nanosegundos.
 * ───────────────────────────────────────────── */
double calcular_tempo_ms(struct timespec tempo_inicio, struct timespec tempo_fim) {
    return (tempo_fim.tv_sec  - tempo_inicio.tv_sec)  * 1000.0
         + (tempo_fim.tv_nsec - tempo_inicio.tv_nsec) / 1e6;
}

/* ─────────────────────────────────────────────
 * MEDIANA DE TRES
 *
 * Recebe o vetor e os indices do primeiro
 * elemento (indice_inicio), do meio
 * (indice_meio) e do ultimo (indice_fim)  
 * do subvetor atual.
 *
 * Compara os tres valores e retorna o INDICE
 * do elemento que possui o valor central.
 *
 * Exemplo:
 *   vetor[indice_inicio]=10
 *   vetor[indice_meio]=3
 *   vetor[indice_fim]=15
 *   Ordenados: 3, 10, 15 → mediana = 10
 *   Retorna: indice_inicio (pois seu valor e 10)
 * ───────────────────────────────────────────── */
int calcular_indice_mediana(int *vetor, int indice_inicio, int indice_meio, int indice_fim) {
    int valor_inicio = vetor[indice_inicio];
    int valor_meio   = vetor[indice_meio];
    int valor_fim    = vetor[indice_fim];

    if ((valor_inicio <= valor_meio && valor_meio <= valor_fim) ||
        (valor_fim    <= valor_meio && valor_meio <= valor_inicio))
        return indice_meio;

    if ((valor_meio <= valor_inicio && valor_inicio <= valor_fim) ||
        (valor_fim  <= valor_inicio && valor_inicio <= valor_meio))
        return indice_inicio;

    return indice_fim;
}

/* ─────────────────────────────────────────────
 * TROCA DE ELEMENTOS
 * ───────────────────────────────────────────── */
void trocar_elementos(int *elemento_a, int *elemento_b) {
    int valor_temporario = *elemento_a;
    *elemento_a = *elemento_b;
    *elemento_b = valor_temporario;
}

/* ─────────────────────────────────────────────
 * PARTICIONAR SUBVETOR
 *
 * 1. Calcula o indice do meio do subvetor.
 * 2. Escolhe o pivo pela mediana de tres.
 * 3. Move o pivo para a ultima posicao.
 * 4. Percorre o subvetor colocando elementos
 *    menores que o pivo a esquerda.
 * 5. Posiciona o pivo definitivamente.
 * 6. Retorna o indice final do pivo.
 * ───────────────────────────────────────────── */
int particionar(int *vetor, int indice_inicio, int indice_fim) {
    int indice_meio = indice_inicio + (indice_fim - indice_inicio) / 2;
    int indice_pivo = calcular_indice_mediana(vetor, indice_inicio, indice_meio, indice_fim);

    trocar_elementos(&vetor[indice_pivo], &vetor[indice_fim]);

    int valor_pivo = vetor[indice_fim];
    int indice_menor_direita = indice_inicio - 1;

    for (int indice_atual = indice_inicio; indice_atual < indice_fim; indice_atual++) {
        if (vetor[indice_atual] <= valor_pivo) {
            indice_menor_direita++;
            trocar_elementos(&vetor[indice_menor_direita], &vetor[indice_atual]);
        }
    }

    trocar_elementos(&vetor[indice_menor_direita + 1], &vetor[indice_fim]);
    return indice_menor_direita + 1;
}

/* ─────────────────────────────────────────────
 * QUICK SORT RECURSIVO
 * ───────────────────────────────────────────── */
void quick_sort(int *vetor, int indice_inicio, int indice_fim) {
    if (indice_inicio < indice_fim) {
        int indice_pivo_final = particionar(vetor, indice_inicio, indice_fim);
        quick_sort(vetor, indice_inicio, indice_pivo_final - 1);
        quick_sort(vetor, indice_pivo_final + 1, indice_fim);
    }
}

/* ─────────────────────────────────────────────
 * LEITURA DO ARQUIVO DE ENTRADA
 *
 * Le exatamente quantidade_elementos inteiros
 * do arquivo, independente de como estao
 * dispostos nas linhas.
 * Retorna 1 em sucesso, 0 em falha.
 * ───────────────────────────────────────────── */
int ler_arquivo_entrada(const char *nome_arquivo, int *vetor, int quantidade_elementos) {
    FILE *arquivo_entrada = fopen(nome_arquivo, "r");
    if (arquivo_entrada == NULL) {
        fprintf(stderr, "Erro: nao foi possivel abrir '%s'\n", nome_arquivo);
        return 0;
    }
    for (int i = 0; i < quantidade_elementos; i++) {
        if (fscanf(arquivo_entrada, "%d", &vetor[i]) != 1) {
            fprintf(stderr, "Erro: arquivo tem menos de %d valores\n", quantidade_elementos);
            fclose(arquivo_entrada);
            return 0;
        }
    }
    fclose(arquivo_entrada);
    return 1;
}

/* ─────────────────────────────────────────────
 * EXECUTAR BENCHMARK PARA UM TAMANHO
 *
 * Para cada tamanho de entrada, repete a
 * ordenacao por um numero de vezes definido,
 * acumula os tempos e imprime a media ao final.
 *
 * Por que relemos o arquivo a cada repeticao?
 *   Porque o Quick Sort modifica o vetor.
 *   Se nao recarregarmos, a segunda execucao
 *   ordenaria um vetor ja ordenado, o que
 *   mudaria o comportamento do algoritmo e
 *   tornaria a media desonesta.
 * ───────────────────────────────────────────── */
void executar_benchmark(const char *nome_arquivo, int quantidade_elementos, int numero_repeticoes) {
    double soma_tempos_ms = 0.0;

    for (int repeticao = 0; repeticao < numero_repeticoes; repeticao++) {
        int *vetor_dados = (int *)malloc(quantidade_elementos * sizeof(int));
        if (vetor_dados == NULL) {
            fprintf(stderr, "Erro: memoria insuficiente para n=%d\n", quantidade_elementos);
            return;
        }

        if (ler_arquivo_entrada(nome_arquivo, vetor_dados, quantidade_elementos) == 0) {
            free(vetor_dados);
            return;
        }

        struct timespec tempo_inicio, tempo_fim;
        clock_gettime(CLOCK_MONOTONIC, &tempo_inicio);
        quick_sort(vetor_dados, 0, quantidade_elementos - 1);
        clock_gettime(CLOCK_MONOTONIC, &tempo_fim);

        soma_tempos_ms += calcular_tempo_ms(tempo_inicio, tempo_fim);

        free(vetor_dados);
    }

    double media_tempo_ms = soma_tempos_ms / numero_repeticoes;

    printf("n = %7d  |  repeticoes = %4d  |  tempo medio = %8.4f ms\n", quantidade_elementos, numero_repeticoes, media_tempo_ms);
}

/* ─────────────────────────────────────────────
 * MAIN
 * ───────────────────────────────────────────── */
int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <arquivo_entrada>\n", argv[0]);
        return 1;
    }

    char *nome_arquivo = argv[1];

    printf("==============================================\n");
    printf("  Quick Sort - Pivo: Mediana de Tres (C)\n");
    printf("==============================================\n");

    int tamanhos_entrada[]       = {100,  1000, 10000, 100000, 1000000};
    int repeticoes_por_tamanho[] = {1000,  500,   250,    100,      50};
    int numero_tamanhos = sizeof(tamanhos_entrada) / sizeof(tamanhos_entrada[0]);

    for (int i = 0; i < numero_tamanhos; i++) {
        executar_benchmark(nome_arquivo, tamanhos_entrada[i], repeticoes_por_tamanho[i]);
    }

    printf("==============================================\n");
    return 0;
}