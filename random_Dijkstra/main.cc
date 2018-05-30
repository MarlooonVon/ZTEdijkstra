#include <stdio.h>
#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <chrono>
#include <vector>
#include <algorithm>
#include "io.h"
#include "dij.h"
#include "design.h"

#define MAX 5000

using std::vector;

int main ()
{	
	int round;
	int caseNum;
	printf("请输入你想读取的拓扑（输入case编号）：\n0.case0 1.case1\n");
	scanf("%d", &caseNum);
	if ( caseNum != 1 && caseNum != 0) 
	{printf("输入错误.\n");
	 return 0;
	}
	printf("请输入你想调用的随机次数：");
	scanf("%d", &round);
	int goal;
	printf("请输入你想要的到的解的类型（1或者2）：\n 1.距离最小 2.点数最少\n");
	scanf("%d", &goal);
	if (goal != 1 && goal != 2) 
	{printf("输入错误.\n");
	 return 0;
	}
	auto start_time = std::chrono::high_resolution_clock::now();
	
	srand ((unsigned)time(NULL));
	
	vector<vector<int> > map (MAX, vector<int> (MAX));
	vector<int> greenVertix;
	vector<vector<int> > green_ev (MAX, vector<int> (3));
	vector<int> parent_v;
	vector<int> tag_isaddgreenv (MAX,0);
	int limitsteps;
	vector<int> answerlist;
	int mindis, leaststep;
	
	
	int distance = 0;
	int cnt = 1;

	int VertixNum, green_vNum, green_eNum;

	if(!caseNum)
	{
		read_file ("case0.txt", map, VertixNum, green_vNum, green_eNum, green_ev, greenVertix, tag_isaddgreenv, limitsteps);
	}
	if(caseNum)
	{
		read_file ("case1.txt", map, VertixNum, green_vNum, green_eNum, green_ev, greenVertix, tag_isaddgreenv, limitsteps);
	}
	int src = 0, des = VertixNum- green_eNum -1;
	design (map, VertixNum, parent_v, src, des, distance, cnt, green_vNum, green_eNum, greenVertix, green_ev, tag_isaddgreenv);
	mindis = distance;
	leaststep = cnt;
	for (int i = 0; i < parent_v.size(); i++)
	{
		answerlist.push_back(parent_v[i]);
	}
	
	if (goal - 1) //点数最少
	{
	while (round)
		{
			random_shuffle(greenVertix.begin(), greenVertix.end());
			src = 0;
			cnt = 1;
			distance = 0;
			parent_v.clear();
			design (map, VertixNum, parent_v, src, des, distance, cnt, green_vNum, green_eNum, greenVertix, green_ev, tag_isaddgreenv);
			if (cnt <= leaststep)  
			{
				answerlist.clear();
				leaststep = cnt;
				mindis = distance;
				for (int i = 0; i < parent_v.size(); i++)
				{
					answerlist.push_back(parent_v[i]);
				}
			}
			round --;
		}
	}
	if (!(goal - 1))//距离最小
	{
		while (round)
		{
			random_shuffle(greenVertix.begin(), greenVertix.end());
			src = 0;
			cnt = 1;
			distance = 0;
			parent_v.clear();
			design (map, VertixNum, parent_v, src, des, distance, cnt, green_vNum, green_eNum, greenVertix, green_ev, tag_isaddgreenv);
			if (distance <= mindis)  
			{	answerlist.clear();
				leaststep = cnt;
				mindis = distance;
				for (int i = 0; i < parent_v.size(); i++)
				{
					answerlist.push_back(parent_v[i]);
				}
			}
			round --;
		}
	}
		
	if (leaststep <= limitsteps)
	{
		printf("满足条件优解为：\n");
	}
	else printf("限制条件下找不到优解，推荐次优解：\n");
	printf ("最短路径是：\n");
	
		for (auto a:answerlist)
		{
			printf ("%d->", a);
		}
		printf ("%d\n", des);
	
	
	printf ("点数总计：%d\n", leaststep);
	printf ("费用总计：%d\n", mindis);
	
	auto finish_time = std::chrono::high_resolution_clock::now();//记录最后时间
	std::chrono::duration<double> elapsed = finish_time - start_time; //计算时间差
	std::cout << elapsed.count() << std::endl;
	return 0;
}
