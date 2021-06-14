#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

void Merge(ElemType A[], int low, int mid, int high);
void MergeSort(ElemType A[], int low, int high);

int main()
{
    int A[10] = {0, 49, 38, 65, 97, 76, 13, 27, 49, 99};
    MergeSort(A, 0, 9);
    for(int i=1; i<10; i++) printf("%d ", A[i]);

}

ElemType *B = (ElemType *)malloc((10+1)*sizeof(ElemType));
void Merge(ElemType A[], int low, int mid, int high){
    int i, j, k;
    for(k=low; k<=high; k++) B[k] = A[k];
    for(i=low, j=mid+1, k=i; i<=mid && j<=high; k++)
        if(B[i] <= B[j]) A[k] = B[i++];
        else A[k] = B[j++];
    while(i <= mid) A[k++] = B[i++];
    while(j <= high) A[k++] = B[j++];
}

void MergeSort(ElemType A[], int low, int high){
    if(low < high){
        int mid = (low + high)/2;
        MergeSort(A, low, mid);
        MergeSort(A, mid+1, high);
        Merge(A, low, mid, high);
    }
}