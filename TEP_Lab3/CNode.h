#ifndef CNODE_H
#define CNODE_H

#include <iostream>
#include <string>
#include <map>
#include <vector>

typedef std::map<std::string, std::pair<int, double (*)(const std::vector<double>&) > > typeCNodeMap;
class CNode {
public:
    friend class CTree;
    friend class CTreeUI;

    CNode(const std::string &tokens);
    CNode(const CNode &other);
    ~CNode();

    std::string toString() const;
    friend std::ostream& operator<<(std::ostream& os, const CNode& node);
private:
    CNode();

    int maxChildren;
    int currentChildren;
    int type;
    std::string tokens;
    CNode **childrenTab;

    void initFields(int currentChildren_, int maxChildren_, const std::string &tokens_);
    int childrenCounter(const std::string &tokens);
    static void copyChildren(CNode *parent, const CNode *other);
    void addChild(const std::string &tokens);

    static int defineType(const std::string &tokens);
    static double strToDouble(const std::string &tokens);
    static char normalizeChar(const char &token);

    static const typeCNodeMap OPR_MAP;
    static typeCNodeMap createOprMap();

    static const std::string DEFAULT_CHILD;

    bool isNum() const;
    bool isOpr() const;
    bool isVar() const;
    bool isUndef() const;
    bool isTrue() const;

    static double add(const std::vector<double> &comps);
    static double sub(const std::vector<double> &comps);
    static double mul(const std::vector<double> &comps);
    static double div(const std::vector<double> &comps);
    static double sin(const std::vector<double> &comps);
    static double cos(const std::vector<double> &comps);
};

#endif //CNODE_H
