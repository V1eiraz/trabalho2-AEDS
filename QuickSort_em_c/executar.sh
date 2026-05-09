#!/bin/bash

# ──────────────────────────────────────────────
#  executar.sh - Quick Sort Mediana de Tres
#
#  Compila o programa e executa uma vez por
#  combinacao de (arquivo x tamanho), medindo
#  o pico de memoria com GNU Time em cada
#  execucao separadamente.
#
#  Primeira vez:cd QuickSort_em_c
#               chmod +x executar.sh
#               ./executar.sh
#
#  Depois Uso: ./executar.sh
# ──────────────────────────────────────────────

set -e

# Compila
echo "Compilando..."
gcc -O0 -Wall -o QuickSort main.c QuickSort.c
echo "Compilado com sucesso."
echo ""

ARQUIVOS=("input.dat" "crescente.dat" "decrescente.dat")
TAMANHOS=(100 1000 10000 100000 1000000)
REPETICOES=100

for arquivo in "${ARQUIVOS[@]}"; do
    echo "============================================================"
    echo "  Arquivo: $arquivo"
    echo "============================================================"

    for tamanho in "${TAMANHOS[@]}"; do
        echo "--- n = $tamanho ---"

        # GNU Time mede a memoria do processo inteiro.
        # Rodamos um processo separado por tamanho para
        # que a medicao seja individual e nao acumulada.
        # O 2>&1 redireciona a saida do time junto com
        # a saida do programa para o terminal.
        /usr/bin/time -f "Memoria maxima: %M KB" \
            ./QuickSort "$arquivo" "$tamanho" \
            2>&1

        echo ""
    done
done