/*
 * Randomized Quick Sort - Pivo Aleatorio (seed 67)
 * Seminario: Ordenacoes por Divisao Recursiva
 */

#include "RandomizedQuickSort.h"

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
 * TROCA DE ELEMENTOS
 * ───────────────────────────────────────────── */
void trocar_elementos(int *elemento_a, int *elemento_b) {
    int valor_temporario = *elemento_a;
    *elemento_a = *elemento_b;
    *elemento_b = valor_temporario;
}

/* ─────────────────────────────────────────────
 * ESCOLHA ALEATORIA DO PIVO
 *
 * Gera um indice aleatorio entre indice_inicio
 * e indice_fim (inclusive) usando rand().
 *
 * Por que aleatorio?
 *   No Quick Sort com pivo fixo, uma entrada
 *   ja ordenada sempre produz o pior caso O(n²)
 *   porque o pivo cai em um extremo e a divisao
 *   fica 0 e n-1.
 *
 *   Com o pivo aleatorio, a chance de cair
 *   sempre no extremo e exponencialmente pequena,
 *   garantindo O(n log n) esperado para qualquer
 *   entrada, independente de sua ordem.
 *
 * Por que seed 67?
 *   A seed fixa garante que os mesmos indices
 *   aleatorios sejam gerados em toda execucao,
 *   tornando o experimento reproduzivel.
 * ───────────────────────────────────────────── */
int calcular_indice_aleatorio(int indice_inicio, int indice_fim) {
    return indice_inicio + rand() % (indice_fim - indice_inicio + 1);
}

/* ─────────────────────────────────────────────
 * PARTICIONAR SUBVETOR
 *
 * 1. Escolhe o pivo em posicao aleatoria.
 * 2. Move o pivo para a ultima posicao.
 * 3. Percorre o subvetor colocando elementos
 *    menores que o pivo a esquerda.
 * 4. Posiciona o pivo definitivamente.
 * 5. Retorna o indice final do pivo.
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
 * Le exatamente quantidade_elementos inteiros
 * do arquivo definido em NOME_ARQUIVO_ENTRADA,
 * independente de como estao dispostos nas
 * linhas. Retorna 1 em sucesso, 0 em falha.
 * ───────────────────────────────────────────── */
int ler_arquivo_entrada(int *vetor, int quantidade_elementos) {
    FILE *arquivo_entrada = fopen(NOME_ARQUIVO_ENTRADA, "r");
    if (arquivo_entrada == NULL) {
        fprintf(stderr, "Erro: nao foi possivel abrir '%s'\n", NOME_ARQUIVO_ENTRADA);
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
 *
 * Escreve todos os elementos do vetor ja
 * ordenado no arquivo definido em
 * NOME_ARQUIVO_SAIDA, um numero por linha.
 *
 * Chamada apenas uma vez apos todos os
 * benchmarks para nao interferir nos tempos.
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
 * Repete a ordenacao numero_repeticoes vezes,
 * acumula os tempos e imprime a media.
 *
 * O arquivo e relido a cada repeticao pois
 * o Quick Sort modifica o vetor. Sem isso,
 * a segunda execucao ordenaria dados ja
 * ordenados, tornando a media desonesta.
 *
 * A seed e resetada a cada repeticao para
 * garantir a mesma sequencia de sorteios
 * em todas as execucoes, tornando o
 * experimento reproduzivel.
 * ───────────────────────────────────────────── */
void executar_benchmark(int quantidade_elementos, int numero_repeticoes) {
    double soma_tempos_ms = 0.0;

    for (int repeticao = 0; repeticao < numero_repeticoes; repeticao++) {
        int *vetor_dados = (int *)malloc(quantidade_elementos * sizeof(int));
        if (vetor_dados == NULL) {
            fprintf(stderr, "Erro: memoria insuficiente para n=%d\n", quantidade_elementos);
            return;
        }

        if (ler_arquivo_entrada(vetor_dados, quantidade_elementos) == 0) {
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

    double media_tempo_ms  = soma_tempos_ms / numero_repeticoes;

    /*
     * CALCULO DO USO DE MEMORIA
     *
     * Para cada entrada de tamanho n, o vetor
     * ocupa exatamente n * sizeof(int) bytes.
     * sizeof(int) retorna 4 bytes na maioria
     * dos sistemas modernos de 64 bits.
     *
     * Dividimos por 1024.0 para converter
     * bytes em kilobytes (KB).
     *
     * Exemplo para n=1.000.000:
     *   1.000.000 * 4 = 4.000.000 bytes
     *   4.000.000 / 1024 = 3906.25 KB
     */
    double memoria_vetor_kb = (quantidade_elementos * sizeof(int)) / 1024.0;

    printf("n = %7d  |  repeticoes = %4d  |  tempo medio = %8.4f ms  |  memoria = %8.2f KB\n",
           quantidade_elementos, numero_repeticoes, media_tempo_ms, memoria_vetor_kb);
}

/* ─────────────────────────────────────────────
 * GERAR OUTPUT ORDENADO
 *
 * Le o maior tamanho de entrada (1.000.000),
 * ordena uma unica vez e salva em output.dat.
 *
 * Feito separadamente do benchmark para nao
 * contaminar as medicoes de tempo.
 * ───────────────────────────────────────────── */
void gerar_output_ordenado() {
    int quantidade_elementos = 1000000;

    int *vetor_dados = (int *)malloc(quantidade_elementos * sizeof(int));
    if (vetor_dados == NULL) {
        fprintf(stderr, "Erro: memoria insuficiente para gerar output\n");
        return;
    }

    if (ler_arquivo_entrada(vetor_dados, quantidade_elementos) == 0) {
        free(vetor_dados);
        return;
    }

    srand(67);
    randomized_quick_sort(vetor_dados, 0, quantidade_elementos - 1);
    escrever_arquivo_saida(vetor_dados, quantidade_elementos);

    free(vetor_dados);
}