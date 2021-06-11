#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

void ShellSort(ElemType A[], int n);

int main()
{
    int A[10] = {0, 49, 38, 65, 97, 76, 13, 27, 49, 99};
    ShellSort(A, 10);
    for(int i=1; i<10; i++) printf("%d ", A[i]);

}

void ShellSort(ElemType A[], int n){
    int i, j, dk;
    for(dk=n/2; dk>=1; dk/=2){
        for(i=dk+1; i<n; i++){
            if(A[i] < A[i-dk]){
                A[0] = A[i];
                for(j=i-dk; j>0 && A[0]<A[j]; j-=dk) A[j+dk] = A[j];
                A[j+dk] = A[0];
            }
        }
    }
}