#include <stdio.h>
#include <stdlib.h>

#define MAX_NUM 10
typedef int ElemType;

typedef struct {
    ElemType *elem;
    int TableLen;
}SSTable;

void Create(SSTable &ST);
void Print(SSTable ST);
int SeqSearch(SSTable ST, ElemType key);

int main()
{
    SSTable ST; Create(ST); Print(ST);
    printf("%d所在的位置为:%d", 19, SeqSearch(ST, 19));
}

void Create(SSTable &ST){
    ST.elem = (ElemType *)malloc(MAX_NUM*sizeof(ElemType));
    ST.TableLen = MAX_NUM;
    for(int i=0; i<ST.TableLen; i++) ST.elem[i] = i*i+3;
}
void Print(SSTable ST){
    for(int i=0; i<ST.TableLen; i++) printf("%d ", ST.elem[i]);
    printf("\n");
}
int SeqSearch(SSTable ST, ElemType key){
    ST.elem[0] = key;
    printf("%d", ST.elem[ST.TableLen-1]);
    for(int i=ST.TableLen-1; ST.elem[i]!=key; --i)
    return i;
}