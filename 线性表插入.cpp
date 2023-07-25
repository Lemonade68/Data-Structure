//线性表插入算法，后面整体右移

// 第i个位置 ：0<i<=n
// L.listsize: 申请的空间长度
// L.length: 顺序表的长度

if(i<1||i>L.length+1)
    return error;

if(L.length>=L.listsize)          //重要的是这边的 "="
{
    newbase = (Elemtype *)realloc(L.elem, (L.listsize + LISTINCREMENT) * sizeof(Elemtype));
    if(!newbase)
        exit(OVERFLOW);
    L.elem = newbase;
    L.listsize += LISTINCREMENT;
}

q = &(L.elem[i - 1]);
for(p=&(L.elem[L.length-1]);p>=q;p--)
    *(p + 1) = *p;

*p = e;     //插入e
L.length++;
