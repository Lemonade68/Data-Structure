//��ָ֪��la��lb�ֱ�ָ��������ͷ��㵥�������Ԫ��㣬�����㷨�Ǵӱ�la��ɾ���Ե�i��Ԫ����len��Ԫ�غ�
//�����ǲ��뵽��lb�е�j��Ԫ��֮ǰ����������㷨��

//ע�⣺la,p���ֶ���ָ�룬���,p=la���޸�p��next��data����ֱ���޸ĵ�ԭ���ݣ�����

//ע�⣺��ͷ�����������Ҫע���һ�����Ĵ���

//˼������ͷ��������la,lb������0����㣬�������죻��ͷ��������Ե�һ��������ʱ��la/lb��Ҫ���¸�ֵ
Status DeleteAndInsertSub(LinkedList la, LinkedList lb, int i, int j, int len) {
    if (i < 0 || j < 0 || len < 0)
        return INFEASIBLE;

    p = la;  k = 1;
    while (k < i - 1 && p)
    {p = p->next; k++;}
    if(!p) return INFEASIBLE;         //�ų���la��ȡ������i-1��Ԫ�ص����
    
    q = p->next;
    if(!q) return INFEASIBLE;         //�ų���la��ȡ������i��Ԫ�ص����
    
    k = 1;
    while (k<len && q) 
    {q = q->next; k++;}
    if(!q) return INFEASIBLE;         //�ų���la��ȡ����i��len�����ȵ����

    if(i==1){la = q->next;}           //i����1���������
    else{p->next = q->next;}          //ɾ��a�е��������
    
    s = lb;  k = 1;
    while (k<j && s)  
    {s = s->next; k++;}
    if(!s) return INFEASIBLE;         //�ų���lb��ȡ������j��Ԫ�ص����
    
    if (j == 1) {q->next = lb; lb = q;}      //j=1ʱ���������
    else{q->next = s->next; s->next = p;} 
    
    return OK;
}  


//ע�⣺�����㷨��һ��׼ȷ