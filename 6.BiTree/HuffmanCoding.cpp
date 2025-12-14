#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int Status;
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef struct{
    unsigned int weight;
    unsigned int parent,lchild,rchild;
}HTNode,*HuffmanTree;
typedef char** HuffmanCode;

void Select(HuffmanTree HT, int n, int *s1, int *s2) {
    int first = 0;
    for (int i = 1; i <= n; i++) {
        if (HT[i].parent == 0) {
            first = i;
            break;
        }
    }
    *s1 = first;
    for (int i = 1; i <= n; i++) {
        if (HT[i].parent == 0 && HT[i].weight < HT[*s1].weight) {
            *s1 = i;
        }
    }
    int second = 0;
    for (int i = 1; i <= n; i++) {
        if (HT[i].parent == 0 && i != *s1) {
            second = i;
            break;
        }
    }
    *s2 = second;
    for (int i = 1; i <= n; i++) {
        if (HT[i].parent == 0 && i != *s1 && HT[i].weight < HT[*s2].weight) {
            *s2 = i;
        }
    }
}

void HuffmanCoding(HuffmanTree &HT,HuffmanCode &HC,int n){
    if(n<=1) return;
    int m=2*n-1;
    HT=(HuffmanTree)malloc((m+1)*sizeof(HTNode));
    int i;HuffmanTree p;
    for(p=HT+1,i=1;i<=n;++i,++p){
        scanf("%d",&(p->weight));
        p->parent=p->lchild=p->rchild=0;
    }
    for(;i<=m;++i,++p){
        p->weight=p->parent=p->lchild=p->rchild=0;
    }
    int s1,s2;
    for(i=n+1;i<=m;++i){
        Select(HT,i-1,&s1,&s2);
        HT[s1].parent=i;    HT[s2].parent=i;
        HT[i].lchild=s1;    HT[i].rchild=s2;
        HT[i].weight=HT[s1].weight+HT[s2].weight;
    }

    HC=(HuffmanCode)malloc((n+1)*sizeof(char*));
    char* cd=(char*)malloc(n*sizeof(char));
    cd[n-1]='\0';
    int start,c,f;
    for(i=1;i<=n;++i){
        start=n-1;
        c=i;f=HT[i].parent;
        while(f!=0){
            if(HT[f].lchild==c)
                cd[--start]='0';
            else
                cd[--start]='1';
            c=f;f=HT[f].parent;
        }
        HC[i]=(char*)malloc((n-start)*sizeof(char));
        strcpy(HC[i],&cd[start]);
    }
    free(cd);
}

int main()
{
    int n;
    scanf("%d",&n);
    char *str = (char*)malloc((n+1)*sizeof(char));
    HuffmanTree HT = NULL;
    HuffmanCode HC = NULL;
    HuffmanCoding(HT,HC,n);
    scanf("%s",str);
    for(int i=1;i<=n;++i){
        printf("%c:%s\n",str[i-1],HC[i]);
    }
    free(str);
    for(int i=1;i<=n;++i){
        free(HC[i]);
    }
    free(HC);
    free(HT);
    return 0;
}