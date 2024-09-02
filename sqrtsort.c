#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// Function to generate random numbers in the array
void gen_random_numbers(int *arr, int size, int min, int max) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % (max - min + 1) + min;
    }
}

// Insertion sort for sorting parts
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// SqrtSort algorithm
void sqrtsort(int arr[], int n) {
    int part_size = (int)sqrt(n);
    int num_parts = (n + part_size - 1) / part_size; // Number of parts

    // Sort each part using insertion sort
    for (int i = 0; i < num_parts; i++) {
        int start = i * part_size;
        int end = (i + 1) * part_size - 1;
        if (end >= n) end = n - 1;
        insertionSort(&arr[start], end - start + 1);
    }

    // Array to store the final sorted result
    int *sorted = (int*)malloc(n * sizeof(int));
    if (sorted == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(1);
    }

    // Place to keep track of the current index in each part
    int *indexes = (int*)calloc(num_parts, sizeof(int));
    if (indexes == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        free(sorted);
        exit(1);
    }

    int count = 0;
    while (count < n) {
        int max_value = -1;
        int max_index = -1;

        // Find the largest element among the current elements of each part
        for (int i = 0; i < num_parts; i++) {
            int start = i * part_size;
            int end = (i + 1) * part_size - 1;
            if (end >= n) end = n - 1;

            if (indexes[i] <= (end - start)) { // Check if index is within the current part
                int value = arr[start + indexes[i]];
                if (value > max_value) {
                    max_value = value;
                    max_index = i;
                }
            }
        }

        // Place the largest element in the sorted array
        sorted[count++] = max_value;
        indexes[max_index]++;
    }

    // Copy sorted array back to the original array
    for (int i = 0; i < n; i++) {
        arr[i] = sorted[i];
    }

    free(sorted);
    free(indexes);
}


int main() {
    clock_t start, end;
    int sizeN = 100000000; // Adjusted size for practical testing

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

    //printArray(arr, sizeN);
    printf("\nTime taken by program is: %.10f sec\n", (((double) end - start) / CLOCKS_PER_SEC));

    free(arr);

    return 0;
}
