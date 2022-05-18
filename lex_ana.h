#pragma once
#ifndef __LEX_ANA_H__
#define __LEX_ANA_H__

#include <iostream>
#include <cstring>
#include <fstream>	//too//
#include <iterator>//���ڶ�ȡ�ļ�// 
#include <ctype.h>		//isalpha// 
#include <vector>


//����token����// 
#define LEX_KEYWORD 1
#define LEX_OPERATION1 2
#define LEX_OPERATION2 3
#define LEX_FUNCTION 4
#define LEX_SEPCIFIC 5			
#define LEX_TAG	6
#define LEX_INIT 7
//������// 


char const *const Lex_Keyword[] = {	//������/// ����һȦֻ��int���� ����void����// 				
	"int","void","const","while",//û��do while���// 
	"if","else","continue","break"
};

char const *const Lex_operation1[] = {	//��������//	//û��λ����// 							
	"+","-","*","/","%","=",">","<","&","!"
};

char const *const Lex_operation2[] = {	//��������	//	��λ��// 
	">=","<=","&&","||","!=","=="
};

char const *const Lex_Function[] = {	//���ܺ���// 	�ο���Ϊ�ṩ��SysY����ʱ�� 2021// 
	"getint","getch","getarray","putint","putch","putarray","putf",//I/O����
	"starttime","stoptime","main" 											//��ʱ���� 
};

char const *const Lex_specific[] = {	//�������// 
	";",",","{","}","[","]","(",")"
};

typedef struct _Token{
	bool flag;				//�����һ���Ƿ�������// 
//	int line;				//��¼�к�//
	int rule;				//��¼��������// 
//	int length;				//��¼����// 
	std::string alToken;			//��¼����// 
} Token,pToken;




bool ReadFileToString(char * FilePath);	//��ȡ�ļ��е�����// 
bool LexAnalyze();
#endif

