#ifndef IO_H
#define IO_H

#include <stdio.h>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

using std::ifstream;
using std::istringstream;
using std::string;
using std::vector;

const int inf = 1<<28; //非常大的一个数字

void read_file ( const char * filename, vector<vector<int> > &map,int &VertixNum, int &green_vNum, int &green_eNum, vector<vector<int> > &green_ev, vector<int> &greenVertix, vector<int> &tag_isaddgreenv, int &limitsteps)
{
	int EdgeNum, red_eNum;
	int v1, v2, w;
	
	string line;
	//读文件
	ifstream input (filename);
	getline (input, line);
	istringstream firstLine (line);
	//读取第一行拓扑信息
	firstLine >> VertixNum >> EdgeNum >> green_vNum >> green_eNum >> red_eNum >> limitsteps;
	int red_e[red_eNum][2];
	//初始化点距离信息
	for (int i = 0; i < VertixNum; i++)
	{
		for (int j = 0; j < VertixNum; j++)
		{	
			if (j == i)
				map[i][j] = 0;
			else 
				map[i][j] = inf;
		}
	}
	//将边信息读入邻接矩阵
	for (int i = 0; i < EdgeNum; i++)
	{	
		getline (input, line);
		istringstream edgeLine(line);
		edgeLine >> v1 >> v2 >> w;
		map[v1][v2] = w;
		map[v2][v1] = w;
	}

	//读取绿点
	getline (input, line);
	int green_v;
	istringstream greenvLine (line);
	for (int i = 0; i < green_vNum; i++)
	{
		greenvLine >> green_v;
		greenVertix.push_back(green_v);
		//tag_isaddgreenv[green_v] = 0;
	}
	//读取绿边
	for (int i = 0; i < green_eNum; i++)
	{	
		getline (input, line);
		istringstream greeneLine (line);
		greeneLine >> v1 >> v2;
		//green_ev[i][0] = v1;
		//green_ev[i][1] = v2;
		//在绿边中间加一个点,初始化这个点
		for (int j = 0; j <= VertixNum; j++)
		{	
			if (j == VertixNum)
				map[VertixNum][j] = 0;
			else 
				map[VertixNum][j] = inf;
				map[j][VertixNum] = inf;
		}
		//到并将这个点到绿边一个端点的权重设置为绿边原来的权重
		map[v1][VertixNum] = map[v1][v2];
		map[VertixNum][v1] = map[v1][v2];
		map[v2][VertixNum] = map[v1][v2];
		map[VertixNum][v2] = map[v1][v2];
		green_ev[i][0] = v1;
		green_ev[i][1] = v2;
		green_ev[i][2] = map[v1][v2];
		greenVertix.push_back (VertixNum);
		tag_isaddgreenv[VertixNum] = 1;
		green_vNum++;
		VertixNum++;
	}
	//读取红边
	for (int i = 0; i < red_eNum; i++)
	{	
		getline (input, line);
		istringstream redeLine (line);
		redeLine >> v1 >> v2;
		red_e[i][0] = v1;
		red_e[i][1] = v2;
		map[v1][v2] = inf;
		map[v2][v1] = inf;//将红边权重设为无穷大
	}
	input.close();
}
#endif
