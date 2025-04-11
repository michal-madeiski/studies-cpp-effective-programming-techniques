#ifndef CTREE_H
#define CTREE_H

#include <iostream>
#include <string>
#include <vector>
#include "CNode.h"
#include "CInfo.h"

class CTree {
public:
    //lista5
    CTree(CTree &&other);
    CTree &operator=(CTree &&other) ;

    static int copyCount;
    static int moveCount;
    //lista5

    friend class CTreeUI;

    CTree(std::vector<std::string> &expression);
    CTree(const CTree &other);
    ~CTree();

    CTree& operator=(CTree &other);
    CTree operator+(const CTree &other) const;

    std::string toString() const;
    friend std::ostream& operator<<(std::ostream& os, const CTree &tree);

    bool comp(std::vector<double> &vars);
    double calculate() const;
    bool hasInfo() const;

    //mod3
    void optimize(CNode *node);
    //mod3

private:
    CNode *root;
    int size;
    std::map<std::string, double> varsMap;
    CInfo info;

    int findParentAndAdd(CNode *parent, const std::vector<std::string> &expression, int startIdx);
    void fixTree(CNode *node);
    static void nodesToVector(const CNode *apc_node, std::vector<const CNode*> &avc_buffer, bool (CNode::*checkFunction)() const);
    static CNode* findFirstLeafToAdd(CNode* parent);

    std::string toString(bool (CNode::*checkFunction)() const) const; //wyswietlanie warunkowe np samych zmiennych
    std::ostream& getOstreamText(std::ostream& os) const;

    double calculateInner(const CNode* node) const;
    void swapWithOtherTree(CTree &other);

    //mod3
    double calculateToOpt(const CNode* node) const;
    //mod3
};
//mod3
static std::string doubleToString(const double &doubleVal);
//mod3

#endif //CTREE_H
