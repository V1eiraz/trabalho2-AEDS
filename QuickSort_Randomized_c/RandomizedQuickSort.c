/*
 * Randomized Quick Sort - Pivo Aleatorio (seed 67)
 * Seminario: Ordenacoes por Divisao Recursiva
 */

#include "RandomizedQuickSort.h"

/* ─────────────────────────────────────────────
 * CALCULO DO TEMPO DECORRIDO
 * ───────────────────────────────────────────── */
double calcular_tempo_ms(struct timespec tempo_inicio, struct timespec tempo_fim) {
    return (tempo_fim.tv_sec  - tempo_inicio.tv_sec)  * 1000.0
         + (tempo_fim.tv_nsec - tempo_inicio.tv_nsec) / 1e6;
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
 * ESCOLHA ALEATORIA DO PIVO
 * ───────────────────────────────────────────── */
int calcular_indice_aleatorio(int indice_inicio, int indice_fim) {
    return indice_inicio + rand() % (indice_fim - indice_inicio + 1);
}

/* ─────────────────────────────────────────────
 * PARTICIONAR SUBVETOR
 * ───────────────────────────────────────────── */
int particionar(int *vetor, int indice_inicio, int indice_fim) {
    int indice_pivo = calcular_indice_aleatorio(indice_inicio, indice_fim);

    trocar_elementos(&vetor[indice_pivo], &vetor[indice_fim]);

    int valor_pivo           = vetor[indice_fim];
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
 * RANDOMIZED QUICK SORT RECURSIVO
 * ───────────────────────────────────────────── */
void randomized_quick_sort(int *vetor, int indice_inicio, int indice_fim) {
    if (indice_inicio < indice_fim) {
        int indice_pivo_final = particionar(vetor, indice_inicio, indice_fim);
        randomized_quick_sort(vetor, indice_inicio, indice_pivo_final - 1);
        randomized_quick_sort(vetor, indice_pivo_final + 1, indice_fim);
    }
}

/* ─────────────────────────────────────────────
 * LEITURA DO ARQUIVO DE ENTRADA
 *
 * Recebe o nome do arquivo como parametro
 * em vez de usar uma constante fixa no .h.
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
 * ESCRITA DO ARQUIVO DE SAIDA
 * ───────────────────────────────────────────── */
void escrever_arquivo_saida(int *vetor, int quantidade_elementos) {
    FILE *arquivo_saida = fopen(NOME_ARQUIVO_SAIDA, "w");
    if (arquivo_saida == NULL) {
        fprintf(stderr, "Erro: nao foi possivel criar '%s'\n", NOME_ARQUIVO_SAIDA);
        return;
    }
    for (int i = 0; i < quantidade_elementos; i++) {
        fprintf(arquivo_saida, "%d\n", vetor[i]);
    }
    fclose(arquivo_saida);
    printf("Vetor ordenado salvo em '%s'\n", NOME_ARQUIVO_SAIDA);
}

/* ─────────────────────────────────────────────
 * EXECUTAR BENCHMARK PARA UM TAMANHO
 *
 * Medicao de memoria removida daqui — feita
 * externamente pelo GNU Time no script .sh,
 * um processo separado por tamanho de entrada.
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

        srand(67);

        struct timespec tempo_inicio, tempo_fim;
        clock_gettime(CLOCK_MONOTONIC, &tempo_inicio);
        randomized_quick_sort(vetor_dados, 0, quantidade_elementos - 1);
        clock_gettime(CLOCK_MONOTONIC, &tempo_fim);

        soma_tempos_ms += calcular_tempo_ms(tempo_inicio, tempo_fim);

        free(vetor_dados);
    }

    double media_tempo_ms = soma_tempos_ms / numero_repeticoes;

    printf("n = %7d  |  repeticoes = %4d  |  tempo medio = %8.4f ms\n",
           quantidade_elementos, numero_repeticoes, media_tempo_ms);
}

/* ─────────────────────────────────────────────
 * GERAR OUTPUT ORDENADO
 * ───────────────────────────────────────────── */
void gerar_output_ordenado(const char *nome_arquivo) {
    int quantidade_elementos = 1000000;

    int *vetor_dados = (int *)malloc(quantidade_elementos * sizeof(int));
    if (vetor_dados == NULL) {
        fprintf(stderr, "Erro: memoria insuficiente para gerar output\n");
        return;
    }

    if (ler_arquivo_entrada(nome_arquivo, vetor_dados, quantidade_elementos) == 0) {
        free(vetor_dados);
        return;
    }

    srand(67);
    randomized_quick_sort(vetor_dados, 0, quantidade_elementos - 1);
    escrever_arquivo_saida(vetor_dados, quantidade_elementos);

    free(vetor_dados);
}