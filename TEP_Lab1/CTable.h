#ifndef CTABLE_H
#define CTABLE_H

#include <iostream>

class CTable {
	private:
		std::string s_name;
		int ctable_length;
		int *ctable;

	public:
		CTable();
		CTable(std::string sName, int iTableLen);
		CTable(CTable &pcOther);

		~CTable();

		void vSetName(std::string sName);
		bool bSetNewSize(int iTableLen);
		
		CTable *pcClone();

		void printCTable();
		void showParametersOfCTable();
};

#endif


