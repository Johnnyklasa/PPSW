#include <LPC21xx.H>
#define NULL '\0' 
#define MAX_TOKEN_NUMBER 3
#define MaxKeywordStringLTH 10
#define MaxKeywordNumber 3

enum CompResult {DIFFERENT, EQUAL};
enum CompResult eCompareString(char pcStr1[], char pcStr2[])
{

    unsigned char ucCharacterCounter;

    for(ucCharacterCounter = 0 ; pcStr1[ucCharacterCounter] != NULL || pcStr2[ucCharacterCounter] != NULL ; ucCharacterCounter++)
    {
        if( pcStr1[ucCharacterCounter] != pcStr2[ucCharacterCounter] )
        {
            return DIFFERENT;
        }
    }
    
    return EQUAL;
}

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

unsigned char ucFindTokensInString (char *pcString){
	unsigned char ucCharCounter;
	unsigned char ucCurrChar;
	enum States eState=DELIMITER;
	ucTokenNumber=0;
	
	for(ucCharCounter=0;;ucCharCounter++){
		ucCurrChar=pcString[ucCharCounter];
		
		switch(eState){
		case DELIMITER:
			if (ucCurrChar==NULL){
				return ucTokenNumber;
			}
			
			else if (ucCurrChar!=' '){
				eState=TOKEN;
				
				asToken[ucCharCounter].uValue.pcString = pcString + ucCharCounter;// na dany element tablicy struktur na jego wartosc pointera na pc string w unii Value przypisujemy wskaznik na pierwszy znak kazdego stringa
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
//Funkcja wyodrebnia max3 tokeny ze stringa oraz przypisuje pointer do pierwszego zanku kazdego z nich do danego elementu w tablicy struktur
//Deklarujemy zmienna np pcStr="load 0X20 nigga"
//Uzywamy funkcje ---(pcString) czyli dajemy adres Stringa na który ma wskazywac 
// po rozdzeleniu do 3 osobnych struktur w kazdej z nich znajduje sie pointer do1 z 3 stringów wyodrebnonych przez funkcje

enum Result {ALLRIGHT, ERROR};

enum Result eSringToKeyword (char pcStr[],enum TokenCode *peKeywordCode){
		unsigned char ucCharCounter;
	  for (ucCharCounter=0; ucCharCounter<=MaxKeywordNumber; ucCharCounter++){
			if(eCompareString(asKeywordList[ucCharCounter].cString,pcStr)==EQUAL){
				*peKeywordCode= asKeywordList[ucCharCounter].eKeyword;
				return ALLRIGHT;				
			}
		}
return ERROR;
}

	
	







	
int main(){
	char pcStr[19]="Janek jest chujem";
	
	ucFindTokensInString(pcStr);
	
}








