# Para executar o código:
# Abra a pasta quicksort_python no terminal
# chmod +x exe.sh | Apenas na primeira vez para dar permissão ao arquivo
# ./exe.sh

import os
import time
import random
import gc
random.seed(67)

def quicksort(arr, left, right):
    if left < right:
        pivo = partition(arr, left, right)
        quicksort(arr, left, pivo - 1)
        quicksort(arr, pivo + 1, right)

def partition(arr, left, right):
    pos1 = random.randint(left, right)
    pos2 = random.randint(left, right)
    pos3 = random.randint(left, right)

    vals = [(arr[pos1], pos1), (arr[pos2], pos2), (arr[pos3], pos3)]
    vals.sort(key=lambda x: x[0])
    median_pos = vals[1][1]

    arr[median_pos], arr[right] = arr[right], arr[median_pos]

    pivo = arr[right]
    i = left - 1
    for j in range(left, right):
        if arr[j] <= pivo:
            i += 1
            arr[i], arr[j] = arr[j], arr[i]
    arr[i + 1], arr[right] = arr[right], arr[i + 1]
    return i + 1

def readarchive(path):
    try:
        with open(path, "r") as file:
            n = int(file.readline().strip())
            nums = list(map(int, file.readline().strip().split()))
    except FileNotFoundError:
        print("Arquivo não encontrado!")
        return [], 0
    return nums, n

def writearchive(arr):
    dir = os.path.dirname(os.path.abspath(__file__))
    try:
        path = os.path.join(dir, "outputs", "output.dat")
        os.makedirs(os.path.dirname(path), exist_ok=True)
        with open(path, "w") as file:
            for num in arr:
                file.write(f"{num}\n")
    except Exception as e:
        print(f"Erro ao escrever arquivo: {e}")

def executar_benchmark(vetor_completo, quantidade_elementos, numero_repeticoes):
    soma_tempos_ms = 0.0

    for _ in range(numero_repeticoes):
        vetor_dados = vetor_completo[:quantidade_elementos].copy()

        gc.collect()

        start = time.perf_counter()
        quicksort(vetor_dados, 0, quantidade_elementos - 1)
        end = time.perf_counter()

        soma_tempos_ms += (end - start) * 1000.0

    media_tempo_ms = soma_tempos_ms / numero_repeticoes

    print(f"n = {quantidade_elementos:7d}  |  repeticoes = {numero_repeticoes:4d}  |  tempo medio = {media_tempo_ms:8.4f} ms")

import sys

if len(sys.argv) < 3:
    print("Uso: python main.py <arquivo> <tamanho>")
    sys.exit(1)

arquivo_path = sys.argv[1]
tamanho_desejado = int(sys.argv[2])

nums, n = readarchive(arquivo_path)

if n > 0 and tamanho_desejado <= n:
    print("---------------------------------------------------------")
    executar_benchmark(nums, tamanho_desejado, 100)
    print("---------------------------------------------------------")
else:
    print("Nenhum dado encontrado ou tamanho maior que o arquivo.")