// 树的带权路径长度：权值*路径长度
// 最小的：最优二叉树/哈夫曼树

// 构造最优二叉树：  哈夫曼算法：
// 将一组权值中的最小两个合成一个二叉树后放回，两者的和作为新的权值，重复操作

// -----------------------注意！！！  构造时默认小在左 大在右-----------------
// 编码：
// 等长码：无论顺序如何，总长度永远相等
// 不等长码：出现次数多的字符编码短，出现少的字符编码长
            //问题：容易产生二义
// 改进：前缀编码----任何一个字符的编码都不是另一个字符编码的前缀
// 哈夫曼编码是一种最优的前缀编码，可让所传电文总长度最短

// 具体写法：按权值画出哈夫曼树，然后按照左0右1对每条路径编码。从根到叶子的路径的编码组合即为该叶子上权值的哈弗曼编码

#include<stdlib.h>
#include<stdio.h> 
#include<string.h>  
#define OVERFLOW -2

typedef struct{
    char ch;
    int weight;
    unsigned int parent, lchild, rchild;
} HTNode, *Huffmantree;         //动态分配数组存储哈夫曼树

typedef char **HuffmanCode;     //动态分配数组存储哈夫曼编码表

// 思想：先找两个并比较，作初始的最小值和次小值，然后剩下的与两个比较
void Select(Huffmantree &T, int n, int &s1, int &s2){
    // int i = 2, min1 = T[1].weight, min2 = T[1].weight;               //有问题！
    int i, min1 = 0, min2 = 0;
    for (i = 1; i <= n; ++i){
        if(T[i].parent == 0){
            if(min1 == 0)                               //找到第一个parent为0的i的值，并赋给两个最小值
                min1 = i;                               //这边一开始不能赋min1=min2=i，不然如果一开始的就是最小的，最后返回的两个就会相等
            else if(min1 != 0 && min2 == 0){            //初始化前两个
                if(T[i].weight >= T[min1].weight)
                    min2 = i;
                else{
                    min2=min1;
                    min1 = i;
                }
            }
            else{
                if(T[i].weight <= T[min1].weight){      //这边要是等号，因为=min1时也比min2小
                    min2 = min1;                        //替换
                    min1 = i;
                }
                else if(T[i].weight < T[min2].weight)
                    min2 = i;
            }
        }
    }
    s1 = min1;
    s2 = min2;
}

// CSDN上的实现方法

// int min1(Huffmantree &t,int i){
//     int j,flag;
//     unsigned int k = UINT_MAX;
//     for (j = 1;j <= i;j++)
//         if(t[j].weight < k && t[j].parent == 0)
//             k = t[j].weight,flag = j;
//             t[flag].parent = 1;
//             return flag;
// }

// void Select(Huffmantree &t,int i,int &s1,int &s2){
//     int j;
//     s1 = min1(t,i);
//     s2 = min1(t,i);
//     if(t[s1].weight > t[s2].weight){
//         j = s1;
//         s1 = s2;
//         s2 = j;
//     }
// }

//编码过程：
void HuffmanCoding(Huffmantree &HT, HuffmanCode &HC, int *w, int n, char* ch){           // w：权重数组
    // w存放n个字符的权值(均>0)，构造哈夫曼树HT,并求出n个字符的哈夫曼编码HC
    if(n<=1)
        return;
    int m = 2 * n - 1;                                                  //用到的空间：最初的n个+进行n-1次合并，共2n-1个空间
    HT = (Huffmantree)malloc(sizeof(HTNode) * (m + 1));                 //0号单元未使用，从1号单元开始使用
    Huffmantree p;
    int i, s1, s2, start, c, f;
    for (p = HT + 1, i = 1; i <= n; ++ch, ++i, ++p, ++w)                //一定要传 HT+1，从1开始使用！
        *p = {*ch, *w, 0, 0, 0};                                        //注意这种赋值方式，结构体可以直接这样赋值
    for (; i <= m; ++i, ++p)    
        *p = {'0', 0, 0, 0, 0};                                         //剩余的初始化为 0 0 0 0
    for (int i = n + 1; i <= m;i++){                                    //构建哈夫曼树
        //在HT[1...i-1]中选择parent为0且weight为最小的两个结点，其序号分别为s1和s2
        Select(HT, i - 1, s1, s2);
        HT[s1].parent = i;
        HT[s2].parent = i;
        HT[i].lchild = s1;                                              //默认更小的作为左孩子
        HT[i].rchild = s2;                                              //默认次小的作为右孩子
        HT[i].weight = HT[s1].weight + HT[s2].weight;   
    }

    //从叶子到根逆向求每个字符的哈弗曼编码
    HC = (HuffmanCode)malloc((n + 1) * sizeof(char *));                 //分配n个字符编码的头指针向量，HC[]代表二维数组的行，起始下标也是1，方便与前面对齐
    char *cd = (char *)malloc(sizeof(char) * n);                        //分配求编码的工作空间，最多n-1位，再多留一位给\0
    cd[n - 1] = '\0';                                                   //编码结束符            别忘记了
    for (int i = 1; i <= n;++i){                                        //逐个字符求哈夫曼编码
        start = n - 1;                                                  //编码结束符位置
        for (c = i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent){   //从叶子到根逆向求编码，注意for是先判断条件再执行    最后是c为根节点，根节点的parent是0，退出      //学习for的用法
            if(HT[f].lchild == c)
                cd[--start] = '0';                                      //0和1是在分支上面的   注意
            else
                cd[--start] = '1';
        }
        HC[i] = (char *)malloc(sizeof(char) * (n - start));             //为第i个字符编码分配空间
        strcpy(HC[i], &cd[start]);                                      //从cd位置开始复制编码到HC
    }
    free(cd);
}


//译码过程：
// 将二进制编码翻译回信息原文，m是树根编号
void Decoding(Huffmantree HT, int n, char *buff){
    int m = 2 * n - 1;                              //HT表的最后一位也就是最后生成的树根                
    int p = m;
    while(*buff != '\0'){                           //存疑：ppt上多给了一个条件：p!=0    为什么？？   
    //前面的条件：一整个二进制编码(包含多个译码)未读完
        if((*buff) == '0')                      
            p = HT[p].lchild;                       //进入左分支
        else
            p = HT[p].rchild;                       //进入右分支

        if(!HT[p].lchild && !HT[p].rchild){         //进入叶子结点
            printf("%c", HT[p].ch);
            p = m;                                  //重新从树根出发进行编码
        }
        buff++;                                     //buff指向下一个编码位
//------------------------如果直接定义char buff[100]的话buff++会报错-----------------------
    }
}


int main(){
    char ch[10] = {0}, buff[1000] = {0};
    int w[10] = {0};
    int n;
    printf("权值个数:");
    scanf("%d", &n);                                //输入完之后会回车，会被后面的%c读到
    getchar();                                      //这边换行符一定要加！！！   上面               
    printf("请输入对应权值与字符\n");
    for (int i = 0; i < n; ++i){    
        // scanf("%c %d\n", &ch[i], &w[i]);         //不能这样写!!!!   \n在scanf里面表示一直读入直到读到非空白符(非空格 换行符 制表符等)
        scanf("%c %d", &ch[i], &w[i]);              //这边结束位置加个\n  将每一行最后的换行符也读入
        getchar();
    }
    Huffmantree HT;
    HuffmanCode HC;
    HuffmanCoding(HT, HC, w, n, ch);
    printf("Huffman编码为:\n");
    for (int i = 1; i <= n; ++i)
        printf("%c   %s\n", HT[i].ch, HC[i]);
    printf("下面进行译码：\n请输入译码:");
    scanf("%s", buff);
    printf("译码对应的密文为：\n");
    Decoding(HT, n, buff);
    return 0;
}
 


// 68-84行的另一种算法：从根出发  遍历哈夫曼树，求哈弗曼编码
void HuffmanCoding(Huffmantree &HT, HuffmanCode &HC, unsigned int *w, int n, char* ch){           // w：权重数组
    //...           68行以前建立哈夫曼树
    HC = (HuffmanCode)malloc((n + 1) * sizeof(char *));
    int m = 2 * n - 1;
    int p = m, cdlen = 0;
    char *cd;
    for (int i = 1; i <= m; ++i)
        HT[i].weight = 0;               //weight变为另一个作用：遍历哈夫曼树时用作结点状态标志，表示第几次经过该结点
    while(p){
        if(HT[p].weight == 0){          //第一次经过这个结点-----向左
            HT[p].weight = 1;           //表示已经过该结点
            if(HT[p].lchild != 0){
                p = HT[p].lchild;
                cd[cdlen++] = '0';
            }
            else if(HT[p].rchild == 0){     //到了叶子结点
                HC[p] = (char *)malloc(sizeof(char) * (cdlen + 1));
                cd[cdlen] = '\0';           //单引号 注意
                strcpy(HC[p], cd);
            }
        }
        else if(HT[p].weight == 1){
            HT[p].weight = 2;
            if(HT[p].rchild != 0){
                p = HT[p].rchild;
                cd[cdlen++] = '1';
            }           
            else{                           //HT[p].weight == 2   退回
                HT[p].weight = 0;
                p = HT[p].parent;
                --cdlen;
            }
        }
    }
}
