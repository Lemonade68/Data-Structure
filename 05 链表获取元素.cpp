// �����GetElem ���룺LinkList L,int i,Elemtype &e

p = L->next;    //pָ���һ�����
int j = 1;      //jΪ������
 //���ﲻ���õ���0����㣬���j�����1��ʼȡ��  ����ͷ���ᱻ���ɵ�0��Ԫ�أ�i=0ʱ���ᱨ��

while(p && j<i)   //˳�������ң�ֱ��pΪ�ջ��ҵ�i
{
    p = p->next;
    j++;
}

if(!p || j>i)     //���j>i��Ϊ�˷�ֹiΪ��������Ϊ����ͨ������������˳���һ���ж�i�볤�ȵĹ�ϵ
    return error;

e = p->data;
return OK;