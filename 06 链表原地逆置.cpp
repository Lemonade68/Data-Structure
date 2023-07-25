Status Reverse(Linklist &L) {
    //将链表第1、2结点间断开
    p = L->next->next;
    L->next->next = NULL;

    //尾插法依次将2结点后的结点插入到L后
    while (p != NULl)
    {
        q = p->next;
        p->next = L->next;
        L->next = p;
        p = q;
    }
    return OK;
}//Reverse