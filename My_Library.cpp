//ввод числа в заданном диапазоне
#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "My_library.h"
using namespace std;

int  _Enter_Int_Number_From_To (int iFrom, int iTo, char * cAr)
{
	const int n = 250;
	if (cAr == " ")
		cout << "Enter number from " << iFrom << " to " << iTo << ":"; 
	cout << cAr << endl;
	char cTemp[1] = {0};
	int iatoi = 0, p = 0; //Целочисленный массив, ib - cчетчик количества цифр в числе
	int iLimit = 10, iPointIndex = 0;
	int iNumber = 0, drazryad = 1, iCurInd = 1;
	bool bMinusIndex = false, bIndexForMinus = false, bEscape = false;
	char cgetch = 0;

	char * Str = new char [n];
	for (int i = 0; i< n; ++i)
		Str[i] = 0;

	//Цикл ввода числа в конкретном диапазоне
	while (iCurInd == 1)
	{
		for(;;)
		{
			cgetch = _getch();
			if (cgetch == 8 || (cgetch == 27 && bEscape == false) || ((cgetch == '-' && bMinusIndex == false) || (cgetch >=48 && cgetch <= 57)) && p < iLimit || cgetch == 13)
			{
				if (cgetch == 8)
				{
					p = p - 1;
					bMinusIndex = (p>0)?true:false;
					Str[p] = ' ';
					putchar(cgetch);
					putchar (Str[p]);
					putchar(cgetch);
					continue;
				}
				int p1 = p;
				if (cgetch == 27)
				{
					bEscape = true;
					for (int i = 0; i < p1; ++i)
					{
						p = p - 1;
						bMinusIndex = (p>0)?true:false;
						Str[p] = ' ';
						cgetch = 8;
						putchar(cgetch);
						putchar (Str[p]);
						putchar(cgetch);
					}
					continue;
				}
				bEscape = false;
				Str[p] = cgetch;
				bIndexForMinus = (Str[0] == '-') ? true:false;
				bMinusIndex = (p>0)?true:false; //отслеживает на ввод - только первым символом
				putchar (cgetch);
				++p;
				//перевод char в числ
				switch(cgetch)
				{
				case 13:
					{
						for (int i = 0; i < p; ++i)
						{
							if (Str[i] != '-')
							for (int j = i; j < p-2; ++j)
								drazryad = drazryad*10;
							cTemp[0] = Str[i];
							iatoi = atoi(cTemp);
							iNumber = iNumber + iatoi*drazryad;
							drazryad = 1;
						}	
						iNumber = (bIndexForMinus == true)?-iNumber:iNumber;
						break;
					}
					
				}
			}
			if (cgetch == 13)
			{
				iCurInd = 2;
				break;
			}
		}
		if (iNumber < iFrom || iNumber > iTo)
			{
				cout <<endl<< "Enter number correctly, please! (From "<<iFrom<<" to "<< iTo <<"):"<<endl;
				p = 0;
				iNumber = 0;
				iCurInd = 1;
			}
	}
	delete [] Str;
	return iNumber;
}

double  _Enter_Double_Number_From_To (int iFrom, int iTo, char * cAr)
{
	const int n = 250;
		if (cAr == " ")
		cout << "Enter number from " << iFrom << " to " << iTo << ":"; 
	cout << cAr << endl;
	char cTemp[1] = {0};
	int iatoi = 0, p = 0; //Целочисленный массив, ib - cчетчик количества цифр в числе
	int iLimit = 12, iPointIndex = 0, iCurInd = 1;
	double dNumber = 0, drazryad = 1;
	bool bMinusIndex = false, bPointIndex = false, bIndexForMinus = false, bEscape = false;
	char cgetch = 0;

	char * Str = new char [n];
	for (int i = 0; i< n; ++i)
		Str[i] = 0;

	//Цикл ввода числа в конкретном диапазоне

	while (iCurInd == 1)
	{
		for(;;)
		{
			cgetch = _getch();
			if (cgetch == 8 || (cgetch == 27 && bEscape == false) || ((cgetch == '-' && bMinusIndex == false) || (cgetch == '.' && bPointIndex == false)|| (cgetch >=48 && cgetch <= 57)) && p < iLimit || (cgetch == 13 && p>0))
			{
				if (cgetch == 8)
				{
					p = p - 1;
					switch (Str[p])
					{
					case '.':
						bPointIndex = false;
						break;
					}
					bMinusIndex = (p>0)?true:false;
					Str[p] = ' ';
					putchar(cgetch);
					putchar (Str[p]);
					putchar(cgetch);
					continue;
				}
				int p1 = p;
				if (cgetch == 27)
				{
					bEscape = true;
					for (int i = 0; i < p1; ++i)
					{
						p = p - 1;
						switch (Str[p])
						{
						case '.':
							bPointIndex = false;
							break;
						}
						bMinusIndex = (p>0)?true:false;
						Str[p] = ' ';
						cgetch = 8;
						putchar(cgetch);
						putchar (Str[p]);
						putchar(cgetch);
					}
					continue;
				}
				bEscape = false;
				Str[p] = cgetch;
				bIndexForMinus = (Str[0] == '-') ? true:false;
				bMinusIndex = (p>0)?true:false; //отслеживает на ввод - только первым символом

				switch(cgetch)
				{
					case '.':
						bPointIndex = true;
						break;
				}
			
				putchar (cgetch);

				++p;
				//перевод char в числ
				switch(cgetch)
				{
				case 13:
					{
						int iPoint = 0;
						for (int i = 0; i < p; ++i)
							if (Str [i] == '.')
							{
								++iPoint;
								break;
							}
							else 
								++iPoint;
				
						for (int i = 0; i < p; ++i)
						{
							if (Str[i] != '.' && i < iPoint-1 && Str[i] != '-')
							{
								for (int j = i+1; j < iPoint-1; ++j)
									drazryad = drazryad*10;
								cTemp[0] = Str[i];
								iatoi = atoi(cTemp);
								dNumber = dNumber + iatoi*drazryad;
								drazryad = 1;
							}
							else if (Str[i] != '.' && i > iPoint-1 && Str[i]!='-')
							{
								drazryad = drazryad/10;
								cTemp[0] = Str[i];
								iatoi = atoi(cTemp);
								dNumber = dNumber + iatoi*drazryad;

							}
						}	
						dNumber = (bIndexForMinus == true)?-dNumber:dNumber;
						break;
					}
				}
				if (cgetch == 13)
				{
					iCurInd = 2;
					break;
				}
			}
		}
		if (dNumber < iFrom || dNumber > iTo)
			{
				cout <<endl<< "Enter number correctly, please! (From "<<iFrom<<" to "<< iTo <<"):"<<endl;
				p = 0;
				dNumber = 0;
				bPointIndex = false;
				bMinusIndex = false;
				bIndexForMinus = false;
				iCurInd = 1;
			}
	}
		delete [] Str;
		return dNumber;
}
char * _Enter_Char_Limited (char * cAr, const int LengthOfString)
{
	cout << cAr << endl;
	int p = 0; //Целочисленный массив, ib - cчетчик количества цифр в числе
	bool bEscape = false;
	char cgetch = 0;
	char * Str = new char [LengthOfString];
	for (int i = 0; i < LengthOfString; ++i)
		Str[i] = 0;

	//Цикл ввода числа в конкретном диапазоне

	for(;;)
	{
		cgetch = _getch();
		if ((p >= 0 && p <= LengthOfString ) || cgetch == 13)
		{
			if (cgetch == 8)
			{
				p = p - 1;
				Str[p] = ' ';
				putchar(cgetch);
				putchar (Str[p]);
				putchar(cgetch);
				continue;
			}
			int p1 = p;
			if (cgetch == 27)
			{
				bEscape = true;
				for (int i = 0; i < p1; ++i)
				{
					p = p - 1;
					Str[p] = ' ';
					cgetch = 8;
					putchar(cgetch);
					putchar (Str[p]);
					putchar(cgetch);
				}
				continue;
			}
			if (cgetch == 13 && p > 0)
				break;
			bEscape = false;
			Str[p] = cgetch;
			putchar (cgetch);
			++p;
			//перевод char в числ
		}
	}
	return Str;
}
char _Enter_Char (char * cAr)
{
	cout << cAr << endl;
	int p = 0; //Целочисленный массив, ib - cчетчик количества цифр в числе
	bool bEscape = false;
	char cgetch = 0;
	char Str = 0;

	//Цикл ввода числа в конкретном диапазоне

	for(;;)
	{
		cgetch = _getch();
		if ((p >= 0 && p < 1) || cgetch == 13||cgetch==8||cgetch==27)
		{
			if (cgetch == 8)
			{
				p = p - 1;
				Str = ' ';
				putchar(cgetch);
				putchar (Str);
				putchar(cgetch);
				continue;
			}
			int p1 = p;
			if (cgetch == 27)
			{
				bEscape = true;
				for (int i = 0; i < p1; ++i)
				{
					p = p - 1;
					Str = ' ';
					cgetch = 8;
					putchar(cgetch);
					putchar (Str);
					putchar(cgetch);
				}
				continue;
			}
			bEscape = false;

			if (cgetch!=13)
				Str = cgetch;
			putchar (cgetch);
			++p;
			//перевод char в числ
		}
		if (cgetch == 13 && p > 0)
			break;
	}
	return Str;
}
	