#include<stdio.h>
#include<stdlib.h>
#define SUCCESS 1
#define UNSUCCESS 0
#define DUPLICATE -1        //重复
#define Status int

// 记录在表中位置和其关键字之间存在一种确定的关系
// 对于一个哈希函数H(k),在知道关键字k后求出的H(k)，即为对应的存储地址

// 冲突：不同关键字对应的哈希函数值相同
// 同义词：发生冲突的关键字

// 哈希表：根据设定的哈希函数以及处理冲突的方法，将一组关键字的存储地址映射到一个连续的地址集的查找表
// 装填因子α：哈希表中存入元素的的个数n与哈希表大小m的比值，即α=n/m


// 哈希函数的构造方法：
// 1.直接定址法
// 2.数字分析法
// 3.平方取中法
// 4.折叠法
// 5.除留余数法    H(key) = key mod p
// 6.随机数法


// 处理冲突的方法：
// 1.开放定址法
// 为产生冲突的地址H(key)求得一个地址序列：H0,H1,H2,...,Hs
// 其中H0 = H(key),  Hi = (H(key)+Di) mod m;
// 对于增量Di有三种取法：
        // a.线性探测再散列:  Di = c * i
        // b.平方探测再散列:  Di = 1^2, -1^2, 2^2, -2^2, ...
        // c.随即探测再散列:  Di 是一组伪随机数列


// 2.链地址法
// 将所有哈希地址相同的记录都链接在同一链表中


// 哈希表的查找：
// 对于给定K, 计算哈希地址i = H(K)
// 若r[i] = NULL 则查找不成功
// 若r[i].key = K 则查找成功
// 否则求下一地址Hi,直至    r[Hi] = NULL --不成功      r[Hi].key = K --成功   


// 开放定址哈希表的存储结构：
int hashsize[] = {997, 103, 97, 13, 11};        //合适的素数序列
typedef struct{
    int *elem;
    int count;          //当前数据元素个数
    int sizeindex;      //hashsize[sizeindex]为当前容量
} HashTable;

int Hash(int k){        //哈希函数

}

void RecreateHash(HashTable &H){                 //重建哈希表函数

}

void collision(int &p, int &c){                 //计算冲突后p的下一位置的函数
    //以线性探测再散列为例：
    p++;
}

Status SearchHash(HashTable H, int k, int &p, int &c){          // p与c都要取址， 值要传出去， c初值为0
    // 查找关键字为k的元素，若查找成功，p指示待查数据元素在表中位置，返回SUCCESS
    // 否则，p指示插入位置，并返回UNSUCCESS
    // c用于计算冲突次数，初值置零，供建表插入时参考
    p = Hash(k);        //求得哈希地址
    while(H.elem[p] != 0 && H.elem[p] != k)     //该位置中填有记录  且关键字冲突
        collision(p, ++c);
    if(H.elem[p] == k)
        return SUCCESS;
    else
        return UNSUCCESS;

    //无论哪种情况，p的位置都符合上面绿字的要求
}

Status InsertHash(HashTable &H, int e){
    //查找不成功时插入数据元素e到开放定址哈希表H中，返回OK；  若冲突次数过大， 重建哈希表
    int c = 0;      //冲突次数
    int p;
    int c_max = hashsize[H.sizeindex] / 2;      //冲突阙值，可调整
    if(SearchHash(H, e, p, c))
        return DUPLICATE;                       //表示表中已有与e同关键字的元素
    else if(c <= c_max){
        H.elem[p] = e;
        H.count++;
        return SUCCESS;
    }
    else{                                       //重建哈希表
        RecreateHash(H);
        return UNSUCCESS;
    }

}

// *****************   ASL计算：  成功与不成功   ****************
// 成功：每个关键字的探测次数之和 / 关键字总个数
// 失败：对于每个地址位而言一直往后探测直到为NULL的次数之和 / 地址位总可能的情况数（所有情况都考虑）     ---例如：H(key)=key % 13，  地址位总可能情况就是0,1,...,12  共13种情况

// 链地址存储也类似（注：链表查找失败的ASL与NULL比较不算次数！！！！！）



