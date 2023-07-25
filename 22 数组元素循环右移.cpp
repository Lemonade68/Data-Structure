// 要求：只用一个元素大小的附加存储，且元素移动次数为O(n)

//进行三次逆转操作即可得到最后结果
void trans(int *a, int k, int n){   //k表示右移k位，n表示a的总元素个数
    if (k >= n)
        k = k % n;
    reverse(a, 0, n - k - 1);
    reverse(a, n - k, n - 1);
    reverse(a, 0, n - 1);
}

// 从head开始到tail结束的元素逆转
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