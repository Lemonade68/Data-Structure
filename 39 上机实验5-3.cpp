// 针对记录集合设计一个哈希表，完成相应的建表和查表程序。
// （1）假定每个记录有下列数据项：电话号码（长度不超过11的数字串）、用户名（长度不超过20个字符的字符串）、地址（长度不超50个字符的字符串）
// （2）从数据文件data.txt（预先建立）中读入各项记录，并逐一插入到哈希表中，分别用以电话号码和姓名为关键码设计相应的哈希函数；
// （3）以姓名为关键字时，采用链地址法解决冲突构造哈希表；以电话号码为关键字时，采用线性探查法解决冲突构造哈希表；
// （4）待查找的记录从键盘输入，应显示查找结果。


// 注意结构体赋值问题！！！      除了定义时   不能直接用{}来进行赋值
// 注意判断字符串是否为空的问题！！    不能直接if(!str)    而是要用strcmp来进行判断
// 涉及字符串的比较都要使用str___类的函数！


// 链式哈希表之后再写

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define Hashsize 11     //哈希表长度，用户可自定义
#define OVERFLOW -2

// 定义用户类
typedef struct{
    char tele[12];
    char UserName[20];
    char Add[50];
    int tele_trans;         //用于存放将电话字符串转成数字的值
} User, *Userptr;

typedef struct{
    Userptr elem;
    int hashsize = Hashsize;
} HashTable_tele;

typedef struct{
    Userptr *elem;          //用于生成每个元素为userptr的一片区域
    int hashsize = Hashsize;
} HashTable_username;

void InitHashTable_tele(HashTable_tele &HT){
    User user[5] = {
        {"13776655469", "wyq", "Jiangsu"},
        {"13584020203", "zxy", "Jiangsu"},
        {"13337818876", "wyl", "Jiangsu"},
        {"110", "jc", "Zhongguo"},
        {"120", "Ambulance", "Zhejiang"}   };

    // 不能这样赋值！！！！！
    // user[0] = {"13776655469", "wyq", "Jiangsu"};
    // user[1] = {"13584020203", "zxy", "Jiangsu"};
    // user[2] = {"13337818876", "wyl", "Jiangsu"};
    // user[3] = {"110", "jc", "Zhongguo"};
    // user[4] = {"120", "Ambulance", "Zhejiang"};

    for (int i = 0; i < 5; i++)                                                     //生成对应的tele_trans
        user[i].tele_trans = (user[i].tele[0] - '0') * 10 + user[i].tele[1] - '0';

    for (int i = 0; i < Hashsize; i++){                                             //算是结构体数组初始化为空
        strcpy(HT.elem[i].tele, "\0");
        strcpy(HT.elem[i].UserName, "\0");
        strcpy(HT.elem[i].Add, "\0");
        HT.elem[i].tele_trans = 0;
    };                             
    
    // 构建哈希表           （冲突次数阙值暂时不考虑）
    for (int i = 0; i < 5; i++){
        int p = user[i].tele_trans % 11;                                            //获得哈希值
        if(strcmp(HT.elem[p].tele,"\0") == 0)                                                        //若为"\0"，学习下  可以不检测整个结构体变量为空  而是某个成员的值为空
            HT.elem[p] = user[i];                                                   //若为空   则插入
        else{
            while(strcmp(HT.elem[p].tele,"\0") != 0 && strcmp(HT.elem[p].tele,user[i].tele) != 0)               //结构体不相等比较的话需要重载运算符 !=  这边简化      *****注意用strcmp判空*****
                p = (p + 1) % Hashsize;
            if(strcmp(HT.elem[p].tele,"\0") == 0)
                HT.elem[p] = user[i];
            else
                continue;                                                           //直接进入下一次循环
        }    
    }   
}

void InitHashTable_usna(HashTable_username &HT){
    
}

void Search(HashTable_tele HT, int &p, char *tele){
    int tele_trans = (tele[0] - '0') * 10 + tele[1] - '0';
    p = tele_trans % 11;                                                            //p为查找指标
    while(strcmp(HT.elem[p].tele,"\0") != 0 && strcmp(HT.elem[p].tele,tele) != 0)   //  小缺陷：哈希表已满的话会死循环-------------不用while    线性探测的话可以使用循环次数 / 或者while加个计数器
        p = (p + 1) % Hashsize;
    if(strcmp(HT.elem[p].tele,"\0") == 0)
        p = -1;
    else
        return;
}

int main(){
    HashTable_tele HT_tele;
    HashTable_username HT_usna;
    if(!(HT_tele.elem = (Userptr)malloc(sizeof(User)*Hashsize)))                    //创建以电话为关键字的哈希表
        exit(OVERFLOW);
    if(!(HT_usna.elem = (Userptr *)malloc(sizeof(Userptr)*Hashsize)))               //创建以姓名为关键字的哈希表
        exit(OVERFLOW);

    //简便起见，这边设置好哈希表中的数据
    InitHashTable_tele(HT_tele);
    // InitHashTable_usna(HT_usna);

    char tele[12] = {0};
    printf("请输入要查找的电话号码：");
    scanf("%s", tele);

    int p = -1;
    Search(HT_tele, p, tele);
    if(p == -1)
        printf("未找到！\n");
    else
        printf("电话：%s  姓名：%s  地址：%s\n", HT_tele.elem[p].tele, HT_tele.elem[p].UserName, HT_tele.elem[p].Add);
    return 0;
}