#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include "Mapper.h"
#include "Repeat.h"

int main() {
    Mapper< Repeat<int, 3> > map_int;
    Mapper< Repeat<std::string, 2> > map_str;

    std::vector<int> vec_int;
    for(int i = 1; i <= 5; ++i){ vec_int.push_back(i); };
    map_int(vec_int);

    // test dla int
    {
        static const int res[] = {3, 6, 9, 12, 15};
        std::vector<int> test(res, res + 5);
        std::cout << "test: "; for (int i = 0; i < test.size(); ++i) { std::cout << test[i] << " "; };

        std::cout << std::endl;

        std::cout << "vec_int: "; for (int i = 0; i < vec_int.size(); ++i) { std::cout << vec_int[i] << " "; };
        assert(test == vec_int);
    }

    std::cout << std::endl << std::endl;

    std::vector<std::string> vec_str;
    vec_str.push_back("foo"); vec_str.push_back("bar");
    map_str(vec_str);

    // test dla str
    {
        static const char* res[] = {"foofoo", "barbar"};
        std::vector<std::string> test(res, res + 2);
        std::cout << "test: "; for (int i = 0; i < test.size(); ++i) { std::cout << test[i] << " "; };

        std::cout << std::endl;

        std::cout << "vec_str: "; for (int i = 0; i < vec_str.size(); ++i) { std::cout << vec_str[i] << " "; };
        assert(test == vec_str);
    }

    std::cout << std::endl;
    return 0;
}
