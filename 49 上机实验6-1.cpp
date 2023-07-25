// ������Ϊ�������ݵ�������ʱ������sizeof�󳤶�   ������������������������
// ����취����ǰ������Ⱥ�����������������

#include<stdio.h>

void Print(int *a, int len){
    for (int i = 0; i < len;++i)
        printf("%d ", a[i]);
    printf("\n");
}

void swap(int &a, int &b){
    int temp = a;
    a = b;
    b = temp;
}

// ð��
void BubbleSort(int *a, int len){
    int i, j;
    for (i = 0; i < len - 1; ++i){
        for (j = 0; j < len - i - 1; ++j){
            if(a[j]>a[j+1])
                swap(a[j], a[j + 1]);
        }
    }
    Print(a, len);
}

// ��ѡ��
void SimpleSelectionSort(int *a, int len){
    for (int i = 0; i < len - 1;i++){
        int k = i;
        for (int j = i + 1; j < len;j++)
            if(a[j] < a[k])
                k = j;
        if(k!=i)
            swap(a[i], a[k]);
    }
    Print(a, len);
}


// ֱ�Ӳ���
void Insertsort(int *a,int len){
    int i, j;
    for (i = 1; i < len; i++){
        if(a[i] < a[i-1]){
            int temp = a[i];            //�ڱ�
            for (j = i - 1; j >= 0 && a[j] > temp;j--)
                a[j + 1] = a[j];
            a[j + 1] = temp;
        }
    }
    Print(a, len);
}

// ����
int Partition(int *a, int low, int high){
    int mid, pivot = a[low];
    while(low < high){
        while(low < high && a[high] >= pivot)
            --high;
        a[low] = a[high];                   // ��߲���a[low++]
        while(low < high && a[low] <= pivot)
            ++low;
        a[high] = a[low];
    }
    a[low] = pivot;
    return low;
}

void Qsort(int *a, int low, int high){
    if(low < high){
        int pivot = Partition(a, low, high);
        Qsort(a, low, pivot - 1);
        Qsort(a, pivot + 1, high);
    }
}

// ������


int main(){
    int a[10] = {8, 6, 5, 1, 3, 9, 7, 2, 4, 10};
    int len = sizeof(a) / sizeof(int);
    // BubbleSort(a, len);
    // SimpleSelectionSort(a, len);
    // Insertsort(a, len);
    Qsort(a, 0, len - 1);
    Print(a, len);
    return 0;
}