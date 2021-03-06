#include <stdio.h>
#include <stdlib.h>

#define LEFT(n) (2 * n + 1)
#define RIGHT(n) (2 * n + 2)

void maxHeapify(int *arr, int size, int index);
void heapSort(int *arr, int size);
void swap(int *a, int *b);

void swap(int *a, int *b){
  int tmp = *a;
  *a = *b;
  *b = tmp;
}
void maxHeapify(int *arr, int size, int index) {
  int leftIndex = LEFT(index);
  int rightIndex = RIGHT(index);
  int largest = index;

  if (leftIndex < size && arr[largest] < arr[leftIndex]) {
    largest = leftIndex;
  }
  if (rightIndex < size && arr[largest] < arr[rightIndex]) {
    largest = rightIndex;
  }
  /**
   * Put the largest element at the root
   **/
  if (largest != index) {
    swap(&arr[index], &arr[largest]);
    maxHeapify(arr, size, largest);
  }
}
void heapSort(int *arr, int size) {
  /**
   * Convert the array to a maxHeap. We can assume that the array elements
   * from (n/2   - 1) are leaves of the complete binary tree which is our heap
   * and heapify the rest of the array from 0 to n/2 - 1
   **/
  int i = 0;
  for (i = (size/2 - 1); i >=0; i--){
    maxHeapify(arr, size, i);
  }
  printf("After maxHeapify\n");
  
  for (i = 0; i < size; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
  for(i = size  - 1; i > 0; i--) {
    swap(&arr[0], &arr[i]);
    maxHeapify(arr, i, 0);
  }
}

int main() {
  int count = 0;
  scanf("%d", & count);
  int *arr = (int *)malloc(sizeof(int) * count);
  int i = 0;
  for (i = 0; i < count; i++) {
    scanf("%d", &arr[i]);
  }
  printf("Before Sorting\n");
  
  for (i = 0; i < count; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
  heapSort(arr, count);

  printf("After Sorting\n");
  for (i = 0; i < count; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
  return 0;
}
