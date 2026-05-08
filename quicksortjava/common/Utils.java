package quicksortjava.common;

import java.io.BufferedInputStream;
import java.io.FileInputStream;
import java.io.IOException;

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
        try(BufferedInputStream bis = new BufferedInputStream(new FileInputStream(file))){
            int[] array = new int[n];

            int c;

            while((c = bis.read()) != '\n'){
                if(c == -1)
                    throw new IOException("Arquivo inválido");
            }

            int i = 0;
            int num = 0;
            boolean lendoNumero = false;

            while((c = bis.read()) != -1 && i < n){
                if(c >= '0' && c <= '9'){
                    num = num * 10 + (c - '0');
                    lendoNumero = true;
                }
                else{
                    if(lendoNumero){
                        array[i++] = num;
                        num = 0;
                        lendoNumero = false;
                    }
                }
            }

            if(lendoNumero && i < n)
                array[i++] = num;

            if(i < n)
                throw new IOException("Arquivo tem menos de " + n + " valores");

            return array;
        }
    }
}
