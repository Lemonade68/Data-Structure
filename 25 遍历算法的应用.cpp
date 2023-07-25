#define status int
#define OK 1
#define FALSE 0
#define OVERFLOW -2
#include<stdlib.h>
#include<stdio.h>

typedef struct BiTree{
    int data;
    struct BiTree *lchild;
    struct BiTree *rchild;
} BiTNode, *BiTree;

// 二叉树里最为重要的就是遇到空返回

// 1.查询二叉树某结点并用p返回       --采用先序遍历方便
status PreOrder(BiTree T, int x, BiTree &p){
    if(T){                          //为空即为返回条件
        if(T->data==x){             //结点本身就是，即找到该结点
            p = T;
            return OK;              //理解：这里的ok是逐层往上传递的
        }
        else{
            if(PreOrder(T->lchild,x,p))
                return OK;
            else
                return (PreOrder(T->rchild, x, p));
        }
    }
    else
        return FALSE;               //若叶子结点的还不是 其双亲就为空，说明这一路上没找到 返回false
}
//  （重要！！！）思考：为什么不直接返回结点？   --因为返回后回到的不是主函数，而是上一个递归函数


// 2.统计二叉树中叶子结点个数(所有结点个数)
// 法1：使用计数器
void CountLeaf(BiTree T, int &count){
    if(T){
        if((!T->lchild)&&(!T->rchild))
            count++;
        CountLeaf(T->lchild, count);
        CountLeaf(T->rchild, count);
    }
}

// 法2：注意掌握与理解！！
int countleaf(BiTree T){
    if(!T)                      //空结点情况
        return 0;

    if(!T->lchild && !T->rchild)
        return 1;
    else{
        int m = countleaf(T->lchild);
        int n = countleaf(T->rchild);
        return (n + m);
    }
}

// 法2拓展：统计二叉树中所有结点个数
int Count(BiTree T){
    if(!T)
        return 0;
    else{
        int m = Count(T->lchild);
        int n = Count(T->rchild);
        return (m + n + 1);
    }
}


// 3.求二叉树的深度   --每个结点返回左右子树深度最大值+1
int Depth(BiTree T){
    int depth;
    if(!T)
        depth = 0;
    else{
        int depth_left = Depth(T->lchild);
        int depth_right = Depth(T->rchild);
        depth = 1 + (depth_left > depth_right ? depth_left : depth_right);
    }
    return depth;
}


// 另一种写法：
void depth(BiTree T, int level, int &dval){
    if(T){
        if(level>dval)
            dval = level;
        depth(T->lchild, level + 1, dval);
        depth(T->rchild, level + 1, dval);
    }
}
// 调用前level初值为1，dval初值为0


// 4.复制二叉树
BiTNode* GetTreeNode(int item, BiTNode *lptr, BiTNode *rptr){
    //数据域：item    左指针域：lptr    右指针域：rptr
    BiTree T;
    if(!(T = (BiTree)malloc(sizeof(BiTNode))))      //不能这里面新创建一个BiTree T = ....   会报错
        exit(OVERFLOW);
    T->data = item;
    T->lchild = lptr;
    T->rchild = rptr;
    return T;
}

BiTNode *CopyTree(BiTNode *T){
    if(!T)
        return NULL;
    BiTree newlptr, newrptr, newTree;
    // 左子树递归复制
    if(T->lchild)
        newlptr = CopyTree(T->lchild);
    else
        newlptr = NULL;
    // 右子树递归复制
    if(T->rchild)
        newrptr = CopyTree(T->rchild);
    else
        newrptr = NULL;
    newTree = GetTreeNode(T->data, newlptr, newrptr);
    return newTree;
}


// 5.建立二叉树
// 以字符串的形式：根 左子树 右子树，没有就是" "
void CreateBiTree(BiTree &T){
    char ch;                  //接收字符串中字符
    scanf(&ch);
    if(ch == ' ')
        T = NULL;
    else{
        if(!(T=(BiTree)malloc(sizeof(BiTNode))))
            exit(OVERFLOW);
        T->data = ch;                   //这边data要改成ch类型
        CreateBiTree(T->lchild);        //构造左子树
        CreateBiTree(T->rchild);        //构造右子树
    }
}


// 按给定的表达式建立对应二叉树

//后续补充完整



//由前序和中序序列构造二叉树

//在中序序列中查找根节点的函数
int Search(char *ino, char c){
    int i = 0;
    while(ino[i]){
        if(ino[i] == c)
            return i;
        else
            i++;
    }
    return -1;
}


void CrtBT(BiTree &T, char pre[], char ino[], int ps, int is, int n){
    // pre[ps...ps+n-1]为二叉树的先序序列，用于找根结点
    // ino[is...is+n-1]为二叉树的中序序列，用于构建根节点对应的左右子树
    // ps代表构建该结点时传入的先序字符串的第一位
    // is代表构建该结点时传入的中序字符串的第一位
    // n表示该结点传入的两个字符串的长度(相等)
    if(n == 0)
        T = NULL;
    else{
        int k = Search(ino, pre[ps]);   //中序序列中查找根节点在中序序列中的位置
        if(k == -1)
            T = NULL;                   //两个序列不对应，建立空树
        else{
            if(!(T=(BiTree)malloc(sizeof(BiTNode))))
                exit(OVERFLOW);
            T->data = pre[ps];          
            //构建左子树
            if(k == is)     //根在中序的最左边
                T->lchild = NULL;
            else
                CrtBT(T->lchild, pre, ino, ps + 1, is, k - is); // ps+1: 先序即先根序，先读到的就是根
            //构建右子树
            if(k == is + n - 1)     //根在中序的最右边
                T->rchild = NULL;
            else{
                CrtBT(T->rchild, pre, ino, ps + 1 + (k - is), k + 1, n - (k - is) - 1);

            // --------------------------技巧：记住左子树的长度为k-is，剩下的都用这个推导--------------------------
            // 因为：k和is都是相对于中序序列而言的，相减才有意义
            }
        }
            
    }
}




// 6.输出二叉树上从根到所有叶子结点的路径       非常巧妙
void AllPath(BiTree T, Stack &S){
    if(T){
        Push(S, T->data);
        if(!T->lchild && !T->rchild)
            PrintStack(S);
        else{
            AllPath(T->lchild, S);
            AllPath(T->rchild, S);      //这两条语句出现后表示经过该结点的所有路径已经被打印
        }                               //因此直接pop掉走另一条路
        Pop(S);                         //每个结点使用完后要及时出栈
    }
}



