//�ڴ�ͷ����˫��ѭ�������е�i��λ��֮ǰ����Ԫ��e

p=L->next;
j = 1;  
while(p!=L && j<i){
    p = p->next;
    j++;
}
//ע�⣺���֮���Բ���j=0������������ԭ��
//1. while������Ϊp!=L�����j=0,��ֱ���˳�
//2. ˫��ѭ���������priorָ�룬�뵥����ͬ

if((p==L && j<i)|| j>i)    //i>n+1��i<1�����
    return ERROR;
if(s=(DulLinkList)malloc(sizeof(DulNode)))
    return ERROR;

s->data = e;
s->prior = p->prior;
p->prior->next = s;
s->next = p;
p->prior = s;
return OK;