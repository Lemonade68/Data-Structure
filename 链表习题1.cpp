// 已知线性表中的元素以值递增有序排列，并以单链表作为存储结构。试写一个高效的算法，
// 删除表中所有值大于mink且小于maxk的元素（若表中存在这样的元素），同时释放被删除结点的空间，
// 并分析你的算法的时间复杂度（注意：mink、maxk是给定的两个参变量，它们的值可以与表中元素相同，也可以不同）

//带头结点的链表
p = L;     
while (p->next && p->next->data <= mink) {p = p->next;}  //寻找第一个大于mink的结点的前一个结点p
if(!p->next) return INFEASIBLE;

q = p->next;
k = 0;  //计数器
while (q && q->data < maxk){q = q->next; k++;}  //寻找最后一个小于maxk的结点q
if(!q) {p->next = NUll;}                        //这边特殊情况：找到最后都不是后面的条件的话说明后面全比maxk小
else{s = p->next; p->next = q->next;}           //否则记录并删除这段链表

for (i = 0; i < k; i++){                        //最后删除结点空间
    m = s->next;
    free(s);
    s = m;
}

//改进：要记录i-1结点的话可以使用pre=L,并且使用  pre不断等于pre->next;
//具体代码：
bool ListDelete(LinkList* L,Element mink,Element maxk){
    if(mink>maxk) return -1;
    LinkList* pre;
    LinkList* head = L;//L为头节点
    pre = L;
    L = L->next;
    while(L->data<mink){
        L = L->next;
        pre = pre->next;
    }
    //删除节点
    while(L->data<=maxk)
    {
        LinkList* q = L;
        pre->next = L->next;
        L = L->next;
        free(q);
    }
 
    while(head->next){
        cout<<head->next->data<<" ";
        head = head->next;
    }
    return 1;
}
