// 链表的GetElem 传入：LinkList L,int i,Elemtype &e

p = L->next;    //p指向第一个结点
int j = 1;      //j为计数器
 //这里不能用到第0个结点，因此j必须从1开始取，  否则头结点会被当成第0个元素，i=0时不会报错

while(p && j<i)   //顺序向后查找，直到p为空或找到i
{
    p = p->next;
    j++;
}

if(!p || j>i)     //这边j>i是为了防止i为负数，因为最普通的链表不可以像顺序表一样判断i与长度的关系
    return error;

e = p->data;
return OK;