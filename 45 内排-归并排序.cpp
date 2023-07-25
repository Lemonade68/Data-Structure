#define MAXSIZE 20  
#define pass 1

typedef struct {
    int key;
    int otherinfo;
} RedType;

typedef struct SqList{
    RedType r[MAXSIZE + 1];     // r[0]闲置或用作哨兵单元      一定要注意这个！！
    int length;                 // 顺序表长度
} SqList;

// 思想：将两个位置相邻的记录有序子序列归并为一个记录的有序序列


// 非递归形式：
void Merge(RedType SR[], RedType *TR, int i, int m,int n){
    //将有序的SR[i ... m]和SR[m+1 ... n]归并为有序的TR[i ... n]
    int j, k;
    for (j = m + 1, k = i; i <= m && j <= n; ++k){          //SR中记录由小到大并入TR
        if(SR[i].key <= SR[j].key)
            TR[k] = SR[i++];
        else
            TR[k] = SR[j++];
    }
    if (i <= m)
        pass;
        // TR[k... n] = SR[i... m];   剩下的全部给TR
    if (j <= n)
        pass;
        // TR[k... n] = SR[j... n];   同上
}

// 一趟完整的归并排序：调用log2n趟这种操作，直到最后只剩下一个有序序列为止

// 两路归并是稳定的  但是要牺牲空间



// 递归形式：用处不大    具体见书上