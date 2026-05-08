package quicksortjava.algorithms;

import quicksortjava.common.SortAlgorithm;
import quicksortjava.common.Utils;
import java.util.Random;

public class Quicksort implements SortAlgorithm{
    private final Random random;

    public Quicksort(long seed){
        this.random = new Random(seed);
    }

    private int indiceMediana(int[] array, int e, int m, int d){
        int a = array[e], b = array[m], c = array[d];

        if((a <= b && b <= c) || (c <= b && b <= a)) return m;
        if((b <= a && a <= c) || (c <= a && a <= b)) return e;

        return d;
    }

    private int particionar(int[] array, int esquerda, int direita){
        int r1 = esquerda + random.nextInt(direita - esquerda + 1);
        int r2 = esquerda + random.nextInt(direita - esquerda + 1);
        int r3 = esquerda + random.nextInt(direita - esquerda + 1);
        
        int pivoInd = indiceMediana(array, r1, r2, r3);

        Utils.swap(array, pivoInd, direita);

        int pivo = array[direita];
        int i = esquerda - 1;

        for(int j = esquerda; j < direita; j++)
                if(array[j] <= pivo) Utils.swap(array, ++i, j);
        Utils.swap(array, i + 1, direita);

        return i + 1;
    }

    @Override
    public void sort(int[] array, int esquerda, int direita){
        if(esquerda < direita){
            int p = particionar(array, esquerda, direita);

            sort(array, esquerda, p - 1);
            sort(array, p + 1, direita);
        }
    }
}
