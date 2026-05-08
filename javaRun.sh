#!/bin/bash

CABECALHO="+------------+--------------+------------------+--------------+"
TITULO="| Tamanho    | Repetições   | Tempo médio (ms) | Memória (KB) |"
RODAPE="+------------+--------------+------------------+--------------+"

ARQUIVOS=("random" "crescente" "decrescente")
TAMANHOS=(100 1000 10000 100000 1000000)
OUTPUT="quicksortjava/output/output.dat"

# COMPILAÇÃO

echo "Compilando..."

javac -Xlint:all -d quicksortjava/bin quicksortjava/common/*.java quicksortjava/algorithms/*.java quicksortjava/Main.java

if [ $? -ne 0 ]; then
    echo "Erro na compilação, abortando."
    exit 1
fi

echo "Compilado com sucesso."

# EXECUÇÃO

mkdir -p quicksortjava/output
> "$OUTPUT"

echo "Executando, aguarde..."

for arquivo in "${ARQUIVOS[@]}"; do 
    {
        echo ""
        echo "========================================"
        echo "Arquivo: $arquivo.dat"
        echo "========================================"      
    } >> "$OUTPUT"

    for algoritmo in "qs" "rqs"; do
        if [ "$algoritmo" = "qs" ]; then
            LABEL="--- Quicksort (Mediana de 3) ---"
        else
            LABEL="--- Randomized Quicksort ---"
        fi

        {
            echo ""
            echo "$LABEL"
            echo "$CABECALHO"
            echo "$TITULO"
            echo "$CABECALHO"
        } >> "$OUTPUT"
        
        for tamanho in "${TAMANHOS[@]}"; do
            TEMPO=$(
                /usr/bin/time -v \
                    java -cp quicksortjava/bin quicksortjava.Main \
                        "quicksortjava/inputs/$arquivo.dat" \
                        "$tamanho" \
                        "$algoritmo" \
                    2>/tmp/gnu_time.txt
            )

            MEMORIA=$(grep "Maximum resident set size" /tmp/gnu_time.txt | awk '{print $NF}')

            printf "| %-10d | %-12d | %-16s | %-12s |\n" \
                "$tamanho" "100" "$TEMPO" "$MEMORIA" >> "$OUTPUT"
        done

        echo "$RODAPE" >> "$OUTPUT"
    done
done

rm -f /tmp/gnu_time.txt
echo "Operação concluída! Resultado em $OUTPUT"