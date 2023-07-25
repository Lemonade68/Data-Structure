// 在采用二叉链表存储结构的基础上，实现二叉排序树的以下运算：
// （1）实现在二叉排序树上查找指定关键字的运算；
// （2）实现在二叉排序树上插入一个关键字的运算；
// （3）实现在二叉排序树上删除指定关键字的运算；
// （4）实现二叉排序树的中序遍历运算，输出中序遍历序列；
// （5）从空的二叉排序树开始，根据一个关键字序列，调用实现插入运算的函数，建立二叉排序树


// 存疑：search中pre不传引用的话   按书上的写法delete的前两种情况会出问题

// 解答：注意对于一个结点而言，得到他的方式是从T->lchild/rchild得到   还是   单独搜到这个结点之后用另一个指针p返回他
// 前者暗含了父子节点间的联系关系，后者没有

#include<stdio.h>
#include<stdlib.h>
#define OVERFLOW -2

typedef struct BiTNode{
    int data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;


// 中序遍历算法
void InOrder(BiTree T){
    if(T){
        InOrder(T->lchild);
        printf("%d ", T->data);
        InOrder(T->rchild);
    }
}


//查找算法
int Search(BiTree T, int key, BiTree &p, BiTree &pre){           // 若找到，p返回该结点；若未找到，p返回该路径上最后一个遍历到的结点   pre初始置空
    if(!T){
        p = pre;                                                // 返回路径上最后一个结点
        return 0;                                               // 0 代表未找到， 1 代表已找到 
    }
    else{
        if(key == T->data){
            p = T;
            return 1;
        }
        else if(key < T->data){
            pre = T;                                            //修改pre值
            return Search(T->lchild, key, p, pre);
        }
        else{
            pre = T;
            return Search(T->rchild, key, p, pre);
        }
    }
}





//插入算法
void Insert(BiTree &T, int key){                                //对树进行了修改，需要引用
    BiTree p, pre = NULL;
    int i = Search(T, key, p, pre);
    if(i == 0){                                                 //找不到才需要插入
        BiTree q = (BiTree)malloc(sizeof(BiTNode));
        if(!q)
            exit(OVERFLOW);
        q->data = key;
        q->lchild = NULL;
        q->rchild = NULL;
        if(!p)                                                  //如果一开始是空树
            T = q;                                              //树根设置为q，并且由于树根要改变，函数中T要设置成引用
        else if(key < p->data)
            p->lchild = q;
        else
            p->rchild = q;
    }
}


// 书上的方法，成功

// void Delete(BiTree &p){
//     if(!p->rchild){             //右子树空，则只需重接它的左子树    包含了删除叶子结点的情况
//         BiTree q = p;
//         p = p->lchild;          //**  引用   让这里可以不通过双亲直接连到左子树
//         free(q);
//     }
//     else if(!p->lchild){
//         BiTree q = p;
//         p = p->rchild;
//         free(q);
//     }
//     else{                       //左右都有孩子结点的情况
//         BiTree q = p, s = p->lchild;
//         while(s->rchild){       //寻找前驱(左孩子的最右子节点)----也保证了s最终没有右孩子，并且s为q的右孩子    
//             q = s;              //q始终指向s的双亲结点
//             s = s->rchild;
//         }
//         p->data = s->data;      //前驱的数据复制到p结点
//         if(q != p)              //注意区分两种情况----q!=p时，s左接到q的右
//             q->rchild = s->lchild;      //重接q结点的右子树
//         else                    //注意区分两种情况----q==p时，s左接到q的左（q此时就是p）
//             q->lchild = s->lchild;
//         free(s);                //最后把前驱结点删除
//     }
// }   

// void DeleteBST(BiTree &T, int key){
//     //若存在key关键字的元素，删除
//     if(!T)
//         return;
//     else{
//         if(T->data == key)
//             Delete(T);                                                           // 注意： 这边暗含了T就是上个T->lchild，所以搞到delete函数里p就相当于T->lchild    !!!!!!!!!!!!
//         else if(T->data > key)
//             DeleteBST(T->lchild, key);
//         else
//             DeleteBST(T->rchild, key);
//     }
// }


//   下面是自己写的版本，使用了search来获得p的位置， 但是这样的话delete p的前两种情况用书上的代码会出现问题                                      ---------- why?????????（见下面）

// 删除算法：
void DeleteBST(BiTree &T, int e){                                   //删除e，对树进行了操作，要引用
    BiTree p, pre = NULL;
    int i = Search(T, e, p, pre);
    if(i == 0){
        printf("未找到该结点\n");
        return;
    }
    else{
        // Delete(p);
        if(!p->lchild){                                             //同时处理了p为叶子结点与p只有右子树的情况
            if(pre->lchild == p)
                pre->lchild = p->rchild;
            else
                pre->rchild = p->rchild;
            free(p);

            //如果用search获得p的位置的话，下面的代码会报错          ***********原因：search只是找到了该结点并让p指向它， 但是并没有包含上个结点和p之间的关系，改变后上个结点的子树就会变成野指针
            // BiTree q = p;
            // p = p->rchild;                                      //父结点的孩子是p，本来指向一片地址，现在重接右子树,并将原来的地址内存清空
            // free(q);
        }
        else if(!p->rchild){
            if(pre->lchild == p)
                pre->lchild = p->lchild;
            else
                pre->rchild = p->lchild;
            free(p);

            // BiTree q = p;
            // p = p->lchild;                                      //父结点的孩子是p，本来指向一片地址，现在重接左子树,并将原来的地址内存清空
            // free(q);
        }
        else{                                                       //有两个子树的情况：找到前驱，把前驱的值赋给该结点，并删除前驱(左孩子的最右子树)
            BiTree s = p->lchild;
            pre = p;
            while(s->rchild){
                pre = s;
                s = s->rchild;
            }
            p->data = s->data;
            if(pre == p){                                       //这边也可以写成 pre == p
                pre->lchild = s->lchild;
                free(s);
            }
            else{
                pre->rchild = s->lchild;                        //s可能有左子树，接上
                free(s);
            }
        }
        printf("删除成功！\n");
    }
}

    

int main(){
    int n;
    BiTree T = NULL, p = NULL, pre = NULL;
    printf("请输入序列元素的个数：");
    scanf("%d", &n);
    printf("请输入序列元素：");
    for (int i = 0; i < n;i++){
        int e;
        scanf("%d", &e);
        Insert(T, e);
    }
    
    InOrder(T);         //第一遍打印，说明构造正确
    printf("\n");
    
    printf("请输入要查找的元素：");
    scanf("%d", &n);
    int i = Search(T, n, p, pre);
    if(i == 0)
        printf("未找到\n");
    else
        printf("已找到\n");
    
    printf("请输入要插入的元素：");
    scanf("%d", &n);
    Insert(T, n);
    InOrder(T);         //第二遍打印，说明插入位置正确
    printf("\n");

    printf("请输入要删除的元素：");
    scanf("%d", &n);
    // Delete(T, n);
    DeleteBST(T, n);
    InOrder(T);         //第三遍打印，说明删除操作正确


    return 0;
}




// 二叉排序树的建立也可以不使用插入函数，只需输入的序列不包含重复的关键字即可