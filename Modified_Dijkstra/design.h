/*我们在此头文件中进行算法设计*/
#include"mapTake.h"
#include<chrono>
#include<math.h>
// result 结构用于输出最后的结果
struct result{
    std::vector<int> order; // 最短路径的节点顺序
    double totalWeight;     // 最短路径的总路程 或 总权重
};
/************************************* 经典 Dijkstra 算法的实现 *******************************/
// classicDijkstraNode 结构用于 基于基本信息重新构造Dijkstra算法所使用的数据结构
struct classicDijkstraNode{
    //来源于基本信息，不用做任何改变
    nodeInfo node;  //基本节点信息
    int label;      //节点编号
    //在算法实施过程中需要改变各变量的状态
    bool visited;   //该节点是否已被访问
    int preNode;    //该节点的上一步所访问的节点
    double shortest;//到达该节点所走过的总路程 或 总权重

};
/* 经典 Dijkstra 实现函数 */
std::vector<classicDijkstraNode> initializeClassic(const std::vector<nodeInfo> node);
//此函数实现classicDijkstraNode结构的初始化

result Dijkstra(const int start,const int end,std::vector<classicDijkstraNode> &data);
//此函数很关键，实现使用Dijkstra算法搜索两点之间的最短路径
//需要注意的是，此函数实现的是： 任意两点 间 基于 全图拓扑结构 使用 Dijkstra算法 所搜索出的最短路径

int getLabelShort(std::vector<int> &waitList,const std::vector<classicDijkstraNode> &data);
bool exist(int neighboor,std::vector<int> waitList);
//以上两个函数是用于实现Dijkstra算法所设计的细节处理函数，完全符合经典Dijkstra算法，可根据算法进行理解
/******************************************************************************/

/**************************************展示结果******************************************/
void showMeTheEnd(std::string name, bool switchRestriction, bool WeightOrStep, int iteratorTime);   //显示结果
std::vector<int> insertGreenNode(const std::vector<nodeInfo> &node, const std::vector<int> &greenList);
std::vector<std::vector<int>> insertGreenLine(const std::vector<nodeInfo> &node,const std::vector<int> &solution,const std::vector<std::array<int,2>> &greenLines);
result calculateResult(const std::vector<nodeInfo> &node,const std::vector<int> &greenNodeInfo,const std::vector<std::vector<int>> &greenLineInfo);
/***************************************************************************************/
result reconstruction(const std::vector<nodeInfo> &node,const std::vector<int> list);
