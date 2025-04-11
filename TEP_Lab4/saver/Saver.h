#ifndef SAVER_H
#define SAVER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "../error/Error.h"
#include "../Result_T_E.h"
#include "../tree/CTree.h"

using namespace std;

template <typename T>
class Saver {
public:
    Saver();
    Saver(const Saver &other);
    ~Saver();

    template <typename A>
    Result<Saver<T>, Error> save(Result<A, Error> res, const string &fileName);

    template<typename A>
    friend ostream& operator<<(ostream& os, const Saver<A> &sav);

    string toString() const;
private:
    int status;
    static const int STATUS_INPROGRESS = 0;
    static const int STATUS_OK = 1;
    static const int STATUS_FAIL = -1;
};

template <typename T>
Saver<T>::Saver() {
    status = STATUS_INPROGRESS;
}

template<typename T>
Saver<T>::Saver(const Saver &other) {
    status = other.status;
}

template <typename T>
Saver<T>::~Saver() {
}

template <typename T>
template <typename A>
Result<Saver<T>, Error> Saver<T>::save(Result<A, Error> res, const string &fileName) {
    const char *fileNameChar = fileName.c_str();
    std::ofstream output(fileNameChar, std::ios::out);

    if (!output.is_open()) {
        status = STATUS_FAIL;
        return Result<Saver<T>, Error>::fail(new Error("Nie udalo sie otworzyc pliku: " + string(fileNameChar)));
    }

    if (!res.isSuccess()) {
        for (unsigned int i = 0; i < res.getErrors().size(); ++i) {
            output << *(res.getErrors()[i]) << '\n';
            output.close();
            status = STATUS_OK;
        }
    }

    return Result<Saver<T>, Error>::ok(*this);
}

template <>
template <typename A>
Result<Saver<CTree>, Error> Saver<CTree>::save(Result<A, Error> res, const string &fileName) {
    const char *fileNameChar = fileName.c_str();
    std::ofstream output(fileNameChar, std::ios::out);

    if (!output.is_open()) {
        status = STATUS_FAIL;
        return Result<Saver<CTree>, Error>::fail(new Error("Nie udalo sie otworzyc pliku: " + string(fileNameChar)));
    }

    if (!res.isSuccess()) {
        for (unsigned int i = 0; i < res.getErrors().size(); ++i) {
            output << *(res.getErrors()[i]) << '\n';
        }
    } else {
        output << res.getVal();
    }

    output.close();
    status = STATUS_OK;

    return Result<Saver<CTree>, Error>::ok(*this);
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Saver<T>& sav) {
    os << sav.toString();
    return os;
}

template<typename T>
std::string Saver<T>::toString()const{
    std::stringstream ss;
    ss << "Saver: " << status;
    return ss.str();
}

#endif //SAVER_H
