

#include "lex_ana.h"
//using namespace std;


extern std::string File_str;	//����ȫ�ֱ���// 
extern std::vector<std::vector<Token>> ve ;
int lines = 1;	//��¼�к�// 
int rows = 1;//���������к�...// 
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
				return i - 1 + 2;	//Խ��// 
			}
		}
	}
	return 0;
}





int IsKeyword(char *unit){
	for(int i = 0;i<sizeof(Lex_Keyword) / sizeof(*Lex_Keyword);i++){
		if(!strncmp(unit,Lex_Keyword[i],strlen(Lex_Keyword[i]))){	//����ȽϹ̶����ȵ��ַ���// 
			
			
			std::string str;
			str.assign(unit,strlen(Lex_Keyword[i]));						//���ַ�����ǰ�����ַ���ֵ��str// 
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
			//str.assign(str_unit,1);						//���ַ�����ǰ�����ַ���ֵ��str// 
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
			str.assign(str_unit.c_str(),2);						//���ַ�����ǰ�����ַ���ֵ��str// 
			Token Tk = {1,LEX_OPERATION2,str};
			ve[lines].push_back(Tk);
			return 1;
		}
	}	
	return 0;
}
int IsLex_Function(char * unit){
	for(int i = 0;i<sizeof(Lex_Function) / sizeof(*Lex_Function);i++){
		if(!strncmp(unit,Lex_Function[i],strlen(Lex_Function[i]))){	//����ȽϹ̶����ȵ��ַ���// 
			
			std::string str;
			str.assign(unit,strlen(Lex_Function[i]));						//���ַ�����ǰ�����ַ���ֵ��str// 
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
	if(unit[0] == '_' || isalpha(unit[0])){	//��һ���ַ�ֻ��Ϊ_����ĸ// 
		int len = 1;
		while(isalpha(unit[len]) || isdigit(unit[len]) || unit[len] == '_'){
			len++;
		}
		
		std::string str_unit(unit);
		std::string str;
		str.assign(str_unit.c_str(),len);						//���ַ�����ǰ�����ַ���ֵ��str// 
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
		str.assign(str_unit.c_str(),len);						//���ַ�����ǰ�����ַ���ֵ��str// 
		Token Tk = {1,LEX_INIT,str};
		ve[lines].push_back(Tk);
	}
	
	return len - 1;
}

bool ReadFileToString(char * FilePath){	//��ȡ�ļ��е�����// https://blog.csdn.net/huashui2009120/article/details/80571101//sb���ͣ��Լ�д���ˣ����ˣ�����// 
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
	std::vector<Token> vt;	//���±�0����//���ǰ����к���// 
	vt.push_back( {0,0,"__empty__"});
	ve.push_back(vt);
	
	
	for(i = 0;i<File_str.length();i++){

		
		std::vector<Token> vtn ;
		vtn.push_back({0,0,"__empty__"});	//���±�0����//���Ǵ�һ��ʼ// �ַ���������ֵΪNULL����Ȼ���е�ʱ�򱨴�����// 
		ve.push_back(vtn);	
			
		int len;
		if(IsSpace(File_str[i])){	//�ж�Ϊ�ո�// 
			continue;		
		}
		
		if(IsLineBreak(File_str[i])){
			lines++;
			continue;
		}
		if(IsAnnotation1(&File_str[i])){	//�ж�Ϊע��//   // //
			i++;
			continue;
		}
		len = IsAnnotation2(&File_str[i]);	//�ж�Ϊע�� /**/  // 
		if(len){
			i += len;
			continue;
		}
		
		
		
		len = IsKeyword(&File_str[i]);		//�ж�Ϊ �ؼ���//  ע�⣬�����ҵ�д�����ؼ�������Ϊ2���ֽ�// 
		if(len){
			i += len;
			
			continue;
		}
		
		if(IsLex_operation1(File_str[i])){	//�ж� �Ƿ�Ϊ��λ������// 
			continue;
		}
		
		if(IsLex_operation2(&File_str[i])){	//�ж��Ƿ�Ϊ˫λ������// 
			i ++;
			continue;
		}
		
		len = IsLex_Function(&File_str[i]);	//���������ٴ���1// 
		if(len){
			i += len;
			continue;
		}
		
		if(IsLex_specific(File_str[i])){	//�ж� �Ƿ�Ϊ�������������// ����������Ϊ������Ŷ��ǵ�λ��// 
			continue;
		}
		
		len = IsTAG(&File_str[i]);
		if(len != -1){						//ע�⣬���������п�����һ����ĸ��!!!// 
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
