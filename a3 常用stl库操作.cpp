#include<algorithm>
#include<iostream>
#include<vector>
#include<stack>
#include<queue>
#include<list>
#include<deque>

bool isempty;

bool cmp(int a, int b){     //compare
    return a > b;
}


int main(){

    int a[10] = {13, 5, 7, 8, 9, 10, 15, 1, 11, 4};
    std::sort(a, a + 10);           //对a进行从小到大的排序
    std::sort(a, a + 10, cmp);      //从大到小

    // vector
    std::vector<int> vec{1, 2, 3, 4, 5};
    std::reverse(vec.begin(), vec.begin() + 5);   
    std::sort(vec.begin(), vec.end());      //递增排序
    std::vector<int>::iterator it;
    
    bool flag = std::binary_search(vec.begin(), vec.end(), 5);  //二分查找
    if(flag == true)
        std::cout << "true" << std::endl;
    
    for (auto a: vec)
        std::cout << a << std::endl;

    vec.push_back(6);
    vec.pop_back();

    int m = vec.at(3);                          //找到对应下标的数据
    std::cout << m << std::endl;
    std::cout << vec.front() << std::endl;
    std::cout << vec.back() << std::endl;
    std::cout << vec.capacity() << std::endl;   //分配的大小(还有内存未使用)
    std::cout << vec.size() << std::endl;       //数据的大小

    isempty = vec.empty();

// stack
    std::stack<int> s;
    isempty = s.empty();
    s.pop();                //移除栈顶元素
    s.push(1);              //栈顶添加元素
    int s_size = s.size();
    int s_top = s.top();    //返回栈顶元素


//queue(没有迭代器)
    std::queue<int> q;
    q.push(1);          //接到队尾
    q.pop();            //删除队头
    int q_front = q.front();    //队头元素
    int q_back = q.back();      //队尾元素
    int q_size = q.size();
    isempty = q.empty();

//priority_queue(没有迭代器)
    std::priority_queue<int, std::vector<int>, std::greater<int>> Q;
    //具有优先排序功能
    Q.push(1);
    Q.top();
    Q.pop();
    Q.size();

    // list 双向链表
    std::list<int> l;
    l.push_back(1);     //尾部插入
    l.push_front(2);    //头部插入
    l.reverse();        //逆置

    if(!l.empty()){     //必须在这个前提下
        int l_f = l.front();
        int l_b = l.back();
        l.pop_back();   //删除尾结点
        l.pop_front();
    }

//deque 双端队列
    std::deque<int> d;
    //操作同list
    
    return 0;
}