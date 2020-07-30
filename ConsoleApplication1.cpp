// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

using namespace std;

void  funct1(int vnum, int & rnum1, int & rnum2)
{
	vnum += 7;
	rnum1 += 4;
	rnum2 = vnum + rnum1;
}




int main()
{
	int num1 = 5, num2 = 16, num3;

	funct1(num1+9, num2, num3);
	cout << endl << "num1 = " << num1 << "\tnum2 = " << num2 << "\tnum3 = " << num3;
	return 0;
}

