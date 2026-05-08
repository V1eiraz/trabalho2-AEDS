package quicksortjava.common;

import java.io.PrintWriter;

public class Benchmark{
    public static void executar(String file, int n, int reps, SortAlgorithm algoritmo, PrintWriter output){
        // TEMPO MÉDIO
        double tempoTotal = 0.0;

        for(int rep = 0; rep < reps; rep++){
            int[] array;

            try{
                array = Utils.lerArquivo(file, n);
            }
            catch(Exception e){
                System.out.println("Erro: " + e.getMessage());
                return;
            }

            long t0 = System.nanoTime();
            algoritmo.sort(array, 0, n - 1);
            long t1 = System.nanoTime();
            
            tempoTotal += Utils.calcularTempoMs(t0, t1);
        }
        double avg = tempoTotal / reps;

        // MEMÓRIA
        Runtime rt = Runtime.getRuntime();
        System.gc();

        long m0 = rt.totalMemory() - rt.freeMemory();

        try{
            int[] arrayMem = Utils.lerArquivo(file, n);
            algoritmo.sort(arrayMem, n, reps);
        }
        catch(Exception e){
            System.out.println("Erro: " + e.getMessage());
            return;
        }
        long deltaKB = (rt.totalMemory() - rt.freeMemory() - m0) / 1024;

        String linha = String.format("| %-10d | %-12d | %-16.4f | %-12d |", n, reps, avg, deltaKB);

        output.println(linha);
    }
}
