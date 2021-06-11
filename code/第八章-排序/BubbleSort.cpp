#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

void BubbleSort(ElemType A[], int n);

int main()
{
    int A[10] = {0, 49, 38, 65, 97, 76, 13, 27, 49, 99};
    BubbleSort(A, 10);
    for(int i=1; i<10; i++) printf("%d ", A[i]);

}

void BubbleSort(ElemType A[], int n){
    int i, j, flag;
    for(i=0; i<n; i++){
        flag = false;
        for(j=n-1; j>i; j--)
            if(A[j-1] > A[j]){
                int temp = A[j];
                A[j] = A[j-1];
                A[j-1] = temp;
                flag = true;
            }
        if(flag==false) return;
    }
}