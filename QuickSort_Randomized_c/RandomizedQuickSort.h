#ifndef RANDOMIZEDQUICKSORT_H
#define RANDOMIZEDQUICKSORT_H

#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Nome fixo do arquivo de saida */
#define NOME_ARQUIVO_SAIDA "output.dat"

/* ── Utilitarios ─────────────────────────────── */
double calcular_tempo_ms(struct timespec tempo_inicio, struct timespec tempo_fim);
void   trocar_elementos(int *elemento_a, int *elemento_b);

/* ── Selecao do pivo ─────────────────────────── */
int calcular_indice_aleatorio(int indice_inicio, int indice_fim);

/* ── Algoritmo ───────────────────────────────── */
int  particionar(int *vetor, int indice_inicio, int indice_fim);
void randomized_quick_sort(int *vetor, int indice_inicio, int indice_fim);

/* ── Entrada e saida ─────────────────────────── */
int  ler_arquivo_entrada(const char *nome_arquivo, int *vetor, int quantidade_elementos);
void escrever_arquivo_saida(int *vetor, int quantidade_elementos);

/* ── Benchmark ───────────────────────────────── */
void executar_benchmark(const char *nome_arquivo, int quantidade_elementos, int numero_repeticoes);
void gerar_output_ordenado(const char *nome_arquivo);

#endif