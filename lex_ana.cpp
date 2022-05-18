

#include "lex_ana.h"
//using namespace std;


extern std::string File_str;	//导入全局变量// 
extern std::vector<std::vector<Token>> ve ;
int lines = 1;	//记录行号// 
int rows = 1;//并不代表列号...// 
bool IsSpace(char unit){		 
	if(unit == ' '){
		return 1;
	}
	return 0;
}
bool IsLineBreak(char unit){
	if(unit == '\n'){
		return 1;
	}
	return 0;
}
bool IsAnnotation1(char *unit){
	if(unit[0] == '/' && unit[1] == '/'){
		return 1;
	}
	
	return 0;
}
int IsAnnotation2(char *unit){
	if(unit[0] == '/' && unit[1] == '*'){
		int i;
		for(i = 2;;i++){
			if(unit[i] == '*' && unit[i+1] == '/'){
				return i - 1 + 2;	//越过// 
			}
		}
	}
	return 0;
}





int IsKeyword(char *unit){
	for(int i = 0;i<sizeof(Lex_Keyword) / sizeof(*Lex_Keyword);i++){
		if(!strncmp(unit,Lex_Keyword[i],strlen(Lex_Keyword[i]))){	//逐个比较固定长度的字符串// 
			
			
			std::string str;
			str.assign(unit,strlen(Lex_Keyword[i]));						//将字符串的前几个字符赋值给str// 
			Token Tk = {1,LEX_KEYWORD,str};
			ve[lines].push_back(Tk);
			return strlen(Lex_Keyword[i]) - 1;
		}
	}
	return 0;
	
}


bool IsLex_operation1(char unit){
	for(int i = 0;i<sizeof(Lex_operation1) / sizeof(*Lex_operation1);i++){
		if(unit == Lex_operation1[i][0]){
			
			std::string str;
			str.push_back(unit);
			//str.assign(str_unit,1);						//将字符串的前几个字符赋值给str// 
			Token Tk = {1,LEX_OPERATION1,str};
			ve[lines].push_back(Tk);
			return 1;
		}
	}	
	return 0;
}

bool IsLex_operation2(char* unit){
	for(int i = 0;i<sizeof(Lex_operation2) / sizeof(*Lex_operation2);i++){
		if(unit[0] == Lex_operation2[i][0] && unit[0] == Lex_operation2[i][1]){
			std::string str_unit(unit);
			std::string str;
			str.assign(str_unit.c_str(),2);						//将字符串的前几个字符赋值给str// 
			Token Tk = {1,LEX_OPERATION2,str};
			ve[lines].push_back(Tk);
			return 1;
		}
	}	
	return 0;
}
int IsLex_Function(char * unit){
	for(int i = 0;i<sizeof(Lex_Function) / sizeof(*Lex_Function);i++){
		if(!strncmp(unit,Lex_Function[i],strlen(Lex_Function[i]))){	//逐个比较固定长度的字符串// 
			
			std::string str;
			str.assign(unit,strlen(Lex_Function[i]));						//将字符串的前几个字符赋值给str// 
			Token Tk = {1,LEX_FUNCTION,str};
			ve[lines].push_back(Tk);
			return strlen(Lex_Function[i]) - 1;
		}
	}	
	return 0;
}

bool IsLex_specific(char unit){
	for(int i = 0;i<sizeof(Lex_specific) / sizeof(*Lex_specific);i++){
		if(unit == Lex_specific[i][0]){
			
			std::string str;
			str.push_back(unit);
			Token Tk = {1,LEX_SEPCIFIC,str};
			ve[lines].push_back(Tk);
			
			return 1;
		}
	}
	return 0;	
}

int IsTAG(char * unit){
	if(unit[0] == '_' || isalpha(unit[0])){	//第一个字符只能为_和字母// 
		int len = 1;
		while(isalpha(unit[len]) || isdigit(unit[len]) || unit[len] == '_'){
			len++;
		}
		
		std::string str_unit(unit);
		std::string str;
		str.assign(str_unit.c_str(),len);						//将字符串的前几个字符赋值给str// 
		Token Tk = {1,LEX_TAG,str};
		ve[lines].push_back(Tk);

		return len - 1;
	}
	return -1;
}

int IsInit(char * unit){
	int len = 0;
	if(unit[0] == '0' && unit[1] == 'x'){
		len = 2;
		while((0x30 <= unit[len] && unit[len] <=  0x39) || (0x41 <= unit[len]  && unit[len] <= 0x46) || (0x61 <= unit[len] && unit[len] <= 0x66)  ){
			len++;
		}
			
	}
	else{
		while(0x30 <= unit[len] && unit[len] <=  0x39){
			len++;
		}
	}
	if(len >= 0){
		std::string str_unit(unit);
		std::string str;
		str.assign(str_unit.c_str(),len);						//将字符串的前几个字符赋值给str// 
		Token Tk = {1,LEX_INIT,str};
		ve[lines].push_back(Tk);
	}
	
	return len - 1;
}

bool ReadFileToString(char * FilePath){	//读取文件中的内容// https://blog.csdn.net/huashui2009120/article/details/80571101//sb博客，自己写错了，误导人，无语// 
	std::ifstream File_Path(FilePath);
	if(!File_Path){
		return 0;
	}
	std::istreambuf_iterator<char> begin(File_Path);
	std::istreambuf_iterator<char> end;
	File_str.assign(begin, end);
	
	return 1;
}
bool LexAnalyze(){
	
	int i;
	std::vector<Token> vt;	//把下标0覆盖//我们按照行号来// 
	vt.push_back( {0,0,"__empty__"});
	ve.push_back(vt);
	
	
	for(i = 0;i<File_str.length();i++){

		
		std::vector<Token> vtn ;
		vtn.push_back({0,0,"__empty__"});	//把下标0覆盖//我们从一开始// 字符串不允许赋值为NULL，不然运行的时候报错。。。// 
		ve.push_back(vtn);	
			
		int len;
		if(IsSpace(File_str[i])){	//判断为空格// 
			continue;		
		}
		
		if(IsLineBreak(File_str[i])){
			lines++;
			continue;
		}
		if(IsAnnotation1(&File_str[i])){	//判断为注释//   // //
			i++;
			continue;
		}
		len = IsAnnotation2(&File_str[i]);	//判断为注释 /**/  // 
		if(len){
			i += len;
			continue;
		}
		
		
		
		len = IsKeyword(&File_str[i]);		//判断为 关键词//  注意，按照我的写法，关键词至少为2个字节// 
		if(len){
			i += len;
			
			continue;
		}
		
		if(IsLex_operation1(File_str[i])){	//判断 是否为单位操作符// 
			continue;
		}
		
		if(IsLex_operation2(&File_str[i])){	//判断是否为双位操作符// 
			i ++;
			continue;
		}
		
		len = IsLex_Function(&File_str[i]);	//函数名至少大于1// 
		if(len){
			i += len;
			continue;
		}
		
		if(IsLex_specific(File_str[i])){	//判断 是否为其他的特殊符号// 这里我门认为特殊符号都是单位的// 
			continue;
		}
		
		len = IsTAG(&File_str[i]);
		if(len != -1){						//注意，变量名很有可能是一个字母的!!!// 
			i += len;
			continue;
		}	
		
		len = IsInit(&File_str[i]);
		if(len != -1){
			i += len;
			continue;
		}
		std::cout<<"error alp \t"<<File_str[i]<<std::endl;	
		return 0;
	}
}
