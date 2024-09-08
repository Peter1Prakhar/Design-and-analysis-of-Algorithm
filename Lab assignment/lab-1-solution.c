#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void merge(long long int arr[], int l, int m, int r)
{
    long long int i, j, k;
    long long int n1 = m - l + 1;
    long long int n2 = r - m;
    long long int L[n1], R[n2];
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        // if (L[i] == R[j])
        // {
        //     arr[k] = L[i];
        //     i++;
        //     k++;
        //     arr[k] = R[j];
        //     j++;
        //     k++;
        // }
        long long int x = L[i], y = R[j];
        while(x>0 && y>0){
            long long int num1 = x % 10;
            long long int num2 = y % 10;
            if (num1 < num2)
            {
                arr[k] = L[i];
                i++;
                k++;
                break;
            }
            else if (num1 > num2)
            {
                arr[k] = R[j];
                j++;
                k++;
                break;
            }
            else
            {
                x = x / 10;
                y = y / 10;
            }
        }
    }
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}
void mergeSort(long long int arr[], int l, int r)
{
    if (l < r)
    {

        long long int m = (r + l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}
void printArray(long long int A[], int size)
{
    long long int i;
    for (i = 0; i < size; i++)
        printf("%llu       ", A[i]);
    printf("\n");
}
int main()
{
    
    long long int n;
    printf("Enter the no. \n");
    scanf("%llu",&n);
    long long int arr[n];
    long long int m;
    printf("Enter the no. \n");
    scanf("%llu",&m);

    long long lower = 1;
    long long upper;
    for (long long  i=1; i<m;i++){
        lower = lower*10;
    }
    upper = lower*10 - 1;
    for (int i = 0; i < n; i++) {
        arr[i] = (rand() %  (upper - lower + 1)) + lower;
    }

    printf("Given array is \n");
    printArray(arr, n);

    mergeSort(arr, 0, n - 1);

    printf("\nSorted array is \n");
    printArray(arr, n);
    return 0;
}