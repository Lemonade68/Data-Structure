//在带头结点的双向循环链表中第i个位置之前插入元素e

p=L->next;
j = 1;  
while(p!=L && j<i){
    p = p->next;
    j++;
}
//注意：这边之所以不用j=0，有以下两个原因：
//1. while中条件为p!=L，如果j=0,会直接退出
//2. 双向循环链表多了prior指针，与单链表不同

if((p==L && j<i)|| j>i)    //i>n+1与i<1的情况
    return ERROR;
if(s=(DulLinkList)malloc(sizeof(DulNode)))
    return ERROR;

s->data = e;
s->prior = p->prior;
p->prior->next = s;
s->next = p;
p->prior = s;
return OK;