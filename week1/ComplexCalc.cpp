// 请设计并实现复数加法、减法、乘法运算的函数。
// 裁判测试程序样例：
// #include <stdio.h>
// struct fushu{
//     float shibu;
//     float xubu;
// };
// /* 你的程序将放在这里 */
// int main()
// {
//     struct fushu a,b,c,d;
//     scanf("%f%fi",&a.shibu,&a.xubu);      //输入第一个复数
//     scanf("%f%fi",&b.shibu,&b.xubu);     //输入第二个复数
//     add(a,b);                                             //计算a=a+b
//     mul(a,b);                                             //计算a=a*b
//     scanf("%f%fi",&c.shibu,&c.xubu);      //输入第三个复数
//     sub(a,c);                                              //计算a=a-c
//     if(a.xubu>0)
//       printf("%.2f+%.2fi\n",a.shibu,a.xubu);
//     else if(a.xubu<0) printf("%.2f%.2fi\n",a.shibu,a.xubu);
//     else printf("%.2f\n",a.shibu);
//     return 0;
// }
// 输入样例：
// 1+2i
// 3+4i
// 5+6i
// 输出样例：
// -17.00+28.00i
#include <stdio.h>
struct fushu{
    float shibu;
    float xubu;
};
/* 你的程序将放在这里 */
int main()
{
    struct fushu a,b,c,d;
    scanf("%f%fi",&a.shibu,&a.xubu);      //输入第一个复数
    scanf("%f%fi",&b.shibu,&b.xubu);     //输入第二个复数
    add(a,b);                                             //计算a=a+b
    mul(a,b);                                             //计算a=a*b
    scanf("%f%fi",&c.shibu,&c.xubu);      //输入第三个复数
    sub(a,c);                                              //计算a=a-c
    if(a.xubu>0)
      printf("%.2f+%.2fi\n",a.shibu,a.xubu);
    else if(a.xubu<0) printf("%.2f%.2fi\n",a.shibu,a.xubu);
    else printf("%.2f\n",a.shibu);
    return 0;
}
void add(struct fushu &a,struct fushu &b){
    struct fushu ret;
    ret.shibu=a.shibu+b.shibu;
    ret.xubu=a.xubu+b.xubu;
    a=ret;
}
void mul(struct fushu &a,struct fushu &b){
    struct fushu ret;
    ret.shibu=a.shibu*b.shibu-a.xubu*b.xubu;
    ret.xubu=a.shibu*b.xubu+a.xubu*b.shibu;
    a=ret;
}
void sub(struct fushu &a,struct fushu &b){
    struct fushu ret;
    ret.shibu=a.shibu-b.shibu;
    ret.xubu=a.xubu-b.xubu;
    a=ret;
}