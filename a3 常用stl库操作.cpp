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
    std::sort(a, a + 10);           //��a���д�С���������
    std::sort(a, a + 10, cmp);      //�Ӵ�С

    // vector
    std::vector<int> vec{1, 2, 3, 4, 5};
    std::reverse(vec.begin(), vec.begin() + 5);   
    std::sort(vec.begin(), vec.end());      //��������
    std::vector<int>::iterator it;
    
    bool flag = std::binary_search(vec.begin(), vec.end(), 5);  //���ֲ���
    if(flag == true)
        std::cout << "true" << std::endl;
    
    for (auto a: vec)
        std::cout << a << std::endl;

    vec.push_back(6);
    vec.pop_back();

    int m = vec.at(3);                          //�ҵ���Ӧ�±������
    std::cout << m << std::endl;
    std::cout << vec.front() << std::endl;
    std::cout << vec.back() << std::endl;
    std::cout << vec.capacity() << std::endl;   //����Ĵ�С(�����ڴ�δʹ��)
    std::cout << vec.size() << std::endl;       //���ݵĴ�С

    isempty = vec.empty();

// stack
    std::stack<int> s;
    isempty = s.empty();
    s.pop();                //�Ƴ�ջ��Ԫ��
    s.push(1);              //ջ�����Ԫ��
    int s_size = s.size();
    int s_top = s.top();    //����ջ��Ԫ��


//queue(û�е�����)
    std::queue<int> q;
    q.push(1);          //�ӵ���β
    q.pop();            //ɾ����ͷ
    int q_front = q.front();    //��ͷԪ��
    int q_back = q.back();      //��βԪ��
    int q_size = q.size();
    isempty = q.empty();

//priority_queue(û�е�����)
    std::priority_queue<int, std::vector<int>, std::greater<int>> Q;
    //��������������
    Q.push(1);
    Q.top();
    Q.pop();
    Q.size();

    // list ˫������
    std::list<int> l;
    l.push_back(1);     //β������
    l.push_front(2);    //ͷ������
    l.reverse();        //����

    if(!l.empty()){     //���������ǰ����
        int l_f = l.front();
        int l_b = l.back();
        l.pop_back();   //ɾ��β���
        l.pop_front();
    }

//deque ˫�˶���
    std::deque<int> d;
    //����ͬlist
    
    return 0;
}