package quicksortjava.common;

import java.io.IOException;

public class Benchmark{
    public static double calcularTempo(String file, int n, int reps, SortAlgorithm algoritmo){
        double tempoTotal = 0.0;

        int[] arrayOriginal;

        try{
            arrayOriginal = Utils.lerArquivo(file, n);
        }
        catch(IOException e){
            System.err.println("Erro: " + e.getMessage());
            return -1.0;
        }

        for(int rep = 0; rep < reps; rep++){
            int[] array = arrayOriginal.clone();

            long t0 = System.nanoTime();
            algoritmo.sort(array, 0, n - 1);
            long t1 = System.nanoTime();

            tempoTotal += Utils.calcularTempoMs(t0, t1);
        }
        return tempoTotal / reps;
    }
}
