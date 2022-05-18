#include <iostream>
#include <string.h>	

#include "lex_ana.h"
//using namespace std;

#define FILEPATH "test.sy"
std::string File_str;	//读取文件内容后存放字符串// 
char FilePath[1024];	//文件路径// 
std::vector<std::vector<Token>> ve ; //定义一个二维vector，用来保存token，每以层vector代表一行// 	这个需要放到main函数里面，不然makefile的时候会出现重复定义// 

extern int lines;
void debug_LexAbalyze(){
	for(int i = 1;i<=lines;i++){
		if(ve[i].size() == 1){
			std::cout<<"lines ："<<i<<"\t\t\t"<<"empty line..."<<std::endl;
			continue;
		}
		for(int j = 1;j<ve[i].size();j++){
			std::cout<<"lines ："<<i<<"\t\t\t"<<"rule: "<<ve[i][j].rule<<"\t\t"<<"alToken:"<<"\t"<<ve[i][j].alToken<<std::endl;
		}
	}
		
}

int main(){
	
	std::cout<<"输入文件路径以及名称:"<<std::endl;
	std::cin>>FilePath;
	std::cout<<"开始工作"<<std::endl;
	
	if(!ReadFileToString(FilePath)){
		std::cout<<"ReadFile Wrong!!!\n";
	}
	std::cout<<"源程序如下:\n";
	std::cout<<File_str<<std::endl;	
	
	//词法分析//
	std::cout<<"词法分析如下"<<std::endl;
	if(!LexAnalyze()){
		std::cout<<"Lex_Analyze Error"<<std::endl;
	}
	debug_LexAbalyze();
	
	return 0;
	
}
