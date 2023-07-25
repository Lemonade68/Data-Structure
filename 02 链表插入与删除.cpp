// 链表插入与删除元素

//插入：第i个位置前插入元素e------找第i-1个元素
p = L;   
j = 0;
// p=L->next; j=1;  两者效果不同！！！    这里插入或者删除第一个元素时都需要用到第0个，因此j要从0开始取值

//思考：这里可以插在最后一位后面，找的是最后一个； 可以插在第一位前面，两个while都是取的=条件，直接跳过
while(p && j<i-1)          //寻找第i-1个结点
{
    p = p->next;
    j++;
}
if(!p || j>i-1)
    return ERROR;

s = (Linklist)malloc(sizeof(LNode));
if(!s)
    exit(OVERFLOW);

s->data = e;
s->next = p->next;
p->next = s;
return OK;


//删除：删除第i个元素，由e返回其值
p = L;
j = 0;
while(p && j<i-1)
{
    p = p->next;
    j++;
}
if(!p || j>i-1)
    return ERROR;
q = p->next;
p->next = q->next;
e = q->data;
free(q);
return OK;




//排序链表去重 O（n）
var deleteDuplicates = function(head) {
    let current = head //把首节点指针赋值给current
    while(current && current.next) { //当前节点以及下一节点不为空时
        if(current.val === current.next.val) { //值相等
            current.next = current.next.next
        }else {
            current = current.next //值不相等
        }
    }
    return head //返回首节点
};