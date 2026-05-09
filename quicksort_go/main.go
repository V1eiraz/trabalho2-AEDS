// Para executar o código:
// Abra a pasta quicksort_go no terminal
// chmod +x exe.sh | Apenas na primeira vez para dar permissão ao arquivo
// ./exe.sh
package main

import (
	"bufio"
	"fmt"
	"math/rand"
	"os"
	"path/filepath"
	"runtime"
	"sort"
	"strconv"
	"strings"
	"time"
)

func quicksort(arr []int, left int, right int) {
	if left < right {
		pivo := partition(arr, left, right)
		quicksort(arr, left, pivo-1)
		quicksort(arr, pivo+1, right)
	}
}

type Val struct {
	value int
	pos   int
}

func partition(arr []int, left int, right int) int {
	pos1 := left + rand.Intn(right-left+1)
	pos2 := left + rand.Intn(right-left+1)
	pos3 := left + rand.Intn(right-left+1)

	vals := []Val{
		{value: arr[pos1], pos: pos1},
		{value: arr[pos2], pos: pos2},
		{value: arr[pos3], pos: pos3},
	}

	sort.Slice(vals, func(i, j int) bool {
		return vals[i].value < vals[j].value
	})

	medianPos := vals[1].pos

	arr[medianPos], arr[right] = arr[right], arr[medianPos]

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

func readArchive(path string) ([]int, int) {
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

func executarBenchmark(vetorCompleto []int, quantidadeElementos int, numeroRepeticoes int) {
	var somaTemposMs float64

	for i := 0; i < numeroRepeticoes; i++ {
		vetorDados := make([]int, quantidadeElementos)
		copy(vetorDados, vetorCompleto[:quantidadeElementos])

		runtime.GC()

		start := time.Now()
		quicksort(vetorDados, 0, quantidadeElementos-1)
		elapsed := time.Since(start).Seconds() * 1000.0

		somaTemposMs += elapsed
	}

	mediaTempoMs := somaTemposMs / float64(numeroRepeticoes)

	fmt.Printf("n = %7d  |  repeticoes = %4d  |  tempo medio = %8.4f ms\n",
		quantidadeElementos, numeroRepeticoes, mediaTempoMs)
}

func main() {

	if len(os.Args) < 3 {
		fmt.Println("Uso: ./main <arquivo> <tamanho>")
		os.Exit(1)
	}

	arquivoPath := os.Args[1]
	tamanhoDesejado, _ := strconv.Atoi(os.Args[2])

	rand.Seed(67)
	nums, n := readArchive(arquivoPath)

	if n > 0 && tamanhoDesejado <= n {
		fmt.Println("---------------------------------------------------------")
		executarBenchmark(nums, tamanhoDesejado, 100)
		fmt.Println("---------------------------------------------------------")
	} else {
		fmt.Println("Nenhum dado encontrado ou tamanho maior que o arquivo.")
	}
}
