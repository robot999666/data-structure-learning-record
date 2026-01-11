// 设哈希表长为18,哈希函数为: H(k)=k MOD 17 建立对应的哈希表。采用开放地址法中的二次探测再散列解决冲突,完成以下工作：
// （1）查找值为x的元素地址（位置）。找不到则输出-1。
// （2）删除关键字为t1、t2的元素，再添加关键字为y的元素
// （3）输出整个哈希表（用%4d格式，没有数据则输出4个*）  

// 输入格式:
// 输入分2部分，
// 第一部分是初始元素个数和序列
// 第二部分是x、t1、t2、y的值，分3行输入。

// 输出格式:
// 输出数据共2行
// 第一行是x的地址
// 第二行是最后的哈希表

// 输入样例:
// 12
// 16 74 60 43 54 90 46 31 29 88 77 26
// 77
// 77 90
// 98
// 输出样例:
// 8
//   26********  54  88****  74********  60  43****  46  29  31****  16  98

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int Status;
#define SUCCESS 1
#define UNSUCCESS 0
#define DUPLICATE -1
#define OK 1
#define ERROR -1

typedef int KeyType;
typedef struct{
    KeyType key;
}ElemType;

typedef struct{
    ElemType *elem;
    int count;
    int size;
}HashTable;

#define Hash(K) ((K)%(17))

int collision(int p,int &c){
    int i=(c+1)/2;
    int sign=(c+1)%2;
    if(!sign) p+=(i*i);
    else p-=(i*i);
    p = (p % 18 + 18) % 18;
    return p;
}

Status SearchHash(HashTable H,KeyType K,int &p,int &c){
    c=0;
    p=Hash(K);
    int p0=p;
    while(H.elem[p].key!=-1 && K!=H.elem[p].key)
        p=collision(p0,++c);
    if(K==H.elem[p].key)
        return SUCCESS;
    else return UNSUCCESS;
}

Status DeleteHash(HashTable &H,KeyType e){
    int c=0;int p;
    if(SearchHash(H,e,p,c)){
         H.elem[p].key=-1;
         --H.count;
        return OK;
    }
    else
         return ERROR;
}

Status InsertHash(HashTable &H,KeyType e){
    int c=0;int p;
    if(SearchHash(H,e,p,c))
        return DUPLICATE;
    else{
         H.elem[p].key=e;
         ++H.count;
         return OK;
    }
}

void PrintHash(HashTable H){
    for(int i=0;i<18;i++){
        if(H.elem[i].key==-1) printf("****");
        else printf("%4d",H.elem[i].key);
    }
}

int main(){
    HashTable H;
    H.size=18;
    int n,x,p,c=0,t1,t2,y;
    scanf("%d",&n);
    H.elem=(ElemType*)malloc(H.size*sizeof(ElemType));
    for(int i=0;i<H.size;i++)
        H.elem[i].key=-1;
    for(int i=0;i<n;i++){
        int temp;
        scanf("%d",&temp);
        InsertHash(H,temp);
    }
    scanf("%d",&x);
    scanf("%d %d",&t1,&t2);
    scanf("%d",&y);
    if (SearchHash(H, x, p, c))
        printf("%d\n", p);
    else
        printf("-1\n");
    DeleteHash(H,t1);
    DeleteHash(H,t2);
    InsertHash(H,y);
    PrintHash(H);
    return 0;
}