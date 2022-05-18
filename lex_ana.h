#pragma once
#ifndef __LEX_ANA_H__
#define __LEX_ANA_H__

#include <iostream>
#include <cstring>
#include <fstream>	//too//
#include <iterator>//用于读取文件// 
#include <ctype.h>		//isalpha// 
#include <vector>


//定义token类型// 
#define LEX_KEYWORD 1
#define LEX_OPERATION1 2
#define LEX_OPERATION2 3
#define LEX_FUNCTION 4
#define LEX_SEPCIFIC 5			
#define LEX_TAG	6
#define LEX_INIT 7
//待补充// 


char const *const Lex_Keyword[] = {	//变量名/// 看了一圈只有int类型 或者void类型// 				
	"int","void","const","while",//没有do while语句// 
	"if","else","continue","break"
};

char const *const Lex_operation1[] = {	//操作符号//	//没有位运算// 							
	"+","-","*","/","%","=",">","<","&","!"
};

char const *const Lex_operation2[] = {	//操作符号	//	两位的// 
	">=","<=","&&","||","!=","=="
};

char const *const Lex_Function[] = {	//功能函数// 	参考华为提供的SysY运行时库 2021// 
	"getint","getch","getarray","putint","putch","putarray","putf",//I/O函数
	"starttime","stoptime","main" 											//计时函数 
};

char const *const Lex_specific[] = {	//特殊符号// 
	";",",","{","}","[","]","(",")"
};

typedef struct _Token{
	bool flag;				//标记这一行是否有数据// 
//	int line;				//记录行号//
	int rule;				//记录规则类型// 
//	int length;				//记录长度// 
	std::string alToken;			//记录符号// 
} Token,pToken;




bool ReadFileToString(char * FilePath);	//读取文件中的内容// 
bool LexAnalyze();
#endif

