package quicksortjava.common;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.StreamTokenizer;

public class Utils{
    public static double calcularTempoMs(long inicio, long fim){
        return (fim - inicio) / 1e6;
    }

    public static void swap(int[] array, int a, int b){
        int temp = array[a];
        array[a] = array[b];
        array[b] = temp;
    }

    public static int[] lerArquivo(String file, int n) throws IOException{
        int[] array = new int[n];
        StreamTokenizer st = new StreamTokenizer(new BufferedReader(new FileReader(file)));
        
        for(int i = 0; i < n; i++){
            if(st.nextToken() == StreamTokenizer.TT_EOF)
                throw new IOException("Arquivo tem menos de " + n + " valores");
            array[i] = (int) st.nval;
        }
        return array;
    }
}
