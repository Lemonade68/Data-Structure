//���Ա�����㷨��������������

// ��i��λ�� ��0<i<=n
// L.listsize: ����Ŀռ䳤��
// L.length: ˳���ĳ���

if(i<1||i>L.length+1)
    return error;

if(L.length>=L.listsize)          //��Ҫ������ߵ� "="
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

*p = e;     //����e
L.length++;
