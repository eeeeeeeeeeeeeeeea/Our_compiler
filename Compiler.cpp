#include <iostream>
#include <string.h>	

#include "lex_ana.h"
//using namespace std;

#define FILEPATH "test.sy"
std::string File_str;	//��ȡ�ļ����ݺ����ַ���// 
char FilePath[1024];	//�ļ�·��// 
std::vector<std::vector<Token>> ve ; //����һ����άvector����������token��ÿ�Բ�vector����һ��// 	�����Ҫ�ŵ�main�������棬��Ȼmakefile��ʱ�������ظ�����// 

extern int lines;
void debug_LexAbalyze(){
	for(int i = 1;i<=lines;i++){
		if(ve[i].size() == 1){
			std::cout<<"lines ��"<<i<<"\t\t\t"<<"empty line..."<<std::endl;
			continue;
		}
		for(int j = 1;j<ve[i].size();j++){
			std::cout<<"lines ��"<<i<<"\t\t\t"<<"rule: "<<ve[i][j].rule<<"\t\t"<<"alToken:"<<"\t"<<ve[i][j].alToken<<std::endl;
		}
	}
		
}

int main(){
	
	std::cout<<"�����ļ�·���Լ�����:"<<std::endl;
	std::cin>>FilePath;
	std::cout<<"��ʼ����"<<std::endl;
	
	if(!ReadFileToString(FilePath)){
		std::cout<<"ReadFile Wrong!!!\n";
	}
	std::cout<<"Դ��������:\n";
	std::cout<<File_str<<std::endl;	
	
	//�ʷ�����//
	std::cout<<"�ʷ���������"<<std::endl;
	if(!LexAnalyze()){
		std::cout<<"Lex_Analyze Error"<<std::endl;
	}
	debug_LexAbalyze();
	
	return 0;
	
}
