#include "mapTake.h"

void showMeTheTopology(const std::vector<nodeInfo> &node){
    for (int i=0;i<node.size();++i){
        std::cout<<"节点性质 "<<node[i].tag<<std::endl;
        std::cout<<"节点编号 "<<node[i].ord<<std::endl;
        for(int j=0;j<node[i].road.size();++j){
            std::cout<<"  路径性质 "<<node[i].road[j].tag<<std::endl;
            std::cout<<"  路径权重 "<<node[i].road[j].weight<<std::endl;
            std::cout<<"  路径末端 "<<node[i].road[j].notice<<std::endl;
            std::cout<<std::endl;
        }
        std::cout<<"------------------------------------"<<std::endl;
    }
}

infoTxt readTexture(std::string name){
    infoTxt info;
    std::ifstream map;
    map.open(name);
    map>>info.numPoint;
    map>>info.numLine;
    map>>info.timeRestrict;

    std::array<int,3> tmpThree;
    for(int i=0;i<info.numLine;++i){
        map>>tmpThree[0];
        map>>tmpThree[1];
        map>>tmpThree[2];
        info.lines.push_back(tmpThree);
    }
    int num;
    map>>info.greenPoint;
    for(int i=0;i<info.greenPoint;++i){
        map>>num;
        info.tagGreenPoint.push_back(num);
    }
    std::array<int,2> tmpTwo;
    map>>info.greenLine;
    for(int i=0;i<info.greenLine;++i){
        map>>tmpTwo[0];
        map>>tmpTwo[1];
        info.tagGreenLines.push_back(tmpTwo);
    }
    map>>info.redLine;
    for(int i=0;i<info.redLine;++i){
        map>>tmpTwo[0];
        map>>tmpTwo[1];
        info.tagRedLines.push_back(tmpTwo);
    }
    return info;
}

std::vector<nodeInfo> initializeNode(infoTxt info){
    std::vector<nodeInfo> node(info.numPoint);
    roadInfo tmp;
    for(int i=0;i<info.numLine;++i){
        tmp.notice=info.lines[i][1];
        tmp.weight=info.lines[i][2];
        tmp.tag=0;
        node[info.lines[i][0]].ord=info.lines[i][0];
        node[info.lines[i][0]].road.push_back(tmp);
        node[info.lines[i][0]].tag=0;
        tmp.notice=info.lines[i][0];
        tmp.weight=info.lines[i][2];
        tmp.tag=0;
        node[info.lines[i][1]].ord=info.lines[i][1];
        node[info.lines[i][1]].road.push_back(tmp);
        node[info.lines[i][1]].tag=0;
    }
    for(int i=0;i<info.greenPoint;++i){//绿色点
        node[info.tagGreenPoint[i]].tag=1;
    }
    for(int i=0;i<info.greenLine;++i){//绿色路径
        for(int j=0;j<node[info.tagGreenLines[i][0]].road.size();++j){
            if(node[info.tagGreenLines[i][0]].road[j].notice==info.tagGreenLines[i][1])node[info.tagGreenLines[i][0]].road[j].tag=1;
        }
        for(int j=0;j<node[info.tagGreenLines[i][1]].road.size();++j){
            if(node[info.tagGreenLines[i][1]].road[j].notice==info.tagGreenLines[i][0])node[info.tagGreenLines[i][1]].road[j].tag=1;
        }
    }
    for(int i=0;i<info.redLine;++i){//红色路径
        for(int j=0;j<node[info.tagRedLines[i][0]].road.size();++j){
            if(node[info.tagRedLines[i][0]].road[j].notice==info.tagRedLines[i][1])node[info.tagRedLines[i][0]].road[j].tag=2;
        }
        for(int j=0;j<node[info.tagRedLines[i][1]].road.size();++j){
            if(node[info.tagRedLines[i][1]].road[j].notice==info.tagRedLines[i][0])node[info.tagRedLines[i][1]].road[j].tag=2;
        }
    }
    // 切断红色路径，这样就不会依照我们的算法最后路径一定不会包含红色路径
    for(int i=0;i<node.size();++i){
        for(int j=0;j<node[i].road.size();++j)
        {
            if(node[i].road[j].tag==2){
                node[i].road.erase(node[i].road.begin()+j);
                --j;
            }
        }
    }

    return node;
}//此处较之前 修改为切断红线 以减少拓扑复杂度 增加速度

std::vector<nodeInfo> initializeLessPoint(infoTxt info){
    std::vector<nodeInfo> node(info.numPoint);
    roadInfo tmp;
    for(int i=0;i<info.numLine;++i){
        tmp.notice=info.lines[i][1];
        tmp.weight=1;
        tmp.tag=0;
        node[info.lines[i][0]].ord=info.lines[i][0];
        node[info.lines[i][0]].road.push_back(tmp);
        node[info.lines[i][0]].tag=0;
        tmp.notice=info.lines[i][0];
        tmp.weight=1;
        tmp.tag=0;
        node[info.lines[i][1]].ord=info.lines[i][1];
        node[info.lines[i][1]].road.push_back(tmp);
        node[info.lines[i][1]].tag=0;
    }
    for(int i=0;i<info.greenPoint;++i){//绿色点
        node[info.tagGreenPoint[i]].tag=1;
    }
    for(int i=0;i<info.greenLine;++i){//绿色路径
        for(int j=0;j<node[info.tagGreenLines[i][0]].road.size();++j){
            if(node[info.tagGreenLines[i][0]].road[j].notice==info.tagGreenLines[i][1])node[info.tagGreenLines[i][0]].road[j].tag=1;
        }
        for(int j=0;j<node[info.tagGreenLines[i][1]].road.size();++j){
            if(node[info.tagGreenLines[i][1]].road[j].notice==info.tagGreenLines[i][0])node[info.tagGreenLines[i][1]].road[j].tag=1;
        }
    }
    for(int i=0;i<info.redLine;++i){//红色路径
        for(int j=0;j<node[info.tagRedLines[i][0]].road.size();++j){
            if(node[info.tagRedLines[i][0]].road[j].notice==info.tagRedLines[i][1])node[info.tagRedLines[i][0]].road[j].tag=2;
        }
        for(int j=0;j<node[info.tagRedLines[i][1]].road.size();++j){
            if(node[info.tagRedLines[i][1]].road[j].notice==info.tagRedLines[i][0])node[info.tagRedLines[i][1]].road[j].tag=2;
        }
    }
    // 切断红色路径，这样就不会依照我们的算法最后路径一定不会包含红色路径
    for(int i=0;i<node.size();++i){
        for(int j=0;j<node[i].road.size();++j)
        {
            if(node[i].road[j].tag==2){
                node[i].road.erase(node[i].road.begin()+j);
                --j;
            }
        }
    }

    return node;
}
//此处函数细节已经逐个检测，结果正确
//此处函数不涉及任何算法，单纯的读入信息并总结入框架
