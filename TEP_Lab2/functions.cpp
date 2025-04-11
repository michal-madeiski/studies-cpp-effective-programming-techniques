#include <iostream>
#include "CNumber.h"
std::ostream& ::operator<<(std::ostream& os, const CNumber& c)
{
	os << c.sToStr();
	return os;
}