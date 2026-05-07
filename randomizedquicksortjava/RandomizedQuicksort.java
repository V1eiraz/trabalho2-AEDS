/*

    Compilação e execução

    -> javac randomizedquicksortjava/RandomizedQuicksort.java
    -> java -cp . randomizedquicksortjava.RandomizedQuicksort randomizedquicksortjava/<nome_do_arquivo>
*/

package randomizedquicksortjava;

import java.io.*;
import java.util.*;

public class RandomizedQuicksort{
    static Random random = new Random(67);

    static double calcularTempoMs(long inicio, long fim){
        return (fim - inicio) / 1e6;
    }

    static int indiceAleatorio(int esquerda, int direita){
        return esquerda + random.nextInt(direita - esquerda + 1);
    }

    static void swap(int[] array, int a, int b){
        int temp = array[a];
        array[a] = array[b];
        array[b] = temp;
    }

    static int particionar(int[] array, int esquerda, int direita){
        int pivoInd = indiceAleatorio(esquerda, direita);

        swap(array, pivoInd, direita);

        int pivo = array[direita];
        int i = esquerda - 1;

        for(int j = esquerda; j < direita; j++){
            if(array[j] <= pivo){
                i++;
                swap(array, i, j);
            }
        }
        swap(array, i + 1, direita);
        return i + 1;
    }

    static void randomizedQuickSort(int[] array, int esquerda, int direita){
        if(esquerda < direita){
            int pivoIndFinal = particionar(array, esquerda, direita);

            randomizedQuickSort(array, esquerda, pivoIndFinal - 1);
            randomizedQuickSort(array, pivoIndFinal + 1, direita);
        }
    }

    static int[] lerArquivoEntrada(String file, int n) throws IOException {
        int[] array = new int[n];
        Scanner scanner = new Scanner(new File(file));

        for(int i = 0; i < n; i++){
            if(!scanner.hasNextInt()){
                scanner.close();
                throw new IOException("Arquivo tem menos de " + n + " valores");
            }
            array[i] = scanner.nextInt();
        }
        scanner.close();
        return array;
    }

    static void benchmark(String file, int n, int reps){
        // TEMPO MÉDIO
        double tempoTotal = 0.0;

        for(int repeticao = 0; repeticao < reps; repeticao++){
            int[] arrayDados;

            try{
                arrayDados = lerArquivoEntrada(file, n);
            }catch(IOException erro){
                System.err.println("Erro: " + erro.getMessage());
                return;
            }

            random = new Random(67);

            long t0 = System.nanoTime();
            randomizedQuickSort(arrayDados, 0, n - 1);
            long t1 = System.nanoTime();

            tempoTotal += calcularTempoMs(t0, t1);
        }
        double avg = tempoTotal / reps;

        // CONSUMO DE MEMÓRIA
        Runtime rt = Runtime.getRuntime();
        System.gc();

        long m0 = rt.totalMemory() - rt.freeMemory();

        int[] arrayMem;

        try{
            arrayMem = lerArquivoEntrada(file, n);
        }catch(IOException erro){
            System.out.println("Erro: " + erro.getMessage());
            return;
        }

        random = new Random(67);
        randomizedQuickSort(arrayMem, 0, n - 1);
        long m1 = rt.totalMemory() - rt.freeMemory();
        
        long deltaKB = (m1 - m0) / 1024;

        System.out.printf("Tamanho = %d\nRepetições = %d\nTempo médio = %.4f ms\nMemória = %d KB\n\n", n, reps, avg, deltaKB);
    }

    public static void main(String[] args){
        String file = args[0];

        int[] tamanhos   = {100, 1000, 10000, 100000, 1000000};
        int reps = 100;

        for(int i = 0; i < tamanhos.length; i++)
            benchmark(file, tamanhos[i], reps);
    }
}