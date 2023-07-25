#define MAXSIZE 20  

typedef struct {
    int key;
    int otherinfo;
} RedType;

typedef struct SqList{
    RedType r[MAXSIZE + 1];     //r[0]���û������ڱ���Ԫ      һ��Ҫע���������
    int length;                 //˳�����
} SqList;



// 1. ð������
int length;
int L[10];

// ֮ǰѧ��ð�ݣ�
void BubbleSort(){
    for (int i = 0; i < length - 1; ++i){                   // ѭ������������-1  ��
        for (int j = 0; j < length - i - 1; ++j){           // �����е� ������i+2λ
            if(L[j + 1] < L[j]){
                int temp = L[j];
                L[j] = L[j + 1];
                L[j + 1] = temp;
            }
        }
    }
}


// ��һ���ð�ݣ�
void swap(int &a, int &b){
    // ����
}

void BubbleSort_adv(int *r, int n){             //�Ľ��棬ÿ����iֱ�ӵ������һ���������λ�ã� �����ٽ���һЩ����������
    int i = n, lastExchange_index = 1;
    while (i > 1){
        lastExchange_index = 1;
        for (int j = 1; j < i; j++){
            if (r[j + 1] < r[j]){
                swap(r[j], r[j + 1]);
                lastExchange_index = j;         //��¼�½��н����ļ�¼λ��
            }
            i = lastExchange_index;
        }
    }
}


// ʱ�临�Ӷ�Ҳ��O(n^2)

// 2. ��������

// һ�ο��ţ���һ�λ���
// �����㷨��
int Partition(SqList  &L, int low, int high){
    L.r[0] = L.r[low];                      // �ӱ�ĵ�һ����¼�������¼
    int pivotkey = L.r[low].key;            // �����¼�ؼ���
    while(low < high){
        while(low < high && L.r[high].key >= pivotkey)
            --high;
        L.r[low] = L.r[high];
        
        while(low < high && L.r[low].key <= pivotkey)
            ++low;
        L.r[high] = L.r[low];
    }
    L.r[low] = L.r[0];                      // high = lowʱ
    return low;                             // ��������λ��
}


// �����㷨��ÿ�λ��ֺ�õ�һ������Ԫ�ص���ȷλ�ã�Ȼ��ֳ����������ֽ��Ż���
void QSort(SqList &L, int low, int high){
    //��˳��������� L.r[low ... high]����������
    if(low < high){
        int Pivotloc = Partition(L, low, high);     //�� L.r[low ... high]һ��Ϊ��
        QSort(L, low, Pivotloc - 1);
        QSort(L, Pivotloc + 1, high);
    }
}

void QuickSort(SqList &L){
    QSort(L, 1, L.length);
}

// ���ۣ����ŵ�ʱ�临�Ӷ�ΪO(nlogn)

// ȱ�ݣ�
// 1.��һ��ʼ���м�Ϊ������ô���ŵ�ʱ�临�Ӷ��˻�ΪO(n^2)
// 2.���ȶ������򷽷�