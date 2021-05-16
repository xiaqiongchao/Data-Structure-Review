#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 20
#define INIT_SIZE 10
#define INCR_SIZE 10

typedef int ElemType;

// 静态分配
typedef struct {
    int data[MAX_SIZE];
    int length;
}SqList;
//动态分配
typedef struct {
    int *data;
    int MaxSize;
    int length;
}D_SqList;

bool InitList(SqList &L);                       // 静态初始化
bool D_InitList(D_SqList &L);                   // 动态初始化
bool DestroyList(SqList &L);                    // 销毁表
bool ClearList(SqList &L);                      // 清空表
bool ListEmpty(SqList L);                       // 判断非空
int ListLength(SqList L);                       // 求表长
int GetElem(SqList L, int i);                   // 按位查找
int LocateElem(SqList L, int e);                // 按值查找
bool PriorElem(SqList L, int e, int &pre_e);    // 返回前驱
bool NextElem(SqList L, int e, int &next_e);    // 返回后继
bool ListInsert(SqList &L, int i, int e);       // 插入元素
bool ListDelete(SqList &L, int i, int &e);      // 删除元素
void TraverseList(SqList L);                    // 打印输出

void BasicFunTest();                            // 用于测试基本功能函数

///王道课后习题代码实现  p19
bool Del_Min(SqList &L, int &value);            // 删除最小元素
void Reverse(SqList &L);                        // 顺序表逆置
void Del_x(SqList &L, int x);                   // 删除所有等于x的元素
bool Del_s_t(SqList &L, int s, int t);          // 删除所有s-t之间的元素
bool Delete_same(SqList &L);                    // 删除表中所有重复的元素
bool Merge(SqList A, SqList B, D_SqList &C);    // 顺序表的合并，需要牢固掌握
void SearchChangeInsert(SqList &L, int x);      // 有序表的二分搜索+交换+插入

int main()
{
    // BasicFunTest();

    // SqList OrderlyList;
    // InitList(OrderlyList);
    // for(int i=0; i<10; i++){
    //     OrderlyList.data[i] = i*i + 1;
    //     OrderlyList.length++;
    // }
    // TraverseList(OrderlyList);

    // Reverse(OrderlyList);

    // int value;
    // Del_Min(OrderlyList, value);
    // TraverseList(OrderlyList);

    // Del_x(OrderlyList, 26);
    // TraverseList(OrderlyList);

    // Del_s_t(OrderlyList, 10, 50);
    // TraverseList(OrderlyList);

    // OrderlyList.length = 0;
    // for(int i=0; i<10; i++){
    //     OrderlyList.data[i] = 3;
    //     OrderlyList.length++;
    // }
    // TraverseList(OrderlyList);
    // Delete_same(OrderlyList);
    // TraverseList(OrderlyList);
    
    // // 合并测试
    // SqList A, B;
    // D_SqList C;
    // InitList(A);
    // InitList(B);
    // D_InitList(C);
    // for(int i=0; i<10; i++){
    //     A.data[i] = i + 1;
    //     A.length++;
    // }
    // for(int i=0; i<10; i++){
    //     B.data[i] = (i + 1)*3;
    //     B.length++;
    // }
    // TraverseList(A);printf("\n");
    // TraverseList(B);printf("\n");

    // Merge(A, B, C);
    // for(int i=0; i<C.length; i++)
    //     printf("%d ", C.data[i]);
    // printf("\n合并表C的长度为：%d\n", C.length);

    // SqList A;
    // InitList(A);
    // for(int i=0; i<9; i++){
    //     A.data[i] = i*i+1;
    //     A.length++;
    // }
    // TraverseList(A);
    // SearchChangeInsert(A, 26);
    // TraverseList(A);

}

void BasicFunTest(){
        SqList TestList;
    if(InitList(TestList)) printf("静态分配初始化成功！\n");
    else printf("动态分配初始化失败！\n");

    for(int i = 0; i < 10; i++){
        TestList.data[i] = i*i+3;
        TestList.length++;
    }
    TraverseList(TestList);

    D_SqList D_TestList;
    if(D_InitList(D_TestList)) printf("动态分配初始化成功！\n");
    else printf("动态分配初始化失败！\n");

    if(ListEmpty(TestList)) printf("此表为空表！\n");
    else printf("此表不为空表！\n");

    printf("当前表长为：%d\n", ListLength(TestList));
    // if(GetElem(TestList, 100)) printf("查找成功！\n");
    // else printf("查找失败！\n");
    printf("第3个元素为：%d\n", GetElem(TestList, 3));

    printf("52所在位序：%d\n", LocateElem(TestList, 52));

    int b = 666;
    if(ListInsert(TestList, 7, b)){
        printf("插入成功！插入的元素为：%d\n", b);
        TraverseList(TestList);
    } else printf("插入失败！\n");

    int a;
    if(ListDelete(TestList, 8, a)){
        printf("删除成功！删除的元素为：%d\n", a);
        TraverseList(TestList);
    } else printf("删除失败\n");
}

// 静态分配初始化
bool InitList(SqList &L){
    for(int i=0; i<MAX_SIZE; i++)
        L.data[i]=0;
    L.length=0;
    return true;
}
// 动态分配初始化
bool D_InitList(D_SqList &L){
    L.data = (int *)malloc(INIT_SIZE*sizeof(int)*10);
    if(L.data == NULL) return false;
    L.length = 0;
    L.MaxSize = INIT_SIZE*10;
    return true;
}
// 针对动态创建的销毁方式
bool DestroyList(D_SqList &L){
    if(L.data == NULL) return false;
    free(L.data);
    L.data = NULL;
    L.length = 0;
    L.MaxSize = 0;
    return true;
}
// 并不回收空间
bool ClearList(SqList &L){
    L.length = 0;
    return true;
}
// 判断表是否为空
bool ListEmpty(SqList L){
    return L.length == 0 ? true : false;
}
// 返回表长
int ListLength(SqList L){
    return L.length;
}
// 按位查找 查找i的范围为[1, length]，找到则返回对应的值
int GetElem(SqList L, int i){
    if(i < 1 || i > L.length) return -1;
    return L.data[i - 1];
}
// 按值查找，找到则返回位序；
int LocateElem(SqList L, int e){
    for(int i = 0; i < L.length; i++)
        if(L.data[i] == e)  return i+1;
    return -1;
}
// 插入元素，插入的位序在[i, length]之间
bool ListInsert(SqList &L, int i, int e){
    if(i < 1 || i > L.length+1) return false;   // 插入位置不合法
    if(L.length >= MAX_SIZE)    return false;   // 当前表已满
    for(int j=L.length; j>=i; j--)
        L.data[j] = L.data[j-1];                // 元素依次后移
    L.data[i-1] = e;
    L.length++;
    return true;
}
// 删除元素，删除的位序在[i, length]之间
bool ListDelete(SqList &L, int i, int &e){
    if(i < 1 || i > L.length+1) return false;
    e = L.data[i - 1];
    for(int j=i; j<L.length; j++)
        L.data[j-1] = L.data[j];
    L.length--;
    return true;    
}
// 遍历输出该表
void TraverseList(SqList L){
    for(int i = 0; i < L.length; i++)
        printf("%d ", L.data[i]);
    printf("\n");
}


/******王道课后习题中的例题******/
// （1）删除最小值，空出的位置由末尾元素填补
bool Del_Min(SqList &L, int &value){
    if(L.length == 0) return false;
    value = L.data[0];      // 假设第一个最小
    int pos = 0;
    for(int i=1; i<L.length; i++){
        if(L.data[i] < value){
            value = L.data[i];
            pos = i;
        }
    }
    L.data[pos] = L.data[L.length-1];
    L.length--;
    return true;
}

// （2）顺序表的逆置
void Reverse(SqList &L){
    int temp, i = 0, j = L.length-1;
    for(; i < j;){
        temp = L.data[i]=0;
        L.data[i++] = L.data[j];
        L.data[j--] = temp;
    }
}

// （3）删除所有等于x的元素
void Del_x(SqList &L, int x){
    int k=0, i=0;
    while(i < L.length){
        if (L.data[i] == x) k++;
        else L.data[i-k] = L.data[i];
        i++;
    }
    L.length = L.length - k;
}

// （5）删除顺序表中所有s-t之间的元素
bool Del_s_t(SqList &L, int s, int t){
    if(L.length == 0 || s >= t) return false;
    int k = 0, i = 0;
    for(; i < L.length; i++){
        if(L.data[i] >= s && L.data[i] <= t)  k++;
        else L.data[i-k] = L.data[i];
    }
    L.length = L.length - k;
    return true;
}
// （6）删除表中所有重复的元素
bool Delete_same(SqList &L){
    if(L.length == 0)   return false;
    int i, j;
    for(i=0, j=1; i<L.length; j++)      // i存储第一个不相同的元素，j为工作指针
        if(L.data[i] != L.data[j])      // 查找上一个与下一个不相同的元素
            L.data[++i] = L.data[j];    // 找到后将元素前移
    L.length = i + 1;
    return true;
}
// （7）有序表的合并
bool Merge(SqList A, SqList B, D_SqList &C){
    if(A.length + B.length > C.MaxSize) return false;
    int i=0, j=0, k=0;
    while(i < A.length && j < B.length){
        if(A.data[i] <= B.data[j])
            C.data[k++] = A.data[i++];
        else 
            C.data[k++] = B.data[j++];
    }
    while(i < A.length) C.data[k++] = A.data[i++];
    while(j < B.length) C.data[k++] = B.data[j++];
    C.length = k;
    return true;
}
// （9）有序表的二分搜索+交换+插入
void SearchChangeInsert(SqList &L, int x){
    int low=0, high=L.length-1, mid;
    while(low <= high){
        mid = (low + high)/2;
        if(L.data[mid] == x) break;
        else if(L.data[mid] < x) low = mid + 1;
        else high = mid - 1; 
    }

    if(L.data[mid] == x && mid != L.length-1){
        int temp = L.data[mid];
        L.data[mid] = L.data[mid+1];
        L.data[mid+1] = temp;
    }

    if(low > high){
        int i;
        for(i=L.length-1; i>high; i--)
            L.data[i+1] = L.data[i];        // 逐次后移元素
        L.data[i+1] = x;
        L.length++;
    }
}
