#include <LPC21xx.H>
#define MAX_TOKEN_NR 3 
#define MAX_KEYWORD_STRING_LTH 10
#define MAX_KEYWORD_NR 3
#define NULL '\0'

enum Keywordlist{LD, RST,ST};
enum TokenType{STRING,KEYWORD,NUMBER};

struct Keyword{
	enum Keywordlist elist;
	char cString[MAX_KEYWORD_STRING_LTH + 1];
};

struct Keyword asKeywordList[MAX_KEYWORD_NR]={
	{RST, "reset"},
	{ST, "store"},
	{LD, "load"}
};




typedef union {
	enum Keywordlist eKeyword;
	unsigned int uiNumber;
	char *pcString;
}TokenValue;	

typedef struct{
	enum TokenType uType;
	TokenValue uValue;
}Token;
		


void ucFindTokensInString (char pcString[]){
	
	
	
	
}








int main(){
	
	
}
























