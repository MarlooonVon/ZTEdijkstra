#ifndef DEDIGN_H
#define DESIGN_H
#include <vector>

using std::vector;
void design (vector<vector<int> > &map, int &VertixNum, vector<int> &parent_v, int &src, int &des, int &distance, int &cnt, int &green_vNum, int &green_eNum, vector<int> &greenVertix, vector<vector<int> > &green_ev, vector<int> &tag_isaddgreenv)
{
	for (int i = green_vNum - 1; i >= 0 ; i--)
	{	

		bool in = false;
		if (!tag_isaddgreenv[greenVertix[i]])
		{
			for (auto a : parent_v)
			{
				
				if ((i > 0) && (a == greenVertix[i - 1]))
				{
					in = true;
					break;
				}
			}
		}
			if (in) 
			{	
				
				continue;
			}
		
		dij (map, VertixNum, parent_v, src, greenVertix[i], distance, cnt);
		
		if(tag_isaddgreenv[greenVertix[i]])
				{
					if (parent_v[parent_v.size() - 1] == green_ev[greenVertix[i] + green_eNum - VertixNum][0])
					{	
						
						src = green_ev[greenVertix[i] + green_eNum - VertixNum][1];
					}
					
					if (parent_v[parent_v.size() - 1] == green_ev[greenVertix[i] + green_eNum - VertixNum][1])
					{
						src = green_ev[greenVertix[i] + green_eNum - VertixNum][0];
					}
					continue;
				}
		
		src = greenVertix[i];
	}
	dij (map, VertixNum, parent_v, src, des, distance, cnt);
}
#endif