// ����һ�ö���������������������У�Ҫ�����ҳ���������������������Ƚ�㣨��� LCA��

// *********    �����������Ľ���Ҳ���Բ�ʹ�ò��뺯����ֻ����������в������ظ��Ĺؼ��ּ���     *********

// ��ÿһ�Ը����� U �� V������ҵ� A �����ǵ�����������Ƚ��ļ�ֵ��
// ����һ������� LCA of U and V is A.������� U �� V �е�һ�������
// ��һ���������ȣ�����һ������� X is an ancestor of Y.������ X ��
// �Ǹ����Ƚ��ļ�ֵ��Y ����һ����ֵ����� �������������Ҳ����� U �� V 
// Ϊ��ֵ�Ľ�㣬����� ERROR: U is not found. ���� ERROR: V is not found.��
// ���� ERROR: U and V are not found.��


// ��ʼ������ʱ��һ��Ҫ��ʼ����NULL      ����һ��Ҫ�ǵó�ʼ��������
// �ж�����ʱע���ж��Ƿ�Ϊ����ǰ����Ȼ�����Ϊ�յ��Ƿ��������Ա�����

// ��LCA��ʱ   ע���㷨

#include<stdio.h>
#include<stdlib.h>
#define OVERFLOW -2

typedef struct BiTNode{
    int data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

void BuildTree(BiTree &T, int e){               // ��������
    if(!T){
        T = (BiTree)malloc(sizeof(BiTNode));
        if(!T)
            exit(OVERFLOW);
        T->data = e;
        T->lchild = NULL;
        T->rchild = NULL;
    }
    else{
        if(T->data > e)
            BuildTree(T->lchild, e);
        else
            BuildTree(T->rchild, e);
    }
}

BiTree FindAnscestor(BiTree T, int u){
    BiTree pre = T;
    while(T->data != u){                            //Ѱ��u���ĸ����
        if(T->data > u){
            pre = T;                                //������pre
            T = T->lchild;
        }
        else{
            pre = T;
            T = T->rchild;
        }
    }
    return pre;
}

bool FindBTNode(BiTree T, int p){
    if(T){  
        if(T->data == p)
            return true;
        else if(T->data > p)
            return FindBTNode(T->lchild, p);
        else
            return FindBTNode(T->rchild, p);
    }
    else
        return false;
}

bool IsAnscestor(BiTree T, int f, int s){
    while(T->data != f){                            //Ѱ��f���
        if(T->data > f)
            T = T->lchild;
        else
            T = T->rchild;
    }
    while(T && T->data != s){                       //********  ���ǰ���ܸ㷴  ********
        if(T->data > s)
            T= T->lchild;
        else
            T = T->rchild;
    }
    if(!T)                                          //û�ҵ�
        return false;
    else
        return true;
}

int findLCA(BiTree T, int u, int v){
    BiTree Tu, Tv;
    Tu = FindAnscestor(T, u);                       //u���ĸ����
    Tv = FindAnscestor(T, v);                       //v���ĸ����
    BiTree T_LCA = Tu;                              //һ��ʼ���ó�u�ĸ����
    bool find;
    while(1){                                       //�ܹ����ҵ���������Ϊ�����
        find = FindBTNode(T_LCA, v);
        if(find == true)
            return T_LCA->data;
        else
            T_LCA = FindAnscestor(T, T_LCA->data);
    }
}

//ѧϰ����뷨��������
int Find_LCA(BiTree t, int u, int v){
    if(u < t->data && v < t->data)
        return Find_LCA(t->lchild, u, v);
    else if(u > t->data && v > t->data)
        return Find_LCA(t->rchild, u, v);
    else
        return t->data;
}

int main(){
    int m, n, e, u, v;
    bool findu, findv, uiav, viau;
    BiTree T = NULL;                                //�ǵó�ʼ��������
    scanf("%d %d", &m, &n);

    for (int i = 0; i < n; ++i){
        scanf("%d", &e);
        BuildTree(T,e);
    }

    for (int i = 0; i < m; i++){
        scanf("%d %d", &u, &v);
        findu = FindBTNode(T, u);
        findv = FindBTNode(T, v);
        if(!findu && !findv)
            printf("ERROR: %d and %d are not found.\n", u, v);
        else if(!findu)
            printf("ERROR: %d is not found.\n", u);
        else if(!findv)
            printf("ERROR: %d is not found.\n", v);
        else{
            uiav = IsAnscestor(T, u, v);
            viau = IsAnscestor(T, v, u);
            if(uiav)
                printf("%d is an ancestor of %d.\n", u, v);
            else if(viau)
                printf("%d is an ancestor of %d.\n", v, u);
            else{
                // int m = findLCA(T, u, v);                                        //���ܻᳬʱ
                int m = Find_LCA(T, u, v);
                printf("LCA of %d and %d is %d.\n", u, v, m);
            }
        }

    }
    return 0;
}




// ����������
// 6 8
// 6 3 1 2 5 4 8 7
// 2 5
// 8 7
// 1 9
// 12 -3
// 0 8
// 99 99
