#define status int
#define OK 1
#define FALSE 0
#define OVERFLOW -2
#include<stdlib.h>
#include<stdio.h>

typedef struct BiTree{
    int data;
    struct BiTree *lchild;
    struct BiTree *rchild;
} BiTNode, *BiTree;

// ����������Ϊ��Ҫ�ľ��������շ���

// 1.��ѯ������ĳ��㲢��p����       --���������������
status PreOrder(BiTree T, int x, BiTree &p){
    if(T){                          //Ϊ�ռ�Ϊ��������
        if(T->data==x){             //��㱾����ǣ����ҵ��ý��
            p = T;
            return OK;              //��⣺�����ok��������ϴ��ݵ�
        }
        else{
            if(PreOrder(T->lchild,x,p))
                return OK;
            else
                return (PreOrder(T->rchild, x, p));
        }
    }
    else
        return FALSE;               //��Ҷ�ӽ��Ļ����� ��˫�׾�Ϊ�գ�˵����һ·��û�ҵ� ����false
}
//  ����Ҫ��������˼����Ϊʲô��ֱ�ӷ��ؽ�㣿   --��Ϊ���غ�ص��Ĳ�����������������һ���ݹ麯��


// 2.ͳ�ƶ�������Ҷ�ӽ�����(���н�����)
// ��1��ʹ�ü�����
void CountLeaf(BiTree T, int &count){
    if(T){
        if((!T->lchild)&&(!T->rchild))
            count++;
        CountLeaf(T->lchild, count);
        CountLeaf(T->rchild, count);
    }
}

// ��2��ע����������⣡��
int countleaf(BiTree T){
    if(!T)                      //�ս�����
        return 0;

    if(!T->lchild && !T->rchild)
        return 1;
    else{
        int m = countleaf(T->lchild);
        int n = countleaf(T->rchild);
        return (n + m);
    }
}

// ��2��չ��ͳ�ƶ����������н�����
int Count(BiTree T){
    if(!T)
        return 0;
    else{
        int m = Count(T->lchild);
        int n = Count(T->rchild);
        return (m + n + 1);
    }
}


// 3.������������   --ÿ����㷵����������������ֵ+1
int Depth(BiTree T){
    int depth;
    if(!T)
        depth = 0;
    else{
        int depth_left = Depth(T->lchild);
        int depth_right = Depth(T->rchild);
        depth = 1 + (depth_left > depth_right ? depth_left : depth_right);
    }
    return depth;
}


// ��һ��д����
void depth(BiTree T, int level, int &dval){
    if(T){
        if(level>dval)
            dval = level;
        depth(T->lchild, level + 1, dval);
        depth(T->rchild, level + 1, dval);
    }
}
// ����ǰlevel��ֵΪ1��dval��ֵΪ0


// 4.���ƶ�����
BiTNode* GetTreeNode(int item, BiTNode *lptr, BiTNode *rptr){
    //������item    ��ָ����lptr    ��ָ����rptr
    BiTree T;
    if(!(T = (BiTree)malloc(sizeof(BiTNode))))      //�����������´���һ��BiTree T = ....   �ᱨ��
        exit(OVERFLOW);
    T->data = item;
    T->lchild = lptr;
    T->rchild = rptr;
    return T;
}

BiTNode *CopyTree(BiTNode *T){
    if(!T)
        return NULL;
    BiTree newlptr, newrptr, newTree;
    // �������ݹ鸴��
    if(T->lchild)
        newlptr = CopyTree(T->lchild);
    else
        newlptr = NULL;
    // �������ݹ鸴��
    if(T->rchild)
        newrptr = CopyTree(T->rchild);
    else
        newrptr = NULL;
    newTree = GetTreeNode(T->data, newlptr, newrptr);
    return newTree;
}


// 5.����������
// ���ַ�������ʽ���� ������ ��������û�о���" "
void CreateBiTree(BiTree &T){
    char ch;                  //�����ַ������ַ�
    scanf(&ch);
    if(ch == ' ')
        T = NULL;
    else{
        if(!(T=(BiTree)malloc(sizeof(BiTNode))))
            exit(OVERFLOW);
        T->data = ch;                   //���dataҪ�ĳ�ch����
        CreateBiTree(T->lchild);        //����������
        CreateBiTree(T->rchild);        //����������
    }
}


// �������ı��ʽ������Ӧ������

//������������



//��ǰ����������й��������

//�����������в��Ҹ��ڵ�ĺ���
int Search(char *ino, char c){
    int i = 0;
    while(ino[i]){
        if(ino[i] == c)
            return i;
        else
            i++;
    }
    return -1;
}


void CrtBT(BiTree &T, char pre[], char ino[], int ps, int is, int n){
    // pre[ps...ps+n-1]Ϊ���������������У������Ҹ����
    // ino[is...is+n-1]Ϊ���������������У����ڹ������ڵ��Ӧ����������
    // ps�������ý��ʱ����������ַ����ĵ�һλ
    // is�������ý��ʱ����������ַ����ĵ�һλ
    // n��ʾ�ý�㴫��������ַ����ĳ���(���)
    if(n == 0)
        T = NULL;
    else{
        int k = Search(ino, pre[ps]);   //���������в��Ҹ��ڵ������������е�λ��
        if(k == -1)
            T = NULL;                   //�������в���Ӧ����������
        else{
            if(!(T=(BiTree)malloc(sizeof(BiTNode))))
                exit(OVERFLOW);
            T->data = pre[ps];          
            //����������
            if(k == is)     //��������������
                T->lchild = NULL;
            else
                CrtBT(T->lchild, pre, ino, ps + 1, is, k - is); // ps+1: �����ȸ����ȶ����ľ��Ǹ�
            //����������
            if(k == is + n - 1)     //������������ұ�
                T->rchild = NULL;
            else{
                CrtBT(T->rchild, pre, ino, ps + 1 + (k - is), k + 1, n - (k - is) - 1);

            // --------------------------���ɣ���ס�������ĳ���Ϊk-is��ʣ�µĶ�������Ƶ�--------------------------
            // ��Ϊ��k��is����������������ж��Եģ������������
            }
        }
            
    }
}




// 6.����������ϴӸ�������Ҷ�ӽ���·��       �ǳ�����
void AllPath(BiTree T, Stack &S){
    if(T){
        Push(S, T->data);
        if(!T->lchild && !T->rchild)
            PrintStack(S);
        else{
            AllPath(T->lchild, S);
            AllPath(T->rchild, S);      //�����������ֺ��ʾ�����ý�������·���Ѿ�����ӡ
        }                               //���ֱ��pop������һ��·
        Pop(S);                         //ÿ�����ʹ�����Ҫ��ʱ��ջ
    }
}



