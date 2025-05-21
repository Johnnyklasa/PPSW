#include <LPC21xx.H>
#define MaxTokenNumber 3
#define MaxKeywordStringLTH 10
#define MaxKeywordNumber 3

enum TokenType {STRING, NUMBER, KEYWORD}; //Tworzymy typy tokenów
enum TokenCode {LD, ST, RST}; // Tworzymy kody dla Keywordów

union TokenValue{
	enum TokenCode eKeyword;
	unsigned int uiNumber;
	char * psString;
}; // Tworzymy Unie zawiajaca wartosc aktualnie badanego tokenu w zaleznosci jakiego typu jest. pointer pokazuje aktualny adres 

struct Token {
	enum TokenType eType;
	union TokenValue uValue;
};//Tworzymy strukture Tokeny która ma w sobie typ tokenu oraz jego wartosc

struct Token asToken[MaxTokenNumber]; //Tworzymy tablice struktur która zawiera asTokem{0} = {eType, uValue} itd. czyli trzy 

struct KeyWord{
	enum TokenCode eKeyword;
	char cString[MaxKeywordStringLTH+1];
};//Tworzymy strukture KeyWOrd która przechowuje kod tokena typu keyword oraz zwiazane z kodem string np. LD- "LOAD"

struct KeyWord asKeyWordList[MaxKeywordNumber]=
	{
		{LD, "load"},
		{ST, "store"},
		{RST, "reset"}
	}; //Tworzymy tablie Struktur i tym razem manualnie ustawiamy jej elementy 


unsigned char ucTokenNumber;	
	
	
	
enum States {TOKEN, DELIMITER};
unsigned char ucFindTokensInString (char *pcString){
	enum States eState=DELIMITER;
	unsigned char ucStringCounter;
	for (ucStringCounter=0;;ucStringCounter++){
		switch (eState){
		case DELIMITER:
			if (pcString[ucStringCounter]!=' '){
				eState=TOKEN;
			}
			else{
				eState=DELIMITER;
			}
			
			break;
		case TOKEN:
			if (pcString[ucStringCounter]==' '){
				eState=DELIMITER;
			}
			else{
				eState=TOKEN;
			}
		}
	}
}	
				
	
	
	
int main(){
	
}












