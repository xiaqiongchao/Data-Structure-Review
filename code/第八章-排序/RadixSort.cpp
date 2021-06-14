#include <stdio.h>
#include <stdlib.h>

typedef int ElemType; 

int GetNum(int num, int s);
void Distribute(int A[], int N, int j, int *radix_array[]);
void Collect(int A[], int N, int j, int *radix_array[]);
void RadixSort(int A[], int N);

int main()
{
    int A[10] = {21, 49, 38, 65, 97, 76, 13, 27, 49, 99};
    RadixSort(A, 10);
    for(int i=0; i<10; i++) printf("%d ", A[i]);
}

int GetNum(int num, int j){
	int temp=1;
	for(int i=0; i<j-1; i++) temp *= 10;
	return (num / temp)%10;
}
void Distribute(int A[], int N, int j, int *radix_array[]){
    for(int i=0; i<N; i++){
        int num = GetNum(A[i], j);
        int index = ++radix_array[num][0];
        radix_array[num][index] = A[i];
    }
}
void Collect(int A[], int N, int j, int *radix_array[]){
    for(int i=0, j=0; i<N; i++){
        for(int k=1; k<=radix_array[i][0]; k++)
            A[j++] = radix_array[i][k];
        radix_array[i][0] = 0;
    }
}
void RadixSort(int A[], int N){
    int *radix_array[10];
    for(int i=0; i<10; i++){
        radix_array[i] = (int *)malloc((N+1)*sizeof(int));
        radix_array[i][0] = 0;
    }
    for(int j=0; j<N; j++) {
        Distribute(A, N, j, radix_array);
        Collect(A, N, j, radix_array);
    }
}
