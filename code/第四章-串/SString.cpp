#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 这里按王道给的实现方式
#define MAXLEN 255
typedef struct {
    char ch[MAXLEN];
    int length;
}SString;

bool StrAssign(SString &T, char *chars);
bool StrCopy(SString &T, SString S);
bool StrEmpty(SString S);
int StrCompare(SString S, SString T);
int StrLength(SString S);
bool SubString(SString &Sub, SString S, int pos, int len);
bool Concat(SString &T, SString S1, SString S2);
int Index(SString S, SString T);
bool ClearString(SString &S);
bool DestroyString(SString &S);
void PrintString(SString S);    

int main()
{
    char teststr[255];
    SString T, S;

    printf("请输入测试串T："); scanf("%s", &teststr);
    if(StrAssign(T, teststr)) PrintString(T);
    printf("请输入测试串S："); scanf("%s", &teststr);
    if(StrAssign(S, teststr)) PrintString(S);

    // if(StrCopy(T, S)) PrintString(T);

    if(StrEmpty(S)) printf("串为空！\n");
    else printf("串非空！\n");

    int mark = StrCompare(S, T);
    if(mark == 0) printf("两串相等！\n");
    else if (mark < 0) printf("S串小于T串！\n");
    else printf("S串大于T串！\n");

    // SString Sub;
    // SubString(Sub, S, 2, 5); PrintString(Sub);

    // SString X;
    // Concat(X, T, S); PrintString(X);
    printf("子串匹配：%d\n", Index(S, T));
}

void PrintString(SString S){
    for(int i=1; i<=S.length; i++) printf("%c", S.ch[i]);
    printf("\n");
}

bool StrAssign(SString &T, char *chars){
    int i, len;
    len = (int)strlen(chars);
    if(len > MAXLEN) return false;

    T.length = len; // 第一个元素不用
    for(i=1; i<=len; i++) T.ch[i] = chars[i-1];
    return true;
}
bool StrCopy(SString &T, SString S){
    for(int i=1; i<=S.length; i++) T.ch[i] = S.ch[i];
    T.length = S.length;
    return true;
}
bool StrEmpty(SString S){
    if(S.length == 0) return true;
    else return false;
}
// 比较操作，若S>T，则返回值>0，若S=T，则返回值=0，若S<T，则返回值<0
int StrCompare(SString S, SString T){
    int i = 1;
    while(i<=S.length && i<=T.length){
        if(S.ch[i] != T.ch[i]) return S.ch[i] - T.ch[i];
        i++;
    }
    return S.ch[i] - T.ch[i];
}
int StrLength(SString S){
    return S.length;
}
bool SubString(SString &Sub, SString S, int pos, int len){     // 求子串
    if(pos+len-1 > MAXLEN) return false;    // 子串范围越界
    for(int i=pos; i<pos+len; i++)
        Sub.ch[i-pos+1] = S.ch[i];
    Sub.length = len;
    return true;
}
// 拼接 T=S1+S2
bool Concat(SString &T, SString S1, SString S2){
    int i=1, j=1;
    for(; i<MAXLEN && i<=S1.length; i++) T.ch[i] = S1.ch[i];
    for(; i<MAXLEN && j<=S2.length; j++) T.ch[i++] = S2.ch[j];
    T.length = i;
    return true;
}
int Index(SString S, SString T){
    int i=1, n=StrLength(S), m=StrLength(T);
    SString sub;
    while(i <= n-m+1){
        SubString(sub, S, i, m);
        if(StrCompare(sub, T) != 0) i++;
        else return i;
    }
    return 0;
}
bool ClearString(SString S){
    S.length = 0;
    return true;
}
bool DestroyString(SString S){
    return false;               // 顺序串无法销毁
}