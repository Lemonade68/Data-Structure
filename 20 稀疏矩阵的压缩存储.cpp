// 稀疏矩阵：m行n列的矩阵含有t个非零元素
// 稀疏因子：t/(mn)<=0.05 称为稀疏矩阵

// 对稀疏矩阵的另一种描述：
// 存储非零元素时记下他所在的行和列的位置------三元组(i,j,aij)
// 可表述为：((),(),(),(),...,())   其中小括号内存放非零元素

// 压缩存储方法：

// 一、三元组顺序表

#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 12500
#define OVERFLOW -2

typedef struct{
    int i, j;       //行下标与列下标
    int e;          //非零元的值
} Triple;           //三元组类型

typedef struct{
    Triple data[MAXSIZE + 1];       //行序，data[0]不使用
    int mu;         //矩阵行数
    int nu;         //矩阵列数
    int tu;         //非零元素个数--三元组总个数，即结构体内总遍历数
} TSMatrix;         //稀疏矩阵类型

int main(){
    TSMatrix m;
    m.data;         //  m.data用于存储m的三元组表
    return 0;
}

// 转置算法为例：   非常规方法（不是t[i][j]=m[j][i]）

// 算法1：多次扫描，每次扫描所有元素并查找列分别为1,2,3...的元素
void TransposeSMatrix(TSMatrix M, TSMatrix &T){
    T.mu = M.mu;
    T.nu = M.nu;
    T.tu = M.tu;
    if(T.tu){
        int index = 1;      //三元组在T.data中存储的位置
        for (int col = 1; col <= M.nu; col++){      //每1列都要查找
            for (int p; p <= M.tu; p++){            //p指向当前三元组
                if(M.data[p].j == col){
                    T.data[index].e = M.data[p].e;
                    T.data[index].i = M.data[p].j;      //注意转置前后ij互换
                    T.data[index].j = M.data[p].i;
                    index++;
                }
            }
        }
    }
}

// 改进：一次扫描完成转置
// 算法2：一次扫描--先求得M各列第一个非零元三元组在T.data的位置
// 设置 num[],num[col]表示第col列的非零元个数
void SetParameters(int *num, int *cpot, TSMatrix M){
    // 求num[]
    for (int p = 1; p <= M.tu; p++){
        num[M.data[p].j]++;             //对应的列的元素个数++
    
    // 求cpot[]，cpot[col]表示M中col列第一个非零元素在T中的位置
    cpot[1] = 1;        // 第1列第1个非零元素对应的肯定是T的第一个位置
    int col;
    for (col = 2; col <= M.nu; col++)
        cpot[col] = cpot[col - 1] + num[col - 1];   //思考合理性
    }
}


void FastTransposeSMatrix(TSMatrix M, TSMatrix &T){
    T.mu = M.mu;
    T.nu = M.nu;
    T.tu = M.tu;
    if(T.tu){
        int num[100] = {0};
        int cpot[100] = {0};
        SetParameters(num, cpot, M);
        for (int p; p <= M.tu; p++){            // p指向M中的当前三元组
            int col = M.data[p].j;              // 当前指向M的三元组的列
            int q = cpot[col];                  // q指向当前M中三元组应在T中的位置
            T.data[q].e = M.data[p].e;
            T.data[q].i = M.data[p].j;          // 注意转置
            T.data[q].j = M.data[p].i;
            cpot[col]++;                        // ++以让后面进来相同列数的三元组也在自己的位置
        }
    }
}
// 由于是按行遍历的，先遍历到的一定是转置后同一行中靠前的元素，因此无需考虑顺序问题



// 二、十字链表
// 存储形式：三元组的双链表，除去三元组外，还包含两指针，分别指向下一同行、下一同列元素
typedef struct olnode{
    int i, j;
    int e;
    struct olnode *right;       //指向右边的元素
    struct olnode *down;        //指向下面的元素
} OLNode, *OLink;               //三元组结点

typedef struct{
    OLink *rhead;       //行头结点，连续的一片区域，与二维数组a[m][n]中的a[m]同原理
    OLink *chead;       //列头结点，注意这边的*，与链表头结点区别！
    int mu, nu, tu;
} CrossList;            //十字链表类型


// 十字链表的创建算法
void CreatCrossList(CrossList &M){
    int m, n, t, i, j, e;
    OLink p, q;
    printf("输入矩阵的行数、列数、非零元总数\n");
    scanf("%d %d %d", &m, &n, &t);
    M.mu = m;
    M.nu = n;
    M.tu = t;
    //为行链和列链的头指针分配空间
    if(!(M.rhead = (OLink *)malloc(sizeof(OLink) * (m))))
        exit(OVERFLOW);
    if(!(M.chead = (OLink *)malloc(sizeof(OLink) * (n))))
        exit(OVERFLOW);
    //初始化行链列链头指针
    for (i = 0; i < m; i++)
        M.rhead[i] = NULL;
    for (i = 0; i < n; i++)
        M.chead[i] = NULL;
    scanf("%d %d %d", &i, &j, &e);      //按任意次序输入非零元
    while(i!=-1){                       //输入i为-1时结束
        if(!(p = (OLink)malloc(sizeof(OLNode))))
            exit(OVERFLOW);
        p->e = e;
        p->i = i;
        p->j = j;

        //按序插入行链：(比的是列)
        if(M.rhead[i]==NULL || M.rhead[i]->j>j){           //行链空，直接插入; 比第一个小，插在第一个前面
            // M.rhead[i] = p;                  //单独写第一个条件的语句，但是可与下面的合并！！！
            // p->right = NULL;
            p->right = M.rhead[i];
            M.rhead[i] = p;
        }
        else{               //寻找在行中的插入位置
            for (q = M.rhead[i]; q->right && q->right->j < j; q=q->right);      //注意中间的写法
            p->right = q->right;
            q->right = p;
        }

        //按序插入列链：(比的是行)
        if(M.chead[j]==NULL || M.chead[j]->i>i){    //同上，两种情况
            p->down = M.chead[j];
            M.chead[j] = p;
        } 
        else{           //查找列插入的位置
            for (q = M.chead[j]; q->down && q->down->i < i; q=q->down);         //同上，注意中间写法
            p->down = q->down;
            q->down = p;
        }

        scanf("%d %d %d", &i, &j, &e);      //再次读入，为下一次循环准备
    }        
}
