// a.平均时间性能：

// 1. O(nlogn)   高效排序
// 快速排序、堆排序、归并排序

// 中间选手：希尔排序 ---O(n^1.3)大概

// 2. O(n^2)     简单排序
// 直接插入、冒泡、简单选择

// 3. O(n)    基数排序
// 基数排序

// 当待排记录序列按关键字有序时：
// 直接插入和冒泡可以达到O(n)的复杂度
// 快排会变成O(n^2)

// 简单选择排序、堆排序、归并排序的时间性能不随记录序列中关键字分布而改变



// b.空间性能:

// 直接插入、冒泡、简单选择以及堆排序空间复杂度都为O(1)
// 快速排序为O(logn)，为递归程序执行过程中栈所需的辅助空间
// 归并排序所需辅助空间最多，O(n)
// 链式基数排序：队列首尾指针，空间复杂度O(rd)     (收集次数)




// 内排方法的选择：
// 1.时间复杂度角度
// 元素较多：快排、堆排、归并排序
// 元素较少：简单排序方法即可

// 2.空间复杂度角度
// 尽量选O(1)，然后选O(logn)的快排，最后选O(n)的归并


// 补充说明：当只需要选出最小的某几个或者最大的某几个时，选用堆排序