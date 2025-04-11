#ifndef REPEAT_H
#define REPEAT_H

template <typename T, unsigned N>
struct Repeat {
    typedef T ValueType;

    ValueType operator()(const ValueType &val) const {
        ValueType ret = ValueType();
        for (unsigned int i = 0; i < N; ++i) {
            ret = ret + val;
        }
        return ret;
    }
};

#endif //REPEAT_H
