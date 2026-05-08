/* 
    Compilar: javac -d quicksortjava/bin quicksortjava/common/*.java quicksortjava/algorithms/*.java quicksortjava/Main.java
    Executar: java -cp quicksortjava/bin quicksortjava.Main
*/
package quicksortjava;

import quicksortjava.algorithms.Quicksort;
import quicksortjava.algorithms.RandomizedQuicksort;
import quicksortjava.common.Benchmark;
import java.io.*;

public class Main{
    static final long SEED = 67;
    static final int[] TAMANHOS = {100, 1_000, 10_000, 100_000, 1_000_000};
    static final int REPS = 100;

    static final String CABECALHO =
        "+------------+--------------+------------------+--------------+\n" +
        "| Tamanho    | Repetições   | Tempo médio (ms) | Memória (KB) |\n" +
        "+------------+--------------+------------------+--------------+";
    
    static final String RODAPE = 
        "+------------+--------------+------------------+--------------+";

    public static void main(String[] args){
        File pasta = new File("inputs").exists() ? new File("inputs") : new File("quicksortjava/inputs");
        File[] arquivos = pasta.listFiles();

        if(arquivos == null || arquivos.length == 0){
            System.out.println("Nenhum arquivo encontrado na pasta inputs/");
            return;
        }

        try(PrintWriter output = new PrintWriter(new FileWriter("quicksortjava/output/output.dat"))){
            for(File arquivo : arquivos){
                output.println("========================================");
                output.println("Arquivo: " + arquivo.getName());
                output.println("========================================");

                String caminho = arquivo.getPath();

                output.println("--- Quicksort (Mediana de 3) ---");
                output.println(CABECALHO);
                for(int n : TAMANHOS)
                    Benchmark.executar(caminho, n, REPS, new Quicksort(SEED), output);
                output.println(RODAPE);
                
                output.println("\n--- Randomized Quicksort ---");
                output.println(CABECALHO);
                for(int n : TAMANHOS)
                    Benchmark.executar(caminho, n, REPS, new RandomizedQuicksort(SEED), output);
                output.println(RODAPE);
            }
        }catch(IOException e){
            System.err.println("Erro ao escrever output.dat: " + e. getMessage());
        }
    }
}