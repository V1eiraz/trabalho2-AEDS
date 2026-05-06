import os
import time
import random

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


clear_output()

tempos_execucao = []

for _ in range(10):
    random.seed(67)
    nums, n = readarchive()
    
    if n > 0:
        start = time.perf_counter()
        randomized_quicksort(nums, 0, n - 1)
        end = time.perf_counter()
        
        tempos_execucao.append(end - start)

print(f"Tempo de execução: {tempos_execucao}\n")
if tempos_execucao:
    media_tempo = sum(tempos_execucao) / len(tempos_execucao)
    print(f"Média de tempo de execução do Randomized QuickSort (10 iterações): {media_tempo:.6f} segundos")
    
    writearchive(nums)
else:
    print("Nenhum dado processado.")
