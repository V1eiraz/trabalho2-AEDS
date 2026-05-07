/*

    Compilação e execução 

    -> javac quicksortjava/Quicksort.java
    -> java -cp . quicksortjava.Quicksort quicksortjava/<nome_do_arquivo>

*/

package quicksortjava;

import java.io.*;
import java.util.*;

public class Quicksort{
    static Random random = new Random(67);

    static double calcularTempoMs(long inicio, long fim){
        return (fim - inicio) / 1e6;
    }

    static int indiceMediana(int[] array, int esquerda, int meio, int direita){
        int a = array[esquerda];
        int b = array[meio];
        int c = array[direita];
        
        if((a <= b && b <= c) || (c <= b && b <= a))
            return meio;
        if((b <= a && a <= c) || (c <= a && a <= b))
            return esquerda;
        return direita;
    }

    static void swap(int[] array, int a, int b){
        int temp = array[a];
        array[a] = array[b];
        array[b] = temp;
    }

    static int particionar(int[] array, int esquerda, int direita){
        int rand1 = esquerda + random.nextInt(direita - esquerda + 1);
        int rand2 = esquerda + random.nextInt(direita - esquerda + 1);
        int rand3 = esquerda + random.nextInt(direita - esquerda + 1);

        int pivoInd = indiceMediana(array, rand1, rand2, rand3);

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

    static void quickSort(int[] array, int esquerda, int direita){
        if(esquerda < direita){
            int pivoIndFinal = particionar(array, esquerda, direita);

            quickSort(array, esquerda, pivoIndFinal - 1);
            quickSort(array, pivoIndFinal + 1, direita);
        }
    }

    static int[] lerArquivoEntrada(String file, int n) throws IOException{
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
            quickSort(arrayDados, 0, n - 1);
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
        quickSort(arrayMem, 0, n - 1);
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