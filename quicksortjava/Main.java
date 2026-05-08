/*  
    *O TERMINAL PRECISA ESTAR NA PASTA RAIZ "trabalho2-AEDS" para funcionar...*
    
    Permissão: chmod +x javaRun.sh
    Executar: ./javaRun.sh
*/
package quicksortjava;

import java.util.Locale;

import quicksortjava.algorithms.Quicksort;
import quicksortjava.algorithms.RandomizedQuicksort;
import quicksortjava.common.Benchmark;
import quicksortjava.common.SortAlgorithm;

public class Main{
    static final long SEED = 67;
    static final int REPS = 100;
    
    public static void main(String[] args){
        if(args.length < 3){
            System.err.println("Está faltando algum dos argumentos na compilação!");
            System.exit(1);
        }
        
        String file = args[0];
        int n = Integer.parseInt(args[1]);
        String algoritmo = args[2];

        SortAlgorithm algoritmos = algoritmo.equals("qs") ? new Quicksort(SEED) : new RandomizedQuicksort(SEED);

        double avg = Benchmark.calcularTempo(file, n, REPS, algoritmos);

        System.out.printf(Locale.US, "%.4f%n", avg);
    }
}