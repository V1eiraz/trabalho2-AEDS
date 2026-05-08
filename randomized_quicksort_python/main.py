import os
import time
import random
import gc

def clear_output():
    os.system('cls' if os.name == 'nt' else 'clear')

def randomized_quicksort(arr, left, right):
    if left < right:
        pivo = partition(arr, left, right)
        randomized_quicksort(arr, left, pivo - 1)
        randomized_quicksort(arr, pivo + 1, right)


def partition(arr, left, right):
    rand_index = random.randint(left, right)
    arr[rand_index], arr[right] = arr[right], arr[rand_index]

    pivo = arr[right]
    i = left - 1
    for j in range(left, right):
        if arr[j] <= pivo:
            i += 1
            arr[i], arr[j] = arr[j], arr[i]
    arr[i + 1], arr[right] = arr[right], arr[i + 1]
    return i + 1

def readarchive():
    dir = os.path.dirname(os.path.abspath(__file__))
    try:
        path = os.path.join(dir, "config", "input.dat")
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
        with open(path, "w") as file:
            for num in arr:
                file.write(f"{num}\n")
    except FileNotFoundError:
        print("Erro ao escrever arquivo!")
        return

def get_memoria_rss_kb():
    try:
        with open("/proc/self/status", "r") as f:
            for line in f:
                if line.startswith("VmRSS:"):
                    return int(line.split()[1])
    except:
        return 0
    return 0

def executar_benchmark(vetor_completo, quantidade_elementos, numero_repeticoes):
    soma_tempos_ms = 0.0
    soma_memoria_kb = 0

    for _ in range(numero_repeticoes):
        vetor_dados = vetor_completo[:quantidade_elementos].copy()

        gc.collect()
        antes = get_memoria_rss_kb()

        start = time.perf_counter()
        randomized_quicksort(vetor_dados, 0, quantidade_elementos - 1)
        end = time.perf_counter()

        depois = get_memoria_rss_kb()

        soma_tempos_ms += (end - start) * 1000.0
        soma_memoria_kb += depois - antes

    media_tempo_ms = soma_tempos_ms / numero_repeticoes
    media_memoria_kb = soma_memoria_kb / numero_repeticoes

    print(f"n = {quantidade_elementos:7d}  |  repeticoes = {numero_repeticoes:4d}  |  tempo medio = {media_tempo_ms:8.4f} ms  |  memoria = {media_memoria_kb:8.2f} KB")


if __name__ == "__main__":
    clear_output()
    
    random.seed(67)
    nums, n = readarchive()
    
    if n > 0:
        tamanhos = [100, 1000, 10000, 100000, 1000000]
        repeticoes = [100, 100, 100, 100, 100]
        
        print("Iniciando Benchmark do Randomized QuickSort...")
        print("-" * 50)
        
        for i in range(len(tamanhos)):
            if tamanhos[i] <= n:
                executar_benchmark(nums, tamanhos[i], repeticoes[i])
        
        print("-" * 50)
        print("Benchmark finalizado.")
        
    else:
        print("Nenhum dado encontrado para o benchmark.")
