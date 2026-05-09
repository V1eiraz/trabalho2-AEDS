#!/bin/bash
# ──────────────────────────────────────────────
#  executar.sh - Randomized Quick Sort (C++)
#
#  Compila o programa e executa uma vez por
#  combinacao de (arquivo x tamanho), medindo
#  o pico de memoria com GNU Time em cada
#  execucao separadamente.
#
#  Uso: ./executar.sh
# ──────────────────────────────────────────────
set -e

# Compila
echo "Compilando..."
g++ -O2 -Wall -o RandomizedQuickSort main.cpp RandomizedQuickSort.cpp benchmark.cpp
echo "Compilado com sucesso."
echo ""

ARQUIVOS=("input.dat" "crescente.dat" "decrescente.dat")
TAMANHOS=(100 1000 10000 100000 1000000)

for arquivo in "${ARQUIVOS[@]}"; do
    echo "============================================================"
    echo "  Arquivo: $arquivo"
    echo "============================================================"
    for tamanho in "${TAMANHOS[@]}"; do
        echo "--- n = $tamanho ---"
        # GNU Time mede a memoria do processo inteiro.
        # Rodamos um processo separado por tamanho para
        # que a medicao seja individual e nao acumulada.
        /usr/bin/time -f "Memoria maxima: %M KB" \
            ./RandomizedQuickSort "$arquivo" "$tamanho" \
            2>&1
        echo ""
    done
done