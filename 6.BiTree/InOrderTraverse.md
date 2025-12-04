## 程序填空题

### Problem 1
本题目要求实现非递归中序遍历算法。
```c++
Status InOrderTraverse(BiTree T,Status(*Visit)(BiTree e))
{ //采用二叉链表存储结构
   //中序历遍二叉树T的非递归算法，对每个数据元素调用函数Visit。
 SqStack S;
 BiTree p;
 InitStack(S);
 p=T;
 while(p || ____1____ )
 {  if(p)
       { ____2____ }   //根指针进栈, 历遍左子树
    else
        { ____3____    //根指针退栈，访问结点，历遍右子树
          (*Visit)(p);
         ____4____;
        }//else
 }
 return OK;
}
```
## 程序填空题
1. 1. `!StackEmpty(S)`
   2. `Push(S,p);p=p->lchild;`
   3. `Pop(S,p);`
   4. `p=p->rchild`
