// 静态查找表：仅查询与检索；
// 动态查找表：多插入与删除；

// 平均查找长度ASL


// 1.静态查找表：     线性查找
typedef struct {
    int *elem;  //按实际长度分配，0号单元留空
    int length;
} SStable;

//线性查找算法
int Search_Seq(SStable ST, int kval){
    int i;
    ST.elem[0] = kval;      //0号位置设置哨兵
    for (i = ST.length; ST.elem[i] != kval; --i);
    return i;               //找不到时i返回0
}

// 顺序表查找成功的ASL: (1+2+...+n)/n = (n+1)/2
// 顺序表查找失败的ASL:              n + 1                -----对任何一个不在顺序表中的数，都必须查找n+1次才能确定不在里面，因此期望就是n+1



// 2.有序查找表：   折半查找（二分法）
// low: 指示查找区间的下界
// high: 指示查找区间的上界
// mid = (high + low)/2,  mid所指的元素用于当前次的比较

//折半查找算法 ( 非递归 )
int Search_bin(SStable ST, int kval){
    int low = 1, high = ST.length, mid;     //注意从1开始
    while(low <= high){
        mid = (high + low) / 2;
        if(kval == ST.elem[mid])
            return mid;
        else if(kval < ST.elem[mid])
            high = mid - 1;
        else
            low = mid + 1;
    }
    return 0;       //不存在 则返回0
}

// ***************  折半查找递归算法：见---- 37 上机实验5-1  ******************

// ASL: 成功与失败
// 成功：画出折半查找判定树，每个结点的查找次数等于深度，相加之后除以总结点数
// 失败：折半查找树叶子结点的左子树和右子树代表查找失败的不同区间，n个结点共有n+1个失败区间(?)    存疑
//      注意：失败区间的查找次数与其双亲的查找次数相同，    相加之后除以失败区间总个数---(n+1)

// 查找成功与失败的平均查找长度与有n个结点的完全二叉树的高度相同：  ASL 约等于log2n向下取整+1


// ***************  区分顺序表和有序表！！！***************
// 顺序表：内部数据是无序的  表示顺序存储结构或者链式结构
// 有序表：内部数据有序，只能是顺序存储结构


// 3.索引顺序表     分块查找

// 注意这边是顺序表  里面数据无序！

// 索引：  在建立顺序表的同时 建立一个索引-------索引顺序表=索引+顺序表
// 查找过程：1.索引确定查找区间        2.在顺序表的某个区间内查找

typedef struct{
    int maxkey;     //最大关键字
    int stadr;      //起始地址（下标）  startaddress
} indexItem;        //索引项

typedef struct{
    indexItem *elem;
    int length;
} indexTable;       //索引表

// ASL:  索引表内ASL + 块内ASL = (b+1)/2 + (s+1)/2
// 其中：均匀分为b块，每块含s个记录
// 看成有先后顺序的两个线性查找
 