package quicksortjava.algorithms;

import quicksortjava.common.SortAlgorithm;
import quicksortjava.common.Utils;
import java.util.Random;

public class RandomizedQuicksort implements SortAlgorithm{
    private final Random random;

    public RandomizedQuicksort(long seed){
        this.random = new Random(seed);
    }

    private int indiceAleatorio(int esquerda, int direita){
        return esquerda + random.nextInt(direita - esquerda + 1);
    }

    private int particionar(int[] array, int esquerda, int direita){
        int pivoInd = indiceAleatorio(esquerda, direita);

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
