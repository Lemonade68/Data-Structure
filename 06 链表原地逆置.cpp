Status Reverse(Linklist &L) {
    //�������1��2����Ͽ�
    p = L->next->next;
    L->next->next = NULL;

    //β�巨���ν�2����Ľ����뵽L��
    while (p != NULl)
    {
        q = p->next;
        p->next = L->next;
        L->next = p;
        p = q;
    }
    return OK;
}//Reverse