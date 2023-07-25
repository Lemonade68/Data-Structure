// 直接插入比较次数存疑*****************************




#define MAXSIZE 20  

typedef struct {
    int key;
    int otherinfo;
} RedType;

typedef struct SqList{
    RedType r[MAXSIZE + 1];     //r[0]闲置或用作哨兵单元
    int length;                 //顺序表长度
} SqList;


// 整体思路： 在R[1,2,...,i-1]中查找R[i]的插入位置j
// 将R[j+1...i-1]的所有记录后移一位，R[i]插入到R[j+1]的位置上

// 1. 直接插入

// 注意：从第二位比较算是第一趟！
void InsertSort(SqList &L){
    int j;
    for (int i = 2; i <= L.length; ++i){
        if(L.r[i].key < L.r[i - 1].key){        //对关键字进行比较
            L.r[0] = L.r[i];                    //复制为哨兵
            //从后往前比较
            L.r[i] = L.r[i - 1];                //可以让后面少比较一次
            for (j = i - 2; L.r[j].key > L.r[0].key; --j)       //思考：包含了一直比到r[0]的情况      这边的>不能取到=   ！！！！
                L.r[j + 1] = L.r[j];
            L.r[j + 1] = L.r[0];                //插入正确位置
        }
    }
}

// 时间复杂度为O(n^2)


// 注意比较次数！！！   比较中找到是第一个小于等于哨兵的位置，然后在该位置的下一位插入
// 如果第1位到第i-1位的都大于哨兵，那么还要和哨兵进行比较！！！！




// 2. 折半插入
// 因为R[1]...R[i-1]是按关键字有序的序列，可以用折半查找找到位置后插入
void BInsertSort(SqList &L){
    for (int i = 2; i <= L.length; ++i){
        L.r[0] = L.r[i];                        //暂存为哨兵
        int low = 1, high = i - 1, mid;
        while(low <= high){                     //循环直到low > high， 即low = high + 1为止
            mid = (high + low) / 2;
            if(L.r[0].key < L.r[mid].key)
                high = mid - 1;
            else
                low = mid + 1;
        }
        //  *************    最后 high + 1 = low 的位置就是应该插入的位置   ***********
        for (int j = i - 1; j >= high + 1; ++j)             //或者是 low 
            L.r[j + 1] = L.r[j];
        L.r[high + 1] = L.r[0];             //或者是 low 
    }
}


// 3. 表插入

// ?  之后补充



// 4. 希尔排序
// 先宏观排序，再微观排序：  增量d   每次排序过程中从大到小递减，最后变为1；  增量为d时，分成d组

void ShellInsert(SqList &L, int dk){
    // 对L的一趟希尔排序，与顺序插入相比，做出了如下修改：
    // 1. 前后记录位置的增量是dk, 而不是1
    // 2. r[0]只是暂存单元，不是哨兵。   当 j <= 0 时，插入位置已找到
    int i, j;
    for (i = dk + 1; i <= L.length; ++i){               //不同组之间同时进行！！！
        if(L.r[i].key < L.r[i-dk].key){
            L.r[0] = L.r[i];                            //暂存
            for (j = i - dk; j > 0 && L.r[0].key < L.r[j].key; j -= dk)     //注意这边的 j>0    后半个语句成立的前提
                L.r[j + dk] = L.r[j];
            L.r[j + dk] = L.r[0];
        }
    }
}

void ShellSort(SqList &L, int dlta[], int t){       // dlta数组的最后一位一定是1
    // 按照增量dlta[0, ... ,t - 1]对顺序表进行希尔排序
    for (int k = 0; k < t; ++k)
        ShellInsert(L, dlta[k]);                    // 一趟增量为dlta[k]的插入排序
}

// 比较与移动次数可达n的1.3次方
// 希尔排序的空间复杂度为O(1)， 是不稳定的排序方法

