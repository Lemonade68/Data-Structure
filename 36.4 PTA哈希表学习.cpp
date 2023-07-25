// 函数Find应根据裁判定义的散列函数Hash( Key, H->TableSize )从散列表H中查到Key的位置并返回。
// 如果Key不存在，则返回线性探测法找到的第一个空单元的位置；若没有空单元，则返回ERROR。

#include <stdio.h>

#define MAXTABLESIZE 100000  /* 允许开辟的最大散列表长度 */
typedef int ElementType;     /* 关键词类型用整型 */
typedef int Index;           /* 散列地址类型 */
typedef Index Position;      /* 数据所在位置与散列地址是同一类型 */

/* 散列单元状态类型，分别对应：有合法元素、空单元、有已删除元素 */
typedef enum { Legitimate, Empty, Deleted } EntryType;                                  //这一步学习下

typedef struct HashEntry Cell; /* 散列表单元类型 */
struct HashEntry{
    ElementType Data; /* 存放元素 */
    EntryType Info;   /* 单元状态 */
};

typedef struct TblNode *HashTable; /* 散列表类型 */
struct TblNode {   /* 散列表结点定义 */
    int TableSize; /* 表的最大长度 */
    Cell *Cells;   /* 存放散列单元数据的数组 */
};

HashTable BuildTable(); /* 裁判实现，细节不表 */
Position Hash( ElementType Key, int TableSize )
{
    return (Key % TableSize);
}

#define ERROR -1
Position Find( HashTable H, ElementType Key );

int main()
{
    HashTable H;
    ElementType Key;
    Position P;

    H = BuildTable(); 
    scanf("%d", &Key);
    P = Find(H, Key);
    if (P==ERROR)
        printf("ERROR: %d is not found and the table is full.\n", Key);
    else if (H->Cells[P].Info == Legitimate)                                            //  这边再判断是空还是有数据
        printf("%d is at position %d.\n", Key, P);
    else
        printf("%d is not found.  Position %d is returned.\n", Key, P);

    return 0;
}

/* 你的代码将被嵌在这里 */
Position Find( HashTable H, ElementType Key ){
    int p = Hash(Key, H->TableSize);
    int count = 1;
    while(H->Cells[p].Info != Empty && H->Cells[p].Data != Key && count <= H->TableSize){
        p = (p + 1) % H->TableSize;
        count++;
    }
    if(count > H->TableSize)
        return ERROR;
    else
        return p;
}