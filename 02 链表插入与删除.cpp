// ���������ɾ��Ԫ��

//���룺��i��λ��ǰ����Ԫ��e------�ҵ�i-1��Ԫ��
p = L;   
j = 0;
// p=L->next; j=1;  ����Ч����ͬ������    ����������ɾ����һ��Ԫ��ʱ����Ҫ�õ���0�������jҪ��0��ʼȡֵ

//˼����������Բ������һλ���棬�ҵ������һ���� ���Բ��ڵ�һλǰ�棬����while����ȡ��=������ֱ������
while(p && j<i-1)          //Ѱ�ҵ�i-1�����
{
    p = p->next;
    j++;
}
if(!p || j>i-1)
    return ERROR;

s = (Linklist)malloc(sizeof(LNode));
if(!s)
    exit(OVERFLOW);

s->data = e;
s->next = p->next;
p->next = s;
return OK;


//ɾ����ɾ����i��Ԫ�أ���e������ֵ
p = L;
j = 0;
while(p && j<i-1)
{
    p = p->next;
    j++;
}
if(!p || j>i-1)
    return ERROR;
q = p->next;
p->next = q->next;
e = q->data;
free(q);
return OK;




//��������ȥ�� O��n��
var deleteDuplicates = function(head) {
    let current = head //���׽ڵ�ָ�븳ֵ��current
    while(current && current.next) { //��ǰ�ڵ��Լ���һ�ڵ㲻Ϊ��ʱ
        if(current.val === current.next.val) { //ֵ���
            current.next = current.next.next
        }else {
            current = current.next //ֵ�����
        }
    }
    return head //�����׽ڵ�
};