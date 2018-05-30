#ifndef DIJ_H
#define DIJ_H

#include <vector>
#include <stdio.h>
#define MAX 5000
using std::vector;
void dij (vector<vector<int> > &map, int &VertixNum, vector<int> &parent_v, int &src, int &des, int &distance, int &cnt)
{
	int parent[VertixNum] = {0};
	vector<int> pare;
	vector <int> dis(MAX);
	vector <int> vis(MAX);
	int min = 0;
	int u;
	//初始化dis数组,表示起点到其余各个点的最短路径
	for (int i = 0; i < VertixNum; i++)
	dis[i] = map[src][i];
	//初始化vis数组
	for (int i = 0; i < VertixNum; i++)
	vis[i] = 0;
	vis[src] = 1; //起点已经被访问过了
	//dijkstra算法核心
	for (int i = 0; i < VertixNum; i++)
		{	
			min = inf;//先假设起始号点到其他点的最小距离是非常大的（无穷大）
			for (int j = 1; j < VertixNum; j++)
			{	
				if (vis[j] == 0 && dis[j] < min)
				{
					min = dis[j];
					u = j;
				}
			}
			vis[u] = 1;
			for (int v = 0; v < VertixNum; v++)
			{
				if (map[u][v] < inf)
					if (dis[u] + map[u][v] < dis[v])
						{	
						dis[v] = dis[u] + map[u][v];
						parent[v] = u;
						}
			}
			
		}
				
				int p = parent [des];
				int parentcnt = 0;
				
				
				parent_v.push_back (src);
				cnt++;
				while (p)
				{	
					++parentcnt; 
					pare.push_back (p);
					p = parent[p];
				}
				
				cnt += parentcnt;
	/*printf ("点数%d\n",parentcnt);
	printf ("最短路径是：\n");
				printf ("%d>>",src);*/
	
				while (parentcnt)
				{
					//printf("%d>>", pare[parentcnt - 1]);
					parent_v.push_back (pare[parentcnt - 1]);
					--parentcnt;
				}
	/*printf ("%d\n",des);
				printf("最小花费：\n");
				printf ("%d\n", dis[des]);
	*/
		distance += dis[des];
		pare.clear ();
}
#endif
