// ��֪���Ա��е�Ԫ����ֵ�����������У����Ե�������Ϊ�洢�ṹ����дһ����Ч���㷨��
// ɾ����������ֵ����mink��С��maxk��Ԫ�أ������д���������Ԫ�أ���ͬʱ�ͷű�ɾ�����Ŀռ䣬
// ����������㷨��ʱ�临�Ӷȣ�ע�⣺mink��maxk�Ǹ����������α��������ǵ�ֵ���������Ԫ����ͬ��Ҳ���Բ�ͬ��

//��ͷ��������
p = L;     
while (p->next && p->next->data <= mink) {p = p->next;}  //Ѱ�ҵ�һ������mink�Ľ���ǰһ�����p
if(!p->next) return INFEASIBLE;

q = p->next;
k = 0;  //������
while (q && q->data < maxk){q = q->next; k++;}  //Ѱ�����һ��С��maxk�Ľ��q
if(!q) {p->next = NUll;}                        //�������������ҵ���󶼲��Ǻ���������Ļ�˵������ȫ��maxkС
else{s = p->next; p->next = q->next;}           //�����¼��ɾ���������

for (i = 0; i < k; i++){                        //���ɾ�����ռ�
    m = s->next;
    free(s);
    s = m;
}

//�Ľ���Ҫ��¼i-1���Ļ�����ʹ��pre=L,����ʹ��  pre���ϵ���pre->next;
//������룺
bool ListDelete(LinkList* L,Element mink,Element maxk){
    if(mink>maxk) return -1;
    LinkList* pre;
    LinkList* head = L;//LΪͷ�ڵ�
    pre = L;
    L = L->next;
    while(L->data<mink){
        L = L->next;
        pre = pre->next;
    }
    //ɾ���ڵ�
    while(L->data<=maxk)
    {
        LinkList* q = L;
        pre->next = L->next;
        L = L->next;
        free(q);
    }
 
    while(head->next){
        cout<<head->next->data<<" ";
        head = head->next;
    }
    return 1;
}
