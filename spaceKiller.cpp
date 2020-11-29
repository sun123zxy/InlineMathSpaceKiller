#include<cstdio>
#include<cstring>
#include<iostream>
#include<vector>
#include<stack>
using namespace std;

string ifile,ofile;

string in;int iLen;
void ReadIn(){
	freopen(ifile.c_str(),"r",stdin);
	in="";
	char c;while((c=getchar())!=EOF){in+=c;}
	iLen=in.length();
}
vector<int> lp,rp;int pN;
vector<bool> notPick;
stack<int> stk;
void GetP(){
	bool inside=0;
	pN=0;
	for(int i=0;i<iLen;i++){
		if((i-1>=0?(in[i-1]!='$'):1)&&in[i]=='$'&&(i+1<iLen?(in[i+1]!='$'):1)){
			if(inside){
				inside=0;
				pN++;
				lp.push_back(stk.top());
				rp.push_back(i);
				stk.pop();
			}else{
				inside=1;
				stk.push(i);
			}
		}
	}
}
void Work(){
	notPick.resize(iLen);
	for(int i=0;i<pN;i++){
		int l=lp[i],r=rp[i];
		for(int j=1;l+j<iLen&&in[l+j]==' ';j++) notPick[l+j]=1;
		for(int j=1;r-j>=0  &&in[r-j]==' ';j++) notPick[r-j]=1;
	}
}
void WriteOut(){
	freopen(ofile.c_str(),"w",stdout);
	for(int i=0;i<iLen;i++){
		if(!notPick[i]) cout.put(in[i]);
	}
}
int main(int argc,char *argv[]){
	if(argc>=2){
		ifile=argv[1];
		ofile="output.md";
		if(argc>=3){
			if(string(argv[2])=="-o"||string(argv[2])=="--overwrite")
				ofile=ifile;
			else ofile=argv[2];
		}
	}else{
		printf("Usage: spaceKiller [inputFlie] [outputFile/-o/--overwrite]\n");
		return 0;
	}
	
	printf("Reading...\n");
	ReadIn();
	printf("Analyzing...\n");
	GetP();
	Work();
	printf("Writing...\n");
	WriteOut();
	return 0;
}
