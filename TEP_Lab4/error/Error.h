#ifndef ERROR_H
#define ERROR_H

#include "iostream"

using namespace std;

class Error {
public:
    Error(const string &errorMessage);
    Error(const Error &other);
    ~Error();

    friend std::ostream& operator<<(std::ostream& os, const Error& err);

    string getErrorMessage();
private:
    string errorMessage;
};


#endif //ERROR_H
