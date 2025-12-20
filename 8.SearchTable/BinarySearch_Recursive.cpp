//折半查找（递归实现）
#include <stdio.h>
#include <stdlib.h>
typedef int keyType;
typedef struct {
    keyType key;
} ElemType;
typedef struct {
    ElemType* elem;
    int length;
} SSTable;
int BinSearch(SSTable ST,int low, int high, keyType key)
{
    if (low > high) return 0;
    else {
        int mid = (low + high) / 2;
        if (ST.elem[mid].key == key)
            return mid; 
        else if (ST.elem[mid].key > key)
            return BinSearch(ST, low, mid - 1, key);
        else
            return BinSearch(ST, mid + 1, high, key);
    }
} 