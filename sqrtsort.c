#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


void gen_random_numbers(int *arr, int size, int min, int max){
    for (int i =0; i < size; i++){
        arr[i] = rand() % (max - min + 1) + min;
    }
}

void bubbleSort(int arr[], int n) {
  int i, j, temp;
  for (i = 0; i < n - 1; i++) {
    for (j = 0; j < n - i - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
  }
}

void sqrtsort(int arr[], int n) {
    int part_size = (int)sqrt(n);
    int parts = n / part_size;

    while (parts > 0) {
        // Encontrar o maior elemento em cada parte
        double max_elements[parts];
        for (int i = 0; i < parts; i++) {
            int start = i * part_size;
            int end = (i + 1) * part_size - 1;
            if (i == parts - 1 && n % part_size != 0) {
                end = n - 1; 
            }
            bubbleSort(&arr[start], end - start + 1);
            max_elements[i] = arr[end];
        }

        // Encontrar o maior elemento dentre os max_elements
        int max_index = 0;
        for (int i = 1; i < parts; i++) {
            if (max_elements[i] > max_elements[max_index]) {
                max_index = i;
            }
        }

        // Inserir o maior elemento no final do vetor e remover da parte
        int index = max_index * part_size + part_size - 1;
        if (index < n - 1) {
            // Shiftar os elementos para a direita para criar espaço
            for (int i = n - 1; i > index; i--) {
                arr[i] = arr[i - 1];
            }
        }
        arr[index] = max_elements[max_index];
        parts--;
    }
}

int main() {
    clock_t start, end;
    int sizeN = 10000000;

    int *arr = (int*)malloc(sizeN * sizeof(int));
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        return 1;
    }

    srand(time(NULL));
    gen_random_numbers(arr, sizeN, 0, 100000000);

    start = clock();
    sqrtsort(arr, sizeN);
    end = clock();

    printf("\nTime taken by program is: %.10f sec\n", (((double) end - start) / CLOCKS_PER_SEC));

    free(arr);


    return 0;
}