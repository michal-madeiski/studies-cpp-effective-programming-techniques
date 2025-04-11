#ifndef RESULT_T_E_H
#define RESULT_T_E_H

#include <iostream>
#include <vector>

using namespace std;

template<typename T, typename E>
class Result {
public:
    Result(const T &val);
    Result(E *error);
    Result(vector<E *> &errors);
    Result(const Result<T, E> &other);

    ~Result();

    static Result<T, E> ok(const T &val);
    static Result<T, E> fail(E *error);
    static Result<T, E> fail(vector<E *> &errors);

    Result<T, E> &operator=(const Result<T, E> &other);

    bool isSuccess();

    T getVal();
    vector<E *> &getErrors();

    void print();
private:
    T *val;
    vector<E *> errors;
};

template<typename T, typename E>
Result<T, E>::Result(const T &val) {
    this->val = new T(val);
}

template<typename T, typename E>
Result<T, E>::Result(E *error) {
    val = NULL;
    this->errors.push_back(new E(*error));
}

template<typename T, typename E>
Result<T, E>::Result(vector<E *> &errors) {
    val = NULL;
    for (unsigned int i = 0; i < errors.size(); i++) {
        this->errors.push_back(new E(*(errors[i])));
    }
}

template<typename T, typename E>
Result<T, E>::Result(const Result<T, E> &other) {
    if (other.val == NULL) val = NULL;
    else this->val = new T(*(other.val));
    for (unsigned int i = 0; i < other.errors.size(); i++) {
        this->errors.push_back(new E(*(other.errors[i])));
    }
}

template<typename T, typename E>
Result<T, E>::~Result() {
    if (val != NULL) delete val;
    for (unsigned int i = 0; i < errors.size(); ++i) {
        if (errors[i] != NULL) delete errors[i];
    }
    errors.clear();
}

template<typename T, typename E>
Result<T, E> Result<T, E>::ok(const T &val) {
    return Result<T, E>(val);
}

template<typename T, typename E>
Result<T, E> Result<T, E>::fail(E *error) {
    return Result<T, E>(error);
}

template<typename T, typename E>
Result<T, E> Result<T, E>::fail(vector<E *> &errors) {
    return Result<T, E>(errors);
}

template<typename T, typename E>
Result<T, E> &Result<T, E>::operator=(const Result<T, E> &other) {
    return Result<T, E>(other);
}

template<typename T, typename E>
bool Result<T, E>::isSuccess() {
    return errors.empty();
}

template<typename T, typename E>
T Result<T, E>::getVal() {
    return *val;
}

template<typename T, typename E>
vector<E *> &Result<T, E>::getErrors() {
    return errors;
}

template<typename T, typename E>
void Result<T, E>::print() {
    if (isSuccess()) {
        std::cout << getVal() << "\n";
    } else {
        for (unsigned int i = 0; i < getErrors().size(); ++i) {
            std::cout << *(getErrors()[i]) << "\n";
        }
    }
}

#endif //RESULT_T_E_H
