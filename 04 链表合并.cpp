//����������Ϊһ����������, ab��Ϊ�ǵݼ�����

//˼����������ֵ��ʵ��û�з����仯��ֻ�����µ�һ�������´����������ı��˽���nextָ�룩



void MergeList_L(Linklist &La, Linklist &Lb, Linklist &Lc)   //����Ķ���ͷ���
{
    Pa = La->next;
    Pb = Lb->next;
    Pc = Lc = La;  //Pc��ָ��ͷ��㣬��La��ͷ�����Ϊ����ͷ���    ����ͷ�����Ȼ��Lc
    while(Pa && Pb)
    {
        if(Pa->data <= Pb->data)
        {
            Pc->next = Pa;
            Pc = Pa;                //���pc��tail��������ͬ����Ҫָ������β��
            Pa=Pa->next;
        }
        else
        {
            Pc->next = Pb;
            Pc = Pb;
            Pb = Pb->next;
        }
    }
    //ע������Ĵ����� ****
    Pc->next = Pa ? Pa : Pb;
    free(Lb);           //���ɾ�������һ��ͷ���
}