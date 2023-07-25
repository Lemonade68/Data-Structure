//����������ʵ��

#include<stdio.h>
#include<stdlib.h>  
#include<string.h>
#define OVERFLOW -2

typedef struct HTNode {
	char ch;
	int weight;
	int parent;
	int lchild, rchild;
} HTNode, *HuffmanTree;

typedef char **HuffmanCode;

void Select(HuffmanTree HT, int n, int &s1, int &s2) {
	if(n < 2)
        return;
    int min1 = 0, min2 = 0;
	for (int i = 1; i <= n; ++i) {
		if (HT[i].parent == 0) {
			if (min1 == 0)
				min1 = i;
			else if (min1 != 0 && min2 == 0) {
				if (HT[min1].weight > HT[i].weight) {
					min2 = min1;
					min1 = i;
				}
				else
					min2 = i;
			}
			else {
				if (HT[i].weight < HT[min1].weight) {
					min2 = min1;
					min1 = i;
				}
				else if (HT[i].weight < HT[min2].weight)
					min2 = i;
			}
		}
	}
    s1 = min1;
    s2 = min2;
}

void CrtHfmanTree(HuffmanTree &HT) {
	int n, i, s1, s2, j, k;
	int w[100] = { 0 };
	char ch[100] = { 0 };
	printf("������Ҫ������ַ�������\n");
	scanf("%d", &n);
	getchar();
	printf("�����������Ӧ���ַ���Ȩֵ��\n");
	for (i = 0; i < n; i++) {
		scanf("%c %d", &ch[i], &w[i]);
		getchar();                          //��ȡ�س�
	}
	int m = 2 * n - 1;

	//��ʼ����������
	if (!(HT = (HuffmanTree)malloc(sizeof(HTNode) * (m + 1))))
		exit(OVERFLOW);
	HuffmanTree p;
	for (p = HT + 1, i = 0; i < n; p++, i++)
		*p = { ch[i], w[i], 0, 0, 0 };
	for (; i < m; p++, i++)
		*p = { '0', 0, 0, 0, 0 };

	//�����������
	for (int i = n + 1; i <= m; i++) {
		Select(HT, i - 1, s1, s2);               //1��i-1��Ѱ��Ȩֵ��С������
		HT[s1].parent = i;
		HT[s2].parent = i;
		HT[i].lchild = s1;
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}


	//��Ҷ�ӽ�㿪ʼΪÿ��ȨֵѰ�ұ���
	HuffmanCode HC = (HuffmanCode)malloc(sizeof(char *) * (n + 1));
	if (!HC)
		exit(OVERFLOW);
    char *cd = (char *)malloc(sizeof(char) * n);
    if (!cd)
        exit(OVERFLOW);
	for (int i = 1; i <= n; i++) {
		int start = n - 1;
		cd[start] = '\0';           //������
		for (j = i, k = HT[j].parent; k != 0; j = k, k = HT[k].parent) {
			if (j == HT[k].lchild)
				cd[--start] = '0';
			else
				cd[--start] = '1';
		}
		HC[i] = (char *)malloc(sizeof(char) * (n - start));
		strcpy(HC[i], &cd[start]);
	}

    free(cd);               //�ǵ�free��

    //��ӡ
	printf("����������������������ַ���ǰ׺���룺\n");
	for (int i = 1; i <= n; i++)
		printf("��%d���ַ�%c�ı���Ϊ��   %s\n", i, HT[i].ch, HC[i]);

    //����
    char *buff = (char *)malloc(sizeof(char) * 100);
    printf("���濪ʼ���룬���������룺");
    scanf("%s", buff);
    int q = m;                              //��Ҷ�ӽ�㿪ʼ��
    while(*buff){                           //���дwhile(buff)���ԣ�
        if((*buff) == '0')
            q = HT[q].lchild;
        else 
            q = HT[q].rchild;
        
        if(HT[q].lchild == 0 && HT[q].rchild == 0){
            printf("%c", HT[q].ch);
            q = m;
        }
        buff++;
    }


}

int main() {
	HuffmanTree T;
	CrtHfmanTree(T);
	return 0;
}