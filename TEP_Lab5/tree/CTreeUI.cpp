#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <cmath>
#include <algorithm>
#include "CTreeUI.h"
#include "CTree.h"
#include "CNode.h"
#include "constants.h"
#include "CInfo.h"
#include <utility>

CTreeUI::CTreeUI() {
    tree = NULL;
    isRunning = true;
}

CTreeUI::~CTreeUI() {
    if (tree == NULL) return;
    delete tree;
}

void CTreeUI::start() {
    std::cout<<"Wprowadz komende po znaku '->': ";
    std::string expression;
    while (isRunning) {
        std::cout << "\n-> ";
        std::getline(std::cin, expression);
        parseExpression(expression);
    }
}

void CTreeUI::parseExpression(std::string &expression) {
    int index = 0;
    parsedExpressions.clear();
    parsedExpressions.push_back("");

    for (; index < expression.size(); ++index) {
        if (expression[index] == ' ') parsedExpressions.push_back("");
        while (index < expression.size() && expression[index] == ' ') ++index;
        parsedExpressions[parsedExpressions.size() - 1] += expression[index];
    }

    if (parsedExpressions.empty()) {
        std::cout << "ERROR: podano niepoprawne polecenie \n";
        return;
    }

   typeCTreeUIMap::const_iterator mapIter = COMMANDS_MAP.find(parsedExpressions[0]);
    if (mapIter == COMMANDS_MAP.end()) {
        std::cout << "ERROR: podano niepoprawne polecenie \n";
        return;
    }

    int argumentsAmount = mapIter->second.first;

    if (argumentsAmount != parsedExpressions.size() - 1 && argumentsAmount != UNDEF_ARGS) {
        std::cout << "ERROR: nie mozna wykonac polecenia - zostala podana zla ilosc parametrow \n";
        return;
    }

    (this ->* (mapIter -> second.second))();
    if (tree != NULL) std::cout << tree->info;
}

void CTreeUI::enter() {
    if (tree != NULL) {
        delete tree;
        tree = NULL;
    }
    std::vector<std::string> temp(parsedExpressions.begin() + 1, parsedExpressions.end());
    tree = new CTree(temp);
}

void CTreeUI::vars() {
    if (tree == NULL) {
        std::cout << "ERROR: nie mozna wyswietlic zmiennych - drzewo nie zostalo podane \n";
        return;
    }
    std::cout << "Vars: " << tree -> toString(&CNode::isVar) << "\n";
}

void CTreeUI::print() {
    if (tree == NULL) {
        std::cout << "ERROR: nie mozna wyswietlic drzewa - drzewo nie zostalo podane \n";
        return;
    }
    std::cout << *tree << "\n";
}

void CTreeUI::comp(){
    if (tree == NULL) {
        std::cout << "ERROR: nie mozna obliczyc wyrazenia - drzewo nie zostalo podane \n";
        return;
    }

    std::vector<double> temp;
    for (int i = 1; i < parsedExpressions.size(); ++i) {
        temp.push_back(CNode::strToDouble(parsedExpressions[i]));
    }

    bool flag = tree->comp(temp);
    if (!flag) {
        std::cout << "ERROR: nie mozna obliczyc wyrazenia - zostala podana zla ilosc parametrow \n";
        return;
    }

    std::cout << "Wartosc wyrazenia: " << tree->calculate() << "\n";
}

void CTreeUI::join(){
    if (tree == NULL) {
        std::cout << "ERROR: nie mozna dolaczyc - drzewo nie zostalo podane \n";
        return;
    }
    std::vector<std::string> temp(parsedExpressions.begin() + 1, parsedExpressions.end());
    CTree tempTree = CTree(temp);
    *tree = *tree + tempTree;
}

void CTreeUI::exit(){
    std::cout << "Zakonczono dzialanie programu. \n";
    isRunning = false;
}

const typeCTreeUIMap CTreeUI::COMMANDS_MAP = createCommandsMap();
typeCTreeUIMap CTreeUI::createCommandsMap(){
    typeCTreeUIMap result;
    result["print"] = std::make_pair(0, &CTreeUI::print);
    result["vars"] = std::make_pair(0, &CTreeUI::vars);
    result["comp"] = std::make_pair(UNDEF_ARGS, &CTreeUI::comp);
    result["enter"] = std::make_pair(UNDEF_ARGS, &CTreeUI::enter);
    result["join"] = std::make_pair(UNDEF_ARGS, &CTreeUI::join);
    result["exit"] = std::make_pair(0, &CTreeUI::exit);
    //mod3
    result["optimize"] = std::make_pair(0, &CTreeUI::opt);
    //mod3
    return result;
}

//mod3
void CTreeUI::opt() {
    if (tree == NULL) {
        std::cout << "ERROR: nie mozna zoptymalizowac - drzewo nie zostalo podane \n";
        return;
    }
    tree->optimize(tree->root->childrenTab[0]);
}
//mod3




