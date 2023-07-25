// ��Լ�¼�������һ����ϣ�������Ӧ�Ľ���Ͳ�����
// ��1���ٶ�ÿ����¼������������绰���루���Ȳ�����11�����ִ������û��������Ȳ�����20���ַ����ַ���������ַ�����Ȳ���50���ַ����ַ�����
// ��2���������ļ�data.txt��Ԥ�Ƚ������ж�������¼������һ���뵽��ϣ���У��ֱ����Ե绰���������Ϊ�ؼ��������Ӧ�Ĺ�ϣ������
// ��3��������Ϊ�ؼ���ʱ����������ַ�������ͻ�����ϣ���Ե绰����Ϊ�ؼ���ʱ����������̽�鷨�����ͻ�����ϣ��
// ��4�������ҵļ�¼�Ӽ������룬Ӧ��ʾ���ҽ����


// ע��ṹ�帳ֵ���⣡����      ���˶���ʱ   ����ֱ����{}�����и�ֵ
// ע���ж��ַ����Ƿ�Ϊ�յ����⣡��    ����ֱ��if(!str)    ����Ҫ��strcmp�������ж�
// �漰�ַ����ıȽ϶�Ҫʹ��str___��ĺ�����


// ��ʽ��ϣ��֮����д

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define Hashsize 11     //��ϣ���ȣ��û����Զ���
#define OVERFLOW -2

// �����û���
typedef struct{
    char tele[12];
    char UserName[20];
    char Add[50];
    int tele_trans;         //���ڴ�Ž��绰�ַ���ת�����ֵ�ֵ
} User, *Userptr;

typedef struct{
    Userptr elem;
    int hashsize = Hashsize;
} HashTable_tele;

typedef struct{
    Userptr *elem;          //��������ÿ��Ԫ��Ϊuserptr��һƬ����
    int hashsize = Hashsize;
} HashTable_username;

void InitHashTable_tele(HashTable_tele &HT){
    User user[5] = {
        {"13776655469", "wyq", "Jiangsu"},
        {"13584020203", "zxy", "Jiangsu"},
        {"13337818876", "wyl", "Jiangsu"},
        {"110", "jc", "Zhongguo"},
        {"120", "Ambulance", "Zhejiang"}   };

    // ����������ֵ����������
    // user[0] = {"13776655469", "wyq", "Jiangsu"};
    // user[1] = {"13584020203", "zxy", "Jiangsu"};
    // user[2] = {"13337818876", "wyl", "Jiangsu"};
    // user[3] = {"110", "jc", "Zhongguo"};
    // user[4] = {"120", "Ambulance", "Zhejiang"};

    for (int i = 0; i < 5; i++)                                                     //���ɶ�Ӧ��tele_trans
        user[i].tele_trans = (user[i].tele[0] - '0') * 10 + user[i].tele[1] - '0';

    for (int i = 0; i < Hashsize; i++){                                             //���ǽṹ�������ʼ��Ϊ��
        strcpy(HT.elem[i].tele, "\0");
        strcpy(HT.elem[i].UserName, "\0");
        strcpy(HT.elem[i].Add, "\0");
        HT.elem[i].tele_trans = 0;
    };                             
    
    // ������ϣ��           ����ͻ������ֵ��ʱ�����ǣ�
    for (int i = 0; i < 5; i++){
        int p = user[i].tele_trans % 11;                                            //��ù�ϣֵ
        if(strcmp(HT.elem[p].tele,"\0") == 0)                                                        //��Ϊ"\0"��ѧϰ��  ���Բ���������ṹ�����Ϊ��  ����ĳ����Ա��ֵΪ��
            HT.elem[p] = user[i];                                                   //��Ϊ��   �����
        else{
            while(strcmp(HT.elem[p].tele,"\0") != 0 && strcmp(HT.elem[p].tele,user[i].tele) != 0)               //�ṹ�岻��ȱȽϵĻ���Ҫ��������� !=  ��߼�      *****ע����strcmp�п�*****
                p = (p + 1) % Hashsize;
            if(strcmp(HT.elem[p].tele,"\0") == 0)
                HT.elem[p] = user[i];
            else
                continue;                                                           //ֱ�ӽ�����һ��ѭ��
        }    
    }   
}

void InitHashTable_usna(HashTable_username &HT){
    
}

void Search(HashTable_tele HT, int &p, char *tele){
    int tele_trans = (tele[0] - '0') * 10 + tele[1] - '0';
    p = tele_trans % 11;                                                            //pΪ����ָ��
    while(strcmp(HT.elem[p].tele,"\0") != 0 && strcmp(HT.elem[p].tele,tele) != 0)   //  Сȱ�ݣ���ϣ�������Ļ�����ѭ��-------------����while    ����̽��Ļ�����ʹ��ѭ������ / ����while�Ӹ�������
        p = (p + 1) % Hashsize;
    if(strcmp(HT.elem[p].tele,"\0") == 0)
        p = -1;
    else
        return;
}

int main(){
    HashTable_tele HT_tele;
    HashTable_username HT_usna;
    if(!(HT_tele.elem = (Userptr)malloc(sizeof(User)*Hashsize)))                    //�����Ե绰Ϊ�ؼ��ֵĹ�ϣ��
        exit(OVERFLOW);
    if(!(HT_usna.elem = (Userptr *)malloc(sizeof(Userptr)*Hashsize)))               //����������Ϊ�ؼ��ֵĹ�ϣ��
        exit(OVERFLOW);

    //��������������úù�ϣ���е�����
    InitHashTable_tele(HT_tele);
    // InitHashTable_usna(HT_usna);

    char tele[12] = {0};
    printf("������Ҫ���ҵĵ绰���룺");
    scanf("%s", tele);

    int p = -1;
    Search(HT_tele, p, tele);
    if(p == -1)
        printf("δ�ҵ���\n");
    else
        printf("�绰��%s  ������%s  ��ַ��%s\n", HT_tele.elem[p].tele, HT_tele.elem[p].UserName, HT_tele.elem[p].Add);
    return 0;
}