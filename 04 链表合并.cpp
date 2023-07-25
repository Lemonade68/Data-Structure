//两有序链表并为一个有序链表, ab都为非递减排列

//思考：各结点的值其实都没有发生变化，只是用新的一条链重新串了起来（改变了结点的next指针）



void MergeList_L(Linklist &La, Linklist &Lb, Linklist &Lc)   //传入的都是头结点
{
    Pa = La->next;
    Pb = Lb->next;
    Pc = Lc = La;  //Pc仍指向头结点，用La的头结点作为最后的头结点    最后的头结点仍然是Lc
    while(Pa && Pb)
    {
        if(Pa->data <= Pb->data)
        {
            Pc->next = Pa;
            Pc = Pa;                //这边pc和tail的意义相同，需要指向链的尾部
            Pa=Pa->next;
        }
        else
        {
            Pc->next = Pb;
            Pc = Pb;
            Pb = Pb->next;
        }
    }
    //注意下面的处理方法 ****
    Pc->next = Pa ? Pa : Pb;
    free(Lb);           //最后删除多出的一个头结点
}