#include <iostream>
#include "Result_T_E.h"
#include "saver/Saver.h"
#include "tree/CTree.h"
#include "tree/CTreeUI.h"

using namespace std;

int main() {
    Saver<CTree> saver;

    //zapis bledow drzewa
    string expr1 = "+ + + # a b c d e";
    Result<CTree, Error> test1 = CTree::createWithResultOrError(expr1);
    test1.print();
    saver.save(test1, "test1");

    cout<<endl;

    //zapis poprawnego drzewa
    string expr2 = "+ a b";
    Result<CTree, Error> test2 = CTree::createWithResultOrError(expr2);
    test2.print();
    saver.save(test2, "test2");

    cout<<endl;

    //czy zapis sie udal
    Result<Saver<CTree>, Error> test3 = saver.save(test2, "test3");
    test3.print();

    // CTreeUI testTree;
    // testTree.start();

    return 0;
}

