#ifndef CInfo_H
#define CInfo_H

#include <iostream>
#include <vector>

class CInfo {
public:
    CInfo();
    CInfo(const CInfo& other);
    ~CInfo();

    friend std::ostream& operator<<(std::ostream& os, CInfo& Info);
    CInfo& operator=(CInfo other);

    std::string lastInfo;
    std::vector<std::string> infoList;

    void addInfo(const std::string& Info);
    void uploadInfo(const std::string& Info);
    void newInfo();
    void closeInfo();

    std::string nextInfo();
private:
    std::string tempInfo;
};
#endif //CInfo_H
