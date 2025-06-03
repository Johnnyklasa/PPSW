#include <LPC21xx.H>
#include "biblio.h"
#define NULL '\0' 
#define MAX_TOKEN_NUMBER 3
#define MaxKeywordStringLTH 10
#define MaxKeywordNumber 3







enum TokenType {STRING, NUMBER, KEYWORD}; 
enum TokenCode {LD, ST, RST};

union TokenValue{
	enum TokenCode eKeyword;
	unsigned int uiNumber;
	char * pcString;
}; 

struct Token {
	enum TokenType eType;
	union TokenValue uValue;
};

struct Token asToken[MAX_TOKEN_NUMBER]; 

struct KeyWord{
	enum TokenCode eKeyword;
	char cString[MaxKeywordStringLTH+1];
};

struct KeyWord asKeywordList[MaxKeywordNumber]=
	{
		{LD, "load"},
		{ST, "store"},
		{RST, "reset"}
	};

	
enum States {TOKEN, DELIMITER};
unsigned char ucTokenNumber;

unsigned char ucFindTokensInString (char *pcString){ //Funkcja rozdziela komunikat na max 3 tokeny i pointer do kazdego z nich wrzuca na dany element struktury 
	unsigned char ucCharCounter;
	unsigned char ucCurrChar;
	enum States eState=DELIMITER;
	ucTokenNumber=0;
	
	for(ucCharCounter=0;;ucCharCounter++){//iterujemy po znakach 
		ucCurrChar=pcString[ucCharCounter];
		
		switch(eState){
		case DELIMITER:
			if (ucCurrChar==NULL){
				return ucTokenNumber;
			}
			
			else if (ucCurrChar!=' '){
				eState=TOKEN;
				
				asToken[ucTokenNumber].uValue.pcString = pcString + ucCharCounter;//Na dany element tablicy przypisz pointer do danego tokenu
				ucTokenNumber++;
			}
			else{
				eState=DELIMITER;
			}
		  break;

		case TOKEN:
				if (ucCurrChar==NULL){
					return ucTokenNumber;
				}
				else if (ucTokenNumber>=MAX_TOKEN_NUMBER){
					return ucTokenNumber;
				}
				else if (ucCurrChar==' '){
					eState=DELIMITER;
				}
				else{
					eState=TOKEN;
				}
				break;
		}
	}	
}	


enum Results {ALLRIGHT, ERRORs};

enum Results eStringToKeyword (char pcStr[],enum TokenCode *peKeywordCode){//funkcja porównuje danego stringa do 3 keywordów. jesli bedatakie same to wrzuca kod tokena na adres zmiennej
		unsigned char ucCharCounter;
	  for (ucCharCounter=0; ucCharCounter<MaxKeywordNumber; ucCharCounter++){
			if(eCompareString(asKeywordList[ucCharCounter].cString,pcStr)==EQUAL){//sprawdzaj czy dany string jest rowny keywordowi
				*peKeywordCode= asKeywordList[ucCharCounter].eKeyword;//podana zmienna ustaw na wartosc danego tokena
				return ALLRIGHT;				
			}
		}
return ERRORs;
}

void DecodeTokens(){
		
	unsigned char ucTokenCounter;
	struct Token *psCurrenttoken; //tworzymy pointer do strukturty typu token
	for (ucTokenCounter=0; ucTokenNumber>ucTokenCounter;ucTokenCounter++){
		psCurrenttoken=&asToken[ucTokenCounter];//ustaw zeby pointer wskazywal na dany element tablicy
		if (eStringToKeyword(psCurrenttoken->uValue.pcString, &psCurrenttoken->uValue.eKeyword)==ALLRIGHT){
		//wez wartosc zmiennej na która wskazuje pointer na stringa elementu tablicy który jest wskazywany i gdy okaza sie te same wrzuc wartosc keyworda do struktury 
			psCurrenttoken->eType= KEYWORD;//ustaw typ na keyword
		}
		else if (eHexStringToUInt(psCurrenttoken->uValue.pcString,&psCurrenttoken->uValue.uiNumber)==OK){//z elementu tablicy na który wskazuje pointer wez stringa na który wskazuje pointer wewnatrz unii i nastepnie przypisz wartosc do struktury jako number
			psCurrenttoken->eType= NUMBER;
		}
		else {
			psCurrenttoken->eType= STRING;
		}
			
	}
}







void DecodeMsg(char *pcString){
	ucTokenNumber= ucFindTokensInString(pcString);
	ReplaceCharactersInString(pcString,' ', NULL);
	DecodeTokens();
	
	
	
	
}







	
int main(){
	char pcStr[19]="store chuj jasiek";
	enum TokenCode eEnum;
	ucFindTokensInString(pcStr);
	eStringToKeyword(pcStr,&eEnum);
	
	
}








