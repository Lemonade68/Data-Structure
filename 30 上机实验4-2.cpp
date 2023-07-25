//哈夫曼树的实现

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
	printf("请输入要编码的字符个数：\n");
	scanf("%d", &n);
	getchar();
	printf("请依次输入对应的字符与权值：\n");
	for (i = 0; i < n; i++) {
		scanf("%c %d", &ch[i], &w[i]);
		getchar();                          //读取回车
	}
	int m = 2 * n - 1;

	//初始化哈夫曼树
	if (!(HT = (HuffmanTree)malloc(sizeof(HTNode) * (m + 1))))
		exit(OVERFLOW);
	HuffmanTree p;
	for (p = HT + 1, i = 0; i < n; p++, i++)
		*p = { ch[i], w[i], 0, 0, 0 };
	for (; i < m; p++, i++)
		*p = { '0', 0, 0, 0, 0 };

	//构造哈夫曼树
	for (int i = n + 1; i <= m; i++) {
		Select(HT, i - 1, s1, s2);               //1到i-1中寻找权值最小的两个
		HT[s1].parent = i;
		HT[s2].parent = i;
		HT[i].lchild = s1;
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}


	//从叶子结点开始为每个权值寻找编码
	HuffmanCode HC = (HuffmanCode)malloc(sizeof(char *) * (n + 1));
	if (!HC)
		exit(OVERFLOW);
    char *cd = (char *)malloc(sizeof(char) * n);
    if (!cd)
        exit(OVERFLOW);
	for (int i = 1; i <= n; i++) {
		int start = n - 1;
		cd[start] = '\0';           //结束符
		for (j = i, k = HT[j].parent; k != 0; j = k, k = HT[k].parent) {
			if (j == HT[k].lchild)
				cd[--start] = '0';
			else
				cd[--start] = '1';
		}
		HC[i] = (char *)malloc(sizeof(char) * (n - start));
		strcpy(HC[i], &cd[start]);
	}

    free(cd);               //记得free掉

    //打印
	printf("下面输出经哈夫曼编码后各字符的前缀编码：\n");
	for (int i = 1; i <= n; i++)
		printf("第%d个字符%c的编码为：   %s\n", i, HT[i].ch, HC[i]);

    //译码
    char *buff = (char *)malloc(sizeof(char) * 100);
    printf("下面开始译码，请输入译码：");
    scanf("%s", buff);
    int q = m;                              //从叶子结点开始走
    while(*buff){                           //这边写while(buff)不对！
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