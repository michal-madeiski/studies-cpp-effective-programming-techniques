#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <cmath>
#include <algorithm>
#include "CTree.h"
#include <sstream>
#include "CNode.h"
#include "constants.h"

CTree::CTree(std::vector<std::string> &expression) {
    root = new CNode();
    size = 0;

    for (int i = 0; i < expression.size(); i++) {
        for (int j = 0; j < expression.size(); ++j) {
            expression[i][j] = CNode::normalizeChar(expression[i][j]);
        }
    }

    int temp = findParentAndAdd(root, expression, 0);
    fixTree(root->childrenTab[0]);

    if (temp < expression.size()) {
        std::cout << "INFO: za duzo argumentow, nie wczytano: ";
        for (int i = temp; i < expression.size(); ++i) {
            for (int j = 0; j < expression[i].size(); ++j) {
                std::cout << expression[i][j];
            }
            std::cout << " ";
        }
        std::cout << "\n";
    }
}

CTree::CTree(const CTree &other) {
    root = new CNode(*other.root);
    size = other.size;
}

CTree::~CTree() {
    delete root;
}

CTree& CTree::operator=(CTree other){
    swapWithOtherTree(other);
    return *this;
}

CTree CTree::operator+(const CTree &other) const {
    CTree copy (*this);
    if (other.size == 0) return copy;
    if (copy.size ==0) return other;

    const CNode* firstLeaf = findFirstLeafToAdd(copy.root);

    delete firstLeaf;
    firstLeaf = new CNode(*other.root->childrenTab[0]);
    copy.size += other.size - 1;

    return copy;
}

std::string CTree::toString() const{
    return toString(&CNode::isTrue);
}

std::string CTree::toString(bool (CNode::*checkFunction)() const) const{
    std::vector<const CNode*> buffer;
    std::string result;
    nodesToVector(root->childrenTab[0], buffer, checkFunction);

    for(int i = 0; i < buffer.size(); ++i){
        result += buffer[i]->toString() + " ";
    }
    return result;
}

std::ostream& operator<<(std::ostream &os, const CTree &other){
    os << "CTree: ";
    return other.size ? other.getOstreamText(os) : os << "";
}

std::ostream& CTree::getOstreamText(std::ostream &os) const{
    os << toString();
    return os;
}

bool CTree::comp(std::vector<double> &vars) {
    std::vector<const CNode*> nodes;
    nodesToVector(root -> childrenTab[0], nodes, &CNode::isVar);

    if (nodes.size() != vars.size()) {
        return false;
    }

    varsMap.clear();
    for (int i = 0; i < std::min(vars.size(), nodes.size()); ++i) {
        varsMap[nodes[i] -> toString()] = vars[i];
    }
    return true;
}

double CTree::calculate() const {
    return calculateInner(root->childrenTab[0]);
}
double CTree::calculateInner(const CNode *node) const {
    if (node == NULL) return 0.0;

    std::string text = node -> toString();

    if (node->isVar()) {
        return varsMap.at(text); //zwraca wartosc dla zmiennej
    }

    else if (node->isNum()) {
        return CNode::strToDouble(text); //zwraca wartosc liczbowa
    }

    std::vector<double> value;
    double (*functionPointer)(const std::vector<double>&);
    functionPointer = (node->OPR_MAP.at(text)).second; //wskaznik do funkcji wykonujacej dany operator
    for (int i = 0; i < node->currentChildren; ++i) {
        value.push_back(calculateInner(node->childrenTab[i]));
    }

    return (*functionPointer)(value);
}

int CTree::findParentAndAdd(CNode *parent, const std::vector<std::string> &expression, int startIdx) {
    if (startIdx >= expression.size()) return startIdx;

    int expressionIdx = startIdx;
    for (int i = 0; i < parent->maxChildren && expressionIdx < expression.size(); ++i) {
        parent->addChild(expression[expressionIdx]);
        ++expressionIdx;
        expressionIdx = findParentAndAdd(parent->childrenTab[parent->currentChildren - 1], expression, expressionIdx);
        size++;
    }
    return expressionIdx;
}

void CTree::fixTree(CNode *node) const {
    if (node == NULL) return;

    if (node->isUndef()) {
        std::cout << "INFO: niepoprawny znak, zastapiono przez: " << node->DEFAULT_CHILD << "\n ";
        node->tokens = node->DEFAULT_CHILD;
        node->currentChildren = 0;
        node->maxChildren = 0;
        node->type = NUM_CODE;
    }

    for (int i = node->currentChildren; i < node->maxChildren; ++i) {
        node->addChild(node->DEFAULT_CHILD);
        std::cout << "INFO: brakujacy argument dla: '" << node->toString() <<"', uzupelniono przez: " << node->DEFAULT_CHILD << "\n ";
    }

    for (int i = 0; i < node->currentChildren; ++i) {
        fixTree(node->childrenTab[i]);
    }
}

void CTree::nodesToVector(const CNode *node, std::vector<const CNode *> &buffer, bool (CNode::*checkFunction)() const) {
    if (node == NULL) return;
    if ((node->*checkFunction)()) buffer.push_back(node);
    for (int i = 0; i < node->currentChildren; ++i) {
        nodesToVector(node->childrenTab[i], buffer, checkFunction);
    }
}

const CNode* CTree::findFirstLeafToAdd(const CNode* parent){
    if(parent->maxChildren == 0 || parent->currentChildren == 0) return parent;
    return findFirstLeafToAdd(parent->childrenTab[0]);
}

void CTree::swapWithOtherTree(CTree &other) {
    size = other.size;
    std::swap(root, other.root);
}

//mod3
void CTree::optimize(CNode *node) {
    if (node == NULL) return;

    for (int i = 0; i < node->currentChildren; ++i) {
        optimize(node->childrenTab[i]);
    }
    if (node->isOpr()) {
        bool flag = true;
        for (int i = 0; i < node->currentChildren; ++i) {
            if (!(node->childrenTab[i] -> isNum())) {
                flag = false;
            }
        }
        if (flag) {
            std::string newVal = doubleToString(calculateToOpt(node));

            for (int i = 0; i < node->currentChildren; ++i) {
                delete node->childrenTab[i];
            }
            delete[] node->childrenTab;
            node->currentChildren = 0;
            node->maxChildren = 0;
            node->childrenTab = new CNode*[node->maxChildren];
            node->tokens = newVal;
            node->type = NUM_CODE;
        }
    }
}

double CTree::calculateToOpt(const CNode *node) const {
    std::vector<double> value;
    double (*functionPointer)(const std::vector<double>&);
    functionPointer = (node->OPR_MAP.at(node->tokens)).second; //wskaznik do funkcji wykonujacej dany operator
    for (int i = 0; i < node->currentChildren; ++i) {
        value.push_back(calculateInner(node->childrenTab[i]));
    }

    return (*functionPointer)(value);
}

static std::string doubleToString(const double &doubleVal) {
    std::ostringstream os;
    os << doubleVal;
    return os.str();
}
//mod3





