// ϡ�����m��n�еľ�����t������Ԫ��
// ϡ�����ӣ�t/(mn)<=0.05 ��Ϊϡ�����

// ��ϡ��������һ��������
// �洢����Ԫ��ʱ���������ڵ��к��е�λ��------��Ԫ��(i,j,aij)
// �ɱ���Ϊ��((),(),(),(),...,())   ����С�����ڴ�ŷ���Ԫ��

// ѹ���洢������

// һ����Ԫ��˳���

#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 12500
#define OVERFLOW -2

typedef struct{
    int i, j;       //���±������±�
    int e;          //����Ԫ��ֵ
} Triple;           //��Ԫ������

typedef struct{
    Triple data[MAXSIZE + 1];       //����data[0]��ʹ��
    int mu;         //��������
    int nu;         //��������
    int tu;         //����Ԫ�ظ���--��Ԫ���ܸ��������ṹ�����ܱ�����
} TSMatrix;         //ϡ���������

int main(){
    TSMatrix m;
    m.data;         //  m.data���ڴ洢m����Ԫ���
    return 0;
}

// ת���㷨Ϊ����   �ǳ��淽��������t[i][j]=m[j][i]��

// �㷨1�����ɨ�裬ÿ��ɨ������Ԫ�ز������зֱ�Ϊ1,2,3...��Ԫ��
void TransposeSMatrix(TSMatrix M, TSMatrix &T){
    T.mu = M.mu;
    T.nu = M.nu;
    T.tu = M.tu;
    if(T.tu){
        int index = 1;      //��Ԫ����T.data�д洢��λ��
        for (int col = 1; col <= M.nu; col++){      //ÿ1�ж�Ҫ����
            for (int p; p <= M.tu; p++){            //pָ��ǰ��Ԫ��
                if(M.data[p].j == col){
                    T.data[index].e = M.data[p].e;
                    T.data[index].i = M.data[p].j;      //ע��ת��ǰ��ij����
                    T.data[index].j = M.data[p].i;
                    index++;
                }
            }
        }
    }
}

// �Ľ���һ��ɨ�����ת��
// �㷨2��һ��ɨ��--�����M���е�һ������Ԫ��Ԫ����T.data��λ��
// ���� num[],num[col]��ʾ��col�еķ���Ԫ����
void SetParameters(int *num, int *cpot, TSMatrix M){
    // ��num[]
    for (int p = 1; p <= M.tu; p++){
        num[M.data[p].j]++;             //��Ӧ���е�Ԫ�ظ���++
    
    // ��cpot[]��cpot[col]��ʾM��col�е�һ������Ԫ����T�е�λ��
    cpot[1] = 1;        // ��1�е�1������Ԫ�ض�Ӧ�Ŀ϶���T�ĵ�һ��λ��
    int col;
    for (col = 2; col <= M.nu; col++)
        cpot[col] = cpot[col - 1] + num[col - 1];   //˼��������
    }
}


void FastTransposeSMatrix(TSMatrix M, TSMatrix &T){
    T.mu = M.mu;
    T.nu = M.nu;
    T.tu = M.tu;
    if(T.tu){
        int num[100] = {0};
        int cpot[100] = {0};
        SetParameters(num, cpot, M);
        for (int p; p <= M.tu; p++){            // pָ��M�еĵ�ǰ��Ԫ��
            int col = M.data[p].j;              // ��ǰָ��M����Ԫ�����
            int q = cpot[col];                  // qָ��ǰM����Ԫ��Ӧ��T�е�λ��
            T.data[q].e = M.data[p].e;
            T.data[q].i = M.data[p].j;          // ע��ת��
            T.data[q].j = M.data[p].i;
            cpot[col]++;                        // ++���ú��������ͬ��������Ԫ��Ҳ���Լ���λ��
        }
    }
}
// �����ǰ��б����ģ��ȱ�������һ����ת�ú�ͬһ���п�ǰ��Ԫ�أ�������迼��˳������



// ����ʮ������
// �洢��ʽ����Ԫ���˫������ȥ��Ԫ���⣬��������ָ�룬�ֱ�ָ����һͬ�С���һͬ��Ԫ��
typedef struct olnode{
    int i, j;
    int e;
    struct olnode *right;       //ָ���ұߵ�Ԫ��
    struct olnode *down;        //ָ�������Ԫ��
} OLNode, *OLink;               //��Ԫ����

typedef struct{
    OLink *rhead;       //��ͷ��㣬������һƬ�������ά����a[m][n]�е�a[m]ͬԭ��
    OLink *chead;       //��ͷ��㣬ע����ߵ�*��������ͷ�������
    int mu, nu, tu;
} CrossList;            //ʮ����������


// ʮ������Ĵ����㷨
void CreatCrossList(CrossList &M){
    int m, n, t, i, j, e;
    OLink p, q;
    printf("������������������������Ԫ����\n");
    scanf("%d %d %d", &m, &n, &t);
    M.mu = m;
    M.nu = n;
    M.tu = t;
    //Ϊ������������ͷָ�����ռ�
    if(!(M.rhead = (OLink *)malloc(sizeof(OLink) * (m))))
        exit(OVERFLOW);
    if(!(M.chead = (OLink *)malloc(sizeof(OLink) * (n))))
        exit(OVERFLOW);
    //��ʼ����������ͷָ��
    for (i = 0; i < m; i++)
        M.rhead[i] = NULL;
    for (i = 0; i < n; i++)
        M.chead[i] = NULL;
    scanf("%d %d %d", &i, &j, &e);      //����������������Ԫ
    while(i!=-1){                       //����iΪ-1ʱ����
        if(!(p = (OLink)malloc(sizeof(OLNode))))
            exit(OVERFLOW);
        p->e = e;
        p->i = i;
        p->j = j;

        //�������������(�ȵ�����)
        if(M.rhead[i]==NULL || M.rhead[i]->j>j){           //�����գ�ֱ�Ӳ���; �ȵ�һ��С�����ڵ�һ��ǰ��
            // M.rhead[i] = p;                  //����д��һ����������䣬���ǿ�������ĺϲ�������
            // p->right = NULL;
            p->right = M.rhead[i];
            M.rhead[i] = p;
        }
        else{               //Ѱ�������еĲ���λ��
            for (q = M.rhead[i]; q->right && q->right->j < j; q=q->right);      //ע���м��д��
            p->right = q->right;
            q->right = p;
        }

        //�������������(�ȵ�����)
        if(M.chead[j]==NULL || M.chead[j]->i>i){    //ͬ�ϣ��������
            p->down = M.chead[j];
            M.chead[j] = p;
        } 
        else{           //�����в����λ��
            for (q = M.chead[j]; q->down && q->down->i < i; q=q->down);         //ͬ�ϣ�ע���м�д��
            p->down = q->down;
            q->down = p;
        }

        scanf("%d %d %d", &i, &j, &e);      //�ٴζ��룬Ϊ��һ��ѭ��׼��
    }        
}
