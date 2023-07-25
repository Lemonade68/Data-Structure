// ����һ�����У�����˳������ҵ�ָ��Ԫ�أ� 
// Ȼ������н���������õݹ���ǵݹ鷽��ʵ���۰����

#include<stdio.h>
#include<stdlib.h>

typedef struct{
    int *elem;
    int length;
} SSTable;

//�ǵݹ鷽ʽ��
int Search_bin(SSTable T, int key){
    int high, low, mid;
    high = T.length - 1;
    low = 1;
    while(high >= low){
        mid = (high + low) / 2;
        if(T.elem[mid] == key)
            return mid;
        else if(T.elem[mid] > key)
            high = mid - 1;
        else
            low = mid + 1;
    }
    return 0;
}   

//�ݹ鷽ʽ��
int Search_bin_2(SSTable T, int key, int high, int low){
    int mid;
    if(low > high)
        return 0;
    else{
        mid = (high + low) / 2;
        if(T.elem[mid] == key)
            return mid;
        else if(T.elem[mid] > key)
            return Search_bin_2(T, key, mid - 1, low);
        else
            return Search_bin_2(T, key, high, mid + 1);
    }
}


int main(){
    int i, n, key;
    printf("���������");
    scanf("%d", &n);
    SSTable T;
    T.elem = (int *)malloc(sizeof(int) * (n + 1));      //��һλ��������
    T.length = n + 1;
    for (i = 1; i <= T.length - 1; ++i)
        scanf("%d", &T.elem[i]);

    printf("����Ҫ���ҵ�Ԫ�أ�");
    scanf("%d", &key);
    T.elem[0] = key;                                    //���ü�����
    // ֱ�Ӳ��ң�
    for (i = T.length - 1; T.elem[i] != key; --i);
    if(i == 0)
        printf("˳����ң�δ�ҵ�\n");
    else
        printf("˳����ң�λ��Ϊ��%d\n", i);

    // ����
    for (i = 1; i <= T.length - 2; i++){                 // ����size - 1��
        for (int j = 1; j <= T.length - 1 - i; j++){     // ��a��ִ�дӵ�һλִ�е�������a+1λ
            if(T.elem[j] > T.elem[j + 1]){
                int temp = T.elem[j];
                T.elem[j] = T.elem[j + 1];
                T.elem[j + 1] = temp;
            }
        }
    }

    //��ӡ��������У�
    i = 1;
    printf("������������£�\n");
    while(i <= T.length - 1)
        printf("%d ", T.elem[i++]);
    printf("\n");

    //�ݹ鷽ʽ�����ң�
    i = Search_bin_2(T, key, T.length - 1, 1);
    if(i == 0)
        printf("�ݹ��۰���ң�δ�ҵ�\n");
    else
        printf("�ݹ��۰���ң�λ��Ϊ��%d\n", i);

    //�ǵݹ鷽ʽ�۰���ң�
    i = Search_bin(T, key);
    if(i == 0)
        printf("�ǵݹ��۰���ң�δ�ҵ�\n");
    else
        printf("�ǵݹ��۰���ң�λ��Ϊ��%d\n", i);

    return 0;
}