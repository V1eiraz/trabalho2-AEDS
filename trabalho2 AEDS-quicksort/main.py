import os
import time
import random

def clear_output():
    os.system('cls' if os.name == 'nt' else 'clear')

def quicksort(arr , left , right):
    if left < right:
        pivo = partition(arr , left , right)
        quicksort(arr , left, pivo-1)
        quicksort( arr , pivo+1, right)
    


def partition(arr , left , right):
    pos1 = random.randint(left, right)
    pos2 = random.randint(left, right)
    pos3 = random.randint(left, right)
    
    vals = [(arr[pos1], pos1), (arr[pos2], pos2), (arr[pos3], pos3)]
    vals.sort(key=lambda x: x[0])
    median_pos = vals[1][1]
    
    arr[median_pos], arr[right] = arr[right], arr[median_pos]
    
    pivo = arr[right]
    i = left-1
    for j in range(left, right):
        if arr[j] <= pivo:
            i+=1
            arr[i], arr[j] = arr[j], arr[i]
    arr[i+1], arr[right] = arr[right], arr[i+1]
    return i+1

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

for _ in range(50):
    random.seed(67)
    nums, n = readarchive()
    
    if n > 0:
        start = time.perf_counter()
        quicksort(nums, 0, n-1)
        end = time.perf_counter()
        
        tempos_execucao.append(end - start)
    
print(f"Tempo de execução: {tempos_execucao}\n")
if tempos_execucao:
    media_tempo = sum(tempos_execucao) / len(tempos_execucao)
    print(f"Média de tempo de execução do QuickSort (10 iterações): {media_tempo:.6f} segundos")
    
    writearchive(nums)
else:
    print("Nenhum dado processado.")