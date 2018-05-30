#include"design.h"
#include<algorithm>
#include<time.h>

/***************************** 经典 Dijkstra 实现函数 *************************************/
std::vector<classicDijkstraNode> initializeClassic(const std::vector<nodeInfo> node){
    const int number=node.size();
    std::vector<classicDijkstraNode> vertex;
    classicDijkstraNode vertmp;
    for(int i=0;i<number;++i){
        //数值不随算法进程而动的部分
        vertmp.node.tag=node[i].tag;
        vertmp.label=node[i].ord;
        vertmp.node.road=node[i].road;       
        //数值随算法进程持续变化部分
        vertmp.visited=false;
        vertmp.preNode=-1;//  悬空 设置 -1
        vertmp.shortest=MAX_WEIGHT;
        vertex.push_back(vertmp);
    }
    return vertex;
}

//此处遵循经典Dijkstra算法，结合经典Dijkstra算法理解
result Dijkstra(const int start,const int end,std::vector<classicDijkstraNode> &data){

    std::vector<int> waitList;//储存待访问节点
    std::vector<int> visited; //储存已访问节点

    data[start].preNode=-1;
    data[start].shortest=0;
    waitList.push_back(start);

    int hold;                 //记录所访问节点编号
    int neighboorCount;       //记录相邻节点数量
    int neighboorhold;        //记录单个相邻节点编号
    double shortest;          //记录目前所走的最短路径数值
    while((hold!=end)&&(waitList.size()!=0)){
        //获得距离起始点路径最短的节点
        hold=getLabelShort(waitList,data);
        data[hold].visited=true;
        visited.push_back(hold);
        //更新所有临近节点里所包含的距离起始节点的最短路径数值
        neighboorCount=data[hold].node.road.size();
        for(int i=0;i<neighboorCount;++i){
            shortest=data[hold].shortest+data[hold].node.road[i].weight;
            neighboorhold=data[hold].node.road[i].notice;
            if(data[neighboorhold].shortest>shortest){
                data[neighboorhold].shortest=shortest;
                data[neighboorhold].preNode=hold;
            }
            if(!data[neighboorhold].visited&&!exist(neighboorhold,waitList)) waitList.push_back(neighboorhold);
        }
    }

    result solution;
    solution.totalWeight=data[hold].shortest;
    solution.order.push_back(hold);
    while(hold!=start){
        hold=data[hold].preNode;
        solution.order.push_back(hold);
    }
    std::reverse(solution.order.begin(),solution.order.end());

    return solution;
}

int getLabelShort(std::vector<int> &waitList,const std::vector<classicDijkstraNode> &data){
    double shortLine=data[waitList[0]].shortest;
    int take=waitList[0];
    for(int i=0;i<waitList.size();++i){
        if(shortLine>data[waitList[i]].shortest){
            shortLine=data[waitList[i]].shortest;
            take=waitList[i];
        }
    }
    for(int i=0;i<waitList.size();++i){
        if(waitList[i]==take){
            waitList.erase(waitList.begin()+i);// 删除节点
            break;
        }
    }
    return take;
}

bool exist(int neighboor,std::vector<int> waitList){
    bool right=false;
    for(int i=0;i<waitList.size();++i){
        if(neighboor==waitList[i]) right=true;
    }
    return right;
}
/*****************************展示结果****************************************************/
void showMeTheEnd(std::string name, bool switchRestriction,bool WeightOrStep, int iteratorTime){

    infoTxt info=readTexture(name);
    std::vector<nodeInfo> node;
    std::vector<nodeInfo> node2;
    int enter=0;
    std::chrono::duration<double> elapsed; //计算时间差
    if(WeightOrStep)node=initializeNode(info);
    else node=initializeLessPoint(info);

    result solution;
    if(!switchRestriction){
        std::cout<<node.size()<<"点 未加限制条件时最短路径信息"<<std::endl;
        std::vector<classicDijkstraNode> data=initializeClassic(node);
        int start =0;
        int end=data.size()-1;
        solution=Dijkstra(start,end,data);
        std::cout<<std::endl;
    }else{
        std::cout<<node.size()<<"点 带限制条件时最短路径信息\n迭代次数:"<<iteratorTime<<std::endl;
        auto start = std::chrono::high_resolution_clock::now();//记录起始时间
        std::vector<int> greenOrder=insertGreenNode(node,info.tagGreenPoint);
        std::vector<std::vector<int>> greenLineOrder=insertGreenLine(node,greenOrder,info.tagGreenLines);
        solution=calculateResult(node,greenOrder,greenLineOrder);
        auto finish = std::chrono::high_resolution_clock::now();//记录最后时间
        elapsed = finish - start; //计算时间差

        result solutionPre;

        int iterator=iteratorTime;
        while(iterator!=0){
            greenOrder=insertGreenNode(node,info.tagGreenPoint);
            greenLineOrder=insertGreenLine(node,greenOrder,info.tagGreenLines);
            solutionPre=calculateResult(node,greenOrder,greenLineOrder);
            if(solution.totalWeight>solutionPre.totalWeight) solution=solutionPre;
            iterator--;
        }
        /***************************************************************************/
        std::cout<<"绿点最短路径链表:"<<std::endl;
        enter=0;
        std::cout<<greenOrder[0];
        for(int i=1;i<greenOrder.size();++i){
            std::cout<<"->"<<greenOrder[i]<<" ";
            enter++;
            if(enter==15){
                std::cout<<std::endl;
                enter=0;
            }
        }
        std::cout<<std::endl;
        std::cout<<"绿点个数 "<<std::endl;
        std::cout<<greenOrder.size()<<std::endl;
        std::cout<<std::endl;

        /***************************************************************************/

        int upset,count;
        count=0;
        for(int i=0;i<greenLineOrder.size();++i){
            if(greenLineOrder[i].size()!=0){
                count++;
                upset=greenLineOrder[i].size()/2;
                std::cout<<greenOrder[i]<<"号绿点与"<<greenOrder[i+1]<<"号绿点间 ：";
                std::cout<<upset<<"段绿线"<<std::endl;
                std::cout<<"绿线编号 ：";
                for(int j=0;j<upset;++j){
                    std::cout<<greenLineOrder[i][j*2]<<" "<<greenLineOrder[i][j*2+1]<<std::endl;
                }
            }
        }
        std::cout<<"绿线段数 ："<<count<<std::endl;
        std::cout<<std::endl;
        /***************************************************************************/

        std::cout<<std::endl;
    }
    //========================================================
    std::cout<<"***************最终结果***************"<<std::endl;
    if(!WeightOrStep){
        std::cout<<"标准： 走的点数最少"<<std::endl;
        node2=initializeNode(info);
        solution=reconstruction(node2,solution.order);
    }
    else std::cout<<"标准： 总权重最小"<<std::endl;
    //========================================================
    if(solution.order.size()!=0){
        std::cout<<"最短路径一共经过： "<<solution.order.size()<<"个点"<<std::endl;
        std::cout<<"行程花费总计   ： "<<solution.totalWeight<<std::endl;   
        std::cout<<"路径详情:"<<std::endl;
        std::cout<<solution.order[0];
        enter=0;
        for(int i=1;i<solution.order.size();++i){
            std::cout<<" -> "<<solution.order[i];
            enter++;
            if(enter==12){
                std::cout<<std::endl;
                std::cout<<" ";
                enter=0;
            }
        }
        std::cout<<std::endl;
    }else
    {
        std::cout<<"抱歉，我走不到终点"<<std::endl;
    }
    std::cout<<"程序所用时间："<<elapsed.count()<<" s"<<std::endl;
}
/******************************************************************************/
/* 3号算法 绿点全部经过版本*/
/* Dijkstra漏点修补大法 */
std::vector<int> insertGreenNode(const std::vector<nodeInfo> &node,const std::vector<int> &greenList){
    std::srand( (unsigned)time(NULL) );
    unsigned int seed;

    std::vector<classicDijkstraNode> data;
    //输出路径信息及其初始化
    std::vector<int> waitList=greenList;
    std::vector<int> solution;
    result tmp;

    solution.push_back(waitList[0]);
    waitList.erase(waitList.begin());
    solution.push_back(waitList.back());
    waitList.pop_back();
    //开始插入

    int inter[]={-1,-1};
    int interEnd[]={-1,-1};
    std::vector<int>::iterator it;
    int takeIn=-1;
    int numChoose;
    double shortest=MAX_WEIGHT;
    double shortestSec=MAX_WEIGHT;
    double sumShort=MAX_WEIGHT;
    double takeShort=0;
    while(!waitList.empty()){
        seed=rand();
        std::srand(seed);
        numChoose=std::rand()%waitList.size();
        sumShort=MAX_WEIGHT;
        for(int i=0;i<solution.size();++i){
            data=initializeClassic(node);
            tmp=Dijkstra(solution[i],waitList[numChoose],data);
            shortest=tmp.totalWeight;
            inter[0]=i;

            shortestSec=MAX_WEIGHT;
            takeIn=inter[0]-1;
            //inter[1]=-100;
            if(takeIn>0){
                data=initializeClassic(node);
                tmp=Dijkstra(solution[takeIn],waitList[numChoose],data);
                if(shortestSec>tmp.totalWeight){
                    shortestSec=tmp.totalWeight;
                    inter[1]=takeIn;
                }
            }
            takeIn=inter[0]+1;
            if(takeIn<solution.size()){
                data=initializeClassic(node);
                tmp=Dijkstra(solution[takeIn],waitList[numChoose],data);
                if(shortestSec>tmp.totalWeight){
                    shortestSec=tmp.totalWeight;
                    inter[1]=takeIn;
                }
            }
            takeShort=shortest+shortestSec;
            if(sumShort>takeShort){
                sumShort=takeShort;
                interEnd[0]=inter[0];
                interEnd[1]=inter[1];
            }
        }
        //it=solution.begin();
        if(interEnd[0]<interEnd[1]) solution.insert(solution.begin()+interEnd[1],waitList[numChoose]);
        else solution.insert(solution.begin()+interEnd[0],waitList[numChoose]);
        waitList.erase(waitList.begin()+numChoose);
    }
    return solution;
}
std::vector<std::vector<int>> insertGreenLine(const std::vector<nodeInfo> &node,const std::vector<int> &solution,const std::vector<std::array<int,2>> &greenLines){
    std::vector<classicDijkstraNode> data;
    result tmp;
    //输出路径信息及其初始化
    std::vector<std::vector<int>> waitZone(solution.size()-1);

    std::vector<int>::iterator it;
    bool tagInert=false;
    double shortPre;
    double shortPreSec;
    int upset;
    int inter[]={-1,-1};
    int interSec[]={-1,-1};
    int takeIn;
    double shortest;
    double sumShort;
    double regle;
    for(int j=0;j<greenLines.size();++j){
        //01
        shortest=MAX_WEIGHT;
        sumShort=0;
        for(int i=0;i<solution.size();++i){
            data=initializeClassic(node);
            tmp=Dijkstra(solution[i],greenLines[j][0],data);
            if(shortest>tmp.totalWeight){
                shortest=tmp.totalWeight;
                inter[0]=i;
            }
        }
        shortPre=shortest;
        sumShort+=shortest;
        shortest=MAX_WEIGHT;
        takeIn=inter[0]-1;
        //inter[1]=-1;
        if(takeIn>0){
            data=initializeClassic(node);
            tmp=Dijkstra(solution[takeIn],greenLines[j][1],data);
            if(shortest>tmp.totalWeight){
                shortest=tmp.totalWeight;
                inter[1]=takeIn;
            }
        }
        takeIn=inter[0]+1;
        if(takeIn<solution.size()){
            data=initializeClassic(node);
            tmp=Dijkstra(solution[takeIn],greenLines[j][1],data);
            if(shortest>tmp.totalWeight){
                shortest=tmp.totalWeight;
                inter[1]=takeIn;
            }
        }
        if(inter[0]>inter[1]) shortPre=shortest;//永远取绿线前端点距离前端绿点的最短距离
        sumShort+=shortest;
        regle=sumShort;
        //10
        shortest=MAX_WEIGHT;
        sumShort=0;
        for(int i=0;i<solution.size();++i){
            data=initializeClassic(node);
            tmp=Dijkstra(solution[i],greenLines[j][1],data);
            if(shortest>tmp.totalWeight){
                shortest=tmp.totalWeight;
                interSec[0]=i;
            }
        }
        shortPreSec=shortest;
        sumShort+=shortest;
        shortest=MAX_WEIGHT;
        takeIn=interSec[0]-1;
        //interSec[1]=-1;
        if(takeIn>0){
            data=initializeClassic(node);
            tmp=Dijkstra(solution[takeIn],greenLines[j][0],data);
            if(shortest>tmp.totalWeight){
                shortest=tmp.totalWeight;
                interSec[1]=takeIn;
            }
        }
        takeIn=interSec[0]+1;
        if(takeIn<solution.size()){
            data=initializeClassic(node);
            tmp=Dijkstra(solution[takeIn],greenLines[j][0],data);
            if(shortest>tmp.totalWeight){
                shortest=tmp.totalWeight;
                interSec[1]=takeIn;
            }
        }
        if(interSec[0]>interSec[1]) shortPreSec=shortest;
        sumShort+=shortest;


        if(sumShort>regle){
            if(inter[0]<inter[1]){
                if(waitZone[inter[0]].size()==0){
                    waitZone[inter[0]].push_back(greenLines[j][0]);
                    waitZone[inter[0]].push_back(greenLines[j][1]);
                }else{
                    upset=waitZone[inter[0]].size()/2;
                    tagInert=false;
                    for(int au=0;au<upset;++au){
                        data=initializeClassic(node);
                        tmp=Dijkstra(waitZone[inter[0]][2*au],solution[inter[0]],data);
                        if(shortPre<tmp.totalWeight){
                            //it=waitZone[inter[0]].begin();
                            waitZone[inter[0]].insert(waitZone[inter[0]].begin()+2*au,greenLines[j][1]);//std::cout<<"1 "<<greenLines[j][1]<<std::endl;
                            waitZone[inter[0]].insert(waitZone[inter[0]].begin()+2*au,greenLines[j][0]);//std::cout<<"2 "<<greenLines[j][0]<<std::endl;
                            tagInert=true;
                            break;
                        }
                    }
                    if(!tagInert){
                        waitZone[inter[0]].push_back(greenLines[j][0]);
                        waitZone[inter[0]].push_back(greenLines[j][1]);
                    }
                }
            }
            else {
                if(waitZone[inter[1]].size()==0){
                    waitZone[inter[1]].push_back(greenLines[j][1]);
                    waitZone[inter[1]].push_back(greenLines[j][0]);
                }else{
                    upset=waitZone[inter[1]].size()/2;
                    tagInert=false;
                    for(int au=0;au<upset;++au){
                        data=initializeClassic(node);
                        tmp=Dijkstra(waitZone[inter[1]][2*au],solution[inter[1]],data);
                        if(shortPre<tmp.totalWeight){
                            //it=waitZone[inter[1]].begin();
                            waitZone[inter[1]].insert(waitZone[inter[1]].begin()+2*au,greenLines[j][0]);//std::cout<<"3 "<<greenLines[j][0]<<std::endl;
                            waitZone[inter[1]].insert(waitZone[inter[1]].begin()+2*au,greenLines[j][1]);//std::cout<<"4 "<<greenLines[j][1]<<std::endl;
                            tagInert=true;
                            break;
                        }
                    }
                    if(!tagInert){
                        waitZone[inter[1]].push_back(greenLines[j][1]);
                        waitZone[inter[1]].push_back(greenLines[j][0]);
                    }
                }
            }
        }
        else{
            if(interSec[0]<interSec[1]){
                if(waitZone[interSec[0]].size()==0){
                    waitZone[interSec[0]].push_back(greenLines[j][1]);
                    waitZone[interSec[0]].push_back(greenLines[j][0]);
                }else{
                    upset=waitZone[interSec[0]].size()/2;
                    tagInert=false;
                    for(int au=0;au<upset;++au){
                        data=initializeClassic(node);
                        tmp=Dijkstra(waitZone[interSec[0]][2*au],solution[interSec[0]],data);
                        if(shortPre<tmp.totalWeight){
                            //it=waitZone[interSec[0]].begin();
                            waitZone[interSec[0]].insert(waitZone[interSec[0]].begin()+2*au,greenLines[j][0]);//std::cout<<"5 "<<greenLines[j][0]<<" "<<waitZone[interSec[0]][2*au]<<std::endl;
                            waitZone[interSec[0]].insert(waitZone[interSec[0]].begin()+2*au,greenLines[j][1]);//std::cout<<"6 "<<greenLines[j][1]<<" "<<waitZone[interSec[0]][2*au]<<std::endl;
                            tagInert=true;
                            break;
                        }
                    }
                    if(!tagInert){
                        waitZone[interSec[0]].push_back(greenLines[j][1]);
                        waitZone[interSec[0]].push_back(greenLines[j][0]);
                    }
                }
            }
            else {
                if(waitZone[interSec[1]].size()==0){
                    waitZone[interSec[1]].push_back(greenLines[j][0]);
                    waitZone[interSec[1]].push_back(greenLines[j][1]);
                }else{
                    upset=waitZone[interSec[1]].size()/2;
                    tagInert=false;
                    for(int au=0;au<upset;++au){
                        data=initializeClassic(node);
                        tmp=Dijkstra(waitZone[interSec[1]][2*au],solution[interSec[1]],data);
                        if(shortPre<tmp.totalWeight){
                            //it=waitZone[interSec[1]].begin();
                            waitZone[interSec[1]].insert(waitZone[interSec[1]].begin()+2*au,greenLines[j][1]);//std::cout<<"7 "<<greenLines[j][1]<<" "<<waitZone[interSec[1]][2*au]<<std::endl;
                            waitZone[interSec[1]].insert(waitZone[interSec[1]].begin()+2*au,greenLines[j][0]);//std::cout<<"8 "<<greenLines[j][0]<<" "<<waitZone[interSec[1]][2*au]<<std::endl;
                            //if(waitZone[interSec[1]][2*au]!=greenLines[j][0])waitZone[interSec[1]][2*au]=greenLines[j][0];
                            tagInert=true;
                            break;
                        }
                    }
                    if(!tagInert){
                        waitZone[interSec[1]].push_back(greenLines[j][0]);
                        waitZone[interSec[1]].push_back(greenLines[j][1]);
                    }
                }
            }
        }
    }
    //************************冲突绿线报警****************************
/*
    takeIn=0;
    for(int i=0;i<waitZone.size();++i){
        if(waitZone[i].size()>3){
            upset=waitZone[i].size()/2;
            std::cout<<i<<"号空隙出现"<<upset<<"段绿线冲突"<<std::endl;
            takeIn++;
        }

    }
    if(takeIn!=0)std::cout<<takeIn<<"个空隙出现绿线冲突情况，此结果可能不是最优"<<std::endl;
    else std::cout<<"很幸运，此地图未出现绿线冲突"<<std::endl;
    */
    return waitZone;
}

result calculateResult(const std::vector<nodeInfo> &node,const std::vector<int> &greenNodeInfo,const std::vector<std::vector<int>> &greenLineInfo){
    std::vector<classicDijkstraNode> data;
    result tmp;
    result solution;
    solution.totalWeight=0;
    //data=initializeClassic(node);
    //tmp=Dijkstra(solution[i],greenLines[j][0],data);

    int takePre,takeAf;
    int upset;
    takePre=greenNodeInfo[0];
    solution.order.push_back(takePre);
    for(int i=0;i<greenLineInfo.size();++i){
        if(greenLineInfo[i].size()!=0){
            upset=greenLineInfo[i].size()/2;
            for(int j=0;j<upset;++j){
                takeAf=greenLineInfo[i][j*2];
                data=initializeClassic(node);
                tmp=Dijkstra(takePre,takeAf,data);
                solution.totalWeight+=tmp.totalWeight;
                for(int k=1;k<tmp.order.size();++k){
                    solution.order.push_back(tmp.order[k]);
                }
                for(int k=0;k<node[takeAf].road.size();++k){
                    if(node[takeAf].road[k].notice==greenLineInfo[i][j*2+1]){
                        solution.totalWeight+=node[takeAf].road[k].weight;
                        solution.order.push_back(greenLineInfo[i][j*2+1]);
                        takePre=greenLineInfo[i][j*2+1];
                        break;
                    }
                }
            }
        }
        takeAf=greenNodeInfo[i+1];
        data=initializeClassic(node);
        tmp=Dijkstra(takePre,takeAf,data);
        solution.totalWeight+=tmp.totalWeight;
        for(int k=1;k<tmp.order.size();++k){
            solution.order.push_back(tmp.order[k]);
        }
        takePre=greenNodeInfo[i+1];
    }
    return solution;

}

/**************************************************************************************/
result reconstruction(const std::vector<nodeInfo> &node,const std::vector<int> list){
    result solution;
    solution.totalWeight=0;
    solution.order=list;
    int take=list[0];
    for(int i=1;i<list.size();++i){
        for(int j=0;j<node[take].road.size();++j){
            if(node[take].road[j].notice==list[i]){
                solution.totalWeight+=node[take].road[j].weight;
                break;
            }
        }
        take=list[i];
    }
    return solution;
}
