#define MAXSIZE 20  
#define pass 1

typedef struct {
    int key;
    int otherinfo;
} RedType;

typedef struct SqList{
    RedType r[MAXSIZE + 1];     // r[0]���û������ڱ���Ԫ      һ��Ҫע���������
    int length;                 // ˳�����
} SqList;

// ˼�룺������λ�����ڵļ�¼���������й鲢Ϊһ����¼����������


// �ǵݹ���ʽ��
void Merge(RedType SR[], RedType *TR, int i, int m,int n){
    //�������SR[i ... m]��SR[m+1 ... n]�鲢Ϊ�����TR[i ... n]
    int j, k;
    for (j = m + 1, k = i; i <= m && j <= n; ++k){          //SR�м�¼��С������TR
        if(SR[i].key <= SR[j].key)
            TR[k] = SR[i++];
        else
            TR[k] = SR[j++];
    }
    if (i <= m)
        pass;
        // TR[k... n] = SR[i... m];   ʣ�µ�ȫ����TR
    if (j <= n)
        pass;
        // TR[k... n] = SR[j... n];   ͬ��
}

// һ�������Ĺ鲢���򣺵���log2n�����ֲ�����ֱ�����ֻʣ��һ����������Ϊֹ

// ��·�鲢���ȶ���  ����Ҫ�����ռ�



// �ݹ���ʽ���ô�����    ���������