//头插法建立单链表

//建立头结点-----输入的数据需要逆序！
L = (Linklist)malloc(sizeof(LNode));
if(!L)
    exit(OVERFLOW);
L->next = NULL;

for (int i = n; i > 0; i--)
{
    p = (Linklist)malloc(sizeof(LNode));
    if(!p)
        exit(OVERFLOW);
    scanf("%d", &p->data);
    p->next = L->next;
    L->next = p;
}


//尾插法建立单链表--------顺序输入数据，每次链表的表尾
tail = L = (Linklist)malloc(sizeof(LNode));
if(!L)
    exit(OVERFLOW);
L->next = NULL;
for (int i = n; i > 0; i--)
{
    p = (Linklist)malloc(sizeof(LNode));
    scanf("%d", &p->data);
    tail->next = p;
    tail = p;
}
tail->next = NULL;
