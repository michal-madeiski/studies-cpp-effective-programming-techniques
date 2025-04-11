#include <iostream>
#include "constants.h"
#include "CTable.h"

CTable::CTable() {
	s_name = CTable_DEFAULT_NAME;
	ctable_length = CTable_DEFAULT_LENGTH;
	ctable = new int[ctable_length];

	std::cout << "bezp: '<" << s_name << ">' \n";
}

CTable::CTable(std::string sName, int iTableLen) {
	s_name = sName;
	ctable_length = iTableLen;
	ctable = new int[iTableLen];
	std::cout << "parametr: '<" << s_name << ">' \n";
}

CTable::CTable(CTable &pcOther) {
	s_name = pcOther.s_name + "_copy";
	ctable_length = pcOther.ctable_length;
	ctable = new int[ctable_length];

	for (int i = 0; i < ctable_length; ++i) {
		ctable[i] = pcOther.ctable[i];
	}

	std::cout << "kopiuj: '<" << s_name << ">' \n";
}

CTable::~CTable() {
	std::cout << "usuwam: '<" << s_name << ">' \n";
	delete[] ctable;
}

void CTable::vSetName(std::string sName) {
	s_name = sName;
}

bool CTable::bSetNewSize(int iTableLen) {
	if (iTableLen < 0) {
		return false;
	}

	int *ctable_new = new int[iTableLen];
	for (int i = 0; i < ctable_length; ++i) {
		if (i < iTableLen) {
			ctable_new[i] = ctable[i];
		}
	}

	ctable_length = iTableLen;
	delete[] ctable;

	ctable = new int[ctable_length];
	for (int i = 0; i < ctable_length; ++i) {
		ctable[i] = ctable_new[i];
	}
	delete[] ctable_new;

	return true;
}

CTable *CTable::pcClone() {
	return new CTable(*this);
}


void CTable::printCTable() {
	for (int i = 0; i < ctable_length; ++i) {
		std::cout << ctable[i] << " ";
	}
	std::cout << "\n";
}

void CTable::showParametersOfCTable() {
	std::cout << "s_name='<" << s_name << ">'; ctable_length=" << ctable_length << ">' \n";
}