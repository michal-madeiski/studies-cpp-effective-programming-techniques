#include <iostream>
#include "SmartPointer.h"
#include "tree/CTree.h"
using namespace std;

void testSP(int* p) {
    SmartPointer<int> sp(p);
    cout << "Wartosc wskazywana przez wskaznik opakowany przez SmartPointer we wnetrzu funkcji: " << *sp << endl;
}

int main() {
    //smart pointer
    cout <<"SMART POINTER TEST:" << "\n";

    int *p = new int(10);
    SmartPointer<int> sp(p);

    testSP(p);

    cout << "Wartosc wskazywana przez wskaznik opakowany przez SmartPointer po wyjsciu z funkcji: " << *sp << "\n";
    //wartość jest inna, bo wychodząc z funkcji SmartPointer usunął swoje zasoby tj. *p

    cout << "---------------------------------------------------------------------------------------------------------\n";

    //move semantics
    cout <<"MOVE SEMANTICS TEST:" << "\n";

    vector<string> vec1 = {"+", "a", "b"};
    vector<string> vec2 = {"*", "c", "10"};
    CTree t1(vec1), t2(vec2);
    cout << "t1 -> " << t1 << "\n";
    cout << "t2 -> " << t2 << "\n";
    CTree t3 = t1 + t2; //move semantics, bo t1 + t2 to obiekt tymczasowy (operator+ zwraca przez wartość) i jest to rvalue
    cout << "t3 = t1 + t2 -> " << t3 << "\n";

    CTree t4(vec1), t5(vec2);
    cout << "t4 -> " << t4 << "\n";
    cout << "t5 -> " << t5 << "\n";
    CTree t6 = t4 + t5; //move semantics
    cout << "t6 = t4 + t5 -> " << t6 << "\n";

    CTree t7 = t3 + t6; //move semantics
    cout << "t7 = t3 + t6 -> " << t7 << "\n\n";

    cout << "Dane przed wprowadzeniem move semantics: \n-number of copies: 6\n-number of moves: 0\n\n";
    cout << "Dane po wprowadzeniu move semantics: " << "\n";
    cout << "-number of copies: " << CTree::copyCount << "\n";
    cout << "-number of moves: " << CTree::moveCount << "\n";

    cout << "---------------------------------------------------------------------------------------------------------\n";

    //mod5
    cout << "MOD5 TEST: " << "\n";

    int *p_mod1 = new int(1);
    SmartPointer<int> sp_mod1(p_mod1);
    cout << "sp_mod1 = " << *sp_mod1 << "\n";

    //konstrukcja przez przeniesienie
    SmartPointer<int> sp_mod2(move(sp_mod1));
    cout << "sp_mod2 = " << *sp_mod2 << "\n";

    //konstrukcja przez przypisanie
    SmartPointer<int> sp_mod3 = move(sp_mod2);
    cout << "sp_mod3 = " << *sp_mod3 << "\n";
    //cout << "sp_mod2 = " << *sp_mod2 << "\n"; //program się wysypuje - niepoprawna pamięć po przeniesieniu

    sp_mod2 = move(sp_mod1);
    //cout << "sp_mod2 = " << *sp_mod2 << "\n"; //program się wysypuje - próba podwójnego przeniesienia

    int *p_mod2 = new int(2);
    SmartPointer<int> sp_mod4(p_mod2);
    SmartPointer<int> sp_mod5 = move(sp_mod4 = move(sp_mod3));
    cout << "sp_mod5 = " << *sp_mod5 << "\n";
    //cout << "sp_mod4 = " << *sp_mod4 << "\n"; //program się wysypuje - próba podwójnego przeniesienia
    //mod5

    return 0;
}
