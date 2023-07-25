// 树的二叉链表存储表示
#define Elem int

typedef struct CSNode{
    Elem data;
    struct CSNode *firstchild, *nextsibling;    //第一个孩子结点和其右边的下一个兄弟结点
} CSNode, *CSTree;



// 树和森林的遍历
// 树的遍历：先根遍历，后根遍历，层序遍历     没有中序遍历！！
// 先根：先访问根节点，然后依次先根遍历各子树
// 后根：先依次后根遍历各子树，然后访问根节点

// 树的先根遍历等同于对转换所得的二叉树进行先序遍历
// 树的后根遍历等同于对转化所得的二叉树进行中序遍历


// 森林：   可分解为3部分：
// 1.森林中第一棵树的根结点
// 2.森林中第一棵树的子树森林
// 3.森林中其他树构成的森林


// 森林的先序遍历：从左到右对森林每一棵树进行先根遍历
// 森林的中序遍历：从左到右对森林的每棵树进行后根遍历

// 森林的先序遍历等同于对转化所得的的二叉树进行先序遍历
// 森林的中序遍历等同于对转化所得的的二叉树进行中序遍历



// 求树的深度：
int Depth(CSTree T){
    if(!T)
        return 0;
    else{
        int D1 = Depth(T->firstchild);
        int D2 = Depth(T->nextsibling);
        return (D1 + 1 > D2 ? (D1 + 1) : D2);       //返回的是从T的双亲结点看来，T和T的兄弟提供的深度
    }
}


// 输出森林中所有从根到叶子的路径的算法：
void AllPath(CSTree T, Stack &s){
    while(!T){                              //while的作用：T只给了firstchild  需要把兄弟结点一起打印完后
        Push(S, T->data);
        if(!T->firstchild)
            PrintStack(s);
        else
            AllPath(T->firstchild, s);      //这条语句出现表示经过很多递归之后，经过这个结点的所有路径已经被打印
        Pop(s);                             //直接pop掉该结点，并换成兄弟节点
        T = T->nextsibling;
    }
}



// 建树的存储结构算法：  以二元组(F,C)的形式自上而下，自左而右依次输入树的各边...

// 后续补充



