#include <iostream>
#include "CInfo.h"
#include <algorithm>

CInfo::CInfo() {
    lastInfo = "";
    tempInfo = "";
    infoList.clear();
}

CInfo::CInfo(const CInfo &other) {
    lastInfo = other.lastInfo;
    tempInfo = other.tempInfo;
    infoList = other.infoList;
}

CInfo::~CInfo() {
}

std::ostream& operator<<(std::ostream& os, CInfo& Info){
    std::reverse(Info.infoList.begin(),Info.infoList.end());
    while(!Info.infoList.empty()){
        os << "INFO: " << Info.nextInfo() << "\n ";
    }
    return os;
}

CInfo& CInfo::operator=(CInfo other){
    std::swap(*this, other);
    return *this;
}

void CInfo::addInfo(const std::string& Info) {
    infoList.push_back(Info);
    lastInfo = Info;
}

void CInfo::uploadInfo(const std::string& Info) {
    tempInfo += Info;
}

void CInfo::newInfo() {
    tempInfo = "";
}

void CInfo::closeInfo() {
    if (!tempInfo.empty()) infoList.push_back(tempInfo);
    tempInfo = "";
}

std::string CInfo::nextInfo() {
    lastInfo = infoList[infoList.size() - 1];
    infoList.pop_back();
    return lastInfo;
}






