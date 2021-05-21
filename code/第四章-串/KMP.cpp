#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 255
typedef struct {
    char ch[MAXLEN];
    int length;
}SString;

bool StrAssign(SString &T, char *chars);
void PrintString(SString S);

int Index_BF(SString S, SString T);         // 朴素匹配 最坏时间复杂度O(m*n)    
int Index_KMP(SString S, SString T);        // KMP匹配 最坏时间复杂度O(m+n)

void get_next(SString T, int next[]);
void get_nextval(SString T, int nextval[]);

int main()
{
    SString S, T;
    char teststr[255];

    printf("请输入主串S："); scanf("%s", &teststr);
    if(StrAssign(S, teststr)) PrintString(S);
    printf("请输入子串T："); scanf("%s", &teststr);
    if(StrAssign(T, teststr)) PrintString(T);
    printf("%d, %d\n", S.length, T.length);
    
    printf("BF模式匹配位置为：%d\n", Index_BF(S, T));
    // printf("KMP模式匹配位置为：%d\n", Index_KMP(S, T));
    printf("优化的KMP匹配位置：%d\n", Index_KMP(S, T));
    
}

bool StrAssign(SString &T, char *chars){
    int i, len;
    len = (int)strlen(chars);
    if(len > MAXLEN) return false;
    for(i=1; i<=len; i++) T.ch[i] = chars[i-1];
    T.length = len;
    return true;
}
void PrintString(SString S){
    for(int i=1; i<=S.length; i++) printf("%c", S.ch[i]);
    printf("\n");
}

int Index_BF(SString S, SString T){
    int i=1, j=1;
    while(i<=S.length && j<=T.length){
        if(S.ch[i] == T.ch[j]){
            i++; 
            j++;
        } else {
            i = i-j+2;                      // 重要
            j = 1;
        }
    }
    if(j > T.length) return i-T.length;
    else return 0;
}

int Index_KMP(SString S, SString T){
    int i=1, j=1;
    
    // int next[T.length+1];
    // get_next(T, next);
    
    // 对KMP算法进行优化
    int nextval[T.length+1];
    get_nextval(T, nextval);

    while(i<=S.length && j<=T.length){
        if(j==0 || S.ch[i] == T.ch[j]){        // 重要
            i++;
            j++;
        } else {
            // j = next[j];                    // 重要
            j = nextval[j];
        }
    }
    if(j > T.length) return i-T.length;
    else return 0;
}

void get_next(SString T, int next[]){
    int i=1, j=0;
    next[i] = 0;                           // 重要
    while(i < T.length){
        if(j==0 || T.ch[i]==T.ch[j]){
            i++; j++; 
            next[i] = j;
        }
        else j = next[j];
    }
}
void get_nextval(SString T, int nextval[]){
    int i=1, j=0;
    nextval[1] = 0;
    while(i < T.length){
        if(j==0 || T.ch[i]==T.ch[j]){
            i++; j++;
            if(T.ch[i] != T.ch[j]) nextval[i] = j;  // 重要
            else nextval[i] = nextval[j];
        }
        else j = nextval[j];
    }
}
