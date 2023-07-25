//  特殊矩阵

// 一、对称矩阵----n^2元素搞到n(n+1)/2元素

//--------技巧：压缩后矩阵从0下标开始-----该元素前面有多少个元素，压缩后就位于数组的第几位--------
//--------技巧：压缩后矩阵从1下标开始-----该元素是第多少个元素，压缩后就位于数组的第几位--------

// 1.从(1,1)开始
// 对应的下标k：
// i>=j时：[i(i-1)/2+j]-1      []中是第_个元素
// i<j时：[j(j-1)/2+i]-1       转置--i j互换

// 2.从(0,0)开始
// 对应的下标k:
// i>=j时：[(i+1)i/2+j+1]-1
// i<j时：[(j+1)j/2+i+1]-1


// 二、三角矩阵----按(0,0)开始讨论

// 1.上三角矩阵：
// 除重复元素外，其余元素共n(n+1)/2个----->存入s[0,1,...,n(n+1)/2]中        其中，重复元素c存放在最后一个位置上
// 主对角线上第i行恰有n-i个元素(i从0开始)，aij之前的i行一共有i(2n-i+1)/2个元素
// aij前  从aii,ai(i+1),...,ai(j-1)共j-i个元素
// 所以有对应下标k：
// i<=j时，k=i(2n-i+1)/2+j-i
// i>j时，k=n(n+1)/2

// 2.下三角矩阵
// 与对称矩阵相同，只不过最后一个元素存放重复元素
// 对应的下标k：
// i>=j时，k=i(i+1)/2+j
// i<j时，k=n(n+1)/2

// 3.对角矩阵-----所有非零元素都集中在以主对角线为中心的袋装区域内
// 以三对角矩阵为例
// n行--用s[3n-2]来储存，除第一行和最后一行外，每行三个元素中间i j相同，左：j=i-1,右：i=j-1
// 规律：aij前有i行，共3i-1个元素，aij前有j-i+1个元素，加起来共 2i+j
// 因此在矩阵中，aij的地址为    location(0,0)+(2i+j)*d
// 对应的下标k:
// i=j+1 || i=j || i=j-1 时，k=2i+j

// 以(1,1)开头的数组用相同的方法计算


