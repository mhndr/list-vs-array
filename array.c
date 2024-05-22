#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <string.h>


int binarySearch(int64_t arr[], int size, int64_t key) {
    int left = 0;
    int right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == key) {
            return mid;
        } else if (arr[mid] < key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return left; 
}

void insertSorted(int64_t arr[], int *size, int64_t key) {

    int pos = binarySearch(arr, *size, key);

    // Move elements to the right to create space for the new element
 /* 
    for (int i = *size; i > pos; i--) {
        arr[i] = arr[i - 1];
    }
 */
    memmove(&arr[pos + 1], &arr[pos], (*size - pos) * sizeof(int64_t));

    arr[pos] = key;
    (*size)++;
}

void printArray(int64_t arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%lld ", arr[i]);
    }
    printf("\n");
}

int main(int argc, char **argv){
    int64_t *arr;
    int size = 0;

	if(argc<2) {
		printf("\nusage: ll_test SIZE");
		return -1;
	}

	srand(time(NULL));
	int SIZE = atoi(argv[1]);
	arr = malloc(sizeof(int64_t)*SIZE);
	for(int i=0;i<SIZE;i++) {
		int r = rand()%SIZE;
	    insertSorted(arr, &size, r);
	}
//    printArray(arr, size); 

    return 0;
}
