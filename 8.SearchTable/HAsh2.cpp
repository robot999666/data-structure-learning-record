// 设哈希表长为10,哈希函数为: H(k)=k MOD 10 建立对应的哈希表。采用链地址法解决冲突。先建立哈希表，再删除x，插入y后，输出哈希表。

// 输入格式:
// 输入数据为初始元素个数和序列，以及x、y的值

// 输出格式:
// 输出数据为最后的哈希表

// 输入样例:
// 12
// 16 74 60 43 54 90 46 31 29 88 77 26
// 77 38
// 输出样例:
// 0->90->60^
// 1->31^
// 2^
// 3->43^
// 4->54->74^
// 5^
// 6->26->46->16^
// 7^
// 8->38->88^
// 9->29^

#include <stdio.h>
#include <stdlib.h>

typedef int Status;
#define OK 1
#define ERROR -1
#define DUPLICATE -1

typedef int KeyType;

typedef struct Node {
    KeyType key;
    struct Node *next;
} Node;

typedef struct {
    Node **head; 
    int size;   
    int count; 
} HashTable;

#define Hash(K) ((K) % 10)

Status InitHashTable(HashTable &H, int m) {
    H.size = m;
    H.count = 0;
    H.head = (Node **)malloc(H.size * sizeof(Node *));
    if (!H.head) return ERROR;
    for (int i = 0; i < H.size; i++) H.head[i] = NULL;
    return OK;
}

Status SearchHash(HashTable H, KeyType k, Node *&pre, Node *&cur, int &p) {
    p = Hash(k);
    pre = NULL;
    cur = H.head[p];
    while (cur) {
        if (cur->key == k) return OK;
        pre = cur;
        cur = cur->next;
    }
    return ERROR;
}

Status InsertHash(HashTable &H, KeyType k) {
    Node *pre, *cur;
    int p;
    if (SearchHash(H, k, pre, cur, p) == OK) return DUPLICATE;

    Node *s = (Node *)malloc(sizeof(Node));
    s->key = k;
    s->next = H.head[p];
    H.head[p] = s;
    ++H.count;
    return OK;
}

Status DeleteHash(HashTable &H, KeyType k) {
    Node *pre, *cur;
    int p;
    if (SearchHash(H, k, pre, cur, p) != OK) return ERROR;
    if (pre == NULL) H.head[p] = cur->next;
    else pre->next = cur->next;
    free(cur);
    --H.count;
    return OK;
}

void PrintHash(HashTable H) {
    for (int i = 0; i < H.size; i++) {
        printf("%d", i);
        Node *p = H.head[i];
        while (p) {
            printf("->%d", p->key);
            p = p->next;
        }
        printf("^\n");
    }
}

int main() {
    HashTable H;
    InitHashTable(H, 10);
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        InsertHash(H, x);
    }
    int x, y;
    scanf("%d %d", &x, &y);
    DeleteHash(H, x);
    InsertHash(H, y);
    PrintHash(H);
    return 0;
}