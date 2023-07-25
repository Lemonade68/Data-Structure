#define MAXSIZE 20  

typedef struct {
    int key;
    int otherinfo;
} RedType;

typedef struct SqList{
    RedType r[MAXSIZE + 1];     // r[0]闲置或用作哨兵单元      一定要注意这个！！
    int length;                 // 顺序表长度
} SqList;



// 1.简单选择排序：
// 每次从无序序列中选出关键字最小的记录与无序序列第一位进行交换（如果不相等）

void swap(RedType &a, RedType &b){

}

void SelectSort(SqList &L){
    int i, j, k;
    for (i = 1; i < L.length; ++i){
        k = i;
        for (j = i + 1; j < L.length; ++j)
            if (L.r[j].key < L.r[k].key)                // 注意是根据关键字进行比较
                k = j;
        if (k != i)
            swap(L.r[i], L.r[k]);
    }
}

// 时间复杂度：O(n^2)



// 2.树形选择排序：
// 先对n个数据两两比较，每组取较小值后生成[n/2]组数据后再比较，重复 直到选出最小为止；
// 每次选出最小值后，将其一开始的位置置为正无穷，即退出比较

// 时间复杂度：O(nlogn)




// 3.堆排序：

// 堆：满足以下性质的数列{r1,r2,...,rn}称为堆
// r_i <= r_2i   且    r_i <= r_2i+1    ----小顶堆
// r_i >= r_2i   且    r_i >= r_2i+1    ----大顶堆

// 堆的性质：
// 1.从左到右依次可写成一颗完全二叉树，且满足任何一个根节点的两个孩子要么均大于它要么均小于它
// 2.堆构成的完全二叉树的每个结点的子树都是满足堆的条件

// 注意：实际上并没有构树！！！

// 一次"筛选"：输出堆顶元素并生成一个新堆。
// 将堆的最后一个元素与堆顶的元素进行交换，然后对交换后的堆顶元素往下进行依次交换：如果它大于他的某个子树结点，那么将它与该结点进行交换（如果大于两个，则挑其中较小的那个交换）。重复多次直到其回到正确位置为止，原堆顶元素出堆。


typedef SqList HeapType;            // 堆采用顺序表存储

void swap(RedType &a, RedType &b){

}

// 建大顶堆的一步操作                   整体思想：定义辅助变量先等于这个值，然后寻找位置的过程中不断覆盖，最后找到位置再写上去
// 已知H.r[s ... m]中记录的关键字除H.r[s].key之外均满足堆的定义，本函数调整
// H.r[s]的关键字，使H.r[s ... m]成为一个大顶堆(对其中的关键字而言)
void HeapAdjust(HeapType &H, int s, int m){
    RedType rc = H.r[s];
    for (int j = 2 * s; j <= m; j *= 2){            // 沿key较大的记录的下标向下筛选
        if (j < m && H.r[j].key < H.r[j + 1].key)   // 注意这边的j<m，因为后面有L.r[j+1]，
            ++j;                                    // j指向当前位置的两个孩子中关键字较大记录的位置     
        if(rc.key >= H.r[j].key)                    // 大于较大的，就说明该位置已经符合堆的定义了
            break;
        H.r[s] = H.r[j];                            // 直接覆盖
        s = j;                                      // s指向该孩子的位置，后重复操作
    }
    H.r[s] = rc;                                    // 调整前的堆顶记录插到s位置
}

// 形象化理解：j指向的结点只要符合条件值就上移给父结点，直到j指向开头的s应该在的位置，赋值给该位置


// 小顶堆：中间的过程变成j找较小的孩子， 然后如果s位置的关键字>j位置的关键字，两者就交换

void HeapSort(HeapType &H){
    int i;
    for (i = H.length / 2; i > 0; --i)               // 最后一个结点下标为H.length，则第一个需要被筛选的有孩子的结点下标为H.length/2
        HeapAdjust(H, i, H.length);                  // 建成大顶堆
    
    for (i = H.length; i > 1; --i){                  // i>1是因为
        swap(H.r[i], H.r[1]);                        // 大的放到最后，相当于是排序完了放出来
        HeapAdjust(H, 1, i - 1);                     // 剩下的重新调整为大顶堆
    }
}


// 大顶堆最后生成的是从小到大的序列

// 时间复杂度为O(nlogn)，只需要一个记录大小的辅助空间


// ********   堆排序的好处：可以只进行少量的次数得到最大或是最小的某几个元素   *******




#include<iostream>
#include<algorithm>
using namespace std;
int n,m,k;
int a[15];
void down(int x){//堆排序模板
    int t=x;
    if(2*x<=k&&a[t]>=a[2*x])t=2*x;
    if(2*x+1<=k&&a[t]>=a[2*x+1])t=2*x+1;
    if(x!=t){
        swap(a[t],a[x]);
        down(t);
    }
}
int main(){
    cin>>n>>m;
     k=(n>=m?m:n);//判断n，m大小
    for(int i=1;i<=k;++i)cin>>a[i];
    for(int i=k/2;i;i--)down(i);
    n-=k;
    while(n--){
        int x;
        scanf("%d",&x);
        if(x<=a[1])continue;
        else {
            a[1]=x;
            down(1);
        }
    }
    sort(a+1,a+k+1);
    cout<<a[k];
    for(int i=k-1;i;--i)cout<<" "<<a[i];
    cout<<endl;
    return 0;
}



