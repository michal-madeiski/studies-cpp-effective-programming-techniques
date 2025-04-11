#ifndef CTREEUI_H
#define CTREEUI_H

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "CTree.h"
#include "CNode.h"

class CTreeUI; //to musi byc zeby zdefiniowac typ bo uzywa rzeczy z CTreeUI
typedef std::map<std::string, std::pair<int, void (CTreeUI::*)() > > typeCTreeUIMap; //drugi element wartosci to wskaznik na jakas funkcje z CTreeUI

class CTreeUI {
public:
    CTreeUI();
    ~CTreeUI();

    void start();
    void parseExpression(std::string &expression);

    //mod3
    void opt();
    //mod3
private:
    CTree *tree;
    bool isRunning;
    std::vector<std::string> parsedExpressions;

    void enter();
    void vars();
    void print();
    void comp();
    void join();
    void exit();

    static const typeCTreeUIMap COMMANDS_MAP;
    static typeCTreeUIMap createCommandsMap();
};

#endif //CTREEUI_H
