// �ڲ��ö�������洢�ṹ�Ļ����ϣ�ʵ�ֶ������������������㣺
// ��1��ʵ���ڶ����������ϲ���ָ���ؼ��ֵ����㣻
// ��2��ʵ���ڶ����������ϲ���һ���ؼ��ֵ����㣻
// ��3��ʵ���ڶ�����������ɾ��ָ���ؼ��ֵ����㣻
// ��4��ʵ�ֶ���������������������㣬�������������У�
// ��5���ӿյĶ�����������ʼ������һ���ؼ������У�����ʵ�ֲ�������ĺ�������������������


// ���ɣ�search��pre�������õĻ�   �����ϵ�д��delete��ǰ��������������

// ���ע�����һ�������ԣ��õ����ķ�ʽ�Ǵ�T->lchild/rchild�õ�   ����   �����ѵ�������֮������һ��ָ��p������
// ǰ�߰����˸��ӽڵ�����ϵ��ϵ������û��

#include<stdio.h>
#include<stdlib.h>
#define OVERFLOW -2

typedef struct BiTNode{
    int data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;


// ��������㷨
void InOrder(BiTree T){
    if(T){
        InOrder(T->lchild);
        printf("%d ", T->data);
        InOrder(T->rchild);
    }
}


//�����㷨
int Search(BiTree T, int key, BiTree &p, BiTree &pre){           // ���ҵ���p���ظý�㣻��δ�ҵ���p���ظ�·�������һ���������Ľ��   pre��ʼ�ÿ�
    if(!T){
        p = pre;                                                // ����·�������һ�����
        return 0;                                               // 0 ����δ�ҵ��� 1 �������ҵ� 
    }
    else{
        if(key == T->data){
            p = T;
            return 1;
        }
        else if(key < T->data){
            pre = T;                                            //�޸�preֵ
            return Search(T->lchild, key, p, pre);
        }
        else{
            pre = T;
            return Search(T->rchild, key, p, pre);
        }
    }
}





//�����㷨
void Insert(BiTree &T, int key){                                //�����������޸ģ���Ҫ����
    BiTree p, pre = NULL;
    int i = Search(T, key, p, pre);
    if(i == 0){                                                 //�Ҳ�������Ҫ����
        BiTree q = (BiTree)malloc(sizeof(BiTNode));
        if(!q)
            exit(OVERFLOW);
        q->data = key;
        q->lchild = NULL;
        q->rchild = NULL;
        if(!p)                                                  //���һ��ʼ�ǿ���
            T = q;                                              //��������Ϊq��������������Ҫ�ı䣬������TҪ���ó�����
        else if(key < p->data)
            p->lchild = q;
        else
            p->rchild = q;
    }
}


// ���ϵķ������ɹ�

// void Delete(BiTree &p){
//     if(!p->rchild){             //�������գ���ֻ���ؽ�����������    ������ɾ��Ҷ�ӽ������
//         BiTree q = p;
//         p = p->lchild;          //**  ����   ��������Բ�ͨ��˫��ֱ������������
//         free(q);
//     }
//     else if(!p->lchild){
//         BiTree q = p;
//         p = p->rchild;
//         free(q);
//     }
//     else{                       //���Ҷ��к��ӽ������
//         BiTree q = p, s = p->lchild;
//         while(s->rchild){       //Ѱ��ǰ��(���ӵ������ӽڵ�)----Ҳ��֤��s����û���Һ��ӣ�����sΪq���Һ���    
//             q = s;              //qʼ��ָ��s��˫�׽��
//             s = s->rchild;
//         }
//         p->data = s->data;      //ǰ�������ݸ��Ƶ�p���
//         if(q != p)              //ע�������������----q!=pʱ��s��ӵ�q����
//             q->rchild = s->lchild;      //�ؽ�q����������
//         else                    //ע�������������----q==pʱ��s��ӵ�q����q��ʱ����p��
//             q->lchild = s->lchild;
//         free(s);                //����ǰ�����ɾ��
//     }
// }   

// void DeleteBST(BiTree &T, int key){
//     //������key�ؼ��ֵ�Ԫ�أ�ɾ��
//     if(!T)
//         return;
//     else{
//         if(T->data == key)
//             Delete(T);                                                           // ע�⣺ ��߰�����T�����ϸ�T->lchild�����Ը㵽delete������p���൱��T->lchild    !!!!!!!!!!!!
//         else if(T->data > key)
//             DeleteBST(T->lchild, key);
//         else
//             DeleteBST(T->rchild, key);
//     }
// }


//   �������Լ�д�İ汾��ʹ����search�����p��λ�ã� ���������Ļ�delete p��ǰ������������ϵĴ�����������                                      ---------- why?????????�������棩

// ɾ���㷨��
void DeleteBST(BiTree &T, int e){                                   //ɾ��e�����������˲�����Ҫ����
    BiTree p, pre = NULL;
    int i = Search(T, e, p, pre);
    if(i == 0){
        printf("δ�ҵ��ý��\n");
        return;
    }
    else{
        // Delete(p);
        if(!p->lchild){                                             //ͬʱ������pΪҶ�ӽ����pֻ�������������
            if(pre->lchild == p)
                pre->lchild = p->rchild;
            else
                pre->rchild = p->rchild;
            free(p);

            //�����search���p��λ�õĻ�������Ĵ���ᱨ��          ***********ԭ��searchֻ���ҵ��˸ý�㲢��pָ������ ���ǲ�û�а����ϸ�����p֮��Ĺ�ϵ���ı���ϸ����������ͻ���Ұָ��
            // BiTree q = p;
            // p = p->rchild;                                      //�����ĺ�����p������ָ��һƬ��ַ�������ؽ�������,����ԭ���ĵ�ַ�ڴ����
            // free(q);
        }
        else if(!p->rchild){
            if(pre->lchild == p)
                pre->lchild = p->lchild;
            else
                pre->rchild = p->lchild;
            free(p);

            // BiTree q = p;
            // p = p->lchild;                                      //�����ĺ�����p������ָ��һƬ��ַ�������ؽ�������,����ԭ���ĵ�ַ�ڴ����
            // free(q);
        }
        else{                                                       //������������������ҵ�ǰ������ǰ����ֵ�����ý�㣬��ɾ��ǰ��(���ӵ���������)
            BiTree s = p->lchild;
            pre = p;
            while(s->rchild){
                pre = s;
                s = s->rchild;
            }
            p->data = s->data;
            if(pre == p){                                       //���Ҳ����д�� pre == p
                pre->lchild = s->lchild;
                free(s);
            }
            else{
                pre->rchild = s->lchild;                        //s������������������
                free(s);
            }
        }
        printf("ɾ���ɹ���\n");
    }
}

    

int main(){
    int n;
    BiTree T = NULL, p = NULL, pre = NULL;
    printf("����������Ԫ�صĸ�����");
    scanf("%d", &n);
    printf("����������Ԫ�أ�");
    for (int i = 0; i < n;i++){
        int e;
        scanf("%d", &e);
        Insert(T, e);
    }
    
    InOrder(T);         //��һ���ӡ��˵��������ȷ
    printf("\n");
    
    printf("������Ҫ���ҵ�Ԫ�أ�");
    scanf("%d", &n);
    int i = Search(T, n, p, pre);
    if(i == 0)
        printf("δ�ҵ�\n");
    else
        printf("���ҵ�\n");
    
    printf("������Ҫ�����Ԫ�أ�");
    scanf("%d", &n);
    Insert(T, n);
    InOrder(T);         //�ڶ����ӡ��˵������λ����ȷ
    printf("\n");

    printf("������Ҫɾ����Ԫ�أ�");
    scanf("%d", &n);
    // Delete(T, n);
    DeleteBST(T, n);
    InOrder(T);         //�������ӡ��˵��ɾ��������ȷ


    return 0;
}




// �����������Ľ���Ҳ���Բ�ʹ�ò��뺯����ֻ����������в������ظ��Ĺؼ��ּ���