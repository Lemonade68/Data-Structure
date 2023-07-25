//已知指针la和lb分别指向两个无头结点单链表的首元结点，下面算法是从表la中删除自第i个元素起共len个元素后，
//将它们插入到表lb中第j个元素之前。请改正该算法。

//注意：la,p这种都是指针，因此,p=la后修改p的next或data都是直接修改的原数据！！！

//注意：无头结点链表尤其要注意第一个结点的处理

//思考：有头结点的链表：la,lb当做第0个结点，计算无异；无头结点链表：对第一个结点操作时，la/lb需要重新赋值
Status DeleteAndInsertSub(LinkedList la, LinkedList lb, int i, int j, int len) {
    if (i < 0 || j < 0 || len < 0)
        return INFEASIBLE;

    p = la;  k = 1;
    while (k < i - 1 && p)
    {p = p->next; k++;}
    if(!p) return INFEASIBLE;         //排除在la中取不到第i-1个元素的情况
    
    q = p->next;
    if(!q) return INFEASIBLE;         //排除在la中取不到第i个元素的情况
    
    k = 1;
    while (k<len && q) 
    {q = q->next; k++;}
    if(!q) return INFEASIBLE;         //排除在la中取不到i后共len个长度的情况

    if(i==1){la = q->next;}           //i等于1的特殊情况
    else{p->next = q->next;}          //删除a中的这段链表
    
    s = lb;  k = 1;
    while (k<j && s)  
    {s = s->next; k++;}
    if(!s) return INFEASIBLE;         //排除在lb中取不到第j个元素的情况
    
    if (j == 1) {q->next = lb; lb = q;}      //j=1时的特殊情况
    else{q->next = s->next; s->next = p;} 
    
    return OK;
}  


//注意：上述算法不一定准确