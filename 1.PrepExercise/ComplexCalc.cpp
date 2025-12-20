// 复数计算程序
// 实现复数加法、减法、乘法运算
// 输入：三个复数，格式如1+2i
// 输出：计算结果
#include <stdio.h>
// 复数结构体定义
struct fushu
{
    float shibu; // 实部
    float xubu;  // 虚部
};
/* 你的程序将放在这里 */
int main()
{
    struct fushu a, b, c, d;  // 定义四个复数变量
    scanf("%f%fi", &a.shibu, &a.xubu); // 输入第一个复数，格式如1+2i
    scanf("%f%fi", &b.shibu, &b.xubu); // 输入第二个复数，格式如3-4i
    add(a, b);                         // 计算a = a + b（复数加法）
    mul(a, b);                         // 计算a = a * b（复数乘法）
    scanf("%f%fi", &c.shibu, &c.xubu); // 输入第三个复数
    sub(a, c);                         // 计算a = a - c（复数减法）

    // 根据虚部符号输出结果
    if (a.xubu > 0)
        printf("%.2f+%.2fi\n", a.shibu, a.xubu);  // 虚部为正：a+bi
    else if (a.xubu < 0)
        printf("%.2f%.2fi\n", a.shibu, a.xubu);   // 虚部为负：a-bi
    else
        printf("%.2f\n", a.shibu);                // 虚部为0：a

    return 0;
}
// 复数加法：a = a + b
// 复数加法规则：(a + bi) + (c + di) = (a+c) + (b+d)i
void add(struct fushu &a, struct fushu &b)
{
    struct fushu ret;  // 临时变量存储计算结果
    ret.shibu = a.shibu + b.shibu;  // 实部相加
    ret.xubu = a.xubu + b.xubu;     // 虚部相加
    a = ret;  // 将结果赋值给a
}

// 复数乘法：a = a * b
// 复数乘法规则：(a + bi) * (c + di) = (ac - bd) + (ad + bc)i
void mul(struct fushu &a, struct fushu &b)
{
    struct fushu ret;  // 临时变量存储计算结果
    ret.shibu = a.shibu * b.shibu - a.xubu * b.xubu;  // 实部：ac - bd
    ret.xubu = a.shibu * b.xubu + a.xubu * b.shibu;   // 虚部：ad + bc
    a = ret;  // 将结果赋值给a
}

// 复数减法：a = a - b
// 复数减法规则：(a + bi) - (c + di) = (a-c) + (b-d)i
void sub(struct fushu &a, struct fushu &b)
{
    struct fushu ret;  // 临时变量存储计算结果
    ret.shibu = a.shibu - b.shibu;  // 实部相减
    ret.xubu = a.xubu - b.xubu;     // 虚部相减
    a = ret;  // 将结果赋值给a
}