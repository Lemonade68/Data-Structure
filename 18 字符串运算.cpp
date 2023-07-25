//�ַ����Ļ������㣬�ִ������ִ��淽����
// 1.�̶���С������
// 2.��̬����


//ע�⣺free�����ͷŵ���֮ǰmalloc���ģ������ͷſ�ָ��
//ע�⣺realloc����Ҳ��֮ǰ��̬������ģ����reallocǰ����free

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define OVERFLOW -2

//����˳��洢��ʾ��            
//       -----------ע�����ʱ�Խ�����'\0'����ӣ�����------------
#define MAXSIZE 255                             //����255�ڶ�����󴮳�
typedef unsigned char SString[MAXSIZE + 1];     //  SString a�൱��unsigned char a[maxsize+1];
                                                //  ��һλ��'\0'

//��̬�����ʾ��
//  -----------ע�����ʱ��ch�Ͷ�length��Ҫ�����޸� || ������'\0'ҲҪ��ӣ���--------------
typedef struct HString{
    char *ch;           //���Ƿǿմ����򰴴�������洢��������chΪNULL
    int length;         //������
} HString;
//����ַ���ʱע����  ����.ch   ���������ƣ�
//ÿ��ʹ��ǰһ��Ҫinit����Ȼfree�ᱨ��


//HString��ʼ������     �����ͱ������
void InitString(HString &s){
    s.ch = NULL;
    s.length = 0;
}

// 1.�󴮳��� if������ --> ������ĳ���
int SStrLength(SString s){
    int len = 0;
    for (len; s[len]; len++);           //�󳤶�
    return len;                         //��ʱ����s[0]������        
}

int HStrLength(HString s){      //�Ǳ�Ҫ  ֱ��s.length����
    return s.length;
}


// 2.����ֵ�� ��s2��ֵ����s1��s1ԭ����ֵ������------��s2����������ֵ----s2������������

//  ����SString: ���Ǵ��������
void SStrAssign(SString &s1, SString s2){
    int len = SStrLength(s2);
    for (int i = 0; i < len; i++){
        s1[i] = s2[i];
    }
    s1[len] = '\0';     //�����ַ���������
}

//  ����HString: ���Ǵ���ֵ���
void HStrAssign(HString &s1, const char *s){                //���дconst��ʾ�ַ�������
    if(s1.ch)
        free(s1.ch);            //�ͷžɿռ�
    int len = 0;
    for (len; s[len];len++);    //���s�ĳ���
    if(!(s1.ch=(char*)malloc(sizeof(char)*(len+1))))    //�������ɶ�Ӧ�ռ�-------ע��len+1  ��'\0'Ԥ��λ��-------
        exit(OVERFLOW);
    for (int i = 0; i < len; i++)
        s1.ch[i] = s[i];
    s1.ch[len] = '\0';          //��һ�������٣���������
    s1.length = len;            //�����Ǵ�ű仯���s1�ĳ���
}


// 3.�����ӣ� ��s1��s2���ӵ�s
void SStrConcat(SString s1, SString s2, SString &s){        //ע�ⲻ�ܷ������飬Ҫ�����׵�ַ
    int len1 = SStrLength(s1);
    int len2 = SStrLength(s2);
    int i = 0, j = 0;

    //�Ƚ�s1�е��ȸ�ֵ��s
    while(i < len1){
        s[i] = s1[i];
        i++;
    }
    //���1�����ߺϲ��󳤶�δ��
    if(len1 + len2 <= MAXSIZE){
        while(j < len2){
            s[i + j] = s2[j];
            j++;
        }
    }
    //���2��s1����δ����s1+s2���ȳ�
    else if(len1 < MAXSIZE){
        while(j < MAXSIZE - len1){
            s[i + j] = s2[j];
            j++;
        }
    }
    //���3��s1���ȳ�  ������д

    s[i + j] = '\0';        //���ֵ�ַ�����ֹ�� (�±�Ϊs1¼�볤��+s2¼�볤��-1+1)
}

void HStrConcat(HString s1, HString s2, HString &s){
    if(s.ch)
        free(s.ch);         //����ɿռ�
    int len = s1.length + s2.length;
    if(!(s.ch = (char*)malloc(sizeof(char)*(len+1))))       //len+1��'\0'Ԥ���ռ�
        exit(OVERFLOW);
    int i = 0, j = 0;
    for (i; i < s1.length; i++)
        s.ch[i] = s1.ch[i];
    for (j; j < s2.length; j++)
        s.ch[s1.length + j] = s2.ch[j];
    s.ch[s1.length + s2.length] = '\0';     //��һ�������٣�������
    s.length = len;                         //  �����Ǳ��泤��
}


// 4.���Ӵ��� ���شӴ�s�ĵ�i���ַ���ʼ�ĳ���Ϊlen���Ӵ�----������i����len=0���ؿմ�
void SubSStr(SString &sub, SString s, int i, int len){
    if (i <= 0 || i > SStrLength(s) || len < 0 || len > SStrLength(s) - i + 1){
        sub[0] = '\0';              //���ؿմ�
        return;
    }
    int j = 0;
    i--;                            //��0�±꿪ʼ
    while(j < len)
        sub[j++] = s[i++];
    sub[j] = '\0';
}

void SubHStr(HString &sub, HString s, int i, int len){
    if (i <= 0 || i > s.length || len < 0 || len > s.length - i + 1){
        sub.ch = NULL;
        sub.length = 0;
        return;
    }
    if(sub.ch)
        free(sub.ch);           //ɾ���ɿռ�
    if(!(sub.ch=(char*)malloc(sizeof(char)*(len+1))))       //len+1 �� '\0'Ԥ���ռ�
        exit(OVERFLOW);
    int j = 0;
    i--;
    while(j<len)
        sub.ch[j++] = s.ch[i++];
    sub.ch[len] = '\0';         //�ⲽ�����٣�������
    sub.length = len;           //�����Ǳ��泤��
}


// 5.���Ƚϣ� ��s1 = s2������0����s1 < s2������һ������������s1 > s2������һ��������
int SStrCmp(SString s1, SString s2){
    int i = 0;
    while(s1[i] && s2[i]){
        if(s1[i] - s2[i] > 0){
            return 1;
        }
        else if(s1[i] - s2[i] < 0){
            return -1;
        }
        else{
            i++;
        }
    }
    if(s1[i])           // s1��δ����������s2����
        return 1;
    else if(s2[i])      // ��֮
        return -1;
    else                // ͬʱ��������
        return 0;
}

int HStrCmp(HString s1, HString s2){
    int i = 0;
    while(s1.ch[i] && s2.ch[i]){
        if (s1.ch[i] - s2.ch[i] > 0)
            return 1;
        else if(s1.ch[i]-s2.ch[i]<0)
            return -1;
        else
            i++;
    }
    if(s1.ch[i])
        return 1;
    else if(s2.ch[i])
        return -1;
    else
        return 0;
}


// 6.�Ӵ���λ��ģʽƥ�䣩�� ��t��S�����������t��s���״γ��ֵ�λ�ã����򷵻�-1

//  �����ҵ�λ�ö��ǰ���0��ʼ�����
//  �㷨1�����ò����Ӵ���αȽ�
int SStrIndex(SString s, SString t){
    int s_len = SStrLength(s);
    int t_len = SStrLength(t);
    SString sub;
    int i = 0;
    for (i; i < s_len - t_len + 1; i++){
        SubSStr(sub, s, i + 1, t_len);          // �±�Ϊi��ʾ��i+1��Ԫ��    
        if(SStrCmp(sub,t) == 0)
            return i;
    }
    return -1;
}

//  �㷨2��BF�㷨 
int SStrIndex_BF(SString s, SString t){
    int s_len = SStrLength(s);
    int t_len = SStrLength(t);
    int i = 0, j = 0;
    while(s[i] && t[j]){
        if(s[i] == t[j]){
            i++;
            j++;
        }
        else{                   // i���л���
            i = i - j + 1;      // i���˶��� j�ͼ��˶��٣������+1ָ����һ��λ��
            j = 0;              // jֵ����Ϊ0
        }
    }
    if(!t[j])
        return i - j;
    return -1;
}

//  �㷨3��KMP�㷨
int SStrIndex_KMP(SString s, SString t){
    
    //�ȶ�t����next����ļ���
    int next[MAXSIZE] = {0};        // s��next���飬ע���±��1��ʼ
    int i = 1, j = 0;
    while(t[i]){
        if(j == 0 || t[i] == t[j])
            next[++i] = ++j;
        else
            j = next[j];
    }
    // next�����������

    i = 0, j = 0;   //�Ƚ�������ģʽ��
    while(s[i] && t[j]){
        if(j==0 || s[i] == t[j]){
            i++;
            j++;
        }
        else
            j = next[j];            // j=0��������������else��
    }
    if(!t[j])
        return i - j;
    return -1;
}

int HStrIndex_KMP(HString s, HString t){
    //����ģʽ��t��next����
    int *next = (int *)malloc(sizeof(int) * (t.length+1));      //��̬����һ�����飬��һλ�ճ���length+1
    int i = 1, j = 0;
    next[i] = 0;                                //�ǵð�next[1]��Ϊ��ֵ0
    while(t.ch[i] && t.ch[j]){
        if(j==0 || t.ch[i] == t.ch[j])
            next[++i] = ++j;
        else
            j = next[j];
    }

    i = 0, j = 0;
    while(s.ch[i] && t.ch[j]){
        if(j == 0 || s.ch[i] == t.ch[j]){       //�����߻�ĺ���
            i++;
            j++;
        }
        else
            j = next[j];
    }
    free(next);         //�ͷſռ�
    if(!t.ch[j])
        return i - j;
    return -1;
}


// 7.�����룺 ����t���뵽��s�ĵ�i���ַ�λ���ϣ�s�Ĵ�ֵ�����ı�
void SStrInsert(SString &s, int i, SString t){
    int s_len = SStrLength(s);
    int t_len = SStrLength(t);

    //�жϲ�����Ƿ񳬳���Χ��������ֻ���t��һ����
    if(s_len + t_len >MAXSIZE)
        t_len = MAXSIZE - s_len;

    for (int k = s_len - 1; k >= i - 1; k--)        //ע��Ҫ�Ӻ���ǰ��  ��Ȼ�������
        s[k + t_len] = s[k];

    for (int j = 0; j < t_len; j++)
        s[j + i - 1] = t[j];                        //�ӵ�i-1�±꿪ʼ����

    s[s_len + t_len] = '\0';                        //�����ӽ�����
}

void HStrInsert(HString &s, int i, HString t){
    // if(s.ch)
    //     free(s.ch);         //�ͷžɿռ�
    int len = s.length + t.length;
    char *ch = (char *)realloc(s.ch, sizeof(char) * (len + 1));     //�����������һƬ�ռ䣬���治��free����
    if(!ch)
        exit(OVERFLOW);
    s.ch = ch;
    // if(!((char*)ch=(char*)realloc(s.ch, sizeof(char)*(len+1)))) //ע����realloc   len+1---'\0'
        // exit(OVERFLOW);
    for (int j = s.length - 1; j >= i - 1; j--)
        s.ch[j + t.length] = s.ch[j]; //�Ӻ���ǰ��ֵ
    for (int k = 0; k < t.length; k++)
        s.ch[i - 1 + k] = t.ch[k];
    s.ch[len] = '\0';                               //������������
    s.length = len;                                 //�����˱��泤��
}


// 8.��ɾ���� ɾ����s�дӵ�i���ַ���ʼ�ĳ���Ϊlen���Ӵ���s�Ĵ�ֵ�ı�
void SStrDelete(SString &s, int i, int len){
    int j = 0;
    int s_len = SStrLength(s);
    for (j; j < s_len - len - i + 1; j++)                   //������෴����ǰ�������
        s[i - 1 + j] = s [i - 1 + j + len];
    s[s_len - len] = '\0';
}

void HStrDelete(HString &s, int i, int len){
    //����������ѵĴ�С���ı�
    int j = 0;
    for (j; j < s.length - i + 1 - len; j++)
        s.ch[i - 1 + j] = s.ch[i - 1 + j + len];
    s.ch[s.length - len] = '\0';
}


// 9.���滻�� �ô�r�滻s�г��ֵ������봮t��ȵĲ��ص����Ӵ���s�Ĵ�ֵ�ı�  (r��t�ĳ��Ȳ�һ����ͬ)
void SStrRep(SString &s, SString t, SString r){
    int pos = SStrIndex_KMP(s, t);
    while(pos != -1){           //����t�Ӵ�
        SStrDelete(s, pos + 1, SStrLength(t));      //��ɾ����ע���� pos + 1
        SStrInsert(s, pos + 1, r);                  //�ٲ���
        pos = SStrIndex_KMP(s, t);                  //�ٴμ��
    }
    //���������Ѿ�����������ˣ���������ӽ�����
}

void HStrRep(HString &s, HString t, HString r){
    int pos = HStrIndex_KMP(s, t);
    while(pos != -1){
        HStrDelete(s, pos + 1, t.length);           //ͬ��ע����pos + 1
        HStrInsert(s, pos + 1, r);
        pos = HStrIndex_KMP(s, t);
    }
    //ͬ�������ɾ���������Ѿ���s.length��'\0'�����˴������������ٴδ���
}


int main(){
    // ����˳��洢
    printf("\n-------------����˳��洢��ʾ-------------\n");

    SString ss1 = "abcd";
    printf("��1���ַ���Ϊ%s, ����: %d\n", ss1, SStrLength(ss1));

    SString ss2 = "abcde";
    SString ss3 = "abCde";
    printf("��2���ַ���Ϊ%s, ����: %d\n", ss2, SStrLength(ss2));
    printf("��3���ַ���Ϊ%s, ����: %d\n", ss3, SStrLength(ss3));
    
    SStrAssign(ss2, ss3);
    printf("���ַ���3�����ַ���2�� �ַ���2��Ϊ: %s\n", ss2);

    SString ss;
    SStrConcat(ss1, ss2, ss);
    printf("�ϲ�1 2���ַ���: %s\n", ss);

    SString ssub;
    SubSStr(ssub, ss, 2, 3);
    if(SStrLength(ssub))
        printf("��2���ַ���ʼȡ3λ���Ӵ�Ϊ: %s\n", ssub);

    int result = SStrCmp(ss1, ss2);
    printf("%s��%s�ıȽϽ��Ϊ: %d\n", ss1, ss2, result);

    SString t = "abC";
    // int i = SStrIndex(ss, t);
    // int i = SStrIndex_BF(ss, t);
    int i = SStrIndex_KMP(ss, t);
    printf("�׸� %s �Ӵ����ַ�λ��Ϊ: %d\n", t, i);

    SStrInsert(ss,2,t);
    printf("���� %s �Ӵ�����2��λ���Ϻ��ַ�����Ϊ: %s\n", t, ss);

    SStrDelete(ss, 2, 3);
    printf("ɾ����2��λ�ÿ�ʼ��3���ַ����ַ�����Ϊ: %s\n", ss);

    SString s1 = "ab";
    SString s2 = "ABC";
    SStrRep(ss, s1, s2);
    printf("��%s�滻Ϊ%s���ַ�����Ϊ: %s\n", s1, s2, ss);

    // �ѷ���洢
    printf("\n-------------�ѷ���洢��ʾ-------------\n");
    HString hs1, hs2, hs;
    InitString(hs1);
    InitString(hs2);
    InitString(hs);

    HStrAssign(hs1, "abcd");
    printf("��1���ַ���Ϊ%s, ����: %d\n", hs1.ch, hs1.length);
    HStrAssign(hs2, "abCde");
    printf("��2���ַ���Ϊ%s, ����: %d\n", hs2.ch, hs2.length);

    HStrConcat(hs1, hs2, hs);
    printf("�ϲ�1 2���ַ���: %s, ����Ϊ: %d\n", hs.ch, hs.length);
    //����и�����-----------ż���������-------->��������Ҫ����'\0'����

    HString hsub;
    InitString(hsub);                       //һ��Ҫinit
    SubHStr(hsub, hs, 2, 3);
    if(HStrLength(hsub))
        printf("��2���ַ���ʼȡ3λ���Ӵ�Ϊ: %s\n", hsub.ch);

    printf("%s��%s�ıȽϽ��Ϊ: %d\n", hs1.ch, hs2.ch, HStrCmp(hs1, hs2));

    HString ht;
    InitString(ht);                         //һ��Ҫinit����Ȼfree�ᱨ��
    HStrAssign(ht, "abC");                  //����ֱ�Ӹ�ֵ
    printf("�׸� %s �Ӵ����ַ�λ��Ϊ: %d\n", ht.ch, HStrIndex_KMP(hs, ht));

    HStrInsert(hs,2,ht);
    printf("���� %s �Ӵ�����2��λ���Ϻ��ַ�����Ϊ: %s\n", ht.ch, hs.ch);

    HStrDelete(hs, 2, 3);
    printf("ɾ����2��λ�ÿ�ʼ��3���ַ����ַ�����Ϊ: %s\n", hs.ch);

    HString hhs1, hhs2;
    InitString(hhs1);           //Ҫ�ı���Ӵ�
    InitString(hhs2);           //�ı����Ӵ�
    HStrAssign(hhs1, "ab");
    HStrAssign(hhs2, "ABC");
    HStrRep(hs, hhs1, hhs2);
    printf("��%s�滻Ϊ%s���ַ�����Ϊ: %s\n", hhs1.ch, hhs2.ch, hs.ch);

    printf("\n");
    return 0;
}
