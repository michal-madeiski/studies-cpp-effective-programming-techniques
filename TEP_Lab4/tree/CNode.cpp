#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <cmath>
#include <algorithm>
#include "CNode.h"
#include "constants.h"

CNode::CNode(const std::string &tokens) {
    initFields(0, childrenCounter(tokens), tokens);
}

CNode::CNode(const CNode &other) {
    initFields(0, other.maxChildren, other.tokens);
    copyChildren(this, &other);
}

CNode::CNode() {
    initFields(0, ROOT_MAX_CHILDREN, "R");
}

CNode::~CNode() {
    for (int i = 0; i < maxChildren; ++i) {
        delete childrenTab[i];
        childrenTab[i] = NULL;
    }
    currentChildren = 0;
    delete[] childrenTab;
}

void CNode::initFields(int currentChildren_, int maxChildren_, const std::string &tokens_) {
    currentChildren = currentChildren_;
    maxChildren = maxChildren_;
    childrenTab = new CNode*[maxChildren_];
    for (int i = 0; i < maxChildren_; i++) {
        childrenTab[i] = NULL;
    }
    tokens = tokens_;
    type = defineType(tokens_);
}

int CNode::childrenCounter(const std::string &tokens) {
    typeCNodeMap::const_iterator mapIter = OPR_MAP.find(std::string(tokens.begin(), tokens.end()));

    if(mapIter == OPR_MAP.end()) return 0; //nie ma takiego operatora
    return mapIter -> second.first; //zwraca 1szy czlon wartosci (ktora jest para) - ilosc dzieci
}

void CNode::copyChildren(CNode *parent, const CNode *other) {
    if (other == NULL) return;
    for (int i = 0; i < other->maxChildren; ++i) {
        parent->addChild(other->childrenTab[i]->tokens);
        int next = parent->currentChildren - 1;
        copyChildren(parent->childrenTab[next], other->childrenTab[i]);
    }
}

void CNode::addChild(const std::string &tokens) {
    if (currentChildren == maxChildren) return;
    childrenTab[currentChildren++] = new CNode(tokens);
}

std::string CNode::toString() const {
    return std::string(tokens.begin(), tokens.end());
}

std::ostream& operator<<(std::ostream& os, const CNode& node) {
    os << node.toString();
    return os;
}

int CNode::defineType(const std::string &tokens) {
    //iterator przechodzacy po mapie
    //jesli znajdzie klucz zlozony ze stringa stworzonego z tokenow to zwroci wartosc od tego klucza
    //jesli nie to zwroci specjalna wartosc koncowa wskazujaca na pozycje poza mapa
    typeCNodeMap::const_iterator mapIter = OPR_MAP.find(tokens);

    //klucz zlozomy ze stringa z tokenow jest czescia mapy
    if (mapIter != OPR_MAP.end()) return OPR_CODE;

    for (char c : tokens) {
        if (int(c) != 46 && !(int(c) >= 48 && int(c) <= 57) && !(int(c) >= 65 && int(c) <= 90) && !(int(c) >= 97 && int(c) <= 122)) return UNDEF_CODE;
    }

    for (char c : tokens) {
        if ((int(c) >= 65 && int(c) <= 90) || (int(c) >= 97 && int(c) <= 122)) return VAR_CODE;
    }

    //sprawdzanie czy jest to double czyli num
    bool dotFlag = false; //false czyli domyslnie wyrazenie bez kropki
    if (int(tokens[0]) >= 48 && int(tokens[0]) <= 57) {
        for (int i = 1; i < tokens.length(); ++i) {
            if (int(tokens[i]) == 46 && dotFlag == false) dotFlag = true;
            else if (int(tokens[i]) == 46 && dotFlag == true) return UNDEF_CODE;
        }
        if (dotFlag == true && tokens.length() < 3) return UNDEF_CODE;
        return NUM_CODE;
    }
    if (int(tokens[0]) == 46) return UNDEF_CODE;

    //zostaly tylko num bo w ctree bylo sprawdzenie niepoprawnych znakow
    return NUM_CODE;
}

double CNode::strToDouble(const std::string &tokens) {
    char* end;
    return std::strtod(tokens.c_str(), &end);
}

char CNode::normalizeChar(const char &token) {
    std::string temp = "";
    temp += token;
    typeCNodeMap::const_iterator map_iter = OPR_MAP.find(temp);
    //if(map_iter != OPR_MAP.end()) return token;

    char ret = std::tolower(token);
    int asciiVal = int(ret);
    if ((asciiVal >= 48 && asciiVal < 57) || (asciiVal >= 65 && asciiVal <=90) || (asciiVal >= 97 && asciiVal <=122)){
        return ret;
    }

    return token;
    //return 0;
}

const typeCNodeMap CNode::OPR_MAP = createOprMap();
typeCNodeMap CNode::createOprMap() {
    typeCNodeMap result;
    result["/"] = std::make_pair(2, &CNode::div);
    result["*"] = std::make_pair(2, &CNode::mul);
    result["+"] = std::make_pair(2, &CNode::add);
    result["-"] = std::make_pair(2, &CNode::sub);
    result["sin"] = std::make_pair(1, &CNode::sin);
    result["cos"] = std::make_pair(1, &CNode::cos);
    return result;
}

const std::string CNode::DEFAULT_CHILD = "1";

bool CNode::isOpr() const{return type == OPR_CODE;}
bool CNode::isVar() const{return type == VAR_CODE;}
bool CNode::isNum() const{return type == NUM_CODE;}
bool CNode::isUndef() const {return type == UNDEF_CODE;}
bool CNode::isTrue() const{return true;}

double CNode::add(const std::vector<double> &comps){return comps[0] + comps[1];}
double CNode::sub(const std::vector<double> &comps){return comps[0] - comps[1];}
double CNode::mul(const std::vector<double> &comps){return comps[0] * comps[1];}
double CNode::div(const std::vector<double> &comps){return comps[0] / comps[1];}
double CNode::sin(const std::vector<double> &comps){return std::sin(comps[0]);}
double CNode::cos(const std::vector<double> &comps){return std::cos(comps[0]);}
