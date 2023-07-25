//字符串的基本运算，分串的两种储存方案：
// 1.固定大小的数组
// 2.动态申请


//注意：free必须释放的是之前malloc过的；不能释放空指针
//注意：realloc必须也是之前动态分配过的，因此realloc前不能free

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define OVERFLOW -2

//定长顺序存储表示：            
//       -----------注意操作时对结束符'\0'的添加！！！------------
#define MAXSIZE 255                             //可在255内定义最大串长
typedef unsigned char SString[MAXSIZE + 1];     //  SString a相当于unsigned char a[maxsize+1];
                                                //  留一位给'\0'

//动态申请表示：
//  -----------注意操作时对ch和对length都要进行修改 || 结束符'\0'也要添加！！--------------
typedef struct HString{
    char *ch;           //若是非空串，则按串长分配存储区，否则ch为NULL
    int length;         //串长度
} HString;
//输出字符串时注意是  名称.ch   而不是名称！
//每次使用前一定要init，不然free会报错


//HString初始化操作     定义后就必须跟着
void InitString(HString &s){
    s.ch = NULL;
    s.length = 0;
}

// 1.求串长： if串存在 --> 求出串的长度
int SStrLength(SString s){
    int len = 0;
    for (len; s[len]; len++);           //求长度
    return len;                         //暂时不管s[0]的问题        
}

int HStrLength(HString s){      //非必要  直接s.length即可
    return s.length;
}


// 2.串赋值： 将s2的值赋给s1，s1原来的值被覆盖------若s2常量：串赋值----s2变量：串拷贝

//  对于SString: 考虑串拷贝情况
void SStrAssign(SString &s1, SString s2){
    int len = SStrLength(s2);
    for (int i = 0; i < len; i++){
        s1[i] = s2[i];
    }
    s1[len] = '\0';     //设置字符串结束符
}

//  对于HString: 考虑串赋值情况
void HStrAssign(HString &s1, const char *s){                //这边写const表示字符串常量
    if(s1.ch)
        free(s1.ch);            //释放旧空间
    int len = 0;
    for (len; s[len];len++);    //求出s的长度
    if(!(s1.ch=(char*)malloc(sizeof(char)*(len+1))))    //重新生成对应空间-------注意len+1  给'\0'预留位置-------
        exit(OVERFLOW);
    for (int i = 0; i < len; i++)
        s1.ch[i] = s[i];
    s1.ch[len] = '\0';          //这一步不能少！！！！！
    s1.length = len;            //别忘记存放变化后的s1的长度
}


// 3.串连接： 将s1与s2连接到s
void SStrConcat(SString s1, SString s2, SString &s){        //注意不能返回数组，要返回首地址
    int len1 = SStrLength(s1);
    int len2 = SStrLength(s2);
    int i = 0, j = 0;

    //先将s1中的先赋值给s
    while(i < len1){
        s[i] = s1[i];
        i++;
    }
    //情况1：两者合并后长度未超
    if(len1 + len2 <= MAXSIZE){
        while(j < len2){
            s[i + j] = s2[j];
            j++;
        }
    }
    //情况2：s1长度未超，s1+s2长度超
    else if(len1 < MAXSIZE){
        while(j < MAXSIZE - len1){
            s[i + j] = s2[j];
            j++;
        }
    }
    //情况3：s1长度超  无需再写

    s[i + j] = '\0';        //最后赋值字符串截止符 (下标为s1录入长度+s2录入长度-1+1)
}

void HStrConcat(HString s1, HString s2, HString &s){
    if(s.ch)
        free(s.ch);         //清除旧空间
    int len = s1.length + s2.length;
    if(!(s.ch = (char*)malloc(sizeof(char)*(len+1))))       //len+1给'\0'预留空间
        exit(OVERFLOW);
    int i = 0, j = 0;
    for (i; i < s1.length; i++)
        s.ch[i] = s1.ch[i];
    for (j; j < s2.length; j++)
        s.ch[s1.length + j] = s2.ch[j];
    s.ch[s1.length + s2.length] = '\0';     //这一步不能少！！！！
    s.length = len;                         //  别忘记保存长度
}


// 4.求子串： 返回从串s的第i个字符开始的长度为len的子串----包含第i个。len=0返回空串
void SubSStr(SString &sub, SString s, int i, int len){
    if (i <= 0 || i > SStrLength(s) || len < 0 || len > SStrLength(s) - i + 1){
        sub[0] = '\0';              //返回空串
        return;
    }
    int j = 0;
    i--;                            //从0下标开始
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
        free(sub.ch);           //删除旧空间
    if(!(sub.ch=(char*)malloc(sizeof(char)*(len+1))))       //len+1 给 '\0'预留空间
        exit(OVERFLOW);
    int j = 0;
    i--;
    while(j<len)
        sub.ch[j++] = s.ch[i++];
    sub.ch[len] = '\0';         //这步不能少！！！！
    sub.length = len;           //别忘记保存长度
}


// 5.串比较： 若s1 = s2，返回0；若s1 < s2，返回一个负整数；若s1 > s2，返回一个正整数
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
    if(s1[i])           // s1仍未遍历结束而s2结束
        return 1;
    else if(s2[i])      // 反之
        return -1;
    else                // 同时遍历结束
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


// 6.子串定位（模式匹配）： 若t∈S，则操作返回t在s中首次出现的位置，否则返回-1

//  这里我的位置都是按从0开始计算的
//  算法1：利用查找子串多次比较
int SStrIndex(SString s, SString t){
    int s_len = SStrLength(s);
    int t_len = SStrLength(t);
    SString sub;
    int i = 0;
    for (i; i < s_len - t_len + 1; i++){
        SubSStr(sub, s, i + 1, t_len);          // 下标为i表示第i+1个元素    
        if(SStrCmp(sub,t) == 0)
            return i;
    }
    return -1;
}

//  算法2：BF算法 
int SStrIndex_BF(SString s, SString t){
    int s_len = SStrLength(s);
    int t_len = SStrLength(t);
    int i = 0, j = 0;
    while(s[i] && t[j]){
        if(s[i] == t[j]){
            i++;
            j++;
        }
        else{                   // i进行回溯
            i = i - j + 1;      // i加了多少 j就加了多少，相减后+1指向下一个位置
            j = 0;              // j值重置为0
        }
    }
    if(!t[j])
        return i - j;
    return -1;
}

//  算法3：KMP算法
int SStrIndex_KMP(SString s, SString t){
    
    //先对t进行next数组的计算
    int next[MAXSIZE] = {0};        // s的next数组，注意下标从1开始
    int i = 1, j = 0;
    while(t[i]){
        if(j == 0 || t[i] == t[j])
            next[++i] = ++j;
        else
            j = next[j];
    }
    // next数组生成完毕

    i = 0, j = 0;   //比较主串和模式串
    while(s[i] && t[j]){
        if(j==0 || s[i] == t[j]){
            i++;
            j++;
        }
        else
            j = next[j];            // j=0的情况不会往这个else走
    }
    if(!t[j])
        return i - j;
    return -1;
}

int HStrIndex_KMP(HString s, HString t){
    //先求模式串t的next数组
    int *next = (int *)malloc(sizeof(int) * (t.length+1));      //动态创建一个数组，第一位空出，length+1
    int i = 1, j = 0;
    next[i] = 0;                                //记得把next[1]赋为初值0
    while(t.ch[i] && t.ch[j]){
        if(j==0 || t.ch[i] == t.ch[j])
            next[++i] = ++j;
        else
            j = next[j];
    }

    i = 0, j = 0;
    while(s.ch[i] && t.ch[j]){
        if(j == 0 || s.ch[i] == t.ch[j]){       //理解这边或的含义
            i++;
            j++;
        }
        else
            j = next[j];
    }
    free(next);         //释放空间
    if(!t.ch[j])
        return i - j;
    return -1;
}


// 7.串插入： 将串t插入到串s的第i个字符位置上，s的串值发生改变
void SStrInsert(SString &s, int i, SString t){
    int s_len = SStrLength(s);
    int t_len = SStrLength(t);

    //判断插入后是否超出范围，超出则只添加t的一部分
    if(s_len + t_len >MAXSIZE)
        t_len = MAXSIZE - s_len;

    for (int k = s_len - 1; k >= i - 1; k--)        //注意要从后往前！  不然会出问题
        s[k + t_len] = s[k];

    for (int j = 0; j < t_len; j++)
        s[j + i - 1] = t[j];                        //从第i-1下标开始插入

    s[s_len + t_len] = '\0';                        //最后添加结束符
}

void HStrInsert(HString &s, int i, HString t){
    // if(s.ch)
    //     free(s.ch);         //释放旧空间
    int len = s.length + t.length;
    char *ch = (char *)realloc(s.ch, sizeof(char) * (len + 1));     //这边重新生成一片空间，上面不能free！！
    if(!ch)
        exit(OVERFLOW);
    s.ch = ch;
    // if(!((char*)ch=(char*)realloc(s.ch, sizeof(char)*(len+1)))) //注意是realloc   len+1---'\0'
        // exit(OVERFLOW);
    for (int j = s.length - 1; j >= i - 1; j--)
        s.ch[j + t.length] = s.ch[j]; //从后往前赋值
    for (int k = 0; k < t.length; k++)
        s.ch[i - 1 + k] = t.ch[k];
    s.ch[len] = '\0';                               //别忘赋结束符
    s.length = len;                                 //别忘了保存长度
}


// 8.串删除： 删除串s中从第i个字符开始的长度为len的子串，s的串值改变
void SStrDelete(SString &s, int i, int len){
    int j = 0;
    int s_len = SStrLength(s);
    for (j; j < s_len - len - i + 1; j++)                   //与插入相反，从前往后操作
        s[i - 1 + j] = s [i - 1 + j + len];
    s[s_len - len] = '\0';
}

void HStrDelete(HString &s, int i, int len){
    //方便起见，堆的大小不改变
    int j = 0;
    for (j; j < s.length - i + 1 - len; j++)
        s.ch[i - 1 + j] = s.ch[i - 1 + j + len];
    s.ch[s.length - len] = '\0';
}


// 9.串替换： 用串r替换s中出现的所有与串t相等的不重叠的子串，s的串值改变  (r和t的长度不一定相同)
void SStrRep(SString &s, SString t, SString r){
    int pos = SStrIndex_KMP(s, t);
    while(pos != -1){           //存在t子串
        SStrDelete(s, pos + 1, SStrLength(t));      //先删除，注意是 pos + 1
        SStrInsert(s, pos + 1, r);                  //再插入
        pos = SStrIndex_KMP(s, t);                  //再次检测
    }
    //插入的最后已经插入结束符了，无需再添加结束符
}

void HStrRep(HString &s, HString t, HString r){
    int pos = HStrIndex_KMP(s, t);
    while(pos != -1){
        HStrDelete(s, pos + 1, t.length);           //同，注意是pos + 1
        HStrInsert(s, pos + 1, r);
        pos = HStrIndex_KMP(s, t);
    }
    //同理，插入和删除函数中已经对s.length和'\0'做出了处理，这里无需再次处理
}


int main(){
    // 定长顺序存储
    printf("\n-------------定长顺序存储表示-------------\n");

    SString ss1 = "abcd";
    printf("第1个字符串为%s, 长度: %d\n", ss1, SStrLength(ss1));

    SString ss2 = "abcde";
    SString ss3 = "abCde";
    printf("第2个字符串为%s, 长度: %d\n", ss2, SStrLength(ss2));
    printf("第3个字符串为%s, 长度: %d\n", ss3, SStrLength(ss3));
    
    SStrAssign(ss2, ss3);
    printf("将字符串3赋给字符串2后 字符串2变为: %s\n", ss2);

    SString ss;
    SStrConcat(ss1, ss2, ss);
    printf("合并1 2后字符串: %s\n", ss);

    SString ssub;
    SubSStr(ssub, ss, 2, 3);
    if(SStrLength(ssub))
        printf("第2个字符开始取3位的子串为: %s\n", ssub);

    int result = SStrCmp(ss1, ss2);
    printf("%s和%s的比较结果为: %d\n", ss1, ss2, result);

    SString t = "abC";
    // int i = SStrIndex(ss, t);
    // int i = SStrIndex_BF(ss, t);
    int i = SStrIndex_KMP(ss, t);
    printf("首个 %s 子串首字符位置为: %d\n", t, i);

    SStrInsert(ss,2,t);
    printf("插入 %s 子串到第2个位置上后字符串变为: %s\n", t, ss);

    SStrDelete(ss, 2, 3);
    printf("删除第2个位置开始的3个字符后字符串变为: %s\n", ss);

    SString s1 = "ab";
    SString s2 = "ABC";
    SStrRep(ss, s1, s2);
    printf("将%s替换为%s后字符串变为: %s\n", s1, s2, ss);

    // 堆分配存储
    printf("\n-------------堆分配存储表示-------------\n");
    HString hs1, hs2, hs;
    InitString(hs1);
    InitString(hs2);
    InitString(hs);

    HStrAssign(hs1, "abcd");
    printf("第1个字符串为%s, 长度: %d\n", hs1.ch, hs1.length);
    HStrAssign(hs2, "abCde");
    printf("第2个字符串为%s, 长度: %d\n", hs2.ch, hs2.length);

    HStrConcat(hs1, hs2, hs);
    printf("合并1 2后字符串: %s, 长度为: %d\n", hs.ch, hs.length);
    //这边有个问题-----------偶尔会出乱码-------->解决：最后要加上'\0'！！

    HString hsub;
    InitString(hsub);                       //一定要init
    SubHStr(hsub, hs, 2, 3);
    if(HStrLength(hsub))
        printf("第2个字符开始取3位的子串为: %s\n", hsub.ch);

    printf("%s和%s的比较结果为: %d\n", hs1.ch, hs2.ch, HStrCmp(hs1, hs2));

    HString ht;
    InitString(ht);                         //一定要init，不然free会报错
    HStrAssign(ht, "abC");                  //不能直接赋值
    printf("首个 %s 子串首字符位置为: %d\n", ht.ch, HStrIndex_KMP(hs, ht));

    HStrInsert(hs,2,ht);
    printf("插入 %s 子串到第2个位置上后字符串变为: %s\n", ht.ch, hs.ch);

    HStrDelete(hs, 2, 3);
    printf("删除第2个位置开始的3个字符后字符串变为: %s\n", hs.ch);

    HString hhs1, hhs2;
    InitString(hhs1);           //要改变的子串
    InitString(hhs2);           //改变后的子串
    HStrAssign(hhs1, "ab");
    HStrAssign(hhs2, "ABC");
    HStrRep(hs, hhs1, hhs2);
    printf("将%s替换为%s后字符串变为: %s\n", hhs1.ch, hhs2.ch, hs.ch);

    printf("\n");
    return 0;
}
