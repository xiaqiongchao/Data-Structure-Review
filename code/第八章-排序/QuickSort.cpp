#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

void QuickSort(ElemType A[], int low, int high);
int Partition(ElemType A[], int low, int high);

int main()
{
    int A[10] = {0, 49, 38, 65, 97, 76, 13, 27, 49, 99};
    QuickSort(A, 0, 9);
    for(int i=0; i<10; i++) printf("%d ", A[i]);

}

void QuickSort(ElemType A[], int low, int high){
    if(low < high){
        int pivotpos = Partition(A, low, high);
        QuickSort(A, low, pivotpos-1);
        QuickSort(A, pivotpos+1, high);
    }
}
int Partition(ElemType A[], int low, int high){
    ElemType pivot = A[low];
    while(low < high){
        while(low<high && A[high]>=A[pivot]) high--;
        A[low] = A[high];
        while(low<high && A[low]<=A[pivot]) low++;
        A[high] = A[low];
    }
    A[low] = pivot;
    return low;
}