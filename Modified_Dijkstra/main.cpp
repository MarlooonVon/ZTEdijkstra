#include "design.h"

int main()
{
    auto start = std::chrono::high_resolution_clock::now();//记录起始时间
    /*展示拓扑结构*/
    std::string name="case1.txt";
    infoTxt info=readTexture(name);
    double complex=(double)info.numLine/(double)info.numPoint;//计算拓扑复杂度
    if(complex>3.5&&(info.numLine>2000||info.numPoint>750)) std::cout<<"你好,这张拓扑图的拓扑结构复杂，所以建议迭代次数不要过多，否则需要时间会很长"<<std::endl;

    //std::vector<nodeInfo> node=initializeNode(info);
    //showMeTheTopology(node);  // 展示生成的拓扑结构信息
   /*****************************************************************/
    bool switchRestriction=true;
    bool WeightOrStep=true; // weight Smallest true; step Smallest false
    int iteratorTime=100;
    showMeTheEnd(name,switchRestriction,WeightOrStep,iteratorTime);
    /*****************************************************************/
    auto finish = std::chrono::high_resolution_clock::now();//记录最后时间
    std::chrono::duration<double> elapsed = finish - start; //计算时间差
    std::cout<<std::endl;std::cout<<std::endl;std::cout<<std::endl;
    std::cout<<"程序所用时间："<<elapsed.count()<<" s"<<std::endl;
    return 0;
}

/*
std::cout<<"绿点个数 "<<info.greenPoint<<std::endl;
std::cout<<"绿线个数 "<<info.greenLine<<std::endl;
std::cout<<"红线个数 "<<info.redLine<<std::endl;
std::cout<<"绿线例子 "<<info.tagGreenLines[0][0]<<" "<<info.tagGreenLines[0][1]<<std::endl;


    std::vector<int> greenOrder=insertGreenNode(node,info.tagGreenPoint);
    std::cout<<"<-绿点最短路径 "<<std::endl;
    for(int i=0;i<greenOrder.size();++i){
        std::cout<<"->"<<greenOrder[i]<<" ";
    }
    std::cout<<std::endl;
    std::cout<<"绿点个数 "<<std::endl;
    std::cout<<greenOrder.size()<<std::endl;

    std::vector<std::vector<int>> greenLineOrder=insertGreenLine(node,greenOrder,info.tagGreenLines);
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

*/
