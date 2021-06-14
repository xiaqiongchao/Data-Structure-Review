#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

void SelectSort(ElemType A[], int n);

int main()
{
    int A[10] = {0, 49, 38, 65, 97, 76, 13, 27, 49, 99};
    SelectSort(A, 10);
    for(int i=1; i<10; i++) printf("%d ", A[i]);

}

void SelectSort(ElemType A[], int n){
    for(int i=0; i<n-1; i++){
        int min = i; 
        for(int j=i+1; j<n; j++)
            if(A[j] < A[min]) min = j;
        if(min != i){
            int temp = A[i];
            A[i] = A[min];
            A[min] = temp;
        }
    }
}