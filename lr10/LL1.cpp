#include "stdafx.h"
#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <stdio.h>
#include "Defs.h"
#include "Scaner.h"
#include "LL1.h"
 
//проблема с символами и ++, --

int m[MAX_TEXT],z=0; //мазагин LL1-анализатора и указатель магазина

void LL1::epsilon() //обработка правил с пустой правой частью
{/*z--;*/}

void LL1::Osh(int m) {
	switch(m){
	case 4: 
		std::cout<<"ќжидалс€ main"<<std::endl;
		break;
	case 11: 
		std::cout<<"ќжидалась ("<<std::endl;
		break;
	case 12: 
		std::cout<<"ќжидалась )"<<std::endl;
		break;
	case 13: 
		std::cout<<"ќжидалась {"<<std::endl;
		break;
	case 14: 
		std::cout<<"ќжидалась }"<<std::endl;
		break;
	case 15: 
		std::cout<<"ќжидалась ;"<<std::endl;
		break;
	case 29: 
		std::cout<<"ќжидалось ="<<std::endl;
		break;
	case 30: 
		std::cout<<"ќжидалась ["<<std::endl;
		break;
	case 31: 
		std::cout<<"ќжидалась ]"<<std::endl;
		break;
	case 100: 
		std::cout<<"ќжидалс€ конец файла"<<std::endl;
		break;
	case 1001: 
		std::cout<<"ќжидалась программа"<<std::endl;
		break;
	case 1002: 
		std::cout<<"ќжидалс€ тип"<<std::endl;
		break;
	case 1003: 
		std::cout<<"ќжидалс€ идентификатор"<<std::endl;
		break;
	case 1005: 
		std::cout<<"ќжидалось выражение"<<std::endl;
		break;
	case 1006: 
		std::cout<<"ќжидалс€ тип"<<std::endl;
		break;
	case 1021: 
		std::cout<<"ќжидалось выражение"<<std::endl;
		break;
	case 1029: 
		std::cout<<"ќжидалось описание типа, или элемент массива, или присваивание"<<std::endl;
		break;
	case 1030: 
		std::cout<<"ќжидалась константа или символ {"<<std::endl;
		break;					
	default:
		break;
	}
}

int LL1::LL_1() {
	int fl=1, i, uk1, ttt;
	TypeLex l, lll;
	char sss[30];
	TScaner * sc ;
	sc = new TScaner("input.txt");// файл по умолчанию
	int type;
	m[z]=NS; 
	type = sc->Scaner(l);
	while (fl){
		if (m[z] < NS){ //в вершущке магазина терминал? (<=)
		// в вершушке мазазина терминал
			if(m[z] == type)
			{
		// верхушка совпадает с отсканированным терминалом
				if (type == TEnd || type == TError) fl=0;
				else {
					type = sc->Scaner(l); // сканируем новый символ
					z--; // стираем верхушку магазина
				}
			}
			else
			{ // обнаружена ошибка
				sc->PrintError("Ќеверный символ",l);
				Osh(m[z]);
				fl=0;
				return -1; 
			}
		}
		else{ //в верхушке магазина нетерминал
			switch (m[z]){
			case NS:
				m[z++] = TEnd;
				m[z++] = NProgram;
				break;
			case NProgram:
				if (type == TIdent){
					m[z++] = NProgram;
					m[z++] = TTochkaZap;
					m[z++] = NOpisPerem;
				}
				else if (type == TTypedef){
					m[z++] = NProgram;
					m[z++] = TTochkaZap;
					m[z++] = NMassiv;
				}
				else if (type == TVoid){
					m[z++] = NProgram;
					m[z++] = NMain;
				}
				else if (type == TInt){
					m[z++] = NProgram;
					m[z++] = TTochkaZap;
					m[z++] = NOpisPerem;
				}
				else if (type == TDouble){
					m[z++] = NProgram;
					m[z++] = TTochkaZap;
					m[z++] = NOpisPerem;
				}
				break;
			case NOpisPerem:
				if (type == TIdent || type == TInt || type == TDouble){
					m[z++] = NSpisPerem;
					m[z++] = NType;
				}
				break;
			case NSpisPerem:
				if (type == TIdent){
					m[z++] = NElemSpis;
					m[z++] = TIdent;
				}
				break;
			case NElemSpis:
				if (type == TPris){
					m[z++] = NSpisPerem2;
					m[z++] = NVyr;
					m[z++] = TPris;
				}
				else if (type == TTochkaZap){
					epsilon();
				}
				else if (type == TLKvScob){
					m[z++] = NSpisPerem2;
					m[z++] = NIndexInt;
					m[z++] = TRKvScob;
					m[z++] = TConstInt10;
					m[z++] = TLKvScob;
				}
				else if (type == TZap){
					m[z++] = NSpisPerem;
					m[z++] = TZap;
				}
				break;
			case NSpisPerem2:
				if (type == TTochkaZap){
					epsilon();
				}
				else if (type == TZap){
					m[z++] = NSpisPerem;
					m[z++] = TZap;
				}break;
			case NIndexInt:
				if (type == TTochkaZap){
					epsilon();
				}
				else if (type == TLKvScob){
					m[z++] = NIndexInt;
					m[z++] = TRKvScob;
					m[z++] = TConstInt10;
					m[z++] = TLKvScob;
				}
				break;
			case NIndexVyr:
				if (type == TPlus || type == TPlusPlus || type == TMinus ||
					type == TMinusMinus || type == TMul || type == TDiv || type == TMod || type == TMenshe ||
					type == TMensheRavno || type == TBolshe || type == TBolsheRavno || type == TPris || type == TRavno ||
					type == TNeRavno || type == TTochkaZap || type == TZap || type == TRSkob){
					epsilon();
				}
				else if (type == TLKvScob){
					m[z++] = NIndexVyr;
					m[z++] = TRKvScob;
					m[z++] = NVyr;
					m[z++] = TLKvScob;
				}
				else if (type == TRKvScob){
					epsilon();
				}break;
			case NOpers:
				if (type == TIdent || type == TIf || type == TInt || type == TDouble ||
					type == TTochkaZap || type == TLFigScob){
					m[z++] = NOpers;
					m[z++] = NOper1;
				}
				else if (type == TRFigScob){
					epsilon();
				}break;
			case NOper1:
				if (type == TIdent){
					m[z++] = NPris;
					m[z++] = TIdent;
				}
				else if (type == TIf){
					m[z++] = NIf;
				}
				else if (type == TInt){
					m[z++] = NSpisPerem;
					m[z++] = TInt;
				}
				else if (type == TDouble){
					m[z++] = NSpisPerem;
					m[z++] = TDouble;
				}
				else if (type == TTochkaZap){
					m[z++] = TTochkaZap;
				}
				else if (type == TLFigScob){
					m[z++] = TRFigScob;
					m[z++] = NOpers;
					m[z++] = TLFigScob;
				}break;
			case NPris:
				if (type == TIdent){
					m[z++] = NElemSpis;
					m[z++] = TIdent;
				}
				else if (type == TPris){
					m[z++] = NVyr;
					m[z++] = TPris;
				}
				else if (type == TLKvScob){
					m[z++] = NVyr;
					m[z++] = TPris;
					m[z++] = NIndexVyr;
				}break;
			case NVyr:
				if (type == TIdent){
					m[z++] = NVyr1;
				}
				else if (type == TConstInt10){
					m[z++] = NVyr1;
				}
				else if (type == TPlus){
					m[z++] = NVyr1;
					m[z++] = TPlus;
				}
				else if (type == TPlusPlus){
					m[z++] = NVyr1;
				}
				else if (type == TMinus){
					m[z++] = NVyr1;
					m[z++] = TMinus;
				}
				else if (type == TMinusMinus){
					m[z++] = NVyr1;
				}
				else if (type == TLSkob){
					m[z++] = NVyr1;
				}break;
			case NVyr1:
				if (type == TIdent){
					m[z++] = NVyr15;
					m[z++] = NVyr2;
				}
				else if (type == TConstInt10){
					m[z++] = NVyr15;
					m[z++] = NVyr2;
				}
				else if (type == TPlusPlus){
					m[z++] = NVyr15;
					m[z++] = NVyr2;
				}
				else if (type == TMinusMinus){
					m[z++] = NVyr15;
					m[z++] = NVyr2;
				}
				else if (type == TLSkob){
					m[z++] = NVyr15;
					m[z++] = NVyr2;
				}
				break;
			case NVyr15:
				if (type == TPlus){
					m[z++] = NVyr1;
					m[z++] = TPlus;
				}
				else if (type == TMinus){
					m[z++] = NVyr1;
					m[z++] = TMinus;
				}
				else if (type == TMul || type == TDiv || type == TMod || type == TMenshe ||
					type == TMensheRavno || type == TBolshe || type == TBolsheRavno || type == TRavno || type == TNeRavno ||
					type == TTochkaZap || type == TZap || type == TRSkob || type == TRKvScob){
					epsilon();
				}break;
			case NVyr2:
				if (type == TIdent){
					m[z++] = NVyr25;
					m[z++] = NVyr3;
				}
				else if (type == TConstInt10){
					m[z++] = NVyr25;
					m[z++] = NVyr3;
				}
				else if (type == TPlusPlus){
					m[z++] = NVyr25;
					m[z++] = NVyr3;
				}
				else if (type == TMinusMinus){
					m[z++] = NVyr25;
					m[z++] = NVyr3;
				}
				else if (type == TLSkob){
					m[z++] = NVyr25;
					m[z++] = NVyr3;
				}
				break;
			case NVyr25:
				if (type == TPlus || type == TMinus){
					epsilon();
				}
				else if (type == TMul){
					m[z++] = NVyr2;
					m[z++] = TMul;
				}
				else if (type == TDiv){
					m[z++] = NVyr2;
					m[z++] = TDiv;
				}
				else if (type == TMod){
					m[z++] = NVyr2;
					m[z++] = TMod;
				}
				else if (type == TMenshe ||type == TMensheRavno || type == TBolshe || type == TBolsheRavno 
					|| type == TRavno || type == TNeRavno || type == TTochkaZap || type == TZap || 
					type == TRSkob || type == TRKvScob){
					epsilon();
				}
				break;
			case NVyr3:
				if (type == TIdent){
					m[z++] = NVyr35;
					m[z++] = NVyr4;
				}
				else if (type == TConstInt10){
					m[z++] = NVyr35;
					m[z++] = NVyr4;
				}
				else if (type == TPlusPlus){
					m[z++] = NVyr35;
					m[z++] = NVyr4;
				}
				else if (type == TMinusMinus){
					m[z++] = NVyr35;
					m[z++] = NVyr4;
				}
				else if (type == TLSkob){
					m[z++] = NVyr35;
					m[z++] = NVyr4;
				}break;
			case NVyr35:
				if (type == TPlus || type == TMinus || type == TMinusMinus || type == TMul || type == TDiv ||
					type == TMod){
					epsilon();
				}
				else if (type == TMenshe){
					m[z++] = NVyr4;
					m[z++] = TMenshe;
				}
				else if (type == TMensheRavno){
					m[z++] = NVyr4;
					m[z++] = TMensheRavno;
				}
				else if (type == TBolshe){
					m[z++] = NVyr4;
					m[z++] = TBolshe;
				}
				else if (type == TBolsheRavno){
					m[z++] = NVyr4;
					m[z++] = TBolsheRavno;
				}
				else if (type == TRavno || type == TNeRavno || type == TTochkaZap || type == TZap || type == TRSkob || type == TRKvScob){
					epsilon();
				}break;
			case NVyr4:
				if (type == TIdent){
					m[z++] = NVyr45;
					m[z++] = NVyr5;
				}
				else if (type == TConstInt10){
					m[z++] = NVyr45;
					m[z++] = NVyr5;
				}
				else if (type == TPlusPlus){
					m[z++] = NVyr45;
					m[z++] = NVyr5;
				}
				else if (type == TMinusMinus){
					m[z++] = NVyr45;
					m[z++] = NVyr5;
				}
				else if (type == TLSkob){
					m[z++] = NVyr45;
					m[z++] = NVyr5;
				}break;
			case NVyr45:
				if (type == TPlus || type == TMinus || type == TMinusMinus || type == TMul || type == TDiv ||
					type == TMod || type == TMenshe || type == TMensheRavno || type == TBolshe || type == TBolsheRavno){
					epsilon();
				}
				else if (type == TRavno){
					m[z++] = NVyr5;
					m[z++] = TRavno;
				}
				else if (type == TNeRavno){
					m[z++] = NVyr5;
					m[z++] = TNeRavno;
				}
				else if (type == TTochkaZap || type == TZap || type == TRSkob || type == TRKvScob){
					epsilon();
				}
				break;
			case NVyr5:
				if (type == TIdent){
					m[z++] = NVyr55;
					m[z++] = NIndexVyr;
					m[z++] = TIdent;
				}
				else if (type == TConstInt10){
					m[z++] = TConstInt10;
				}
				else if (type == TPlusPlus){
					m[z++] = NIndexVyr;
					m[z++] = TIdent;
					m[z++] = TPlusPlus;
				}
				else if (type == TMinusMinus){
					m[z++] = NIndexVyr;
					m[z++] = TIdent;
					m[z++] = TMinusMinus;
				}
				else if (type == TLSkob){
					m[z++] = TRSkob;
					m[z++] = NVyr;
					m[z++] = TLSkob;
				}break;
			case NVyr55:
				if (type == TPlus){
					epsilon();
				}
				else if (type == TPlusPlus){
					m[z++] = TPlusPlus;
				}
				else if (type == TMinus){
					epsilon();
				}
				else if (type == TMinusMinus){
					m[z++] = TMinusMinus;
				}
				else if (type == TMul || type == TDiv || type == TMod || type == TMenshe || type == TMensheRavno ||
					type == TBolshe || type == TBolsheRavno){
					epsilon();
				}
				else if (type == TPris){
					m[z++] = NVyr;
					m[z++] = TPris;
				}
				else if (type == TRavno || type == TNeRavno || type == TTochkaZap || type == TZap || type == TRSkob ||
					type == TRKvScob){
					epsilon();
				}break;
			case NIf:
				if (type == TIf){
					m[z++] = NH6;
					m[z++] = NOper1;
					m[z++] = TRSkob;
					m[z++] = NVyr;
					m[z++] = TLSkob;
					m[z++] = TIf;
				}break;
			case NH6:
				if (type == TIf){
					m[z++] = NH7;
					m[z++] = TElse;
				}
				else if (type == TTochkaZap){
					epsilon();
				}break;
			case NH7:
				if (type == TIf){
					m[z++] = NIf;
				}
				else
				{
					m[z++] = NOper1;
				}break;
			case NMain:
				if (type == TVoid){
					m[z++] = TRFigScob;
					m[z++] = NOpers;
					m[z++] = TLFigScob;
					m[z++] = TRSkob;
					m[z++] = TLSkob;
					m[z++] = TMain;
					m[z++] = TVoid;
				}break;
			case NType:
				if (type == TIdent){
					m[z++] = TIdent;
				}
				else if (type == TInt){
					m[z++] = TInt;
				}
				else if (type == TDouble){
					m[z++] = TDouble;
				}break;
			case NMassiv:
				if (type == TTypedef){
					m[z++] = NIndexInt;
					m[z++] = TIdent;
					m[z++] = NType;
					m[z++] = TTypedef;
				}break;
			default:
				break;
			}
			z--;
		}
	}
	if (type==TEnd) printf("—интаксических ошибок не обнаружено\n");
	else sc->PrintError("Ћишний текст в конце программы","");
}