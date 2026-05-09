#!/bin/bash
# ──────────────────────────────────────────────
#  exe.sh - Randomized QuickSort (Go)
# ──────────────────────────────────────────────
set -e

echo "Compilando..."
go build -o randomized_quicksort_go main.go
echo "Compilado com sucesso."
echo ""

ARQUIVOS=("config/input.dat" "config/crescente.dat" "config/decrescente.dat")
TAMANHOS=(100 1000 10000 100000 1000000)

for arquivo in "${ARQUIVOS[@]}"; do
    echo "============================================================"
    echo "  Arquivo: $arquivo"
    echo "============================================================"
    for tamanho in "${TAMANHOS[@]}"; do
        echo "--- n = $tamanho ---"
        /usr/bin/time -f "Memoria maxima: %M KB" \
            ./randomized_quicksort_go "$arquivo" "$tamanho" \
            2>&1
        echo ""
    done
done
