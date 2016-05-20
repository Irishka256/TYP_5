// lr10.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "Defs.h"
#include "Scaner.h"
#include "LL1.h"

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "Russian");
	LL1 *ll;
	ll = new LL1();
	ll->LL_1();
	system("pause");
	return 0;
}

