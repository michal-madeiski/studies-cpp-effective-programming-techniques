#ifndef RESULT_VOID_E_H
#define RESULT_VOID_E_H

#include "../Result_T_E.h"
#include<vector>

using namespace std;

template <typename E>
class Result<void, E> {
public:
    Result();
    Result(E *error);
    Result(vector<E*>& errors);
    Result(const Result<void, E>& other);

    ~Result();

    static Result<void, E> ok();
    static Result<void, E> fail(E* error);
    static Result<void, E> fail(vector<E*>& errors);

    Result<void, E>& operator=(const Result<void, E>& other);

    bool isSuccess();

    vector<E*>& getErrors();
private:
    vector<E*> errors;
};

template <typename E>
Result<void, E>::Result() {
}

template <typename E>
Result<void, E>::Result(E* error) {
    this->errors.push_back(new E(*error));
}

template <typename E>
Result<void, E>::Result(vector<E*>& errors) {
    for (unsigned int i = 0; i < errors.size(); i++) {
        this->errors.push_back(new E(*(errors[i])));
    }
}

template <typename E>
Result<void, E>::Result(const Result<void, E>& other) {
    for (unsigned int i = 0; i < other.errors.size(); i++) {
        this->errors.push_back(new E(*(other.errors[i])));
    }
}

template <typename E>
Result<void, E>::~Result() {
    for(unsigned int i = 0 ; i < errors.size(); ++i){
        if(errors[i] != NULL) delete errors[i];
    }
    errors.clear();
}

template<typename E>
Result<void, E> Result<void, E>::ok() {
    return Result<void, E>();
}

template<typename E>
Result<void, E> Result<void, E>::fail(E* error) {
    return Result<void, E>(error);
}

template<typename E>
Result<void, E> Result<void, E>::fail(vector<E*>& errors) {
    return Result<void, E>(errors);
}

template <typename E>
Result<void, E>& Result<void, E>::operator=(const Result<void, E>& other) {
    return Result<void, E>(other);
}

template <typename E>
bool Result<void, E>::isSuccess() {
    return errors.empty();
}

template <typename E>
vector<E*>& Result<void, E>::getErrors() {
    return errors;
}

#endif //RESULT_VOID_E_H
