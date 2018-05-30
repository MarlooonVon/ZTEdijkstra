/* 此头文件包含所有基本信息                  *
 * 即 从文本信息 转换到 节点框架的所有结构和函数*/
#include <stdio.h>
#include<vector>
#include<array>
#include<iostream>
#include<fstream>
#define MAX_WEIGHT 100000
#define RED_WEIGHT 100
/* 基本信息框架部分*/
/* 由两块结构组成 roadInfo 和 nodeInfo */
struct roadInfo{
    int tag;       // 正常路径->0 绿色路径->1 红色路径->2
    double weight; // 路径权重
    int notice;    // 代表每个路径末端的节点（此处结合nodeInfo结构理解）
};

struct nodeInfo{
    int tag;                   // 正常点->0 绿色点->1
    int ord;                   // 节点编号
    std::vector<roadInfo> road;// 包含该节点所连接的所有路径的信息（此处与roadInfo结构结合理解）
};
//以上部分包含了拓扑图中所有的基本信息。
//任何拓扑图，只要基本要素是：
//基本节点 绿色节点 绿色道路 红色道路 普通道路
//都可以用这两个结构精确描述


/* 中兴科技提供的文本格式导入部分 */
struct infoTxt{
    int timeRestrict;     //限制次数 100
    int numPoint;         //所有节点的数量 此算例中即 800
    int numLine;          //所有道路的数量 此算例中即 2994
    int greenPoint;       //所有绿色节点的数量 此算例中 即 51
    int greenLine;        //所有绿色道路的数量 此算例中 即 14
    int redLine;          //所有红色道路的数量 此算例中 即 8
    std::vector<std::array<int,3>> lines;       // 所有道路信息
    std::vector<int> tagGreenPoint;             // 所有绿色节点的编号
    std::vector<std::array<int,2>>tagGreenLines;// 所有绿色路径的两端节点编号
    std::vector<std::array<int,2>>tagRedLines;  // 所有红色路径的两端节点编号
};
//以上信息均由文本自动输入输入


/* 读取数据函数与讲数据总结入基本框架的函数 */
infoTxt readTexture(std::string name);                    //文本读入函数
std::vector<nodeInfo> initializeNode(infoTxt info);       //将读入信息归结到基本框架的函数

//运行到此处，一切变化总结起来就是
//算例从原来的18点 扩展到了 500点 扩展到了800点
void showMeTheTopology(const std::vector<nodeInfo> &node);//展示所生成节点的拓扑结构
/*************************************************************************************/
std::vector<nodeInfo> initializeLessPoint(infoTxt info);  //为了寻找最短步数路

