//Para executar o código:
// go build main.go
// .\main.exe ou go run main.go

package main

import (
	"bufio"
	"fmt"
	"math/rand"
	"os"
	"os/exec"
	"path/filepath"
	"runtime"
	"strconv"
	"strings"
	"time"
)

func clearOutput() {
	var cmd *exec.Cmd
	if runtime.GOOS == "windows" {
		cmd = exec.Command("cmd", "/c", "cls")
	} else {
		cmd = exec.Command("clear")
	}
	cmd.Stdout = os.Stdout
	cmd.Run()
}

func quicksort(arr []int, left int, right int) {
	if left < right {
		pivo := partition(arr, left, right)
		quicksort(arr, left, pivo-1)
		quicksort(arr, pivo+1, right)
	}
}

func partition(arr []int, left int, right int) int {
	randPos := left + rand.Intn(right-left+1)
	arr[randPos], arr[right] = arr[right], arr[randPos]

	pivo := arr[right]
	i := left - 1
	for j := left; j < right; j++ {
		if arr[j] <= pivo {
			i++
			arr[i], arr[j] = arr[j], arr[i]
		}
	}
	arr[i+1], arr[right] = arr[right], arr[i+1]
	return i + 1
}

func readArchive() ([]int, int) {
	_, filename, _, ok := runtime.Caller(0)
	if !ok {
		fmt.Println("Erro ao obter diretório atual!")
		return []int{}, 0
	}
	dir := filepath.Dir(filename)

	path := filepath.Join(dir, "config", "input.dat")

	content, err := os.ReadFile(path)
	if err != nil {
		fmt.Printf("Arquivo não encontrado em: %s\n", path)
		return []int{}, 0
	}

	lines := strings.Split(strings.ReplaceAll(string(content), "\r\n", "\n"), "\n")
	if len(lines) < 2 {
		return []int{}, 0
	}

	n, _ := strconv.Atoi(strings.TrimSpace(lines[0]))
	numsStr := strings.Fields(lines[1])

	nums := make([]int, 0, len(numsStr))
	for _, s := range numsStr {
		val, _ := strconv.Atoi(s)
		nums = append(nums, val)
	}

	return nums, n
}

func writeArchive(arr []int) {
	_, filename, _, ok := runtime.Caller(0)
	if !ok {
		fmt.Println("Erro ao obter diretório atual!")
		return
	}
	dir := filepath.Dir(filename)

	path := filepath.Join(dir, "outputs", "output.dat")

	os.MkdirAll(filepath.Dir(path), os.ModePerm)

	file, err := os.Create(path)
	if err != nil {
		fmt.Println("Erro ao escrever arquivo!")
		return
	}
	defer file.Close()

	writer := bufio.NewWriter(file)
	for _, num := range arr {
		writer.WriteString(strconv.Itoa(num))
		writer.WriteString("\n")
	}
	writer.Flush()
}

func getMemoriaRSSKb() int64 {
	data, err := os.ReadFile("/proc/self/status")
	if err != nil {
		return 0
	}
	for _, line := range strings.Split(string(data), "\n") {
		if strings.HasPrefix(line, "VmRSS:") {
			fields := strings.Fields(line)
			val, _ := strconv.ParseInt(fields[1], 10, 64)
			return val
		}
	}
	return 0
}

func executarBenchmark(vetorCompleto []int, quantidadeElementos int, numeroRepeticoes int) {
	var somaTemposMs float64
	var somaMemoriaKb int64

	for i := 0; i < numeroRepeticoes; i++ {
		vetorDados := make([]int, quantidadeElementos)
		copy(vetorDados, vetorCompleto[:quantidadeElementos])

		runtime.GC()

		antes := getMemoriaRSSKb()

		start := time.Now()
		quicksort(vetorDados, 0, quantidadeElementos-1)
		elapsed := time.Since(start).Seconds() * 1000.0

		depois := getMemoriaRSSKb()

		somaTemposMs += elapsed
		somaMemoriaKb += depois - antes
	}

	mediaTempoMs := somaTemposMs / float64(numeroRepeticoes)
	mediaMemoriaKb := float64(somaMemoriaKb) / float64(numeroRepeticoes)

	fmt.Printf("n = %7d  |  repeticoes = %4d  |  tempo medio = %8.4f ms  |  memoria = %8.2f KB\n",
		quantidadeElementos, numeroRepeticoes, mediaTempoMs, mediaMemoriaKb)
}

func main() {
	clearOutput()

	rand.Seed(67)
	nums, n := readArchive()

	if n > 0 {
		tamanhos := []int{100, 1000, 10000, 100000, 1000000}
		repeticoes := []int{100, 100, 100, 100, 100}

		fmt.Println("Iniciando Benchmark do Randomized QuickSort...")
		fmt.Println("---------------------------------------------------------")

		for i := 0; i < len(tamanhos); i++ {
			if tamanhos[i] <= n {
				executarBenchmark(nums, tamanhos[i], repeticoes[i])
			}
		}

		fmt.Println("---------------------------------------------------------")
		fmt.Println("Benchmark finalizado.")

	} else {
		fmt.Println("Nenhum dado encontrado para o benchmark.")
	}
}
