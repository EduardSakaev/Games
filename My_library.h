
#pragma once 
//#ifndef POWER2_NFVJSHFKVJHSDFKJVHKSJF
//#define POWER2_NFVJSHFKVJHSDFKJVHKSJF

int  _Enter_Int_Number_From_To (int iFrom, int iTo, char * cAr = " ");
double  _Enter_Double_Number_From_To (int iFrom, int iTo, char * cAr= "");
template <class T>
void FuncAssignment(T* src, const T * dest) //шаблонная функция присваивания.
{
	T Temp (*dest);
	char * pBuff = new char [sizeof(T)];
	memcpy(pBuff, src, sizeof(T));
	memcpy(src, &Temp, sizeof(T));
	memcpy(&Temp, pBuff, sizeof(T));
	delete [] pBuff;
}
char * _Enter_Char_Limited (char * cAr = "", const int LengthOfString = 100);
char _Enter_Char (char * cAr = "");

//#endif