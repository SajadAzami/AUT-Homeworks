# include <stdio.h>
# include <conio.h>
# include <string.h>
# include <string>
# include <stdlib.h>
# include <ctype.h>
# include <time.h>
#include <math.h>
# define SIZE 300
# define MAX 10000
# define MaxSizeOfLine 50
# define MaxSizeOfWord 30

typedef enum errors{NoError=0,};
typedef enum attribs{Declerations,Initializations,Conditions,Trashes};
typedef enum kinds {nonIdentified=0,
	Type_int,Type_char,Type_bool,
	Value_Int32,Value_SInt32,Value_Float,Value_true,Value_false,
	Math,Condition,Logic,Compare,
	Var,Sign,Keyword_if};
typedef struct line
{
	double Num ;
	char Value[MaxSizeOfLine] ;
	int ParentLine;
	attribs Attrib; 
	errors Error;
	bool AsmChecked;
};
typedef struct word
{
	char Value[50];
	int Line;
	int Seq;
	bool IsValid;
	int ParentLine;
};
typedef struct virtualVar
{
	char Name[10] ;
	double InitLineNum ;
};
typedef struct asmLine
{
	char Value[SIZE];
	int WillAdded;
};

asmLine ASMLines[SIZE];
line RLines[SIZE];

int VVarCounter =0;
//char MainNote[SIZE];
int LineCounter=0;
line Lines[SIZE];
int AsmCounter = 0;

word Words[SIZE];
int LCounter = 0;
int randomNum=0;

void Help(void) ;
bool Open(char *address) ;
bool Save(char *table,char *address) ;
int _index(double num) ;
void InitializeLines(void);
char _randomChar(void);
virtualVar VirtualVars[SIZE];
char *_randomName(void);
double _min(double arrayTemp[SIZE],int lenght);
int _addLine(char *value,double num,int parent);
double _nextNum(double num);
void _processLevel1(void);
bool _processLevel2(line *thisLine);
void _processLevel3(void);
bool _isFloat(const char *str);
bool _isInt32(const char *str);
bool _isSInt32(const char *str);
kinds _id(const char* str);
bool _isDigitORAlpha(const char c);
bool _multiplyCheck(line* thisLine);
bool _prntzCheck(line* thisLine);
bool _devideCheck(line* thisLine);
bool _plusCheck(line* thisLine);
bool _minusCheck(line* thisLine);
bool _removeSharpLines(line* thisLine);
bool _removeSlashSlashCommentes(line* thisLine);
bool _removeMultiSpaces(line* thisLine);
bool _removeLineFirstSpace(line* thisLine);
bool _devide2SemiColons(line* thisLine);
bool _removeMainFunctionLine(line* thisLine);
bool _devideLetMath(line* thisLine);
bool _devideDeclerateAndLet(line* thisLine);
bool _devideAfterIf(line* thisLine);
bool _removePhiLines(line* thisLine);
bool _removeLineLastSpace(line* thisLine);
void _spaceFix(void);
bool _repair1LineIf(line* thisLine);
bool _biggerThanCheck(line* thisLine);
bool _smallerThanCheck(line* thisLine);
bool _notCheck(line* thisLine);
bool _replace2CharOperators(line* thisLine);
bool _bitWiseAndCheck(line* thisLine);
bool _bitWiseORCheck(line* thisLine);
bool _changeAll2Int32(line* thisLine);
bool _Not2EqualZeroCheck(line* thisLine);
bool _smaller2BiggerCheck(line* thisLine);
bool _biggerThanZeroCheck(line* thisLine);
bool _biggerThanEqual2OR(line* thisLine);
void _mathAssistant();
bool _2ZeroComp(line* thisLine);
bool _biggerThanSmallerThanEqual2OR(line* thisLine);
bool _compareAssistant(line* thisLine);
bool _andORAssistant(line* thisLine);
bool _openBoxGotoCheck(line*  thisLine);
bool _orTranslate(line* thisLine);
bool _elseTranslate(line* thisLine);
void _processLevel4();
void _asmLineAdd(char* value,int willAdded);
void _asm1(line* thisLine);
void _asm2(line* thisLine);
void _asm3(line* thisLine);
void _asm4(line* thisLine);
void _asm5(line* thisLine);
void _asm6(line* thisLine);
void _asm7(line* thisLine);
void _repairDecleratedVars();
void _repairRlines();


int main (int argCounter,char *argValue[])
{/*
	if(argCounter == 3)
	{
		Open(MainNote, argValue[1]) ;
		InitializeLines();

	}
	else
	{
		Help();
		return 1;
	}
	*/
	Open("C:\\Users\\Espinas\\Desktop\\3.txt");
	printf("processing...");
	InitializeLines();
	_processLevel1();

	_processLevel3();
	_processLevel4();
	char _final[SIZE];
	_final[0] = '\0';
	for(int j=0;j<SIZE;j++)
	{
		strcat(_final,ASMLines[j].Value);
		strcat(_final,"\n");
	}
	
//	Save(_final,"C:\\Users\\Espinas\\Desktop\\_final.txt");
	return 0;
}
int WordCounter = 0;
void InitWords()
{
	for(int i=0;i<SIZE;i++)
	{
		Words[i].IsValid = false;
		Words[i].Line = -1;
		Words[i].Seq = -1;
		Words[i].Value[0] = '\0';
	}
	int seq=0;
	for(int i=0;i<SIZE;i++,seq=0)
	{
		if(RLines[i].Num !=-1)
		{
			char *_word;
			_word = strtok(RLines[i].Value," ");
			for(int j =0 ;_word!=NULL;j++)
			{
				Words[WordCounter].Line = i;
				Words[WordCounter].IsValid= true;
				Words[WordCounter].Seq = seq++;
				Words[WordCounter].ParentLine = RLines[i].ParentLine;
				strcpy(Words[WordCounter++].Value,_word);
				_word = strtok(NULL," ");
			}
		}
	}
}
void _detect(void)
{
	for (int j =0 ; j<SIZE ; j++)
	{
		for (int i =0 ; i<SIZE ; i++)
		{
			if (Words[WordCounter].IsValid && (Words[i].Value[j] == '{' || Words[i].Value[j] == '}' || Words[i].Value[j] == '@' || Words[i].Value[j] == '=' || Words[i].Value[j] == '+' || Words[i].Value[j] == '-' || Words[i].Value[j] == '*' || Words[i].Value[j] == '/' || Words[i].Value[j] == ';'))
				printf("Error");
		}
	}
}


bool Open(char *address)
{
	char _fullFIle[SIZE];
	char table[SIZE];
	FILE *filePtr = fopen(address,"r");
	if (filePtr==NULL)
	{
		fclose(filePtr);
		return false ;
	}
	else 
	{
		int i ;
		int lineCounter = 0;
		for(i =0;!feof(filePtr);i++)
		{
			table[i] = fgetc(filePtr);
		}
		table[i-1] = '\0';
		char*line ;
		for(int k = 0; k<SIZE;k++)
		{
			Lines[i].Num = -1 ;
		strcpy(Lines[i].Value,"");
		Lines[i].Error = NoError;
		Lines[i].AsmChecked = false;
		}
	line = strtok(table,"\n");
	for(int i =0;line !=NULL;i++)
	{
		strcpy(Lines[i].Value,line);
		Lines[i].Num = i;
		Lines[i].ParentLine = i;
		Lines[i].Error = NoError;
		LineCounter++;
		line = strtok(NULL,"\n");
	}
		fclose(filePtr);
		return true ;
	}
}
bool Save(char *table,char *address)
{
	FILE *filePtr = fopen(address,"w+");
	if (filePtr==NULL)
	{
		fclose(filePtr);
		return false ;
	}
	else 
	{
		fputs(table, filePtr);
		fclose(filePtr);
		return true ;
	}
}
void Help(void)
{
	printf("Bad use of EkaCompiler.exe\nUse:EkaCompiler.exe [source address] [destinition address]");
}
void InitializeLines(void)
{
	srand(time(NULL));
	for ( int i=0 ; i<SIZE ; i++)
	{
		strcpy(ASMLines[i].Value,"");
		ASMLines[i].WillAdded = 0;
		//
		//
		RLines[i].Num = -1 ;
		strcpy(RLines[i].Value,"");
		RLines[i].Error = NoError;
		RLines[i].AsmChecked = false;
		//init vvars
		VirtualVars[i].InitLineNum = -1;
		strcpy(VirtualVars[i].Name,"");
		///--------
	}
	char*line ;
	/*line = strtok(MainNote,"\n");
	for(int i =0;line !=NULL;i++)
	{
		strcpy(Lines[i].Value,line);
		Lines[i].Num = i;
		Lines[i].ParentLine = i;
		Lines[i].Error = NoError;
		LineCounter++;
		line = strtok(NULL,"\n");
	}*/
}
char *_randomName(void)
{
	static char _randomWords[9];
	_randomWords[0] = '$';
	_randomWords[1] = 't';
	_randomWords[2] = '\0';
	char randNum[10];
	sprintf(randNum,"%d",randomNum++);
	strcat(_randomWords,randNum);
	return _randomWords;
}
char _randomChar(void)
{
	return rand()%('z' - 'a' +1) +'a';
}
bool _removeSharpLines(line* thisLine)//& comment lines
{
	if((*thisLine).Num ==-1) return false;
	bool _flag = false ;
	if((*thisLine).Num != -1 && (*thisLine).Value[0] == '#')
	{
		_flag = true;
		(*thisLine).Num = -1;
	}
	if((*thisLine).Num != -1 && (*thisLine).Value[0] == '/' && (*thisLine).Value[1] == '/')
	{
		_flag = true;
		(*thisLine).Num = -1;
	}
	

	return _flag;
}
bool _removeSlashSlashCommentes(line* thisLine)
{
	if((*thisLine).Num ==-1) return false;
	bool _flag = false;

	for(int i = 0;i<strlen((*thisLine).Value)-1;i++)
	{
		if((*thisLine).Num !=-1 &&(*thisLine).Value[i] =='/'&& (*thisLine).Value[i+1] == '/' )
		{
			_flag =true;
			//copying line without //Comment
			int _firstZero = _index(-1);
			strncpy(Lines[_firstZero].Value,(*thisLine).Value,i-1);
			Lines[_firstZero].ParentLine = (*thisLine).ParentLine;
			Lines[_firstZero].Num = (*thisLine).Num;
			//removing line
			(*thisLine).Num = -1;
		}
	}
	return _flag;
}
bool _removeMultiSpaces(line* thisLine)
{
	if((*thisLine).Num ==-1) return false;
	bool _flag = false;

	for(int k = 0; k<strlen((*thisLine).Value);k++)
	{
		for(int i =0;i<strlen((*thisLine).Value)-1;i++)
		{
			
			if((*thisLine).Num != -1 && (*thisLine).Value[i] == ' ' && (*thisLine).Value[i+1] == ' ')
			{
				_flag = true;
				//backward 1 level from i+1
				for(int j = i;j<strlen((*thisLine).Value)+1;j++)
				{
					(*thisLine).Value[j] = (*thisLine).Value[j+1];
				}
			}
		}
	}


	return _flag;
}
bool _removeLineFirstSpace(line* thisLine)
{
	if((*thisLine).Num ==-1) return false;
	bool _flag = false;

	if((*thisLine).Num != -1 && (*thisLine).Value[0] == ' ')
	{
		_flag = true;
		for(int i = 0;i<strlen((*thisLine).Value);i++)
		{
			(*thisLine).Value[i] = (*thisLine).Value[i+1];
		}
	}

	return _flag;
}
bool _removeLineLastSpace(line* thisLine)
{
	if((*thisLine).Num == -1) return false;
	int l;
	if((*thisLine).Value[l = (strlen((*thisLine).Value)-1)] ==' ')
	{
		(*thisLine).Value[l] = '\0';
		return true;
	}
	return false;
}
bool _devide2SemiColons(line* thisLine)
{
	if((*thisLine).Num ==-1) return false;
	bool _flag = false;

	for (int i = 0;i<strlen((*thisLine).Value)-1 ; i++)
	{
		if((*thisLine).Num != -1 && (*thisLine).Value[i] == ';' && (*thisLine).Value[i+1] != '\0')
		{
			_flag = true;
			//copying after ; to new line
			char _temp[SIZE];
			int k = 0;
			for(int j = i+1;j < strlen((*thisLine).Value)+1;j++)
			{
				_temp[k++] = (*thisLine).Value[j];
			}
			_addLine(_temp,((*thisLine).Num + _nextNum((*thisLine).Num))/2,(*thisLine).ParentLine);
			//removing after ;
			(*thisLine).Value[i+1] = '\0';
		}
	}

	return _flag;
}
bool _removeMainFunctionLine(line* thisLine)
{
	if((*thisLine).Num ==-1) return false;
	bool _flag = false;
	if((*thisLine).Num !=-1)
	{
		char _cpy[SIZE];
		strcpy(_cpy,(*thisLine).Value);
		char *_first;
		_first = strtok(_cpy," ()");
		if(!strcmp(_first,"int")  || !strcmp(_first,"void"))
		{
			_first = strtok(NULL," ()");
			if(!strcmp(_first,"main"))
			{
				_flag = true;
				if(Lines[_index(_nextNum((*thisLine).Num))].Value[0] != '{')
				{
					_addLine("{",((*thisLine).Num + _nextNum((*thisLine).Num))/2,(*thisLine).ParentLine);
				}
				//removing line
				(*thisLine).Num=-1;
			}
		}
	}


	return _flag;
}
bool _removePhiLines(line* thisLine)
{
	if((*thisLine).Num ==-1) return false;
	if((*thisLine).Value[0] == '\0')
	{
		(*thisLine).Num = -1;
		return true;
	}
	return false;
}
bool _devideLetMath(line* thisLine)
{
	if((*thisLine).Num ==-1) return false;
	bool _flag = false;

	for(int i = 0;i<strlen((*thisLine).Value)-1;i++)
	{
		
		if((*thisLine).Num !=-1 &&((*thisLine).Value[i] =='+' || (*thisLine).Value[i] =='-' || (*thisLine).Value[i] =='*' || (*thisLine).Value[i] =='/' )&& (*thisLine).Value[i+1] == '=' )
		{
			_flag =true;
			char _temp[4] = {' ',(*thisLine).Value[i],' ','\0'};
			char _part1[SIZE];
			char _part2[SIZE];
			char _final[SIZE];
			_final[0] = '\0';
			char cpy[SIZE];
			strcpy(cpy,(*thisLine).Value);
			char *_tok;
			_tok = strtok(cpy," +-*/");
			strcpy(_part1,_tok);
			strcat(_final,_part1);
			strcat(_final," = ");
			int _from = strlen(_final);
			strcat(_final,(*thisLine).Value);
			for(int j=_from;j<strlen(_final);j++)
				if(_final[j] == '=')
				{
					_final[j] = ' ';
					break;
				}
			strcpy((*thisLine).Value,_final);
		}
	}

	
	return _flag;
}
bool _devideDeclerateAndLet(line* thisLine)
{
	if((*thisLine).Num ==-1) return false;
	bool _flag = false;

	if((*thisLine).Num !=-1)
	{
		char* _tok;
		char cpy[SIZE];
		strcpy(cpy,(*thisLine).Value);
		_tok = strtok(cpy," ");
		if(_id(_tok) ==Type_int || _id(_tok) ==Type_char|| _id(_tok) ==Type_bool)
		{
			bool _letFlag = false;
			for(int i = strlen(_tok);i<strlen((*thisLine).Value);i++)
			{
				if((*thisLine).Value[i] == '=')
					_letFlag = true;
			}
			if(_letFlag)
			{
				_flag = true;
				char _word1[SIZE];
				char _final[SIZE];
				strcpy(_word1,_tok);
				strcpy(_final,(*thisLine).Value);
				strcpy(cpy,(*thisLine).Value);
				_tok = strtok(cpy,"=");
				(*thisLine).Value[strlen(_tok)] = ';';
				(*thisLine).Value[strlen(_tok)+1] = '\0';
				//khat 1 hal shod
				for(int j=0;j<4;j++)
					_final[j] = ' ';
				_addLine(_final,((*thisLine).Num + _nextNum((*thisLine).Num))/2,(*thisLine).ParentLine);
			}
		}
	}


	return _flag;
}
bool _devideAfterIf(line* thisLine)
{
	if((*thisLine).Num ==-1) return false;
	bool _flag = false;

	if((*thisLine).Num!= -1 && (*thisLine).Value[0] == 'i' && (*thisLine).Value[1] == 'f')
	{
		if(((*thisLine).Value[2] == ' ' && (*thisLine).Value[3] == '(') || (*thisLine).Value[2] == '(')
		{
			
			int _prntzStack = 0;
			int _from=-1;
			bool _1flag = false;
			for(int i =0;i<strlen((*thisLine).Value);i++)
			{
				if((*thisLine).Value[i] == '(')
				{
					_1flag = true;
					_prntzStack++;
				}
				if((*thisLine).Value[i] == ')')
					_prntzStack--;
				if(_1flag && _prntzStack == 0)
				{
					_from = i;
					break;
				}

			}
			if(_from !=-1 && (*thisLine).Value[_from+1] != '\0')
			{
				_flag = true;
				char _cpy[SIZE];
				strcpy(_cpy,(*thisLine).Value);
				(*thisLine).Value[_from+1] = '\0';
				int _newLineIndex = _addLine(_cpy,((*thisLine).Num + _nextNum((*thisLine).Num))/2,(*thisLine).ParentLine);
				for(int i = 0 ; i<_from+1;i++)
				{
					Lines[_newLineIndex].Value[i] = ' ';
				}
			}
		}
		

	}
	
	return _flag;
}
bool _changeAll2Int32(line* thisLine)
{
	if((*thisLine).Num == -1) return false;
	bool _flag = false;

	for(int i =0;i<strlen((*thisLine).Value)-1;i++)
	{
		if((*thisLine).Value[i] == '\'' && (*thisLine).Value[i+2] == '\'')
		{
			_flag = true;
			char _number[10];
			itoa((int)(*thisLine).Value[i+1],_number,3);//***********************
			char _newLine[SIZE];
			int k=0;
			for(int j=0;j<i;j++)
			{
				_newLine[k++] = (*thisLine).Value[j];
			}
			_newLine[k++] = '\0';
			strcat(_newLine,_number);
			k = strlen(_newLine);
			for(int j=i+3;j<strlen((*thisLine).Value)+1;j++)
			{
				_newLine[j] = (*thisLine).Value[j];
			}
			 strcpy((*thisLine).Value,_newLine);
			break;
		}
	}
	
	if((*thisLine).Value[0] == 'c' && (*thisLine).Value[1] == 'h' &&(*thisLine).Value[2] == 'a' &&(*thisLine).Value[3] == 'r')
	{
			_flag = true;
			(*thisLine).Value[0] = 'i';
			(*thisLine).Value[1] = 'n';
			(*thisLine).Value[2] = 't';
			(*thisLine).Value[3] = ' ';
	}
	if((*thisLine).Value[0] == 'b' && (*thisLine).Value[1] == 'o' &&(*thisLine).Value[2] == 'o' &&(*thisLine).Value[3] == 'l')
	{
			_flag = true;
			(*thisLine).Value[0] = 'i';
			(*thisLine).Value[1] = 'n';
			(*thisLine).Value[2] = 't';
			(*thisLine).Value[3] = ' ';
	}
	for(int i =0;i<strlen((*thisLine).Value)-1;i++)
	{
		if((*thisLine).Value[i] == 't' && (*thisLine).Value[i+1] == 'r'&& (*thisLine).Value[i+2] == 'u'&& (*thisLine).Value[i+3] == 'e')
		{
			_flag = true;
			(*thisLine).Value[i] = ' ';
			(*thisLine).Value[i+1] = '1';
			(*thisLine).Value[i+2] = ' ';
			(*thisLine).Value[i+3] = ' ';
			break;
		}
		if((*thisLine).Value[i] == 'f' && (*thisLine).Value[i+1] == 'a'&& (*thisLine).Value[i+2] == 'l'&& (*thisLine).Value[i+3] == 's'&& (*thisLine).Value[i+4] == 'e')
		{
			_flag = true;
			(*thisLine).Value[i] = ' ';
			(*thisLine).Value[i+1] = '0';
			(*thisLine).Value[i+2] = ' ';
			(*thisLine).Value[i+3] = ' ';
			(*thisLine).Value[i+4] = ' ';
			break;
		}
	}
	_spaceFix();
	return _flag;

}
bool _repair1LineIf(line* thisLine)
{
	if((*thisLine).Num ==-1) return false;
	bool _flag = false;

	if(((*thisLine).Value[0] == 'i' && (*thisLine).Value[1] == 'f') || ((*thisLine).Value[0] == 'e' && (*thisLine).Value[1] == 'l'&& (*thisLine).Value[2] == 's'&& (*thisLine).Value[3] == 'e'))
	{
		line _nLine = Lines[_index(_nextNum((*thisLine).Num))];
		
		if(_nLine.Value[0] != '{')
		{
			_flag = true;
			char _newLine[SIZE];
			_newLine[0] = '{';
			_newLine[1] = ' ';
			int k=2;
			for(int i = 0;i<strlen(_nLine.Value);i++)
			{
				_newLine[k++] = _nLine.Value[i];
			}
			_newLine[k++] = ' ';
			_newLine[k++] = '}';
			_newLine[k] = '\0';
			strcpy(Lines[_index(_nextNum((*thisLine).Num))].Value,_newLine);
		}
	}


	return _flag;
}
bool _repairOpenBoxes(line* thisLine)
{
	if((*thisLine).Num == -1) return false;
	bool _flag = false , _openFlag = false ;
	int i;
	for(i=0 ; i<strlen((*thisLine).Value) ; i++)
	{
		if((*thisLine).Value[i] == '{')
		{
			_openFlag = true;
			break;
		}
	}
	if(i!=0 && _openFlag)
	{
		_flag =true;
		char _after[SIZE];
		int k=0;
		for(int j=i;j<strlen((*thisLine).Value)+1;j++)
		{
			_after[k++] = (*thisLine).Value[j];
		}
		_addLine(_after,((*thisLine).Num + _nextNum((*thisLine).Num))/2,(*thisLine).ParentLine);
		(*thisLine).Value[i] = '\0';
	}
	if((*thisLine).Value[i+1] != '\0' && _openFlag)
	{
		_flag = true;
		char _after2 [SIZE];
		int k =0;
		for(int j=i+1;j<strlen((*thisLine).Value)+1;j++)
		{
			_after2[k++] = (*thisLine).Value[j];
		}
		_addLine(_after2,((*thisLine).Num + _nextNum((*thisLine).Num))/2,(*thisLine).ParentLine);
		(*thisLine).Value[i+1] = '\0';
	}

	return _flag;
}
bool _repairCloseBoxes(line* thisLine)	
{
	if((*thisLine).Num == -1) return false;
	bool _flag = false , _openFlag = false ;
	int i;
	for(i=0 ; i<strlen((*thisLine).Value) ; i++)
	{
		if((*thisLine).Value[i] == '}')
		{
			_openFlag = true;
			break;
		}
	}
	if(i!=0 && _openFlag)
	{
		_flag =true;
		char _after[SIZE];
		int k=0;
		for(int j=i;j<strlen((*thisLine).Value)+1;j++)
		{
			_after[k++] = (*thisLine).Value[j];
		}
		_addLine(_after,((*thisLine).Num + _nextNum((*thisLine).Num))/2,(*thisLine).ParentLine);
		(*thisLine).Value[i] = '\0';
	}
	if((*thisLine).Value[i+1] != '\0' && _openFlag)
	{
		_flag = true;
		char _after2 [SIZE];
		int k =0;
		for(int j=i+1;j<strlen((*thisLine).Value)+1;j++)
		{
			_after2[k++] = (*thisLine).Value[j];
		}
		_addLine(_after2,((*thisLine).Num + _nextNum((*thisLine).Num))/2,(*thisLine).ParentLine);
		(*thisLine).Value[i+1] = '\0';
	}

	return _flag;
}
bool _repairSigns(line* thisLine)
{
	
	if((*thisLine).Num == -1) return false;
	bool _flag = false;

	int i =0;
	char c ='\0';
	for(i =1 ; i<strlen((*thisLine).Value);i++)
	{
		c = (*thisLine).Value[i];
		if((c == ';' ||c == '=' || c == '>' || c == '<' || c=='(' || c== ')' || c == '~' || c == '@' || c == '?' || c == '^' || c == '+' || c == '-' || c == '/' || c == '*' || c == '!' || c == '.' || c == '%' || c == '|' || c == '&' )&&  (*thisLine).Value[i-1] !=' ')
		{
			_flag = true;
			//1 unit to forward
			for(int j = strlen((*thisLine).Value)+1;j>=i+1;j--)
			{
				(*thisLine).Value[j] = (*thisLine).Value[j-1];
			}
			(*thisLine).Value[i] = ' ';
			break;
		}
		if((c == ';' ||c == '=' || c == '>' || c == '<' || c=='(' || c== ')' || c == '~' || c == '@' || c == '?' || c == '^' || c == '+' || c == '-' || c == '/' || c == '*' || c == '!' || c == '.' || c == '%' || c == '|' || c == '&' ) &&  ((*thisLine).Value[i+1] !=' ' && (*thisLine).Value[i+1] != '\0'))
		{
			_flag = true;
			//1 unit to forward
			for(int j = strlen((*thisLine).Value)+1;j>=i+2;j--)
			{
				(*thisLine).Value[j] = (*thisLine).Value[j-1];
			}
			(*thisLine).Value[i+1] = ' ';
			break;
		}
	}
	
	_spaceFix();
	return _flag;
}
void _spaceFix(void)
{
	for(int i =0;i<SIZE;i++)
		for(;_removeLineFirstSpace(&Lines[i]);){}
	for(int i =0;i<SIZE;i++)
		for(;_removeLineLastSpace(&Lines[i]);){}
	for(int i =0;i<SIZE;i++)
		for(;_removeMultiSpaces(&Lines[i]);){}
	for(int i =0;i<SIZE;i++)
		for(;_removePhiLines(&Lines[i]);){}

}
void _fix(void)
{
	for(int i =0;i<SIZE;i++)
		for(;_repairSigns(&Lines[i]);){}
	_spaceFix();
}
void _processLevel1()
{
	_fix();
	// R1 : #<...>   ->   <>     ||    //<...>     ->    <>
	for(int i =0;i<SIZE;i++)
		for(;_removeSharpLines(&Lines[i]);){}
	// R2:<...>//Comment   ->   <...>
	for(int i =0;i<SIZE;i++)
		for(;_removeSlashSlashCommentes(&Lines[i]);){}

	_fix();
	for(int i =0;i<SIZE;i++)
		for(;_devide2SemiColons(&Lines[i]);){}
	_spaceFix();
	for(int i =0;i<SIZE;i++)
		for(;_removeMainFunctionLine(&Lines[i]);){}
	//R10 : if(...)<...>    ->    if(...)\n<...>
	_fix();
		//****
	for(int i =0;i<SIZE;i++)
		for(;_devideAfterIf(&Lines[i]);){}
		//****
	_fix();
	for(int i =0;i<SIZE;i++)
		for(;_changeAll2Int32(&Lines[i]);){}

	for(int i =0;i<SIZE;i++)
		for(;_repairOpenBoxes(&Lines[i]);){}

	for(int i =0;i<SIZE;i++)
		for(;_repair1LineIf(&Lines[i]);){}

	_fix();
	for(int i =0;i<SIZE;i++)
		for(;_repairOpenBoxes(&Lines[i]);){}
	for(int i =0;i<SIZE;i++)
		for(;_repairCloseBoxes(&Lines[i]);){}
	for(int i =0;i<SIZE;i++)
		for(;_repair1LineIf(&Lines[i]);){}

	//end of on the 1 line IF repair
	_fix();

	for(int i =0;i<SIZE;i++)
		for(;_repairSigns(&Lines[i]);){}

	_fix();

	for(int i =0;i<SIZE;i++)
		for(;_devideLetMath(&Lines[i]);){}
	for(int i =0;i<SIZE;i++)
		for(;_devideDeclerateAndLet(&Lines[i]);){}

	_fix();

}
bool _replace2CharOperators(line* thisLine)
{
	if((*thisLine).Num == -1) return false;
	bool _flag = false;

	for(int i = 0;i<strlen((*thisLine).Value)-1;i++)
	{
		if((*thisLine).Value[i] == '|' && (*thisLine).Value[i+2] == '|')
		{
			_flag = true;
			(*thisLine).Value[i] = '.';
			(*thisLine).Value[i+2] = ' ';
		}
		if((*thisLine).Value[i] == '&' && (*thisLine).Value[i+2] == '&')
		{
			_flag = true;
			(*thisLine).Value[i] = '*';   // : BOOLIAN MULTIPLY 
			(*thisLine).Value[i+2] = ' ';
		}
		if((*thisLine).Value[i] == '=' && (*thisLine).Value[i+2] == '=')
		{
			_flag = true;
			(*thisLine).Value[i] = '@';
			(*thisLine).Value[i+2] = ' ';
		}
		if((*thisLine).Value[i] == '!' && (*thisLine).Value[i+2] == '=')
		{
			_flag = true;
			(*thisLine).Value[i] = '~';
			(*thisLine).Value[i+2] = ' ';
		}
		if((*thisLine).Value[i] == '>' && (*thisLine).Value[i+2] == '=')
		{
			_flag = true;
			(*thisLine).Value[i] = '?';
			(*thisLine).Value[i+2] = ' ';
		}
		if((*thisLine).Value[i] == '<' && (*thisLine).Value[i+2] == '=')
		{
			_flag = true;
			(*thisLine).Value[i] = '^';
			(*thisLine).Value[i+2] = ' ';
		}

	}

	_spaceFix();
	return _flag;
}
bool _processLevel2(line *thisLine)
{
	bool _flag = false;


	return _flag;
}
int _mathOperatorCounter(const char* str)
{
	
	int _MathOperatorCounter=0;
	for(int i=0;i<strlen(str);i++)
	{
		char c = str[i];
		if(c == '>' || c == '<' || c=='(' || c== ')' || c == '~' || c == '@' || c == '?' || c == '^' || c == '+' || c == '-' || c == '/' || c == '*' || c == '!' || c == '.' || c == '%' || c == '|' )
			_MathOperatorCounter++;
	}
	
		return _MathOperatorCounter;

}
void _initRLines()
{
	double _nums[SIZE];
	int _numsCounter=0;
	double _numsTemp ;
	for(int i=0;i<SIZE;i++)
	{
		if(Lines[i].Num != -1)
		{
			_nums[_numsCounter] = Lines[i].Num ;
			_numsCounter++ ;
		}
	}
	for(int j=0 ; j<_numsCounter ; j++)
	{
		for ( int i=0 ; i<_numsCounter-1 ; i++)
		{
			if (_nums[i] > _nums[i+1])
			{
				_numsTemp = _nums[i+1];
				_nums[i+1] = _nums[i];
				_nums[i] = _numsTemp;
			}
		}
	}
	//nums sorted
	int _RLinesCounter =0;
	for(int i=0;i<_numsCounter;i++)
	{
		RLines[i] = Lines[_index(_nums[i])];
	}
}
void _processLevel3()
{
	_fix();
	
	for(int i=0;i<SIZE;i++)
		for(;_elseTranslate(&Lines[i]);){}
	
	for(int i=0;i<SIZE;i++)
		for(;_replace2CharOperators(&Lines[i]);){}
	
	for(int i=0;i<SIZE;i++)
		for(;_prntzCheck(&Lines[i]);){}

	for(int i=0;i<SIZE;i++)
		for(;_Not2EqualZeroCheck(&Lines[i]);){}

	_mathAssistant();

	for(int i=0;i<SIZE;i++)
		for(;_biggerThanSmallerThanEqual2OR(&Lines[i]);){}

	for(int i=0;i<SIZE;i++)
		for(;_smaller2BiggerCheck(&Lines[i]);){}
	
		
	for(int i=0;i<SIZE;i++)
		for(;_2ZeroComp(&Lines[i]);){}

	_mathAssistant();


	for(int i=0;i<SIZE;i++)
		for(;_bitWiseORCheck(&Lines[i]);){}
	for(int i=0;i<SIZE;i++)
		for(;_bitWiseAndCheck(&Lines[i]);){}
//////
	for(int i=0;i<SIZE;i++)
		for(;_compareAssistant(&Lines[i]);){}

	for(int i=0;i<SIZE;i++)
		for(;_andORAssistant(&Lines[i]);){}



	for(int i=0;i<SIZE;i++)
		for(;_orTranslate(&Lines[i]);){}//very slow

	//ALL OF THE BEFORE BECAUSE _ORTRANSLATE
	_fix();
	for(int i=0;i<SIZE;i++)
		for(;_replace2CharOperators(&Lines[i]);){}
	
	for(int i=0;i<SIZE;i++)
		for(;_prntzCheck(&Lines[i]);){}

	for(int i=0;i<SIZE;i++)
		for(;_Not2EqualZeroCheck(&Lines[i]);){}

	_mathAssistant();

	for(int i=0;i<SIZE;i++)
		for(;_biggerThanSmallerThanEqual2OR(&Lines[i]);){}

	for(int i=0;i<SIZE;i++)
		for(;_smaller2BiggerCheck(&Lines[i]);){}
	
		
	for(int i=0;i<SIZE;i++)
		for(;_2ZeroComp(&Lines[i]);){}

	_mathAssistant();


	for(int i=0;i<SIZE;i++)
		for(;_bitWiseORCheck(&Lines[i]);){}
	for(int i=0;i<SIZE;i++)
		for(;_bitWiseAndCheck(&Lines[i]);){}

	for(int i=0;i<SIZE;i++)
		for(;_compareAssistant(&Lines[i]);){}

	for(int i=0;i<SIZE;i++)
		for(;_andORAssistant(&Lines[i]);){}

	//END OF ALL OF THE BEFORE
	_initRLines();
	InitWords();
	_repairDecleratedVars();

}


void _repairDecleratedVars()
{
	for(int i = 0;i<SIZE;i++)
	{
		if(Words[i].IsValid && Words[i].Seq==0 && (!strcmp(Words[i].Value,"int") || !strcmp(Words[i].Value,"float")))
		{
			char name[SIZE];
			strcpy(name,Words[i+1].Value);
			// repair all names
			char _newName[SIZE];
			strcpy(_newName,_randomName());
			for(int j =0;j<SIZE;j++)
			{
				if(!strcmp(Words[j].Value,name))
				{

					strcpy(Words[j].Value,_newName);
				}
			}
			Words[i].IsValid = false;
			Words[i+1].IsValid = false;
		}
	}
}
void _repairASM()
{
	for(int i = 0;i<AsmCounter;i++)
	{
		if(ASMLines[i].Value[0] == '#' && ASMLines[i].Value[1] == 'B')
		{
			char _number[30];
			for(int j=2;j<strlen(ASMLines[i].Value)+1;j++)
			{
				_number[j-2] = ASMLines[i].Value[j];
			}
			for(int j=0;j<AsmCounter;j++)
			{
				if(ASMLines[j].Value[0] == 'j' && ASMLines[j].Value[4] == '#' )
				{
					char _origNumber[30];
					for(int l=6;l<strlen(ASMLines[j].Value)+1;l++)
					{
						_origNumber[l-6] = ASMLines[j].Value[l];
					}
					if(!strcmp(_origNumber,_number))
					{
						//here
						char index[10];
						sprintf(index,"%d",i);
						ASMLines[j].Value[4] = '\0';
						strcat(ASMLines[j].Value,index);
						ASMLines[i].Value[0] = '\0';
					}
				}
			}
		}
	}


	//   ? repair

	for(int i=0;i<AsmCounter;i++)
	{
		for(int j=0;j<strlen(ASMLines[i].Value);j++)
		{
			if(ASMLines[i].Value[j] == '?')
			{
				//here
				char number[10];
				sprintf(number,"%d",i+ASMLines[i].WillAdded);
				ASMLines[i].Value[j] = '\0';
				strcat(ASMLines[i].Value,number);
			}
		}
	}
}

void _repairRlines()
{
	for(int i = 0; i<SIZE;i++)
	{
		RLines[i].Value[0] = '\0';
	}
	for(int i = 0; i<SIZE;i++)
	{
		strcat(RLines[Words[i].Line].Value,Words[i].Value);
	}
}

void _processLevel4()
{
	for(int i=0;i<SIZE;i++)
		for(;_openBoxGotoCheck(&Lines[i]);){}
	_initRLines();
	

	//

	for(int i = 0;i<SIZE;i++)
	{
		if(!RLines[i].AsmChecked)
		{
			_asm1(&RLines[i]);
			_asm2(&RLines[i]);
			_asm3(&RLines[i]);
			_asm4(&RLines[i]);
			_asm5(&RLines[i]);
			_asm6(&RLines[i]);
			_asm7(&RLines[i]);
		}
	}
	_repairASM();
		

}
int _index(double num)
{
	for(int i = 0;i<SIZE;i++)
	{
		if(Lines[i].Num == num)
		{
			return i;
		}
	}
}
int _addLine(char *value,double num,int parent)
{
	int _i = _index(-1);
	strcpy(Lines[_i].Value,value);
	Lines[_i].Num = num ;
	Lines[_i].ParentLine = parent ;
	return _i;
}
double _nextNum(double num)
{
	static double _arrayTemp[SIZE];
	int k =0;
	for(int i=0; i<SIZE;i++)
	{
		if(Lines[i].Num>num)
			_arrayTemp[k++] = Lines[i].Num;
	}
	if(k==0)
		return num+1;
	return _min(_arrayTemp,k);
}
double _min(double arrayTemp[SIZE],int lenght)
{
	//first
	double _minTemp = arrayTemp[0];
	for(int i = 0;i<lenght;i++)
	{
		if(arrayTemp[i]<_minTemp)
			_minTemp = arrayTemp[i];
	}
	return _minTemp;
}
kinds _id(const char* str)
{
	if(!strcmp(str,"if"))
		return Keyword_if;
	if(_isSInt32(str))
		return Value_SInt32;
	if(_isFloat(str))
		return Value_Float;
	if(_isInt32(str))
		return Value_Int32;
	if(!strcmp("true",str))
		return Value_true;
	if(!strcmp("false",str))
		return Value_false;
	if(!strcmp("int",str))
		return Type_int;
	if(!strcmp("bool",str))
		return Type_bool;
	if(!strcmp("char",str))
		return Type_char;
	if(!strcmp("+",str) || !strcmp("*",str) || !strcmp("/",str) || !strcmp("-",str))
		return Math;
	if(!strcmp("||",str) || !strcmp("&&",str))
		return Condition;
	if(!strcmp("|",str) || !strcmp("&",str))
		return Logic;
	if(!strcmp(">",str) || !strcmp("<",str) || !strcmp("<=",str) || !strcmp(">=",str) || !strcmp("!=",str) || !strcmp("==",str))
		return Compare;
	return nonIdentified;

}
bool _isInt32(const char *str)
{
	//Value_int
	bool _flagInt32 = false;
	if(!str[0] == '-' && !isdigit(str[0]))
		_flagInt32 = true;
	for(int i =1;i<strlen(str);i++)
	{
		if(!isdigit(str[i]))
			_flagInt32 = true;
	}
	if(!_flagInt32)
		return true;
	else
		return false;
}
bool _isFloat(const char *str)
{
	
	//Value_float
	bool _flagNDigit = false;
	int  _Dot = 0;
	if(str[0] != '-' && !isdigit(str[0]))
		_flagNDigit = true;
	for(int i =1;i<strlen(str);i++)
	{
		if(!isdigit(str[i]) &&  str[i]!='.')
			_flagNDigit = true;
		if(str[i]=='.')
			_Dot++;
	}
	if(_Dot<=1 && !_flagNDigit && str[strlen(str)]!='.')
		return true;
	else
		return false;
}
bool _isSInt32(const char *str)
{
	int _E = 0;
	for(int i =1 ; i<strlen(str)-1;i++)
		if(str[i] == 'e')
			_E++;
	if(str[0]=='e'|| str[strlen(str)] == 'e')
		return false;
	if(_E==1)
	{
		char* _temp;
		char cpy[SIZE];
		strcpy(cpy,str);
		_temp = strtok(cpy,"e");
		if(!_isInt32(_temp))
			return false;
		else
		{
		_temp = strtok(NULL,"e");
		if(!_isInt32(_temp))
			return false;
		else
			return true;
		}
	}
	else
		return false;
}
bool _isDigitORAlpha(const char c)
{
	if(isdigit(c) || c=='_')
		return true;
	if(c<='z' && c>='a')
		return true;
	if(c<='Z' && c>='A')
		return true;
	return false;
}
bool _prntzCheck(line* thisLine)
{
	if((*thisLine).Num == -1) return false;
	bool _flag = false;
	


	if((*thisLine).Num != -1 && (*thisLine).Error == NoError)
	{
		int _first = -1;
		bool _firstFlag = false;
		int _last = -1;
		int _prntzStack = 0;
		bool _1flag = false;
		char _betweenPrntz[SIZE];
		int k = 0;
		char _newLine[SIZE];
		int l=0;
		char _newName[SIZE];
		char _after[SIZE];
		int m=0;
		for(int i = 0;i<strlen((*thisLine).Value);i++)
		{
			if((*thisLine).Value[i] == '(')
			{
					_prntzStack++;
					_1flag = true;
			}
			if((*thisLine).Value[i] == ')')
				_prntzStack--;
			if(_prntzStack == 1 && !_firstFlag)
			{
				_first = i;
				_firstFlag = true;
			}
			if(_1flag && _prntzStack==0 && _first !=-1)
			{
				_last = i;
				_flag = true;
				for(int j = _first+1; j<=_last-1 ; j++)
				{
					_betweenPrntz[k++] = (*thisLine).Value[j];
				}
				_betweenPrntz[k] = '\0';
				//copying before first
				for(int j =0;j<_first;j++)
				{
					_newLine[l++] = (*thisLine).Value[j];
				}
				_newLine[l] = '\0';
				strcpy(_newName,_randomName());
				strcat(_newLine,_newName);
				for(int j=_last+1;j<strlen((*thisLine).Value)+1;j++)
				{
					_after[m++] = (*thisLine).Value[j];
				}
				strcat(_newLine,_after);
				int _newLineIndex = _addLine(_newLine,((*thisLine).Num + _nextNum((*thisLine).Num))/2,(*thisLine).ParentLine);
				//VVar init
				VirtualVars[VVarCounter].InitLineNum = (*thisLine).Num;
				strcpy(VirtualVars[VVarCounter++].Name,_newName);
				// end of vvar init
				strcpy((*thisLine).Value,_newName);
				strcat((*thisLine).Value," = ");
				strcat((*thisLine).Value,_betweenPrntz);
				strcat((*thisLine).Value," ;");
				break;
			}
			

		}
	}

	return _flag;
}
bool _multiplyCheck(line* thisLine)
{

	if((*thisLine).Num == -1) return false;
	bool _flag = false;

	
	if(_mathOperatorCounter((*thisLine).Value) == 1) return false;
	// * counter
	int _counter = 0;
	for(int i=0;i<strlen((*thisLine).Value);i++)
	{
		if((*thisLine).Value[i] == '*')
			_counter++;
	}
	if(_counter ==0)
		return false;
	//end of * counter 
	//R2 : a*b   ->    N ; N = a*b;
	if((*thisLine).Error ==NoError )
	{
		for(int i = 0 ; i<strlen((*thisLine).Value);i++)
		{
			if((*thisLine).Value[i] == '*')
			{
				_flag = true;
				int _from1 = -1 , _from2 = -1 , _until1 = -1 , _until2 = -1;
				for(int j = i-1;j>0;j--)
				{
					if(_isDigitORAlpha((*thisLine).Value[j]) && _until1 ==-1)
					{
						_until1 = j;
					}
					if(_until1 !=-1 && !_isDigitORAlpha((*thisLine).Value[j]))
					{
						_from1 = j+1;
						break;
					}
				}
				for(int j = i+1;j<=strlen((*thisLine).Value);j++)
				{
					if(_isDigitORAlpha((*thisLine).Value[j]) && _from2 ==-1)
					{
						_from2 = j;
					}
					if(_from2 !=-1 && !_isDigitORAlpha((*thisLine).Value[j]))
					{
						_until2 = j-1;
						break;
					}
				}
				if(_from1 != -1 && _from2 != -1 && _until1 != -1 && _until2 != -1 )
				{
					char _newLine[SIZE];
					int k=0;
					for(k=0;k<_from1;k++)
					{
						_newLine[k] = (*thisLine).Value[k];
					}
					_newLine[k] = '\0';
					char _newName[SIZE];
					strcpy(_newName,_randomName());
					//VVar init
					VirtualVars[VVarCounter].InitLineNum = (*thisLine).Num;
					strcpy(VirtualVars[VVarCounter++].Name,_newName);
					// end of vvar init
					strcat(_newLine,_newName);
					char _afterU2[SIZE];
					int l = 0;
					for(int j = _until2+1; j<strlen((*thisLine).Value)+1;j++)
					{
						_afterU2[l++] = (*thisLine).Value[j];
					}
					strcat(_newLine,_afterU2);
					_addLine(_newLine,((*thisLine).Num + _nextNum((*thisLine).Num))/2,(*thisLine).ParentLine);
					char _between[SIZE];
					int m=0;
					for(int j = _from1;j<=_until2;j++)
					{
						_between[m++] = (*thisLine).Value[j];
					}
					_between[m] = '\0';
					strcpy((*thisLine).Value,_newName);
					strcat((*thisLine).Value," = ");
					strcat((*thisLine).Value,_between);
					strcat((*thisLine).Value," ;");
					break;
				}
			}
		}
	}

	return _flag;
}
bool _devideCheck(line* thisLine)
{

	if((*thisLine).Num == -1) return false;
	bool _flag = false;


	
	if(_mathOperatorCounter((*thisLine).Value) == 1) return false;

		// / counter
	int _counter = 0;
	for(int i=0;i<strlen((*thisLine).Value);i++)
	{
		if((*thisLine).Value[i] == '/')
			_counter++;
	}
	if(_counter ==0)
		return false;
	//end of * counter 

	
	//R2 : a*b   ->    N ; N = a*b;
	if((*thisLine).Error ==NoError )
	{
		for(int i = 0 ; i<strlen((*thisLine).Value);i++)
		{
			if((*thisLine).Value[i] == '/')
			{
				_flag = true;
				int _from1 = -1 , _from2 = -1 , _until1 = -1 , _until2 = -1;
				for(int j = i-1;j>0;j--)
				{
					if(_isDigitORAlpha((*thisLine).Value[j]) && _until1 ==-1)
					{
						_until1 = j;
					}
					if(_until1 !=-1 && !_isDigitORAlpha((*thisLine).Value[j]))
					{
						_from1 = j+1;
						break;
					}
				}
				for(int j = i+1;j<=strlen((*thisLine).Value);j++)
				{
					if(_isDigitORAlpha((*thisLine).Value[j]) && _from2 ==-1)
					{
						_from2 = j;
					}
					if(_from2 !=-1 && !_isDigitORAlpha((*thisLine).Value[j]))
					{
						_until2 = j-1;
						break;
					}
				}
				if(_from1 != -1 && _from2 != -1 && _until1 != -1 && _until2 != -1 )
				{
					char _newLine[SIZE];
					int k=0;
					for(k=0;k<_from1;k++)
					{
						_newLine[k] = (*thisLine).Value[k];
					}
					_newLine[k] = '\0';
					char _newName[SIZE];
					strcpy(_newName,_randomName());
					//VVar init
					VirtualVars[VVarCounter].InitLineNum = (*thisLine).Num;
					strcpy(VirtualVars[VVarCounter++].Name,_newName);
					// end of vvar init
					strcat(_newLine,_newName);
					char _afterU2[SIZE];
					int l = 0;
					for(int j = _until2+1; j<strlen((*thisLine).Value)+1;j++)
					{
						_afterU2[l++] = (*thisLine).Value[j];
					}
					strcat(_newLine,_afterU2);
					_addLine(_newLine,((*thisLine).Num + _nextNum((*thisLine).Num))/2,(*thisLine).ParentLine);
					char _between[SIZE];
					int m=0;
					for(int j = _from1;j<=_until2;j++)
					{
						_between[m++] = (*thisLine).Value[j];
					}
					_between[m] = '\0';
					strcpy((*thisLine).Value,_newName);
					strcat((*thisLine).Value," = ");
					strcat((*thisLine).Value,_between);
					strcat((*thisLine).Value," ;");
					break;
				}
			}
		}
	}

	return _flag;
}
bool _plusCheck(line* thisLine)
{

	if((*thisLine).Num == -1) return false;
	bool _flag = false;


	
	if(_mathOperatorCounter((*thisLine).Value) == 1) return false;

		// / counter
	int _counter = 0;
	for(int i=0;i<strlen((*thisLine).Value);i++)
	{
		if((*thisLine).Value[i] == '+')
			_counter++;
	}
	if(_counter ==0)
		return false;
	//end of * counter 

	
	//R2 : a*b   ->    N ; N = a*b;
	if((*thisLine).Error ==NoError )
	{
		for(int i = 0 ; i<strlen((*thisLine).Value);i++)
		{
			if((*thisLine).Value[i] == '+')
			{
				_flag = true;
				int _from1 = -1 , _from2 = -1 , _until1 = -1 , _until2 = -1;
				for(int j = i-1;j>0;j--)
				{
					if(_isDigitORAlpha((*thisLine).Value[j]) && _until1 ==-1)
					{
						_until1 = j;
					}
					if(_until1 !=-1 && !_isDigitORAlpha((*thisLine).Value[j]))
					{
						_from1 = j+1;
						break;
					}
				}
				for(int j = i+1;j<=strlen((*thisLine).Value);j++)
				{
					if(_isDigitORAlpha((*thisLine).Value[j]) && _from2 ==-1)
					{
						_from2 = j;
					}
					if(_from2 !=-1 && !_isDigitORAlpha((*thisLine).Value[j]))
					{
						_until2 = j-1;
						break;
					}
				}
				if(_from1 != -1 && _from2 != -1 && _until1 != -1 && _until2 != -1 )
				{
					char _newLine[SIZE];
					int k=0;
					for(k=0;k<_from1;k++)
					{
						_newLine[k] = (*thisLine).Value[k];
					}
					_newLine[k] = '\0';
					char _newName[SIZE];
					strcpy(_newName,_randomName());
					//VVar init
					VirtualVars[VVarCounter].InitLineNum = (*thisLine).Num;
					strcpy(VirtualVars[VVarCounter++].Name,_newName);
					// end of vvar init
					strcat(_newLine,_newName);
					char _afterU2[SIZE];
					int l = 0;
					for(int j = _until2+1; j<strlen((*thisLine).Value)+1;j++)
					{
						_afterU2[l++] = (*thisLine).Value[j];
					}
					strcat(_newLine,_afterU2);
					_addLine(_newLine,((*thisLine).Num + _nextNum((*thisLine).Num))/2,(*thisLine).ParentLine);
					char _between[SIZE];
					int m=0;
					for(int j = _from1;j<=_until2;j++)
					{
						_between[m++] = (*thisLine).Value[j];
					}
					_between[m] = '\0';
					strcpy((*thisLine).Value,_newName);
					strcat((*thisLine).Value," = ");
					strcat((*thisLine).Value,_between);
					strcat((*thisLine).Value," ;");
					break;
				}
			}
		}
	}

	return _flag;
}
bool _minusCheck(line* thisLine)
{

	if((*thisLine).Num == -1) return false;
	bool _flag = false;


	
	if(_mathOperatorCounter((*thisLine).Value) == 1) return false;
		// / counter
	int _counter = 0;
	for(int i=0;i<strlen((*thisLine).Value);i++)
	{
		if((*thisLine).Value[i] == '-')
			_counter++;
	}
	if(_counter ==0)
		return false;
	//end of * counter 

	
	//R2 : a*b   ->    N ; N = a*b;
	if((*thisLine).Error ==NoError )
	{
		for(int i = 0 ; i<strlen((*thisLine).Value);i++)
		{
			if((*thisLine).Value[i] == '-')
			{
				_flag = true;
				int _from1 = -1 , _from2 = -1 , _until1 = -1 , _until2 = -1;
				for(int j = i-1;j>0;j--)
				{
					if(_isDigitORAlpha((*thisLine).Value[j]) && _until1 ==-1)
					{
						_until1 = j;
					}
					if(_until1 !=-1 && !_isDigitORAlpha((*thisLine).Value[j]))
					{
						_from1 = j+1;
						break;
					}
				}
				for(int j = i+1;j<=strlen((*thisLine).Value);j++)
				{
					if(_isDigitORAlpha((*thisLine).Value[j]) && _from2 ==-1)
					{
						_from2 = j;
					}
					if(_from2 !=-1 && !_isDigitORAlpha((*thisLine).Value[j]))
					{
						_until2 = j-1;
						break;
					}
				}
				if(_from1 != -1 && _from2 != -1 && _until1 != -1 && _until2 != -1 )
				{
					char _newLine[SIZE];
					int k=0;
					for(k=0;k<_from1;k++)
					{
						_newLine[k] = (*thisLine).Value[k];
					}
					_newLine[k] = '\0';
					char _newName[SIZE];
					strcpy(_newName,_randomName());
					//VVar init
					VirtualVars[VVarCounter].InitLineNum = (*thisLine).Num;
					strcpy(VirtualVars[VVarCounter++].Name,_newName);
					// end of vvar init
					strcat(_newLine,_newName);
					char _afterU2[SIZE];
					int l = 0;
					for(int j = _until2+1; j<strlen((*thisLine).Value)+1;j++)
					{
						_afterU2[l++] = (*thisLine).Value[j];
					}
					strcat(_newLine,_afterU2);
					_addLine(_newLine,((*thisLine).Num + _nextNum((*thisLine).Num))/2,(*thisLine).ParentLine);
					char _between[SIZE];
					int m=0;
					for(int j = _from1;j<=_until2;j++)
					{
						_between[m++] = (*thisLine).Value[j];
					}
					_between[m] = '\0';
					strcpy((*thisLine).Value,_newName);
					strcat((*thisLine).Value," = ");
					strcat((*thisLine).Value,_between);
					strcat((*thisLine).Value," ;");
					break;
				}
			}
		}
	}

	return _flag;
}
bool _biggerThanCheck(line* thisLine)
{

	if((*thisLine).Num == -1) return false;
	bool _flag = false;

	
	if(_mathOperatorCounter((*thisLine).Value) == 1) return false;
		// / counter
	int _counter = 0;
	for(int i=0;i<strlen((*thisLine).Value);i++)
	{
		if((*thisLine).Value[i] == '>')
			_counter++;
	}
	if(_counter ==0)
		return false;
	//end of * counter 

	
	//R2 : a*b   ->    N ; N = a*b;
	if((*thisLine).Error ==NoError )
	{
		for(int i = 0 ; i<strlen((*thisLine).Value);i++)
		{
			if((*thisLine).Value[i] == '>')
			{
				_flag = true;
				int _from1 = -1 , _from2 = -1 , _until1 = -1 , _until2 = -1;
				for(int j = i-1;j>0;j--)
				{
					if(_isDigitORAlpha((*thisLine).Value[j]) && _until1 ==-1)
					{
						_until1 = j;
					}
					if(_until1 !=-1 && !_isDigitORAlpha((*thisLine).Value[j]))
					{
						_from1 = j+1;
						break;
					}
				}
				for(int j = i+1;j<=strlen((*thisLine).Value);j++)
				{
					if(_isDigitORAlpha((*thisLine).Value[j]) && _from2 ==-1)
					{
						_from2 = j;
					}
					if(_from2 !=-1 && !_isDigitORAlpha((*thisLine).Value[j]))
					{
						_until2 = j-1;
						break;
					}
				}
				if(_from1 != -1 && _from2 != -1 && _until1 != -1 && _until2 != -1 )
				{
					char _newLine[SIZE];
					int k=0;
					for(k=0;k<_from1;k++)
					{
						_newLine[k] = (*thisLine).Value[k];
					}
					_newLine[k] = '\0';
					char _newName[SIZE];
					strcpy(_newName,_randomName());
					//VVar init
					VirtualVars[VVarCounter].InitLineNum = (*thisLine).Num;
					strcpy(VirtualVars[VVarCounter++].Name,_newName);
					// end of vvar init
					strcat(_newLine,_newName);
					char _afterU2[SIZE];
					int l = 0;
					for(int j = _until2+1; j<strlen((*thisLine).Value)+1;j++)
					{
						_afterU2[l++] = (*thisLine).Value[j];
					}
					strcat(_newLine,_afterU2);
					_addLine(_newLine,((*thisLine).Num + _nextNum((*thisLine).Num))/2,(*thisLine).ParentLine);
					char _between[SIZE];
					int m=0;
					for(int j = _from1;j<=_until2;j++)
					{
						_between[m++] = (*thisLine).Value[j];
					}
					_between[m] = '\0';
					strcpy((*thisLine).Value,_newName);
					strcat((*thisLine).Value," = ");
					strcat((*thisLine).Value,_between);
					strcat((*thisLine).Value," ;");
					break;
				}
			}
		}
	}

	return _flag;
}
bool _smallerThanCheck(line* thisLine)
{

	if((*thisLine).Num == -1) return false;
	bool _flag = false;


	
	if(_mathOperatorCounter((*thisLine).Value) == 1) return false;
		// / counter
	int _counter = 0;
	for(int i=0;i<strlen((*thisLine).Value);i++)
	{
		if((*thisLine).Value[i] == '<')
			_counter++;
	}
	if(_counter ==0)
		return false;
	//end of * counter 

	
	//R2 : a*b   ->    N ; N = a*b;
	if((*thisLine).Error ==NoError )
	{
		for(int i = 0 ; i<strlen((*thisLine).Value);i++)
		{
			if((*thisLine).Value[i] == '<')
			{
				_flag = true;
				int _from1 = -1 , _from2 = -1 , _until1 = -1 , _until2 = -1;
				for(int j = i-1;j>0;j--)
				{
					if(_isDigitORAlpha((*thisLine).Value[j]) && _until1 ==-1)
					{
						_until1 = j;
					}
					if(_until1 !=-1 && !_isDigitORAlpha((*thisLine).Value[j]))
					{
						_from1 = j+1;
						break;
					}
				}
				for(int j = i+1;j<=strlen((*thisLine).Value);j++)
				{
					if(_isDigitORAlpha((*thisLine).Value[j]) && _from2 ==-1)
					{
						_from2 = j;
					}
					if(_from2 !=-1 && !_isDigitORAlpha((*thisLine).Value[j]))
					{
						_until2 = j-1;
						break;
					}
				}
				if(_from1 != -1 && _from2 != -1 && _until1 != -1 && _until2 != -1 )
				{
					char _newLine[SIZE];
					int k=0;
					for(k=0;k<_from1;k++)
					{
						_newLine[k] = (*thisLine).Value[k];
					}
					_newLine[k] = '\0';
					char _newName[SIZE];
					strcpy(_newName,_randomName());
					//VVar init
					VirtualVars[VVarCounter].InitLineNum = (*thisLine).Num;
					strcpy(VirtualVars[VVarCounter++].Name,_newName);
					// end of vvar init
					strcat(_newLine,_newName);
					char _afterU2[SIZE];
					int l = 0;
					for(int j = _until2+1; j<strlen((*thisLine).Value)+1;j++)
					{
						_afterU2[l++] = (*thisLine).Value[j];
					}
					strcat(_newLine,_afterU2);
					_addLine(_newLine,((*thisLine).Num + _nextNum((*thisLine).Num))/2,(*thisLine).ParentLine);
					char _between[SIZE];
					int m=0;
					for(int j = _from1;j<=_until2;j++)
					{
						_between[m++] = (*thisLine).Value[j];
					}
					_between[m] = '\0';
					strcpy((*thisLine).Value,_newName);
					strcat((*thisLine).Value," = ");
					strcat((*thisLine).Value,_between);
					strcat((*thisLine).Value," ;");
					break;
				}
			}
		}
	}

	return _flag;
}
bool _bitWiseAndCheck(line* thisLine)
{
	


	if((*thisLine).Num == -1) return false;
	bool _flag = false;

	
	if(_mathOperatorCounter((*thisLine).Value) == 1) return false;

		// / counter
	int _counter = 0;
	for(int i=0;i<strlen((*thisLine).Value);i++)
	{
		if((*thisLine).Value[i] == '&')
			_counter++;
	}
	if(_counter ==0)
		return false;
	//end of * counter 

	
	//R2 : a*b   ->    N ; N = a*b;
	if((*thisLine).Error ==NoError )
	{
		for(int i = 0 ; i<strlen((*thisLine).Value);i++)
		{
			if((*thisLine).Value[i] == '&')
			{
				_flag = true;
				int _from1 = -1 , _from2 = -1 , _until1 = -1 , _until2 = -1;
				for(int j = i-1;j>0;j--)
				{
					if(_isDigitORAlpha((*thisLine).Value[j]) && _until1 ==-1)
					{
						_until1 = j;
					}
					if(_until1 !=-1 && !_isDigitORAlpha((*thisLine).Value[j]))
					{
						_from1 = j+1;
						break;
					}
				}
				for(int j = i+1;j<=strlen((*thisLine).Value);j++)
				{
					if(_isDigitORAlpha((*thisLine).Value[j]) && _from2 ==-1)
					{
						_from2 = j;
					}
					if(_from2 !=-1 && !_isDigitORAlpha((*thisLine).Value[j]))
					{
						_until2 = j-1;
						break;
					}
				}
				if(_from1 != -1 && _from2 != -1 && _until1 != -1 && _until2 != -1 )
				{
					char _newLine[SIZE];
					int k=0;
					for(k=0;k<_from1;k++)
					{
						_newLine[k] = (*thisLine).Value[k];
					}
					_newLine[k] = '\0';
					char _newName[SIZE];
					strcpy(_newName,_randomName());
					//VVar init
					VirtualVars[VVarCounter].InitLineNum = (*thisLine).Num;
					strcpy(VirtualVars[VVarCounter++].Name,_newName);
					// end of vvar init
					strcat(_newLine,_newName);
					char _afterU2[SIZE];
					int l = 0;
					for(int j = _until2+1; j<strlen((*thisLine).Value)+1;j++)
					{
						_afterU2[l++] = (*thisLine).Value[j];
					}
					strcat(_newLine,_afterU2);
					_addLine(_newLine,((*thisLine).Num + _nextNum((*thisLine).Num))/2,(*thisLine).ParentLine);
					char _between[SIZE];
					int m=0;
					for(int j = _from1;j<=_until2;j++)
					{
						_between[m++] = (*thisLine).Value[j];
					}
					_between[m] = '\0';
					strcpy((*thisLine).Value,_newName);
					strcat((*thisLine).Value," = ");
					strcat((*thisLine).Value,_between);
					strcat((*thisLine).Value," ;");
					break;
				}
			}
		}
	}

	return _flag;

}
bool _bitWiseORCheck(line* thisLine)
{
	


	if((*thisLine).Num == -1) return false;
	bool _flag = false;


	
	
	if(_mathOperatorCounter((*thisLine).Value) == 1) return false;


		// / counter
	int _counter = 0;
	for(int i=0;i<strlen((*thisLine).Value);i++)
	{
		if((*thisLine).Value[i] == '|')
			_counter++;
	}
	if(_counter ==0)
		return false;
	//end of * counter 

	
	//R2 : a*b   ->    N ; N = a*b;
	if((*thisLine).Error ==NoError )
	{
		for(int i = 0 ; i<strlen((*thisLine).Value);i++)
		{
			if((*thisLine).Value[i] == '|')
			{
				_flag = true;
				int _from1 = -1 , _from2 = -1 , _until1 = -1 , _until2 = -1;
				for(int j = i-1;j>0;j--)
				{
					if(_isDigitORAlpha((*thisLine).Value[j]) && _until1 ==-1)
					{
						_until1 = j;
					}
					if(_until1 !=-1 && !_isDigitORAlpha((*thisLine).Value[j]))
					{
						_from1 = j+1;
						break;
					}
				}
				for(int j = i+1;j<=strlen((*thisLine).Value);j++)
				{
					if(_isDigitORAlpha((*thisLine).Value[j]) && _from2 ==-1)
					{
						_from2 = j;
					}
					if(_from2 !=-1 && !_isDigitORAlpha((*thisLine).Value[j]))
					{
						_until2 = j-1;
						break;
					}
				}
				if(_from1 != -1 && _from2 != -1 && _until1 != -1 && _until2 != -1 )
				{
					char _newLine[SIZE];
					int k=0;
					for(k=0;k<_from1;k++)
					{
						_newLine[k] = (*thisLine).Value[k];
					}
					_newLine[k] = '\0';
					char _newName[SIZE];
					strcpy(_newName,_randomName());
					//VVar init
					VirtualVars[VVarCounter].InitLineNum = (*thisLine).Num;
					strcpy(VirtualVars[VVarCounter++].Name,_newName);
					// end of vvar init
					strcat(_newLine,_newName);
					char _afterU2[SIZE];
					int l = 0;
					for(int j = _until2+1; j<strlen((*thisLine).Value)+1;j++)
					{
						_afterU2[l++] = (*thisLine).Value[j];
					}
					strcat(_newLine,_afterU2);
					_addLine(_newLine,((*thisLine).Num + _nextNum((*thisLine).Num))/2,(*thisLine).ParentLine);
					char _between[SIZE];
					int m=0;
					for(int j = _from1;j<=_until2;j++)
					{
						_between[m++] = (*thisLine).Value[j];
					}
					_between[m] = '\0';
					strcpy((*thisLine).Value,_newName);
					strcat((*thisLine).Value," = ");
					strcat((*thisLine).Value,_between);
					strcat((*thisLine).Value," ;");
					break;
				}
			}
		}
	}

	return _flag;

}
bool _Not2EqualZeroCheck(line* thisLine)
{
	if((*thisLine).Num == -1) return false;

	bool _flag = false;

	if((*thisLine).Error ==NoError )
	{
		for(int i = 0 ; i<strlen((*thisLine).Value);i++)
		{
			if((*thisLine).Value[i] == '!')
			{
				_flag = true;
				int  _from2 = -1  , _until2 = -1;
				
				for(int j = i+1;j<=strlen((*thisLine).Value);j++)
				{
					if(_isDigitORAlpha((*thisLine).Value[j]) && _from2 ==-1)
					{
						_from2 = j;
					}
					if(_from2 !=-1 && !_isDigitORAlpha((*thisLine).Value[j]))
					{
						_until2 = j-1;
						break;
					}
				}
				if(_from2 != -1 &&  _until2 != -1  )
				{
					
					char _after[SIZE];
					int l = 0;
					for(int j = _until2+1;j<strlen((*thisLine).Value)+1;j++)
					{
						_after[l++] = (*thisLine).Value[j];
					}

					char _part2[SIZE];
					int k=0;
					for(int j =_from2;j<=_until2;j++)
						_part2[k++] = (*thisLine).Value[j];
					_part2[k] = '\0';
					(*thisLine).Value[i] = '\0';
					strcat((*thisLine).Value," ");
					strcat((*thisLine).Value,_part2);
					strcat((*thisLine).Value," @ 0 ");
					_spaceFix();
					break;
				}

			}

		}

	}
	return _flag;
}
bool _smaller2BiggerCheck(line* thisLine)

{

	if((*thisLine).Num == -1) return false;
	bool _flag = false;


	

		// / counter
	int _counter = 0;
	for(int i=0;i<strlen((*thisLine).Value);i++)
	{
		if((*thisLine).Value[i] == '<' || (*thisLine).Value[i] == '^')
			_counter++;
	}
	if(_counter ==0)
		return false;
	//end of * counter 

	
	//R2 : a*b   ->    N ; N = a*b;
	if((*thisLine).Error ==NoError )
	{
		for(int i = 0 ; i<strlen((*thisLine).Value);i++)
		{
			if((*thisLine).Value[i] == '<' || (*thisLine).Value[i] == '^')
			{
				_flag = true;
				char x = (*thisLine).Value[i];
				int _from1 = -1 , _from2 = -1 , _until1 = -1 , _until2 = -1;
				for(int j = i-1;j>0;j--)
				{
					if(_isDigitORAlpha((*thisLine).Value[j]) && _until1 ==-1)
					{
						_until1 = j;
					}
					if(_until1 !=-1 && !_isDigitORAlpha((*thisLine).Value[j]))
					{
						_from1 = j+1;
						break;
					}
				}
				for(int j = i+1;j<=strlen((*thisLine).Value);j++)
				{
					if(_isDigitORAlpha((*thisLine).Value[j]) && _from2 ==-1)
					{
						_from2 = j;
					}
					if(_from2 !=-1 && !_isDigitORAlpha((*thisLine).Value[j]))
					{
						_until2 = j-1;
						break;
					}
				}
				if(_from1 != -1 && _from2 != -1 && _until1 != -1 && _until2 != -1 )
				{
					char _before[SIZE];
					int k=0;
					for(k=0;k<_from1;k++)
					{
						_before[k] = (*thisLine).Value[k];
					}
					_before[k] = '\0';
					char _part1[SIZE];
					int l =0;
					for(int j =_from1;j<=_until1;j++)
					{
						_part1[l++] = (*thisLine).Value[j];
					}
					_part1[l] = '\0';
					char _part2[SIZE];
					int m =0;
					for(int j =_from2;j<=_until2;j++)
					{
						_part2[m++] = (*thisLine).Value[j];
					}
					_part2[m] = '\0';
					char _after[SIZE];
					int n =0;
					for(int j=_until2+1;j<strlen((*thisLine).Value)+1;j++)
					{
						_after[n++] = (*thisLine).Value[j];
					}
					strcpy((*thisLine).Value,_before);
					strcat((*thisLine).Value,_part2);
					strcat((*thisLine).Value,(x=='<')?" > ":" ? ");
					strcat((*thisLine).Value,_part1);
					strcat((*thisLine).Value,_after);
					break;
				}
			}
		}
	}

	return _flag;
}
bool _2ZeroComp(line* thisLine)

{

	if((*thisLine).Num == -1) return false;
	bool _flag = false;


	

		// / counter
	int _counter = 0;
	for(int i=0;i<strlen((*thisLine).Value);i++)
	{
		if((*thisLine).Value[i] == '>' || (*thisLine).Value[i] == '?' || (*thisLine).Value[i] == '<'|| (*thisLine).Value[i] == '^')
			_counter++;
	}
	if(_counter ==0)
		return false;
	//end of * counter 

	
	//R2 : a*b   ->    N ; N = a*b;
	if((*thisLine).Error ==NoError )
	{
		for(int i = 0 ; i<strlen((*thisLine).Value);i++)
		{
			if(((*thisLine).Value[i] == '>' || (*thisLine).Value[i] == '?' || (*thisLine).Value[i] == '<'|| (*thisLine).Value[i] == '^') && (*thisLine).Value[i+2] != '0')
			{
				_flag = true;
				char x = (*thisLine).Value[i];
				int _from1 = -1 , _from2 = -1 , _until1 = -1 , _until2 = -1;
				for(int j = i-1;j>0;j--)
				{
					if(_isDigitORAlpha((*thisLine).Value[j]) && _until1 ==-1)
					{
						_until1 = j;
					}
					if(_until1 !=-1 && !_isDigitORAlpha((*thisLine).Value[j]))
					{
						_from1 = j+1;
						break;
					}
				}
				for(int j = i+1;j<=strlen((*thisLine).Value);j++)
				{
					if(_isDigitORAlpha((*thisLine).Value[j]) && _from2 ==-1)
					{
						_from2 = j;
					}
					if(_from2 !=-1 && !_isDigitORAlpha((*thisLine).Value[j]))
					{
						_until2 = j-1;
						break;
					}
				}
				if(_from1 != -1 && _from2 != -1 && _until1 != -1 && _until2 != -1 )
				{
					char _before[SIZE];
					int k=0;
					for(k=0;k<_from1;k++)
					{
						_before[k] = (*thisLine).Value[k];
					}
					_before[k] = '\0';
					char _part1[SIZE];
					int l =0;
					for(int j =_from1;j<=_until1;j++)
					{
						_part1[l++] = (*thisLine).Value[j];
					}
					_part1[l] = '\0';
					char _part2[SIZE];
					int m =0;
					for(int j =_from2;j<=_until2;j++)
					{
						_part2[m++] = (*thisLine).Value[j];
					}
					_part2[m] = '\0';
					char _after[SIZE];
					int n =0;
					for(int j=_until2+1;j<strlen((*thisLine).Value)+1;j++)
					{
						_after[n++] = (*thisLine).Value[j];
					}
					strcpy((*thisLine).Value,_before);
					strcat((*thisLine).Value," ");
					strcat((*thisLine).Value,_part1);
					strcat((*thisLine).Value," - ");
					strcat((*thisLine).Value,_part2);
					strcat((*thisLine).Value,(x=='>')?" > 0 ":((x=='?')?" ? 0 ":((x=='<')?" < ":" ^ ")));
					strcat((*thisLine).Value,_after);
					_fix();
					break;
				}
			}
		}
	}

	return _flag;
}
bool _biggerThanSmallerThanEqual2OR(line* thisLine)
{

	if((*thisLine).Num == -1) return false;
	bool _flag = false;


	

		// / counter
	int _counter = 0;
	for(int i=0;i<strlen((*thisLine).Value);i++)
	{
		if((*thisLine).Value[i] == '?' || (*thisLine).Value[i] == '^')
			_counter++;
	}
	if(_counter ==0)
		return false;
	//end of * counter 

	
	//R2 : a*b   ->    N ; N = a*b;
	if((*thisLine).Error ==NoError )
	{
		for(int i = 0 ; i<strlen((*thisLine).Value);i++)
		{
			if((*thisLine).Value[i] == '?' || (*thisLine).Value[i] == '^')
			{
				char x =(*thisLine).Value[i];
				_flag = true;
				int _from1 = -1 , _from2 = -1 , _until1 = -1 , _until2 = -1;
				for(int j = i-1;j>0;j--)
				{
					if(_isDigitORAlpha((*thisLine).Value[j]) && _until1 ==-1)
					{
						_until1 = j;
					}
					if(_until1 !=-1 && !_isDigitORAlpha((*thisLine).Value[j]))
					{
						_from1 = j+1;
						break;
					}
				}
				for(int j = i+1;j<=strlen((*thisLine).Value);j++)
				{
					if(_isDigitORAlpha((*thisLine).Value[j]) && _from2 ==-1)
					{
						_from2 = j;
					}
					if(_from2 !=-1 && !_isDigitORAlpha((*thisLine).Value[j]))
					{
						_until2 = j-1;
						break;
					}
				}
				if(_from1 != -1 && _from2 != -1 && _until1 != -1 && _until2 != -1 )
				{
					char _before[SIZE];
					int k=0;
					for(k=0;k<_from1;k++)
					{
						_before[k] = (*thisLine).Value[k];
					}
					_before[k] = '\0';
					char _part1[SIZE];
					int l =0;
					for(int j =_from1;j<=_until1;j++)
					{
						_part1[l++] = (*thisLine).Value[j];
					}
					_part1[l] = '\0';
					char _part2[SIZE];
					int m =0;
					for(int j =_from2;j<=_until2;j++)
					{
						_part2[m++] = (*thisLine).Value[j];
					}
					_part2[m] = '\0';
					char _after[SIZE];
					int n =0;
					for(int j=_until2+1;j<strlen((*thisLine).Value)+1;j++)
					{
						_after[n++] = (*thisLine).Value[j];
					}
					strcpy((*thisLine).Value,_before);
					strcat((*thisLine).Value," ");
					strcat((*thisLine).Value,_part1);
					strcat((*thisLine).Value,(x=='?') ? " > ":" < ");
					strcat((*thisLine).Value,_part2);
					strcat((*thisLine).Value," . ");
					strcat((*thisLine).Value,_part1);
					strcat((*thisLine).Value," @ ");
					strcat((*thisLine).Value,_part2);
					strcat((*thisLine).Value," ");
					strcat((*thisLine).Value,_after);
					_fix();
					break;
				}
			}
		}
	}

	return _flag;
}
void _mathAssistant()
{
	for(int i=0;i<SIZE;i++)
		for(;_multiplyCheck(&Lines[i]);){}
	for(int i=0;i<SIZE;i++)
		for(;_devideCheck(&Lines[i]);){}
	for(int i=0;i<SIZE;i++)
		for(;_plusCheck(&Lines[i]);){}
	for(int i=0;i<SIZE;i++)
		for(;_minusCheck(&Lines[i]);){}
}
bool _compareAssistant(line* thisLine)	

	
{
	_fix();
	if((*thisLine).Num == -1) return false;
	bool _flag = false;


	
	//if(_mathOperatorCounter((*thisLine).Value) == 1) return false;

		// / counter
	int _counter = 0;
	for(int i=0;i<strlen((*thisLine).Value);i++)
	{
		if((*thisLine).Value[i] == '^' || (*thisLine).Value[i] == '?' || (*thisLine).Value[i] == '<' || (*thisLine).Value[i] == '>'|| (*thisLine).Value[i] == '@'|| (*thisLine).Value[i] == '~')
			_counter++;
	}
	if(_counter ==0)
		return false;
	//= flag
	bool _letFlag = false;
	for(int i = 0; i<strlen((*thisLine).Value);i++)
		if((*thisLine).Value[i] == '=')
			_letFlag = true;
	if(_counter==1 &&  _letFlag)
		return false;
	//end of * counter 

	
	//R2 : a*b   ->    N ; N = a*b;
	if((*thisLine).Error ==NoError )
	{
		for(int i = 0 ; i<strlen((*thisLine).Value);i++)
		{
			if((*thisLine).Value[i] == '^' || (*thisLine).Value[i] == '?' || (*thisLine).Value[i] == '<' || (*thisLine).Value[i] == '>'|| (*thisLine).Value[i] == '@'|| (*thisLine).Value[i] == '~')
			{
				char x = (*thisLine).Value[i];
				
				int _from1 = -1 , _from2 = -1 , _until1 = -1 , _until2 = -1;
				for(int j = i-1;j>0;j--)
				{
					if(_isDigitORAlpha((*thisLine).Value[j]) && _until1 ==-1)
					{
						_until1 = j;
					}
					if(_until1 !=-1 && !_isDigitORAlpha((*thisLine).Value[j]))
					{
						_from1 = j+1;
						break;
					}
				}
				for(int j = i+1;j<=strlen((*thisLine).Value);j++)
				{
					if(_isDigitORAlpha((*thisLine).Value[j]) && _from2 ==-1)
					{
						_from2 = j;
					}
					if(_from2 !=-1 && !_isDigitORAlpha((*thisLine).Value[j]))
					{
						_until2 = j-1;
						break;
					}
				}
				if(_from1 != -1 && _from2 != -1 && _until1 != -1 && _until2 != -1 )
				{
					_flag = true;
					char _newLine[SIZE];
					int k=0;
					for(k=0;k<_from1;k++)
					{
						_newLine[k] = (*thisLine).Value[k];
					}
					_newLine[k] = '\0';
					char _newName[SIZE];
					strcpy(_newName,_randomName());
					//VVar init
					VirtualVars[VVarCounter].InitLineNum = (*thisLine).Num;
					strcpy(VirtualVars[VVarCounter++].Name,_newName);
					// end of vvar init
					strcat(_newLine,_newName);
					char _afterU2[SIZE];
					int l = 0;
					for(int j = _until2+1; j<strlen((*thisLine).Value)+1;j++)
					{
						_afterU2[l++] = (*thisLine).Value[j];
					}
					strcat(_newLine,_afterU2);
					_addLine(_newLine,((*thisLine).Num + _nextNum((*thisLine).Num))/2,(*thisLine).ParentLine);
					char _between[SIZE];
					int m=0;
					for(int j = _from1;j<=_until2;j++)
					{
						_between[m++] = (*thisLine).Value[j];
					}
					_between[m] = '\0';
					strcpy((*thisLine).Value,_newName);
					strcat((*thisLine).Value," = ");
					strcat((*thisLine).Value,_between);
					strcat((*thisLine).Value," ;");
					break;
				}
			}
		}
	}

	return _flag;
}
bool _andORAssistant(line* thisLine)	

	
{

	if((*thisLine).Num == -1) return false;
	bool _flag = false;


	
	if(_mathOperatorCounter((*thisLine).Value) == 1) return false;

		// / counter
	int _counter = 0;
	for(int i=0;i<strlen((*thisLine).Value);i++)
	{
		if((*thisLine).Value[i] == '.' || (*thisLine).Value[i] == '%' )
			_counter++;
	}
	if(_counter ==0)
		return false;
	//end of * counter 

	
	//R2 : a*b   ->    N ; N = a*b;
	if((*thisLine).Error ==NoError )
	{
		for(int i = 0 ; i<strlen((*thisLine).Value);i++)
		{
			if((*thisLine).Value[i] == '.' || (*thisLine).Value[i] == '%' )
			{
				_flag = true;
				int _from1 = -1 , _from2 = -1 , _until1 = -1 , _until2 = -1;
				for(int j = i-1;j>0;j--)
				{
					if(_isDigitORAlpha((*thisLine).Value[j]) && _until1 ==-1)
					{
						_until1 = j;
					}
					if(_until1 !=-1 && !_isDigitORAlpha((*thisLine).Value[j]))
					{
						_from1 = j+1;
						break;
					}
				}
				for(int j = i+1;j<=strlen((*thisLine).Value);j++)
				{
					if(_isDigitORAlpha((*thisLine).Value[j]) && _from2 ==-1)
					{
						_from2 = j;
					}
					if(_from2 !=-1 && !_isDigitORAlpha((*thisLine).Value[j]))
					{
						_until2 = j-1;
						break;
					}
				}
				if(_from1 != -1 && _from2 != -1 && _until1 != -1 && _until2 != -1 )
				{
					char _newLine[SIZE];
					int k=0;
					for(k=0;k<_from1;k++)
					{
						_newLine[k] = (*thisLine).Value[k];
					}
					_newLine[k] = '\0';
					char _newName[SIZE];
					strcpy(_newName,_randomName());
					//VVar init
					VirtualVars[VVarCounter].InitLineNum = (*thisLine).Num;
					strcpy(VirtualVars[VVarCounter++].Name,_newName);
					// end of vvar init
					strcat(_newLine,_newName);
					char _afterU2[SIZE];
					int l = 0;
					for(int j = _until2+1; j<strlen((*thisLine).Value)+1;j++)
					{
						_afterU2[l++] = (*thisLine).Value[j];
					}
					strcat(_newLine,_afterU2);
					_addLine(_newLine,((*thisLine).Num + _nextNum((*thisLine).Num))/2,(*thisLine).ParentLine);
					char _between[SIZE];
					int m=0;
					for(int j = _from1;j<=_until2;j++)
					{
						_between[m++] = (*thisLine).Value[j];
					}
					_between[m] = '\0';
					strcpy((*thisLine).Value,_newName);
					strcat((*thisLine).Value," = ");
					strcat((*thisLine).Value,_between);
					strcat((*thisLine).Value," ;");
					break;
				}
			}
		}
	}

	return _flag;
}
bool _openBoxGotoCheck(line*  thisLine)
{
	if((*thisLine).Num == -1) return false;

	bool _flag = false;

	if((*thisLine).Value[0] == '{' && (*thisLine).Value[1]!=' ')
	{
		
		double _tempNum=(*thisLine).Num;
		int _BoxStack=0;
		bool _1flag=false;
		for(_tempNum=(*thisLine).Num;Lines[_index(_tempNum)].Num!=-1;_tempNum=_nextNum(_tempNum))
		{
			if(Lines[_index(_tempNum)].Value[0] == '{')
			{
				_BoxStack++;
				_1flag=true;
			}
			if(Lines[_index(_tempNum)].Value[0] == '}')
				_BoxStack--;
			if(_BoxStack==0 && _1flag)
			{
				_flag = true;
				strcat((*thisLine).Value," goto #");
				strcat(Lines[_index(_tempNum)].Value," #");
				char num1[10],num2[10] ;
				sprintf(num1,"A%d",LCounter);
				sprintf(num2,"B%d",LCounter++);
				strcat((*thisLine).Value,num1);
				strcat(Lines[_index(_tempNum)].Value,num2);
				break;
			}
		}
	}

	return _flag;

}
bool _orTranslate(line* thisLine)

{

	if((*thisLine).Num == -1) return false;
	bool _flag = false;


	
	
		// / counter
	int _counter = 0;
	for(int i=0;i<strlen((*thisLine).Value);i++)
	{
		if((*thisLine).Value[i] == '.')
			_counter++;
	}
	if(_counter ==0)
		return false;
	//end of * counter 

	
	//R2 : a*b   ->    N ; N = a*b;
	if((*thisLine).Error ==NoError )
	{
		for(int i = 0 ; i<strlen((*thisLine).Value);i++)
		{
			if((*thisLine).Value[i] == '.')
			{
				_flag = true;
				int _from1 = -1 , _from2 = -1 , _until1 = -1 , _until2 = -1;
				for(int j = i-1;j>0;j--)
				{
					if(_isDigitORAlpha((*thisLine).Value[j]) && _until1 ==-1)
					{
						_until1 = j;
					}
					if(_until1 !=-1 && !_isDigitORAlpha((*thisLine).Value[j]))
					{
						_from1 = j+1;
						break;
					}
				}
				for(int j = i+1;j<=strlen((*thisLine).Value);j++)
				{
					if(_isDigitORAlpha((*thisLine).Value[j]) && _from2 ==-1)
					{
						_from2 = j;
					}
					if(_from2 !=-1 && !_isDigitORAlpha((*thisLine).Value[j]))
					{
						_until2 = j-1;
						break;
					}
				}
				if(_from1 != -1 && _from2 != -1 && _until1 != -1 && _until2 != -1 )
				{
					char _before[SIZE];
					int k=0;
					for(k=0;k<_from1;k++)
					{
						_before[k] = (*thisLine).Value[k];
					}
					_before[k] = '\0';
					char _part1[SIZE];
					int l =0;
					for(int j =_from1;j<=_until1;j++)
					{
						_part1[l++] = (*thisLine).Value[j];
					}
					_part1[l] = '\0';
					char _part2[SIZE];
					int m =0;
					for(int j =_from2;j<=_until2;j++)
					{
						_part2[m++] = (*thisLine).Value[j];
					}
					_part2[m] = '\0';
					char _after[SIZE];
					int n =0;
					for(int j=_until2+1;j<strlen((*thisLine).Value)+1;j++)
					{
						_after[n++] = (*thisLine).Value[j];
					}



					char _newName[SIZE];
					strcpy(_newName,_randomName());
					//VVar init
					VirtualVars[VVarCounter].InitLineNum = (*thisLine).Num;
					strcpy(VirtualVars[VVarCounter++].Name,_newName);
					// end of vvar init

					char _line1[SIZE];
					sprintf(_line1,"%s = 1 ;",_newName);
					char _line2[SIZE];
					sprintf(_line2,"if ( %s @ 0 %s %s @ 0 )",_part1,"%",_part2);
					char _line3[] = "{";
					char _line4[SIZE];
					sprintf(_line4,"%s = 0 ;",_newName);
					char _line5[] = "}";
					char _line6[SIZE];
					sprintf(_line6,"%s%s%s",_before,_newName,_after);
					double nx = _nextNum((*thisLine).Num);

					_addLine(_line1,((*thisLine).Num + 1*nx)/7,(*thisLine).ParentLine);
					_addLine(_line2,((*thisLine).Num + 2*nx)/7,(*thisLine).ParentLine);
					_addLine(_line3,((*thisLine).Num + 3*nx)/7,(*thisLine).ParentLine);
					_addLine(_line4,((*thisLine).Num + 4*nx)/7,(*thisLine).ParentLine);
					_addLine(_line5,((*thisLine).Num + 5*nx)/7,(*thisLine).ParentLine);
					_addLine(_line6,((*thisLine).Num + 6*nx)/7,(*thisLine).ParentLine);

					(*thisLine).Num = -1;
					break;
				}
			}
		}
	}

	return _flag;
}
bool _elseTranslate(line* thisLine)
{
	if((*thisLine).Num == -1) return false;

	bool _flag = false;

	if((*thisLine).Value[0] == 'i' && (*thisLine).Value[1] == 'f')
	{
		
		double _tempNum=(*thisLine).Num;
		int _BoxStack=0;
		bool _1flag=false;
		for(_tempNum=(*thisLine).Num;Lines[_index(_tempNum)].Num!=-1;_tempNum=_nextNum(_tempNum))
		{
			if(Lines[_index(_tempNum)].Value[0] == '{')
			{
				_BoxStack++;
				_1flag=true;
			}
			if(Lines[_index(_tempNum)].Value[0] == '}')
				_BoxStack--;
			if(_BoxStack==0 && _1flag )
			{
				if(Lines[_index(_nextNum(_tempNum))].Value[0] == 'e' && Lines[_index(_nextNum(_tempNum))].Value[1] == 'l' &&Lines[_index(_nextNum(_tempNum))].Value[2] == 's' &&Lines[_index(_nextNum(_tempNum))].Value[3] == 'e' )
				{
					_flag = true;
					char _afterIf[SIZE];

					for(int j =3;j<strlen((*thisLine).Value)+1;j++)
					{
						_afterIf[j-3] = (*thisLine).Value[j];
					}

					sprintf(Lines[_index(_nextNum(_tempNum))].Value,"if !%s",_afterIf);
					_fix();
				//	for(;_repair1LineIf(&Lines[_index(_nextNum(_tempNum))]);){}
					break;
				}
				else
					break;
			}
		}
	}

	return _flag;

}
void _asm1(line* thisLine)
{
	// M1 = M2 @ 0;
	if((*thisLine).Num != -1 && !(*thisLine).AsmChecked)
	{
		bool _flag = false;
		for(int i =0;i<strlen((*thisLine).Value);i++)
		{
			if((*thisLine).Value[i] == '@')
			{
				_flag = true;
				int _from1 = -1 , _from2 = -1 , _until1 = -1 , _until2 = -1;
				for(int j = i-1;j>0;j--)
				{
					if(_isDigitORAlpha((*thisLine).Value[j]) && _until1 ==-1)
					{
						_until1 = j;
					}
					if(_until1 !=-1 && !_isDigitORAlpha((*thisLine).Value[j]))
					{
						_from1 = j+1;
						break;
					}
				}
				for(int j = i+1;j<=strlen((*thisLine).Value);j++)
				{
					if(_isDigitORAlpha((*thisLine).Value[j]) && _from2 ==-1)
					{
						_from2 = j;
					}
					if(_from2 !=-1 && !_isDigitORAlpha((*thisLine).Value[j]))
					{
						_until2 = j-1;
						break;
					}
				}
				if(_from1 != -1 && _from2 != -1 && _until1 != -1 && _until2 != -1 )
				{
					char _before[SIZE];
					int k=0;
					for(k=0;k<_from1;k++)
					{
						_before[k] = (*thisLine).Value[k];
					}
					_before[k] = '\0';
					char _part1[SIZE];
					int l =0;
					for(int j =_from1;j<=_until1;j++)
					{
						_part1[l++] = (*thisLine).Value[j];
					}
					_part1[l] = '\0';
					char _part2[SIZE];
					int m =0;
					for(int j =_from2;j<=_until2;j++)
					{
						_part2[m++] = (*thisLine).Value[j];
					}
					_part2[m] = '\0';
					char _after[SIZE];
					int n =0;
					for(int j=_until2+1;j<strlen((*thisLine).Value)+1;j++)
					{
						_after[n++] = (*thisLine).Value[j];
					}
					char _line1[SIZE],_line2[SIZE],_line3[SIZE];
					sprintf(_line1,"mov %s,0",_part1);
					sprintf(_line2,"beq %s,0,?",_part2); // willadded 2
					sprintf(_line3,"mov %s,1",_part1);
					_asmLineAdd(_line1,0);
					_asmLineAdd(_line2,2);
					_asmLineAdd(_line3,0);
					(*thisLine).AsmChecked = true;
					break;
				}
				
			}

		}
	}
}
void _asm2(line* thisLine)
{
	// M1 = M2 > 0;
	if((*thisLine).Num != -1 && !(*thisLine).AsmChecked)
	{
		bool _flag = false;
		for(int i =0;i<strlen((*thisLine).Value);i++)
		{
			if((*thisLine).Value[i] == '>')
			{
				_flag = true;
				int _from1 = -1 , _from2 = -1 , _until1 = -1 , _until2 = -1;
				for(int j = i-1;j>0;j--)
				{
					if(_isDigitORAlpha((*thisLine).Value[j]) && _until1 ==-1)
					{
						_until1 = j;
					}
					if(_until1 !=-1 && !_isDigitORAlpha((*thisLine).Value[j]))
					{
						_from1 = j+1;
						break;
					}
				}
				for(int j = i+1;j<=strlen((*thisLine).Value);j++)
				{
					if(_isDigitORAlpha((*thisLine).Value[j]) && _from2 ==-1)
					{
						_from2 = j;
					}
					if(_from2 !=-1 && !_isDigitORAlpha((*thisLine).Value[j]))
					{
						_until2 = j-1;
						break;
					}
				}
				if(_from1 != -1 && _from2 != -1 && _until1 != -1 && _until2 != -1 )
				{
					char _before[SIZE];
					int k=0;
					for(k=0;k<_from1;k++)
					{
						_before[k] = (*thisLine).Value[k];
					}
					_before[k] = '\0';
					char _part1[SIZE];
					int l =0;
					for(int j =_from1;j<=_until1;j++)
					{
						_part1[l++] = (*thisLine).Value[j];
					}
					_part1[l] = '\0';
					char _part2[SIZE];
					int m =0;
					for(int j =_from2;j<=_until2;j++)
					{
						_part2[m++] = (*thisLine).Value[j];
					}
					_part2[m] = '\0';
					char _after[SIZE];
					int n =0;
					for(int j=_until2+1;j<strlen((*thisLine).Value)+1;j++)
					{
						_after[n++] = (*thisLine).Value[j];
					}
					char _line1[SIZE],_line2[SIZE],_line3[SIZE];
					sprintf(_line1,"move %s,0",_part1);
					sprintf(_line2,"bltz %s,?",_part2); // willadded 2
					sprintf(_line3,"mov %s,1",_part1);
					_asmLineAdd(_line1,0);
					_asmLineAdd(_line2,2);
					_asmLineAdd(_line3,0);
					(*thisLine).AsmChecked = true;
					break;
				}
				
			}

		}
	}
}
void _asm3(line* thisLine)
{

	//M1 = M2 + M3 ;
	if((*thisLine).Num != -1 && !(*thisLine).AsmChecked)
	{
		bool _flag = false;
		int i;
		int l;
		for(i=0;i<strlen((*thisLine).Value);i++)
		{
			if((*thisLine).Value[i] == '+' || (*thisLine).Value[i] == '-' || (*thisLine).Value[i] == '*' || (*thisLine).Value[i] == '/' )
			{
				_flag = true;
				break;
			}
		}
		for(l=0;l<strlen((*thisLine).Value);l++)
		{
			if((*thisLine).Value[l] == '='  )
			{
				break;
			}
		}
		if(_flag)
		{
			int _from1 = -1 , _from2 = -1 , _until1 = -1 , _until2 = -1,_from0=0,_until0=-1;
				for(int j = i-1;j>0;j--)
				{
					if(_isDigitORAlpha((*thisLine).Value[j]) && _until1 ==-1)
					{
						_until1 = j;
					}
					if(_until1 !=-1 && !_isDigitORAlpha((*thisLine).Value[j]))
					{
						_from1 = j+1;
						break;
					}
				}
				for(int j = i+1;j<=strlen((*thisLine).Value);j++)
				{
					if(_isDigitORAlpha((*thisLine).Value[j]) && _from2 ==-1)
					{
						_from2 = j;
					}
					if(_from2 !=-1 && !_isDigitORAlpha((*thisLine).Value[j]))
					{
						_until2 = j-1;
						break;
					}
				}
				for(int j = l-1;j>0;j--)
				{
					if(_isDigitORAlpha((*thisLine).Value[j]) && _until0 ==-1)
					{
						_until0 = j;
					}
					if(_until0 !=-1 && !_isDigitORAlpha((*thisLine).Value[j]))
					{
						_from0 = j+1;
						break;
					}
				} 
				char _part1[20],_part2[20],_part3[20];
				int q=0,w=0,e=0;
				for(int j=_from0;j<=_until0;j++)
				{
					_part1[q++] = (*thisLine).Value[j];
				}
				_part1[q] = '\0';
				for(int j=_from1;j<=_until1;j++)
				{
					_part2[w++] = (*thisLine).Value[j];
				}
				_part2[w] = '\0';
				for(int j=_from2;j<=_until2;j++)
				{
					_part3[e++] = (*thisLine).Value[j];
				}
				_part3[e] = '\0';
				char _line1[SIZE];
				if((*thisLine).Value[i] == '+')
					sprintf(_line1,"add %s,%s,%s",_part1,_part2,_part3);
				if((*thisLine).Value[i] == '-')
					sprintf(_line1,"sub %s,%s,%s",_part1,_part2,_part3);
				if((*thisLine).Value[i] == '*')
					sprintf(_line1,"mult %s,%s,%s",_part1,_part2,_part3);
				if((*thisLine).Value[i] == '/')
					sprintf(_line1,"div %s,%s,%s",_part1,_part2,_part3);

				_asmLineAdd(_line1,0);
				(*thisLine).AsmChecked = true;
		}
	}
}
void _asm4(line* thisLine)
{
	//M1 = n;
	if((*thisLine).Num != -1 && !(*thisLine).AsmChecked)
	{
		bool _flag = false;
		int i;
		for( i = 0 ; i<strlen((*thisLine).Value);i++)
		{
			if((*thisLine).Value[i] == '=')
				_flag = true;
		}
		if(_flag)
		{
			int _from1 = 0 , _from2 = 0 , _until1 = 0 , _until2 = 0;
				for(int j = i-1;j>0;j--)
				{
					if(_isDigitORAlpha((*thisLine).Value[j]) && _until1 ==0)
					{
						_until1 = j;
					}
					if(_until1 !=0 && !_isDigitORAlpha((*thisLine).Value[j]))
					{
						_from1 = j+1;
						break;
					}
				}
				for(int j = i+1;j<=strlen((*thisLine).Value);j++)
				{
					if(_isDigitORAlpha((*thisLine).Value[j]) && _from2 ==0)
					{
						_from2 = j;
					}
					if(_from2 !=0 && !_isDigitORAlpha((*thisLine).Value[j]))
					{
						_until2 = j-1;
						break;
					}
				}
				char _part1[20],_part2[20];
				int w=0,e=0;
				
				for(int j=_from1;j<=_until1;j++)
				{
					_part1[w++] = (*thisLine).Value[j];
				}
				_part1[w] = '\0';
				for(int j=_from2;j<=_until2;j++)
				{
					_part2[e++] = (*thisLine).Value[j];
				}
				_part2[e] = '\0';
				char _line[SIZE];
				sprintf(_line,"mov %s,%s",_part2,_part1);

				_asmLineAdd(_line,0);
				(*thisLine).AsmChecked = true;

		}
	}
}
void _asm5(line* thisLine)
{
	//if M1
	if((*thisLine).Num != -1 && !(*thisLine).AsmChecked)
	{
		if((*thisLine).Value[0] == 'i' && (*thisLine).Value[1]  == 'f')
		{
			char _part[20];
			for(int j = 3;j<=strlen((*thisLine).Value);j++)
			{
				_part[j-3] = (*thisLine).Value[j];
			}
			char _line[SIZE];
			sprintf(_line,"beq %s,0,?",_part);
			_asmLineAdd(_line,2);
			(*thisLine).AsmChecked = true;
		}
	}
}
void _asm6(line* thisLine)
{
	//{ goto #A2
	if((*thisLine).Num != -1 && !(*thisLine).AsmChecked)
	{
		if((*thisLine).Value[0] == '{')
		{
			char _line[SIZE];
			char _part[20];
			for(int i = 7;i<strlen((*thisLine).Value)+1;i++)
			{
				_part[i-7] = (*thisLine).Value[i];
			}
			sprintf(_line,"jmp %s",_part);
			_asmLineAdd(_line,0);
			(*thisLine).AsmChecked = true;
		}
	}

}
void _asm7(line* thisLine)
{
	//} #A2
	if((*thisLine).Num != -1 && !(*thisLine).AsmChecked)
	{
		if((*thisLine).Value[0] == '}')
		{
			char _line[SIZE];
			char _part[20];
			for(int i = 2;i<strlen((*thisLine).Value)+1;i++)
			{
				_part[i-2] = (*thisLine).Value[i];
			}
			sprintf(_line,"%s",_part);
			_asmLineAdd(_line,0);
			(*thisLine).AsmChecked = true;
		}
	}
}
void _asmLineAdd(char* value,int willAdded)
{
	strcpy(ASMLines[AsmCounter].Value,value);
	ASMLines[AsmCounter].WillAdded  = willAdded;
	AsmCounter++;
}