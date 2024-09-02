#include <stdio.h>
#include <math.h>

// Function to swap two elements
void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

// Function to heapify a subtree rooted at index 'i'
// n is size of heap
void heapify(int arr[], int n, int i) {
  int largest = i;
  int left = 2 * i + 1; // left = 2*i + 1
  int right = 2 * i + 2; // right = 2*i + 2

  // If left child is larger than root
  if (left < n && arr[left] > arr[largest])
    largest = left;

  // If right child is larger than largest so far
  if (right < n && arr[right] > arr[largest])
    largest = right;

  // If largest is not root
  if (largest != i) {
    swap(&arr[i], &arr[largest]);
    heapify(arr, n, largest);
  }
}

// Function to build a max heap
void buildHeap(int arr[], int n) {
  int startIdx = (n / 2) - 1; // start from (n / 2) - 1 because the parent is at index (i - 1)
  for (int i = startIdx; i >= 0; i--) {
    heapify(arr, n, i);
  }
}

// Subroutine to sort a small sub-array using heap sort (works for any size sub-array)
void subarraySort(int arr[], int left, int right) {
  buildHeap(arr + left, right - left + 1); // Build a max heap within the sub-array

  // One by one extract an element from heap
  for (int i = right - left; i >= 0; i--) {
    // Move current root element to end
    swap(&arr[left + i], &arr[left + right - left]);

    // call max heapify on the reduced heap
    heapify(arr + left, i, 0);
  }
}

// SqrtSort algorithm - sorts the entire array
void SqrtSort(int arr[], int n) {
  int subarraySize = sqrt(n);

  // Find the largest elements progressively using subarraySort (heap sort)
  for (int i = 0; i < n; i += subarraySize) {
    int end = i + subarraySize - 1;
    if (end >= n) {
      end = n - 1;
    }
    subarraySort(arr, i, end);
  }

  // Sort the remaining sub-array and identified largest elements recursively
  int remaining = n - subarraySize;
  if (remaining > 0) {
    SqrtSort(arr + remaining, remaining);
    SqrtSort(arr, subarraySize);
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
  int arr[] = {16, 10, 15, 2, 1, 8, 6, 4, 3, 5};
  int n = sizeof(arr) / sizeof(arr[0]);

  printf("Unsorted array: \n");
  printArray(arr, n);

  SqrtSort(arr, n);

  printf("Sorted array: \n");
  printArray(arr, n);

  return 0;
}
