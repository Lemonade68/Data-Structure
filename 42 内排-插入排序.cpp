// ֱ�Ӳ���Ƚϴ�������*****************************




#define MAXSIZE 20  

typedef struct {
    int key;
    int otherinfo;
} RedType;

typedef struct SqList{
    RedType r[MAXSIZE + 1];     //r[0]���û������ڱ���Ԫ
    int length;                 //˳�����
} SqList;


// ����˼·�� ��R[1,2,...,i-1]�в���R[i]�Ĳ���λ��j
// ��R[j+1...i-1]�����м�¼����һλ��R[i]���뵽R[j+1]��λ����

// 1. ֱ�Ӳ���

// ע�⣺�ӵڶ�λ�Ƚ����ǵ�һ�ˣ�
void InsertSort(SqList &L){
    int j;
    for (int i = 2; i <= L.length; ++i){
        if(L.r[i].key < L.r[i - 1].key){        //�Թؼ��ֽ��бȽ�
            L.r[0] = L.r[i];                    //����Ϊ�ڱ�
            //�Ӻ���ǰ�Ƚ�
            L.r[i] = L.r[i - 1];                //�����ú����ٱȽ�һ��
            for (j = i - 2; L.r[j].key > L.r[0].key; --j)       //˼����������һֱ�ȵ�r[0]�����      ��ߵ�>����ȡ��=   ��������
                L.r[j + 1] = L.r[j];
            L.r[j + 1] = L.r[0];                //������ȷλ��
        }
    }
}

// ʱ�临�Ӷ�ΪO(n^2)


// ע��Ƚϴ���������   �Ƚ����ҵ��ǵ�һ��С�ڵ����ڱ���λ�ã�Ȼ���ڸ�λ�õ���һλ����
// �����1λ����i-1λ�Ķ������ڱ�����ô��Ҫ���ڱ����бȽϣ�������




// 2. �۰����
// ��ΪR[1]...R[i-1]�ǰ��ؼ�����������У��������۰�����ҵ�λ�ú����
void BInsertSort(SqList &L){
    for (int i = 2; i <= L.length; ++i){
        L.r[0] = L.r[i];                        //�ݴ�Ϊ�ڱ�
        int low = 1, high = i - 1, mid;
        while(low <= high){                     //ѭ��ֱ��low > high�� ��low = high + 1Ϊֹ
            mid = (high + low) / 2;
            if(L.r[0].key < L.r[mid].key)
                high = mid - 1;
            else
                low = mid + 1;
        }
        //  *************    ��� high + 1 = low ��λ�þ���Ӧ�ò����λ��   ***********
        for (int j = i - 1; j >= high + 1; ++j)             //������ low 
            L.r[j + 1] = L.r[j];
        L.r[high + 1] = L.r[0];             //������ low 
    }
}


// 3. �����

// ?  ֮�󲹳�



// 4. ϣ������
// �Ⱥ��������΢������  ����d   ÿ����������дӴ�С�ݼ�������Ϊ1��  ����Ϊdʱ���ֳ�d��

void ShellInsert(SqList &L, int dk){
    // ��L��һ��ϣ��������˳�������ȣ������������޸ģ�
    // 1. ǰ���¼λ�õ�������dk, ������1
    // 2. r[0]ֻ���ݴ浥Ԫ�������ڱ���   �� j <= 0 ʱ������λ�����ҵ�
    int i, j;
    for (i = dk + 1; i <= L.length; ++i){               //��ͬ��֮��ͬʱ���У�����
        if(L.r[i].key < L.r[i-dk].key){
            L.r[0] = L.r[i];                            //�ݴ�
            for (j = i - dk; j > 0 && L.r[0].key < L.r[j].key; j -= dk)     //ע����ߵ� j>0    ������������ǰ��
                L.r[j + dk] = L.r[j];
            L.r[j + dk] = L.r[0];
        }
    }
}

void ShellSort(SqList &L, int dlta[], int t){       // dlta��������һλһ����1
    // ��������dlta[0, ... ,t - 1]��˳������ϣ������
    for (int k = 0; k < t; ++k)
        ShellInsert(L, dlta[k]);                    // һ������Ϊdlta[k]�Ĳ�������
}

// �Ƚ����ƶ������ɴ�n��1.3�η�
// ϣ������Ŀռ临�Ӷ�ΪO(1)�� �ǲ��ȶ������򷽷�

