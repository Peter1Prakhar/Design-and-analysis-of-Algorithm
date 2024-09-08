#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

bool compareArrays(int a[4], int b[4]) {
    int sum_a = a[0] + a[1] + a[2] + a[3];
    int sum_b = b[0] + b[1] + b[2] + b[3];
    
    if (sum_a < sum_b) return true;
    if (sum_a == sum_b) {
        for (int i = 3; i >= 0; i--) {
            if (a[i] > b[i]) return true;
            if (a[i] < b[i]) return false;
        }
    }
    return false;
}

void swapArrays(int a[4], int b[4]) {
    int temp;
    for (int i = 0; i < 4; i++) {
        temp = a[i];
        a[i] = b[i];
        b[i] = temp;
    }
}

void heapify(int k, int arr[100][4], int i) {
    if (i >= k) return;
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < k && compareArrays(arr[left], arr[smallest])) smallest = left;
    if (right < k && compareArrays(arr[right], arr[smallest])) smallest = right;
    if (smallest != i) {
        swapArrays(arr[i], arr[smallest]);
        heapify(k, arr, smallest);
    }
}

void buildHeap(int k, int arr[100][4]) {
    for (int i = k / 2 - 1; i >= 0; i--) heapify(k, arr, i);
}

void printHeap(int k, int arr[100][4]) {
    for (int i = 0; i < k; i++) {
        printf("[%d] ", i);
        for (int j = 0; j < 4; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}

void insert(int *k, int arr[100][4]) {
    printf("Enter a 4-element array (comma-separated): ");
    int newArray[4];
    for (int i = 0; i < 4; i++) scanf("%d", &newArray[i]);
    if (*k < 100) {
        for (int i = 0; i < 4; i++) arr[*k][i] = newArray[i];
        (*k)++;
        buildHeap(*k, arr);
        printf("After insertion:\n");
        printHeap(*k, arr);
    } else printf("Heap is full. Cannot insert.\n");
}

void pop(int *k, int arr[100][4]) {
    if (*k == 0) printf("Heap is empty. Cannot pop.\n");
    else {
        printf("Popped array: [");
        for (int i = 0; i < 4; i++) {
            printf("%d", arr[0][i]);
            if (i < 3) printf(", ");
        }
        printf("]\n");
        for (int i = 0; i < 4; i++) arr[0][i] = arr[(*k) - 1][i];
        (*k)--;
        heapify(*k, arr, 0);
        printf("After popping:\n");
        printHeap(*k, arr);
    }
}

void heapSort(int k, int arr[100][4]) {
    int original_k = k;
    for (int i = k - 1; i > 0; i--) {
        swapArrays(arr[0], arr[i]);
        k--;
        heapify(k, arr, 0);
    }
    printf("Sorted arrays:\n");
    for (int i = 0; i < original_k; i++) {
        for (int j = 0; j < 4; j++) printf("%d ", arr[i][j]);
        printf("\n");
    }
}

void generateRandomArrays(int n, int r, int *k, int arr[100][4]) {
    if (*k + r <= 100) {
        srand(time(NULL));
        for (int i = *k; i < *k + r; i++) {
            for (int j = 0; j < 4; j++) {
                arr[i][j] = rand() % n;
            }
        }
        *k += r;
        buildHeap(*k, arr);
        printf("Arrays before sorting:\n");
        printHeap(*k, arr);
        heapSort(*k, arr);
    } else printf("Heap will exceed the maximum size. Cannot generate random arrays.\n");
}

int main() {
    int k = 0;
    int MAX_SIZE = 100;
    int arr[100][4];
    int choice;
    while (1) {
        printf("\nOptions:\n1. Insert an array\n2. Pop the smallest array\n3. Sort arrays\n4. Generate random arrays\n5. Quit\nEnter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: insert(&k, arr); break;
            case 2: pop(&k, arr); break;
            case 3: heapSort(k, arr); break;
            case 4: {
                int n, r;
                printf("Enter the maximum value for array elements (n): ");
                scanf("%d", &n);
                printf("Enter the number of random arrays to generate (r): ");
                scanf("%d", &r);
                generateRandomArrays(n, r, &k, arr);
                break;
            }
            case 5: printf("Exiting.\n"); return 0;
            default: printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}
