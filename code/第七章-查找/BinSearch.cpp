#include <stdio.h>
#include <stdlib.h>

#define LEN 10

int Binary_Search_1(int A[LEN], int key);
int Binary_Search_2(int A[LEN], int key, int low, int high);

int main()
{
    int A[LEN];
    for(int i=0; i<LEN; i++) A[i] = i*i+1;
    for(int i=0; i<LEN; i++) printf("%d ", A[i]); printf("\n");

    printf("%d \n", Binary_Search_1(A, 17)+1);
    printf("%d \n", Binary_Search_2(A, 17, 0, LEN)+1);
}

// ·ÇµÝ¹é
int Binary_Search_1(int A[], int key){
    int low=0, high=LEN-1, mid;
    while(low <= high){
        mid = (low+high) / 2;
        if(A[mid] == key) return mid;
        else if(A[mid] < key) low = mid+1;
        else high = mid-1;
    }
    return -1;
}
// µÝ¹é
int Binary_Search_2(int A[LEN], int key, int low, int high){
    if(low > high) return 0;
    int mid = (low+high) / 2;
    if(A[mid] > key) 
        return Binary_Search_2(A, key, low, mid-1);
    else if(A[mid] < key) 
        return Binary_Search_2(A, key, mid+1, high);
    else return mid;
}