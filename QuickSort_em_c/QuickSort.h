#ifndef QUICKSORT_H
#define QUICKSORT_H

#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Nome fixo do arquivo de entrada */
#define NOME_ARQUIVO_ENTRADA "decrescente.dat"

/* Nome fixo do arquivo de saida */
#define NOME_ARQUIVO_SAIDA   "output.dat"

/* ── Utilitarios ─────────────────────────────── */
double calcular_tempo_ms(struct timespec tempo_inicio, struct timespec tempo_fim);
void   trocar_elementos(int *elemento_a, int *elemento_b);

/* ── Selecao do pivo ─────────────────────────── */
int sortear_indice_unico(int indice_inicio, int indice_fim,
                         int indice_excluido_a, int indice_excluido_b);
int calcular_indice_mediana(int *vetor, int indice_inicio, int indice_fim);

/* ── Algoritmo ───────────────────────────────── */
int  particionar(int *vetor, int indice_inicio, int indice_fim);
void quick_sort(int *vetor, int indice_inicio, int indice_fim);

/* ── Entrada e saida ─────────────────────────── */
int  ler_arquivo_entrada(int *vetor, int quantidade_elementos);
void escrever_arquivo_saida(int *vetor, int quantidade_elementos);

/* ── Benchmark ───────────────────────────────── */
void executar_benchmark(int quantidade_elementos, int numero_repeticoes);
void gerar_output_ordenado(void);

#endif