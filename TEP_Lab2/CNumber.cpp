#include<iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include "constants.h"
#include "CNumber.h"

CNumber::CNumber() {
	length = DEFAULT_NUMBERSTABLE_LENGTH;
	numbersTab = new int[length];
	isPositiveOrZero = DEFAULT_ISPOSITIVEORZERO;
}

CNumber::CNumber(const CNumber& other) {
	length = other.length;
	isPositiveOrZero = other.isPositiveOrZero;

	numbersTab = new int[length];

	for (int i = 0; i < length; ++i) {
		numbersTab[i] = other.numbersTab[i];
	}
}

CNumber::~CNumber() {
	delete[] numbersTab;
}

int CNumber::digitCounter(int val) {
	int count = 0;
	if (val == 0) {
		return 1;
	}

	while (val != 0) {
		val /= DEFAULT_SYSTEM;
		++count;
	}

	return count;
}

void CNumber::normalize() {
	int countZero = 0;
	bool flag = true;
	for (int i = length - 1; i > 0; --i) {
		if (numbersTab[i] == 0 && flag == true) countZero++;
		else if (numbersTab[i] != 0) flag = false;
	}

	if (countZero > 0) {
		int* resultWithoutZero = new int[length - countZero]();
		for (int i = length - countZero - 1; i >= 0; --i) {
			resultWithoutZero[i] = numbersTab[i];

		}

		delete[] numbersTab;
		length = length - countZero;
		numbersTab = new int[length];
		for (int i = 0; i < length; ++i) {
			numbersTab[i] = resultWithoutZero[i];
		}
		
		delete[] resultWithoutZero;
		resultWithoutZero = NULL;
	}
}

CNumber CNumber::addZeros(int n) {
	CNumber retCNumber;
	retCNumber = *this;

	if (n <= 0) return retCNumber;

	int* temp = new int[length + n]();
	for (int i = 0; i < length; ++i) {
		temp[i + n] = numbersTab[i];
	}

	delete[] retCNumber.numbersTab;
	retCNumber.numbersTab = temp;
	retCNumber.length += n;

	temp = NULL;
	return retCNumber;
}

CNumber CNumber::half(const CNumber& pCNumberOther) {
	CNumber retCNum;
	retCNum.numbersTab = new int[pCNumberOther.length];
	retCNum.length = pCNumberOther.length;

	int carry = 0;
	for (int i = pCNumberOther.length - 1; i >= 0; --i) {
		int sum = carry + pCNumberOther.numbersTab[i];
		retCNum.numbersTab[i] = sum / 2;
		carry = (sum % 2) * DEFAULT_SYSTEM;
	}

	retCNum.normalize();
	return retCNum;
}

std::string CNumber::sToStr() const{
	std::string stringValueOfCNumber = (isPositiveOrZero) ? "" : "-";
	for (int i = length - 1; i >= 0; --i) {
		stringValueOfCNumber += '0' + numbersTab[i]; //cyfra jako string: '0' o wartosci ASCII 48 + cyfra = wartoœæ ASCII tej cyfry
	}
	return stringValueOfCNumber;
}

void CNumber::printCNumber() const{
	std::cout << sToStr();
}

CNumber CNumber::absCNum(const CNumber &pCNumberOther) const {
	CNumber retCNum;
	retCNum = pCNumberOther;
	retCNum.isPositiveOrZero = true;
	return retCNum;
}

void CNumber::operator=(const int newValue) {
	delete[] numbersTab;

	length = digitCounter(newValue);
	isPositiveOrZero = (newValue >= 0) ? true : false;

	numbersTab = new int[length];

	int temp = std::abs(newValue);

	for (int i = 0; i < length; ++i) {
		numbersTab[i] = temp % DEFAULT_SYSTEM;
		temp /= DEFAULT_SYSTEM;
	}
}

/*
//zad2: operator=
void CNumber::operator=(const CNumber &pCNumberOther) {
	length = pCNumberOther.length;
	numbersTab = pCNumberOther.numbersTab;
}
*/

void CNumber::operator=(const CNumber& pCNumberOther) {
	if (this == &pCNumberOther) {
		return;
	}

	delete[] numbersTab;

	length = pCNumberOther.length;
	isPositiveOrZero = pCNumberOther.isPositiveOrZero;

	numbersTab = new int[length];

	for (int i = 0; i < length; ++i) {
		numbersTab[i] = pCNumberOther.numbersTab[i];
	}
}

bool CNumber::operator==(const CNumber &pCNumberOther) const {
	if (isPositiveOrZero != pCNumberOther.isPositiveOrZero) return false;

	if (length == pCNumberOther.length) {
		for (int i = 0; i < length; ++i) {
			if (numbersTab[i] != pCNumberOther.numbersTab[i]) {
				return false;
			}
		}
		return true;
	}
	else {
		return false;
	}
}

bool CNumber::operator<(const CNumber &pCNumberOther) const {
	bool ret = true;

	if (!isPositiveOrZero && !pCNumberOther.isPositiveOrZero) ret = false; //zmiana na false bo jesli 2 ujemne to na odwrot

	else if (!isPositiveOrZero && pCNumberOther.isPositiveOrZero) return ret;
	else if (isPositiveOrZero && !pCNumberOther.isPositiveOrZero) return !ret;
	
	else if (length < pCNumberOther.length) {
		return ret;
	}
	else if (length > pCNumberOther.length) {
		return !ret;
	}
	else if (length == pCNumberOther.length) {
		for (int i = length - 1; i >= 0; --i) {
			if (numbersTab[i] < pCNumberOther.numbersTab[i]) {
				return ret;
			}
			else if (numbersTab[i] > pCNumberOther.numbersTab[i]) {
				return !ret;
			}
		}
		return !ret;
	}

	return !ret; //tu i tak nie wejdzie bo sa wszystkie przypadki ale byl warning ze niewszystkie sciezki kodu zwracaja wartosc
}

bool CNumber::operator>(const CNumber& pCNumberOther) const {
	if (*this == pCNumberOther) return false;
	return !(*this < pCNumberOther);
}

bool CNumber::operator<=(const CNumber& pCNumberOther) const {
	bool ret = *this == pCNumberOther || *this < pCNumberOther;
	return ret;
}

bool CNumber::operator>=(const CNumber& pCNumberOther) const {
	bool ret = *this == pCNumberOther || *this > pCNumberOther;
	return ret;
}

CNumber CNumber::operator+(const CNumber &pCNumberOther) const {
	//przekierowanie do odejmowania:
	
	//a<0; b>=0 -> -a + b = b - a
	if (!isPositiveOrZero && pCNumberOther.isPositiveOrZero) {
		CNumber temp;
		temp = *this;
		temp.isPositiveOrZero = true;
		return pCNumberOther - temp;
	}
	//a>=0; b<0 -> a + (-b) = a - b
	if (isPositiveOrZero && !pCNumberOther.isPositiveOrZero) {
		CNumber temp;
		temp = pCNumberOther;
		temp.isPositiveOrZero = true;
		return *this - temp;
	}

	//zwykle dodawanie:

	bool symbol;
	//a>=0; b>=0 -> a + b
	if (isPositiveOrZero && pCNumberOther.isPositiveOrZero) {
		symbol = true;
	}
	//a<0; b<0 -> -a + (-b) = - (a + b)
	if (!isPositiveOrZero && !pCNumberOther.isPositiveOrZero) {
		symbol = false;
	}
	
	int biggerLength = std::max(length, pCNumberOther.length);

	CNumber retCNum;
	delete[] retCNum.numbersTab;
	retCNum.numbersTab = new int[biggerLength + 1]();
	retCNum.length = biggerLength + 1;
	
	int carry = 0;
	for (int i = 0; i < biggerLength; ++i) {
		int num1;
		int num2;

		num1 = (i < length) ? numbersTab[i] : 0;
		num2 = (i < pCNumberOther.length) ? pCNumberOther.numbersTab[i] : 0;

		int sum = num1 + num2 + carry;

		retCNum.numbersTab[i] = sum % DEFAULT_SYSTEM;

		carry = sum / DEFAULT_SYSTEM;
	}

	retCNum.numbersTab[biggerLength] = carry;

	retCNum.isPositiveOrZero = symbol;
	retCNum.normalize(); //usuwanie zer wiodacych
	return retCNum;
}

CNumber CNumber::operator+(const int value) const {
	CNumber temp;
	temp = value;
	return *this + temp;
}

CNumber CNumber::operator-(const CNumber& pCNumberOther) const {
	//przekierowanie do dodawania:
	
	//a>=0; b<0 -> a - (-b) = a + b
	if (isPositiveOrZero && !(pCNumberOther.isPositiveOrZero)) {
		CNumber temp;
		temp = pCNumberOther;
		temp.isPositiveOrZero = true;
		return *this + temp;
	}
	//a<0; b>=0 -> -a - b = - (a + b)
	if (!isPositiveOrZero && pCNumberOther.isPositiveOrZero) {
		CNumber temp;
		temp = *this;
		temp.isPositiveOrZero = true;
		temp = temp + pCNumberOther;
		temp.isPositiveOrZero = false;
		return temp;
	}

	//zwykle odejmowanie:

	//a>=0; b>=0 -> a - b
	bool symbol = true;
	if (isPositiveOrZero && pCNumberOther.isPositiveOrZero && *this >= pCNumberOther) symbol = true; //a>=b -> (a - b)>=0
	if (isPositiveOrZero && pCNumberOther.isPositiveOrZero && *this < pCNumberOther) symbol = false; //a<b ->  (a - b)<0
	//a<0; b<0 -> -a - (-b) = -a + b = - (a - b)
	if (!isPositiveOrZero && !pCNumberOther.isPositiveOrZero) {
		CNumber temp1;
		temp1 = *this;
		temp1.isPositiveOrZero = true;
		CNumber temp2;
		temp2 = pCNumberOther;
		temp2.isPositiveOrZero = true;
		return temp2 - temp1; //odwrotnosc bo ustawienie wyniku dla false przy rownych dawaloby -0
	}

	int biggerLength = std::max(length, pCNumberOther.length);

	CNumber retCNum;
	delete[] retCNum.numbersTab;
	retCNum.numbersTab = new int[biggerLength]();
	retCNum.length = biggerLength;

	CNumber bigger, smaller;

	bigger = std::max(absCNum(*this), absCNum(pCNumberOther));
	smaller = std::min(absCNum(*this), absCNum(pCNumberOther));

	int borrow = 0;
	for (int i = 0; i < biggerLength; ++i) {

		int num1 = bigger.numbersTab[i];
		int num2 = (i < smaller.length) ? smaller.numbersTab[i] : 0;

		int diff = num1 - num2 - borrow;

		if (diff < 0) {
			diff += DEFAULT_SYSTEM;
			borrow = 1;
		}
		else {
			borrow = 0;
		}
		retCNum.numbersTab[i] = diff;
	}

	retCNum.isPositiveOrZero = symbol;
	retCNum.normalize(); //usuwanie zer wiodacych
	return retCNum;	
}

CNumber CNumber::operator-(const int value) const{
	CNumber temp;
	temp = value;
	return *this - temp;
}

CNumber CNumber::operator*(const CNumber& pCNumberOther) const {
	//ustawienie znaku wyniku: te same znaki -> +; rozne znak -> -
	bool symbol = true;
	if (isPositiveOrZero != pCNumberOther.isPositiveOrZero) symbol = false;

	CNumber retCNum;

	std::vector<CNumber> vectCNumberToSum;

	int resultLength = 2*(std::max(length, pCNumberOther.length));

	delete[] retCNum.numbersTab;
	retCNum.numbersTab = new int[resultLength]();
	retCNum.length = resultLength;

	int carry, temp;
	for (int i = 0; i < length; ++i) {
		carry = 0;
		
		delete[] retCNum.numbersTab;
		retCNum.numbersTab = new int[resultLength]();
		retCNum.length = resultLength;

		for (int j = 0; j < pCNumberOther.length; ++j) {
			temp = (numbersTab[i] * pCNumberOther.numbersTab[j] + carry);
			retCNum.numbersTab[j] = temp % DEFAULT_SYSTEM;
			carry = temp / DEFAULT_SYSTEM;
		}
		if (pCNumberOther.length < resultLength) retCNum.numbersTab[pCNumberOther.length] = carry;
		retCNum.normalize(); //usuwanie zer wiodacych
		vectCNumberToSum.push_back(retCNum);
	}

	delete[] retCNum.numbersTab;
	retCNum.numbersTab = new int[resultLength]();
	retCNum.length = resultLength;
	
	for (int i = 0; i < vectCNumberToSum.size(); ++i) {
		retCNum = retCNum + vectCNumberToSum[i].addZeros(i); //mnozenie razy 10^i
	}
	
	retCNum.isPositiveOrZero = symbol;
	retCNum.normalize(); //usuwanie zer wiodacych
	return retCNum;
}

CNumber CNumber::operator*(const int value) const {
	CNumber temp;
	temp = value;
	return *this * temp;
}

CNumber CNumber::operator/(const CNumber& pCNumberOther) const {
	//powinien byc wyjatek przy probie dzielenia przez zero bo komunikat zabezpieczy tylko przed wyswietlaniem a nie przed dalszym uzywaniem
	
	//ustawienie znaku wyniku: te same znaki -> +; rozne znak -> -
	bool symbol = true;
	if (isPositiveOrZero != pCNumberOther.isPositiveOrZero) symbol = false;

	CNumber mid;

	//gdy dzielna jest mniejsza od dzielnika to dzielenie calkowite daje 0
	if (*this < pCNumberOther) {
		mid = 0;
		return mid;
	}
	//gdy dzielna jest rowna dzielnikowi to dzielenie calkowite daje 1
	if (*this == pCNumberOther) {
		mid = 1;
		return mid;
	}

	CNumber left, right;
	left = 1;
	right = *this;
	mid = 0;

	bool flag = true; //do wyjscia z while bo nie mozna uzywac break

	//wyszukiwanie binarne liczby ktora po pomnozeniu przez dzielnik da dzielna:
	while (left <= right && flag) {
		mid = half(right + left);
		if (mid * pCNumberOther > *this) right = mid - 1;
		else if (mid * pCNumberOther < *this) left = mid + 1;
		else {
			right = mid;
			flag = false;
		}
	}

	right = (right * pCNumberOther > *this) ? right - 1 : right; //gdy nie dzieli sie calkowicie to petla zwroci za duzy o 1 wynik dzielenia
	right.isPositiveOrZero = symbol;
	return right;
}

CNumber CNumber::operator/(const int value) const {
	CNumber temp;
	temp = value;
	return *this / temp;
}

//mod2
CNumber CNumber::operator<<(const unsigned int value) const{
	unsigned int temp = value;
	CNumber retCNum;
	retCNum = *this;

	for (unsigned int i = 0; i < temp; ++i)  {
		retCNum = retCNum * 2;
	}

	return retCNum;
}

CNumber CNumber::operator<<(const CNumber& pCNumberRight) const{
	CNumber zeroCNum;
	zeroCNum = 0;

	if (pCNumberRight == zeroCNum) return *this;

	CNumber pCNumberRightCopy;
	pCNumberRightCopy = pCNumberRight;
	pCNumberRightCopy.isPositiveOrZero = true;

	CNumber retCNum, lengthCNum, shiftCNum;

	int shift = 0;

	retCNum = *this;
	lengthCNum = length;
	shiftCNum = (pCNumberRightCopy - ((pCNumberRightCopy/lengthCNum)*lengthCNum)); //modulo
	
	while (shiftCNum > zeroCNum) {
		shiftCNum = shiftCNum - 1;
		shift++;
	}
	
	delete[] retCNum.numbersTab;
	retCNum.numbersTab = new int[length];

	for (int i = 0; i < length; ++i) {
		//operacje sa odwrotnie niz w normalnych tablicach bo cyfry liczby sa przechowywane w kolejnosci od tylu
		if (pCNumberRight.isPositiveOrZero) retCNum.numbersTab[(i + shift) % length] = numbersTab[i]; //right>0 -> w lewo
		else if (!pCNumberRight.isPositiveOrZero) retCNum.numbersTab[i] = numbersTab[(i + shift) % length]; //right<0 -> w prawo
	}
	
	return retCNum;
}

std::ostream& operator<<(std::ostream& os, const CNumber& CNum) {
	os << CNum.sToStr();
	return os;
}
//mod2