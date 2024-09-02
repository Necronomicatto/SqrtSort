#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

void gen_random_numbers(int *arr, int size, int min, int max){
    for (int i =0; i < size; i++){
        arr[i] = rand() % (max - min + 1) + min;
    }
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to heapify a subtree rooted at index 'i'
// n is size of heap
void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

// Function to build a max heap
void buildHeap(int arr[], int n) {
    int startIdx = (n / 2) - 1;
    for (int i = startIdx; i >= 0; i--) {
        heapify(arr, n, i);
    }
}

// Subroutine to sort a small sub-array using heap sort
void subarraySort(int arr[], int left, int right) {
    int size = right - left + 1;
    buildHeap(arr + left, size);

    for (int i = size - 1; i > 0; i--) {
        swap(&arr[left], &arr[left + i]);
        heapify(arr + left, i, 0);
    }
}

// In-place merging of two sorted sub-arrays
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int i = 0, j = 0, k = left;

    // Temporary arrays to store left and right subarrays
    int* leftArr = malloc(n1 * sizeof(int));
    int* rightArr = malloc(n2 * sizeof(int));

    for (i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }

    free(leftArr);
    free(rightArr);
}

// SqrtSort algorithm - sorts the entire array
void SqrtSort(int arr[], int n) {
    int subarraySize = sqrt(n);

    // Step 1: Sort each sub-array of size sqrt(n) using heap sort
    for (int i = 0; i < n; i += subarraySize) {
        int end = i + subarraySize - 1;
        if (end >= n) {
            end = n - 1;
        }
        subarraySort(arr, i, end);
    }

    // Step 2: Iteratively merge the sorted sub-arrays
    for (int size = subarraySize; size < n; size *= 2) {
        for (int left = 0; left < n - size; left += 2 * size) {
            int mid = left + size - 1;
            int right = (left + 2 * size - 1 < n) ? left + 2 * size - 1 : n - 1;
            merge(arr, left, mid, right);
        }
    }
}

// Print the sorted array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}



int main() {
    clock_t start, end;
    int n = 100000000;

    int *arr = (int*)malloc(n * sizeof(int));
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        return 1;
    }

    srand(time(NULL));
    gen_random_numbers(arr, n, 0, 100000000);


    start = clock();
    SqrtSort(arr, n);
    end = clock();

    //printArray(arr, n);
    //isSorted(arr, n);
    
    printf("\nTime taken by program is: %.10f sec\n", (((double) end - start) / CLOCKS_PER_SEC));

    free(arr);

    return 0;
}
