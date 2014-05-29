#pragma once
#include <vector>

template <typename T>
class VectorChild : public std::vector <T> // наследник вектора 
{
	int m_iSize;
public:
	VectorChild()
	{
		m_iSize = size();
	}
	~VectorChild()
	{
		int iSize = size();
		for(int i = 0; i < iSize; ++i)
		{
			delete(*this)[iSize-i-1];
			pop_back();
		}
	}//public methods
};