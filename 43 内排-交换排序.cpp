#define MAXSIZE 20  

typedef struct {
    int key;
    int otherinfo;
} RedType;

typedef struct SqList{
    RedType r[MAXSIZE + 1];     //r[0]闲置或用作哨兵单元      一定要注意这个！！
    int length;                 //顺序表长度
} SqList;



// 1. 冒泡排序
int length;
int L[10];

// 之前学的冒泡：
void BubbleSort(){
    for (int i = 0; i < length - 1; ++i){                   // 循环次数：长度-1  次
        for (int j = 0; j < length - i - 1; ++j){           // 最后进行到 倒数第i+2位
            if(L[j + 1] < L[j]){
                int temp = L[j];
                L[j] = L[j + 1];
                L[j + 1] = temp;
            }
        }
    }
}


// 另一版的冒泡：
void swap(int &a, int &b){
    // 交换
}

void BubbleSort_adv(int *r, int n){             //改进版，每次让i直接等于最后一个被排序的位置， 可以少进行一些次数的排序
    int i = n, lastExchange_index = 1;
    while (i > 1){
        lastExchange_index = 1;
        for (int j = 1; j < i; j++){
            if (r[j + 1] < r[j]){
                swap(r[j], r[j + 1]);
                lastExchange_index = j;         //记录下进行交换的记录位置
            }
            i = lastExchange_index;
        }
    }
}


// 时间复杂度也是O(n^2)

// 2. 快速排序

// 一次快排：即一次划分
// 划分算法：
int Partition(SqList  &L, int low, int high){
    L.r[0] = L.r[low];                      // 子表的第一个记录作枢轴记录
    int pivotkey = L.r[low].key;            // 枢轴记录关键字
    while(low < high){
        while(low < high && L.r[high].key >= pivotkey)
            --high;
        L.r[low] = L.r[high];
        
        while(low < high && L.r[low].key <= pivotkey)
            ++low;
        L.r[high] = L.r[low];
    }
    L.r[low] = L.r[0];                      // high = low时
    return low;                             // 返回枢轴位置
}


// 快排算法：每次划分后得到一个枢轴元素的正确位置，然后分成左右两部分接着划分
void QSort(SqList &L, int low, int high){
    //对顺序表子序列 L.r[low ... high]作快速排序
    if(low < high){
        int Pivotloc = Partition(L, low, high);     //将 L.r[low ... high]一分为二
        QSort(L, low, Pivotloc - 1);
        QSort(L, Pivotloc + 1, high);
    }
}

void QuickSort(SqList &L){
    QSort(L, 1, L.length);
}

// 结论：快排的时间复杂度为O(nlogn)

// 缺陷：
// 1.若一开始序列即为有序，那么快排的时间复杂度退化为O(n^2)
// 2.不稳定的排序方法