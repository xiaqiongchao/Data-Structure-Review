#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

void HeapSort(ElemType A[], int len);
void BuildMaxHeap(ElemType A[], int len);
void HeadAdjust(ElemType A[], int k, int len);

int main()
{
    int A[10] = {0, 49, 38, 65, 97, 76, 13, 27, 49, 99};
    HeapSort(A, 9);
    for(int i=1; i<10; i++) printf("%d ", A[i]);

}
void HeapSort(ElemType A[], int len){
    BuildMaxHeap(A, len);
    for(int i=len; i>1; i--){
        int temp = A[i];
        A[i] = A[1]; 
        A[1] = temp;
        HeadAdjust(A, 1, i-1);
    }
}
void BuildMaxHeap(ElemType A[], int len){
    for(int i=len/2; i>0; i--)  HeadAdjust(A, i, len);
}
void HeadAdjust(ElemType A[], int k, int len){
    A[0] = A[k];
    for(int i=2*k; i<len; i*=2){
        if(i<len && A[i]<A[i+1]) i++;
        if(A[0] >= A[i]) break;
        else {
            A[k] = A[i]; 
            k = i;
        }
    }
    A[k] = A[0];
}
