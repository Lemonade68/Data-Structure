//ɾ��*p����ֱ�Ӻ�̽�㣺
q = p->next;
p->next = q->next;
free(q);

//ɾ��*p����ֱ��ǰ����㣺
q = L;
while(q->next->next != p)
    q = q->next;
s = q->next;
q->next = p;
free(s);

//ɾ��*p��㣺
q = L;
while(q->next != p)
    q = q->next;
q->next = p->next;
free(p);

//ɾ����Ԫ��㣺
s = L->next;
L->next = s->next;
free(s);

//ɾ�����һ����㣺
q = L;
while(q->next->next != NULL)
    q = q->next;
tail = q->next;
q->next = NULL;
free(tail);
