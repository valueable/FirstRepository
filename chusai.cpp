#include<iostream>
#include<vector>
#include<cstring>
#include<algorithm>
#include<fstream> 
using namespace std;
const int maxn=300000;

struct edge{
	int to;
	int length;
	edge(int t,int l):to(t),length(l){}
}; 
vector<string> route;
vector<edge> graph[maxn];
bool visit[maxn];
int fr[maxn];
int rs=0;
vector<int> sk;
int totalmoney[maxn];
bool search(int s,int count,int tmps,string str,int total){
	if(count>=3&&s==tmps){
		for(int i=0;i<rs;i++){
			if(totalmoney[i]==total-s) return false;
		}
		route.push_back(str.substr(0,str.size()-to_string(s).size()-1));
		totalmoney[rs]=total-s;
		rs++;
		return true;
	}
	if(count>=7) return false;
	bool flag=false;
	for(int i=0;i<graph[tmps].size();i++){
		int v=graph[tmps][i].to;
		if(count<2&&v==s){
			continue;
		}
		if(visit[v]&&v!=s) continue; 
		visit[tmps]=true;
		string tmpstr=str;
		string s1=','+to_string(v);
		str+=s1;
		//cout<<str<<endl;
	    flag=search(s,count+1,v,str,total+v);
	    for(int i=0;i<maxn;i++){
    	   visit[i]=false;
	    }
	    str=tmpstr;
		
	}
	if(flag) return true;
	return false;
} 
bool cmp(string str,string s){
	int c1=0;
	int c2=0;
	int index=0;
	while ((index = str.find(',', index)) < str.length())
	{
		c1++;
		index++;
	}
	index=0;
	while ((index = s.find(',', index)) < s.length())
	{
		c2++;
		index++;
	}
	if(c1==c2){
		int s0=0;
	    int s2=0;
	    while(1){
	    	
	    	string str1=str.substr(s0,str.find(',',s0));
	    	s0=s.find(',',s0)+1;
	    	string s1=s.substr(s2,s.find(',',s2));
	    	s2=s.find(',',s2)+1;
	    	if(str1!=s1){
	    		if(str1.size()==s1.size()){
	    			return str1<s1;
				}
				return str1.size()<s1.size();
			}
		}
		
	}
	return c1<c2;
}
int main(){
    memset(fr,0,sizeof(fr));
	int cases=5030;
	FILE *fp;
	fp=fopen("test_data.txt","r");
	while(!feof(fp)){
		int from,to,mo;
		fscanf(fp,"%d,%d,%d",&from,&to,&mo);
		graph[from].push_back(edge(to,mo));
		fr[from]++;
	}
	fclose(fp);
	cout<<"ok"<<endl;
	/*while(cases--){
		int from,to,mo;
		scanf("%d,%d,%d",&from,&to,&mo);
		graph[from].push_back(edge(to,mo));
		fr[from]++;
	}*/
    for(int i=0;i<maxn;i++){
    	visit[i]=false;
	}
	//cout<<fr[1]<<endl;
	//cout<<"hi"<<endl; 
	for(int i=0;i<maxn;i++){
		if(fr[i]==0) continue;
		else{
			sk.push_back(i);
			bool flag=search(i,0,i,to_string(i),i);
		    for(int j=0;j<sk.size();j++) visit[j]=true;
		}
	}
	cout<<rs<<endl;
	ofstream out;
	out.open("result.txt", ios::out);
	out<<rs<<endl;
	sort(route.begin(),route.end(),cmp);
	for(int i=0;i<rs;i++){
		//cout<<route[i]<<endl;
		out<<route[i]<<endl;
	}
	out.close();
	cout<<"finish"<<endl;
	
	
	return 0;
}
/*
56
18,197,56
23,179,121
24,159,83
26,214,198
27,144,126
58,164,149
61,188,139
64,128,231
65,67,205
91,223,94
94,145,234
94,237,114
150,194,192
158,295,175
255,271,296
208,375,447,383
222,227,582,325
234,505,413,485
242,440,434,476
259,409,299,558
272,593,300,546
293,528,460,587
303,395,500,542
338,564,501,382
437,572,501,456
1627,2196,2112,1655
6002,6003,6007,6006
513,1226,1160,521,1245
551,569,748,708,575
614,777,675,755,699
628,1077,1143,826,757
652,1190,1129,993,961
745,1124,1066,799,835
877,1041,1054,903,996
1010,1129,1067,1163,1162
1005,1359,2246,1436,1594,1375
1050,1661,1181,1999,1966,2287
1115,2393,2043,2276,1466,1889
1131,1780,1627,2196,2112,1630
1192,1755,2061,2142,2027,2171
1195,1931,2354,1697,2099,1574
1359,2391,1763,2112,1655,1627
1436,1710,2113,2165,2250,2052
1609,1776,1707,2414,1782,1703
6001,6002,6003,6007,6006,6005
6002,6003,6004,6008,6007,6006
2311,2824,4463,3871,3926,3610,4892
2315,4836,3024,3789,2418,4685,4996
2323,3967,2515,3059,4589,4785,3902
2375,2504,3275,4338,2803,4258,2619
2395,2541,2633,4954,3847,4426,4898
2563,3761,3196,3635,3586,4098,4407
2651,3516,4699,4210,3055,3004,3367
2666,4459,3708,3490,2934,3453,4281
2921,3541,3574,3742,3488,2990,4147
3454,3480,4589,4924,3930,4075,4671
*/ 
