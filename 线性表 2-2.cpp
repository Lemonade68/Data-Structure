//两线性表元素按值非递减有序排列

#include<stdio.h>

int main()
{
    int a[5] = {3, 5, 8, 10, 11};
    int b[8] = {2, 3, 6, 8, 9, 11, 15, 20};
    int c[13] = {0};
    int i = 0, j = 0, k = 0;
    while(i<=4 && j<=7)
    {
        if(a[i]>=b[j])
            c[k++] = b[j++];
        else
            c[k++] = a[i++];
    }
    while(i<=4)
        c[k++] = a[i++];
    while(j<=7)
        c[k++] = b[j++];

    //exit(OVERFLOW);                 //c语言exit函数怎么用？
    for (int p = 0; p < 13;p++)
        printf("%d ",c[p]);
    return 0;
}