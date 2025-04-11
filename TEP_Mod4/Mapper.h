#ifndef MAPPER_H
#define MAPPER_H

#include <vector>

template <class Funct>
struct Mapper {

    std::vector<typename Funct::ValueType> operator()(std::vector<typename Funct::ValueType> &vec) const {
        Funct funct;
        for (int i = 0; i < vec.size(); ++i) {
            vec[i] = funct(vec[i]);
        }
        return vec;
    }
};

#endif //MAPPER_H
