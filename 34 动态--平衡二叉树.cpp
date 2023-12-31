// 二叉平衡树：左右结点深度差不超过1
// 定义：结点的平衡因子BF等于结点左子树高度-右子树高度   可取的值有-1,0,1

// 构造方法：平衡旋转技术
// 离插入结点最近且平衡因子为2、-2的祖先节点作为根的子树称为最小不平衡子树

// 平衡操作分为：
// 1.RR型左旋
// 2.LL型右旋
// 3.LR型先左后右
// 4.RL型先右后左

// *****************************************
// 每插入一个节点，AVL树中相关节点的平衡状态会发生变化，因此需要从 *插入位置* 沿向根的路径回溯，检查各结点的平衡因子，
// 若发现某一结点的高度不平衡，则停止回溯
// 从该结点开始，沿刚才回溯的路径取直接下两层的结点

// RR型：最小不平衡子树的根结点下降为其右孩子的左子树，原右孩子变为根结点---左单旋转
// LL型：最小不平衡子树的根结点下降为其左孩子的右子树，原左孩子变为根结点---右单旋转
// LR型与RL型：见34.1与34.2图    注意：第一步操作时关于变化后B放在C的哪边----B<C  放左子树，  反之  放右子树

// 总结要点：保证按直线型旋转时中间的结点上一定是中间值

// 算法：  ppt上未讲  具体见书  日后补充

#define pass 0


// 问：含n个关键字的二叉平衡树可能达到的最大深度是多少？
// 找规律---Nh = Nh-1 +Nh-2 + 1    与斐波那契数列相似
// 即：深度为h的平衡二叉树中含有的最少结点数为Nh     进而推导出结果

