// Ҫ��ֻ��һ��Ԫ�ش�С�ĸ��Ӵ洢����Ԫ���ƶ�����ΪO(n)

//����������ת�������ɵõ������
void trans(int *a, int k, int n){   //k��ʾ����kλ��n��ʾa����Ԫ�ظ���
    if (k >= n)
        k = k % n;
    reverse(a, 0, n - k - 1);
    reverse(a, n - k, n - 1);
    reverse(a, 0, n - 1);
}

// ��head��ʼ��tail������Ԫ����ת
void reverse(int *a, int head, int tail){
    int temp = 0;
    while(head <= tail){
        temp = a[tail];
        a[tail] = a[head];
        a[head] = temp;
        head++;
        tail--;
    }
}