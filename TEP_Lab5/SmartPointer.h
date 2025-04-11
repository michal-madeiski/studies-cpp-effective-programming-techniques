#ifndef SMARTPOINTER_H
#define SMARTPOINTER_H
#include "RefCounter.h"
using namespace std;

template <typename T>
class SmartPointer {
public:
    explicit SmartPointer(T *pointer);
    SmartPointer(const SmartPointer<T> &other);

    ~SmartPointer();

    T &operator*();
    T *operator->();

    SmartPointer<T> &operator=(const SmartPointer<T> &other);

    //mod5
    SmartPointer(SmartPointer<T> &&other);
    SmartPointer<T> &operator=(SmartPointer<T> &&other);
    //mod5

private:
    RefCounter *counter;
    T *pointer;
};

template<typename T>
SmartPointer<T>::SmartPointer(T *pointer) {
    this->pointer = pointer;
    counter = new RefCounter();
    counter->add();
}

template<typename T>
SmartPointer<T>::SmartPointer(const SmartPointer<T> &other) {
    pointer = other.pointer;
    counter = other.counter;
    counter->add();
}

template<typename T>
SmartPointer<T>::~SmartPointer() {
    if (counter != nullptr && counter->dec() == 0) {
        delete pointer;
        delete counter;
    }
}

template<typename T>
T& SmartPointer<T>::operator*() { return *pointer; };

template<typename T>
T* SmartPointer<T>::operator->() { return pointer; }

template<typename T>
SmartPointer<T> &SmartPointer<T>::operator=(const SmartPointer<T> &other) {
    if (this != &other) {
        if (counter != nullptr && counter->dec() == 0) {
            delete pointer;
            delete counter;
        }
        pointer = other.pointer;
        counter = other.counter;
        counter->add();
    }
    return *this;
}

//mod5
template<typename T>
SmartPointer<T>::SmartPointer(SmartPointer<T> &&other) {
    pointer = move(other.pointer);
    counter = other.counter;

    other.pointer = nullptr;
    other.counter = nullptr;
}

template<typename T>
SmartPointer<T> &SmartPointer<T>::operator=(SmartPointer<T> &&other) {
    if (this != &other) {
        if (counter != nullptr && counter->dec() == 0) {
            delete pointer;
            delete counter;
        }
        pointer = move(other.pointer);
        counter = other.counter;

        other.pointer = nullptr;
        other.counter = nullptr;
    }
    return *this;
}
//mod5

#endif //SMARTPOINTER_H
