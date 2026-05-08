package quicksortjava.common;

@FunctionalInterface
public interface SortAlgorithm{
    void sort(int[] array, int esquerda, int direita);
}
