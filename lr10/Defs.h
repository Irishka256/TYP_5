#ifndef __DEFS
#define __DEFS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TEXT 10000 //макс длина текста ИМ
#define MAX_LEX 100 //макс длина лексемы
#define MAX_KEYW 7 // число ключевых слов
#define MAX_CONST 9 // 
#define MAX_N 8

#define LetterSmall ( (t[uk]>='a') && (t[uk]<='z') )
#define LetterBig ( (t[uk]>='A') && (t[uk]<='Z') )
#define Number ( (t[uk]>='0') && (t[uk]<='9') )

typedef char TypeMod[MAX_TEXT]; // текст ИМ
typedef char TypeLex[MAX_LEX]; // лексема

// Нетерминалы
#define NS			1000
#define NProgram	1001
#define NOpisPerem	1002 
#define NSpisPerem	1003 
#define NElemSpis	1004 
#define NSpisPerem2 1005 
#define NIndexInt   1023
#define NMassiv     1024
#define NType       1027
#define NMain     	1006 
#define NMassiv	    1007 
#define NOpers		1008
#define NOper1		1009 
#define NPris		1010
#define NIndexVyr   1028
#define NVyr   		1011 
#define NVyr1		1012 
#define NVyr15		1013 
#define NVyr2  		1025 
#define NVyr25		1014 
#define NVyr3  		1026 
#define NVyr35		1015
#define NVyr4      	1016
#define NVyr45		1017
#define NVyr5     	1018
#define NVyr55		1019
#define NIf 		1020
#define NH6			1021 
#define NH7 		1022 


//идентификаторы, константы и массивы
#define TIdent 1
#define TConstInt10 2
#define TConstSymvol 3

//ключевые слова
#define TInt 5
#define TDouble 6
#define TIf 7
#define TElse 8
#define TTypedef 9
#define TMain 4
#define TVoid 32

//специальные знаки
#define TZap 10
#define TLSkob 11
#define TRSkob 12
#define TLFigScob 13
#define TRFigScob 14
#define TTochkaZap 15
#define TLKvScob 30
#define TRKvScob 31

//знаки операций
#define TPlusPlus 16
#define TMinusMinus 17
#define TBolshe 18
#define TBolsheRavno 19
#define TMenshe 20
#define TMensheRavno 21
#define TRavno 22
#define TNeRavno 23
#define TPlus 24
#define TMinus 25
#define TMul 26
#define TDiv 27
#define TMod 28
#define TPris 29

//конец исходного модуля
#define TEnd 100

//ошибочный символ
#define TError 101

#endif