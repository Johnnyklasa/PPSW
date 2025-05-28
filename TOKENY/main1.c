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
enum Result {OK, ERROR};

enum Result eHexStringToUInt(char pcStr[],unsigned int *puiValue)
{
    unsigned char ucCharacterCounter;
    unsigned char ucCurrentCharacter;

    *puiValue = 0;
    if((pcStr[0] != '0') || (pcStr[1] != 'x') || (pcStr[2] == NULL))
    {
        return ERROR;
    }
    for(ucCharacterCounter = 2; pcStr[ucCharacterCounter] !=NULL ; ucCharacterCounter++)
    {
        ucCurrentCharacter = pcStr[ucCharacterCounter];
        if (ucCharacterCounter == 6)
        {
            return ERROR;
        }
	  *puiValue = *puiValue << 4;
        if((ucCurrentCharacter <= '9') && (ucCurrentCharacter >= '0'))
        {
            *puiValue = (*puiValue) | (ucCurrentCharacter - '0');
        }
        else if((ucCurrentCharacter <= 'F') && (ucCurrentCharacter >= 'A'))
        {
            *puiValue = (*puiValue) | (ucCurrentCharacter - 'A' + 10);
        }
        else
        {
            return ERROR;
        }
    }
    return OK;
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
				
				asToken[ucTokenNumber].uValue.pcString = pcString + ucCharCounter;// na dany element tablicy struktur na jego wartosc pointera na pc string w unii Value przypisujemy wskaznik na pierwszy znak kazdego stringa
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

enum Results eStringToKeyword (char pcStr[],enum TokenCode *peKeywordCode){
		unsigned char ucCharCounter;
	  for (ucCharCounter=0; ucCharCounter<MaxKeywordNumber; ucCharCounter++){
			if(eCompareString(asKeywordList[ucCharCounter].cString,pcStr)==EQUAL){
				*peKeywordCode= asKeywordList[ucCharCounter].eKeyword;
				return ALLRIGHT;				
			}
		}
return ERRORs;
}

void DecodeTokens(){
		
	unsigned char ucTokenCounter;
	struct Token *psCurrenttoken; 
	for (ucTokenCounter=0; ucTokenNumber>ucTokenCounter;ucTokenCounter++){
		psCurrenttoken=&asToken[ucTokenCounter];
		if (eStringToKeyword(psCurrenttoken->uValue.pcString, &psCurrenttoken->uValue.eKeyword)==ALLRIGHT){
		//wez adres skladowej uiNumber znajdujacej sie w uValue, która z kolei jest skladowa struktury/unii wskazywanej przez psCurrenttoken".
			psCurrenttoken->eType= KEYWORD;
		}
		else if (eHexStringToUInt(psCurrenttoken->uValue.pcString,&psCurrenttoken->uValue.uiNumber)==OK){
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








