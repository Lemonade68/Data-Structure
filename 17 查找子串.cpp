//BF算法（自己写）：
//txt为主串，pat为子串
char* StrStr(const char *txt, const char *pat){
    int j=0,length =0;
    for(length =0;pat[length];length++);    //注意循环结束时括号里声明的变量会被消除
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



//标准bf算法：
char* StrStr(const char* txt, const char* pat) {
    int m,n,i,j=0;
    m=n=i=j=0;
    for(;txt[m];m++);           //得到txt串的长度m
    for(;pat[n];n++);           //得到pat串的长度n
    for(;i<m&&j<n;){            //当串没有匹配到终点时一直循环
        if(txt[i]==pat[j]){     //匹配上了就都加一继续匹配
            i++;
            j++;
        }
        else{                  //否则就i返回原来位置加1，重新开始匹配
            i=i-j+1;            //i加的数量就是j
            j=0;
        }
    }
    if(j==n)                    //当j==n证明了txt全匹配上，则返回地址
        return &(txt[i-j]);     //下标为i-j同理
    return NULL;
}


//书上写法：
int Index(SString S, SString T, int pos){
    i = pos, j = 1;
    while(i<=S[0] && j <= T[0]){
        if(S[i] == T[j]){
            ++i;
            ++j;
        }
        else{
            i = i - j + 2;      //i指针回溯
            j = 1;
        }
    }
    if(j>T[0])                  //整个串有被找到
        return i - T[0];        //返回模式串的起始位置
    return 0;
}



//kmp算法：
    //利用模式串T的next函数求在主串S中第pos个字符之后的位置的kmp算法
int Index_KMP(SString S, SString T, int pos){
    int i = pos, j = 1;                 //  i指向主串，j指向模式串
    while(i<=S[0] && j <= T[0]){        //  S[0],T[0]储存的是S T的长度
        if(j == 0 || S[i] == T[j]){     //  j=0：完全没有相同的首位字符的情况
            ++i;
            ++j;
        }
        else
            j = next[j];        
    }
    if(j>T[0])                  //整个串被找到
        return i - T[0];        //返回模式串起始位置      i先减1回到++前的位置 再减T[0]长度 再加1
    return 0;
}   



//求模式串的next[j]的函数：         求的是模式串！！！
    // next[]下标从1开始，  ch[]下标从也从1开始
int GetNext(char ch[], int length, int next[]){ //length为ch中的长度
    next[1] = 0;
    int i = 1, j = 0;                   //  i j代表ch中的下标，i还代表next中的下标
    while(i <= length){
        if(j==0 || ch[i] == ch[j])      //  j=0两种情况：  next[1]  以及  完全没有重合字符串     （从而让下一位的next值变为1）
            next[++i] = ++j;            //  next[k]反映的是从1到k-1位的前缀后缀重合字符个数+1
        else
            j = next[j];                //  next[j]的含义：指向j位置前面的字符串中最长字符重合串的下一个字符，
    }                                   //  再从ch[next[j]]与ch[i]比较，若相等，则用next[j]的值+1（加上最新相等的一个）作为next[++i]的值
}                                       //  若还是不相等，再递推


// 具体理解见图示


//代码改进：

// 特殊情况为例： a a a a a b

// 改进点：如果发生s[i]和t[j]不匹配的情况，j回到next[j]
// 然后t[j]和t[next[j]]相同，且与s[i]不同，…… 会重复操作
// 在设置next数组时就将这些重复的中间过程去掉

// 一般方法：P表示字符
// j=1时，nextval赋值为0
// Pj不等于Pnext[j]，则nextval[j]=next[j];
// Pj等于Pnext[j]，则nextval[j]=nextval[next[j]];


//理解next[]数组的本质：当s与t匹配到不同的字符时，j回溯到next[j]

void get_nextval(SString T, int nextval []){
    i = 1;
    nextval[1] = 0;
    j = 0;
    while(i < T[0]){
        if (j == 0 || T[i] == T[j]){
            ++i;  ++j;
            if (T[i] != T[j]){          // 如果下面两个字符不等-->按正常的来
                nextval[i] = j
            } else{                     
// 如果下面i j指向的两字符相等，那么next[i]直接等于next[j]，跳过next[j]的位置
                nextval[i] = nextval[j]
            }
        }else{
            j = nextval[j];
        }
    }
}
 