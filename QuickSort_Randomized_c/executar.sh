#!/bin/bash

# ──────────────────────────────────────────────
#  executar.sh - Randomized Quick Sort
#
#  Compila e executa uma vez por combinacao
#  de (arquivo x tamanho), medindo o pico de
#  memoria com GNU Time em cada execucao
#  separadamente.
#
#  Primeira vez, abra o terminal da pasta executar.sh e rode:
#               cd QuickSort_Randomized_c
#               chmod +x executar.sh
#               ./executar.sh
#
#  Depois do primeiro uso: ./executar.sh
# ──────────────────────────────────────────────

set -e

echo "Compilando..."
gcc -O0 -Wall -o RandomizedQuickSort mainRandomized.c RandomizedQuickSort.c
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

        /usr/bin/time -f "Memoria maxima: %M KB" \
            ./RandomizedQuickSort "$arquivo" "$tamanho" \
            2>&1

        echo ""
    done
done