#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

void InsertSort(ElemType A[], int n);

int main()
{
    int A[10] = {0, 49, 38, 65, 97, 76, 13, 27, 49, 99};
    InsertSort(A, 10);
    for(int i=1; i<10; i++) printf("%d ", A[i]);

}

void InsertSort(ElemType A[], int n){
    int i, j;
    for(i=2; i<n; i++){
        if(A[i] < A[i-1]){
            A[0] = A[i];                        // ÉèÖÃ¡±ÉÚ±ø¡°
            for(j=i-1; A[0]<A[j]; j--) A[j+1] = A[j];
            A[j+1] = A[0];
        }
    }
}