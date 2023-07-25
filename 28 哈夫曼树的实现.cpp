// ���Ĵ�Ȩ·�����ȣ�Ȩֵ*·������
// ��С�ģ����Ŷ�����/��������

// �������Ŷ�������  �������㷨��
// ��һ��Ȩֵ�е���С�����ϳ�һ����������Żأ����ߵĺ���Ϊ�µ�Ȩֵ���ظ�����

// -----------------------ע�⣡����  ����ʱĬ��С���� ������-----------------
// ���룺
// �ȳ��룺����˳����Σ��ܳ�����Զ���
// ���ȳ��룺���ִ�������ַ�����̣������ٵ��ַ����볤
            //���⣺���ײ�������
// �Ľ���ǰ׺����----�κ�һ���ַ��ı��붼������һ���ַ������ǰ׺
// ������������һ�����ŵ�ǰ׺���룬�������������ܳ������

// ����д������Ȩֵ��������������Ȼ������0��1��ÿ��·�����롣�Ӹ���Ҷ�ӵ�·���ı�����ϼ�Ϊ��Ҷ����Ȩֵ�Ĺ���������

#include<stdlib.h>
#include<stdio.h> 
#include<string.h>  
#define OVERFLOW -2

typedef struct{
    char ch;
    int weight;
    unsigned int parent, lchild, rchild;
} HTNode, *Huffmantree;         //��̬��������洢��������

typedef char **HuffmanCode;     //��̬��������洢�����������

// ˼�룺�����������Ƚϣ�����ʼ����Сֵ�ʹ�Сֵ��Ȼ��ʣ�µ��������Ƚ�
void Select(Huffmantree &T, int n, int &s1, int &s2){
    // int i = 2, min1 = T[1].weight, min2 = T[1].weight;               //�����⣡
    int i, min1 = 0, min2 = 0;
    for (i = 1; i <= n; ++i){
        if(T[i].parent == 0){
            if(min1 == 0)                               //�ҵ���һ��parentΪ0��i��ֵ��������������Сֵ
                min1 = i;                               //���һ��ʼ���ܸ�min1=min2=i����Ȼ���һ��ʼ�ľ�����С�ģ���󷵻ص������ͻ����
            else if(min1 != 0 && min2 == 0){            //��ʼ��ǰ����
                if(T[i].weight >= T[min1].weight)
                    min2 = i;
                else{
                    min2=min1;
                    min1 = i;
                }
            }
            else{
                if(T[i].weight <= T[min1].weight){      //���Ҫ�ǵȺţ���Ϊ=min1ʱҲ��min2С
                    min2 = min1;                        //�滻
                    min1 = i;
                }
                else if(T[i].weight < T[min2].weight)
                    min2 = i;
            }
        }
    }
    s1 = min1;
    s2 = min2;
}

// CSDN�ϵ�ʵ�ַ���

// int min1(Huffmantree &t,int i){
//     int j,flag;
//     unsigned int k = UINT_MAX;
//     for (j = 1;j <= i;j++)
//         if(t[j].weight < k && t[j].parent == 0)
//             k = t[j].weight,flag = j;
//             t[flag].parent = 1;
//             return flag;
// }

// void Select(Huffmantree &t,int i,int &s1,int &s2){
//     int j;
//     s1 = min1(t,i);
//     s2 = min1(t,i);
//     if(t[s1].weight > t[s2].weight){
//         j = s1;
//         s1 = s2;
//         s2 = j;
//     }
// }

//������̣�
void HuffmanCoding(Huffmantree &HT, HuffmanCode &HC, int *w, int n, char* ch){           // w��Ȩ������
    // w���n���ַ���Ȩֵ(��>0)�������������HT,�����n���ַ��Ĺ���������HC
    if(n<=1)
        return;
    int m = 2 * n - 1;                                                  //�õ��Ŀռ䣺�����n��+����n-1�κϲ�����2n-1���ռ�
    HT = (Huffmantree)malloc(sizeof(HTNode) * (m + 1));                 //0�ŵ�Ԫδʹ�ã���1�ŵ�Ԫ��ʼʹ��
    Huffmantree p;
    int i, s1, s2, start, c, f;
    for (p = HT + 1, i = 1; i <= n; ++ch, ++i, ++p, ++w)                //һ��Ҫ�� HT+1����1��ʼʹ�ã�
        *p = {*ch, *w, 0, 0, 0};                                        //ע�����ָ�ֵ��ʽ���ṹ�����ֱ��������ֵ
    for (; i <= m; ++i, ++p)    
        *p = {'0', 0, 0, 0, 0};                                         //ʣ��ĳ�ʼ��Ϊ 0 0 0 0
    for (int i = n + 1; i <= m;i++){                                    //������������
        //��HT[1...i-1]��ѡ��parentΪ0��weightΪ��С��������㣬����ŷֱ�Ϊs1��s2
        Select(HT, i - 1, s1, s2);
        HT[s1].parent = i;
        HT[s2].parent = i;
        HT[i].lchild = s1;                                              //Ĭ�ϸ�С����Ϊ����
        HT[i].rchild = s2;                                              //Ĭ�ϴ�С����Ϊ�Һ���
        HT[i].weight = HT[s1].weight + HT[s2].weight;   
    }

    //��Ҷ�ӵ���������ÿ���ַ��Ĺ���������
    HC = (HuffmanCode)malloc((n + 1) * sizeof(char *));                 //����n���ַ������ͷָ��������HC[]�����ά������У���ʼ�±�Ҳ��1��������ǰ�����
    char *cd = (char *)malloc(sizeof(char) * n);                        //���������Ĺ����ռ䣬���n-1λ���ٶ���һλ��\0
    cd[n - 1] = '\0';                                                   //���������            ��������
    for (int i = 1; i <= n;++i){                                        //����ַ������������
        start = n - 1;                                                  //���������λ��
        for (c = i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent){   //��Ҷ�ӵ�����������룬ע��for�����ж�������ִ��    �����cΪ���ڵ㣬���ڵ��parent��0���˳�      //ѧϰfor���÷�
            if(HT[f].lchild == c)
                cd[--start] = '0';                                      //0��1���ڷ�֧�����   ע��
            else
                cd[--start] = '1';
        }
        HC[i] = (char *)malloc(sizeof(char) * (n - start));             //Ϊ��i���ַ��������ռ�
        strcpy(HC[i], &cd[start]);                                      //��cdλ�ÿ�ʼ���Ʊ��뵽HC
    }
    free(cd);
}


//������̣�
// �������Ʊ��뷭�����Ϣԭ�ģ�m���������
void Decoding(Huffmantree HT, int n, char *buff){
    int m = 2 * n - 1;                              //HT������һλҲ����������ɵ�����                
    int p = m;
    while(*buff != '\0'){                           //���ɣ�ppt�϶����һ��������p!=0    Ϊʲô����   
    //ǰ���������һ���������Ʊ���(�����������)δ����
        if((*buff) == '0')                      
            p = HT[p].lchild;                       //�������֧
        else
            p = HT[p].rchild;                       //�����ҷ�֧

        if(!HT[p].lchild && !HT[p].rchild){         //����Ҷ�ӽ��
            printf("%c", HT[p].ch);
            p = m;                                  //���´������������б���
        }
        buff++;                                     //buffָ����һ������λ
//------------------------���ֱ�Ӷ���char buff[100]�Ļ�buff++�ᱨ��-----------------------
    }
}


int main(){
    char ch[10] = {0}, buff[1000] = {0};
    int w[10] = {0};
    int n;
    printf("Ȩֵ����:");
    scanf("%d", &n);                                //������֮���س����ᱻ�����%c����
    getchar();                                      //��߻��з�һ��Ҫ�ӣ�����   ����               
    printf("�������ӦȨֵ���ַ�\n");
    for (int i = 0; i < n; ++i){    
        // scanf("%c %d\n", &ch[i], &w[i]);         //��������д!!!!   \n��scanf�����ʾһֱ����ֱ�������ǿհ׷�(�ǿո� ���з� �Ʊ����)
        scanf("%c %d", &ch[i], &w[i]);              //��߽���λ�üӸ�\n  ��ÿһ�����Ļ��з�Ҳ����
        getchar();
    }
    Huffmantree HT;
    HuffmanCode HC;
    HuffmanCoding(HT, HC, w, n, ch);
    printf("Huffman����Ϊ:\n");
    for (int i = 1; i <= n; ++i)
        printf("%c   %s\n", HT[i].ch, HC[i]);
    printf("����������룺\n����������:");
    scanf("%s", buff);
    printf("�����Ӧ������Ϊ��\n");
    Decoding(HT, n, buff);
    return 0;
}
 


// 68-84�е���һ���㷨���Ӹ�����  �������������������������
void HuffmanCoding(Huffmantree &HT, HuffmanCode &HC, unsigned int *w, int n, char* ch){           // w��Ȩ������
    //...           68����ǰ������������
    HC = (HuffmanCode)malloc((n + 1) * sizeof(char *));
    int m = 2 * n - 1;
    int p = m, cdlen = 0;
    char *cd;
    for (int i = 1; i <= m; ++i)
        HT[i].weight = 0;               //weight��Ϊ��һ�����ã�������������ʱ�������״̬��־����ʾ�ڼ��ξ����ý��
    while(p){
        if(HT[p].weight == 0){          //��һ�ξ���������-----����
            HT[p].weight = 1;           //��ʾ�Ѿ����ý��
            if(HT[p].lchild != 0){
                p = HT[p].lchild;
                cd[cdlen++] = '0';
            }
            else if(HT[p].rchild == 0){     //����Ҷ�ӽ��
                HC[p] = (char *)malloc(sizeof(char) * (cdlen + 1));
                cd[cdlen] = '\0';           //������ ע��
                strcpy(HC[p], cd);
            }
        }
        else if(HT[p].weight == 1){
            HT[p].weight = 2;
            if(HT[p].rchild != 0){
                p = HT[p].rchild;
                cd[cdlen++] = '1';
            }           
            else{                           //HT[p].weight == 2   �˻�
                HT[p].weight = 0;
                p = HT[p].parent;
                --cdlen;
            }
        }
    }
}
