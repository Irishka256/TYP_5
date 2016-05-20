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
		std::cout<<"Ожидался main"<<std::endl;
		break;
	case 11: 
		std::cout<<"Ожидалась ("<<std::endl;
		break;
	case 12: 
		std::cout<<"Ожидалась )"<<std::endl;
		break;
	case 13: 
		std::cout<<"Ожидалась {"<<std::endl;
		break;
	case 14: 
		std::cout<<"Ожидалась }"<<std::endl;
		break;
	case 15: 
		std::cout<<"Ожидалась ;"<<std::endl;
		break;
	case 29: 
		std::cout<<"Ожидалось ="<<std::endl;
		break;
	case 30: 
		std::cout<<"Ожидалась ["<<std::endl;
		break;
	case 31: 
		std::cout<<"Ожидалась ]"<<std::endl;
		break;
	case 100: 
		std::cout<<"Ожидался конец файла"<<std::endl;
		break;
	case 1001: 
		std::cout<<"Ожидалась программа"<<std::endl;
		break;
	case 1002: 
		std::cout<<"Ожидался тип"<<std::endl;
		break;
	case 1003: 
		std::cout<<"Ожидался идентификатор"<<std::endl;
		break;
	case 1005: 
		std::cout<<"Ожидалось выражение"<<std::endl;
		break;
	case 1006: 
		std::cout<<"Ожидался тип"<<std::endl;
		break;
	case 1021: 
		std::cout<<"Ожидалось выражение"<<std::endl;
		break;
	case 1029: 
		std::cout<<"Ожидалось описание типа, или элемент массива, или присваивание"<<std::endl;
		break;
	case 1030: 
		std::cout<<"Ожидалась константа или символ {"<<std::endl;
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
				sc->PrintError("Неверный символ",l);
				Osh(m[z]);
				fl=0;
				return -1; 
			}
		}
		else{ //в верхушке магазина нетерминал
			switch(m[z]){ //по нетерминалу в верхушке магазина
				case NS:
				m[z++] = TEnd;
				m[z++] = NProgram;
				break;
				case NProgram:
					/*if (type == TPlus || type == TMinus) *///m[z++] = NOper;
				if (type == TIdent){
					m[z++] = NProgram;
					//m[z++] = TTochkaZap;
					m[z++] = NOpisPerem;
				}if (type == TTypedef){
					m[z++] = NProgram;
					m[z++] = TTochkaZap;
					m[z++] = NMassiv;
				}else if (type == TVoid){
					m[z++] = NProgram;
					m[z++] = NMain;
				} else if (type == TInt){
					m[z++] = NProgram;
					//m[z++] = TTochkaZap;
					m[z++] = NOpisPerem;
				}else if (type == TDouble){
					m[z++] = NProgram;
					//m[z++] = TTochkaZap;
					m[z++] = NOpisPerem;
				}
				/*else {
						sc->PrintError("Неверный символ",l);
						std::cout<<"Ожидалось "<<m[z]<<std::endl;
						return -1; 
				}*/
				break;
				case NOpisPerem:
				if (type == TIdent || type == TInt || type == TDouble){
					m[z++] = TTochkaZap;
					m[z++] = NSpisPerem;
					m[z++] = NType;
				}
				else {
						sc->PrintError("Неверный символ",l);
						Osh(m[z]);
						return -1; 
					}
				break;
				case NSpisPerem:
				if (type == TIdent){ 
					m[z++] = NElemSpis;
					m[z++] = TIdent;
				}
				else {
						sc->PrintError("Неверный символ",l);
						Osh(m[z]);
						return -1; 
					}
				break;
				case NElemSpis: 
				if (type == TPris){
					m[z++] = NH1;
					m[z++] = TPris;
				}else if (type == TZap){
					m[z++] = NH2;
				}
				break;
				case NH1:
				if (type == TLFigScob){
					m[z++] = NT1;
					//m[z++] = TTochkaZap;/////////////////////////////////////////
					m[z++] = TRFigScob;
					//m[z++] = TZap;
					m[z++] = NT;
					m[z++] = TLFigScob;
				}else if (type == TIdent || type == TConstInt10 || type == TLSkob){ //добавить фигур скобку, обыч скобку
					m[z++] = NH2;
					m[z++] = NVyr; //&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
				}
				else {
					sc->PrintError("Неверный символ",l);
					Osh(m[z]);
					return -1; 
				}
				break;
				case NT:
					if (type == TLFigScob)
						m[z++] = NH1;
					else if (/*type == TIdent || */type == TConstInt10/* || type == TLSkob*/){
						//m[z++] = NT;
						m[z++] = NT2;
						m[z++] = TConstInt10;
					}
					/*else if (type == TRFigScob){
						//m[z++] = TRFigScob;
						//m[z++] = NT;
						break;

					}*/
					else {
						sc->PrintError("Неверный символ",l);
						Osh(m[z]);
						return -1; 
					}
				break;
				case NT1: //между скобок
					if (type == TZap){
						m[z++] = NH1;
						m[z++] = TZap;
					}
				break;
				case NT2: //между константами
					if (type == TZap){
						m[z++] = NT;
						m[z++] = TZap;
					}
				break;
				case NH2:
					if (type == TZap){
						m[z++] = NSpisPerem;
						m[z++] = TZap;
					}
				break;
				case NMassiv: 
					if (type == TTypedef){
						m[z++] = NIndexInt;
						m[z++] = TIdent;
						m[z++] = NType;
						m[z++] = TTypedef;
				}
				break;
				case NMain: //мб один блок оставить
					//m[z++] = NMain;
					m[z++] = NBlock;
					m[z++] = TRSkob;
					m[z++] = TLSkob;
					m[z++] = TMain;
					m[z++] = TVoid;
					//m[z++] = TLFigScob; 
				break; 
				case NBlock:
					/*if (type == TLFigScob)
					{*/
						m[z++] = TRFigScob;
						m[z++] = NOper;
						m[z++] = TLFigScob; //мб не надо???????????????????????
					//}
					// вывод ошибки????
				break;
				case NOper:

					if (type == TTypedef)
					{
						m[z++] = NOper;
						m[z++] = NMassiv;
					}
					else if(type == TInt || type == TDouble)
					{
						m[z++] = NOper;
						m[z++] = NOpisPerem;
					}
					else if(type == TIf || type == TTochkaZap || type == TLFigScob){ 
						m[z++] = NOper;
						m[z++] = NOper1;
					}
					else if (type == TIdent)
					{
						m[z++] = NOper;
						m[z++] = NH8;
						m[z++] = TIdent;
					}
				break;
				case NH8:
				if (type == TIdent){
					//m[z++] = NOpisPerem;
					m[z++] = NSpisPerem;
				}
				else if (type == TLKvScob || type == TPris){
					m[z++] = NH3;
					//m[z++] = NPris;
					//m[z++] = TIdent;
					//m[z++] = TPris;
				}
				else {
					sc->PrintError("Неверный символ",l);
					Osh(m[z]);
					return -1; 
				}
				// вывод ошибки????????????????7
				break;
				case NOper1:
				if (type == TIdent){
					m[z++] = NPris;
				}else if (type == TIf){
					m[z++] = NIf;
				}else if (type == TTochkaZap){
					m[z++] = TTochkaZap;
				}else if (type == TLFigScob){
					m[z++] = NBlock;
				}break;
				case NPris:
					m[z++] = NH3;
					m[z++] = TIdent;
				break;
				case NH3:
					if (type == TPris){
						m[z++] = TTochkaZap;
						m[z++] = NVyr;
						m[z++] = TPris;
					}
					else
					{
						m[z++] = TTochkaZap;
						m[z++] = NVyr;
						m[z++] = TPris;
						m[z++] = NH5;
					}
				break;
				case NH5:
					if (type == TLKvScob){
						m[z++] = NH5;
						m[z++] = TRKvScob;
						m[z++] = NVyr;
						m[z++] = TLKvScob;
					}
				break;
				case NElemMass:
					m[z++] = NH4;
					m[z++] = TRKvScob;
					m[z++] = NVyr;
					m[z++] = TLKvScob;
					m[z++] = TIdent;
				break;
				case NH4:
					if (type == TLKvScob){
						m[z++] = NH4;
						m[z++] = TRKvScob;
						m[z++] = NVyr;
						m[z++] = TLKvScob;
					}
				break;
				case NVyr:
					if (type == TPlus)
					{
						m[z++] = NA;
						m[z++] = NVyr1;
						m[z++] = TPlus;
					}
					else if (type == TMinus)
					{
						m[z++] = NA;
						m[z++] = NVyr1;
						m[z++] = TMinus;
					}
					else 
					{
						m[z++] = NA;
						m[z++] = NVyr1;
					}
				break;
				case NA:
					if (type == TRavno)
					{
						m[z++] = NA;
						m[z++] = NVyr1;
						m[z++] = TRavno;
					}
					else if (type == TNeRavno)
					{
						m[z++] = NA;
						m[z++] = NVyr1;
						m[z++] = TNeRavno;
					}
					else if (type == TMenshe)
					{
						m[z++] = NA;
						m[z++] = NVyr1;
						m[z++] = TMenshe;
					}
					else if (type == TMensheRavno)
					{
						m[z++] = NA;
						m[z++] = NVyr1;
						m[z++] = TMensheRavno;
					}
					else if (type == TBolshe)
					{
						m[z++] = NA;
						m[z++] = NVyr1;
						m[z++] = TBolshe;
					}
					else if (type == TBolsheRavno)
					{
						m[z++] = NA;
						m[z++] = NVyr1;
						m[z++] = TBolsheRavno;
					}
					else if (type == TPlusPlus)
					{
						m[z++] = NA;
						m[z++] = NVyr1;
						m[z++] = TPlusPlus;
					}
					else if (type == TMinusMinus)
					{
						m[z++] = NA;
						m[z++] = NVyr1;
						m[z++] = TMinusMinus;
					}
				break;
				case NVyr1:
					m[z++] = NA1;
					m[z++] = NVyr2;
				break;
				case NA1:
					if (type == TPlus)
					{
						m[z++] = NA1;
						m[z++] = NVyr2;
						m[z++] = TPlus;
					}
					else if (type == TMinus)
					{
						m[z++] = NA1;
						m[z++] = NVyr2;
						m[z++] = TMinus;
					}
				break;
				case NVyr2:
					m[z++] = NA2;
					m[z++] = NVyr3;
				break;
				case NA2:
					if (type == TMul)
					{
						m[z++] = NA2;
						m[z++] = NVyr3;
						m[z++] = TMul;
					}
					else if (type == TDiv)
					{
						m[z++] = NA2;
						m[z++] = NVyr3;
						m[z++] = TDiv;
					}
					else if (type == TMod)
					{
						m[z++] = NA2;
						m[z++] = NVyr3;
						m[z++] = TMod;
					}
				break;
				case NVyr3:
					if (type == TIdent)
					{
						m[z++] = NH4;
						m[z++] = TIdent;
					}
					else if (type == TConstInt10)
					{
						m[z++] = TConstInt10;
					}
					else if (type == TLSkob)
					{
						m[z++] = TRSkob;
						m[z++] = NVyr;
						m[z++] = TLSkob;
					}
					else {
						sc->PrintError("Неверный символ",l);
						Osh(m[z]);
						return -1; 
					}
				break;
				case NIf:
						m[z++] = NH6;
						m[z++] = NOper1;
						m[z++] = TRSkob;
						m[z++] = NVyr;
						m[z++] = TLSkob; 
						m[z++] = TIf;
				break;
				case NH6:
					 if (type == TElse){
						m[z++] = NH7;
						m[z++] = TElse; 
					}
				break;
				case NH7:
					if (type == TIf){
						m[z++] = NIf;
					}else 
					{
						m[z++] = NOper1;
					}
					
				break;
				case NType: 
					if (type == TIdent){
					m[z++] = TIdent;
					}else if (type == TInt){
					m[z++] = TInt;
					}else if (type == TDouble){
					m[z++] = TDouble;
				}break;
				break;
				case NIndexInt: 
					if (type == TTochkaZap){
						epsilon();
					}else if (type == TLKvScob){
						m[z++] = NIndexInt;
						m[z++] = TRKvScob;
						m[z++] = TConstInt10;
						m[z++] = TLKvScob;
				}
				break;
				default:
					break;
			}
			z--;
		}
	}
	if (type==TEnd) printf("Синтаксических ошибок не обнаружено\n");
	else sc->PrintError("Лишний текст в конце программы","");
}