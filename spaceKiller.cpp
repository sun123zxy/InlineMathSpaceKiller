#include<cstdio>
#include<cstring>
#include<iostream>
#include<vector>
#include<stack>
using namespace std;

string ifile,ofile;

string in;int iLen;
bool isVerbose;
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
		if(in[i]=='$'){
			if(inside){
				inside=0;
				if(stk.top()+1!=i){ //ignore display math
					lp.push_back(stk.top());
					rp.push_back(i);
					if(isVerbose){
						printf("%d: ",pN);
						for(int k=stk.top();k<=i;k++) printf("%c",in[k]);
						printf("\n");
					}
					pN++;
				}
				stk.pop();
			}else{
				inside=1;
				stk.push(i);
			}
		}
	}
}
void Kill(){
	notPick.resize(iLen);
	for(int i=0;i<pN;i++){
		if(isVerbose) printf("%d: ...",i);
		int cnt=0;
		int l=lp[i],r=rp[i];
		for(int j=1;l+j<iLen&&in[l+j]==' ';j++) notPick[l+j]=1,cnt++;
		for(int j=1;r-j>=0  &&in[r-j]==' ';j++) notPick[r-j]=1,cnt++;
		if(isVerbose) printf(" | %d space killed\n",cnt);
	}
}
void WriteOut(){
	freopen(ofile.c_str(),"w",stdout);
	for(int i=0;i<iLen;i++){
		if(!notPick[i]) cout.put(in[i]);
	}
	freopen("CON","w",stdout);
}
void WrongUsage(){
	printf("Usage: spaceKiller <inputFile> [-o <outputFile>|--overwrite] [--verbose]\n");
	exit(0);
}
int main(int argc,char *argv[]){
	if(argc==1) WrongUsage();
	ifile=argv[1];
	ofile="output.md";
	isVerbose=0;
	for(int i=2;i<argc;i++){
		string str=string(argv[i]);
		if(str=="--verbose") isVerbose=1;
		else if(str=="--overwrite") ofile=ifile;
		else if(str=="-o"){ofile=string(argv[++i]);}
		else WrongUsage();
	}
	printf("----->\n");
	printf(("Reading \""+ifile+"\"...\n").c_str());
	ReadIn();
	printf("Analyzing...\n");
	GetP();
	printf("Killing...\n");
	Kill();
	printf(("Writing as \""+ofile+"\"...\n").c_str());
	WriteOut();
	printf("Done\n");
	printf("<-----\n");
	return 0;
}
