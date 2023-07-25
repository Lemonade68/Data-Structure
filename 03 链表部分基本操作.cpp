//删除*p结点的直接后继结点：
q = p->next;
p->next = q->next;
free(q);

//删除*p结点的直接前驱结点：
q = L;
while(q->next->next != p)
    q = q->next;
s = q->next;
q->next = p;
free(s);

//删除*p结点：
q = L;
while(q->next != p)
    q = q->next;
q->next = p->next;
free(p);

//删除首元结点：
s = L->next;
L->next = s->next;
free(s);

//删除最后一个结点：
q = L;
while(q->next->next != NULL)
    q = q->next;
tail = q->next;
q->next = NULL;
free(tail);
