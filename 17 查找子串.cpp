//BF�㷨���Լ�д����
//txtΪ������patΪ�Ӵ�
char* StrStr(const char *txt, const char *pat){
    int j=0,length =0;
    for(length =0;pat[length];length++);    //ע��ѭ������ʱ�����������ı����ᱻ����
    for(int i = 0; txt[i];i++){
        int k = i;
        while(txt[i] == pat[j]){
            if(j == length - 1){
                return &txt[k];
            }
            i++;
            j++;
        }
        i = k;
        j = 0;
    }
    return NULL;
}



//��׼bf�㷨��
char* StrStr(const char* txt, const char* pat) {
    int m,n,i,j=0;
    m=n=i=j=0;
    for(;txt[m];m++);           //�õ�txt���ĳ���m
    for(;pat[n];n++);           //�õ�pat���ĳ���n
    for(;i<m&&j<n;){            //����û��ƥ�䵽�յ�ʱһֱѭ��
        if(txt[i]==pat[j]){     //ƥ�����˾Ͷ���һ����ƥ��
            i++;
            j++;
        }
        else{                  //�����i����ԭ��λ�ü�1�����¿�ʼƥ��
            i=i-j+1;            //i�ӵ���������j
            j=0;
        }
    }
    if(j==n)                    //��j==n֤����txtȫƥ���ϣ��򷵻ص�ַ
        return &(txt[i-j]);     //�±�Ϊi-jͬ��
    return NULL;
}


//����д����
int Index(SString S, SString T, int pos){
    i = pos, j = 1;
    while(i<=S[0] && j <= T[0]){
        if(S[i] == T[j]){
            ++i;
            ++j;
        }
        else{
            i = i - j + 2;      //iָ�����
            j = 1;
        }
    }
    if(j>T[0])                  //�������б��ҵ�
        return i - T[0];        //����ģʽ������ʼλ��
    return 0;
}



//kmp�㷨��
    //����ģʽ��T��next������������S�е�pos���ַ�֮���λ�õ�kmp�㷨
int Index_KMP(SString S, SString T, int pos){
    int i = pos, j = 1;                 //  iָ��������jָ��ģʽ��
    while(i<=S[0] && j <= T[0]){        //  S[0],T[0]�������S T�ĳ���
        if(j == 0 || S[i] == T[j]){     //  j=0����ȫû����ͬ����λ�ַ������
            ++i;
            ++j;
        }
        else
            j = next[j];        
    }
    if(j>T[0])                  //���������ҵ�
        return i - T[0];        //����ģʽ����ʼλ��      i�ȼ�1�ص�++ǰ��λ�� �ټ�T[0]���� �ټ�1
    return 0;
}   



//��ģʽ����next[j]�ĺ�����         �����ģʽ��������
    // next[]�±��1��ʼ��  ch[]�±��Ҳ��1��ʼ
int GetNext(char ch[], int length, int next[]){ //lengthΪch�еĳ���
    next[1] = 0;
    int i = 1, j = 0;                   //  i j����ch�е��±꣬i������next�е��±�
    while(i <= length){
        if(j==0 || ch[i] == ch[j])      //  j=0���������  next[1]  �Լ�  ��ȫû���غ��ַ���     ���Ӷ�����һλ��nextֵ��Ϊ1��
            next[++i] = ++j;            //  next[k]��ӳ���Ǵ�1��k-1λ��ǰ׺��׺�غ��ַ�����+1
        else
            j = next[j];                //  next[j]�ĺ��壺ָ��jλ��ǰ����ַ�������ַ��غϴ�����һ���ַ���
    }                                   //  �ٴ�ch[next[j]]��ch[i]�Ƚϣ�����ȣ�����next[j]��ֵ+1������������ȵ�һ������Ϊnext[++i]��ֵ
}                                       //  �����ǲ���ȣ��ٵ���


// ��������ͼʾ


//����Ľ���

// �������Ϊ���� a a a a a b

// �Ľ��㣺�������s[i]��t[j]��ƥ��������j�ص�next[j]
// Ȼ��t[j]��t[next[j]]��ͬ������s[i]��ͬ������ ���ظ�����
// ������next����ʱ�ͽ���Щ�ظ����м����ȥ��

// һ�㷽����P��ʾ�ַ�
// j=1ʱ��nextval��ֵΪ0
// Pj������Pnext[j]����nextval[j]=next[j];
// Pj����Pnext[j]����nextval[j]=nextval[next[j]];


//���next[]����ı��ʣ���s��tƥ�䵽��ͬ���ַ�ʱ��j���ݵ�next[j]

void get_nextval(SString T, int nextval []){
    i = 1;
    nextval[1] = 0;
    j = 0;
    while(i < T[0]){
        if (j == 0 || T[i] == T[j]){
            ++i;  ++j;
            if (T[i] != T[j]){          // ������������ַ�����-->����������
                nextval[i] = j
            } else{                     
// �������i jָ������ַ���ȣ���ônext[i]ֱ�ӵ���next[j]������next[j]��λ��
                nextval[i] = nextval[j]
            }
        }else{
            j = nextval[j];
        }
    }
}
 