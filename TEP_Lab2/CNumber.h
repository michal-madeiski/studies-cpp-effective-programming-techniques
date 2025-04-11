#ifndef CNUMBER_H
#define CNUMBER_H

#include<iostream>
#include "constants.h"
#include <ostream>

class CNumber {
private:
	int length;
	int *numbersTab;
	bool isPositiveOrZero;

	int digitCounter(int val);
	void normalize();
	CNumber addZeros(int n);
	static CNumber half(const CNumber& pCNumberOther);

public:
	CNumber();
	CNumber(const CNumber& other);
	~CNumber();
	
	std::string sToStr() const;
	void printCNumber() const;

	CNumber absCNum(const CNumber &pCNumberOther) const;

	void operator=(const int value);
	void operator=(const CNumber& pCNumberOther);

	bool operator==(const CNumber& pCNumberOther) const;
	bool operator<(const CNumber& pCNumberOther) const;
	bool operator>(const CNumber& pCNumberOther) const;
	bool operator<=(const CNumber& pCNumberOther) const;
	bool operator>=(const CNumber& pCNumberOther) const;

	CNumber operator+(const int value) const;
	CNumber operator+(const CNumber &pCNumberOther) const;

	CNumber operator-(const int value) const;
	CNumber operator-(const CNumber& pCNumberOther) const;

	CNumber operator*(const int value) const;
	CNumber operator*(const CNumber& pCNumberOther) const;

	CNumber operator/(const int value) const;
	CNumber operator/(const CNumber& pCNumberOther) const;

	//mod2
	CNumber operator<<(const CNumber& pCNumberRight) const;
	CNumber operator<<(const unsigned int value) const;
	//mod2
};

//mod2
std::ostream& operator<<(std::ostream& os, const CNumber& CNum);
//mod2

#endif

