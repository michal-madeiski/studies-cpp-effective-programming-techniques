#include <iostream>
#include "constants.h"
#include "CTable.h"

//zad1
void v_alloc_table_fill_34(int iSize) {
    if (iSize <= 0) {
        std::cout << "Tab size must be above 0! \n";
        return;
    }

    int *table_to_fill;
    table_to_fill = new int[iSize];

    for (int i = 0; i < iSize; i++) {
        table_to_fill[i] = v_alloc_table_fill_34_DEFAULT_VALUE;
    }

    std::cout << "v_alloc_table_fill_34(" << iSize << "): ";
    for (int i = 0; i < iSize; i++) {
        std::cout << table_to_fill[i] << " ";
    }
    std::cout << "\n";

    delete[] table_to_fill;
}
//zad1

//zad2
bool b_alloc_table_2_dim(int ***piTable, int iSizeX, int iSizeY) {
    if (iSizeX <= 0 || iSizeY <= 0) {
        return false;
    }

    *piTable = new int *[iSizeY];

    for (int i = 0; i < iSizeY; ++i) {
        (*piTable)[i] = new int[iSizeX];
    }

    return true;
}
//zad2

//zad3
bool b_dealloc_table_2_dim(int ***piTable, int iSizeX, int iSizeY) {
    if (*piTable == NULL) {
        return false;
    }

    for (int i = 0; i < iSizeY; ++i) {
        delete (*piTable)[i];
    }
    delete *piTable;
    *piTable = NULL;

    return true;
}
//zad3

//zad4
void v_mod_tab(CTable *pcTab, int iNewSize) {
    if (pcTab != NULL) {
        pcTab->bSetNewSize(iNewSize);
    }
}

void v_mod_tab(CTable cTab, int iNewSize) {
    cTab.bSetNewSize(iNewSize);
}
//zad4

int main() {
    //zad1 test
    std::cout << "zad1 test: \n";

    std::cout << "//dynamiczna alokacja, wypelnienie i wyswietlenie tablicy: \n";
    v_alloc_table_fill_34(5);
    std::cout << "\n";

    std::cout << "\n";
    //zad1 test

    //zad2 test
    std::cout << "zad2 test: \n";

    int **piTable;
    int sizeX = 5, sizeY = 3;
    bool alloc_try = b_alloc_table_2_dim(&piTable, sizeX, sizeY);
    std::cout << "//proba alokacji tablicy2d: \n";
    std::cout << "alloc_try=" << alloc_try << "\n";
    std::cout << "\n";

    std::cout << "//wyswietlenie tablicy2d po alokacji: \n";
    for (int i = 0; i < sizeY; ++i) {
        for (int j = 0; j < sizeX; ++j) {
            std::cout << piTable[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";

    std::cout << "//stan pointera **piTable po alokacji: \n";
    std::cout << "**piTable=" << piTable << "\n";
    std::cout << "\n";

    std::cout << "\n";
    //zad2 test

    //zad3 test
    std::cout << "zad3 test: \n";

    std::cout << "//pierwsza proba dealokacji: \n";
    bool first_dealloc_try = b_dealloc_table_2_dim(&piTable, sizeX, sizeY);
    std::cout << "first_dealloc_try=" << first_dealloc_try << "\n";
    std::cout << "//stan pointera **piTable po dealokacji: \n";
    std::cout << "**piTable=" << piTable << "\n";
    std::cout << "\n";

    std::cout << "//druga proba dealokacji: \n";
    bool second_dealloc_try = b_dealloc_table_2_dim(&piTable, sizeX, sizeY);
    std::cout << "second_dealloc_try=" << second_dealloc_try << "\n";
    std::cout << "\n";

    std::cout << "\n";
    //zad3 test

    //zad4 test
    std::cout << "zad4 test: \n";

    std::cout << "//statyczna alokacja CTable: \n";
    CTable CTableTest("test CTable", 5);
    CTableTest.showParametersOfCTable();
    CTableTest.printCTable();
    std::cout << "\n";

    std::cout << "//zmiana nazwy i dlugosci CTable: \n";
    CTableTest.vSetName("test CTable - nowa");
    CTableTest.bSetNewSize(10);
    CTableTest.showParametersOfCTable();
    CTableTest.printCTable();
    std::cout << "\n";

    std::cout << "//tworzenie CTable poprzez konstruktor kopiujacy: \n";
    CTable CTableTestCopy(CTableTest);
    CTableTestCopy.bSetNewSize(10);
    CTableTestCopy.showParametersOfCTable();
    CTableTestCopy.printCTable();
    std::cout << "\n";

    std::cout << "//alokacja dynamiczna CTable poprzez metode pcClone(): \n";
    CTable *pCTableClone = CTableTestCopy.pcClone();
    std::cout << "\n";

    std::cout << "//tablica obiektow CTable (alokacja dynamiczna): \n";
    CTable *CTableObjects = new CTable[CTableObjects_DEFAULT_LENGTH];
    std::cout << "\n";

    std::cout << "//v_mod_tab z obiektem (tworzy sie kopia): \n";
    v_mod_tab(CTableTest, CTable_DEFAULT_LENGTH); //nie zmieni¹ siê parametry - tworzy siê kopia i potem siê usunie
    CTableTest.showParametersOfCTable();
    std::cout << "\n";

    std::cout << "//v_mod_tab z referencja (zmienia sie parametry): \n";
    v_mod_tab(&CTableTest, CTable_DEFAULT_LENGTH); //zmieni¹ siê parametry
    CTableTest.showParametersOfCTable();
    std::cout << "\n";

    std::cout << "//usuniecie dynamicznie zaalokowanych elmentow tablicy obiektow CTable: \n";
    delete[] CTableObjects;
    std::cout << "\n";
    //zad4 test

    std::cout << "//usuniecie statycznie zaalokowanych obiektow CTable:: \n";
    return 0;
}
