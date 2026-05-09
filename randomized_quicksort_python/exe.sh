#!/bin/bash
# ──────────────────────────────────────────────
#  exe.sh - Randomized QuickSort(Python)
# ──────────────────────────────────────────────
set -e

echo "Verificando Python..."
python3 --version
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
            python3 main.py "$arquivo" "$tamanho" \
            2>&1
        echo ""
    done
done
