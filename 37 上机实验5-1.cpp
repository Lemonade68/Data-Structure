// 输入一个序列，先用顺序查找找到指定元素； 
// 然后对序列进行排序后用递归与非递归方法实现折半查找

#include<stdio.h>
#include<stdlib.h>

typedef struct{
    int *elem;
    int length;
} SSTable;

//非递归方式：
int Search_bin(SSTable T, int key){
    int high, low, mid;
    high = T.length - 1;
    low = 1;
    while(high >= low){
        mid = (high + low) / 2;
        if(T.elem[mid] == key)
            return mid;
        else if(T.elem[mid] > key)
            high = mid - 1;
        else
            low = mid + 1;
    }
    return 0;
}   

//递归方式：
int Search_bin_2(SSTable T, int key, int high, int low){
    int mid;
    if(low > high)
        return 0;
    else{
        mid = (high + low) / 2;
        if(T.elem[mid] == key)
            return mid;
        else if(T.elem[mid] > key)
            return Search_bin_2(T, key, mid - 1, low);
        else
            return Search_bin_2(T, key, high, mid + 1);
    }
}


int main(){
    int i, n, key;
    printf("输入个数：");
    scanf("%d", &n);
    SSTable T;
    T.elem = (int *)malloc(sizeof(int) * (n + 1));      //留一位给监视哨
    T.length = n + 1;
    for (i = 1; i <= T.length - 1; ++i)
        scanf("%d", &T.elem[i]);

    printf("输入要查找的元素：");
    scanf("%d", &key);
    T.elem[0] = key;                                    //设置监视哨
    // 直接查找：
    for (i = T.length - 1; T.elem[i] != key; --i);
    if(i == 0)
        printf("顺序查找：未找到\n");
    else
        printf("顺序查找：位置为：%d\n", i);

    // 排序：
    for (i = 1; i <= T.length - 2; i++){                 // 进行size - 1趟
        for (int j = 1; j <= T.length - 1 - i; j++){     // 第a趟执行从第一位执行到倒数第a+1位
            if(T.elem[j] > T.elem[j + 1]){
                int temp = T.elem[j];
                T.elem[j] = T.elem[j + 1];
                T.elem[j + 1] = temp;
            }
        }
    }

    //打印排序后序列：
    i = 1;
    printf("排序后序列如下：\n");
    while(i <= T.length - 1)
        printf("%d ", T.elem[i++]);
    printf("\n");

    //递归方式这版查找：
    i = Search_bin_2(T, key, T.length - 1, 1);
    if(i == 0)
        printf("递归折半查找：未找到\n");
    else
        printf("递归折半查找：位置为：%d\n", i);

    //非递归方式折半查找：
    i = Search_bin(T, key);
    if(i == 0)
        printf("非递归折半查找：未找到\n");
    else
        printf("非递归折半查找：位置为：%d\n", i);

    return 0;
}