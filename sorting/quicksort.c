#include <stdio.h>
#include <stdlib.h>

void quickSort(int *A, int beg, int end){
    if (beg >= end) { 
        return;
    }
    int pivot = beg;
    int pivotElem = A[end];
    int i = 0; 
    for (i = beg; i < end; i++) {
        if (A[i] < pivotElem) {
            int tmp = A[i];
            A[i] = A[pivot];
            A[pivot] = tmp;
            pivot++;
        }
    }
    int tmp = A[pivot];
    A[pivot] = A[end];
    A[end] = tmp;
    
    quickSort(A, beg, pivot - 1);
    quickSort(A, pivot + 1, end);
}

int main() {
	//code
	int numCases;
	scanf("%d", &numCases);
	int i = 0;
	for (i = 0; i < numCases;i++) {
	    int size = 0;
	    scanf("%d", &size);
	    int j = 0;
	    int *arr = (int *)malloc(sizeof(int) * size);
	    for(j = 0; j < size; j++) {
	        scanf("%d", &arr[j]);
	    }
	    quickSort(arr, 0, size - 1);
	    for (j = 0; j < size; j++) {
	        printf("%d ", arr[j]);
	    }
	    printf("\n");
	}
	return 0;
}
